// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
//---------------------------------------------------------------------------
#include "utils/version_utils.h"
//---------------------------------------------------------------------------
bool parse_version(const char* str, int& major, int& minor, int& release, int& build)
{
//	int num_read = sscanf(str, "%d%c%d%c%d%c%d", &major, &minor, &release, &build);
	int num_read = 0;
	int nr[4];

	size_t last_start = 0;
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++){
		if (str[i] == '.')
			if (i > last_start){
				if (sscanf(str + last_start, "%d", &nr[num_read]) == 0)
					return false;
				last_start = i + 1;
				num_read++;
				if (num_read == 4)
					break;
			}
	}
	if (num_read < 4){
		if (sscanf(str + last_start, "%d", &nr[num_read]) == 0)
			return false;
		num_read++;
	}
	if (num_read != 4)
		return false;

	major = nr[0];
	minor = nr[1];
	release = nr[2];
	build = nr[3];

	return true;
}
//---------------------------------------------------------------------------
bool newer_version(int M1, int m1, int r1, int b1, int M2, int m2, int r2, int b2)
{
	if (M1 > M2)
		return true;
    else{
        if (M1 < M2)
            return false;
    }

	if (m1 > m2)
		return true;
    else{
        if (m1 < m2)
            return false;
    }

	if (r1 > r2)
		return true;
    else{
        if (r1 < r2)
            return false;
    }

	if (b1 > b2)
		return true;
    else{
        if (b1 < b2)
            return false;
    }

	return false;
}
//---------------------------------------------------------------------------
