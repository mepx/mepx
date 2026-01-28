// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/updates_window.h"
#include "app_x_info.h"
// ---------------------------------------------------------------------------
#include "chart_bar_16x16.xpm"
// ---------------------------------------------------------------------------
t_updates_window* f_updates_window = NULL;
//------------------------------------------------------------------------
t_updates_window::t_updates_window(wxWindow* parent)
	: wxDialog(parent, 
		wxID_ANY, "Updates")
{
	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	st_current_version = new wxStaticText(this, -1, "Current version                               ");
	st_new_version = new wxStaticText(this, -1,     "New version                                   ");
	st_new_version->SetForegroundColour(wxColor(*wxRED));

    b_download = new wxButton(this, -1, "Download");//, wxDefaultPosition, wxSize(-1, 70));
	//wxBitmap bmp_updates(download2_32_xpm);
	//b_download->SetBitmap(bmp_updates);
	//b_download->SetBitmapPosition(wxLEFT);

	b_download->Bind(wxEVT_BUTTON, &t_updates_window::on_download_new_version, this);

	wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
	main_sizer->Add(st_current_version, 0, wxEXPAND | wxALL, 10);
	main_sizer->Add(st_new_version, 0, wxEXPAND | wxALL, 10);
	main_sizer->Add(b_download, 0, wxEXPAND | wxALL, 10);
  //  main_sizer->Fit(this);

	Bind(wxEVT_SHOW, &t_updates_window::OnShow, this);

	SetSizerAndFit(main_sizer);
}
//------------------------------------------------------------------------
void t_updates_window::on_download_new_version(wxCommandEvent&)
{
	wxLaunchDefaultBrowser(update_version_link);
}
// ---------------------------------------------------------------------------
void t_updates_window::set_language(void)
{
	b_download->SetLabel("Download");
}
// ---------------------------------------------------------------------------
void t_updates_window::OnShow(wxShowEvent& event)
{
	if (event.IsShown()){
		set_language();
		CenterOnParent();
	}
}
// ---------------------------------------------------------------------------
