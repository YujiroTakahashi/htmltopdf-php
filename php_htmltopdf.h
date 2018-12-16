/* htmltopdf extension for PHP */

#ifndef PHP_HTMLTOPDF_H
# define PHP_HTMLTOPDF_H

#include <stdbool.h>
#include <stdio.h>
#include <wkhtmltox/pdf.h>

extern zend_module_entry htmltopdf_module_entry;
# define phpext_htmltopdf_ptr &htmltopdf_module_entry

# define PHP_HTMLTOPDF_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_HTMLTOPDF)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_HTMLTOPDF_H */

