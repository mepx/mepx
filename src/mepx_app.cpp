// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <string.h>
//------------------------------------------------------------------------
#include <wx/log.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
//------------------------------------------------------------------------
#include "windows/main_window.h"
#include "windows/about_window.h"
#include "windows/scale_limits_window.h"
#include "windows/replace_symbol_window.h"
#include "windows/import_data_window.h"
#include "windows/decimal_separator_selector_window.h"
//------------------------------------------------------------------------
#include "mepx_app.h"
#include "mepx_project.h"
#include "app_x_info.h"
//-------------------------------------------------------------------------
char* s_project_name;

wxString param_stop_filename = "";
//------------------------------------------------------------------------
t_mep mep_engine;
//------------------------------------------------------------------------
void on_progress_command_line(void)
{
	if (wxFileExists(param_stop_filename))
		mep_engine.stop();
}
//---------------------------------------------------------
IMPLEMENT_APP(t_MEPX)
//---------------------------------------------------------
t_MEPX::t_MEPX(void) : wxApp()
{
	/*
	_CrtDumpMemoryLeaks(); //memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(429904);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	*/
}
//---------------------------------------------------------
bool t_MEPX::OnInit()
{
	setlocale(LC_NUMERIC, "");

	s_project_name = NULL;
	param_stop_filename = "";
	
	strcpy(s_runs_errors_label_regression, "Runs (Errors)");
	strcpy(s_runs_errors_label_classification, "Runs (Num. incorrect %)");

	
	if (wxApp::argc == 1 || wxApp::argc == 2) {
		run_from_command_line = false;
		wxString docs_path = wxStandardPaths::Get().GetDocumentsDir();

		//wxMessageBox(docs_path);

		wxFileName app_docs_path;
		app_docs_path.AssignDir(docs_path);
		app_docs_path.AppendDir("mepx");

		wxString app_docs_path_as_string = app_docs_path.GetFullPath();
		if (!wxDirExists(app_docs_path_as_string))
			wxMkdir(app_docs_path_as_string);

		wxFileName settings_dir = app_docs_path;
		settings_dir.AppendDir("settings");

		wxString app_settings_path_as_string = settings_dir.GetFullPath();
		if (!wxDirExists(app_settings_path_as_string))
			wxMkdir(app_settings_path_as_string);

		wxFileName full_params_path(settings_dir.GetFullPath(), params_file_name);

		settings_path = full_params_path.GetFullPath();

		if (full_params_path.Exists())
			if (mepx_settings.from_xml_file(settings_path.utf8_str())) {}

		// call the base class initialization method, currently it only parses a
		// few common command-line options but it could be do more in the future
		//if (!wxApp::OnInit())
			//return false;

		// create the main application window
		f_main_window = new t_main_window(app_name);
		f_about_window = new t_about_window(f_main_window, "About", wxPoint(50, 50), wxSize(450, 340));
		f_scale_limits_window = new t_scale_limits_window(f_main_window, "Interval", wxPoint(50, 50), wxSize(450, 340));
		f_replace_symbol_window = new t_replace_symbol_window(f_main_window, "Replace values", wxPoint(50, 50), wxSize(450, 340));
		f_import_data_window = new t_import_data_window(f_main_window, "Import data settings", wxPoint(50, 50), wxSize(550, 340));
		f_decimal_separator_selector_window = new t_decimal_separator_selector_window(f_main_window, "Separator", wxPoint(50, 50), wxSize(250, 340));

		f_main_window->do_new_project();

		if (wxApp::argc == 2) {
			 wxString input_filename = wxApp::argv[1];
			s_project_name = new char[strlen(input_filename.utf8_str()) + 1];
			 strcpy(s_project_name, input_filename.utf8_str());
			//from_xml_file(input_filename.utf8_str());
		}
		/*
		training_data_error_provider.data = mep_engine.get_training_data_ptr();

		validation_data_error_provider.data = mep_engine.get_validation_data_ptr();
		test_data_error_provider.data = mep_engine.get_test_data_ptr();
*/
		// and show it (the frames, unlike simple controls, are not shown when
		// created initially)
		SetTopWindow(f_main_window);
		f_main_window->Show(true);
		f_main_window->Maximize();

		f_main_window->splitter_stats_evolution->SetSashPosition(mepx_settings.interface_layout.stats_table_height);
		f_main_window->splitter_runs_results->SetSashPosition(mepx_settings.interface_layout.stats_table_width);
		f_main_window->splitter_charts_code->SetSashPosition(mepx_settings.interface_layout.errors_table_width);
		f_main_window->splitter_code_graphics->SetSashPosition(mepx_settings.interface_layout.code_box_height);
	}
	else
		if (wxApp::argc >= 3) {
			
			optimize_from_command_line();
		}

	return true;
}
//---------------------------------------------------------
int t_MEPX::OnExit()
{
	if (!run_from_command_line) {
		if (s_project_name) {
			delete[] s_project_name;
			s_project_name = NULL;
		}

		if (!mepx_settings.to_xml_file(settings_path.utf8_str()))
			wxMessageBox("Cannot save settings! Please contact me at mihai.oltean@gmail.com", "Error");
	}
	return true;
}
//------------------------------------------------------------------------
void t_MEPX::optimize_from_command_line(void)
{
	run_from_command_line = true;

	wxString input_filename = wxApp::argv[1];
	wxString output_filename = wxApp::argv[2];

	if (wxApp::argc == 4)
		param_stop_filename = wxApp::argv[3];


	if (mep_engine.from_xml_file(input_filename.utf8_str())) {
		int error = mep_engine.start(on_progress_command_line, NULL, NULL);
		if (!error) {
			if (!mep_engine.to_xml_file(output_filename.utf8_str()))//, app_version_nr))
				return;
		}
		else
			return;
	}
	else {
		// cannot open input file
		// write the error to file


		FILE* f = NULL;

#ifdef _WIN32
		f = _wfopen(output_filename.wc_str(), L"w");
#else
		const char* filename = output_filename.utf8_str();
		f = fopen(filename, "w");
#endif

		if (f) {
			//	fprintf(f, "%s\n", my_project.software_version.data);
			fprintf(f, "ERROR: Cannot open input file!\n");
			fclose(f);
		}
	}
}
//------------------------------------------------------------------------
int t_MEPX::OnRun()
{
	if (run_from_command_line)
		ExitMainLoop();
	else
		wxApp::OnRun();

	return 0;
}
//------------------------------------------------------------------------
