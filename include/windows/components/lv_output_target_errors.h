// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef lv_errors_data_H
#define lv_errors_data_H
//---------------------------------------------------------
#include <wx/wx.h>
#include <wx/listctrl.h>
//---------------------------------------------------------
#include "model_target_errors_data_providers.h"
//--------------------------------------------------------
class t_lv_output_target_error : public wxListCtrl {
public:
	t_lv_output_target_error(wxWindow* parent, t_model_target_error_data_provider*);
    wxString OnGetItemText(long item, long column) const;

    void my_update(void);
private:
	t_model_target_error_data_provider* data_provider;
};
//---------------------------------------------------------
#endif
