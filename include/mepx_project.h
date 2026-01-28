// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef MEP_PROJECT_H
#define MEP_PROJECT_H
//-----------------------------------------------------------------
#include "libmep.h"
#include "mepx_interface_layout.h"
#include "model_target_errors_data_providers.h"
#include "mep_stats_errors.h"
#include "mepx_chart_options.h"
//-----------------------------------------------------------------
class t_mepx_settings{
public:
	
	t_mepx_interface_layout interface_layout;

	t_mepx_target_output_chart_options target_output_chart_options;
	t_mepx_evolution_chart_options evolution_chart_options;

	t_mepx_settings();
	~t_mepx_settings();

	int to_xml_file(const char *filename);
	int from_xml_file(const char *filename);
};
//-----------------------------------------------------------------
//bool to_xml_file(const char* filename, const char *version);
//bool from_xml_file(const char* filename);
//-----------------------------------------------------------------
extern t_mep mep_engine;
extern t_mepx_settings mepx_settings;
extern char* s_project_name;

extern char s_runs_errors_label_regression[100];
extern char s_runs_errors_label_classification[100];

extern t_mep_run_errors_array run_errors;

//-----------------------------------------------------------------
extern t_model_target_error_data_provider training_data_error_provider,
							validation_data_error_provider,
							test_data_error_provider,
							prediction_data_provider;
//-----------------------------------------------------------------
unsigned int compute_num_data_to_draw(void);
//-----------------------------------------------------------------

#endif
