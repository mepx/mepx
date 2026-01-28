// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef decimal_separator_selector_window_H
#define decimal_separator_selector_window_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
// ---------------------------------------------------------------------------
class t_decimal_separator_selector_window : public wxDialog
{
public:
	wxRadioBox* rb_decimal_separator;

	t_decimal_separator_selector_window(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	
	void OnOKPressed(wxCommandEvent& event);

	void get_separator(char& decimal_separator);

private:
};
// ---------------------------------------------------------------------------
extern t_decimal_separator_selector_window* f_decimal_separator_selector_window;
// ---------------------------------------------------------------------------
#endif

