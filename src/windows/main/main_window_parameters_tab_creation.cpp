// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
//-------------------------------------------------------------------------
void t_main_window::create_params_ui(void)
{
	///////////////////////////////////////////
	//parameters
	///////////////////////////////////////////

	w_parameters = new wxWindow(n_settings, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	//data type
	wxString data_type_choices[2] = { "Real numbers", "Integer numbers"};
	rb_data_type = new wxRadioBox(w_parameters, -1, "Data type", wxDefaultPosition, wxDefaultSize, 2, data_type_choices, 1, wxRA_SPECIFY_COLS);

	rb_data_type->Bind(wxEVT_RADIOBOX, &t_main_window::on_change_data_type_rb_clicked, this);
	
	// problem

	wxString problem_type_choices[4] = { "Symbolic regression", "Binary classification", "Multi-class classification", "Time-series"};
	rb_problem_type = new wxRadioBox(w_parameters, -1, "Problem type", wxDefaultPosition, wxDefaultSize, 4, problem_type_choices, 1, wxRA_SPECIFY_COLS);

	rb_problem_type->Bind(wxEVT_RADIOBOX, &t_main_window::on_problem_type_change_rb_clicked, this);

	wxString error_measure_choices[7] = { "Mean Absolute Error", "Mean Squared Error", "Automatic threshold", "Winner takes all-Fixed", "Winner takes all-Smooth", "Winner takes all-Dynamic", "Closest center"};
	rb_error_measure = new wxRadioBox(w_parameters, -1, "Error measure", wxDefaultPosition, wxDefaultSize, 7, error_measure_choices, 1, wxRA_SPECIFY_COLS);
	rb_error_measure->Bind(wxEVT_RADIOBOX, &t_main_window::on_error_measure_change_rb_clicked, this);

	rb_error_measure->Enable(MEP_REGRESSION_MEAN_ABSOLUTE_ERROR, 1);
	rb_error_measure->Enable(MEP_REGRESSION_MEAN_SQUARED_ERROR, 1);
	rb_error_measure->Enable(MEP_BINARY_CLASSIFICATION_AUTOMATIC_THRESHOLD, 0);
	rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_ERROR, 0);
	rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_SMOOTH_ERROR, 0);
	rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_WINNER_TAKES_ALL_DYNAMIC_ERROR, 0);
	rb_error_measure->Enable(MEP_MULTICLASS_CLASSIFICATION_CLOSEST_CENTER_ERROR, 0);

	wxStaticBoxSizer* sbs_time_serie = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Time series");

	st_window_size = new wxStaticText(sbs_time_serie->GetStaticBox(), -1, "Window size");;
	tc_window_size = new wxTextCtrl(sbs_time_serie->GetStaticBox(), -1, "10");
	tc_window_size->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	wxString time_series_mode_choices[2] = { "Predict on Test set", "Predict new data"};
	rb_time_series_mode = new wxRadioBox(sbs_time_serie->GetStaticBox(), -1, "Mode", wxDefaultPosition, wxDefaultSize, 2, time_series_mode_choices, 1, wxRA_SPECIFY_COLS);
	rb_time_series_mode->Bind(wxEVT_RADIOBOX, &t_main_window::on_time_series_mode_change_rb_clicked, this);
	rb_time_series_mode->SetToolTip("Test means that prediction is made on the Test set. Predict means that future values are generated.");

	st_num_predictions = new wxStaticText(sbs_time_serie->GetStaticBox(), -1, "Num. predictions");;
	tc_num_predictions = new wxTextCtrl(sbs_time_serie->GetStaticBox(), -1, "10");
	tc_num_predictions->Bind(wxEVT_TEXT, &t_main_window::on_change_num_predictions_value, this);
	tc_num_predictions->SetToolTip("Number of predictions for a time serie");

	sbs_time_serie->Add(st_window_size, 0, wxTOP, 5);
	sbs_time_serie->Add(tc_window_size, 0, wxEXPAND, 5);
	sbs_time_serie->Add(rb_time_series_mode, 0, wxTOP, 5);
	sbs_time_serie->Add(st_num_predictions, 0, wxTOP, 5);
	sbs_time_serie->Add(tc_num_predictions, 0, wxBOTTOM|wxEXPAND, 5);

	// mathematical operators (functions)
	wxStaticBoxSizer* sbs_operators = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Functions");

	cb_addition = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Addition");
	cb_addition->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_subtraction = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Subtraction");
	cb_subtraction->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_multiplication = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Multiplication");
	cb_multiplication->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_division = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Division");
	cb_division->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_power = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Power");
	cb_power->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_sqrt = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Sqrt");
	cb_sqrt->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_exp = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Exp");
	cb_exp->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_pow10 = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Pow10");
	cb_pow10->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_ln = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Ln");
	cb_ln->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_log10 = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Log10");
	cb_log10->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_log2 = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Log2");
	cb_log2->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_floor = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Floor");
	cb_floor->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_ceil = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Ceil");
	cb_ceil->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_abs = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Abs");
	cb_abs->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_inv = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Inv (1/x)");
	cb_inv->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_neg = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Neg (-x)");
	cb_neg->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_x2 = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "X^2");
	cb_x2->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_min = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Min");
	cb_min->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_max = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Max");
	cb_max->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_sin = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Sin");
	cb_sin->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_cos = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Cos");
	cb_cos->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_tan = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Tan");
	cb_tan->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_asin = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "ASin");
	cb_asin->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_acos = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "ACos");
	cb_acos->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_atan = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "ATan");
	cb_atan->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_iflz = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "If a<0?b:c");
	cb_iflz->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_ifalbcd = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "If a<b?c:d");
	cb_ifalbcd->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_if_a_or_b_cd = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "If a<0 or b<0 ? c:d");
	cb_if_a_or_b_cd->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_if_a_xor_b_cd = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "If a<0 xor b<0 ? c:d");
	cb_if_a_xor_b_cd->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_fmod = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Modulus");
	cb_fmod->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);
	/*
	cb_min_gen = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Min Generalized");
	cb_min_gen->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_max_gen = new wxCheckBox(sbs_operators->GetStaticBox(), -1, "Max Generalized");
	cb_max_gen->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);
	*/

	/*
	cb_inputs_average = new wxCheckBox(w_parameters, -1, "Inputs average");
	cb_inputs_average->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);

	cb_num_inputs = new wxCheckBox(w_parameters, -1, "Num. inputs");
	cb_num_inputs->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);
	*/

	sbs_operators->Add(cb_addition, 0, 0, 0);
	sbs_operators->Add(cb_subtraction, 0, 0, 0);
	sbs_operators->Add(cb_multiplication, 0, 0, 0);
	sbs_operators->Add(cb_division, 0, 0, 0);
	sbs_operators->Add(cb_power, 0, 0, 0);
	sbs_operators->Add(cb_sqrt, 0, 0, 0);
	sbs_operators->Add(cb_exp, 0, 0, 0);
	sbs_operators->Add(cb_pow10, 0, 0, 0);
	sbs_operators->Add(cb_ln, 0, 0, 0);
	sbs_operators->Add(cb_log10, 0, 0, 0);
	sbs_operators->Add(cb_log2, 0, 0, 0);
	sbs_operators->Add(cb_floor, 0, 0, 0);
	sbs_operators->Add(cb_ceil, 0, 0, 0);
	sbs_operators->Add(cb_abs, 0, 0, 0);
	sbs_operators->Add(cb_inv, 0, 0, 0);
	sbs_operators->Add(cb_neg, 0, 0, 0);
	sbs_operators->Add(cb_x2, 0, 0, 0);
	sbs_operators->Add(cb_min, 0, 0, 0);
	sbs_operators->Add(cb_max, 0, 0, 0);

	sbs_operators->Add(cb_sin, 0, 0, 0);
	sbs_operators->Add(cb_cos, 0, 0, 0);
	sbs_operators->Add(cb_tan, 0, 0, 0);

	sbs_operators->Add(cb_asin, 0, 0, 0);
	sbs_operators->Add(cb_acos, 0, 0, 0);
	sbs_operators->Add(cb_atan, 0, 0, 0);

	sbs_operators->Add(cb_iflz, 0, 0, 0);
	sbs_operators->Add(cb_ifalbcd, 0, 0, 0);
	sbs_operators->Add(cb_if_a_or_b_cd, 0, 0, 0);
	sbs_operators->Add(cb_if_a_xor_b_cd, 0, 0, 0);
	sbs_operators->Add(cb_fmod, 0, wxBOTTOM, 5);
	//sbs_operators->Add(cb_min_gen, 0, wxBOTTOM, 5);
	//sbs_operators->Add(cb_max_gen, 0, wxBOTTOM, 5);

	//   sbs_operators->Add(cb_inputs_average, 0, 0, 0);
	// 	sbs_operators->Add(cb_num_inputs, 0, 0, 0);
	
	wxStaticBoxSizer* sbs_parameters = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Parameters");

	st_num_demes = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Num. subpopulations");
	sc_num_demes = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "1");
	sc_num_demes->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	st_deme_size = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Subpopulation size");
	sc_deme_size = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "100");
	sc_deme_size->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	st_code_length = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Code length");
	sc_code_length = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "10");
	sc_code_length->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	st_crossover_prob = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Crossover probability [0..1]");
	tc_crossover_prob = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "0.9");
	tc_crossover_prob->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	wxString crossover_type_choices[2] = { "Uniform", "One-cutting point" };
	rb_crossover_type = new wxRadioBox(sbs_parameters->GetStaticBox(), -1, "Crossover type",
		wxDefaultPosition, wxDefaultSize, 2, crossover_type_choices, 1, wxRA_SPECIFY_COLS);
	rb_crossover_type->Bind(wxEVT_RADIOBOX, &t_main_window::on_selection_operators_clicked, this);

	st_mutation_prob = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Mutation probability [0..1]");
	tc_mutation_prob = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "0.1");
	tc_mutation_prob->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	st_tournament_size = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Tournament size");
	sc_tournament_size = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "2");
	sc_tournament_size->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	wxStaticBoxSizer* bs_probabilities = new wxStaticBoxSizer(wxVERTICAL,
															  sbs_parameters->GetStaticBox(),
															  "Probabilities");

	st_operators_probability = new wxStaticText(bs_probabilities->GetStaticBox(), -1, "Functions");
	tc_operators_probability = new wxTextCtrl(bs_probabilities->GetStaticBox(), -1, "0.9");
	tc_operators_probability->Bind(wxEVT_KILL_FOCUS, &t_main_window::on_operators_probabilities_change, this);
	tc_operators_probability->SetToolTip("Sum of Functions, Variables and Constants probabilities must be 1.");

	st_variables_probability = new wxStaticText(bs_probabilities->GetStaticBox(), -1, "Variables");
	tc_variables_probability = new wxTextCtrl(bs_probabilities->GetStaticBox(), -1, "0.9");
	tc_variables_probability->Bind(wxEVT_KILL_FOCUS, &t_main_window::on_operators_probabilities_change, this);
	tc_variables_probability->SetToolTip("Sum of Functions, Variables and Constants probabilities must be 1.");

	st_constants_probability = new wxStaticText(bs_probabilities->GetStaticBox(), -1, "Constants");
	tc_constants_probability = new wxTextCtrl(bs_probabilities->GetStaticBox(), -1, "0.9");
	tc_constants_probability->SetEditable(false);
	tc_constants_probability->SetToolTip("Sum of Functions, Variables and Constants probabilities must be 1.");

	bs_probabilities->Add(st_operators_probability, 0, wxTOP, 3);
	bs_probabilities->Add(tc_operators_probability, 0, wxEXPAND, 0);
	bs_probabilities->Add(st_variables_probability, 0, wxTOP, 3);
	bs_probabilities->Add(tc_variables_probability, 0, wxEXPAND, 0);
	bs_probabilities->Add(st_constants_probability, 0, wxTOP, 3);
	bs_probabilities->Add(tc_constants_probability, 0, wxEXPAND, 0);

	st_num_generations = new wxStaticText(sbs_parameters->GetStaticBox(), -1, "Num. generations");
	sc_num_generations = new wxTextCtrl(sbs_parameters->GetStaticBox(), -1, "100");
	sc_num_generations->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	sbs_parameters->Add(st_num_demes, 0, wxTOP, 3);
	sbs_parameters->Add(sc_num_demes, 0, wxEXPAND, 0);
	sbs_parameters->Add(st_deme_size, 0, wxTOP, 3);
	sbs_parameters->Add(sc_deme_size, 0, wxEXPAND, 0);
	sbs_parameters->Add(st_code_length, 0, wxTOP, 3);
	sbs_parameters->Add(sc_code_length, 0, wxEXPAND, 0);
	sbs_parameters->Add(st_crossover_prob, 0, wxTOP, 3);
	sbs_parameters->Add(tc_crossover_prob, 0, wxEXPAND, 0);
	sbs_parameters->Add(rb_crossover_type, 0, wxTOP, 3);

	sbs_parameters->Add(st_mutation_prob, 0, wxTOP, 3);
	sbs_parameters->Add(tc_mutation_prob, 0, wxEXPAND, 0);

	sbs_parameters->Add(st_tournament_size, 0, wxTOP, 3);
	sbs_parameters->Add(sc_tournament_size, 0, wxEXPAND, 0);

	sbs_parameters->Add(bs_probabilities, 0, wxTOP, 3);

	sbs_parameters->Add(st_num_generations, 0, wxTOP, 3);
	sbs_parameters->Add(sc_num_generations, 0, wxBOTTOM|wxEXPAND, 5);

	// constants
	wxStaticBoxSizer* sbs_constants = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Constants");

	//cb_use_constants = new wxCheckBox(w_parameters, -1, "Use constants");
	//cb_use_constants->Bind(wxEVT_CHECKBOX, &t_main_window::on_use_constants_clicked, this);

	wxString constants_type_choices[2] = { "User defined", "Automatically generated" };
	rb_constants_type = new wxRadioBox(sbs_constants->GetStaticBox(), -1, "Type", wxDefaultPosition, wxDefaultSize,
		2, constants_type_choices, 1, wxRA_SPECIFY_COLS);
	rb_constants_type->Bind(wxEVT_RADIOBOX, &t_main_window::on_constants_type_change, this);

	// user defined
	wxStaticBoxSizer* sbs_user_defined_constants = new wxStaticBoxSizer(wxHORIZONTAL,
																		sbs_constants->GetStaticBox(),
																		"User defined constants");
	lv_constants = new wxListBox(sbs_user_defined_constants->GetStaticBox(), -1, wxDefaultPosition, wxSize(100, 200));
	lv_constants->Bind(wxEVT_LISTBOX, &t_main_window::on_change_selected_constants, this);
	b_add_constant = new wxButton(sbs_user_defined_constants->GetStaticBox(), -1, "Add");
	b_add_constant->Bind(wxEVT_BUTTON, &t_main_window::on_add_constant_button_clicked, this);
	b_delete_constant = new wxButton(sbs_user_defined_constants->GetStaticBox(), -1, "Delete");
	b_delete_constant->Enable(false);
	b_delete_constant->Bind(wxEVT_BUTTON, &t_main_window::on_delete_constant_button_clicked, this);

	wxBoxSizer* bs_operations_user_defined_constants = new wxBoxSizer(wxVERTICAL);
	bs_operations_user_defined_constants->Add(b_add_constant, 0, 0, 0);
	bs_operations_user_defined_constants->Add(b_delete_constant, 0, wxTOP, 5);

	sbs_user_defined_constants->Add(lv_constants, 0, wxEXPAND | wxALL, 5);
	sbs_user_defined_constants->Add(bs_operations_user_defined_constants, 0, wxALL, 5);

	// automatic
	wxStaticBoxSizer* sbs_automatically_constants = new wxStaticBoxSizer(wxVERTICAL,
																		 sbs_constants->GetStaticBox(),
																		 "Automatically generated constants");

	st_num_constants = new wxStaticText(sbs_automatically_constants->GetStaticBox(), -1, "Number of constants");
	sc_num_constants = new wxTextCtrl(sbs_automatically_constants->GetStaticBox(), -1, "1");
	sc_num_constants->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);

	st_min_interval_constants = new wxStaticText(sbs_automatically_constants->GetStaticBox(), -1, "Min initial interval");
	tc_min_interval_constants = new wxTextCtrl(sbs_automatically_constants->GetStaticBox(), -1, "-10");
	tc_min_interval_constants->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_min_interval_constants->SetToolTip("Min value a constant can have initially");

	st_max_interval_constants = new wxStaticText(sbs_automatically_constants->GetStaticBox(), -1, "Max initial interval");
	tc_max_interval_constants = new wxTextCtrl(sbs_automatically_constants->GetStaticBox(), -1, "10");
	tc_max_interval_constants->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_max_interval_constants->SetToolTip("Max value a constant can have initially");

	cb_evolve_constants = new wxCheckBox(sbs_automatically_constants->GetStaticBox(), -1, "May evolve");
	cb_evolve_constants->Bind(wxEVT_CHECKBOX, &t_main_window::on_evolve_constants_clicked, this);
	cb_evolve_constants->SetToolTip("Constants may evolve (can be modified) during training");

	cb_evolve_constants_outside_initial_interval = new wxCheckBox(sbs_automatically_constants->GetStaticBox(), -1, "Evolve outside initial interval");
	cb_evolve_constants_outside_initial_interval->Bind(wxEVT_CHECKBOX, &t_main_window::on_operator_clicked, this);
	cb_evolve_constants_outside_initial_interval->SetToolTip("Constants may have values outside initial interval");

	st_stddev = new wxStaticText(sbs_automatically_constants->GetStaticBox(), -1, "Max delta");
	tc_stddev = new wxTextCtrl(sbs_automatically_constants->GetStaticBox(), -1, "1");
	tc_stddev->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_stddev->SetToolTip("Maximum value that is added or subtracted to/from a constant during evolution");
	
	sbs_automatically_constants->Add(st_num_constants, 0, wxTOP, 5);
	sbs_automatically_constants->Add(sc_num_constants, 0, wxEXPAND, 0);

	sbs_automatically_constants->Add(st_min_interval_constants, 0, wxTOP, 5);
	sbs_automatically_constants->Add(tc_min_interval_constants, 0, wxEXPAND, 0);

	sbs_automatically_constants->Add(st_max_interval_constants, 0, wxTOP, 5);
	sbs_automatically_constants->Add(tc_max_interval_constants, 0, wxEXPAND, 0);

	sbs_automatically_constants->Add(cb_evolve_constants, 0, wxTOP, 5);
	sbs_automatically_constants->Add(cb_evolve_constants_outside_initial_interval, 0, wxTOP, 5);
	sbs_automatically_constants->Add(st_stddev, 0, wxTOP, 5);
	sbs_automatically_constants->Add(tc_stddev, 0, wxBOTTOM|wxEXPAND, 5);

	//sbs_constants->Add(cb_use_constants, 0, 0, 0);
	sbs_constants->Add(rb_constants_type, 0, wxTOP, 10);

	sbs_constants->Add(sbs_user_defined_constants, 0, wxTOP | wxEXPAND, 5);
	sbs_constants->Add(sbs_automatically_constants, 0, wxTOP, 5);
	
	// runs
	wxStaticBoxSizer* sbs_runs = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Runs");

	st_random_seed = new wxStaticText(sbs_runs->GetStaticBox(), -1, "Random seed");
	sc_random_seed = new wxTextCtrl(sbs_runs->GetStaticBox(), -1, "0");
	sc_random_seed->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	sc_random_seed->SetToolTip("The seed of the random number generator");

	st_num_runs = new wxStaticText(sbs_runs->GetStaticBox(), -1, "Num. runs");
	sc_num_runs = new wxTextCtrl(sbs_runs->GetStaticBox(), -1, "10");
	sc_num_runs->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	sc_num_runs->SetToolTip("How many runs are performed");

	st_num_cores = new wxStaticText(sbs_runs->GetStaticBox(), -1, "Num. threads");
	tc_num_cores = new wxTextCtrl(sbs_runs->GetStaticBox(), -1, "1");
	tc_num_cores->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_num_cores->SetToolTip("On how many threads the training is done.");

	sbs_runs->Add(st_random_seed, 0, wxTOP, 5);
	sbs_runs->Add(sc_random_seed, 0, wxEXPAND, 0);
	sbs_runs->Add(st_num_runs, 0, wxTOP, 5);
	sbs_runs->Add(sc_num_runs, 0, wxEXPAND, 0);
	sbs_runs->Add(st_num_cores, 0, wxTOP, 5);
	sbs_runs->Add(tc_num_cores, 0, wxBOTTOM|wxEXPAND, 5);

	wxStaticBoxSizer* sbs_training_subset = new wxStaticBoxSizer(wxVERTICAL, w_parameters, "Training subset");
	tc_subset_size = new wxTextCtrl(sbs_training_subset->GetStaticBox(), -1, "100");
	st_subset_size = new wxStaticText(sbs_training_subset->GetStaticBox(), -1, "Random subset size (%)");
	tc_subset_size->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_subset_size->SetToolTip("The size (%) of the training subset on which the algoritm is trained on [1..100].");

	tc_num_generations_for_which_random_subset_is_kept_fixed = new wxTextCtrl(sbs_training_subset->GetStaticBox(), -1, "1");
	st_num_generations_for_which_random_subset_is_kept_fixed = new wxStaticText(sbs_training_subset->GetStaticBox(), -1, "Num. generations for a subset");
	tc_num_generations_for_which_random_subset_is_kept_fixed->Bind(wxEVT_TEXT, &t_main_window::on_change_param_value, this);
	tc_num_generations_for_which_random_subset_is_kept_fixed->SetToolTip("After this number of generations, another random subset is selected for training.");

	sbs_training_subset->Add(st_subset_size, 0, wxTOP, 5);
	sbs_training_subset->Add(tc_subset_size, 0, wxEXPAND, 0);
	sbs_training_subset->Add(st_num_generations_for_which_random_subset_is_kept_fixed, 0, wxTOP, 5);
	sbs_training_subset->Add(tc_num_generations_for_which_random_subset_is_kept_fixed, 0, wxEXPAND|wxBOTTOM, 5);

	wxBoxSizer* bs_problem_and_time_serie = new wxBoxSizer(wxVERTICAL);
	//bs_problem_and_time_serie->Add(sbs_problem, 0, wxLEFT | wxTOP, 5);
	
	bs_problem_and_time_serie->Add(rb_data_type, 0, 0, 0);
	bs_problem_and_time_serie->Add(rb_problem_type, 0, wxTOP, 5);
	bs_problem_and_time_serie->Add(rb_error_measure, 0, wxTOP, 5);
	bs_problem_and_time_serie->Add(sbs_time_serie, 0, wxLEFT | wxTOP|wxEXPAND, 5);
	
	cb_use_validation_set = new wxCheckBox(w_parameters, -1, "Use validation data");
	cb_use_validation_set->Bind(wxEVT_CHECKBOX, &t_main_window::on_change_param_value, this);
	cb_use_validation_set->SetToolTip("Data from the validation set are used for selecting the best solution.");

	wxBoxSizer* bs_runs_and_data = new wxBoxSizer(wxVERTICAL);
	//bs_problem_and_time_serie->Add(sbs_problem, 0, wxLEFT | wxTOP, 5);
	bs_runs_and_data->Add(sbs_runs, 0, 0, 0);
	bs_runs_and_data->Add(sbs_training_subset, 0, wxTOP, 5);
	bs_runs_and_data->Add(cb_use_validation_set, 0, wxTOP, 5);

	//final
	wxBoxSizer* bs_parameters_main = new wxBoxSizer(wxHORIZONTAL);

	bs_parameters_main->Add(bs_problem_and_time_serie, 0, wxLEFT | wxTOP, 5);
	bs_parameters_main->Add(sbs_operators, 0, wxLEFT | wxTOP, 5);
	bs_parameters_main->Add(sbs_parameters, 0, wxLEFT | wxTOP, 5);
	bs_parameters_main->Add(sbs_constants, 0, wxLEFT | wxTOP, 5);
	bs_parameters_main->Add(bs_runs_and_data, 0, wxLEFT | wxTOP, 5);

	w_parameters->SetSizer(bs_parameters_main);
}
//-------------------------------------------------------------------------
