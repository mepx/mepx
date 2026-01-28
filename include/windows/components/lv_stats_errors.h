// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef lv_stats_errors_H
#define lv_stats_errors_H
//---------------------------------------------------------
#include <wx/wx.h>
#include <wx/listctrl.h>
//---------------------------------------------------------
#include "mep_stats_errors.h"
//--------------------------------------------------------
#define MEPX_STATS_TRAINING_COL 1
#define MEPX_STATS_VALIDATION_COL 2
#define MEPX_STATS_TEST_COL 3
#define MEPX_STATS_CODE_LENGTH_COL 4
#define MEPX_STATS_RUNTIME_COL 5
//--------------------------------------------------------
class t_list_view_stats_errors : public wxListView {
public:
	t_list_view_stats_errors(wxWindow* parent,
							 t_mep_run_errors_array* _data);
	wxString OnGetItemText(long item, long column) const;

	void update_num_rows(bool end_of_all_runs);
private:
	t_mep_run_errors_array* data_provider;
};
//---------------------------------------------------------
#endif /* lv_stats_errors_h */
