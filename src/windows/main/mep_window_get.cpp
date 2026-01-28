// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//---------------------------------------------------------
void t_main_window::get_functions_from_UI(t_mep_functions* mep_operators)
{
	mep_operators->set_addition( cb_addition->IsChecked() && cb_addition->IsEnabled());
	mep_operators->set_subtraction(cb_subtraction->IsChecked() && cb_subtraction->IsEnabled());
	mep_operators->set_division(cb_division->IsChecked() && cb_division->IsEnabled());
	mep_operators->set_multiplication(cb_multiplication->IsChecked() && cb_multiplication->IsEnabled());
	mep_operators->set_power(cb_power->IsChecked() && cb_power->IsEnabled());
	mep_operators->set_sqrt(cb_sqrt->IsChecked() && cb_sqrt->IsEnabled());
	mep_operators->set_exp(cb_exp->IsChecked() && cb_exp->IsEnabled());
	mep_operators->set_pow10(cb_pow10->IsChecked() && cb_pow10->IsEnabled());
	mep_operators->set_ln(cb_ln->IsChecked() && cb_ln->IsEnabled());
	mep_operators->set_log10(cb_log10->IsChecked() && cb_log10->IsEnabled());
	mep_operators->set_log2(cb_log2->IsChecked() && cb_log2->IsEnabled());
	mep_operators->set_floor(cb_floor->IsChecked() && cb_floor->IsEnabled());
	mep_operators->set_ceil(cb_ceil->IsChecked() && cb_ceil->IsEnabled());
	mep_operators->set_abs(cb_abs->IsChecked() && cb_abs->IsEnabled());
	mep_operators->set_inv(cb_inv->IsChecked() && cb_inv->IsEnabled());
	mep_operators->set_neg(cb_neg->IsChecked() && cb_neg->IsEnabled());
	mep_operators->set_x2(cb_x2->IsChecked() && cb_x2->IsEnabled());
	mep_operators->set_min(cb_min->IsChecked() && cb_min->IsEnabled());
	mep_operators->set_max(cb_max->IsChecked() && cb_max->IsEnabled());

	mep_operators->set_sin(cb_sin->IsChecked());
	mep_operators->set_cos(cb_cos->IsChecked());
	mep_operators->set_tan(cb_tan->IsChecked());

	mep_operators->set_asin(cb_asin->IsChecked());
	mep_operators->set_acos(cb_acos->IsChecked());
	mep_operators->set_atan(cb_atan->IsChecked());

	mep_operators->set_iflz(cb_iflz->IsChecked());
	mep_operators->set_ifalbcd(cb_ifalbcd->IsChecked());
	mep_operators->set_if_a_or_b_cd(cb_if_a_or_b_cd->IsChecked());
	mep_operators->set_if_a_xor_b_cd(cb_if_a_xor_b_cd->IsChecked());
	mep_operators->set_mod(cb_fmod->IsChecked());
	//mep_operators->set_min_gen(cb_min_gen->IsChecked() && cb_min_gen->IsEnabled());
	//mep_operators->set_max_gen(cb_max_gen->IsChecked() && cb_max_gen->IsEnabled());
}
//---------------------------------------------------------
bool t_main_window::get_constants_from_UI(t_mep_constants* mep_constants,
										  char *error_message,
										  char data_type)
{
	long value_l;
	long long value_ll;
	double value_d;
	
	mep_constants->init();

	if (!sc_num_constants->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Num. constants : Invalid number!");
		sc_num_constants->SetFocus();
		return false;
	}
	else {
		if (value_l < 0) {
			strcpy(error_message, "Num. constants : Value must be greater or equal to 0");
			sc_num_constants->SetFocus();
			return false;
		}
		else
			mep_constants->set_num_automatic_constants((int)value_l);
	}
	
	long num_user_defined_constants = lv_constants->GetCount();
	mep_constants->set_num_user_defined_constants((int)num_user_defined_constants);

	if (data_type == MEP_DATA_DOUBLE){
		if (!tc_min_interval_constants->GetValue().Trim().ToDouble(&value_d)) {
			strcpy(error_message, "Min. interval constants : Invalid number!");
			tc_min_interval_constants->SetFocus();
			return false;
		}
		else
			mep_constants->set_min_constants_interval_double(value_d);

		if (!tc_max_interval_constants->GetValue().Trim().ToDouble(&value_d)) {
			strcpy(error_message, "Max. interval constants : Invalid number!");
			tc_max_interval_constants->SetFocus();
			return false;
		}
		else
			mep_constants->set_max_constants_interval_double(value_d);
		
		if (!tc_stddev->GetValue().Trim().ToDouble(&value_d)) {
			strcpy(error_message, "Constants: Max. delta : Invalid number!");
			tc_stddev->SetFocus();
			return false;
		}
		else {
			if (value_d <= 0) {
				strcpy(error_message, "Constants: Max. delta : Value must be greater than 0!");
				tc_stddev->SetFocus();
				return false;
			}
			else
				mep_constants->set_constants_mutation_max_deviation_double(value_d);
		}
		
		// get the constants
		for (int i = 0; i < num_user_defined_constants; i++){
			if (!lv_constants->GetString(i).Trim().ToDouble(&value_d)) {
				strcpy(error_message, "User defined constant: Invalid number!");
				lv_constants->SetFocus();
				return false;
			}
			else
				mep_constants->set_constants_double(i, value_d);
		}
	}
	else
		if (data_type == MEP_DATA_LONG_LONG){
			if (!tc_min_interval_constants->GetValue().Trim().ToLongLong(&value_ll)) {
				strcpy(error_message, "Min. interval constants : Invalid integer number!");
				tc_min_interval_constants->SetFocus();
				return false;
			}
			else
				mep_constants->set_min_constants_interval_long_long(value_ll);

			if (!tc_max_interval_constants->GetValue().Trim().ToLongLong(&value_ll)) {
				strcpy(error_message, "Max. interval constants : Invalid integer number!");
				tc_max_interval_constants->SetFocus();
				return false;
			}
			else
				mep_constants->set_max_constants_interval_long_long(value_ll);
			
			if (!tc_stddev->GetValue().Trim().ToLongLong(&value_ll)) {
				strcpy(error_message, "Constants: Max. delta : Invalid integer number!");
				tc_stddev->SetFocus();
				return false;
			}
			else {
				if (value_ll <= 0) {
					strcpy(error_message, "Constants: Max. delta : Value must be greater than 0!");
					tc_stddev->SetFocus();
					return false;
				}
				else
					mep_constants->set_constants_mutation_max_deviation_long_long(value_ll);
			}
			
			// get the constants
			for (int i = 0; i < num_user_defined_constants; i++){
				if (!lv_constants->GetString(i).Trim().ToLongLong(&value_ll)) {
					strcpy(error_message, "User defined constant: Invalid integer number!");
					lv_constants->SetFocus();
					return false;
				}
				else
					mep_constants->set_constants_long_long(i, value_ll);
			}
		}

	mep_constants->set_constants_type(rb_constants_type->GetSelection());
	mep_constants->set_constants_can_evolve(cb_evolve_constants->IsChecked());
	if (!cb_evolve_constants->IsChecked()) {
		mep_constants->set_constants_can_evolve_outside_initial_interval(false);
	}
	else {
		mep_constants->set_constants_can_evolve_outside_initial_interval(cb_evolve_constants_outside_initial_interval->IsChecked());
	}
	
	mep_constants->set_data_type_no_update(data_type);

	return true;
}
//---------------------------------------------------------
bool t_main_window::get_parameters_from_UI(t_mep_parameters *mep_parameters, char *error_message)
{
	long value_l;
	double value_d;

	if (!sc_code_length->GetValue().ToLong(&value_l)) {
		strcpy(error_message, "Code length : Invalid number!");
		sc_code_length->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Code length : Value must be greater than 0");
			sc_code_length->SetFocus();
			return false;
		}
		mep_parameters->set_code_length((int)value_l);
	}

	if (!sc_num_demes->GetValue().ToLong(&value_l)) {
		strcpy(error_message, "Num. subpopulations : Invalid number!");
		sc_num_demes->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Num. subpopulations : Value must be greater than 0");
			sc_num_demes->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_subpopulations((int)value_l);
	}

	if (!sc_deme_size->GetValue().ToLong(&value_l)) {
		strcpy(error_message, "Subpopulation size : Invalid number!");
		sc_deme_size->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Subpopulation size : Value must be greater than 0");
			sc_deme_size->SetFocus();
			return false;
		}
		else
			mep_parameters->set_subpopulation_size((int)value_l);
	}

	if (!sc_num_generations->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Num. generations: Invalid number!");
		sc_num_generations->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Num. generations : Value must be greater than 0");
			sc_num_generations->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_generations((int)value_l);
	}

	if (rb_data_type->GetSelection() == 1)
		mep_parameters->set_data_type(MEP_DATA_LONG_LONG);
	else
		mep_parameters->set_data_type(MEP_DATA_DOUBLE);
	
	mep_parameters->set_problem_type(rb_problem_type->GetSelection());
	mep_parameters->set_error_measure(rb_error_measure->GetSelection());
	mep_parameters->set_crossover_type(rb_crossover_type->GetSelection());

	if (!sc_random_seed->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Random seed : Invalid number!");
		sc_random_seed->SetFocus();
		return false;
	}
	else
		mep_parameters->set_random_seed((int)value_l);

	if (!sc_num_runs->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Num. runs: Invalid number!");
		sc_num_runs->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Num. runs : Value must be greater than 0.");
			sc_num_runs->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_runs((int)value_l);
	}

	if (!tc_num_cores->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Num. threads: Invalid number!");
		tc_num_cores->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Num. threads : Value must be greater than 0.");
			tc_num_cores->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_threads((int)value_l);
	}

	if (!sc_tournament_size->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Tournament size: Invalid number!");
		sc_tournament_size->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Tournament size : Value must be greater than 0.");
			sc_tournament_size->SetFocus();
			return false;
		}
		else
			mep_parameters->set_tournament_size((int)value_l);
	}

	if (!tc_mutation_prob->GetValue().Trim().ToDouble(&value_d)) {
		strcpy(error_message, "Mutation probability : Invalid number!");
		tc_mutation_prob->SetFocus();
		return false;
	}
	else {
		if (value_d < 0 || value_d > 1) {
			strcpy(error_message, "Mutation probability : Value must be between 0 and 1.");
			tc_mutation_prob->SetFocus();
			return false;
		}
		else
			mep_parameters->set_mutation_probability(value_d);
	}

	if (!tc_crossover_prob->GetValue().Trim().ToDouble(&value_d)) {
		strcpy(error_message, "Crossover probability : Invalid number!");
		tc_crossover_prob->SetFocus();
		return false;
	}
	else {
		if (value_d < 0 || value_d > 1) {
			strcpy(error_message, "Crossover probability : Value must be between 0 and 1.");
			tc_crossover_prob->SetFocus();
			return false;
		}
		else
			mep_parameters->set_crossover_probability(value_d);
	}

	if (!tc_operators_probability->GetValue().Trim().ToDouble(&value_d)) {
		strcpy(error_message, "Operators probability : Invalid number!");
		tc_operators_probability->SetFocus();
		return false;
	}
	else {
		if (value_d < 0 || value_d > 1) {
			strcpy(error_message, "Operators probability : Value must be between 0 and 1.");
			tc_operators_probability->SetFocus();
			return false;
		}
		else
			mep_parameters->set_operators_probability(value_d);
	}

	if (!tc_variables_probability->GetValue().Trim().ToDouble(&value_d)) {
		strcpy(error_message, "Variables probability : Invalid number!");
		tc_variables_probability->SetFocus();
		return false;
	}
	else {
		if (value_d < 0 || value_d > 1) {
			strcpy(error_message, "Variables probability : Value must be between 0 and 1.");
			tc_variables_probability->SetFocus();
			return false;
		}
		else
			mep_parameters->set_variables_probability(value_d);
	}


	if (!tc_subset_size->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Random subset size: Invalid number!");
		tc_subset_size->SetFocus();
		return false;
	}
	else {
		if (value_l < 1 || value_l > 100) {
			strcpy(error_message, "Random subset size : Value must be greater than 0 and less or equal to 100.");
			tc_subset_size->SetFocus();
			return false;
		}
		else
			mep_parameters->set_random_subset_selection_size_percent((int)value_l);
	}

	if (!tc_num_generations_for_which_random_subset_is_kept_fixed->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Num. generations for which random subset is kept fixed: Invalid number!");
		tc_num_generations_for_which_random_subset_is_kept_fixed->SetFocus();
		return false;
	}
	else {
		if (value_l < 1) {
			strcpy(error_message, "Num. generations for which random subset is kept fixed : Value must be greater than 1.");
			tc_num_generations_for_which_random_subset_is_kept_fixed->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_generations_for_which_random_subset_is_kept_fixed((int)value_l);
	}

	if (rb_time_series_mode->GetSelection() == MEP_TIME_SERIES_PREDICTION)
		mep_parameters->set_time_series_mode(MEP_TIME_SERIES_PREDICTION);
	else
		mep_parameters->set_time_series_mode(MEP_TIME_SERIES_TEST);
	
	if (!tc_num_predictions->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Time series: Num. predictions: Invalid number!");
		tc_num_predictions->SetFocus();
		return false;
	}
	else {
		if (value_l < 0) {
			strcpy(error_message, "Time series: Num. predictions : Value must be greater than 0.");
			tc_num_predictions->SetFocus();
			return false;
		}
		else
			mep_parameters->set_num_predictions((int)value_l);
	}

	if (!tc_window_size->GetValue().Trim().ToLong(&value_l)) {
		strcpy(error_message, "Time series: Window size: Invalid number!");
		tc_window_size->SetFocus();
		return false;
	}
	else {
		if (value_l < 0) {
			strcpy(error_message, "Time series: Window size : Value must be greater than 0.");
			tc_window_size->SetFocus();
			return false;
		}
		else
			mep_parameters->set_window_size((int)value_l);
	}

	mep_parameters->set_constants_probability(1 - mep_parameters->get_operators_probability() - mep_parameters->get_variables_probability());
	
	mep_parameters->set_simplified_programs(cb_simplified_code->IsChecked());

	mep_parameters->set_use_validation_data(cb_use_validation_set->IsChecked());

	return true;
}
//---------------------------------------------------------
void t_main_window::get_interface_layout(t_mepx_interface_layout *p)
{
	p->stats_table_height = splitter_stats_evolution->GetSashPosition();
	p->stats_table_width = splitter_runs_results->GetSashPosition();
	p->errors_table_width = splitter_charts_code->GetSashPosition();
	p->code_box_height = splitter_code_graphics->GetSashPosition();
}
//-----------------------------------------------------------
void t_main_window::get_target_output_chart_options(t_mepx_target_output_chart_options& p)
{
	p.cb_chart_training_target_output = cb_chart_training_target_output->IsChecked();
	p.cb_chart_validation_target_output = cb_chart_validation_target_output->IsChecked();
	p.cb_chart_testing_target_output = cb_chart_testing_target_output->IsChecked();
	p.cb_chart_predictions_target_output = cb_chart_predictions_target_output->IsChecked();
	p.cb_chart_target = cb_chart_target->IsChecked();
	p.cb_chart_output = cb_chart_output->IsChecked();
	p.cb_chart_show_lines = cb_chart_show_lines->IsChecked();
	p.cb_chart_show_separator = cb_chart_show_separator->IsChecked();
}
//-----------------------------------------------------------
void t_main_window::get_evolution_chart_options(t_mepx_evolution_chart_options& p)
{
	p.cb_pop_average_evolution = cb_pop_average_evolution->IsChecked();
	p.cb_validation_evolution = cb_validation_evolution->IsChecked();
}
//-----------------------------------------------------------
void t_main_window::get_enabled_grid_columns(void)
{
	if (mep_engine.get_training_data_ptr()->get_num_cols() == 0)
		return;
	
	unsigned int num_variables = mep_engine.get_training_data_ptr()->get_num_cols() -
							mep_engine.get_parameters_ptr()->get_num_outputs();
	
	for (unsigned int c = 0; c < num_variables; c++) {
		wxListItem col;
		col.SetMask(wxLIST_MASK_TEXT);
		g_training_data->GetColumn(c + 1, col);
		wxString text = col.GetText();
		if (!text.IsEmpty() && text[0] == '-')
			mep_engine.set_variable_enable(c, false);
		else
			mep_engine.set_variable_enable(c, true);
	}
}
//-----------------------------------------------------------
