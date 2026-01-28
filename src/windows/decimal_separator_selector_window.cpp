// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/decimal_separator_selector_window.h"
#include "chart_bar_16x16.xpm"
#include "utils/data_separators.h"
// ---------------------------------------------------------------------------
t_decimal_separator_selector_window* f_decimal_separator_selector_window = NULL;
// ---------------------------------------------------------------------------
t_decimal_separator_selector_window::t_decimal_separator_selector_window(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxDialog(parent, wxID_ANY, title, pos, size)
{
	wxIcon icon(chart_bar_16x16_xpm);
	SetIcon(icon);

	struct lconv* lc;
	lc = localeconv();
	
	wxString rb_decimal_separator_choices[2] = { "Dot (.)", "System defined (" + wxString(lc->decimal_point) + ")"};
	rb_decimal_separator = new wxRadioBox(this, -1, "Decimal separator", wxDefaultPosition, wxDefaultSize, 2, rb_decimal_separator_choices);

	wxBoxSizer* bottom_sizer = (wxBoxSizer*)CreateSeparatedButtonSizer(wxOK | wxCANCEL);
	Bind(wxEVT_COMMAND_BUTTON_CLICKED, &t_decimal_separator_selector_window::OnOKPressed, this, wxID_OK);

	wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

	main_sizer->Add(rb_decimal_separator, 0, wxLEFT, 10);

	main_sizer->Add(bottom_sizer, 0, wxEXPAND | wxALL, 10);

	SetSizerAndFit(main_sizer);
}
// ---------------------------------------------------------------------------
void t_decimal_separator_selector_window::OnOKPressed(wxCommandEvent&)
{
	EndModal(wxID_OK);
}
// ---------------------------------------------------------------------------
void t_decimal_separator_selector_window::get_separator(char& decimal_separator)
{
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
