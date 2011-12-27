SHELL = /bin/sh

#### Start of system configuration section. ####

srcdir = .
VPATH = $(srcdir)/missing

CC = gcc
YACC = yacc
PURIFY =
AUTOCONF = autoconf

DESTDIR = ..

prefix = /usr/local
CFLAGS = -g -O2
CPPFLAGS = -I. -I$(srcdir)
LDFLAGS =  $(CFLAGS) -rdynamic
XLDFLAGS = 
EXTLIBS = 
LIBS = -ldl -lcrypt -lm  $(EXTLIBS)
MISSING =  
LDSHARED = gcc -shared
DLDFLAGS = 
SOLIBS = 
MAINLIBS = 

RUBY_INSTALL_NAME=ruby
RUBY_SO_NAME=
EXEEXT = 
PROGRAM=$(RUBY_INSTALL_NAME)$(EXEEXT)

#### End of system configuration section. ####

MAJOR=	1
MINOR=	7
TEENY=	3

LIBRUBY_A     = lib$(RUBY_INSTALL_NAME).a
LIBRUBY_SO    = lib$(RUBY_INSTALL_NAME).so.$(MAJOR).$(MINOR).$(TEENY)
LIBRUBY_ALIASES= lib$(RUBY_INSTALL_NAME).so
LIBRUBY	      = $(LIBRUBY_A)
LIBRUBYARG    = $(LIBRUBY_A)

EXTOBJS	      = 

MAINOBJ	      = main.o

OBJS	      = array.o \
		bignum.o \
		class.o \
		compar.o \
		dir.o \
		dln.o \
		enum.o \
		error.o \
		eval.o \
		file.o \
		gc.o \
		hash.o \
		inits.o \
		io.o \
		marshal.o \
		math.o \
		numeric.o \
		object.o \
		pack.o \
		parse.o \
		process.o \
		prec.o \
		random.o \
		range.o \
		re.o \
		regex.o \
		ruby.o \
		signal.o \
		sprintf.o \
		st.o \
		string.o \
		struct.o \
		time.o \
		util.o \
		variable.o \
		version.o \
		$(MISSING)

all:		miniruby$(EXEEXT)  rbconfig.rb $(LIBRUBY)
		@./miniruby$(EXEEXT) $(srcdir)/ext/extmk.rb 

miniruby$(EXEEXT):	config.status $(LIBRUBY_A) $(MAINOBJ) dmyext.o
		@rm -f $@
		$(PURIFY) $(CC) $(LDFLAGS) $(MAINOBJ) dmyext.o $(LIBRUBY_A) $(LIBS) -o $@

$(PROGRAM):     $(LIBRUBY) $(MAINOBJ) $(EXTOBJS) 
		@rm -f $@
		$(PURIFY) $(CC) $(LDFLAGS) $(XLDFLAGS) $(MAINLIBS) $(MAINOBJ) $(EXTOBJS) $(LIBRUBYARG) $(LIBS) -o $@

$(LIBRUBY_A):	$(OBJS) dmyext.o
		ar rcu $@ $(OBJS) dmyext.o
		@-ranlib $@ 2> /dev/null || true

$(LIBRUBY_SO):	$(OBJS) dmyext.o miniruby$(EXEEXT)
		$(LDSHARED) $(DLDFLAGS) $(OBJS) dmyext.o $(SOLIBS) -o $@
		@-./miniruby$(EXEEXT) -e 'ARGV.each{|link| File.delete link if File.exist? link; \
						  File.symlink "$(LIBRUBY_SO)", link}' \
				$(LIBRUBY_ALIASES) || true

install:	rbconfig.rb
		./miniruby$(EXEEXT) $(srcdir)/instruby.rb $(DESTDIR)

clean-ext:;	@-./miniruby$(EXEEXT) $(srcdir)/ext/extmk.rb clean 2> /dev/null || true

clean-local:
		@rm -f $(OBJS) $(MAINOBJ) $(LIBRUBY_A) $(LIBRUBY_SO) $(LIBRUBY_ALIASES)
		@rm -f ext/extinit.c ext/extinit.o dmyext.o
		@rm -f $(PROGRAM) miniruby$(EXEEXT)

clean: clean-ext clean-local

distclean-ext:
		@-./miniruby$(EXEEXT) $(srcdir)/ext/extmk.rb distclean 2> /dev/null || true

distclean-local: clean-local
		@rm -f Makefile config.h rbconfig.rb
		@rm -f ext/config.cache config.cache config.log config.status
		@rm -f *~ core *.core gmon.out y.tab.c y.output ruby.imp

distclean: distclean-ext distclean-local

realclean: 	distclean
		@rm -f parse.c
		@rm -f lex.c

test:		miniruby$(EXEEXT) rbconfig.rb
		@./miniruby$(EXEEXT) $(srcdir)/rubytest.rb

rbconfig.rb:	miniruby$(EXEEXT) $(srcdir)/mkconfig.rb config.status
		@./miniruby$(EXEEXT) $(srcdir)/mkconfig.rb rbconfig.rb

fake.rb:	miniruby$(EXEEXT)
		@echo ' \
		class Object; \
		  remove_const :RUBY_PLATFORM; \
		  remove_const :RUBY_VERSION; \
		  RUBY_PLATFORM = "i686-linux"; \
		  RUBY_VERSION = "1.7.3"; \
		  CROSS_COMPILING = true; \
		end \
		' > $@

config.status:	$(srcdir)/configure
		$(SHELL) ./config.status --recheck

$(srcdir)/configure: $(srcdir)/configure.in
		cd $(srcdir) && $(AUTOCONF)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

lex.c: keywords
	gperf -p -j1 -i 1 -g -o -t -N rb_reserved_word -k1,3,$$ $(srcdir)/keywords > lex.c

parse.c: parse.y
	$(YACC) $<
	mv -f y.tab.c parse.c

acosh.o: $(srcdir)/missing/acosh.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/acosh.c

alloca.o: $(srcdir)/missing/alloca.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/alloca.c

crypt.o: $(srcdir)/missing/crypt.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/crypt.c

dup2.o: $(srcdir)/missing/dup2.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/dup2.c

fileblocks.o: $(srcdir)/missing/fileblocks.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/fileblocks.c

finite.o: $(srcdir)/missing/finite.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/finite.c

flock.o: $(srcdir)/missing/flock.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/flock.c

isinf.o: $(srcdir)/missing/isinf.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/isinf.c

isnan.o: $(srcdir)/missing/isnan.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/isnan.c

fnmatch.o: $(srcdir)/missing/fnmatch.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/fnmatch.c

memcmp.o: $(srcdir)/missing/memcmp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/memcmp.c

memmove.o: $(srcdir)/missing/memmove.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/memmove.c

mkdir.o: $(srcdir)/missing/mkdir.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/mkdir.c

vsnprintf.o: $(srcdir)/missing/vsnprintf.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/vsnprintf.c

strcasecmp.o: $(srcdir)/missing/strcasecmp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strcasecmp.c

strncasecmp.o: $(srcdir)/missing/strncasecmp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strncasecmp.c

strchr.o: $(srcdir)/missing/strchr.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strchr.c

strerror.o: $(srcdir)/missing/strerror.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strerror.c

strftime.o: $(srcdir)/missing/strftime.c
	$(CC) -I. $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strftime.c

strstr.o: $(srcdir)/missing/strstr.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strstr.c

strtol.o: $(srcdir)/missing/strtol.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strtol.c

strtoul.o: $(srcdir)/missing/strtoul.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/strtoul.c

x68.o: $(srcdir)/missing/x68.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/x68.c

os2.o: $(srcdir)/missing/os2.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/os2.c

dl_os2.o: $(srcdir)/missing/dl_os2.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(srcdir)/missing/dl_os2.c

win32.o: $(srcdir)/win32/win32.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(srcdir)/win32 -c $(srcdir)/win32/win32.c

# Prevent GNU make v3 from overflowing arg limit on SysV.
.NOEXPORT:
###
array.o: array.c ruby.h config.h defines.h intern.h missing.h \
  util.h st.h
bignum.o: bignum.c ruby.h config.h defines.h intern.h missing.h
class.o: class.c ruby.h config.h defines.h intern.h missing.h \
  rubysig.h node.h st.h
compar.o: compar.c ruby.h config.h defines.h intern.h missing.h
dir.o: dir.c ruby.h config.h defines.h intern.h missing.h util.h
dln.o: dln.c config.h defines.h dln.h
dmyext.o: dmyext.c
enum.o: enum.c ruby.h config.h defines.h intern.h missing.h node.h \
  util.h
error.o: error.c ruby.h config.h defines.h intern.h missing.h \
  env.h version.h
eval.o: eval.c ruby.h config.h defines.h intern.h missing.h node.h \
  env.h util.h rubysig.h st.h dln.h
file.o: file.c ruby.h config.h defines.h intern.h missing.h \
  rubyio.h rubysig.h util.h dln.h
gc.o: gc.c ruby.h config.h defines.h intern.h missing.h rubysig.h \
  st.h node.h env.h re.h regex.h
hash.o: hash.c ruby.h config.h defines.h intern.h missing.h st.h \
  util.h rubysig.h
inits.o: inits.c ruby.h config.h defines.h intern.h missing.h
io.o: io.c ruby.h config.h defines.h intern.h missing.h rubyio.h \
  rubysig.h env.h util.h
main.o: main.c ruby.h config.h defines.h intern.h missing.h
marshal.o: marshal.c ruby.h config.h defines.h intern.h missing.h \
  rubyio.h st.h
math.o: math.c ruby.h config.h defines.h intern.h missing.h
numeric.o: numeric.c ruby.h config.h defines.h intern.h missing.h
object.o: object.c ruby.h config.h defines.h intern.h missing.h \
  st.h
pack.o: pack.c ruby.h config.h defines.h intern.h missing.h
parse.o: parse.c ruby.h config.h defines.h intern.h missing.h \
  env.h node.h st.h regex.h util.h lex.c
prec.o: prec.c ruby.h config.h defines.h intern.h missing.h
process.o: process.c ruby.h config.h defines.h intern.h missing.h \
  rubysig.h st.h
random.o: random.c ruby.h config.h defines.h intern.h missing.h
range.o: range.c ruby.h config.h defines.h intern.h missing.h
re.o: re.c ruby.h config.h defines.h intern.h missing.h re.h \
  regex.h
regex.o: regex.c config.h regex.h
ruby.o: ruby.c ruby.h config.h defines.h intern.h missing.h dln.h \
  node.h util.h
signal.o: signal.c ruby.h config.h defines.h intern.h missing.h \
  rubysig.h
sprintf.o: sprintf.c ruby.h config.h defines.h intern.h missing.h
st.o: st.c config.h st.h
string.o: string.c ruby.h config.h defines.h intern.h missing.h \
  re.h regex.h
struct.o: struct.c ruby.h config.h defines.h intern.h missing.h
time.o: time.c ruby.h config.h defines.h intern.h missing.h
util.o: util.c ruby.h config.h defines.h intern.h missing.h util.h
variable.o: variable.c ruby.h config.h defines.h intern.h \
  missing.h env.h node.h st.h util.h
version.o: version.c ruby.h config.h defines.h intern.h missing.h \
  version.h
