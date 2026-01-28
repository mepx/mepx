// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <wx/filename.h>
#include <wx/clipbrd.h>
//-----------------------------------------------------------------------------------------
#include "windows/main_window.h"
#include "utils/time_utils.h"
#include "mepx_project.h"
#include "mepx_save_errors.h"
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
#define MEP_CPP_CODE 0
#define MEP_VBA_CODE 1
#define MEP_PYTHON_CODE 2
#define MEP_CPP_INFIX_CODE 3
#define MEP_LATEX_CODE 4
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
#define TRAINING_ERRORS_PAGE 0
#define VALIDATION_ERRORS_PAGE 1
#define TEST_ERRORS_PAGE 2
#define PREDICTION_ERRORS_PAGE 3
//-----------------------------------------------------------------------------------------
void t_main_window::on_to_clipboard_code_button_clicked(wxCommandEvent&)
{
	if (!wxTheClipboard->Open())
		return;

	wxTheClipboard->Clear();
	wxTheClipboard->SetData(new wxTextDataObject(tc_source_code->GetValue().mb_str()));
	wxTheClipboard->Close();
}
//---------------------------------------------------------------------
void t_main_window::on_save_code_button_clicked(wxCommandEvent&)
{
	wxFileDialog* fd_save_code = NULL;
	switch (cb_language->GetSelection()) {
	case MEP_CPP_CODE:
	case MEP_CPP_INFIX_CODE:
		fd_save_code = new wxFileDialog(this, _("Save file"), "", "",
				"C files (.c)|*.c", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		break;
	case MEP_VBA_CODE:
		fd_save_code = new wxFileDialog(this, _("Save file"), "", "",
				"VBA files (.vba)|*.vba", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		break;
	case MEP_PYTHON_CODE:
		fd_save_code = new wxFileDialog(this, _("Save file"), "", "",
			"Python files (.py)|*.py", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		break;
	case MEP_LATEX_CODE:
		fd_save_code = new wxFileDialog(this, _("Save file"), "", "",
				"Latex files (.tex)|*.tex", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		break;
	}

	char* tmp_s = current_time_to_string();
	fd_save_code->SetFilename("mepx_" + wxString(tmp_s));
	delete[]tmp_s;

	if (fd_save_code->ShowModal() != wxID_OK)
		return;

	wxFileName fname;
	fname.Assign(fd_save_code->GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		switch (cb_language->GetSelection()) {
		case MEP_CPP_CODE:
		case MEP_CPP_INFIX_CODE:
			fname.SetExt("c");
			break;
		case MEP_VBA_CODE:
			fname.SetExt("vba");
			break;
		case MEP_PYTHON_CODE:
			fname.SetExt("py");
			break;
		case MEP_LATEX_CODE:
			fname.SetExt("tex");
			break;
		}
	}

	tc_source_code->SaveFile(fname.GetFullPath());
	delete fd_save_code;
}
//---------------------------------------------------------------------
void t_main_window::on_stats_row_change(wxListEvent&)
{
	if (mep_engine.is_running() || loading_data || t_timer->IsRunning())
		return;
	long selected = g_stats->GetFirstSelected();
	if (selected != -1 && selected <= mep_engine.get_last_run_index()) {
		last_processed_run = (int)selected;
	}
	else
		last_processed_run = -1;

	process_on_stats_row_change(last_processed_run);
	update_results_buttons();
}
//---------------------------------------------------------------------
void t_main_window::process_on_stats_row_change(int row_index)
{
	//last_processed_run = row_index;
	if (row_index != -1)
		last_processed_generation = mep_engine.get_stats_ptr()->get_latest_generation(row_index);
	else
		last_processed_generation = -1;

	show_errors_in_grids(row_index);
	show_program(row_index);
	set_status_bar_info(row_index, last_processed_generation);
	//draw_evolution();
	update_target_combobox();
	p_chart_evolution->Refresh();
	p_chart_target_output->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::update_target_combobox(void)
{
	cb_target_for_chart->Clear();
	unsigned int num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	for (unsigned int o = 0; o < num_outputs; o++)
		cb_target_for_chart->Append(wxString("Output") + wxString() << o);
	cb_target_for_chart->SetSelection(0);
}
//---------------------------------------------------------------------
void t_main_window::set_results(void)
{
	for (int r = 0; r <= mep_engine.get_last_run_index(); r++) {
		run_errors.add_new_item();
		run_errors.data[run_errors.count - 1].run_index = r;
		
		set_run_stats(r);
		last_processed_run = r;
		last_processed_generation = mep_engine.get_stats_ptr()->get_latest_generation(last_processed_run);
	}

	if (last_processed_run >= 0) {

		if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_REGRESSION ||
			mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE) {
			mep_engine.get_stats_ptr()->get_mean_error(run_errors.mean_training,
													run_errors.mean_validation,
													run_errors.mean_test,
													run_errors.mean_runtime,
													run_errors.mean_code_length);
			mep_engine.get_stats_ptr()->get_sttdev_error(run_errors.stddev_training,
													  run_errors.stddev_validation,
													  run_errors.stddev_test,
													  run_errors.stddev_runtime,
													  run_errors.stddev_code_length);
			mep_engine.get_stats_ptr()->get_best_error(run_errors.best_training,
													run_errors.best_validation,
													run_errors.best_test,
													run_errors.best_runtime,
													run_errors.best_code_length);
		}
		else {
			mep_engine.get_stats_ptr()->get_mean_num_incorrect(run_errors.mean_training,
															run_errors.mean_validation,
															run_errors.mean_test,
															run_errors.mean_runtime,
															run_errors.mean_code_length);
			mep_engine.get_stats_ptr()->get_sttdev_num_incorrect(run_errors.stddev_training,
															  run_errors.stddev_validation,
															  run_errors.stddev_test,
															  run_errors.stddev_runtime,
															  run_errors.stddev_code_length);
			mep_engine.get_stats_ptr()->get_best_num_incorrect(run_errors.best_training,
															run_errors.best_validation,
															run_errors.best_test,
															run_errors.best_runtime,
															run_errors.best_code_length);
		}

		g_stats->update_num_rows(true);
	}
}
//---------------------------------------------------------------------
void t_main_window::on_save_errors_button_clicked(wxCommandEvent&)
{
	int what_to_save = n_error_tables->GetSelection();
	wxString dialog_title = "";
	switch (what_to_save) {
	case TRAINING_ERRORS_PAGE:
		// training
		dialog_title = "Save training error";
		break;
	case VALIDATION_ERRORS_PAGE:
		// validation
		dialog_title = "Save validation error";
		break;
	case TEST_ERRORS_PAGE:
		// testing
		dialog_title = "Save test error";
		break;
	case PREDICTIONS_PAGE:
		// testing
		dialog_title = "Save predictions";
		break;
	}

	wxFileDialog
		fd_save_errors(this, "Save", "", "",
			"CSV files(;) (.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	char* tmp_s = current_time_to_string();
	switch (what_to_save) {
	case TRAINING_ERRORS_PAGE:
		// training
		fd_save_errors.SetFilename("mepx_errors_training_" + wxString(tmp_s));
		break;
	case VALIDATION_ERRORS_PAGE:
		// validation
		fd_save_errors.SetFilename("mepx_errors_validation_" + wxString(tmp_s));
		break;
	case TEST_ERRORS_PAGE:
		// testing
		fd_save_errors.SetFilename("mepx_errors_test_" + wxString(tmp_s));
		break;
	case PREDICTIONS_PAGE:
		// testing
		fd_save_errors.SetFilename("mepx_predictions_" + wxString(tmp_s));
		break;
	}
	delete[] tmp_s;

	if (fd_save_errors.ShowModal() != wxID_OK)
		return;

	wxFileName fname;
	fname.Assign(fd_save_errors.GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		fname.SetExt("csv");
		ext = "csv";
	}

	wxString wx_file_name = fname.GetFullPath();

	bool save_result = false;
	switch (what_to_save) {
	case TRAINING_ERRORS_PAGE:// training
		save_result = save_training_errors_to_csv_file(wx_file_name);
		break;
	case VALIDATION_ERRORS_PAGE:// validation
		save_result = save_validation_errors_to_csv_file(wx_file_name);
		break;
	case TEST_ERRORS_PAGE:// test
		save_result = save_test_errors_to_csv_file(wx_file_name);
		break;
	case PREDICTIONS_PAGE:// test
		save_result = save_predictions_to_csv_file(wx_file_name, last_processed_run);
		break;
	}

	if (!save_result) {
		wxMessageBox("Cannot save file", "error");
		return;
	}
}
//---------------------------------------------------------------------
void t_main_window::on_save_stats_button_clicked(wxCommandEvent&)
{
	wxFileDialog
		fd_save_stats(this, _("Save files"), "", "",
			"CSV(.csv)|*.csv|Latex (.tex)|*.tex|HTML (.html)|*.html", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	char* tmp_s = current_time_to_string();
	fd_save_stats.SetFilename("mepx_stats_" + wxString(tmp_s));
	delete[] tmp_s;

	if (fd_save_stats.ShowModal() != wxID_OK)
		return;

	wxFileName fname;
	fname.Assign(fd_save_stats.GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		fname.SetExt("csv");
		ext = "csv";
	}

	if (ext == "tex")
		mep_engine.get_stats_ptr()->to_tex_file(fname.GetFullPath().utf8_str(), mep_engine.get_parameters_ptr()->get_problem_type());
	else
		if (ext == "csv")
			mep_engine.get_stats_ptr()->to_csv_file(fname.GetFullPath().utf8_str(), mep_engine.get_parameters_ptr()->get_problem_type());
		else
			mep_engine.get_stats_ptr()->to_html_file(fname.GetFullPath().utf8_str(), mep_engine.get_parameters_ptr()->get_problem_type());
}
//---------------------------------------------------------------------
void t_main_window::on_simplified_code_clicked(wxCommandEvent&)
{
	show_program(last_processed_run);
}
//---------------------------------------------------------------------
void t_main_window::show_errors_in_grids(int run)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	training_data_error_provider.set_run(run,
										 mep_engine.get_training_data_ptr()->get_num_rows(),
										 mep_engine.get_training_data_ptr(),
										 mep_engine.get_parameters_ptr()->get_num_outputs(),
										 true);
	if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
		mep_engine.compute_output_on_training(run, training_data_error_provider.output_long_long,
									   training_data_error_provider.valid_output);
	else
		mep_engine.compute_output_on_training(run, training_data_error_provider.output_double,
									   training_data_error_provider.valid_output);

	g_error_training->my_update();

	if (mep_engine.get_parameters_ptr()->get_use_validation_data()){
		validation_data_error_provider.set_run(run,
											   mep_engine.get_validation_data_ptr()->get_num_rows(),
											   mep_engine.get_validation_data_ptr(),
											   mep_engine.get_parameters_ptr()->get_num_outputs(),
											   true);
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
			mep_engine.compute_output_on_validation(run, validation_data_error_provider.output_long_long,
												 validation_data_error_provider.valid_output);
		else
			mep_engine.compute_output_on_validation(run, validation_data_error_provider.output_double,
												 validation_data_error_provider.valid_output);
		g_error_validation->my_update();
	}

	test_data_error_provider.set_run(run,
									 mep_engine.get_test_data_ptr()->get_num_rows(),
									 mep_engine.get_test_data_ptr(),
									 mep_engine.get_parameters_ptr()->get_num_outputs(),
									 mep_engine.get_training_data_ptr()->get_num_cols() ==
									 mep_engine.get_test_data_ptr()->get_num_cols());
	if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
		mep_engine.compute_output_on_test(run, test_data_error_provider.output_long_long,
								   test_data_error_provider.valid_output);
	else
		mep_engine.compute_output_on_test(run,
									   test_data_error_provider.output_double,
								   test_data_error_provider.valid_output);
	g_error_testing->my_update();

	wxWindow::SetCursor(wxNullCursor);

	show_predictions_in_grid(run);
}
//---------------------------------------------------------------------
void t_main_window::show_predictions_in_grid(int run)
{
//	if (run == -1)
//		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);

	if (mep_engine.get_parameters_ptr()->get_time_series_mode() == MEP_TIME_SERIES_PREDICTION)
		prediction_data_provider.set_run(run,
										 mep_engine.get_parameters_ptr()->get_num_predictions(),
										 NULL, mep_engine.get_parameters_ptr()->get_num_outputs(), false);
	else
		prediction_data_provider.set_run(run, 0, NULL, 1, false);

	if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
		mep_engine.predict(run, prediction_data_provider.output_long_long,
						prediction_data_provider.valid_output);
	else
		mep_engine.predict(run, prediction_data_provider.output_double,
						prediction_data_provider.valid_output);

	g_predictions->my_update();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::show_program(int run_index)
{
	if (run_index == -1) {
		tc_source_code->Clear();
		return;
	}

	wxWindow::SetCursor(wxCURSOR_WAIT);

	// now program
	bool can_be_simplified =
		mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_MULTICLASS_CLASSIFICATION||
		(mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION &&
		mep_engine.get_parameters_ptr()->get_error_measure() == MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR);
	char* prg_as_mep = NULL;
	double** example_data_double = mep_engine.get_training_data_ptr()->get_data_matrix_as_double();
	long long** example_data_long = mep_engine.get_training_data_ptr()->get_data_matrix_as_long_long();
	/*
	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE){
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
			example_data_long = mep_engine.get_training_data_ptr()->get_data_matrix_long_long();
		else
			example_data_double = mep_engine.get_training_data_ptr()->get_data_matrix_double();
	}
	else {
		unsigned int window_size = mep_engine.get_parameters_ptr()->get_window_size();
		unsigned int num_rows = mep_engine.get_training_data_ptr()->get_num_rows();
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG){
			example_data_long = new long long[window_size];
			for (unsigned int i = 0; i < window_size; i++)
				example_data_long[i] = mep_engine.get_training_data_ptr()->get_data_matrix_long_long() [num_rows - window_size + i][0];
		}
		else{
			example_data_double = new double[window_size];
			for (unsigned int i = 0; i < window_size; i++)
				example_data_double[i] = mep_engine.get_training_data_ptr()->get_data_matrix_double() [num_rows - window_size + i][0];
		}
	}
	 */
	switch (cb_language->GetSelection()) {
		case MEP_CPP_CODE:// C++
			prg_as_mep = mep_engine.program_as_C(run_index,
				can_be_simplified ? cb_simplified_code->IsChecked(): false,
											  example_data_double,
											  example_data_long
											  );
			break;
		case MEP_VBA_CODE: // Excel
			prg_as_mep = mep_engine.program_as_Excel_function(run_index,
				can_be_simplified ? cb_simplified_code->IsChecked() : false);
			break;
		case MEP_PYTHON_CODE: // Python
			prg_as_mep = mep_engine.program_as_Python(run_index,
				can_be_simplified ? cb_simplified_code->IsChecked() : false,
												   example_data_double,
												   example_data_long
												   );
			break;
		case MEP_CPP_INFIX_CODE:// C++
			prg_as_mep = mep_engine.program_as_C_infix(run_index,
													example_data_double,
													example_data_long
													);
			break;
		case MEP_LATEX_CODE:
			prg_as_mep = mep_engine.program_as_Latex(run_index);
			break;
	}// end switch

	tc_source_code->SetValue(prg_as_mep);
	delete[] prg_as_mep;
	
	if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE){
		// delete only for time series, because they are the only one allocated here in this function
		// all others are taken from training data
		/*
		if (example_data_double)
			delete[] example_data_double;
		if (example_data_long)
			delete[] example_data_long;
		 */
	}
	
	wxWindow::SetCursor(wxNullCursor);
}
//-------------------------------------------------------------------------
void t_main_window::set_status_bar_info(int run, int current_generation)
{
	if (run == -1) {
		sb_status->SetStatusText("Training best error: ", STATUSBAR_BEST_TRAINING_ERROR_INDEX);
		//sb_status->SetStatusText("Training average error: ", STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
		sb_status->SetStatusText("Generation: ", STATUSBAR_GENERATION_INDEX);
		sb_status->SetStatusText("Validation error: ", STATUSBAR_BEST_VALIDATION_ERROR_INDEX);
		return;
	}
	double best_training_error = mep_engine.get_stats_ptr()->get_best_training_error(run, current_generation);
	//double average_training_error = mep_engine.get_stats_ptr()->get_average_training_error(run, current_generation);
	double best_training_num_incorrectly_classified = -1;
	double best_validation_num_incorrectly_classified = -1;

	if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION ||
		mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_BINARY_CLASSIFICATION)
		best_training_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_training_num_incorrectly_classified(run, current_generation);

	// status bar
	sb_status->SetStatusText("Generation: " + wxString() << current_generation, STATUSBAR_GENERATION_INDEX);

	// training

	switch (mep_engine.get_parameters_ptr()->get_problem_type()) {
	case MEP_PROBLEM_REGRESSION:
	case MEP_PROBLEM_TIME_SERIE:
		sb_status->SetStatusText("Training best error: " + wxString() << best_training_error, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
		//sb_status->SetStatusText("Training average error: " + wxString() << average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
		break;
	case MEP_PROBLEM_BINARY_CLASSIFICATION:
		sb_status->SetStatusText("Training " + best_num_incorrectly_classified_percent + ": " + wxString() << best_training_num_incorrectly_classified, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
		//sb_status->SetStatusText("Training " + average_num_incorrectly_classified_percent + ": " + wxString() << average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
		break;
	case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
		switch (mep_engine.get_parameters_ptr()->get_error_measure()) {
		case MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR:
		case MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR:
		case MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR:
			sb_status->SetStatusText("Training " + best_num_incorrectly_classified_percent + ": " + wxString() << best_training_num_incorrectly_classified, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
			//sb_status->SetStatusText("Training " + average_num_incorrectly_classified_percent + ": " + wxString() << average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
			break;
		case MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR:
			sb_status->SetStatusText(("Training best error: " + wxString() << best_training_error) + ("; " + best_num_incorrectly_classified_percent + ": " + wxString() << best_training_num_incorrectly_classified), STATUSBAR_BEST_TRAINING_ERROR_INDEX);
			//sb_status->SetStatusText("Training average error: " + wxString() << average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
			break;
		}
	}

	if (mep_engine.get_validation_data_ptr()->get_num_rows() &&
		mep_engine.get_parameters_ptr()->get_use_validation_data()) {
		double validation_error = -1;
		best_validation_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_validation_num_incorrectly_classified(run);
		validation_error = mep_engine.get_stats_ptr()->get_best_validation_error(run);

		switch (mep_engine.get_parameters_ptr()->get_problem_type()) {
		case MEP_PROBLEM_REGRESSION:
		case MEP_PROBLEM_TIME_SERIE:
			sb_status->SetStatusText("Validation error: " + wxString() << validation_error, STATUSBAR_BEST_VALIDATION_ERROR_INDEX);
			break;
		case MEP_PROBLEM_BINARY_CLASSIFICATION:
		case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
			sb_status->SetStatusText("Validation " + best_num_incorrectly_classified_percent + ": " + wxString() << best_validation_num_incorrectly_classified, STATUSBAR_BEST_VALIDATION_ERROR_INDEX);
			break;
		}
	}
}
//-------------------------------------------------------------------------
void t_main_window::set_run_stats(int run_index)
{
	set_status_bar_info(run_index, mep_engine.get_stats_ptr()->get_latest_generation(run_index));

	double best_training_error = mep_engine.get_stats_ptr()->get_best_training_error(run_index,
		mep_engine.get_stats_ptr()->get_latest_generation(run_index));

	double best_training_num_incorrectly_classified = -1;
	double best_validation_num_incorrectly_classified = -1;

	if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION ||
		mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_BINARY_CLASSIFICATION)
		best_training_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_training_num_incorrectly_classified(run_index,
			mep_engine.get_stats_ptr()->get_latest_generation(run_index));

	double validation_error = -1;
	if (mep_engine.get_validation_data_ptr()->get_num_rows() &&
		mep_engine.get_parameters_ptr()->get_use_validation_data()) {
		best_validation_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_validation_num_incorrectly_classified(run_index);
		validation_error = mep_engine.get_stats_ptr()->get_best_validation_error(run_index);
	}
	// statistics grid

	if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION ||
		mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_BINARY_CLASSIFICATION) {
		run_errors.data[run_index].training_error = best_training_num_incorrectly_classified;
		
		if (mep_engine.get_parameters_ptr()->get_use_validation_data() &&
			mep_engine.get_validation_data_ptr()->get_num_rows()){
			run_errors.data[run_index].validation_error = best_validation_num_incorrectly_classified;
		}
		else
			run_errors.data[run_index].validation_error = -1;
		
		if (mep_engine.get_test_data_ptr()->get_num_rows()&&
			mep_engine.get_test_data_ptr()->get_num_cols() ==
			mep_engine.get_training_data_ptr()->get_num_cols()
			) {
			double test_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_test_num_incorrectly_classified(run_index);
			run_errors.data[run_index].test_error = test_num_incorrectly_classified;
		}
		else
			run_errors.data[run_index].test_error = -1;
	}
	else {// regression or binary classification
		run_errors.data[run_index].training_error = best_training_error;
		
		if (mep_engine.get_parameters_ptr()->get_use_validation_data() &&
			mep_engine.get_validation_data_ptr()->get_num_rows()){
			run_errors.data[run_index].validation_error = validation_error;
		}
		else
			run_errors.data[run_index].validation_error = -1;
			
		if (mep_engine.get_test_data_ptr()->get_num_rows() &&
			mep_engine.get_test_data_ptr()->get_num_cols() == mep_engine.get_training_data_ptr()->get_num_cols()
			) {
			double test_error = mep_engine.get_stats_ptr()->get_test_error(run_index);
			run_errors.data[run_index].test_error = test_error;
		}
		else
			run_errors.data[run_index].test_error = -1;
	}

	run_errors.data[run_index].running_time = mep_engine.get_stats_ptr()->get_running_time(run_index);;
	run_errors.data[run_index].num_utilized_instructions = mep_engine.get_stats_ptr()->get_stat_ptr(run_index)->best_program.get_num_utilized_genes();
}
//-------------------------------------------------------------------------
void t_main_window::clear_results(void)
{
	//	tc_training_error->SetLabel("");
	//	tc_validation_error->SetLabel("");
	//	tc_generation->SetLabel("");

	sb_status->SetStatusText("Generation: ", STATUSBAR_GENERATION_INDEX);
	sb_status->SetStatusText("Best training error: ", STATUSBAR_BEST_TRAINING_ERROR_INDEX);
	//sb_status->SetStatusText("Average training error: ", STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
	sb_status->SetStatusText("Validation error: ", STATUSBAR_BEST_VALIDATION_ERROR_INDEX);

	tc_source_code->SetValue("");
	run_errors.clear();
	g_stats->update_num_rows(false);

	mep_engine.clear_stats();
	last_processed_generation = -1;
	last_processed_run = -1;

	training_data_error_provider.set_run(-1, 0, NULL, 1, true);
	g_error_training->my_update();

	validation_data_error_provider.set_run(-1, 0, NULL, 1, true);
	g_error_validation->my_update();

	test_data_error_provider.set_run(-1, 0, NULL, 1, true);
	g_error_testing->my_update();

	g_predictions->DeleteAllItems();

	p_chart_target_output->Refresh();
	p_chart_evolution->Refresh();

	update_results_buttons();
}
//-------------------------------------------------------------------------
void t_main_window::update_results(void)
{
	bool _is_running = mep_engine.is_running();
	int _last_run_index = mep_engine.get_last_run_index();

	if (!_is_running && _last_run_index > -1 &&
		last_processed_run == _last_run_index &&
		last_processed_generation == mep_engine.get_stats_ptr()->get_latest_generation(last_processed_run)) {
		t_timer->Stop();

		wxWindow::SetCursor(wxNullCursor);

		//st_project_name->SetForegroundColour(wxColour(0x0000FF));
		//st_project_name->Refresh();

		// now I have to fill the error tables
		if (last_processed_generation > -1 &&
			last_processed_generation <= (int)mep_engine.get_parameters_ptr()->get_num_generations() - 1) {
			int saved_last_processed_run = last_processed_run;
			int saved_last_processed_generation = last_processed_generation;
			run_errors.add_new_item();
			last_processed_run = saved_last_processed_run;
			last_processed_generation = saved_last_processed_generation;
			set_run_stats(last_processed_run);
			g_stats->update_num_rows(false);

		}
		show_errors_in_grids(last_processed_run);
		show_program(last_processed_run);
		//draw_evolution();
		p_chart_evolution->Refresh();
		p_chart_target_output->Refresh();
		update_results_buttons();

		if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_REGRESSION||
			mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE) {
			mep_engine.get_stats_ptr()->get_mean_error(run_errors.mean_training,
													run_errors.mean_validation,
													run_errors.mean_test,
													run_errors.mean_runtime,
													run_errors.mean_code_length);
			mep_engine.get_stats_ptr()->get_sttdev_error(run_errors.stddev_training,
													  run_errors.stddev_validation,
													  run_errors.stddev_test,
													  run_errors.stddev_runtime,
													  run_errors.stddev_code_length);
			mep_engine.get_stats_ptr()->get_best_error(run_errors.best_training,
													run_errors.best_validation,
													run_errors.best_test,
													run_errors.best_runtime,
													run_errors.best_code_length);
		}
		else {
			mep_engine.get_stats_ptr()->get_mean_num_incorrect(run_errors.mean_training,
															run_errors.mean_validation,
															run_errors.mean_test,
															run_errors.mean_runtime,
															run_errors.mean_code_length);
			mep_engine.get_stats_ptr()->get_sttdev_num_incorrect(run_errors.stddev_training,
															  run_errors.stddev_validation,
															  run_errors.stddev_test,
															  run_errors.stddev_runtime,
															  run_errors.stddev_code_length);
			mep_engine.get_stats_ptr()->get_best_num_incorrect(run_errors.best_training,
															run_errors.best_validation,
															run_errors.best_test,
															run_errors.best_runtime,
															run_errors.best_code_length);
		}

		if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION)
		{};
		//mep_engine.get_be
		
		g_stats->update_num_rows(true);
		g_stats->Select(last_processed_run, true);

		enable_when_stop();

		return;
	}

	if (!is_on_timer_running) {

		is_on_timer_running = true;
		int current_run = mep_engine.get_last_run_index();
		int current_generation = -1;
		if (current_run > -1)
			current_generation = mep_engine.get_stats_ptr()->get_latest_generation(current_run);

		if (current_run > last_processed_run) {
			last_processed_generation = -1;

			for (int r = last_processed_run == -1 ? 0 : last_processed_run; r < current_run; r++)
				if (mep_engine.get_stats_ptr()->get_latest_generation(r) == (int)mep_engine.get_parameters_ptr()->get_num_generations() - 1)// only if the run is completed
				{
					run_errors.add_new_item();
					set_run_stats(r);
				}
				g_stats->update_num_rows(false);
		}

		if (current_run > -1 && current_run >= last_processed_run) {
			if (current_generation > last_processed_generation) {

				wxClientDC dc(p_chart_evolution);
				for (int g = last_processed_generation + 1; g <= current_generation; g++)
					if (!g) {
						do_draw_first_generation(dc, current_run);
					}
					else {
						do_draw_next_generations(dc, current_run, g);
					}
				last_processed_generation = current_generation;

				set_status_bar_info(current_run, current_generation);

				/*
				//					double last_average_error = mep_engine.get_average_training_error(current_run, current_generation);
				double last_best_training_error = mep_engine.get_stats_ptr()->get_best_training_error(current_run, current_generation);
				double last_average_training_error = mep_engine.get_stats_ptr()->get_average_training_error(current_run, current_generation);
				double validation_error = mep_engine.get_stats_ptr()->get_best_validation_error(current_run);

				double last_best_training_num_incorrectly_classified = -1;
				if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_MULTICLASS_CLASSIFICATION ||
					mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_BINARY_CLASSIFICATION)
					last_best_training_num_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_training_num_incorrectly_classified(current_run, current_generation);

				sb_status->SetStatusText("Generation: " + wxString() << current_generation, STATUSBAR_GENERATION_INDEX);

				switch (mep_engine.get_parameters_ptr()->get_problem_type()) {
				case MEP_PROBLEM_REGRESSION:
				case MEP_PROBLEM_TIME_SERIE:
					sb_status->SetStatusText("Best training error: " + wxString() << last_best_training_error, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
					sb_status->SetStatusText("Average training error: " + wxString() << last_average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
					break;
				case MEP_PROBLEM_BINARY_CLASSIFICATION:
					sb_status->SetStatusText("Training " + best_num_incorrectly_classified_percent + ": " + wxString() << last_best_training_num_incorrectly_classified, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
					sb_status->SetStatusText("Training " + average_num_incorrectly_classified_percent + ": " + wxString() << last_average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
					break;
				case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
					switch (mep_engine.get_parameters_ptr()->get_error_measure()) {
					case MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR:
					case MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR:
					case MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR:
						sb_status->SetStatusText("Training " + best_num_incorrectly_classified_percent + ": " + wxString() << last_best_training_num_incorrectly_classified, STATUSBAR_BEST_TRAINING_ERROR_INDEX);
						sb_status->SetStatusText("Training " + average_num_incorrectly_classified_percent + ": " + wxString() << last_average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
						break;
					case MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR:
						sb_status->SetStatusText(("Training best error: " + wxString() << last_best_training_error) + ("; " + best_num_incorrectly_classified_percent + ": " + wxString() << last_best_training_num_incorrectly_classified), STATUSBAR_BEST_TRAINING_ERROR_INDEX);
						sb_status->SetStatusText("Training average error: " + wxString() << last_average_training_error, STATUSBAR_AVERAGE_TRAINING_ERROR_INDEX);
						break;
					}
				}


				if (mep_engine.get_validation_data_ptr()->get_num_rows() && mep_engine.get_parameters_ptr()->get_use_validation_data()) {
					double validation_error_incorrectly_classified = mep_engine.get_stats_ptr()->get_best_validation_num_incorrectly_classified(current_run);

					switch (mep_engine.get_parameters_ptr()->get_problem_type()) {
					case MEP_PROBLEM_REGRESSION:
					case MEP_PROBLEM_TIME_SERIE:
						sb_status->SetStatusText("Validation error: " + wxString() << validation_error, STATUSBAR_BEST_VALIDATION_ERROR_INDEX);
						break;
					case MEP_PROBLEM_BINARY_CLASSIFICATION:
					case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
						sb_status->SetStatusText("Validation " + best_num_incorrectly_classified_percent + ": " + wxString() << validation_error_incorrectly_classified, STATUSBAR_BEST_VALIDATION_ERROR_INDEX);
						break;
					}
				}
				*/
			}
			last_processed_run = current_run;
		}
		is_on_timer_running = false;
	}
}
//-------------------------------------------------------------------------
void t_main_window::on_code_language_changed(wxCommandEvent& event)
{
	on_simplified_code_clicked(event);
}
//-------------------------------------------------------------------------
void t_main_window::update_results_buttons(void)
{
	if (mep_engine.is_running()) {
		b_save_stats->Enable(false);
		//b_copy_stats->Enable(false);

		b_save_error_tables->Enable(false);
		//b_copy_error_table->Enable(false);
		cb_simplified_code->Enable(false);
		cb_language->Enable(false);
		b_save_code->Enable(false);
		b_to_clipboard_code->Enable(false);

		cb_target_for_chart->Enable(false);
		cb_chart_training_target_output->Enable(false);
		cb_chart_validation_target_output->Enable(false);
		cb_chart_testing_target_output->Enable(false);
		cb_chart_predictions_target_output->Enable(false);

		cb_chart_target->Enable(false);
		cb_chart_output->Enable(false);
		cb_chart_show_separator->Enable(false);
		cb_chart_show_lines->Enable(false);
	}
	else {
		if (mep_engine.get_stats_ptr()->num_runs > 0) {
			b_save_stats->Enable(true);
			//b_copy_stats->Enable(true);
		}
		else {
			b_save_stats->Enable(false);
			//b_copy_stats->Enable(false);
		}
		if (last_processed_run == -1) {
			b_save_error_tables->Enable(false);
			//b_copy_error_table->Enable(false);
			cb_simplified_code->Enable(false);
			cb_language->Enable(false);
			b_save_code->Enable(false);
			b_to_clipboard_code->Enable(false);

			cb_target_for_chart->Enable(false);
			cb_chart_training_target_output->Enable(false);
			cb_chart_validation_target_output->Enable(false);
			cb_chart_testing_target_output->Enable(false);
			cb_chart_predictions_target_output->Enable(false);

			cb_chart_target->Enable(false);
			cb_chart_output->Enable(false);
			cb_chart_show_separator->Enable(false);
			cb_chart_show_lines->Enable(false);
		}
		else {
			b_save_error_tables->Enable(true);
			//b_copy_error_table->Enable(true);
			cb_simplified_code->Enable(true);
			cb_language->Enable(true);
			b_save_code->Enable(true);
			b_to_clipboard_code->Enable(true);

			cb_chart_show_separator->Enable(true);
			cb_chart_show_lines->Enable(true);

			cb_target_for_chart->Enable(true);
			cb_chart_training_target_output->Enable(mep_engine.get_training_data_ptr()->get_num_rows());
			if (!cb_chart_training_target_output->IsEnabled())
				cb_chart_training_target_output->SetValue(false);

			cb_chart_validation_target_output->Enable(mep_engine.get_validation_data_ptr()->get_num_rows() &&
													  mep_engine.get_parameters_ptr()->get_use_validation_data() );
			if (!cb_chart_validation_target_output->IsEnabled())
				cb_chart_validation_target_output->SetValue(false);

			cb_chart_testing_target_output->Enable(mep_engine.get_test_data_ptr()->get_num_rows());
			if (!cb_chart_testing_target_output->IsEnabled())
				cb_chart_testing_target_output->SetValue(false);

			cb_chart_target->Enable(mep_engine.get_training_data_ptr()->get_num_rows() ||
									mep_engine.get_validation_data_ptr()->get_num_rows()||
									mep_engine.get_test_data_ptr()->get_num_rows());

			if (!cb_chart_target->IsEnabled())
				cb_chart_target->SetValue(false);

			cb_chart_output->Enable(mep_engine.get_training_data_ptr()->get_num_rows() ||
									mep_engine.get_validation_data_ptr()->get_num_rows() ||
									mep_engine.get_test_data_ptr()->get_num_rows());
			if (!cb_chart_output->IsEnabled())
				cb_chart_output->SetValue(false);

			if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE &&
				mep_engine.get_parameters_ptr()->get_time_series_mode() == MEP_TIME_SERIES_PREDICTION) {
				cb_chart_predictions_target_output->Enable(true);
			}
			else {
				cb_chart_predictions_target_output->Enable(false);
				cb_chart_predictions_target_output->SetValue(false);
			}
		}
	}
}
//-------------------------------------------------------------------------
void t_main_window::on_chart_target_output_clicked(wxCommandEvent&)
{
	p_chart_target_output->Refresh();
}
//-------------------------------------------------------------------------- -
void t_main_window::on_chart_evolution_clicked(wxCommandEvent&)
{
	p_chart_evolution->Refresh();
}
//-------------------------------------------------------------------------- -
void t_main_window::on_change_errors_notebook_page(wxBookCtrlEvent& event)
{
	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
		if (event.GetSelection() == PREDICTION_ERRORS_PAGE) {
			wxMessageBox("This page is for Time Series only", "Info");
			if (event.GetOldSelection() != wxNOT_FOUND)
				n_error_tables->SetSelection(event.GetOldSelection());
			else
				n_error_tables->SetSelection(TRAINING_ERRORS_PAGE);
		}
	}
}
//-------------------------------------------------------------------------- -
// 1143
// 1135
// 1078
// 1144
// 1241
