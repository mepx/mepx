// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/components/lv_output_target_errors.h"
#include "mepx_project.h"
//--------------------------------------------------------
#define MEPX_COL_OUTPUT 0
#define MEPX_COL_TARGET 1
#define MEPX_COL_ERROR 2

//--------------------------------------------------------
t_lv_output_target_error::t_lv_output_target_error(wxWindow* parent,
												   t_model_target_error_data_provider *_data_provider):
    wxListCtrl(parent, wxID_ANY, wxDefaultPosition,
			   wxSize(300, -1), wxLC_REPORT | wxLC_VIRTUAL)
{
    data_provider = _data_provider;
}
//--------------------------------------------------------
wxString t_lv_output_target_error::OnGetItemText(long item, long column) const
{
    if (!data_provider)
        return "";

    if (data_provider->get_run() == -1)
        return "";

    if (column == 0)
        return wxString() << (item + 1);

	
	double value_as_double;
	long long value_as_long;
	char data_type;
	
    char error_type = data_provider->get_value((unsigned int)item,
											 (unsigned int)(column - 1),
												value_as_double, value_as_long,
												data_type);
    switch (error_type) {
    case MEPX_ERROR_UNKNOWN:
        return "ERROR";
    case MEPX_ERROR_OK:
		if (data_type == MEP_DATA_LONG_LONG)
			return wxString() << value_as_long;
		else
			return wxString() << value_as_double;
    case MEPX_ERROR_NO_VALUE:
        return "";
    }

    return "";
}
//--------------------------------------------------------
void t_lv_output_target_error::my_update(void)
{
    if (!data_provider) {
        SetItemCount(0);
		DeleteAllColumns();
        Refresh();
        return;
    }
    if (data_provider->get_run() == -1) {
        SetItemCount(0);
		DeleteAllColumns();
        Refresh();
        return;
    }
	
	if (data_provider->get_num_data() == 0) {
		SetItemCount(0);
		DeleteAllColumns();
		Refresh();
		return;
	}
	SetItemCount(0);
	DeleteAllColumns();
	
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("#"));
	col0.SetWidth(50);
	InsertColumn(0, col0);

	// Add output columns
	unsigned int num_actual_cols = 1;
	for (unsigned int o = 0; o < data_provider->num_problem_outputs; o++){
		wxListItem col1;
		col1.SetId(num_actual_cols);
		col1.SetText(("Output" + (wxString()<<o)));
		col1.SetWidth(80);
		InsertColumn(num_actual_cols, col1);
		num_actual_cols++;
		
		if (data_provider->has_target){
			wxListItem col2;
			col2.SetId(num_actual_cols);
			col2.SetText(("Target" + (wxString()<<o)));
			col2.SetWidth(100);
			InsertColumn(num_actual_cols, col2);
			num_actual_cols++;

			wxListItem col3;
			col3.SetId(num_actual_cols);
			col3.SetText(("Abs. Diff." + (wxString()<<o)));
			col3.SetWidth(100);
			InsertColumn(num_actual_cols, col3);
			num_actual_cols++;
		}
	}
	
    SetItemCount(data_provider->get_num_data());
    Refresh();
}
//--------------------------------------------------------
