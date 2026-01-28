// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef mepx_chart_options_H
#define mepx_chart_options_H
//-----------------------------------------------------
class t_mepx_target_output_chart_options{
public:

	bool cb_chart_training_target_output, cb_chart_validation_target_output, cb_chart_testing_target_output, cb_chart_predictions_target_output;
	bool cb_chart_target, cb_chart_output;
	bool cb_chart_show_lines, cb_chart_show_separator;

	t_mepx_target_output_chart_options();
	void init(void);
};
//-----------------------------------------------------
class t_mepx_evolution_chart_options{
public:

	bool cb_pop_average_evolution, cb_validation_evolution;

	t_mepx_evolution_chart_options();
	void init(void);
};
//-----------------------------------------------------
#endif
