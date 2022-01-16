dnl config.m4 for the PHP SDL extension

PHP_ARG_WITH(sdl, whether to enable SDL functions,
[  --with-sdl[=SDLCONFIG_PATH]         Enable SDL support])

PHP_ARG_ENABLE(sdl-debug, whether to enable PHP-SDL debug support,
[  --enable-sdl-debug     Enable SDL debug support], no, no)

PHP_ARG_WITH(sdl-ttf, whether to enable sdl_ttf functions,
[  --with-sdl-ttf[=SDLTTF_PATH]      Enable SDL2_ttf library], no, no)

if test "$PHP_SDL" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_SDL2 -Wall -Wfatal-errors"

  REQ_PHP_VERSION="8.0.0"
  REQ_PHP_VERSION_ID=80000
  if test -z "$PHP_VERSION_ID"; then
    AC_MSG_CHECKING(PHP version)
    AC_TRY_COMPILE([#include <php_version.h>], [
    #if PHP_VERSION_ID < $REQ_PHP_VERSION_ID
    #error  this extension requires at least PHP version $REQ_PHP_VERSION
    #endif
    ],
    [AC_MSG_RESULT(ok)],
    [AC_MSG_ERROR([need at least PHP v$REQ_PHP_VERSION])])
  else
    if test "$PHP_VERSION_ID" -lt "$REQ_PHP_VERSION_ID"; then
      AC_MSG_ERROR([SDL needs at least PHP v$REQ_PHP_VERSION])
    fi
  fi
  PHP_SDL_CFLAGS="$CPPFLAGS"

  export CPPFLAGS="$OLD_CPPFLAGS"

  dnl {{{ --enable-sdl-debug
  if test "$PHP_SDL_DEBUG" != "no"; then
    CFLAGS="$CFLAGS -Wall -Wpedantic -g -ggdb -O0"
  fi
  dnl }}}

  if test "$PHP_SDL" == "yes"; then
    AC_PATH_PROG(SDL2_CONFIG, sdl2-config, no)
  else
    SDL2_CONFIG="$PHP_SDL"
  fi

  AC_MSG_CHECKING(for SDL2 library)
  if test -x "$SDL2_CONFIG" ; then
    SDL2_VERSION=`$SDL2_CONFIG --version`
    AC_MSG_RESULT(using SDL2 version $SDL2_VERSION)
    PHP_EVAL_INCLINE(`$SDL2_CONFIG --cflags`)
    PHP_EVAL_LIBLINE(`$SDL2_CONFIG --libs`, SDL_SHARED_LIBADD)
  else
    AC_MSG_ERROR(Cannot find sdl2-config)
  fi

  if test "$PHP_SDL_TTF" != "no"; then
    AC_MSG_CHECKING(for pkg-config)

    if test ! -f "$PKG_CONFIG"; then
      PKG_CONFIG=`which pkg-config`
    fi

    if test -f "$PKG_CONFIG"; then
      AC_MSG_RESULT(found)
      AC_MSG_CHECKING(for SDL2_ttf)

      if $PKG_CONFIG --exists SDL2_ttf; then
        SDL_TTF_VERSION=`$PKG_CONFIG --modversion SDL2_ttf`
        AC_MSG_RESULT(using SDL2_ttf version $SDL_TTF_VERSION)
        SDL_TTF_LIBS=`$PKG_CONFIG --libs SDL2_ttf`
        LDFLAGS=$SDL_TTF_LIBS
        PHP_EVAL_LIBLINE($SDL_TTF_LIBS, SDL_TTF_SHARED_LIBADD)
        AC_DEFINE(HAVE_SDL2_TTF, 1, [whether SDL2_ttf exists in the system])
    
      else
        AC_MSG_RESULT(not found)
        AC_MSG_ERROR(Ooops ! Could not find SDL2_ttf, either proceed to install it or configure the extension without it.)
      fi

    else
      AC_MSG_RESULT(not found)
      AC_MSG_ERROR(Ooops ! no pkg-config found .... )
    fi
  fi

  PHP_SUBST(SDL_SHARED_LIBADD)
  AC_DEFINE(HAVE_SDL2, 1, [ ])

  SDL_SOURCE_FILES="`find src -name "*.c"`"
  PHP_NEW_EXTENSION(sdl, $SDL_SOURCE_FILES, $ext_shared,, $PHP_SDL_CFLAGS)
fi
