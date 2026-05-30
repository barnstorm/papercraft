#ifndef _PAPERCRAFT_ERR_H
#define _PAPERCRAFT_ERR_H

/*
 * Minimal BSD <err.h> shim for platforms that lack it (e.g. mingw).
 * Implements err/errx/warn/warnx as static inline functions so no
 * separate translation unit is needed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

extern char *__progname;

static inline const char *
_err_progname(void)
{
	return "papercraft";
}

static inline void
warnx(const char *fmt, ...)
{
	va_list ap;
	fprintf(stderr, "%s: ", _err_progname());
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
}

static inline void
warn(const char *fmt, ...)
{
	int saved = errno;
	va_list ap;
	fprintf(stderr, "%s: ", _err_progname());
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(saved));
}

static inline void
errx(int code, const char *fmt, ...)
{
	va_list ap;
	fprintf(stderr, "%s: ", _err_progname());
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	exit(code);
}

static inline void
err(int code, const char *fmt, ...)
{
	int saved = errno;
	va_list ap;
	fprintf(stderr, "%s: ", _err_progname());
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(saved));
	exit(code);
}

#endif
