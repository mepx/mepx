// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//---------------------------------------------------------
void t_main_window::set_functions_to_UI(const t_mep_functions * mep_operators,
								  int data_type)
{
	cb_addition->SetValue(mep_operators->get_addition());
	
	cb_subtraction->SetValue(mep_operators->get_subtraction());
	
	cb_multiplication->SetValue(mep_operators->get_multiplication());
	
	cb_division->SetValue(mep_operators->get_division());
	
	cb_power->Enable(mep_operators->get_power_enabled(data_type));
	cb_power->SetValue(mep_operators->get_power());
	if (!mep_operators->get_power_enabled(data_type))
		cb_power->SetValue(0);
	
	cb_sqrt->Enable(mep_operators->get_sqrt_enabled(data_type));
	cb_sqrt->SetValue(mep_operators->get_sqrt());
	if (!mep_operators->get_sqrt_enabled(data_type))
		cb_sqrt->SetValue(0);
	
	cb_exp->Enable(mep_operators->get_exp_enabled(data_type));
	cb_exp->SetValue(mep_operators->get_exp());
	if (!mep_operators->get_exp_enabled(data_type))
		cb_exp->SetValue(0);
	
	cb_pow10->Enable(mep_operators->get_pow10_enabled(data_type));
	cb_pow10->SetValue(mep_operators->get_pow10());
	if (!mep_operators->get_pow10_enabled(data_type))
		cb_pow10->SetValue(0);
	
	cb_ln->Enable(mep_operators->get_ln_enabled(data_type));
	cb_ln->SetValue(mep_operators->get_ln());
	if (!mep_operators->get_ln_enabled(data_type))
		cb_ln->SetValue(0);
	
	cb_log10->Enable(mep_operators->get_log10_enabled(data_type));
	cb_log10->SetValue(mep_operators->get_log10());
	if (!mep_operators->get_log10_enabled(data_type))
		cb_log10->SetValue(0);
	
	cb_log2->Enable(mep_operators->get_log2_enabled(data_type));
	cb_log2->SetValue(mep_operators->get_log2());
	if (!mep_operators->get_log2_enabled(data_type))
		cb_log2->SetValue(0);
	
	cb_floor->Enable(mep_operators->get_floor_enabled(data_type));
	cb_floor->SetValue(mep_operators->get_floor());
	if (!mep_operators->get_floor_enabled(data_type))
		cb_floor->SetValue(0);
	
	cb_ceil->Enable(mep_operators->get_ceil_enabled(data_type));
	cb_ceil->SetValue(mep_operators->get_ceil());
	if (!mep_operators->get_ceil_enabled(data_type))
		cb_ceil->SetValue(0);
	
	cb_abs->Enable(mep_operators->get_abs_enabled(data_type));
	cb_abs->SetValue(mep_operators->get_abs());
	if (!mep_operators->get_abs_enabled(data_type))
		cb_abs->SetValue(0);
	
	cb_inv->Enable(mep_operators->get_inv_enabled(data_type));
	cb_inv->SetValue(mep_operators->get_inv());
	if (!mep_operators->get_inv_enabled(data_type))
		cb_inv->SetValue(0);
	
	cb_neg->SetValue(mep_operators->get_neg());
	
	cb_x2->SetValue(mep_operators->get_x2());
	
	cb_min->SetValue(mep_operators->get_min());
	cb_max->SetValue(mep_operators->get_max());
	
	cb_sin->Enable(mep_operators->get_sin_enabled(data_type));
	cb_sin->SetValue(mep_operators->get_sin());
	if (!mep_operators->get_sin_enabled(data_type))
		cb_sin->SetValue(0);
	
	cb_cos->Enable(mep_operators->get_cos_enabled(data_type));
	cb_cos->SetValue(mep_operators->get_cos());
	if (!mep_operators->get_cos_enabled(data_type))
		cb_cos->SetValue(0);
	
	cb_tan->Enable(mep_operators->get_tan_enabled(data_type));
	cb_tan->SetValue(mep_operators->get_tan());
	if (!mep_operators->get_tan_enabled(data_type))
		cb_tan->SetValue(0);
	
	cb_asin->Enable(mep_operators->get_asin_enabled(data_type));
	cb_asin->SetValue(mep_operators->get_asin());
	if (!mep_operators->get_asin_enabled(data_type))
		cb_asin->SetValue(0);
	
	cb_acos->Enable(mep_operators->get_acos_enabled(data_type));
	cb_acos->SetValue(mep_operators->get_acos());
	if (!mep_operators->get_acos_enabled(data_type))
		cb_acos->SetValue(0);
	
	cb_atan->Enable(mep_operators->get_atan_enabled(data_type));
	cb_atan->SetValue(mep_operators->get_atan());
	if (!mep_operators->get_atan_enabled(data_type))
		cb_atan->SetValue(0);
	
	cb_iflz->SetValue(mep_operators->get_iflz());
	
	cb_ifalbcd->SetValue(mep_operators->get_ifalbcd());
	
	cb_if_a_or_b_cd->SetValue(mep_operators->get_if_a_or_b_cd());
	
	cb_if_a_xor_b_cd->SetValue(mep_operators->get_if_a_xor_b_cd());

	cb_fmod->SetValue(mep_operators->get_mod());

	//cb_min_gen->SetValue(mep_operators->get_min_gen());
	//cb_max_gen->SetValue(mep_operators->get_max_gen());

	//    cb_inputs_average->SetValue(mep_operators->get_inputs_average());
	//    cb_num_inputs->SetValue(mep_operators->get_num_inputs());
}
//---------------------------------------------------------
void t_main_window::set_enabled_functions_to_UI(
									const t_mep_functions * mep_operators,
								  int data_type)
{
	cb_power->Enable(mep_operators->get_power_enabled(data_type));
	if (!mep_operators->get_power_enabled(data_type))
		cb_power->SetValue(0);
	
	cb_sqrt->Enable(mep_operators->get_sqrt_enabled(data_type));
	if (!mep_operators->get_sqrt_enabled(data_type))
		cb_sqrt->SetValue(0);
	
	cb_exp->Enable(mep_operators->get_exp_enabled(data_type));
	if (!mep_operators->get_exp_enabled(data_type))
		cb_exp->SetValue(0);
	
	cb_pow10->Enable(mep_operators->get_pow10_enabled(data_type));
	if (!mep_operators->get_pow10_enabled(data_type))
		cb_pow10->SetValue(0);
	
	cb_ln->Enable(mep_operators->get_ln_enabled(data_type));
	if (!mep_operators->get_ln_enabled(data_type))
		cb_ln->SetValue(0);
	
	cb_log10->Enable(mep_operators->get_log10_enabled(data_type));
	if (!mep_operators->get_log10_enabled(data_type))
		cb_log10->SetValue(0);
	
	cb_log2->Enable(mep_operators->get_log2_enabled(data_type));
	if (!mep_operators->get_log2_enabled(data_type))
		cb_log2->SetValue(0);
	
	cb_floor->Enable(mep_operators->get_floor_enabled(data_type));
	if (!mep_operators->get_floor_enabled(data_type))
		cb_floor->SetValue(0);
	
	cb_ceil->Enable(mep_operators->get_ceil_enabled(data_type));
	if (!mep_operators->get_ceil_enabled(data_type))
		cb_ceil->SetValue(0);
	
	cb_inv->Enable(mep_operators->get_inv_enabled(data_type));
	if (!mep_operators->get_inv_enabled(data_type))
		cb_inv->SetValue(0);
	
	cb_sin->Enable(mep_operators->get_sin_enabled(data_type));
	if (!mep_operators->get_sin_enabled(data_type))
		cb_sin->SetValue(0);
	
	cb_cos->Enable(mep_operators->get_cos_enabled(data_type));
	if (!mep_operators->get_cos_enabled(data_type))
		cb_cos->SetValue(0);
	
	cb_tan->Enable(mep_operators->get_tan_enabled(data_type));
	if (!mep_operators->get_tan_enabled(data_type))
		cb_tan->SetValue(0);
	
	cb_asin->Enable(mep_operators->get_asin_enabled(data_type));
	if (!mep_operators->get_asin_enabled(data_type))
		cb_asin->SetValue(0);
	
	cb_acos->Enable(mep_operators->get_acos_enabled(data_type));
	if (!mep_operators->get_acos_enabled(data_type))
		cb_acos->SetValue(0);
	
	cb_atan->Enable(mep_operators->get_atan_enabled(data_type));
	if (!mep_operators->get_atan_enabled(data_type))
		cb_atan->SetValue(0);
	
//    cb_inputs_average->SetValue(mep_operators->get_inputs_average());
//    cb_num_inputs->SetValue(mep_operators->get_num_inputs());
}
//---------------------------------------------------------
void t_main_window::set_enable_constants(double constants_probability,
										 const t_mep_constants* mep_constants)
{
	if (constants_probability > 1E-6) {
		rb_constants_type->Enable(true);

		if (mep_constants->get_constants_type() == MEP_CONSTANTS_USER_DEFINED) {
			sc_num_constants->Enable(false);
			tc_min_interval_constants->Enable(false);
			tc_max_interval_constants->Enable(false);
			cb_evolve_constants->Enable(false);
			cb_evolve_constants_outside_initial_interval->Enable(false);
			tc_stddev->Enable(false);

			b_delete_constant->Enable(true);
			b_add_constant->Enable(true);
			lv_constants->Enable(true);
		}
		else {// automatic constants
			b_delete_constant->Enable(false);
			b_add_constant->Enable(false);
			lv_constants->Enable(false);

			sc_num_constants->Enable(true);
			tc_min_interval_constants->Enable(true);
			tc_max_interval_constants->Enable(true);
			cb_evolve_constants->Enable(true);
			tc_stddev->Enable(true);
			cb_evolve_constants_outside_initial_interval->Enable(true);
		}
	}
	else {
		sc_num_constants->Enable(false);
		tc_min_interval_constants->Enable(false);
		tc_max_interval_constants->Enable(false);
		rb_constants_type->Enable(false);
		cb_evolve_constants->Enable(false);
		tc_stddev->Enable(false);
		lv_constants->Enable(false);
		b_delete_constant->Enable(false);
		b_add_constant->Enable(false);
		cb_evolve_constants_outside_initial_interval->Enable(false);
	}
}
//------------------------------------------------------------------------------
void t_main_window::set_constants_to_UI(double constants_probability,
										const t_mep_constants* mep_constants,
										char data_type)
{
	sc_num_constants->ChangeValue(wxString() << mep_constants->get_num_automatic_constants());

	if (data_type == MEP_DATA_DOUBLE){
		tc_min_interval_constants->ChangeValue(wxString() << mep_constants->get_min_constants_interval_double());
		tc_max_interval_constants->ChangeValue(wxString() << mep_constants->get_max_constants_interval_double());
		tc_stddev->ChangeValue(wxString() << mep_constants->get_constants_mutation_max_deviation_double());
		
		lv_constants->Clear();

		for (unsigned int i = 0; i < mep_constants->get_num_user_defined_constants(); i++)
			lv_constants->AppendString(wxString() << mep_constants->get_constants_double(i));
	}
	else{
		if (data_type == MEP_DATA_LONG_LONG){
			tc_min_interval_constants->ChangeValue(wxString() << mep_constants->get_min_constants_interval_long_long());
			tc_max_interval_constants->ChangeValue(wxString() << mep_constants->get_max_constants_interval_long_long());
			tc_stddev->ChangeValue(wxString() << mep_constants->get_constants_mutation_max_deviation_long_long());
			
			lv_constants->Clear();

			for (unsigned int i = 0; i < mep_constants->get_num_user_defined_constants(); i++)
				lv_constants->AppendString(wxString() << mep_constants->get_constants_long_long(i));
		}
	}
	
	rb_constants_type->SetSelection(mep_constants->get_constants_type());
	cb_evolve_constants->SetValue(mep_constants->get_constants_can_evolve());

	if (!cb_evolve_constants->IsChecked()) {
		cb_evolve_constants_outside_initial_interval->Enable(false);
		cb_evolve_constants_outside_initial_interval->SetValue(false);
	}
	else {
		cb_evolve_constants_outside_initial_interval->SetValue(mep_constants->get_constants_can_evolve_outside_initial_interval());
	}

	set_enable_constants(constants_probability, mep_constants);
}
//---------------------------------------------------------

void t_main_window::set_parameters_to_UI(const t_mep_parameters *mep_parameters)
{
	sc_code_length->ChangeValue(wxString() << mep_parameters->get_code_length());
	sc_num_demes->ChangeValue(wxString() << mep_parameters->get_num_subpopulations());
	sc_deme_size->ChangeValue(wxString() << mep_parameters->get_subpopulation_size());
	sc_num_generations->ChangeValue(wxString() << mep_parameters->get_num_generations());
	tc_mutation_prob->ChangeValue(wxString() << mep_parameters->get_mutation_probability());
	tc_crossover_prob->ChangeValue(wxString() << mep_parameters->get_crossover_probability());
	rb_crossover_type->SetSelection(mep_parameters->get_crossover_type());

	rb_time_series_mode->SetSelection(mep_parameters->get_time_series_mode());

	rb_problem_type->SetSelection(mep_parameters->get_problem_type());
	if (mep_parameters->get_data_type() == MEP_DATA_LONG_LONG)
		rb_data_type->SetSelection(1);
	else
		rb_data_type->SetSelection(0); // it is not long, so it should be double
	
	if (mep_parameters->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
		tc_window_size->Enable(false);
		rb_time_series_mode->Enable(false);
		tc_num_predictions->Enable(false);
	}
	else {// time series
		tc_window_size->Enable(true);
		rb_time_series_mode->Enable(true);
		tc_num_predictions->Enable(mep_parameters->get_time_series_mode() == MEP_TIME_SERIES_PREDICTION);

		if (mep_parameters->get_time_series_mode() == MEP_TIME_SERIES_PREDICTION) {
			cb_chart_predictions_target_output->Enable(true);
		}
		else {
			cb_chart_predictions_target_output->Enable(false);
			cb_chart_predictions_target_output->SetValue(false);
		}
	}

	sc_random_seed->ChangeValue(wxString() << mep_parameters->get_random_seed());
	sc_num_runs->ChangeValue(wxString() << mep_parameters->get_num_runs());
	tc_num_cores->ChangeValue(wxString() << mep_parameters->get_num_threads());

	tc_operators_probability->ChangeValue(wxString() << mep_parameters->get_operators_probability());
	tc_variables_probability->ChangeValue(wxString() << mep_parameters->get_variables_probability());
	tc_constants_probability->ChangeValue(wxString() << mep_parameters->get_constants_probability());

	sc_tournament_size->ChangeValue(wxString() << mep_parameters->get_tournament_size());

	cb_use_validation_set->SetValue(mep_parameters->get_use_validation_data());
	cb_simplified_code->SetValue(mep_parameters->get_simplified_programs());

	tc_subset_size->ChangeValue(wxString() << mep_parameters->get_random_subset_selection_size_percent());

	tc_num_generations_for_which_random_subset_is_kept_fixed->ChangeValue(wxString() << mep_parameters->get_num_generations_for_which_random_subset_is_kept_fixed());

	rb_error_measure->SetSelection(mep_parameters->get_error_measure());

	tc_num_predictions->ChangeValue(wxString() << mep_parameters->get_num_predictions());
	tc_window_size->ChangeValue(wxString() << mep_parameters->get_window_size());

	switch (mep_parameters->get_problem_type()) {
	case MEP_PROBLEM_REGRESSION:
	case MEP_PROBLEM_TIME_SERIE:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 1);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 1);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 0);
		if (rb_error_measure->GetSelection() > MEP_REGRESSION_MEAN_SQUARED_ERROR)
			rb_error_measure->SetSelection(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR);
		break;
	case MEP_PROBLEM_BINARY_CLASSIFICATION:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 0);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 0);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 0);

		if (rb_error_measure->GetSelection() != MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD)
			rb_error_measure->SetSelection(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD);
		break;
	case MEP_PROBLEM_MULTICLASS_CLASSIFICATION:
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 0);
		rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 0);
		rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 0);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 1);
		rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 1);

		if (rb_error_measure->GetSelection() <= MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD)
			rb_error_measure->SetSelection(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR);
		break;
	}
}
//---------------------------------------------------------
void t_main_window::set_interface_layout(const t_mepx_interface_layout *p)
{
	splitter_stats_evolution->SetSashPosition(p->stats_table_height);
	splitter_runs_results->SetSashPosition(p->stats_table_width);
	splitter_charts_code->SetSashPosition(p->errors_table_width);
	splitter_code_graphics->SetSashPosition(p->code_box_height);
}
//-----------------------------------------------------------
void t_main_window::set_target_output_chart_options(const t_mepx_target_output_chart_options& p)
{
	cb_chart_training_target_output->SetValue(p.cb_chart_training_target_output);
	cb_chart_validation_target_output->SetValue(p.cb_chart_validation_target_output);
	cb_chart_testing_target_output->SetValue(p.cb_chart_testing_target_output);
	cb_chart_predictions_target_output->SetValue(p.cb_chart_predictions_target_output);
	cb_chart_target->SetValue(p.cb_chart_target);
	cb_chart_output->SetValue(p.cb_chart_output);
	cb_chart_show_lines->SetValue(p.cb_chart_show_lines);
	cb_chart_show_separator->SetValue(p.cb_chart_show_separator);
}
//-----------------------------------------------------------
void t_main_window::set_evolution_chart_options(const t_mepx_evolution_chart_options& p)
{
	cb_pop_average_evolution->SetValue(p.cb_pop_average_evolution);
	cb_validation_evolution->SetValue(p.cb_validation_evolution);
}
//-----------------------------------------------------------
void t_main_window::set_enabled_grid_columns(void)
{
	if (mep_engine.get_training_data_ptr()->get_num_cols() == 0)
		return;
	
	unsigned int num_variables = mep_engine.get_training_data_ptr()->get_num_cols() -
								mep_engine.get_parameters_ptr()->get_num_outputs();
	
	for (unsigned int c = 0; c < num_variables; c++) {
		wxListItem col;
		col.SetMask(wxLIST_MASK_TEXT);
		g_training_data->GetColumn(c + 1, col);
		if (mep_engine.is_variable_enabled(c))
			col.SetText("+x" + wxString::Format("%d", c));
		else
			col.SetText("-x" + wxString::Format("%d", c));
	}
}
//-----------------------------------------------------------
// 421
// 500
