/**********************************************************************

  error.c -

  $Author: matz $
  $Date: 2002/09/03 05:20:06 $
  created at: Mon Aug  9 16:11:34 JST 1993

  Copyright (C) 1993-2002 Yukihiro Matsumoto

**********************************************************************/

#include "ruby.h"
#include "env.h"
#include "version.h"

#include <stdio.h>
#ifdef HAVE_STDARG_PROTOTYPES
#include <stdarg.h>
#define va_init_list(a,b) va_start(a,b)
#else
#include <varargs.h>
#define va_init_list(a,b) va_start(a)
#endif

#if defined __CYGWIN__
# include <cygwin/version.h>
# if (CYGWIN_VERSION_API_MAJOR > 0) || (CYGWIN_VERSION_API_MINOR >= 8)
#  define sys_nerr _sys_nerr
# endif
#endif

int ruby_nerrs;

