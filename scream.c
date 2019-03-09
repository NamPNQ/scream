/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2009 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Gopal Vijayaraghavan <gopalv@php.net>                        |
  |         Johannes Schlueter <johannes@php.net>                        |
  +----------------------------------------------------------------------+
*/

/* $Id: scream.c,v 1.1 2009/02/25 21:11:06 johannes Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_scream.h"

/* {{{ ZEND_DECLARE_MODULE_GLOBALS(scream) */
ZEND_DECLARE_MODULE_GLOBALS(scream)
/* }}} */

/* {{{ php_scream_init_globals */
static void php_scream_init_globals(zend_scream_globals* scream_globals TSRMLS_DC)
{
	scream_globals->enabled = 1;
}
/* }}} */

/* {{{ ini entries */
PHP_INI_BEGIN()
	STD_PHP_INI_BOOLEAN("scream.enabled", "0", PHP_INI_ALL, OnUpdateBool, enabled, zend_scream_globals, scream_globals)
PHP_INI_END()
/* }}} */

#ifdef COMPILE_DL_SCREAM
ZEND_GET_MODULE(scream)
#endif

/* {{{ zend hooks */
static int scream_op_ZEND_SILENCE(zend_execute_data *execute_data)
{
	if(SCREAM_G(enabled))
	{
		execute_data->opline++;
		return ZEND_USER_OPCODE_CONTINUE;
	}
	return ZEND_USER_OPCODE_DISPATCH;
}

void scream_zend_init(TSRMLS_D) 
{
	if((zend_set_user_opcode_handler(ZEND_BEGIN_SILENCE, 
				scream_op_ZEND_SILENCE) == FAILURE) ||
	   (zend_set_user_opcode_handler(ZEND_END_SILENCE, 
				scream_op_ZEND_SILENCE) == FAILURE))
	{
		zend_error(E_NOTICE, "cannot install silence opcode override");
		SCREAM_G(enabled) = 0;
	}
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(scream)
{
	ZEND_INIT_MODULE_GLOBALS(scream, php_scream_init_globals, NULL);

	REGISTER_INI_ENTRIES();
	
	scream_zend_init(TSRMLS_C);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 *  */
PHP_MSHUTDOWN_FUNCTION(scream)
{
#ifdef ZTS
	ts_free_id(scream_globals_id);
#endif
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(scream)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "scream support", "enabled");
	php_info_print_table_row(2, "extension version", PHP_SCREAM_VERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ scream_module_entry
 */
zend_module_entry scream_module_entry = {
	STANDARD_MODULE_HEADER,
	"scream",
	NULL,
	PHP_MINIT(scream),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(scream),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_SCREAM_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
