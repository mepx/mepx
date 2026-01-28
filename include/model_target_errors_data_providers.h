// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef grid_errors_data_providers_H
#define grid_errors_data_providers_H
//---------------------------------------------------------
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/listctrl.h>
//---------------------------------------------------------
#include "mep_data.h"
//--------------------------------------------------------
#define MEPX_ERROR_OK 0
#define MEPX_ERROR_NO_VALUE 1
#define MEPX_ERROR_UNKNOWN 2
//---------------------------------------------------------
class t_model_target_error_data_provider{
private:

	t_mep_data* data;
	int run;
	void clear_computed_output(void);
	
public:
	unsigned int num_data; // this is different from the data.num_data in the case of time series prediction
	double** output_double;
	long long** output_long_long;
	char* valid_output;
	
	unsigned int num_problem_outputs;
	bool has_target;

	t_model_target_error_data_provider();
    //void set_data(t_mep_data* _data, unsigned int num_outputs, bool has_target);
    ~t_model_target_error_data_provider();

	char get_value(unsigned int row,
				   unsigned int col,
				   double & value_as_double,
				 long long& value_as_long,
				   char& data_type) const;

    void set_run(int _run, unsigned int _num_data,
				 t_mep_data* _data,
				 unsigned int _num_problem_outputs,
				 bool _has_target);
    int get_run(void);
	
	unsigned int get_num_data(void);

};
//---------------------------------------------------------
#endif
