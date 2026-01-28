// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef utils_save_errors_H
#define utils_save_errors_H
//----------------------------------------------------------------
#include <wx/string.h>
//----------------------------------------------------------------
bool save_training_errors_to_csv_file(const wxString& wx_file_name);
bool save_validation_errors_to_csv_file(const wxString& wx_file_name);
bool save_test_errors_to_csv_file(const wxString& wx_file_name);
bool save_predictions_to_csv_file(const wxString& wx_file_name, int run);
//----------------------------------------------------------------
#endif
