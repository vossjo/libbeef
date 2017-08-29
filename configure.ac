AC_INIT(libbeef, 0.1.2, vossj@slac.stanford.edu)

PACKAGE=libbeef
VERSION=0.1.2

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

AC_PROG_CC
AX_COMPILER_VENDOR
AX_CC_MAXOPT
AX_CHECK_COMPILE_FLAG(-std=c99, CFLAGS="$CFLAGS -std=c99")
AX_CHECK_COMPILE_FLAG(-no-prec-div -xHost, CFLAGS="$CFLAGS -no-prec-div -xHost")

AC_HEADER_STDC

AC_PROG_RANLIB
AC_PROG_INSTALL


AC_OUTPUT(Makefile src/Makefile)

touch aclocal.m4
touch Makefile.in
touch configure
touch config.sub
touch config.status
