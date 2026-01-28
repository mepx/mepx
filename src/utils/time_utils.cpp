// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <string.h>
#include <time.h>
//---------------------------------------------------------------------------
#include "utils/time_utils.h"
//---------------------------------------------------------------------------
char* current_time_to_string(void)
{
	char *result = new char[100];
	strcpy(result, "");

	time_t _current_time = time(NULL);

	struct tm * ptm;

	ptm = localtime(&_current_time);

	strftime(result, 100, "%Y_%m_%d_%H_%M_%S", ptm);

	return result;
}
//---------------------------------------------------------------------------
