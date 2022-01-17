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


#ifndef PHP_SDL_TTF_H
#define PHP_SDL_TTF_H

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <SDL2/SDL_ttf.h>
#else
#include <SDL_ttf.h>
#endif

#include "php_sdl.h"

zend_class_entry *get_php_sdl_ttf_font_ce(void);
zend_bool sdl_ttf_font_to_zval(TTF_Font *font, zval *value);
zend_bool zval_to_sdl_ttf_font(zval *value, TTF_Font *font);

ZEND_BEGIN_ARG_INFO_EX(arginfo_TTF_Init, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(TTF_Init);
/*
ZEND_BEGIN_ARG_INFO_EX(arginfo_TTF_InitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(TTF_InitSubSystem);

ZEND_BEGIN_ARG_INFO_EX(arginfo_TTF_QuitSubSystem, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(TTF_QuitSubSystem);

ZEND_BEGIN_ARG_INFO_EX(arginfo_TTF_WasInit, 0, 0, 1)
       ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()

PHP_FUNCTION(TTF_WasInit);
*/
ZEND_BEGIN_ARG_INFO_EX(arginfo_TTF_Quit, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_FUNCTION(TTF_Quit);

PHP_MINIT_FUNCTION(sdl_ttf);

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_SDL_TTF_H */

