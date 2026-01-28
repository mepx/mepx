// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "mepx_chart_options.h"
//-----------------------------------------------------------------------------
t_mepx_target_output_chart_options::t_mepx_target_output_chart_options()
{
	init();
}
//-----------------------------------------------------------------------------
void t_mepx_target_output_chart_options::init(void)
{
	cb_chart_training_target_output = true;
	cb_chart_validation_target_output = cb_chart_testing_target_output = cb_chart_predictions_target_output = false;
	cb_chart_target = cb_chart_output = true;
	cb_chart_show_lines = cb_chart_show_separator = true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
t_mepx_evolution_chart_options::t_mepx_evolution_chart_options()
{
	init();
}
//-----------------------------------------------------------------------------
void t_mepx_evolution_chart_options::init(void)
{
	cb_pop_average_evolution = true;
	cb_validation_evolution = true;
}
//-----------------------------------------------------------------------------
