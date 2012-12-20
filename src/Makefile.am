bin_PROGRAMS=cSnake
cSnake_SOURCES=main.c cSnake.c

cSnake_LDADD = @NCURSES_DEP_LIBS@

AM_CFLAGS = -g3 -O0 \
	-D_GNU_SOURCE \
	@cSnake_CFLAGS@ \
	@NCURSES_DEP_CFLAGS@
