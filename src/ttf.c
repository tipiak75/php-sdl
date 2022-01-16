/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Santiago Lizardo <santiagolizardo@php.net>                  |
  |          Remi Collet <remi@php.net>                                  |
  +----------------------------------------------------------------------+
*/


/*
  +----------------------------------------------------------------------+
  | wrapper for SDL2/SDL_ttf                                             |
  +----------------------------------------------------------------------+
*/
#include "ttf.h"

#ifdef HAVE_SDL2_TTF

/* {{{ proto int TTF_Init(void)
*/
PHP_FUNCTION(TTF_Init) {
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG(TTF_Init());
}
/* }}} */


/* {{{ proto void SDL_Quit(void)

 *  This function cleans up all initialized subsystems. You should
 *  call it upon all exit conditions.
extern DECLSPEC void SDLCALL SDL_Quit(void);
*/
PHP_FUNCTION(TTF_Quit)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	TTF_Quit();
}
/* }}} */


/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_ttf)
{
	return SUCCESS;
}
/* }}} */
#endif