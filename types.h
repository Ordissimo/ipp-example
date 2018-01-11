/**
 * Common definitions.
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <cups/cups.h>

/*
 * Types...
 */
typedef struct _cups_vars_s		/**** Set of variables ****/
{
  char	*uri,			/* URI for printer */
		*filename,		/* Filename */
		scheme[64],		/* Scheme from URI */
		userpass[256],		/* Username/password from URI */
		hostname[256],		/* Hostname from URI */
		resource[1024];		/* Resource path from URI */
  int 		port;			/* Port number from URI */
  http_encryption_t encryption;		/* Encryption for connection? */
  double	timeout;		/* Timeout for connection */
  int		family;			/* Address family */
} _cups_vars_t;

#endif
