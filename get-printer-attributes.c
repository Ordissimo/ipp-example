/**
 * Get the attributes from an IPP printer.
 * 
 * Usage:
 *  ./get-printer-attributes PRINTER_URI
 * 
 * Where "PRINTER_URI" is the URI of the IPP printer.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cups/cups.h>

/*
 * Types...
 */
typedef struct _cups_vars_s		/**** Set of variables ****/
{
   char		*uri,			/* URI for printer */
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

/**
 * 'usage()' - Show program usage and exit.
 */
void usage() {
  printf("Usage:\n\t./get-printer-attributes PRINTER_URI\n\n");
  printf("PRINTER_URI: The URI of the IPP printer.\n");
  exit(1);
}

/**
 * 'debug()' - Print the contents of _cups_vars_t type variable to stderr.
 */
void debug(_cups_vars_t vars) /* I - Variables */
{
  fprintf(stderr, "URI: %s\nFilename: %s\nScheme: %s\n"
                  "Userpass: %s\nHost: %s\nPort: %d\nResource: %s\n"
                  "Encryption: %d\nTimeout: %.3lf\nFamily: %d\n",
                  vars.uri, vars.filename, vars.scheme, vars.userpass,
                  vars.hostname, vars.port,vars.resource, vars.encryption,
                  vars.timeout, vars.family);
}

/*
 * 'do_tests()' - Do get-printer-attributes test.
 */

static int				/* 0 = success, 1 = failure */
do_tests(_cups_vars_t *vars)		/* I - Variables */
{
  http_t	*http = NULL;             /* HTTP connection to server */
  ipp_t *request, *response = NULL; /* IPP request and response */
  ipp_attribute_t *attr;            /* IPP attributes */
  char buffer[1024];                /* Buffer for IPP attributes */

  /* Try to connect to IPP server */
  if ((http = httpConnect2(vars->hostname, vars->port, NULL, vars->family,
                           vars->encryption, 1, 30000, NULL)) == NULL) {
    printf("Unable to connect to %s on port %d.\n", vars->hostname, vars->port);
    return 1;
  }

  /* Fire a Get-Printer-Attributes request */
  request = ippNewRequest(IPP_OP_GET_PRINTER_ATTRIBUTES);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri",
	             NULL, vars->uri);
  response = cupsDoRequest(http, request, vars->resource);

  /* Print the attributes received from the IPP printer */
  attr = ippFirstAttribute(response);
  while (attr) {
    /* Ponvert IPP attribute's value to string */
    ippAttributeString(attr, buffer, sizeof(buffer));
    
    /*
     * Print the attribute and value in the format
     * attr = value
     */
    printf("%s = %s\n", ippGetName(attr), buffer);

    /* next attribute */
    attr = ippNextAttribute(response);
  }

  fprintf(stderr, "\nOperation Get-Printer-Attributes successful. Exiting!\n");
  return 0;
}

int main(int argc, char *argv[]) {
  _cups_vars_t vars;          /* variables */
  char uri[1024];             /* copy of printer URI */
  http_uri_status_t	uri_status;	/* URI separation status */

  /* Initializing vars */
  memset(&vars, 0, sizeof(vars));
  vars.family = AF_UNSPEC;
  
  if (argc != 2) {
    usage();
  }

  vars.uri = argv[1];
  uri_status = httpSeparateURI(HTTP_URI_CODING_ALL, vars.uri,
                                   vars.scheme, sizeof(vars.scheme),
                                   vars.userpass, sizeof(vars.userpass),
				   vars.hostname, sizeof(vars.hostname),
				   &(vars.port),
				   vars.resource, sizeof(vars.resource));

  if (uri_status != HTTP_URI_OK)
  {
    fprintf(stderr, "Bad URI - %s.\n", httpURIStatusString(uri_status));
    return (1);
  }

  httpAssembleURI(HTTP_URI_CODING_ALL, uri, sizeof(uri), vars.scheme, NULL,
                      vars.hostname, vars.port, vars.resource);
  vars.uri = uri;
  // debug(vars);
  return do_tests(&vars);
}