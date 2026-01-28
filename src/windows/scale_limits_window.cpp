// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/scale_limits_window.h"
#include "chart_bar_16x16.xpm"
// ---------------------------------------------------------------------------
t_scale_limits_window* f_scale_limits_window = NULL;
// ---------------------------------------------------------------------------
t_scale_limits_window::t_scale_limits_window(wxWindow *parent, const wxString& title,
											 const wxPoint& pos, const wxSize& size)
	: wxDialog(parent, wxID_ANY, title, pos, size)
{
	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	st_min = new wxStaticText(this, -1, "Min");
	st_max = new wxStaticText(this, -1, "Max");
	tc_min = new wxTextCtrl(this, -1, "0", wxDefaultPosition, wxSize(100, -1));
	tc_max = new wxTextCtrl(this, -1, "1", wxDefaultPosition, wxSize(100, -1));
    
    wxString rb_scale_where_choices[4] = { "Everywhere", "Selected column"};
	rb_scale_where = new wxRadioBox( this, -1, "Replace where", wxDefaultPosition, wxDefaultSize, 2, rb_scale_where_choices);
	rb_scale_where->Bind(wxEVT_RADIOBOX, &t_scale_limits_window::on_scale_where_changed, this);
    
	wxArrayString x;
	cb_column = new wxComboBox( this, -1, "", wxDefaultPosition, wxDefaultSize, x, wxCB_READONLY);

	wxBoxSizer *bottom_sizer = (wxBoxSizer *)CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &t_scale_limits_window::OnOKPressed, this, wxID_OK);

	wxBoxSizer *main_sizer = new wxBoxSizer(wxVERTICAL);
	
	main_sizer->Add(st_min, 0, wxLEFT|wxTOP, 10);
	main_sizer->Add(tc_min, 0, wxLEFT, 10);
	main_sizer->Add(st_max, 0, wxLEFT|wxTOP , 10);
	main_sizer->Add(tc_max, 0, wxLEFT, 10);
	main_sizer->Add(rb_scale_where, 0, wxLEFT | wxTOP | wxRIGHT, 10);
	main_sizer->Add(cb_column, 0, wxLEFT | wxTOP, 10);

	main_sizer->Add(bottom_sizer, 0, wxEXPAND | wxALL, 10);

	SetSizerAndFit(main_sizer);
}
// ---------------------------------------------------------------------------
void t_scale_limits_window::OnOKPressed(wxCommandEvent&)
{
	EndModal(wxID_OK);
}
// ---------------------------------------------------------------------------
void t_scale_limits_window::on_scale_where_changed(wxCommandEvent& )
{
	if (rb_scale_where->GetSelection() == 1)
		cb_column->Enable(true);
	else
		cb_column->Enable(false);
}
// ---------------------------------------------------------------------------
