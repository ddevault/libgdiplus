/*
 * Copyright © 2004,2006 Red Hat, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of
 * Red Hat, Inc. not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. Red Hat, Inc. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * RED HAT, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL RED HAT, INC. BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Author: Carl D. Worth <cworth@cworth.org>
 */

#ifndef _CAIRO_BOILERPLATE_H_
#define _CAIRO_BOILERPLATE_H_

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo.h>
#include <string.h>

#if   HAVE_STDINT_H
# include <stdint.h>
#elif HAVE_INTTYPES_H
# include <inttypes.h>
#elif HAVE_SYS_INT_TYPES_H
# include <sys/int_types.h>
#elif defined(_MSC_VER)
  typedef __int8 int8_t;
  typedef unsigned __int8 uint8_t;
  typedef __int16 int16_t;
  typedef unsigned __int16 uint16_t;
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
  typedef __int64 int64_t;
  typedef unsigned __int64 uint64_t;
# ifndef HAVE_UINT64_T
#  define HAVE_UINT64_T 1
# endif
# ifndef INT16_MIN
#  define INT16_MIN	(-32767-1)
# endif
# ifndef INT16_MAX
#  define INT16_MAX	(32767)
# endif
# ifndef UINT16_MAX
#  define UINT16_MAX	(65535)
# endif
#else
#error Cannot find definitions for fixed-width integral types (uint8_t, uint32_t, etc.)
#endif

#include "xmalloc.h"

#ifndef CAIRO_BOILERPLATE_LOG
#define CAIRO_BOILERPLATE_LOG(...) fprintf(stderr, __VA_ARGS__)
#endif

/* A fake format we use for the flattened ARGB output of the PS and
 * PDF surfaces. */
#define CAIRO_TEST_CONTENT_COLOR_ALPHA_FLATTENED ((unsigned int) -1)

const char *
_cairo_test_content_name (cairo_content_t content);

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef enum {
    CAIRO_BOILERPLATE_MODE_TEST,
    CAIRO_BOILERPLATE_MODE_PERF
} cairo_boilerplate_mode_t;

typedef cairo_surface_t *
(*cairo_boilerplate_create_surface_t) (const char		 *name,
				       cairo_content_t		  content,
				       int			  width,
				       int			  height,
				       cairo_boilerplate_mode_t	  mode,
				       void			**closure);

typedef cairo_status_t
(*cairo_boilerplate_write_to_png_t) (cairo_surface_t *surface, const char *filename);

typedef void
(*cairo_boilerplate_cleanup_t) (void *closure);

typedef void
(*cairo_boilerplate_wait_t) (void *closure);

typedef struct _cairo_boilerplate_target
{
    const char		       	       *name;
    cairo_surface_type_t		expected_type;
    cairo_content_t			content;
    unsigned int			error_tolerance;
    cairo_boilerplate_create_surface_t	create_surface;
    cairo_boilerplate_write_to_png_t	write_to_png;
    cairo_boilerplate_cleanup_t		cleanup;
    cairo_boilerplate_wait_t		synchronize;
    void			       *closure;
} cairo_boilerplate_target_t;

extern cairo_boilerplate_target_t targets[];

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define CAIRO_PRINTF_FORMAT(fmt_index, va_index) \
	__attribute__((__format__(__printf__, fmt_index, va_index)))
#else
#define CAIRO_PRINTF_FORMAT(fmt_index, va_index)
#endif

void
xasprintf (char **strp, const char *fmt, ...) CAIRO_PRINTF_FORMAT(2, 3);

#endif
