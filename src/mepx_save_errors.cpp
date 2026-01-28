// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "mepx_save_errors.h"
#include "mepx_project.h"
//-------------------------------------------------------------------------------
bool save_errors_to_csv_file(const wxString &wx_file_name,
						const t_mep_data* data_ptr,
						const t_model_target_error_data_provider& data_error_provider)
{
	FILE* f = NULL;

#ifdef _WIN32
	f = _wfopen(wx_file_name.wc_str(), L"w");
#else
	f = fopen(wx_file_name.utf8_str(), "w");
#endif

	if (!f)
		return false;
	
	unsigned int num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	for (unsigned int o = 0; o < num_outputs; o++){
		fprintf(f, "Output%u;Target%u;Error%u", o, o, o);
		if (o < num_outputs - 1)
			fprintf(f, ";");
	}
	fprintf(f, "\n");
	
	for (unsigned int r = 0; r < data_ptr->get_num_rows(); r++) {
		double output_double = 0, target_double = 0, difference_double = 0;
		long long output_long = 0, target_long = 0, difference_long = 0;
		char data_type;
		
		char error_type = 0;
		for (unsigned int o = 0; o < num_outputs; o++){
			
			error_type = data_error_provider.get_value(r, o * 3 + 1, target_double, target_long, data_type);
			error_type = data_error_provider.get_value(r, o * 3 + 2, difference_double, difference_long, data_type);
			error_type = data_error_provider.get_value(r, o * 3 + 0, output_double, output_long, data_type);

			if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_REGRESSION ||
				mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE) {
				
				if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG){
					switch (error_type) {
						case MEPX_ERROR_UNKNOWN:
							fprintf(f, "ERROR;%lld;ERROR", target_long);// definitively was an error
							break;
						case MEPX_ERROR_OK:
							fprintf(f, "%lld;%lld;%lld", output_long, target_long, difference_long);
							break;
						case MEPX_ERROR_NO_VALUE:
							fprintf(f, ";%lld;", target_long);
							break;
					}
				}
				else{// double
					switch (error_type) {
						case MEPX_ERROR_UNKNOWN:
							fprintf(f, "ERROR;%lf;ERROR", target_double);// definitively was an error
							break;
						case MEPX_ERROR_OK:
							fprintf(f, "%lf;%lf;%lf", output_double, target_double, difference_double);
							break;
						case MEPX_ERROR_NO_VALUE:
							fprintf(f, ";%lf;", target_double);
							break;
					}
					
				}
			}
			else {// classification
				switch (error_type) {
					case MEPX_ERROR_UNKNOWN:
						fprintf(f, "ERROR;%lld;ERROR", target_long);// definitively was an error
						break;
					case MEPX_ERROR_OK:
						fprintf(f, "%lld;%lld;%lld", output_long, target_long, difference_long);
						break;
					case MEPX_ERROR_NO_VALUE:
						fprintf(f, ";%lld;", target_long);
						break;
				}
			}
			if (o < num_outputs - 1)
				fprintf(f, ";");
		}// end for o
		fprintf(f, "\n");
	}// end for r
	fclose(f);
	return true;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
bool save_training_errors_to_csv_file(const wxString &wx_file_name)
{
	return save_errors_to_csv_file(wx_file_name,
		mep_engine.get_training_data_ptr(),
							  training_data_error_provider);
}
//-------------------------------------------------------------------------------
bool save_validation_errors_to_csv_file(const wxString& wx_file_name)
{
	return save_errors_to_csv_file(wx_file_name,
		mep_engine.get_validation_data_ptr(),
							  validation_data_error_provider);
}
//-------------------------------------------------------------------------------
bool save_test_errors_to_csv_file(const wxString& wx_file_name)
{
	if (mep_engine.get_test_data_ptr()->get_num_cols() ==
		mep_engine.get_training_data_ptr()->get_num_cols()){
		return save_errors_to_csv_file(wx_file_name,
			mep_engine.get_test_data_ptr(),
								  test_data_error_provider);
	}
	// no target
	FILE* f = NULL;

#ifdef _WIN32
	f = _wfopen(wx_file_name.wc_str(), L"w");
#else
	f = fopen(wx_file_name.utf8_str(), "w");
#endif

	if (!f)
		return false;
	
	unsigned int num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	for (unsigned int o = 0; o < num_outputs; o++){
		fprintf(f, "Output%u", o);
		if (o < num_outputs - 1)
			fprintf(f, ";");
	}
	fprintf(f, "\n");


	for (unsigned int r = 0; r < mep_engine.get_test_data_ptr()->get_num_rows(); r++) {
		double model_double = 0;
		long long model_long = 0;
		char data_type;
		
		for (unsigned int o = 0; o < num_outputs; o++){
			
			char error_type = test_data_error_provider.get_value(r, o,
																 model_double,
																 model_long, data_type);
			
			if (mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_REGRESSION ||
				mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE) {
				// regression
				if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG){
					switch (error_type) {
						case MEPX_ERROR_UNKNOWN:
							fprintf(f, "ERROR");
							break;
						case MEPX_ERROR_OK:
							fprintf(f, "%lld", model_long);
							break;
					}
				}
				else{// double
					switch (error_type) {
						case MEPX_ERROR_UNKNOWN:
							fprintf(f, "ERROR");
							break;
						case MEPX_ERROR_OK:
							fprintf(f, "%lf", model_double);
							break;
					}
				}
			}
			else {
				// classification
				switch (error_type) {
					case MEPX_ERROR_UNKNOWN:
						fprintf(f, "ERROR");
						break;
					case MEPX_ERROR_OK:
						fprintf(f, "%lld", model_long);
						break;
				}
			}
			if (o < num_outputs - 1)
				fprintf(f, ";");
		}// end for o
		fprintf(f, "\n");
	} // end for i
	fclose(f);
	return true;
}
//-------------------------------------------------------------------------------
bool save_predictions_to_csv_file(const wxString& wx_file_name, int run)
{
	FILE* f = NULL;

#ifdef _WIN32
	f = _wfopen(wx_file_name.wc_str(), L"w");
#else
	f = fopen(wx_file_name.utf8_str(), "w");
#endif

	if (!f)
		return false;

	unsigned int num_predictions = mep_engine.get_parameters_ptr()->get_num_predictions();
	if (num_predictions > 0 && run >= 0 &&
		mep_engine.get_parameters_ptr()->get_problem_type() == MEP_PROBLEM_TIME_SERIE) {
		
		char* correct_output = new char[num_predictions];
		unsigned int num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
		
		for (unsigned int o = 0; o < num_outputs; o++){
			fprintf(f, "Output%u", o);
			if (o < num_outputs - 1)
				fprintf(f, ";");
		}
		fprintf(f, "\n");
		
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_LONG_LONG){
			long long** output = new long long*[num_predictions];
			for (unsigned int i = 0; i < num_predictions; i++)
				output[i] = new long long[num_outputs];
			
			if (mep_engine.predict(run, output, correct_output))
				for (unsigned int i = 0; i < num_predictions; i++) {
					if (correct_output[i]) {
						for (unsigned int o = 0; o < num_outputs; o++){
							fprintf(f, "%lld", output[i][o]);
							if (o < num_outputs - 1)
								fprintf(f, ";");
						}
						fprintf(f, "\n");
					}
					else
						break; // cannot continue a broken prediction
				}

			for (unsigned int i = 0; i < num_predictions; i++)
				delete[] output[i];
			delete[] output;
		}
		else{// double
			double** output = new double*[num_predictions];
			for (unsigned int i = 0; i < num_predictions; i++)
				output[i] = new double[num_outputs];
			
			if (mep_engine.predict(run, output, correct_output))
				for (unsigned int i = 0; i < num_predictions; i++) {
					if (correct_output[i]) {
						for (unsigned int o = 0; o < num_outputs; o++){
							fprintf(f, "%lf", output[i][o]);
							if (o < num_outputs - 1)
								fprintf(f, ";");
						}
						fprintf(f, "\n");
					}
					else
						break; // cannot continue a broken prediction

				}

			for (unsigned int i = 0; i < num_predictions; i++)
				delete[] output[i];
			delete[] output;
		}
		delete[] correct_output;
	}

	fclose(f);
	return true;
}
//-------------------------------------------------------------------------------
