// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <wx/listctrl.h>
#include <wx/renderer.h>
//--------------------------------------------------------
#include "windows/components/lv_input_data.h"
//--------------------------------------------------------
t_list_view_data::t_list_view_data(wxWindow* parent,
								   t_mep_data* data,
								   bool _is_training) :
					wxListCtrl(parent, wxID_ANY, wxDefaultPosition,
								wxSize(300, -1),
							   wxLC_REPORT | wxLC_VIRTUAL)
{
    data_provider = data;
    is_training = _is_training;
	num_outputs = 1;
}
//--------------------------------------------------------
wxString t_list_view_data::OnGetItemText(long item, long column) const
{
    if (!data_provider)
        return "";

    if (column == 0) {
        return wxString() << (item + 1);
    }

    char data_type = data_provider->get_data_type();
    if (data_type == MEP_DATA_DOUBLE) {
        return wxString::Format("%lf", data_provider->get_value_double((unsigned int)item, (unsigned int)column - 1));
    }
	else{
		if (data_type == MEP_DATA_LONG_LONG) {
			return wxString::Format("%lld", data_provider->get_value_long_long((unsigned int)item, (unsigned int)column - 1));
		}
		else {
			return wxString(data_provider->get_value_string((unsigned int)item, (unsigned int)(column - 1)));
		}
	}
//    return "";
}
//--------------------------------------------------------
void t_list_view_data::update_num_rows_cols(void)
{
    if (!data_provider) {
        SetItemCount(0);
        Refresh();
        return;
    }

    if (data_provider->get_num_rows() == 0) {
        SetItemCount(0);
        DeleteAllColumns();
		Refresh();
		return;
    }

	DeleteAllItems();
	DeleteAllColumns();
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("#"));
	col0.SetWidth(65);
	InsertColumn(0, col0);

	for (unsigned int c = 0; c < data_provider->get_num_cols(); c++) {
		wxListItem col;
		col.SetWidth(65);

		col.SetId(c + 1);

		if (num_outputs <= data_provider->get_num_cols()){
			if ((unsigned int)col <= data_provider->get_num_cols() - num_outputs) {
				if (is_training)
					col.SetText("+x" + wxString::Format("%d", c));
				else
					col.SetText("x" + wxString::Format("%d", c));
			}
			else {
				if (num_outputs >= 1 &&
					data_provider->get_num_cols())
					col.SetText("Target" + wxString::Format("%d", c - data_provider->get_num_cols() +
															num_outputs));
			}
		}
		else{ // num outputs is greater than the number of cols
			if (num_outputs >= 1 &&
				data_provider->get_num_cols())
				col.SetText("Target" + wxString::Format("%d", c));

		}

		InsertColumn(c + 1, col);
	}

    SetItemCount(data_provider->get_num_rows());


    Refresh();
}
//--------------------------------------------------------
t_list_view_data_with_checkboxes::t_list_view_data_with_checkboxes(
								wxWindow* parent,
								t_mep_data* data,
								bool _is_training) :
							t_list_view_data(parent, data, _is_training)
{

	Bind(wxEVT_LIST_ITEM_CHECKED, &t_list_view_data_with_checkboxes::on_checked_change_state_clicked, this);
	Bind(wxEVT_LIST_ITEM_UNCHECKED, &t_list_view_data_with_checkboxes::on_checked_change_state_clicked, this);
	EnableCheckBoxes(true);
	checked = NULL;

	attr_checked = new wxListItemAttr();
	attr_checked->SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));

	attr_unchecked = new wxListItemAttr();
	attr_unchecked->SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
}
//--------------------------------------------------------
/*
void t_list_view_data_with_checkboxes::on_MouseEvent(wxMouseEvent& event)
{
   if (event.LeftDown()){
	  int flags;
	  long item = HitTest(event.GetPosition(), flags);
	  if (item > -1 && (flags & wxLIST_HITTEST_ONITEM)){
		  checked[item] = !checked[item];
		  SetChecked(item, checked[item]);
	  }
	  else
		 event.Skip();
   }
   else{
	  event.Skip();
   }
}
 */
//--------------------------------------------------------
t_list_view_data_with_checkboxes::~t_list_view_data_with_checkboxes()
{
	if (checked){
		delete[] checked;
		checked = NULL;
	}
	delete attr_checked;
	delete attr_unchecked;
}
//--------------------------------------------------------
wxListItemAttr* t_list_view_data_with_checkboxes::OnGetItemAttr(long item) const
{
	if (!checked[item])
		return attr_unchecked;
	return attr_checked;
}
//--------------------------------------------------------
void t_list_view_data_with_checkboxes::on_checked_change_state_clicked(wxListEvent& event)
{
	long item = event.GetIndex();
	checked[item] = !checked[item];
	RefreshItem(item);
}
//--------------------------------------------------------
bool t_list_view_data_with_checkboxes::OnGetItemIsChecked(long item)	const
{
	return checked[item];
}
//--------------------------------------------------------
void t_list_view_data_with_checkboxes::update_num_rows_cols(void)
{
	t_list_view_data::update_num_rows_cols();
	if (checked){
		delete[] checked;
		checked = NULL;
	}

	if (data_provider &&
		data_provider->get_num_rows()){
		unsigned int num_rows = data_provider->get_num_rows();
		checked = new char[num_rows];
		for (unsigned int i = 0; i < num_rows; i++)
			checked[i] = 1;
	}
}
//--------------------------------------------------------
