#include <string.h>
#include "errlist.h"

#define ERR_COUNT 9

static const char *errlist[ERR_COUNT] = {
	ERR_INSUFFICIENT_MEMORY,
	ERR_COMMAND_LINE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_BAD_STATUS,
	ERR_WRONG_PARAM,
	ERR_INSUFFICIENT_PARAMS,
	ERR_NO_CONFIG,
	ERR_HELP_REQUESTED
};

const char *strerror_client(
	int errcode)
{
	if ((errcode <= -500) && (errcode >= -500 - ERR_COUNT))
	{
		return errlist[-(errcode + 500)];
	}
	return strerror(errcode);
}
