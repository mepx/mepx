// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <wx/filename.h>
#include <wx/numdlg.h>
#include <wx/choicdlg.h>
#include <wx/url.h>
#include <wx/sstream.h>
//-------------------------------------------------------------------------
#include "mepx_app.h"

#include "windows/main_window.h"
#include "windows/about_window.h"
#include "windows/scale_limits_window.h"
#include "windows/replace_symbol_window.h"
#include "windows/updates_window.h"

#include "mepx_project.h"
#include "utils/time_utils.h"
#include "utils/version_utils.h"
#include "utils/validation_string.h"
#include "app_x_info.h"
//-------------------------------------------------------------------------
#define TIMER_ID 1300

#define timer_interval 100
//-------------------------------------------------------------------------
t_main_window * f_main_window = NULL;
//-------------------------------------------------------------------------
t_main_window::t_main_window(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	set_language();


	create_interface();

#ifdef __WXMAC__
    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* testmenu = new  wxMenu();

    testmenu->Append(wxID_EXIT, _("Exit"));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(t_main_window::OnExitMenuClicked));

    menubar->Append(testmenu, _("File"));

    menubar->Remove(0);

    SetMenuBar(menubar);
#endif

	t_timer = new wxTimer;
	t_timer->SetOwner(this, TIMER_ID);
	Bind(wxEVT_TIMER, &t_main_window::on_timer, this);

	mep_engine_thread = NULL;
	loading_data = false;
}
//-------------------------------------------------------------------------
void t_main_window::OnExitMenuClicked(wxCommandEvent&)
{
    Close();
}
//------------------------------------------------------------------------
void t_main_window::on_close_window_clicked(wxCloseEvent& event)
{
	t_timer->Stop();

	mep_engine.stop();

	if (mep_engine_thread) {
		mep_engine_thread->join();
		delete mep_engine_thread;
		mep_engine_thread = NULL;
	}

	if (event.CanVeto() &&
		(mep_engine.is_project_modified() ||
		mep_engine.get_training_data_ptr()->is_modified() ||
		mep_engine.get_validation_data_ptr()->is_modified() ||
		mep_engine.get_test_data_ptr()->is_modified())) {
		int answer = wxMessageBox("Do you want to save existing project?", "info", wxYES_NO | wxCANCEL);
		if (answer == wxYES) {
			if (!s_project_name) {
				wxString wx_file_name = get_project_filename_to_save();
				const char * fname = wx_file_name.utf8_str();
				if (wx_file_name != "" && do_save_project(fname)) {
					s_project_name = new char[strlen(fname) + 1];
					strcpy(s_project_name, fname);
				}
				else {
					event.Veto();
					return;
				}
			}
			else
				if (!do_save_project(s_project_name)) {
					event.Veto();
					return;
				}
		}
		else
			if (answer == wxCANCEL) {
				event.Veto();
				return;
			}
	}

	get_interface_layout(&mepx_settings.interface_layout);

	delete m_training_columns;

	delete t_timer;

	delete fd_open_data;
	delete fd_open_project;

	delete il_notebook;

	Destroy();
}
//-------------------------------------------------------------------------
void t_main_window::set_language(void)
{
	num_incorrectly_classified = "num. incorrectly classified";
	best_num_incorrectly_classified_percent = "best num. incorrectly classified (%)";
	average_num_incorrectly_classified_percent = "average num. incorrectly classified (%)";
}
//-------------------------------------------------------------------------
void t_main_window::on_save_project_button_clicked(wxCommandEvent &)
{
	if (!s_project_name) {
		wxString wx_file_name = get_project_filename_to_save();
		const char * fname = wx_file_name.utf8_str();
		if (wx_file_name != "" && do_save_project(fname)) {
			s_project_name = new char[strlen(fname) + 1];
			strcpy(s_project_name, fname);

			SetLabel(wxString(app_name) + " - " + wxString().FromUTF8(s_project_name));
		}
	}
	else {
		if (do_save_project(s_project_name)) {

		}

	}
}
//-------------------------------------------------------------------------
wxString t_main_window::get_project_filename_to_save(void)
{
	wxFileDialog
		fd_save_project(this, _("Save project"), "", "",
			"XML files (.xml)|*.xml", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	char * tmp_s = current_time_to_string();
	fd_save_project.SetFilename("mepx_project_" + wxString(tmp_s));
	delete[]tmp_s;

	if (fd_save_project.ShowModal() != wxID_OK)
		return "";

	wxFileName fname;
	fname.Assign(fd_save_project.GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		fname.SetExt("xml");
		//ext = "xml";
	}

	wxString file_name = fname.GetFullPath();
	return file_name;
}
//-------------------------------------------------------------------------
bool t_main_window::do_save_project(const char *file_name)
{
	char error_message[1000];
	if (!get_parameters_from_UI(mep_engine.get_parameters_ptr(), error_message)) {
		wxMessageBox(error_message, "Error");
		return false;
	}

	if (!get_constants_from_UI(mep_engine.get_constants_ptr(),
							   error_message,
							   mep_engine.get_parameters_ptr()->get_data_type())) {
		wxMessageBox(error_message, "Error");
		return false;
	}
	get_functions_from_UI(mep_engine.get_functions_ptr());
	mep_engine.init_enabled_variables();
	get_enabled_grid_columns();

	mep_engine.set_problem_description(tc_problem_description->GetValue().ToUTF8());

	wxWindow::SetCursor(wxCURSOR_WAIT);
	//to_xml_file(file_name, app_version_nr);
	
	mep_engine.to_xml_file(file_name);

	wxWindow::SetCursor(wxNullCursor);

	b_save_project->Enable(false);
	//st_project_name->SetForegroundColour(*wxBLACK);
	//st_project_name->Refresh();

	return true;
}
//-------------------------------------------------------------------------
void t_main_window::on_save_as_project_button_clicked(wxCommandEvent &)
{
	wxString wx_file_name = get_project_filename_to_save();
	const char * fname = wx_file_name.utf8_str();

	if (wx_file_name != "" && do_save_project(fname)) {
		//project_name = wx_file_name;
		if (s_project_name)
			delete[] s_project_name;
		s_project_name = new char[strlen(fname) + 1];
		strcpy(s_project_name, fname);

		SetLabel(wxString(app_name) + " - " + wxString().FromUTF8(s_project_name));
	}
}
//-------------------------------------------------------------------------
void t_main_window::on_load_project_button_clicked(wxCommandEvent &)
{
	if (mep_engine.is_project_modified() ||
		mep_engine.get_training_data_ptr()->is_modified() ||
		mep_engine.get_validation_data_ptr()->is_modified() ||
		mep_engine.get_test_data_ptr()->is_modified() ||
		mep_engine.get_functions_ptr()->is_modified()) {
		if (wxMessageBox("Do you want to save existing project?", "info", wxYES_NO) == wxYES) {
			if (!s_project_name) {
				wxString wx_file_name = get_project_filename_to_save();
				const char * fname = wx_file_name.utf8_str();
				if (!(wx_file_name != "" && do_save_project(fname)))
					return;
			}
			else
				if (!do_save_project(s_project_name))
					return;
		}
	}

	if (fd_open_project->ShowModal() != wxID_OK)
		return;     // the user changed idea...

	wxString wx_file_name = fd_open_project->GetPath();
	const char* fname = wx_file_name.utf8_str();
	if (s_project_name)
		delete[] s_project_name;
	s_project_name = new char[strlen(fname) + 1];
	strcpy(s_project_name, fname);

	wxWindow::SetCursor(wxCURSOR_WAIT);
	if (!load_project()){
		if (s_project_name){
			delete[] s_project_name;
			s_project_name = NULL;
		}
	}
	wxWindow::SetCursor(wxNullCursor);

	switch (rb_problem_type->GetSelection()) {
		case MEP_PROBLEM_REGRESSION:
		case MEP_PROBLEM_TIME_SERIE:
			st_runs_errors->SetLabel(s_runs_errors_label_regression);
			p_runs->Layout();
			break;
		case MEP_PROBLEM_BINARY_CLASSIFICATION:
		case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
			st_runs_errors->SetLabel(s_runs_errors_label_classification);
			p_runs->Layout();
			break;
	}
	sizer_toolbar_stats->Layout();
}
//-------------------------------------------------------------------------
bool t_main_window::load_project(void)
{
    if (!s_project_name)
        return false;

	clear_results();

	loading_data = true;

	if (!mep_engine.from_xml_file(s_project_name)) {
		wxMessageBox("Error loading project", "Error");
		SetLabel(app_name);
		return false;
	}

	set_functions_to_UI(mep_engine.get_functions_ptr(),
						mep_engine.get_parameters_ptr()->get_data_type());
	set_parameters_to_UI(mep_engine.get_parameters_ptr());
	set_constants_to_UI(mep_engine.get_parameters_ptr()->get_constants_probability(),
						mep_engine.get_constants_ptr(),
						mep_engine.get_parameters_ptr()->get_data_type());
	//set_interface_settings(&mepx_interface_settings);
	g_training_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	g_training_data->update_num_rows_cols();

	set_enabled_grid_columns();
	g_validation_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	g_validation_data->update_num_rows_cols();
	
	if (mep_engine.get_training_data_ptr()->get_num_cols() ==
		mep_engine.get_test_data_ptr()->get_num_cols())
		g_test_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	else
		g_test_data->num_outputs = 0;
	g_test_data->update_num_rows_cols();

	show_errors_in_grids(mep_engine.get_last_run_index());

	set_results();
	mepx_settings.target_output_chart_options.init();
	set_target_output_chart_options(mepx_settings.target_output_chart_options);
	set_evolution_chart_options(mepx_settings.evolution_chart_options);

	if (mep_engine.get_last_run_index() > -1) {
		g_stats->Select(mep_engine.get_last_run_index());
		process_on_stats_row_change(mep_engine.get_last_run_index());
		show_errors_in_grids(mep_engine.get_last_run_index());
		show_program(mep_engine.get_last_run_index());
	}
	else {
		last_processed_run = -1;
		last_processed_generation = -1;
	}

	loading_data = false;

	set_project_info();

	update_advance_commands_buttons();

	SetLabel(wxString(app_name) + " - " + wxString().FromUTF8(s_project_name));
	tc_problem_description->ChangeValue(wxString().FromUTF8(mep_engine.get_problem_description()));

	bs_main_toolbar->Layout();

	b_save_project->Enable(false);
	update_results_buttons();
	//	st_project_name->SetForegroundColour(*wxBLACK);
	//	st_project_name->Refresh();

	do_problem_type_changed();
	return true;
}
//-------------------------------------------------------------------------
void t_main_window::on_new_project_button_clicked(wxCommandEvent &)
{
	if (mep_engine.is_project_modified() ||
		mep_engine.get_training_data_ptr()->is_modified() ||
		mep_engine.get_validation_data_ptr()->is_modified() ||
		mep_engine.get_test_data_ptr()->is_modified()) {

		int result = wxMessageBox("Do you want to save existing project?", "info", wxYES|wxNO|wxCANCEL);
		switch (result) {
			case wxYES: {
				if (!s_project_name) {
					wxString wx_file_name = get_project_filename_to_save();
					const char* fname = wx_file_name.utf8_str();
					if (wx_file_name != "" && do_save_project(fname)) {
						//project_name = wx_file_name;
						s_project_name = new char[strlen(fname) + 1];
						strcpy(s_project_name, fname);
						do_new_project();
					}
				}
				else
					if (do_save_project(s_project_name)) {
						do_new_project();
					}
				}
				break;
			case wxNO:
				do_new_project();
				break;
			case wxCANCEL:
				// do nothing
				break;
		}
	}
	else
		do_new_project();

	update_advance_commands_buttons();
}
//-------------------------------------------------------------------------
void t_main_window::do_new_project(void)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	mep_engine.init();
	mep_engine.get_training_data_ptr()->clear_data();
	mep_engine.get_validation_data_ptr()->clear_data();
	mep_engine.get_test_data_ptr()->clear_data();

	clear_results();

	set_functions_to_UI(mep_engine.get_functions_ptr(), mep_engine.get_parameters_ptr()->get_data_type());
	//	set_enable_operators();
	set_parameters_to_UI(mep_engine.get_parameters_ptr());
	set_constants_to_UI(mep_engine.get_parameters_ptr()->get_constants_probability(),
						mep_engine.get_constants_ptr(),
						mep_engine.get_parameters_ptr()->get_data_type());

	mepx_settings.target_output_chart_options.init();
	set_target_output_chart_options(mepx_settings.target_output_chart_options);
	set_evolution_chart_options(mepx_settings.evolution_chart_options);

	g_training_data->update_num_rows_cols();
	g_test_data->update_num_rows_cols();
	g_validation_data->update_num_rows_cols();

	set_project_info();

	if (s_project_name) {
		delete[] s_project_name;
		s_project_name = NULL;
	}

	SetLabel(app_name);
	tc_problem_description->ChangeValue(wxString().FromUTF8(mep_engine.get_problem_description()));

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	n_data->SetSelection(0);
	n_error_tables->SetSelection(0);
	n_settings->SetSelection(0);
	
	do_problem_type_changed();

	wxWindow::SetCursor(wxNullCursor);
}
//-------------------------------------------------------------------------
bool t_main_window::validate_project(char * error_message)
{
	// validate data`
	if (mep_engine.get_training_data_ptr()->get_num_rows() == 0) {
		strcpy(error_message, "There are no training data! Please enter some data!");
		return false;
	}
	
	if (!get_parameters_from_UI(mep_engine.get_parameters_ptr(), error_message))
		return false;

	if (!get_constants_from_UI(mep_engine.get_constants_ptr(), error_message,
							   mep_engine.get_parameters_ptr()->get_data_type()))
		return false;
	
	mep_engine.init_enabled_variables();
	get_enabled_grid_columns();
	mep_engine.compute_list_of_enabled_variables();

	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
		if (mep_engine.get_num_actual_variables() == 0) {
			strcpy(error_message, "There are no variables selected! Please select some variables!");
			return false;
		}
	}

	wxString s_operators_probability = tc_operators_probability->GetValue().Trim();

	double d_operators_probability;
	if (!is_valid_double(s_operators_probability.utf8_str(), &d_operators_probability)) {
		strcpy(error_message, "Invalid number");
		tc_operators_probability->SetFocus();
		return false;
	}


	wxString s_variables_probability = tc_variables_probability->GetValue().Trim();
	double d_variables_probability;
	if (!is_valid_double(s_variables_probability.utf8_str(), &d_variables_probability)) {
		strcpy(error_message, "Invalid number");
		tc_variables_probability->SetFocus();
		return false;
	}

	if (d_variables_probability + d_operators_probability > 1) {
		strcpy(error_message, "Operators probabilities + Variables probabilities must be less or equal to 1");
		return false;
	}

	double d_constants_probability = 1 - d_variables_probability - d_operators_probability;
	tc_constants_probability->SetValue(wxString() << d_constants_probability);

	//char error_message[1000];
	get_functions_from_UI(mep_engine.get_functions_ptr());

	return true;
}
//-------------------------------------------------------------------------
void t_main_window::on_timer(wxTimerEvent&)
{
	update_results();
}
//-------------------------------------------------------------------------
void t_main_window::on_stop_button_clicked(wxCommandEvent &)
{
	mep_engine.stop();
}
//-------------------------------------------------------------------------
void t_main_window::start(void)
{
	mep_engine.start(NULL, NULL, NULL);
}
//-------------------------------------------------------------------------
void t_main_window::on_start_button_clicked(wxCommandEvent &)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	wxWindow::SetCursor(wxNullCursor);

	char error_message[1000];
	if (!validate_project(error_message) || !mep_engine.validate_project(error_message, 1000)) {
		wxMessageBox(error_message, "Error");
		return;
	}

	wxWindow::SetCursor(wxCURSOR_WAIT);

	disable_when_start();

	n_settings->SetSelection(2);
	last_processed_generation = -1;
	last_processed_run = -1;

	is_on_timer_running = false;

	if (mep_engine_thread) {
		mep_engine_thread->join();
		delete mep_engine_thread;
	}

	t_timer->Start(timer_interval);
	mep_engine_thread = new std::thread(&t_main_window::start, this);
}
//-------------------------------------------------------------------------
void t_main_window::on_about_button_clicked(wxCommandEvent &)
{
	f_about_window->CenterOnParent();
	if (f_about_window->ShowModal() == wxID_OK) {
	}
}
//---------------------------------------------------------------------
void t_main_window::on_change_data_page(wxBookCtrlEvent& event)
{
	/*
	switch (n_data->GetSelection()) {
	case 0:// training
	b_load_data->Enable(true);
	b_clear_data->Enable(true);
	b_save_data->Enable(true);


	b_load_data->SetLabel("Load training data");
	b_clear_data->SetLabel("Clear training data");
	b_save_data->SetLabel("Save training data");
	//		b_save_as_data->SetLabel("Save training data as");

	b_load_data->Fit();
	b_clear_data->Fit();
	b_save_data->Fit();

	bs_data_commands->Layout();

	break;
	case 1:// validation
	b_load_data->Enable(true);
	b_clear_data->Enable(true);
	b_save_data->Enable(true);

	b_load_data->SetLabel("Load validation data");
	b_clear_data->SetLabel("Clear validation data");
	b_save_data->SetLabel("Save validation data");

	b_load_data->Fit();
	b_clear_data->Fit();
	b_save_data->Fit();

	//		b_save_as_data->SetLabel("Save validation data as");
	bs_data_commands->Layout();
	break;
	case 2:// test
	b_load_data->Enable(true);
	b_clear_data->Enable(true);
	b_save_data->Enable(true);

	b_load_data->SetLabel("Load testing data");
	b_clear_data->SetLabel("Clear testing data");
	b_save_data->SetLabel("Save testing data");
	b_load_data->Fit();
	b_clear_data->Fit();
	b_save_data->Fit();

	//		b_save_as_data->SetLabel("Save testing data as");
	bs_data_commands->Layout();
	break;
	case 3:// description
	b_load_data->Enable(false);
	b_clear_data->Enable(false);
	b_save_data->Enable(false);

	break;
	}
	*/
	event.Skip();
}
//---------------------------------------------------------------------
void t_main_window::on_settings_button_clicked(wxCommandEvent &)
{

}
//---------------------------------------------------------------------
void t_main_window::on_update_button_clicked(wxCommandEvent&)
{
	wxURL url(wxT("http://www.mepx.org/mepx_version.txt"));
	wxURLError url_error = url.GetError();

	if (url_error != wxURL_NOERR) {
		wxMessageBox(wxString().FromUTF8("Cannot connect to the Internet. Please visit the website from a browser!"));
		return;
	}

	wxInputStream* in = url.GetInputStream();

	if (!in) {
		wxMessageBox("Cannot read version file!");
		return;
	}

	if (!in->IsOk()) {
		wxMessageBox("Cannot read version file!");
		delete in;
		return;
	}

	wxString s_new_version;
	wxStringOutputStream html_stream(&s_new_version);
	in->Read(html_stream);
	//wxMessageBox(s_new_version);

	int M_web, m_web, r_web, b_web;

	if (!parse_version(s_new_version.c_str(), M_web, m_web, r_web, b_web)) {
		wxMessageBox("Incomplete version number! Please contact me at mihai.oltean@gmail.com");
		delete in;
		return;
	}
	int M_current, m_current, r_current, b_current;

	parse_version(app_version_nr , M_current, m_current, r_current, b_current);

	if (newer_version(M_web, m_web, r_web, b_web, M_current, m_current, r_current, b_current)) {
		if (!f_updates_window)
			f_updates_window = new t_updates_window(this);
		
		f_updates_window->st_current_version->SetLabel(wxString("Current version: ") + wxString(app_version_nr));
		f_updates_window->st_new_version->SetLabel(wxString("New version: ") + s_new_version);

		f_updates_window->ShowModal();
	}
	else
		wxMessageBox("You already have the latest version installed!");

	delete in;
}
//----------------------------------------------------------------
void t_main_window::OnShow(wxShowEvent& event)
{
	if (!event.IsShown()) {
		event.Skip();
		return;
	}

	set_language();

	wxWindow::SetCursor(wxCURSOR_WAIT);
	if (!load_project()){
		if (s_project_name){
			delete[] s_project_name;
			s_project_name = NULL;
		}
	}
	wxWindow::SetCursor(wxNullCursor);

	switch (rb_problem_type->GetSelection()) {
		case MEP_PROBLEM_REGRESSION:
		case MEP_PROBLEM_TIME_SERIE:
			st_runs_errors->SetLabel(s_runs_errors_label_regression);
			p_runs->Layout();
			break;
		case MEP_PROBLEM_BINARY_CLASSIFICATION:
		case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
			st_runs_errors->SetLabel(s_runs_errors_label_classification);
			p_runs->Layout();
			break;
	}
	sizer_toolbar_stats->Layout();
	update_advance_commands_buttons();

	event.Skip();
}
//-------------------------------------------------------------------------- -
void t_main_window::on_change_main_notebook_page(wxBookCtrlEvent& event)
{
	if (event.GetOldSelection() == PARAMETERS_PAGE) {
		// parameters selected before
		// try to extract the num_predictions
		long value_l;
		if (!tc_num_predictions->GetValue().Trim().ToLong(&value_l)) {
//			strcpy(error_message, "Num. predictions: Invalid number!");
			tc_num_predictions->SetValue(wxString::Format("%d", mep_engine.get_parameters_ptr()->get_num_predictions()));
		}
		else {
			if (value_l < 0) {
				tc_num_predictions->SetValue(wxString::Format("%d", mep_engine.get_parameters_ptr()->get_num_predictions()));
			}
			else {
				if (mep_engine.get_parameters_ptr()->get_num_predictions() != (unsigned int)value_l) {
					mep_engine.get_parameters_ptr()->set_num_predictions((unsigned int)value_l);

					int run = -1;
					long selected = g_stats->GetFirstSelected();
					if (selected != -1 && selected <= mep_engine.get_last_run_index())
						run = (int)selected;

					show_predictions_in_grid(run);
				}
			}
		}
	}
}
//-------------------------------------------------------------------------- -
