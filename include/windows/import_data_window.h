// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef separator_selector_window_H
#define separator_selector_window_H
// ---------------------------------------------------------------------------
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
// ---------------------------------------------------------------------------
#include "components/lv_input_data.h"
// ---------------------------------------------------------------------------
class t_import_data_window : public wxDialog{
private:
	wxStaticText* l_preview;

	t_list_view_data_with_checkboxes* g_data;

	void update_grid_data(void);
	void on_change_param_value(wxCommandEvent&);
	void OnOKPressed(wxCommandEvent& event);
	void on_separators_changed(wxCommandEvent& event);
	void OnShow(wxShowEvent& event);
	void on_num_classes_changed(wxSpinEvent& event);
	bool validate_is_one_of_m(void);
	void on_timer(wxTimerEvent&);

	int answer_is_one_of_m_multi_class_classification_problem;
	wxCheckBox* cb_is_one_of_m;
	wxStaticText* l_num_classes;
	wxSpinCtrl* sc_num_classes;
	wxRadioBox* rb_list_separator, * rb_decimal_separator;

	wxTimer* t_timer;
public:
	t_mep_data data;

	wxString file_name;
	wxString* data_as_string;

	t_import_data_window(wxWindow* parent, const wxString& title,
								const wxPoint& pos, const wxSize& size);
	~t_import_data_window();

	void get_separators(char& list_separator, char& decimal_separator);
	void get_info(char& list_separator,
				  char& decimal_separator,
					bool& is_one_of_m_output,
					int &_answer_is_one_of_m_multi_class_classification_problem,
					int& num_classes);
};
// ---------------------------------------------------------------------------
extern t_import_data_window* f_import_data_window;
// ---------------------------------------------------------------------------

#endif
