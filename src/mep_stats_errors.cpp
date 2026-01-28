// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "mep_stats_errors.h"
//--------------------------------------------------
t_mep_run_errors::t_mep_run_errors()
{
	run_index = -1;
	training_error = validation_error = test_error = -1;
	running_time = 0;
	num_utilized_instructions = 0;
}
//--------------------------------------------------
t_mep_run_errors_array::t_mep_run_errors_array()
{
	data = NULL;
	count = 0;
	stddev_training = stddev_validation = stddev_test = stddev_runtime = stddev_code_length = -1;
	mean_training = mean_validation = mean_test = mean_runtime = mean_code_length = -1;
	best_training = best_validation = best_test = best_runtime = -1;
	best_code_length = 0;
}
//--------------------------------------------------
t_mep_run_errors_array::~t_mep_run_errors_array()
{
	clear();
}
//--------------------------------------------------
void t_mep_run_errors_array::clear(void)
{
	if (data){
		delete[] data;
		data = NULL;
	}
	count = 0;
	stddev_training = stddev_validation = stddev_test = stddev_runtime = stddev_code_length = -1;
	mean_training = mean_validation = mean_test = mean_runtime = mean_code_length = -1;
	best_training = best_validation = best_test = best_runtime = -1;
	best_code_length = 0;
}
//--------------------------------------------------
void t_mep_run_errors_array::add_new_item(void)
{
	if (!data){
		count = 1;
		data = new t_mep_run_errors[1];
		return;
	}
	
	t_mep_run_errors *new_data = new t_mep_run_errors[count + 1];
	for (unsigned int i = 0; i < count; i++)
		new_data[i] = data[i];
	delete[] data;
	data = new_data;
	count++;
}
//--------------------------------------------------
