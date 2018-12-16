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

/* {{{ string html2pdf(string $url, string $output)
 */
PHP_FUNCTION(html2pdf)
{
	wkhtmltopdf_global_settings * gs;
	wkhtmltopdf_object_settings * os;
	wkhtmltopdf_converter * c;

	int code;
	char *url;
	size_t url_len;
	char *output;
	size_t output_len;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STRING(url, url_len)
		Z_PARAM_STRING(output, output_len)
	ZEND_PARSE_PARAMETERS_END();

	wkhtmltopdf_init(false);
	gs = wkhtmltopdf_create_global_settings();
	wkhtmltopdf_set_global_setting(gs, "out", output);

	os = wkhtmltopdf_create_object_settings();
	wkhtmltopdf_set_object_setting(os, "page", url);
	c = wkhtmltopdf_create_converter(gs);
	wkhtmltopdf_set_error_callback(c, error);
	wkhtmltopdf_set_warning_callback(c, warning);
	wkhtmltopdf_add_object(c, os, NULL);

	if (!wkhtmltopdf_convert(c)) {
		fprintf(stderr, "Conversion failed!");
	}
	code = wkhtmltopdf_http_error_code(c);

	wkhtmltopdf_destroy_converter(c);
	wkhtmltopdf_deinit();

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
ZEND_BEGIN_ARG_INFO(arginfo_html2pdf, 0)
	ZEND_ARG_INFO(0, str)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ htmltopdf_functions[]
 */
static const zend_function_entry htmltopdf_functions[] = {
	PHP_FE(html2pdf, arginfo_html2pdf)
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

