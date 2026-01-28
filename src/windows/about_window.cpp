// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <wx/version.h>
// ---------------------------------------------------------------------------
#include "windows/about_window.h"
#include "mepx_project.h"
#include "chart_bar_16x16.xpm"
#include "app_x_info.h"
// ---------------------------------------------------------------------------
t_about_window* f_about_window = NULL;
// ---------------------------------------------------------------------------
t_about_window::t_about_window(wxWindow *parent, const wxString& title,
							   const wxPoint& pos, const wxSize& size)
	: wxDialog( parent, wxID_ANY, title, pos, size)
{

	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);


	st_software_name = new wxStaticText(this, -1, "Multi Expression Programming X");
	st_software_name->SetFont(st_software_name->GetFont().MakeBold());
	st_mepx_version = new wxStaticText(this, -1, wxString(app_version_nr));
	
	wxStaticText *st_based_on = new wxStaticText(this, -1, "Based on:");
												   
	st_libmep_version = new wxStaticText(this, -1, "libmep version: " + wxString() << mep_engine.get_version());
	wxStaticText *st_wx_version = new wxStaticText(this, -1, "wxWidgets version: " + (wxString() << wxMAJOR_VERSION) + "." + (wxString() << wxMINOR_VERSION) + "." + (wxString() << wxRELEASE_NUMBER));

	lWebPage = new wxButton(this, -1, "Website: mepx.org", wxDefaultPosition, wxDefaultSize);
	lWebPageCS = new wxButton(this, -1, "Mirror: mepx.github.io", wxDefaultPosition, wxDefaultSize);
	lWebPageGithub = new wxButton(this, -1, "Source code: www.github.com/mepx", wxDefaultPosition, wxDefaultSize);

	lWebPage->Bind(wxEVT_BUTTON , &t_about_window::OnWebSiteClicked, this);
	lWebPageCS->Bind(wxEVT_BUTTON, &t_about_window::OnCSWebSiteClicked, this);
	lWebPageGithub->Bind(wxEVT_BUTTON, &t_about_window::OnGithubWebSiteClicked, this);

	lAuthor = new wxStaticText(this, -1, "Author: Mihai Oltean");
	lEmailAddress = new wxStaticText(this, -1, "Email: mihai.oltean@gmail.com");

	wxBoxSizer *bottom_sizer = (wxBoxSizer *)CreateSeparatedButtonSizer(wxOK);
	wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
	main_sizer->Add(st_software_name, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(st_mepx_version, 0, wxEXPAND | wxLEFT|wxRIGHT, 10);
	main_sizer->Add(st_based_on, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(st_libmep_version, 0, wxEXPAND | wxLEFT|wxRIGHT, 10);
	main_sizer->Add(st_wx_version, 0, wxEXPAND | wxLEFT|wxRIGHT, 10);
	main_sizer->Add(lWebPage, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(lWebPageCS, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(lWebPageGithub, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(lAuthor, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(lEmailAddress, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 10);
	main_sizer->Add(bottom_sizer, 0, wxEXPAND | wxALL, 10);

	SetSizerAndFit(main_sizer);
}
// ---------------------------------------------------------------------------
void t_about_window::OnCSWebSiteClicked(wxCommandEvent &)
{
	wxLaunchDefaultBrowser("https://mepx.github.io");
}
// ---------------------------------------------------------------------------
void t_about_window::OnGithubWebSiteClicked(wxCommandEvent &)
{
	wxLaunchDefaultBrowser("https://www.github.com/mepx");
}
// ---------------------------------------------------------------------------
void t_about_window::OnWebSiteClicked(wxCommandEvent &)
{
	wxLaunchDefaultBrowser("https://www.mepx.org");
}
// ---------------------------------------------------------------------------
