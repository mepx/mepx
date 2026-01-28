// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "model_target_errors_data_providers.h"
#include "mepx_project.h"
//--------------------------------------------------------
#define MEPX_COL_OUTPUT 0
#define MEPX_COL_TARGET 1
#define MEPX_COL_ERROR 2
//--------------------------------------------------------
t_model_target_error_data_provider::t_model_target_error_data_provider(void)
{
    data = NULL;
    run = -1;
    output_double = NULL;
	output_long_long = NULL;
    valid_output = NULL;
    num_data = 0;
	num_problem_outputs = 1;
	has_target = false;
}
//--------------------------------------------------------
/*
void t_model_target_error_provider::set_data(t_mep_data* _data,
									 unsigned int _num_problem_outputs,
									 bool _has_target)
{
    data = _data;
	num_problem_outputs = _num_problem_outputs;
	has_target = _has_target;
}
*/
//--------------------------------------------------------
t_model_target_error_data_provider::~t_model_target_error_data_provider()
{
	clear_computed_output();
}
//--------------------------------------------------------
void t_model_target_error_data_provider::clear_computed_output(void)
{
	if (output_double) {
		for (unsigned int o = 0; o < num_data; o++)
			delete[] output_double[o];
		
		delete[] output_double;
		output_double = NULL;
    }
	if (output_long_long) {
		for (unsigned int o = 0; o < num_data; o++)
			delete[] output_long_long[o];
		delete[] output_long_long;
		output_long_long = NULL;
	}
    if (valid_output) {
        delete[] valid_output;
        valid_output = NULL;
    }
}
//--------------------------------------------------------
char t_model_target_error_data_provider::get_value(unsigned int row,
									unsigned int col,
									double & value_as_double,
									  long long& value_as_long_long,
									  char &data_type) const
{
	//char error_type = MEPX_ERROR_OK;
	value_as_double = 0;
	value_as_long_long = 0;
    //double output_double[1];
	data_type = mep_engine.get_parameters_ptr()->get_data_type();

    if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_REGRESSION ||
        mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE){

		if (!has_target){// that is test without output or predictions
			if (valid_output[row] == valid_output_OK){
				if (data_type == MEP_DATA_LONG_LONG)
					value_as_long_long = output_long_long[row][col];
				else
					value_as_double = output_double[row][col];
				return MEPX_ERROR_OK;
			}
			else{
				return MEPX_ERROR_UNKNOWN;
			}
		}
		else{// has target
			if (col % 3 == 0){// thats output
				if (valid_output[row] == valid_output_OK){
					if (data_type == MEP_DATA_LONG_LONG)
						value_as_long_long = output_long_long[row][col / 3];
					else
						value_as_double = output_double[row][col / 3];
					return MEPX_ERROR_OK;
				}
				else
					if (valid_output[row] == valid_output_NA){
						// no valid output
						return MEPX_ERROR_NO_VALUE;
					}
					else{ // no valid output
						return MEPX_ERROR_UNKNOWN;
					}
			}
			
			if (col % 3 == 1) {// target
				if (data_type == MEP_DATA_LONG_LONG)
					value_as_long_long = data->get_value_long_long(row,
														data->get_num_cols() - num_problem_outputs + col / 3); // target
				else
					value_as_double = data->get_value_double(row,
															  data->get_num_cols() - num_problem_outputs + col / 3);
				return MEPX_ERROR_OK;
			}
// error column
			if (valid_output[row] == valid_output_OK){

				if (data_type == MEP_DATA_LONG_LONG)
					value_as_long_long = llabs(output_long_long[row][col / 3] -
										  data->get_value_long_long(row,
											data->get_num_cols() + col / 3 - num_problem_outputs));
				else // double
					value_as_double = fabs(output_double[row][col / 3] -
										  data->get_value_double(row,
																 data->get_num_cols() + col / 3 - num_problem_outputs));
				return MEPX_ERROR_OK;
			}
			else
				if (valid_output[row] == valid_output_NA){
					// no valid output
					return MEPX_ERROR_NO_VALUE;
				}
				else {
					return MEPX_ERROR_UNKNOWN;
				}
        }

    }  
    else {// classification; all are integers
		data_type = MEP_DATA_LONG_LONG;
        if (col == MEPX_COL_TARGET) {
			if (has_target){// target
				value_as_long_long = (long long)data->get_value_double(row,
																   data->get_num_cols() - 1);
				return MEPX_ERROR_OK;
			}
            else {
                return MEPX_ERROR_NO_VALUE;
            }
        }
        else {
			if (valid_output[row] == valid_output_OK){//if (mep_engine.get_output(run, _data->get_row_as_double(row), output_double)) {// why not use the already computed output
				if (col == MEPX_COL_OUTPUT){
					value_as_long_long = (long long)output_double[row][0];// output
					return MEPX_ERROR_OK;
				}
                else
                    if (col == MEPX_COL_ERROR) {// error
						if (has_target){
							value_as_long_long = (fabs(output_double[row][0] -
												  data->get_value_double(row, data->get_num_cols() - 1)) < 1e-6 ? 0 : 1);
							return MEPX_ERROR_OK;
						}
						else {
							return MEPX_ERROR_NO_VALUE;
                        }
                    }
            }
            else
                if (col == MEPX_COL_OUTPUT || col == MEPX_COL_ERROR) {
                    return MEPX_ERROR_UNKNOWN;
                    // "ERROR";// NAN, DivBy0 etc
                }
        }
    }
    return MEPX_ERROR_UNKNOWN;
}
//--------------------------------------------------------
void t_model_target_error_data_provider::set_run(int _run, unsigned int _num_data,
									t_mep_data* _data,
									unsigned int _num_problem_outputs,
									bool _has_target)
{
	data = _data;
	num_problem_outputs = _num_problem_outputs;
	has_target = _has_target;
	
    if (_run == -1) {
		clear_computed_output();
        num_data = 0;
    }
    else {
        if (_num_data != num_data) {
			clear_computed_output();

            num_data = _num_data;
            if (num_data) {
                output_double = new double*[num_data];
				for (unsigned int o = 0; o < num_data; o++)
					output_double[o]= new double[num_problem_outputs];
				
				output_long_long = new long long*[num_data];
				for (unsigned int o = 0; o < num_data; o++)
					output_long_long[o]= new long long[num_problem_outputs];

                valid_output = new char[num_data];
            }
        }
    }

    run = _run;
}
//--------------------------------------------------------
int t_model_target_error_data_provider::get_run(void)
{
    return run;
}
//--------------------------------------------------------
unsigned int t_model_target_error_data_provider::get_num_data(void)
{
	return num_data;
}
//--------------------------------------------------------
