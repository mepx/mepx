// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/replace_symbol_window.h"
#include "chart_bar_16x16.xpm"
// ---------------------------------------------------------------------------
t_replace_symbol_window* f_replace_symbol_window = NULL;
// ---------------------------------------------------------------------------
t_replace_symbol_window::t_replace_symbol_window(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxDialog(parent, wxID_ANY, title, pos, size)
{

	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	st_find_what = new wxStaticText(this, -1, "Find what");
	st_replace_with = new wxStaticText(this, -1, "Replace with");
	
	tc_find_what = new wxTextCtrl(this, -1, "?", wxDefaultPosition, wxSize(100, -1));
	tc_replace_with = new wxTextCtrl(this, -1, "0", wxDefaultPosition, wxSize(100, -1));

	wxString rb_replace_where_choices[2] = { "Everywhere", "Selected column" };
	rb_replace_where = new wxRadioBox( this, -1, "Replace where", wxDefaultPosition, wxDefaultSize, 2, rb_replace_where_choices);
	rb_replace_where->Bind(wxEVT_RADIOBOX, &t_replace_symbol_window::on_replace_where_changed, this);

	wxArrayString x;
	cb_column = new wxComboBox( this, -1, "", wxDefaultPosition, wxDefaultSize, x, wxCB_READONLY);

	wxBoxSizer *bottom_sizer = (wxBoxSizer *)CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &t_replace_symbol_window::OnOKPressed, this, wxID_OK);

	cb_use_regular = new wxCheckBox(this, -1, "Use regular expressions");

	wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);

	main_sizer->Add(st_find_what, 0, wxLEFT|wxTOP, 10);
	main_sizer->Add(tc_find_what, 0, wxLEFT, 10);
	main_sizer->Add(st_replace_with, 0, wxLEFT | wxTOP, 10);
	main_sizer->Add(tc_replace_with, 0, wxLEFT, 10);
	main_sizer->Add(rb_replace_where, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	main_sizer->Add(cb_column, 0, wxLEFT | wxTOP, 10);
	main_sizer->Add(cb_use_regular, 0, wxLEFT | wxTOP, 10);

	main_sizer->Add(bottom_sizer, 0, wxEXPAND | wxALL, 10);

	cb_column->Enable(false);

	SetSizerAndFit(main_sizer);
}
// ---------------------------------------------------------------------------
void t_replace_symbol_window::OnOKPressed(wxCommandEvent&)
{
	EndModal(wxID_OK);
}
// ---------------------------------------------------------------------------
void t_replace_symbol_window::on_replace_where_changed(wxCommandEvent& )
{
	if (rb_replace_where->GetSelection() == 1)
		cb_column->Enable(true);
	else
		cb_column->Enable(false);
}
// ---------------------------------------------------------------------------
