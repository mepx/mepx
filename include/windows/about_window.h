// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
// ---------------------------------------------------------------------------
#ifndef MEPX_about_window_H
#define MEPX_about_window_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
// ---------------------------------------------------------------------------
class t_about_window : public wxDialog
{
public:

	wxStaticText *st_software_name;
	wxStaticText *st_mepx_version;
	wxStaticText *st_libmep_version;
	
	wxButton *lWebPageCS, *lWebPageGithub, *lWebPage;
	wxStaticText *lEmailAddress, *lAuthor;

	wxString Language;

	t_about_window(wxWindow*parent, const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnCSWebSiteClicked(wxCommandEvent &event);
	void OnWebSiteClicked(wxCommandEvent &event);
	void OnGithubWebSiteClicked(wxCommandEvent &event);
};
// ---------------------------------------------------------------------------
extern t_about_window* f_about_window;
// ---------------------------------------------------------------------------

#endif
