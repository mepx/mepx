// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/import_data_window.h"
#include "chart_bar_16x16.xpm"
#include "utils/data_separators.h"
// ---------------------------------------------------------------------------
t_import_data_window* f_import_data_window = NULL;
// ---------------------------------------------------------------------------
#define TIMER_ID 1301
// ---------------------------------------------------------------------------
t_import_data_window::t_import_data_window(wxWindow* parent,
														 const wxString& title,
														 const wxPoint& pos,
														 const wxSize& size)
	: wxDialog(parent, wxID_ANY, title, pos, size)
{
	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	Bind(wxEVT_SHOW, &t_import_data_window::OnShow, this);

	wxString rb_list_separator_choices[4] = { "Tab", "Semicolon (;)", "Comma (,)", "Space ( )" };
	rb_list_separator = new wxRadioBox(this, -1, "List separator", wxDefaultPosition, wxDefaultSize, 4, rb_list_separator_choices);
	rb_list_separator->Bind(wxEVT_RADIOBOX, &t_import_data_window::on_separators_changed, this);
	rb_list_separator->SetSelection(LIST_SEPARATOR_SEMICOLON);
	
	struct lconv* lc;
	lc = localeconv();
	
	char system_decimal_separator = '.';
	if (lc->decimal_point && lc->decimal_point[0])
		system_decimal_separator = lc->decimal_point[0];

	wxString rb_decimal_separator_choices[2] = { "Dot (.)", "System setting (" + wxString(system_decimal_separator) + ")"};
	rb_decimal_separator = new wxRadioBox(this, -1, "Decimal separator", wxDefaultPosition, wxDefaultSize, 2, rb_decimal_separator_choices);
	rb_decimal_separator->Bind(wxEVT_RADIOBOX, &t_import_data_window::on_separators_changed, this);

	if (system_decimal_separator == '.')
		rb_decimal_separator->SetSelection(DECIMAL_SEPARATOR_DOT);
	else
		rb_decimal_separator->SetSelection(DECIMAL_SEPARATOR_SYSTEM);
	
	cb_is_one_of_m = new wxCheckBox(this, -1, "Is classification data with one-of-m output? ");
	cb_is_one_of_m->SetToolTip("One-of-m output means that the last columns of data look like: 0 1 0 0 0");
	cb_is_one_of_m->SetValue(0);
	cb_is_one_of_m->Bind(wxEVT_CHECKBOX, &t_import_data_window::on_change_param_value, this);

	wxBoxSizer* sizer_num_classes = new wxBoxSizer(wxHORIZONTAL);
	l_num_classes = new wxStaticText(this, -1, "Number of classes");
	l_num_classes->Enable(false);
	sc_num_classes = new wxSpinCtrl(this, -1, "2", wxDefaultPosition, wxSize(100, -1), wxSP_ARROW_KEYS, 2, 2, 2);
	sc_num_classes->Enable(false);
	sc_num_classes->Bind(wxEVT_SPINCTRL, &t_import_data_window::on_num_classes_changed, this);
	sizer_num_classes->Add(l_num_classes);
	sizer_num_classes->Add(sc_num_classes);

	l_preview = new wxStaticText(this, -1, "Preview");

	g_data = new t_list_view_data_with_checkboxes(this, &data, false);

	wxBoxSizer* bottom_sizer = (wxBoxSizer*)CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &t_import_data_window::OnOKPressed, this, wxID_OK);

	wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

	main_sizer->Add(rb_list_separator, 0, wxLEFT | wxTOP| wxRIGHT, 5);
	main_sizer->Add(rb_decimal_separator, 0, wxLEFT, 5);
	main_sizer->Add(cb_is_one_of_m, 0, wxLEFT, 5);
	/*
	main_sizer->Add(l_num_classes, 0, wxLEFT, 10);
	main_sizer->Add(sc_num_classes, 0, wxLEFT, 10);
	*/
	main_sizer->Add(sizer_num_classes, 0, wxLEFT|wxTOP, 5);
	main_sizer->Add(l_preview, 0, wxLEFT|wxTOP, 5);
	main_sizer->Add(g_data, 0, wxEXPAND, 5);

	main_sizer->Add(bottom_sizer, 0, wxEXPAND | wxALL, 5);

	SetSizerAndFit(main_sizer);

	data_as_string = NULL;
	file_name = "";

	t_timer = new wxTimer;
	t_timer->SetOwner(this, TIMER_ID);
	Bind(wxEVT_TIMER, &t_import_data_window::on_timer, this);
}
// ---------------------------------------------------------------------------
t_import_data_window::~t_import_data_window()
{
	//delete data_provider;
	//data.clear_data();
	delete t_timer;
}
// ---------------------------------------------------------------------------
void t_import_data_window::OnOKPressed(wxCommandEvent&)
{
	if (validate_is_one_of_m()){
		data.remove_unchecked_rows(g_data->checked);
		if (data.from_string_cast_to_double()){
			if (cb_is_one_of_m->IsChecked())
				if (answer_is_one_of_m_multi_class_classification_problem == E_MEP_OK) {
					int presumed_num_classes = sc_num_classes->GetValue();
					data.to_one_of_m_multi_class_classification_problem(presumed_num_classes);
				}
		}
		EndModal(wxID_OK);
	}
}
// ---------------------------------------------------------------------------
void t_import_data_window::on_separators_changed(wxCommandEvent&)
{
	struct lconv* lc;
	lc = localeconv();
	
	char sytem_decimal_separator = '.';
	if (lc->decimal_point && lc->decimal_point[0])
		sytem_decimal_separator = lc->decimal_point[0];
	
	
	if (rb_list_separator->GetSelection() == LIST_SEPARATOR_COMMA &&
		rb_decimal_separator->GetSelection() == DECIMAL_SEPARATOR_SYSTEM &&
		(sytem_decimal_separator == ',')
	){
		wxMessageBox("Comma cannot be separator for both options!", "Error");
		rb_decimal_separator->SetSelection(DECIMAL_SEPARATOR_DOT);
	}
	// here I process it
	t_timer->StartOnce(100);
}
// ---------------------------------------------------------------------------
void t_import_data_window::get_separators(char& list_separator,
										  char& decimal_separator)
{
	switch (rb_list_separator->GetSelection()) {
	case LIST_SEPARATOR_TAB:
		list_separator = '\t';
		break;
	case LIST_SEPARATOR_SEMICOLON:
		list_separator = ';';
		break;
	case LIST_SEPARATOR_COMMA:
		list_separator = ',';
		break;
	case LIST_SEPARATOR_SPACE:
		list_separator = ' ';
		break;
	}

	struct lconv* lc;
	lc = localeconv();
	
	char system_decimal_separator = '.';
	if (lc->decimal_point && lc->decimal_point[0])
		system_decimal_separator = lc->decimal_point[0];
	
	switch (rb_decimal_separator->GetSelection()) {
	case DECIMAL_SEPARATOR_DOT:
		decimal_separator = '.';
		break;
	case DECIMAL_SEPARATOR_SYSTEM:
		decimal_separator = system_decimal_separator;
		break;
	}
}
// ---------------------------------------------------------------------------
void t_import_data_window::get_info(char& list_separator,
									char& decimal_separator,
									bool& is_one_of_m,
									int &_answer_is_one_of_m_multi_class_classification_problem,
									int& num_classes)
{
	get_separators(list_separator, decimal_separator);
	is_one_of_m = cb_is_one_of_m->IsChecked();
	_answer_is_one_of_m_multi_class_classification_problem = answer_is_one_of_m_multi_class_classification_problem;
	num_classes = sc_num_classes->GetValue();
}
// ---------------------------------------------------------------------------
void t_import_data_window::on_change_param_value(wxCommandEvent&)
{
	if (cb_is_one_of_m->IsChecked()) {
		l_num_classes->Enable(true);
		sc_num_classes->Enable(true);
		validate_is_one_of_m();
	}
	else {
		l_num_classes->Enable(false);
		sc_num_classes->Enable(false);
	}
}
// ---------------------------------------------------------------------------
void t_import_data_window::OnShow(wxShowEvent& event)
{
	if (!event.IsShown()) {
		event.Skip();
		return;
	}
	cb_is_one_of_m->SetValue(0);
	l_num_classes->Enable(false);
	sc_num_classes->Enable(false);
	
	t_timer->StartOnce(300);
}
// ---------------------------------------------------------------------------
void t_import_data_window::on_timer(wxTimerEvent&)
{
	update_grid_data();
}
//-------------------------------------------------------------------------
void t_import_data_window::update_grid_data(void)
{
	wxWindow::SetCursor(wxCURSOR_WAIT);

	data.clear_data();

	char list_separator, decimal_separator;
	get_separators(list_separator, decimal_separator);

	if (file_name != "")
		data.from_tabular_file_no_conversion(file_name.utf8_str(), list_separator);
	else
		if (data_as_string && *data_as_string != "")
			data.from_tab_separated_string_no_conversion(data_as_string->utf8_str(),
														 list_separator);

	g_data->update_num_rows_cols();

	if (data.get_num_cols() >= 3)
		sc_num_classes->SetRange(2, data.get_num_cols() - 1);
	else
		sc_num_classes->SetRange(2, 2);

	validate_is_one_of_m();

	wxWindow::SetCursor(wxNullCursor);
}
// ---------------------------------------------------------------------------
void t_import_data_window::on_num_classes_changed(wxSpinEvent& )
{
	validate_is_one_of_m();
}
// ---------------------------------------------------------------------------
bool t_import_data_window::validate_is_one_of_m(void)
{
	if (!cb_is_one_of_m->IsChecked())
		return true;

	int presumed_num_classes = sc_num_classes->GetValue();
	answer_is_one_of_m_multi_class_classification_problem =
			data.is_one_of_m_multi_class_classification_problem(presumed_num_classes,
																g_data->checked);

	switch (answer_is_one_of_m_multi_class_classification_problem) {
	case E_MEP_OK:
		// do nothing
			return true;
		break;
	case E_MEP_DATA_NUM_CLASSES_TOO_MANY:
		wxMessageBox("For classification problem, there are not enough columns or the number of classes is too big!");
		break;
	case E_MEP_DATA_NOT_NUMERICAL_VALUE:
		wxMessageBox("For classification problem, some values from the last " + (wxString() << presumed_num_classes) + " columns are not numeric!");
		break;
	case E_MEP_DATA_NOT_ONE_OF_M:
		wxMessageBox("For classification problem, some values from the last " + (wxString() << presumed_num_classes) + " columns are different from 0 and 1!");
		break;
	case E_MEP_DATA_MORE_THAN_ONE_1:
		wxMessageBox("For classification problem, on the last " + (wxString() << presumed_num_classes) + " columns there must be only 1 value of 1 on each row!");
		break;
	}
	return false;
}
// ---------------------------------------------------------------------------
