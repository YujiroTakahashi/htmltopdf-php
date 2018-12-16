/* htmltopdf extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_htmltopdf.h"

/* Print a message to stderr when an error occurs */
void error(wkhtmltopdf_converter * c, const char * msg) {
	fprintf(stderr, "Error: %s\n", msg);
}

/* Print a message to stderr when a warning is issued */
void warning(wkhtmltopdf_converter * c, const char * msg) {
	fprintf(stderr, "Warning: %s\n", msg);
}

/* {{{ string htmltopdf(string $url, string $output)
 */
PHP_FUNCTION(htmltopdf)
{
	wkhtmltopdf_global_settings * gs;
	wkhtmltopdf_object_settings * os;
	wkhtmltopdf_converter * c;

	int code;
	char *url;
	size_t url_len;
	char *output;
	size_t output_len;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_STRING(url, url_len)
		Z_PARAM_STRING(output, output_len)
	ZEND_PARSE_PARAMETERS_END();

	/* Init wkhtmltopdf in graphics less mode */
	wkhtmltopdf_init(false);

	/*
	 * Create a global settings object used to store options that are not
	 * related to input objects, note that control of this object is parsed to
	 * the converter later, which is then responsible for freeing it
	 */
	gs = wkhtmltopdf_create_global_settings();
	/* We want the result to be storred in the file called test.pdf */
	wkhtmltopdf_set_global_setting(gs, "out", "test.pdf");
	wkhtmltopdf_set_global_setting(gs, "load.cookieJar", "myjar.jar");

	/*
	 * Create a input object settings object that is used to store settings
	 * related to a input object, note again that control of this object is parsed to
	 * the converter later, which is then responsible for freeing it
	 */
	os = wkhtmltopdf_create_object_settings();
	/* We want to convert to convert the qstring documentation page */
	wkhtmltopdf_set_object_setting(os, "page", "https://www.yahoo.co.jp");

	/* Create the actual converter object used to convert the pages */
	c = wkhtmltopdf_create_converter(gs);

	/* Call the error function when an error occurs */
	wkhtmltopdf_set_error_callback(c, error);

	/* Call the warning function when a warning is issued */
	wkhtmltopdf_set_warning_callback(c, warning);

	/*
	 * Add the the settings object describing the qstring documentation page
	 * to the list of pages to convert. Objects are converted in the order in which
	 * they are added
	 */
	wkhtmltopdf_add_object(c, os, NULL);

	/* Perform the actual conversion */
	if (!wkhtmltopdf_convert(c)) {
		fprintf(stderr, "Conversion failed!");
	}
	code = wkhtmltopdf_http_error_code(c);

	wkhtmltopdf_destroy_converter(c);
	wkhtmltopdf_deinit();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_LONG(code);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(htmltopdf)
{
#if defined(ZTS) && defined(COMPILE_DL_HTMLTOPDF)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(htmltopdf)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "htmltopdf support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_htmltopdf_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_htmltopdf_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ htmltopdf_functions[]
 */
static const zend_function_entry htmltopdf_functions[] = {
	PHP_FE(htmltopdf_test1,		arginfo_htmltopdf_test1)
	PHP_FE(htmltopdf_test2,		arginfo_htmltopdf_test2)
	PHP_FE_END
};
/* }}} */

/* {{{ htmltopdf_module_entry
 */
zend_module_entry htmltopdf_module_entry = {
	STANDARD_MODULE_HEADER,
	"htmltopdf",					/* Extension name */
	htmltopdf_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(htmltopdf),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(htmltopdf),			/* PHP_MINFO - Module info */
	PHP_HTMLTOPDF_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HTMLTOPDF
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(htmltopdf)
#endif

