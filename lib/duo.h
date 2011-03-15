/*
 * duo.h
 *
 * Copyright (c) 2010 Duo Security
 * All rights reserved, all wrongs reversed.
 */

#ifndef DUO_H
#define DUO_H

#define DUO_API_HOST		"api.duosecurity.com"

typedef enum {
	DUO_OK = 0,			/* great success! */
	DUO_FAIL,			/* nice try */
	DUO_ABORT,			/* give up */
	DUO_LIB_ERROR,			/* unexpected library error */
	DUO_CONN_ERROR,			/* problem connecting */
	DUO_CLIENT_ERROR,		/* you screwed up */
	DUO_SERVER_ERROR,		/* we screwed up */
} duo_code_t;

#define DUO_FLAG_SYNC	(1 << 0)	/* no incremental status reporting */
#define DUO_FLAG_AUTO	(1 << 1)	/* use default factor without prompt */

typedef struct duo_ctx duo_t;

/* Parse INI config file */
int	    duo_parse_config(const char *filename, 
	    	int (*callback)(void *arg, const char *section,
		    const char *name, const char *val),
	    	void *arg);

/* Open Duo API handle */
duo_t	   *duo_open(const char *ikey, const char *skey, const char *progname);

/* Override conversation prompt/status functions */
void	    duo_set_conv_funcs(duo_t *d,
	    	char *(*conv_prompt)(void *conv_arg, const char *prompt,
		    char *buf, size_t bufsz),
	    	void (*conv_status)(void *conv_arg, const char *msg),
	    	void *conv_arg);

/* Override default host */
void	    duo_set_host(duo_t *d, const char *hostname);

/* Override SSL verification */
void	    duo_set_ssl_verify(duo_t *d, int bool);

/* Perform Duo authentication */
duo_code_t  duo_login(duo_t *d, const char *username,
		const char *client_ip, int flags);

/* Return error message from last API call */
const char *duo_geterr(duo_t *d);

/* Close API handle. */
void	    duo_close(duo_t *d);


#endif /* DUO_H */
