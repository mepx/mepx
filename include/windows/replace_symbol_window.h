// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef replace_symbol_window_H
#define replace_symbol_window_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// ---------------------------------------------------------------------------
class t_replace_symbol_window : public wxDialog{
public:

	wxStaticText *st_find_what, *st_replace_with;
	wxTextCtrl *tc_find_what, *tc_replace_with;
	wxRadioBox *rb_replace_where;
	wxComboBox *cb_column;
	wxCheckBox *cb_use_regular;

	t_replace_symbol_window(wxWindow*parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	void OnOKPressed(wxCommandEvent& event);
	void on_replace_where_changed(wxCommandEvent& event);
};
// ---------------------------------------------------------------------------

extern t_replace_symbol_window* f_replace_symbol_window;

#endif
