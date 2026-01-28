// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef stats_errors_H
#define stats_errors_H
//---------------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------------
class t_mep_run_errors{
public:
	int run_index;
	double training_error, validation_error, test_error, running_time;
	unsigned int num_utilized_instructions;
	
	t_mep_run_errors();
};
//---------------------------------------------------------------------
class t_mep_run_errors_array{
public:
	t_mep_run_errors* data;
	unsigned int count;
	
	double stddev_training, stddev_validation, stddev_test, stddev_runtime, stddev_code_length;
	double mean_training, mean_validation, mean_test, mean_runtime, mean_code_length;
	double best_training, best_validation, best_test, best_runtime;
	int best_code_length;
	
	t_mep_run_errors_array();
	~t_mep_run_errors_array();
	
	void clear(void);
	
	void add_new_item(void);
};
//---------------------------------------------------------------------
#endif /* stats_errors_h */
