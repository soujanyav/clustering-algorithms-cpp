#include "error.h"

void Error(ERROR_CODE ec,char *mesg)
{
	switch(ec)
	{
		case ERROR_SUCCESS:
			cout << "ERROR_SUCCESS. " << mesg << "\n";
			break;
		case ERROR_UNKNOWN:
			cout << "ERROR TYPE IS NOT KNOWN. " << mesg << "\n";
			break;
		case ERROR_FILE_NOT_FOUND:
			cout << "FILE IS NOT FOUND. " << mesg << "\n";
			break;
		case ERROR_MEMORY:
			cout << "UNABLE TO ALLOCATE MEMORY. " << mesg << "\n";
			break;
	}
}
