// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
//-----------------------------------------------------------------------------------------
#include "mepx_project.h"
#include "utils/validation_string.h"
//-----------------------------------------------------------------------------------------
void t_main_window::on_selection_operators_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//-------------------------------------------------------------------------
void t_main_window::on_operator_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_evolve_constants_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();
	if (!cb_evolve_constants->IsChecked()) {
		cb_evolve_constants_outside_initial_interval->Enable(false);
		cb_evolve_constants_outside_initial_interval->SetValue(false);
	}
	else {
		cb_evolve_constants_outside_initial_interval->Enable(true);
	}

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_change_value_spin_ctrl(wxSpinEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_change_param_value(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_change_num_predictions_value(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------

void t_main_window::do_problem_type_changed(void)
{
	// error measurement
	switch (rb_problem_type->GetSelection()) {
	case MEP_PROBLEM_REGRESSION:
	case MEP_PROBLEM_TIME_SERIE:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 1);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 1);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR, 0);

		if (rb_error_measure->GetSelection() > MEP_REGRESSION_MEAN_SQUARED_ERROR)
			rb_error_measure->SetSelection(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR);
		st_runs_errors->SetLabel(s_runs_errors_label_regression);
		break;
	case MEP_PROBLEM_BINARY_CLASSIFICATION:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 0);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 0);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR, 0);

		if (rb_error_measure->GetSelection() != MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD)
			rb_error_measure->SetSelection(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD);
		st_runs_errors->SetLabel(s_runs_errors_label_classification);
		
		break;
	case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 0);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 0);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR, 1);

		if (rb_error_measure->GetSelection() <= MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD)
			rb_error_measure->SetSelection(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR);

		st_runs_errors->SetLabel(s_runs_errors_label_classification);
		
		break;
	}

	//change time series mode
	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
		tc_num_predictions->Enable(false);
		tc_window_size->Enable(false);
		rb_time_series_mode->Enable(false);
	}
	else {// time series
		tc_window_size->Enable(true);
		rb_time_series_mode->Enable(true);
		tc_num_predictions->Enable(mep_engine.get_parameters_ptr()->get_time_series_mode() == MEP_TIME_SERIES_PREDICTION);
		//g_training_data->num_outputs = mep_engine.
	}
	
	update_num_target_cols_to_data_grids();
	
	sizer_toolbar_stats->Layout();
	//b_save_stats->Layout();
	p_runs->Layout();
}
//---------------------------------------------------------------------
void t_main_window::on_problem_type_change_rb_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();
	//mep_engine.init_enabled_variables();
	
	mep_engine.get_parameters_ptr()->set_problem_type(rb_problem_type->GetSelection());
	
	if (rb_problem_type->GetSelection() == MEP_PROBLEM_TIME_SERIE)
		mep_engine.get_parameters_ptr()->set_num_outputs(mep_engine.get_training_data_ptr()->get_num_cols());
	else
		mep_engine.get_parameters_ptr()->set_num_outputs(1);

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	do_problem_type_changed();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::do_data_type_changed(void)
{
	if (rb_data_type->GetSelection() == 1)
		mep_engine.get_parameters_ptr()->set_data_type(MEP_DATA_LONG_LONG);
	else
		mep_engine.get_parameters_ptr()->set_data_type(MEP_DATA_DOUBLE);
	
	set_enabled_functions_to_UI(mep_engine.get_functions_ptr(), mep_engine.get_parameters_ptr()->get_data_type());
}
//---------------------------------------------------------------------
void t_main_window::on_change_data_type_rb_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();
	//mep_engine.init_enabled_variables();
	
	mep_engine.get_parameters_ptr()->set_data_type((char)rb_data_type->GetSelection());

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	do_data_type_changed();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_error_measure_change_rb_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_constants_type_change(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	mep_engine.get_constants_ptr()->set_constants_type(rb_constants_type->GetSelection());

	set_enable_constants(mep_engine.get_parameters_ptr()->get_constants_probability(), mep_engine.get_constants_ptr());

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_use_constants_clicked(wxCommandEvent&)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	mep_engine.get_constants_ptr()->set_constants_type(rb_constants_type->GetSelection());

	set_constants_to_UI(mep_engine.get_parameters_ptr()->get_constants_probability(),
						mep_engine.get_constants_ptr(),
						mep_engine.get_parameters_ptr()->get_data_type());

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_add_constant_button_clicked(wxCommandEvent&)
{
	wxString text = wxGetTextFromUser("input value", "input", "", this);
	if (text != "") {
		double d_value;
		if (!is_valid_double(text.utf8_str(), &d_value)) {
			wxMessageBox("Invalid number", "error");
			return;
		}

		lv_constants->AppendAndEnsureVisible(text);

		wxWindow::SetCursor(wxCURSOR_WAIT);

		clear_results();

		b_save_project->Enable(true);
		//st_project_name->SetForegroundColour(wxColour(0x0000FF));
		//st_project_name->Refresh();

		wxWindow::SetCursor(wxNullCursor);
	}
}
//---------------------------------------------------------------------
void t_main_window::on_delete_constant_button_clicked(wxCommandEvent&)
{
	if (lv_constants->GetSelection() != wxNOT_FOUND) {
		lv_constants->Delete(lv_constants->GetSelection());

		wxWindow::SetCursor(wxCURSOR_WAIT);

		clear_results();

		b_save_project->Enable(true);
		//st_project_name->SetForegroundColour(wxColour(0x0000FF));
		//st_project_name->Refresh();

		wxWindow::SetCursor(wxNullCursor);
	}
}
//---------------------------------------------------------------------
void t_main_window::on_change_selected_constants(wxCommandEvent&)
{
	if (lv_constants->GetSelection() != wxNOT_FOUND)
		b_delete_constant->Enable(true);
	else
		b_delete_constant->Enable(false);

}
//---------------------------------------------------------------------
void t_main_window::on_operators_probabilities_change(wxFocusEvent& event)
{
	wxString s_operators_probability = tc_operators_probability->GetValue().Trim();
	wxString s_variables_probability = tc_variables_probability->GetValue().Trim();

	if (s_operators_probability == "") {
		tc_operators_probability->SetValue("0");
		s_operators_probability = "0";
	}

	if (s_variables_probability == "") {
		tc_variables_probability->SetValue("0");
		s_variables_probability = "0";
	}

	double d_operators_probability;
	if (!is_valid_double(s_operators_probability.utf8_str(), &d_operators_probability)) {
		wxMessageBox("Invalid number", "error");
		tc_operators_probability->SetFocus();
		event.Skip();
		return;
	}

	if (d_operators_probability < 0 || d_operators_probability > 1) {
		wxMessageBox("Invalid number", "error");
		tc_operators_probability->SetFocus();
		event.Skip();
		return;
	}

	double d_variables_probability;
	if (!is_valid_double(s_variables_probability.utf8_str(), &d_variables_probability)) {
		wxMessageBox("Number must be between 0 and 1", "error");
		tc_variables_probability->SetFocus();
		event.Skip();
		return;
	}

	if (d_variables_probability < 0 || d_variables_probability > 1) {
		wxMessageBox("Number must be between 0 and 1", "error");
		tc_variables_probability->SetFocus();
		event.Skip();
		return;
	}

	if (d_variables_probability + d_operators_probability > 1) {
		wxMessageBox("Operators proabilities + Variables probabilities must be less or equal to 1", "error");
		event.Skip();
		return;
	}

	tc_constants_probability->SetValue(wxString() << (1 - d_variables_probability - d_operators_probability));
	mep_engine.get_parameters_ptr()->set_constants_probability(1 - d_variables_probability - d_operators_probability);

	set_enable_constants(1 - d_variables_probability - d_operators_probability, mep_engine.get_constants_ptr());

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	event.Skip();
}
//---------------------------------------------------------------------
void t_main_window::on_time_series_mode_change_rb_clicked(wxCommandEvent& )
{
	tc_num_predictions->Enable(rb_time_series_mode->GetSelection() == MEP_TIME_SERIES_PREDICTION);
	// update this here because I need it in the next window
	if (rb_time_series_mode->GetSelection() == MEP_TIME_SERIES_PREDICTION) {
		mep_engine.get_parameters_ptr()->set_time_series_mode(MEP_TIME_SERIES_PREDICTION);
		cb_chart_predictions_target_output->Enable(true);
	}
	else {
		mep_engine.get_parameters_ptr()->set_time_series_mode(MEP_TIME_SERIES_TEST);
		cb_chart_predictions_target_output->Enable(false);
		cb_chart_predictions_target_output->SetValue(false);
		mepx_settings.target_output_chart_options.cb_chart_predictions_target_output = false;
	}
	
	int run = -1;
	long selected = g_stats->GetFirstSelected();
	if (selected != -1 && selected <= mep_engine.get_last_run_index())
		run = (int)selected;

	show_predictions_in_grid(run);
	test_data_error_provider.set_run(run,
									 mep_engine.get_test_data_ptr()->get_num_rows(),
									 mep_engine.get_test_data_ptr(),
									 mep_engine.get_parameters_ptr()->get_num_outputs(),
									 mep_engine.get_test_data_ptr()->get_num_cols() ==
									 mep_engine.get_training_data_ptr()->get_num_cols());
	
	if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG)
		mep_engine.compute_output_on_test(run, test_data_error_provider.output_long_long,
									   test_data_error_provider.valid_output);
	else
		mep_engine.compute_output_on_test(run, test_data_error_provider.output_double,
									   test_data_error_provider.valid_output);

	g_error_testing->my_update();

	b_save_project->Enable(true);
}
//---------------------------------------------------------------------
