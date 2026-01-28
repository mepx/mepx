// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef lv_input_data_H
#define lv_input_data_H
//---------------------------------------------------------
#include <wx/wx.h>
#include <wx/listctrl.h>
//---------------------------------------------------------
#include "mep_data.h"
//--------------------------------------------------------
class t_list_view_data : public wxListCtrl {
public:
    t_list_view_data(wxWindow* parent,
					 t_mep_data* data,
					 bool is_training);
    wxString OnGetItemText(long item, long column) const;

    void update_num_rows_cols(void);
	unsigned int num_outputs;
	t_mep_data* data_provider;
private:

    bool is_training;	
};
//---------------------------------------------------------
class t_list_view_data_with_checkboxes: public t_list_view_data{
public:
	t_list_view_data_with_checkboxes(wxWindow* parent,
					 t_mep_data* data,
					 bool is_training);
	~t_list_view_data_with_checkboxes();
	
	void update_num_rows_cols(void);
	char* checked;

private:
	wxListItemAttr* attr_checked, *attr_unchecked;

	bool OnGetItemIsChecked	(	long 	item	)	const;
	void on_checked_change_state_clicked(wxListEvent& event);

	wxListItemAttr* OnGetItemAttr(long item) const;

	//bool IsChecked(long item) const;
};
//---------------------------------------------------------
#endif
