// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//--------------------------------------------------------
#include "windows/components/lv_stats_errors.h"
//--------------------------------------------------------
t_list_view_stats_errors::t_list_view_stats_errors(wxWindow* parent,
												   t_mep_run_errors_array* data) :
					wxListView(parent, wxID_ANY, wxDefaultPosition,
								wxSize(300, -1),
							   wxLC_REPORT | wxLC_VIRTUAL | wxLC_SINGLE_SEL)
{
	data_provider = data;

	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("#"));
	col0.SetWidth(50);
	InsertColumn(0, col0);

	// training
	wxListItem col_training;

	col_training.SetId(MEPX_STATS_TRAINING_COL);
	col_training.SetText("Training");
	col_training.SetWidth(wxLIST_AUTOSIZE_USEHEADER);

	InsertColumn(MEPX_STATS_TRAINING_COL, col_training);
// validation
	wxListItem col_validation;
	col_validation.SetWidth(wxLIST_AUTOSIZE_USEHEADER);

	col_validation.SetId(MEPX_STATS_VALIDATION_COL);
	col_validation.SetText("Validation");

	InsertColumn(MEPX_STATS_VALIDATION_COL, col_validation);
// test
	wxListItem col_test;
	col_test.SetWidth(wxLIST_AUTOSIZE_USEHEADER);

	col_test.SetId(MEPX_STATS_TEST_COL);
	col_test.SetText("Test");

	InsertColumn(MEPX_STATS_TEST_COL, col_test);
	// code length
	wxListItem col_code_length;
	col_code_length.SetWidth(wxLIST_AUTOSIZE_USEHEADER);

	col_code_length.SetId(MEPX_STATS_CODE_LENGTH_COL);
	col_code_length.SetText("Num Instructions");

	InsertColumn(MEPX_STATS_CODE_LENGTH_COL, col_code_length);
	// run time
	wxListItem col_run_time;
	col_run_time.SetWidth(wxLIST_AUTOSIZE_USEHEADER);

	col_run_time.SetId(MEPX_STATS_RUNTIME_COL);
	col_run_time.SetText("Run time");

	InsertColumn(MEPX_STATS_RUNTIME_COL, col_run_time);
}
//--------------------------------------------------------
wxString t_list_view_stats_errors::OnGetItemText(long item, long column) const
{
	if (!data_provider)
		return "";
	
	if (item < data_provider->count){
		
		switch (column) {
			case 0:
				return wxString() << (item + 1);
				break;
				
			case MEPX_STATS_TRAINING_COL:
				if (data_provider->data[item].training_error < 0)
					return "";
				return wxString() << data_provider->data[item].training_error;
				break;
			case MEPX_STATS_VALIDATION_COL:
				if (data_provider->data[item].validation_error < 0)
					return "";
				return wxString() << data_provider->data[item].validation_error;
				break;
			case MEPX_STATS_TEST_COL:
				if (data_provider->data[item].test_error < 0)
					return "";
				return wxString() << data_provider->data[item].test_error;
				break;
			case MEPX_STATS_CODE_LENGTH_COL:
				return wxString() << data_provider->data[item].num_utilized_instructions;
				break;
			case MEPX_STATS_RUNTIME_COL:
				if (data_provider->data[item].running_time < 0)
					return "";
				return wxString() << data_provider->data[item].running_time;
				break;
		}
		return "";
	}
	
	if (item == data_provider->count){
		switch (column) {
			case 0:
				return wxString("Best");
				break;
				
			case MEPX_STATS_TRAINING_COL:
				if (data_provider->best_training < 0)
					return "";
				return wxString() << data_provider->best_training;
				break;
			case MEPX_STATS_VALIDATION_COL:
				if (data_provider->best_validation < 0)
					return "";
				return wxString() << data_provider->best_validation;
				break;
			case MEPX_STATS_TEST_COL:
				if (data_provider->best_test < 0)
					return "";
				return wxString() << data_provider->best_test;
				break;
			case MEPX_STATS_CODE_LENGTH_COL:
				return wxString() << data_provider->best_code_length;
				break;
			case MEPX_STATS_RUNTIME_COL:
				if (data_provider->best_runtime < 0)
					return "";
				return wxString() << data_provider->best_runtime;
				break;
		}
		return "";

	}
	if (item == data_provider->count + 1){
		switch (column) {
			case 0:
				return wxString("Mean");
				break;
				
			case MEPX_STATS_TRAINING_COL:
				if (data_provider->mean_training < 0)
					return "";
				return wxString() << data_provider->mean_training;
				break;
			case MEPX_STATS_VALIDATION_COL:
				if (data_provider->mean_validation < 0)
					return "";
				return wxString() << data_provider->mean_validation;
				break;
			case MEPX_STATS_TEST_COL:
				if (data_provider->mean_test < 0)
					return "";
				return wxString() << data_provider->mean_test;
				break;
			case MEPX_STATS_CODE_LENGTH_COL:
				return wxString() << data_provider->mean_code_length;
				break;
			case MEPX_STATS_RUNTIME_COL:
				if (data_provider->mean_runtime < 0)
					return "";
				return wxString() << data_provider->mean_runtime;
				break;
		}
		return "";

	}
	
	if (item == data_provider->count + 2){
		switch (column) {
			case 0:
				return wxString("StdDev");
				break;
				
			case MEPX_STATS_TRAINING_COL:
				if (data_provider->stddev_training < 0)
					return "";
				return wxString() << data_provider->stddev_training;
				break;
			case MEPX_STATS_VALIDATION_COL:
				if (data_provider->stddev_validation < 0)
					return "";
				return wxString() << data_provider->stddev_validation;
				break;
			case MEPX_STATS_TEST_COL:
				if (data_provider->stddev_test < 0)
					return "";
				return wxString() << data_provider->stddev_test;
				break;
			case MEPX_STATS_CODE_LENGTH_COL:
				return wxString() << data_provider->stddev_code_length;
				break;
			case MEPX_STATS_RUNTIME_COL:
				if (data_provider->stddev_runtime < 0)
					return "";
				return wxString() << data_provider->stddev_runtime;
				break;
		}
		return "";

	}

    return "";
}
//--------------------------------------------------------
void t_list_view_stats_errors::update_num_rows(bool end_of_all_runs)
{
	if (!data_provider) {
		SetItemCount(0);
		Refresh();
		return;
	}

	if (data_provider->count == 0) {
		SetItemCount(0);
	}
	else {
		DeleteAllItems();
	}

	if (end_of_all_runs)
		SetItemCount(data_provider->count + 3);
	else
		SetItemCount(data_provider->count);
	
	Refresh();
}
//--------------------------------------------------------
