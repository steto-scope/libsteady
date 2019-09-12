AC_PREREQ(2.59)
AC_INIT([steady], [0.1.0], [mail@example.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PATH_CHECK

dnl Initialize Libtool
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT
AC_PROG_LIBTOOL

AC_CONFIG_FILES(Makefile 
                src/Makefile
                tests/Makefile
                )

AC_OUTPUT