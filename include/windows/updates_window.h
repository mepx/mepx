// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef MEPX_updates_window_H
#define MEPX_updates_window_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
//------------------------------------------------------------------------
class t_updates_window : public wxDialog{
private:
	wxButton* b_download;
	void OnShow(wxShowEvent& event);
	void set_language(void);
	void on_download_new_version(wxCommandEvent&);
	wxString s_url;

public:
	wxStaticText* st_current_version, * st_new_version;

	t_updates_window(wxWindow* parent);
};
//------------------------------------------------------------------------
extern t_updates_window* f_updates_window;
#endif
//------------------------------------------------------------------------
