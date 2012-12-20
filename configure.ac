dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(cSnake, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([-Wall])

AC_PROG_CC

AM_PROG_CC_C_O 

PKG_CHECK_MODULES(NCURSES_DEP, [ncurses])


AC_CONFIG_SUBDIRS( cSnake )
	cSnake_CFLAGS="-I\$(top_srcdir)/include"
AC_SUBST(cSnake_CFLAGS)


AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

