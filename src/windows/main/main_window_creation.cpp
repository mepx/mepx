// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//-------------------------------------------------------------------------
#include "save_32x32.xpm"
#include "open_32x32.xpm"
#include "new_32x32.xpm"
#include "about.xpm"
#include "play_32.xpm"
#include "stop_32x32.xpm"
#include "settings_32x32.xpm"
#include "download_32x32.xpm"

#include "results_32.xpm"
#include "settings_32.xpm"
#include "binary_32.xpm"
#include "chart_bar_16x16.xpm"
//-------------------------------------------------------------------------
void t_main_window::create_interface(void)
{
	last_processed_generation = -1;
	last_processed_run = -1;

	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	wxBoxSizer* sizer_main = new wxBoxSizer(wxVERTICAL);

	b_new_project = new wxButton(this, -1, "New project");
	b_new_project->Bind(wxEVT_BUTTON, &t_main_window::on_new_project_button_clicked, this);
	wxBitmap bmp_new_32x32(new_32x32_xpm);
	b_new_project->SetBitmap(bmp_new_32x32);

	b_load_project = new wxButton(this, -1, "Load project");
	b_load_project->Bind(wxEVT_BUTTON, &t_main_window::on_load_project_button_clicked, this);
	wxBitmap bmp_load_32x32(open_32x32_xpm);
	b_load_project->SetBitmap(bmp_load_32x32);

	b_save_project = new wxButton(this, -1, "Save project");
	b_save_project->Bind(wxEVT_BUTTON, &t_main_window::on_save_project_button_clicked, this);
	wxBitmap bmp_save_32x32(save_32x32_xpm);
	b_save_project->SetBitmap(bmp_save_32x32);

	b_save_as_project = new wxButton(this, -1, "Save project as");
	b_save_as_project->Bind(wxEVT_BUTTON, &t_main_window::on_save_as_project_button_clicked, this);
	wxBitmap bmp_save_as_32x32(save_32x32_xpm);
	b_save_as_project->SetBitmap(bmp_save_32x32);

	b_settings = new wxButton(this, -1, "Settings");
	b_settings->Bind(wxEVT_BUTTON, &t_main_window::on_settings_button_clicked, this);
	wxBitmap bmp_settings(settings_32x32_xpm);
	b_settings->SetBitmap(bmp_settings);
	b_settings->Hide();

	b_start = new wxButton(this, -1, "Start");
	b_start->Bind(wxEVT_BUTTON, &t_main_window::on_start_button_clicked, this);
	wxBitmap bmp_start(play_32_xpm);
	b_start->SetBitmap(bmp_start);

	b_stop = new wxButton(this, -1, "Stop");
	b_stop->Bind(wxEVT_BUTTON, &t_main_window::on_stop_button_clicked, this);
	wxBitmap bmp_stop(stop_32x32_xpm);
	b_stop->SetBitmap(bmp_stop);
	b_stop->Enable(false);

	b_about = new wxButton(this, -1, "About");
	b_about->Bind(wxEVT_BUTTON, &t_main_window::on_about_button_clicked, this);
	wxBitmap bmp_about(about_xpm);
	b_about->SetBitmap(bmp_about);

	tb_update = new wxButton(this, wxID_ANY, "Updates");
	tb_update->Bind(wxEVT_BUTTON, &t_main_window::on_update_button_clicked, this);
	wxBitmap bmp_updates(download_32_xpm);
	tb_update->SetBitmap(bmp_updates);

	bs_main_toolbar = new wxBoxSizer(wxHORIZONTAL);
	bs_main_toolbar->Add(b_start, 0, 0, 0);
	bs_main_toolbar->Add(b_stop, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_new_project, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_load_project, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_save_project, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_save_as_project, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_settings, 0, wxLEFT, 2);
	bs_main_toolbar->Add(b_about, 0, wxLEFT, 2);
	bs_main_toolbar->Add(tb_update, 0, wxLEFT, 2);

	il_notebook = new wxImageList(32, 32, false, 3);

	wxBitmap* bmp_data_32 = new wxBitmap(binary_32_xpm);
	il_notebook->Add(*bmp_data_32);
	delete bmp_data_32;

	wxBitmap* bmp_settings_32 = new wxBitmap(settings_32_xpm);
	il_notebook->Add(*bmp_settings_32);
	delete bmp_settings_32;

	wxBitmap* bmp_results_32 = new wxBitmap(results_32_xpm);
	il_notebook->Add(*bmp_results_32);
	delete bmp_results_32;

	n_settings = new wxNotebook(this, -1);
	n_settings->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &t_main_window::on_change_main_notebook_page, this);
	n_settings->SetImageList(il_notebook);

	create_data_ui();

	create_params_ui();

	create_results_ui();

	n_settings->AddPage(w_data, "Data", true, 0);
	n_settings->AddPage(w_parameters, "Parameters", false, 1);
	n_settings->AddPage(w_results, "Results", false, 2);

	sb_status = new wxStatusBar(this);
	sb_status->SetFieldsCount(3);
	const int status_bar_widths[3] = { 200, -1, -1 };
	sb_status->SetStatusWidths(3, status_bar_widths);

	sizer_main->Add(bs_main_toolbar, 0, wxEXPAND, 0);
	sizer_main->Add(n_settings, 1, wxEXPAND|wxTOP, 2);
	sizer_main->Add(sb_status, 0, wxEXPAND, 0);

	Bind(wxEVT_CLOSE_WINDOW, &t_main_window::on_close_window_clicked, this);
	Bind(wxEVT_SHOW, &t_main_window::OnShow, this);
	SetAutoLayout(true);
	SetSizer(sizer_main);
	sizer_main->SetSizeHints(this);

	fd_open_data = new wxFileDialog(this, _("Open data file"), "", "",
		"Data (*.*)|*.*|CSV (*.csv)|*.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	fd_open_project = new wxFileDialog(this, _("Open project"), "", "",
		"XML files (.xml)|*.xml", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	set_target_output_chart_options(mepx_settings.target_output_chart_options);
	set_evolution_chart_options(mepx_settings.evolution_chart_options);
}
//-------------------------------------------------------------------------
