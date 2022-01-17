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

static zend_class_entry *php_sdl_ttf_font_ce;
static zend_object_handlers php_sdl_ttf_font_handlers;

zend_bool sdl_ttf_font_to_zval(TTF_Font *font, zval *value)
{
	if(NULL == font) {
		ZVAL_NULL(value);
		return 0;
	}
	if(value != NULL) {
		zval_ptr_dtor(value);
	}

	object_init_ex(value, php_sdl_ttf_font_ce);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("height"), font->height);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("ascent"), font->ascent);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("descent"), font->descent);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("lineskip"), font->lineskip);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("style"), font->style);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("outline_val"), font->outline_val);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("allow_kerning"), font->allow_kerning);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("use_kerning"), font->use_kerning);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("glyph_overhang"), font->glyph_overhang);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("line_thickness"), font->line_thickness);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("underline_top_row"), font->underline_top_row);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("strikethrough_top_row"), font->strikethrough_top_row);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("ft_load_target"), font->ft_load_target);
	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("render_subpixel"), font->render_subpixel);

	zend_update_property_long(php_sdl_ttf_font_ce, Z_OBJ_P(value), ZEND_STRL("render_sdf"), font->render_sdf);

	return 1;
}

#define read_ttf_font_prop(z_value, name, value) \
{ \
	zval *val, rv; \
	val = zend_read_property(php_sdl_ttf_font_ce, Z_OBJ_P(z_value), ZEND_STRL(name), 0, &rv); \
	convert_to_long(val); \
	Z_LVAL_P(val) = (value) = (int)Z_LVAL_P(val); \
}

zend_bool zval_to_sdl_ttf_font(zval *value, TTF_Font *font)
{
	zval *val, rv;
	
	if (Z_TYPE_P(value) == IS_OBJECT && Z_OBJCE_P(value) == php_sdl_ttf_font_ce) {
		read_ttf_font_prop(value, "height",                 font->height);
		read_ttf_font_prop(value, "ascent",                 font->ascent);
		read_ttf_font_prop(value, "descent",                font->descent);
		read_ttf_font_prop(value, "lineskip",               font->lineskip);

		read_ttf_font_prop(value, "style",                  font->style);
		read_ttf_font_prop(value, "outline_val",            font->outline_val);

		read_ttf_font_prop(value, "allow_kerning",          font->allow_kerning);
		read_ttf_font_prop(value, "use_kerning",            font->use_kerning);

		read_ttf_font_prop(value, "glyph_overhang",         font->glyph_overhang);
		read_ttf_font_prop(value, "line_thickness",         font->line_thickness);
		read_ttf_font_prop(value, "underline_top_row",      font->underline_top_row);
		read_ttf_font_prop(value, "strikethrough_top_row",  font->strikethrough_top_row);

		read_ttf_font_prop(value, "ft_load_target",         font->ft_load_target);
		read_ttf_font_prop(value, "render_subpixel",        font->render_subpixel);
		read_ttf_font_prop(value, "render_sdf",             font->render_sdf);

		return 1;
	}
	/* creupdate an empty struct */
	memset(font, 0, sizeof(TTF_Font));
	return 0;
}

static PHP_METHOD(SDL_Event, __construct)
{
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, NULL, &error_handling);
	if (FAILURE == zend_parse_parameters_none()) {
		zend_restore_error_handling(&error_handling);
		return;
	}
	zend_restore_error_handling(&error_handling);
}

/* {{{ proto TTF_Font::__toString() */
static PHP_METHOD(TTF_Font, __toString)
{
	char *buf;
        size_t buf_len;
	TTF_Font font;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zval_to_sdl_ttf_font(getThis(), &font);
	buf_len = spprintf(&buf, 100, "TTF_Font()");
	RETVAL_STRINGL(buf, buf_len);
        efree(buf);
}

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
*/
PHP_FUNCTION(TTF_Quit)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_FALSE;
	}

	TTF_Quit();
}
/* }}} */

static const zend_function_entry php_sdl_ttf_font_methods[] = {
	PHP_ME(TTF_Font, __construct, arginfo_none, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(TTF_Font, __toString, arginfo_none, ZEND_ACC_PUBLIC)

	/* non-static methods */
//	PHP_FALIAS(Empty,            SDL_RectEmpty,            arginfo_none)
	PHP_FE_END
};

/* {{{ MINIT */
PHP_MINIT_FUNCTION(sdl_ttf)
{
	//zend_class_entry ce_font;

  REGISTER_LONG_CONSTANT(“TTF_STYLE_NORMAL”,            0x00, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_STYLE_BOLD”,              0x01, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_STYLE_ITALIC”,            0x02, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_STYLE_UNDERLINE”,         0x04, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_STYLE_STRIKETHROUGH”,     0x08, CONST_CS | CONST_PERSISTENT);


  REGISTER_LONG_CONSTANT(“TTF_HINTING_NORMAL”,          0, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_HINTING_LIGHT”,           1, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_HINTING_MONO”,            2, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_HINTING_NONE”,            3, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT(“TTF_HINTING_LIGHT_SUBPIXEL”,  4, CONST_CS | CONST_PERSISTENT);

	INIT_CLASS_ENTRY(ce_font, "TTF_Font", php_sdl_ttf_font_methods);
	php_sdl_ttf_font_ce = zend_register_internal_class(&ce_font);

	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("height"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("ascent"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("descent"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("lineskip"), ZEND_ACC_PUBLIC);

	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("style"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("outline_val"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("allow_kerning"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("use_kerning"), ZEND_ACC_PUBLIC);

	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("glyph_overhang"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("line_thickness"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("underline_top_row"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("strikethrough_top_row"), ZEND_ACC_PUBLIC);

	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("ft_load_target"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("render_subpixel"), ZEND_ACC_PUBLIC);
	zend_declare_property_null(php_sdl_ttf_font_ce, ZEND_STRL("render_sdf"), ZEND_ACC_PUBLIC);

	return SUCCESS;
}
/* }}} */
#endif