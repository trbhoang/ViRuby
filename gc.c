/**********************************************************************

  gc.c -

  $Author: matz $
  $Date: 2002/09/06 08:59:38 $
  created at: Tue Oct  5 09:44:46 JST 1993

  Copyright (C) 1993-2002 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby.h"
#include "rubysig.h"
#include "st.h"
#include "node.h"
#include "env.h"
#include "re.h"
#include <stdio.h>
#include <setjmp.h>
#include <sys/types.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif


extern st_table *rb_class_tbl;
VALUE *rb_gc_stack_start = 0;

#ifdef DJGPP
static unsigned int STACK_LEVEL_MAX = 65535;
#else
#ifdef __human68k__
extern unsigned int _stacksize;
# define STACK_LEVEL_MAX (_stacksize - 4096)
# undef HAVE_GETRLIMIT
#else
#ifdef HAVE_GETRLIMIT
static unsigned int STACK_LEVEL_MAX = 655300;
#else
# define STACK_LEVEL_MAX 655300
#endif
#endif
#endif

VALUE rb_gc_start()
{
    rb_gc();
    return Qnil;
}

typedef struct RVALUE {
    union {
	struct {
	    unsigned long flags;	/* always 0 for freed obj */
	    struct RVALUE *next;
	} free;
	struct RBasic  basic;
	struct RObject object;
	struct RClass  klass;
	struct RFloat  flonum;
	struct RString string;
	struct RArray  array;
	struct RRegexp regexp;
	struct RHash   hash;
	struct RData   data;
	struct RStruct rstruct;
	struct RBignum bignum;
	struct RFile   file;
	struct RNode   node;
	struct RMatch  match;
	struct RVarmap varmap;
	struct SCOPE   scope;
    } as;
} RVALUE;

static RVALUE *freelist = 0;
static RVALUE *deferred_final_list = 0;

#define HEAPS_INCREMENT 10
static RVALUE **heaps;
static int heaps_length = 0;
static int heaps_used   = 0;

#define HEAP_MIN_SLOTS 10000
static int *heaps_limits;
static int heap_slots = HEAP_MIN_SLOTS;

#define FREE_MIN  4096

static RVALUE *himem, *lomem;

static void add_heap()
{
    RVALUE *p, *pend;

    if (heaps_used == heaps_length) {
	/* Realloc heaps */
	heaps_length += HEAPS_INCREMENT;
	RUBY_CRITICAL(heaps = (heaps_used>0)?
			(RVALUE**)realloc(heaps, heaps_length*sizeof(RVALUE*)):
			(RVALUE**)malloc(heaps_length*sizeof(RVALUE*)));
	if (heaps == 0) rb_memerror();
	RUBY_CRITICAL(heaps_limits = (heaps_used>0)?
			(int*)realloc(heaps_limits, heaps_length*sizeof(int)):
			(int*)malloc(heaps_length*sizeof(int)));
	if (heaps_limits == 0) rb_memerror();
    }

    for (;;) {
	RUBY_CRITICAL(p = heaps[heaps_used] = (RVALUE*)malloc(sizeof(RVALUE)*heap_slots));
	heaps_limits[heaps_used] = heap_slots;
	if (p == 0) {
	    if (heap_slots == HEAP_MIN_SLOTS) {
		rb_memerror();
	    }
	    heap_slots = HEAP_MIN_SLOTS;
	    continue;
	}
	break;
    }
    pend = p + heap_slots;
    if (lomem == 0 || lomem > p) lomem = p;
    if (himem < pend) himem = pend;
    heaps_used++;
    heap_slots *= 1.8;

    while (p < pend) {
	p->as.free.flags = 0;
	p->as.free.next = freelist;
	freelist = p;
	p++;
    }
}

#define RANY(o) ((RVALUE*)(o))

VALUE
rb_newobj()
{
    VALUE obj;

    if (!freelist) rb_gc();

    obj = (VALUE)freelist;
    freelist = freelist->as.free.next;
    MEMZERO((void*)obj, RVALUE, 1);
    return obj;
}

void Init_stack(addr)
     VALUE *addr;
{
#if defined(__human68k__)
    extern void *_SEND;
    rb_gc_stack_start = _SEND;
#else
    VALUE start;

    if (!addr) addr = &start;
    rb_gc_stack_start = addr;
#endif
#ifdef HAVE_GETRLIMIT
    {
	struct rlimit rlim;

	if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
	    double space = (double)rlim.rlim_cur*0.2;

	    if (space > 1024*1024) space = 1024*1024;
	    STACK_LEVEL_MAX = (rlim.rlim_cur - space) / sizeof(VALUE);
	}
    }
#endif
}

void Init_heap()
{
    if (!rb_gc_stack_start) {
	Init_stack(0);
    }
    add_heap();
}

void *
ruby_xmalloc(size)
    long size;
{
    void *mem;

    if (size < 0) {
	rb_raise(rb_eNoMemError, "negative allocation size (or too big)");
    }
    if (size == 0) size = 1;

    RUBY_CRITICAL(mem = malloc(size));
    if (!mem) {
	rb_gc();
	RUBY_CRITICAL(mem = malloc(size));
	if (!mem) {
	    rb_memerror();
	}
    }

    return mem;
}

void rb_gc_force_recycle(p)
     VALUE p;
{
    RANY(p)->as.free.flags = 0;
    RANY(p)->as.free.next = freelist;
    freelist = RANY(p);
}
