// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
// ---------------------------------------------------------------------------
#ifndef scale_limits_window_H
#define scale_limits_window_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
// ---------------------------------------------------------------------------
class t_scale_limits_window : public wxDialog
{
public:

	wxStaticText *st_min, *st_max;
	wxTextCtrl *tc_min, *tc_max;
    
    wxRadioBox *rb_scale_where;
	wxComboBox *cb_column;

	t_scale_limits_window(wxWindow*parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnOKPressed(wxCommandEvent& event);
    void on_scale_where_changed(wxCommandEvent& event);
};
// ---------------------------------------------------------------------------
extern t_scale_limits_window* f_scale_limits_window;
// ---------------------------------------------------------------------------
#endif
