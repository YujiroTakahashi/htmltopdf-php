dnl config.m4 for extension htmltopdf

PHP_ARG_ENABLE(htmltopdf, whether to enable htmltopdf support,
dnl Make sure that the comment is aligned:
[  --enable-htmltopdf          Enable htmltopdf support], no)

if test "$PHP_HTMLTOPDF" != "no"; then
  # --with-htmltopdf -> check with-path
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="/include/wkhtmltox/pdf.h"
  if test -r $PHP_HTMLTOPDF/$SEARCH_FOR; then # path given as parameter
    WKHTMLTOX_DIR=$PHP_HTMLTOPDF
  else # search default path list
    AC_MSG_CHECKING([for wkhtmltox files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        WKHTMLTOX_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$WKHTMLTOX_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the wkhtmltox distribution, "$PHP_HTMLTOPDF"])
  fi

  # --with-wkhtmltox -> add include path
  PHP_ADD_INCLUDE($WKHTMLTOX_DIR/include/wkhtmltox)

  # --with-wkhtmltox -> check for lib and symbol presence
  LIBNAME="HTMLTOPDF"
  LIBSYMBOL="wkhtmltopdf_init"

  PHP_SUBST(HTMLTOPDF_SHARED_LIBADD)

  PHP_ADD_LIBRARY(wkhtmltox, 1, HTMLTOPDF_SHARED_LIBADD)


  dnl # In case of no dependencies
  AC_DEFINE(HAVE_HTMLTOPDF, 1, [ Have htmltopdf support ])

  PHP_NEW_EXTENSION(htmltopdf, htmltopdf.c, $ext_shared)
fi
