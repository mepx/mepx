// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef version_utils_H
#define version_utils_H
//---------------------------------------------------------------------------
bool parse_version(const char* str, int& major, int& minor, int& release, int& build);

bool newer_version(int M1, int m1, int r1, int b1, int M2, int m2, int r2, int b2);
//----------------------------------------------------------------
#endif
