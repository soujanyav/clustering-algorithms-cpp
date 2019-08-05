#ifndef _ERROR_H
#define _ERROR_H

#include "header.h"

typedef int ERROR_CODE;

#define ERROR_SUCCESS 0		// SUCCESSFUL in completion of the task
#define ERROR_UNKNOWN 1 	// ERROR TYPE NOT KNOWN
#define ERROR_FILE_NOT_FOUND 2	// ERROR IN FILE MANIPULATION. FILE IS NOT FOUND
#define ERROR_MEMORY 3		// ERROR IN malloc() function. Unable to allocate memory

void Error(ERROR_CODE ec,char *mesg);

#endif
