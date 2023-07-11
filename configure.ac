#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([ficonic], [0.0.1], [])
AC_CONFIG_SRCDIR([src/Curler.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.32.0], [], [version 1.32.0 or better of the Boost C++ libraries is required.])
AX_BOOST_PROGRAM_OPTIONS
AC_SEARCH_LIBS(curl_version_info, curl, [])

### Check for C++ library htmlcxx.
### ( Based on information from https://dev.to/keelefi/my-autoconf-primer-1jkb
### ( and https://nerdland.net/2009/07/detecting-c-libraries-with-autotools/
### ( and https://www.gnu.org/software/autoconf/manual/autoconf-2.67/html_node/Printing-Messages.html
### ( and https://stackoverflow.com/a/48132112
### ( and https://stackoverflow.com/a/8290120
AC_LANG_PUSH([C++])
SAVED_LDFLAGS=$LDFLAGS
LDFLAGS="$LDFLAGS -lhtmlcxx"
AC_MSG_CHECKING([for library htmlcxx])
AC_LINK_IFELSE(
	[AC_LANG_PROGRAM([#include <htmlcxx/html/ParserDom.h>], [htmlcxx::HTML::ParserDom testparser])],
	[AC_MSG_RESULT([yes])],
	[
		AC_MSG_RESULT([no])
		LDFLAGS=$SAVED_LDFLAGS
	]
)
AC_LANG_POP([C++])
###

LIBS="$BOOST_PROGRAM_OPTIONS_LIB $LIBS"

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
