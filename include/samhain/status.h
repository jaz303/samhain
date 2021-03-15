#ifndef SAMHAIN_STATUS_H_
#define SAMHAIN_STATUS_H_

/** Success */
#define SAMH_OK				0

/** Generic error */
#define SAMH_ERR			-1

/** Busy */
#define SAMH_ERR_BUSY		-2

/** Invalid configuration params */
#define SAMH_ERR_CONFIG		-3

/** Invalid length */
#define SAMH_ERR_LENGTH		-4

#define SAMH_ERR_INVALID_ARG	-5

typedef int samh_status_t;

#endif