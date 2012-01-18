/**********************************************************************

  eval.c -

  $Author: nobu $
  $Date: 2002/09/11 09:58:02 $
  created at: Thu Jun 10 14:22:17 JST 1993

  Copyright (C) 1993-2002 Yukihiro Matsumoto
  Copyright (C) 2000  Network Applied Communication Laboratory, Inc.
  Copyright (C) 2000  Information-technology Promotion Agency, Japan

**********************************************************************/

#include "ruby.h"
#include "node.h"
#include "env.h"
#include "util.h"
#include "rubysig.h"

#include <stdio.h>
#include <setjmp.h>
#include "st.h"
#include "dln.h"

static int scope_vmode;
#define SCOPE_PUBLIC    0
#define SCOPE_PRIVATE   1
#define SCOPE_PROTECTED 2
#define SCOPE_MODFUNC   5
#define SCOPE_MASK      7
#define SCOPE_SET(f)  (scope_vmode=(f))
#define SCOPE_TEST(f) (scope_vmode&(f))

static NODE* ruby_last_node;
NODE* ruby_current_node;
int ruby_safe_level = 0;
/* safe-level:
   0 - strings from streams/environment/ARGV are tainted (default)
   1 - no dangerous operation by tainted value
   2 - process/file operations prohibited
   3 - all genetated objects are tainted
   4 - no global (non-tainted) variable modification/no direct output
*/

static VALUE safe_getter _((void));
static void safe_setter _((VALUE val));
struct FRAME *ruby_frame;


struct SCOPE *ruby_scope;
static struct FRAME *top_frame;
static struct SCOPE *top_scope;

extern VALUE ruby_top_self;

static NODE *ruby_cref = 0;
static NODE *top_cref;
#define PUSH_CREF(c) ruby_cref = rb_node_newnode(NODE_CREF,(c),0,ruby_cref)
#define POP_CREF() ruby_cref = ruby_cref->nd_next

struct iter {
    int iter;
    struct iter *prev;
};
static struct iter *ruby_iter;

#define ITER_NOT 0
#define ITER_PRE 1
#define ITER_CUR 2

#define PUSH_ITER(i) do {		\
    struct iter _iter;			\
    _iter.prev = ruby_iter;		\
    _iter.iter = (i);			\
    ruby_iter = &_iter

#define POP_ITER()			\
    ruby_iter = _iter.prev;		\
} while (0)

struct tag {
    jmp_buf buf;
    struct FRAME *frame;
    struct iter *iter;
    ID tag;
    VALUE retval;
    struct SCOPE *scope;
    int dst;
    struct tag *prev;
};
static struct tag *prot_tag;

#define PUSH_TAG(ptag) do {		\
    struct tag _tag;			\
    _tag.retval = Qnil;			\
    _tag.frame = ruby_frame;		\
    _tag.iter = ruby_iter;		\
    _tag.prev = prot_tag;		\
    _tag.scope = ruby_scope;		\
    _tag.tag = ptag;			\
    _tag.dst = 0;			\
    prot_tag = &_tag

#define PROT_NONE   0
#define PROT_FUNC   -1
#define PROT_THREAD -2

#define EXEC_TAG()    setjmp(prot_tag->buf)

#define JUMP_TAG(st) do {		\
    ruby_frame = prot_tag->frame;	\
    ruby_iter = prot_tag->iter;		\
    longjmp(prot_tag->buf,(st));	\
} while (0)

#define POP_TAG()			\
    if (_tag.prev)			\
        _tag.prev->retval = _tag.retval;\
    prot_tag = _tag.prev;		\
} while (0)

#define POP_TMPTAG()			\
    prot_tag = _tag.prev;		\
} while (0)

#define TAG_RETURN	0x1
#define TAG_BREAK	0x2
#define TAG_NEXT	0x3
#define TAG_RETRY	0x4
#define TAG_REDO	0x5
#define TAG_RAISE	0x6
#define TAG_THROW	0x7
#define TAG_FATAL	0x8
#define TAG_MASK	0xf

VALUE ruby_errinfo = Qnil;
extern NODE *ruby_eval_tree_begin;
extern NODE *ruby_eval_tree;
extern int ruby_nerrs;

#define PUSH_SCOPE() do {		\
    volatile int _vmode = scope_vmode;	\
    struct SCOPE * volatile _old;	\
    NEWOBJ(_scope, struct SCOPE);	\
    OBJSETUP(_scope, 0, T_SCOPE);	\
    _scope->local_tbl = 0;		\
    _scope->local_vars = 0;		\
    _scope->flags = 0;			\
    _old = ruby_scope;			\
    ruby_scope = _scope;		\
    scope_vmode = SCOPE_PUBLIC

typedef struct thread * rb_thread_t;
static rb_thread_t curr_thread = 0;
static rb_thread_t main_thread;
static void scope_dup _((struct SCOPE *));

#define POP_SCOPE() 			\
    if (ruby_scope->flags & SCOPE_DONT_RECYCLE) {\
       if (_old) scope_dup(_old);	\
    }					\
    if (!(ruby_scope->flags & SCOPE_MALLOC)) {\
	ruby_scope->local_vars = 0;	\
	ruby_scope->local_tbl  = 0;	\
	if (!(ruby_scope->flags & SCOPE_DONT_RECYCLE) && \
            ruby_scope != top_scope) {	\
	    rb_gc_force_recycle((VALUE)ruby_scope);\
        }				\
    }					\
    ruby_scope->flags |= SCOPE_NOSTACK;	\
    ruby_scope = _old;			\
    scope_vmode = _vmode;		\
} while (0)

static VALUE rb_eval _((VALUE,NODE*));
static VALUE eval _((VALUE,VALUE,VALUE,char*,int));
static NODE *compile _((VALUE, char*, int));

static VALUE rb_yield_0 _((VALUE, VALUE, VALUE, int));
static VALUE rb_call _((VALUE,VALUE,ID,int,const VALUE*,int));
static VALUE module_setup _((VALUE,NODE*));

static VALUE massign _((VALUE,NODE*,VALUE,int));
static void assign _((VALUE,NODE*,VALUE,int));

static VALUE trace_func = 0;
static int tracing = 0;
static void call_trace_func _((char*,NODE*,VALUE,ID,VALUE));

#define SET_CURRENT_SOURCE() (ruby_sourcefile = ruby_current_node->nd_file, \
			      ruby_sourceline = nd_line(ruby_current_node))

static void error_print()
{
    VALUE errat = Qnil;		/* OK */
    volatile VALUE eclass;
    char *einfo;
    long elen;

    if (NIL_P(ruby_errinfo)) return;

    PUSH_TAG(PROT_NONE);
    if (EXEC_TAG() == 0) {
	errat = get_backtrace(ruby_errinfo);
    }
    else {
	errat = Qnil;
    }
    POP_TAG();
    if (NIL_P(errat)){
	ruby_set_current_source();
	if (ruby_sourcefile)
	    fprintf(stderr, "%s:%d", ruby_sourcefile, ruby_sourceline);
	else
	    fprintf(stderr, "%d", ruby_sourceline);
    }
    else if (RARRAY(errat)->len == 0) {
	error_pos();
    }
    else {
	VALUE mesg = RARRAY(errat)->ptr[0];

	if (NIL_P(mesg)) error_pos();
	else {
	    fwrite(RSTRING(mesg)->ptr, 1, RSTRING(mesg)->len, stderr);
	}
    }

    eclass = CLASS_OF(ruby_errinfo);
    PUSH_TAG(PROT_NONE);
    if (EXEC_TAG() == 0) {
	VALUE e = rb_obj_as_string(ruby_errinfo);
	einfo = RSTRING(e)->ptr;
	elen = RSTRING(e)->len;
    }
    else {
	einfo = "";
	elen = 0;
    }
    POP_TAG();
    if (eclass == rb_eRuntimeError && elen == 0) {
	fprintf(stderr, ": unhandled exception\n");
    }
    else {
	VALUE epath;

	epath = rb_class_path(eclass);
	if (elen == 0) {
	    fprintf(stderr, ": ");
	    fwrite(RSTRING(epath)->ptr, 1, RSTRING(epath)->len, stderr);
	    putc('\n', stderr);
	}
	else {
	    char *tail  = 0;
	    long len = elen;

	    if (RSTRING(epath)->ptr[0] == '#') epath = 0;
	    if (tail = strchr(einfo, '\n')) {
		len = tail - einfo;
		tail++;		/* skip newline */
	    }
	    fprintf(stderr, ": ");
	    fwrite(einfo, 1, len, stderr);
	    if (epath) {
		fprintf(stderr, " (");
		fwrite(RSTRING(epath)->ptr, 1, RSTRING(epath)->len, stderr);
		fprintf(stderr, ")\n");
	    }
	    if (tail) {
		fwrite(tail, 1, elen-len-1, stderr);
		putc('\n', stderr);
	    }
	}
    }

    if (!NIL_P(errat)) {
	long i;
	struct RArray *ep = RARRAY(errat);

#define TRACE_MAX (TRACE_HEAD+TRACE_TAIL+5)
#define TRACE_HEAD 8
#define TRACE_TAIL 5

	ep = RARRAY(errat);
	for (i=1; i<ep->len; i++) {
	    if (TYPE(ep->ptr[i]) == T_STRING) {
		fprintf(stderr, "\tfrom %s\n", RSTRING(ep->ptr[i])->ptr);
	    }
	    if (i == TRACE_HEAD && ep->len > TRACE_MAX) {
		fprintf(stderr, "\t ... %ld levels...\n",
			ep->len - TRACE_HEAD - TRACE_TAIL);
		i = ep->len - TRACE_TAIL;
	    }
	}
    }
}


#if !defined(NT) && !defined(__MACOS__)
extern char **environ;
#endif
char **rb_origenviron;

void rb_call_inits _((void));
void Init_stack _((void*));
void Init_heap _((void));
void Init_ext _((void));

void ruby_init()
{
    static int initialized = 0;
    static struct FRAME frame;
    static struct iter iter;
    int state;

    if (initialized)
	return;
    initialized = 1;

    ruby_frame = top_frame = &frame;
    ruby_iter = &iter;

#ifdef __MACOS__
    rb_origenviron = 0;
#else
    rb_origenviron = environ;
#endif

    Init_stack(0);
    Init_heap();
    PUSH_SCOPE();
    ruby_scope->local_vars = 0;
    ruby_scope->local_tbl = 0;
    top_scope = ruby_scope;
    /* default visibility is private at toplevel */
    SCOPE_SET(SCOPE_PRIVATE);

    PUSH_TAG(PROT_NONE);
    if ((state = EXEC_TAG()) == 0) {
	rb_call_inits();
	ruby_class = rb_cObject;
	ruby_frame->self = ruby_top_self;
	top_cref = rb_node_newnode(NODE_CREF, rb_cObject, 0, 0);
	ruby_cref = top_cref;
	ruby_frame->cbase = (VALUE)ruby_cref;
	rb_define_global_const("TOPLEVEL_BINDING", rb_f_binding(ruby_top_self));
#ifdef __MACOS__
	_macruby_init();
#endif
	ruby_prog_init();
    }
    POP_TAG();
    if (state) error_print();
    POP_SCOPE();
    ruby_scope = top_scope;
}

static int error_handle(ex)
    int ex;
{
    switch (ex & TAG_MASK) {
    case 0:
        ex = 0;
	break;
    case TAG_RETURN:
	error_pos();
	fprintf(stderr, ": unexpected return\n");
	ex = 1;
	break;
      case TAG_NEXT:
	error_pos();
	fprintf(stderr, ": unexpected next\n");
	ex = 1;
	break;
      case TAG_BREAK:
	error_pos();
	fprintf(stderr, ": unexpected break\n");
	ex = 1;
	break;
      case TAG_REDO:
	error_pos();
	fprintf(stderr, ": unexpected redo\n");
	ex = 1;
	break;
      case TAG_RETRY:
	error_pos();
	fprintf(stderr, ": retry outside of rescue clause\n");
	ex = 1;
	break;
      case TAG_THROW:
	if (prot_tag && prot_tag->frame && prot_tag->frame->node) {
	    NODE *tag = prot_tag->frame->node;
	    fprintf(stderr, "%s:%d: uncaught throw\n",
		    tag->nd_file, nd_line(tag));
	}
	else {
	    error_pos();
	    fprintf(stderr, ": unexpected throw\n");
	}
	ex = 1;
	break;
      case TAG_RAISE:
      case TAG_FATAL:
	if (rb_obj_is_kind_of(ruby_errinfo, rb_eSystemExit)) {
	    VALUE st = rb_iv_get(ruby_errinfo, "status");
	    ex = NIL_P(st) ? 1 : NUM2INT(st);
	}
	else {
	    error_print();
	    ex = 1;
	}
	break;
      default:
	rb_bug("Unknown longjmp status %d", ex);
	break;
    }
    return ex;
}

void ruby_options(argc, argv)
     int argc;
     char **argv;
{
     int state;

     PUSH_TAG(PROT_NONE);
     if ((state = EXEC_TAG()) == 0) {
         ruby_process_options(argc, argv);
     }
     if (state) {
         trace_func = 0;
         tracing = 0;
exit(error_handle(state));
     }
POP_TAG();
}

void ruby_run()
{
    int state;
    static int ex;
    volatile NODE *tmp;

    if (ruby_nerrs > 0) exit(ruby_nerrs);

    Init_stack((void*)&tmp);
    PUSH_TAG(PROT_NONE);
    PUSH_ITER(ITER_NOT);
    if ((state = EXEC_TAG()) == 0) {
	eval_node(ruby_top_self, ruby_eval_tree);
    }
    POP_ITER();
    POP_TAG();

    if (state && !ex) ex = state;
    ruby_stop(ex);
}

static void
scope_dup(scope)
    struct SCOPE *scope;
{
    ID *tbl;
    VALUE *vars;

    scope->flags |= SCOPE_DONT_RECYCLE;
    if (scope->flags & SCOPE_MALLOC) return;

    if (scope->local_tbl) {
	tbl = scope->local_tbl;
	vars = ALLOC_N(VALUE, tbl[0]+1);
	*vars++ = scope->local_vars[-1];
	MEMCPY(vars, scope->local_vars, VALUE, tbl[0]);
	scope->local_vars = vars;
	scope->flags |= SCOPE_MALLOC;
    }
}

