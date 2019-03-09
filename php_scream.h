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

/* $Id: php_scream.h,v 1.2 2009/02/25 21:12:54 johannes Exp $ */

#ifndef PHP_SCREAM_H
#define PHP_SCREAM_H

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_globals.h"
#include "ext/standard/php_var.h"
//#include "ext/standard/php_smart_str.h"

extern zend_module_entry scream_module_entry;
#define phpext_scream_ptr &scream_module_entry

#define PHP_SCREAM_VERSION "0.1.0"

#ifdef PHP_WIN32
#define PHP_SCREAM_API __declspec(dllexport)
#else
#define PHP_SCREAM_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* {{{ zend_scream_globals */
ZEND_BEGIN_MODULE_GLOBALS(scream)
	/* configuration parameters */
	zend_bool enabled;		/* defaults to false */
ZEND_END_MODULE_GLOBALS(scream)
/* }}} */

/* {{{ extern scream_globals */
ZEND_EXTERN_MODULE_GLOBALS(scream)
/* }}} */

#ifdef ZTS
#define SCREAM_G(v) TSRMG(scream_globals_id, zend_scream_globals *, v)
#else
#define SCREAM_G(v) (scream_globals.v)
#endif

#endif	/* PHP_SCREAM_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
