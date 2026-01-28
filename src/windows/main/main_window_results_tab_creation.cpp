// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//-----------------------------------------------------------------------------------------
#include "save_16x16.xpm"
#include "clipboard_16x16.xpm"
//-----------------------------------------------------------------------------------------
void t_main_window::build_panel_error_tables(wxPanel* p_error_tables)
{
	// panel error codes
	wxStaticText* st_results_errors = new wxStaticText(p_error_tables, -1, "Output, Target, Errors");
	b_save_error_tables = new wxButton(p_error_tables, -1, "Save");
	wxBitmap bmp_save(save_16x16_xpm);
	b_save_error_tables->SetBitmap(bmp_save);
	b_save_error_tables->Bind(wxEVT_BUTTON, &t_main_window::on_save_errors_button_clicked, this);

	n_error_tables = new wxNotebook(p_error_tables, -1);
	n_error_tables->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &t_main_window::on_change_errors_notebook_page, this);

	g_error_training = new t_lv_output_target_error(n_error_tables, &training_data_error_provider);

	g_error_validation = new t_lv_output_target_error(n_error_tables, &validation_data_error_provider);

	g_error_testing = new t_lv_output_target_error(n_error_tables, &test_data_error_provider);

	g_predictions = new t_lv_output_target_error(n_error_tables, &prediction_data_provider);

	n_error_tables->AddPage(g_error_training, "Training");
	n_error_tables->AddPage(g_error_validation, "Validation");
	n_error_tables->AddPage(g_error_testing, "Test");
	n_error_tables->AddPage(g_predictions, "Predictions");

	wxBoxSizer* bs_toolbar_results = new wxBoxSizer(wxHORIZONTAL);
	bs_toolbar_results->Add(st_results_errors, 0, wxCENTER | wxLEFT | wxRIGHT, 5);
	bs_toolbar_results->Add(b_save_error_tables);
	//bs_toolbar_results->Add(b_copy_error_table);

	wxBoxSizer* bs_error_results = new wxBoxSizer(wxVERTICAL);
	bs_error_results->Add(bs_toolbar_results);
	bs_error_results->Add(n_error_tables, 1, wxEXPAND, 0);

	p_error_tables->SetSizer(bs_error_results);
}
//-----------------------------------------------------------------------------------------
void t_main_window::build_panel_chart(wxPanel* p_chart_with_menu)
{
	cb_target_for_chart = new wxComboBox(p_chart_with_menu, -1, "",
										 wxDefaultPosition, wxDefaultSize,
										 0, NULL,
										 wxCB_READONLY);
	cb_target_for_chart->Bind(wxEVT_COMBOBOX, &t_main_window::on_cb_target_for_chart_change, this);

	cb_chart_training_target_output = new wxCheckBox(p_chart_with_menu, -1, "Training");
	cb_chart_training_target_output->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_validation_target_output = new wxCheckBox(p_chart_with_menu, -1, "Validation");
	cb_chart_validation_target_output->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_testing_target_output = new wxCheckBox(p_chart_with_menu, -1, "Test");
	cb_chart_testing_target_output->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_predictions_target_output = new wxCheckBox(p_chart_with_menu, -1, "Predictions");
	cb_chart_predictions_target_output->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_target = new wxCheckBox(p_chart_with_menu, -1, "Target");
	cb_chart_target->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_output = new wxCheckBox(p_chart_with_menu, -1, "Output");
	cb_chart_output->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_show_lines = new wxCheckBox(p_chart_with_menu, -1, "Lines");
	cb_chart_show_lines->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	cb_chart_show_separator = new wxCheckBox(p_chart_with_menu, -1, "Separator");
	cb_chart_show_separator->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_target_output_clicked, this);

	wxBoxSizer* bs_toolbar_chart_target_output1 = new wxBoxSizer(wxHORIZONTAL);
	
	bs_toolbar_chart_target_output1->Add(cb_target_for_chart, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output1->Add(cb_chart_training_target_output, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output1->Add(cb_chart_validation_target_output, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output1->Add(cb_chart_testing_target_output, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output1->Add(cb_chart_predictions_target_output, 0, wxLEFT, 5);

	wxBoxSizer* bs_toolbar_chart_target_output2 = new wxBoxSizer(wxHORIZONTAL);

	bs_toolbar_chart_target_output2->Add(cb_chart_target, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output2->Add(cb_chart_output, 0, wxLEFT, 5);
	bs_toolbar_chart_target_output2->Add(cb_chart_show_lines, 0, wxLEFT, 30);
	bs_toolbar_chart_target_output2->Add(cb_chart_show_separator, 0, wxLEFT, 5);

	wxBoxSizer* bs_toolbar_chart_target_output = new wxBoxSizer(wxVERTICAL);
	bs_toolbar_chart_target_output->Add(bs_toolbar_chart_target_output1, 0, 0, 0);
	bs_toolbar_chart_target_output->Add(bs_toolbar_chart_target_output2, 0, wxTOP, 5);
	
	p_chart_target_output = new wxPanel(p_chart_with_menu, -1, wxDefaultPosition, wxSize(350, 100));
	p_chart_target_output->SetCursor(*wxCROSS_CURSOR);

	p_chart_target_output->Bind(wxEVT_SIZE, &t_main_window::on_resize_chart_target_output, this);
	p_chart_target_output->Bind(wxEVT_PAINT, &t_main_window::on_paint_chart_output_target, this);

	wxBoxSizer* bs_toolbar_and_chart_target_output = new wxBoxSizer(wxVERTICAL);
	bs_toolbar_and_chart_target_output->Add(bs_toolbar_chart_target_output, 0, wxTOP | wxBOTTOM, 5);
	bs_toolbar_and_chart_target_output->Add(p_chart_target_output, 1, wxEXPAND, 0);

	p_chart_with_menu->SetSizer(bs_toolbar_and_chart_target_output);

}
//-----------------------------------------------------------------------------------------
void t_main_window::build_panel_code(wxPanel* p_code)
{
	st_code = new wxStaticText(p_code, -1, "Code");

	wxString language_choices[5] = { "C/C++", "Excel VBA", "Python", "C/C++ Infix", "Latex" };
	cb_language = new wxComboBox(p_code, -1, language_choices[0], wxDefaultPosition, wxDefaultSize, 5, language_choices, wxCB_READONLY);
	cb_language->Bind(wxEVT_COMBOBOX, &t_main_window::on_code_language_changed, this);

	cb_simplified_code = new wxCheckBox(p_code, -1, "Simplified");
	cb_simplified_code->Bind(wxEVT_CHECKBOX, &t_main_window::on_simplified_code_clicked, this);

	b_save_code = new wxButton(p_code, -1, "Save");
	wxBitmap bmp_save(save_16x16_xpm);
	b_save_code->SetBitmap(bmp_save);
	b_save_code->Bind(wxEVT_BUTTON, &t_main_window::on_save_code_button_clicked, this);

	wxBitmap bmp_clipboard(clipboard_16x16_xpm);
	b_to_clipboard_code = new wxButton(p_code, -1, "To Clipboard");
	b_to_clipboard_code->SetBitmap(bmp_clipboard);
	b_to_clipboard_code->Bind(wxEVT_BUTTON, &t_main_window::on_to_clipboard_code_button_clicked, this);

	wxBoxSizer* bs_toolbar_code = new wxBoxSizer(wxHORIZONTAL);
	bs_toolbar_code->Add(st_code, 0, wxCENTER | wxRIGHT | wxLEFT, 5);
	bs_toolbar_code->Add(cb_language, 0, wxCENTER | wxRIGHT | wxLEFT, 5);
	bs_toolbar_code->Add(cb_simplified_code, 0, wxCENTER | wxRIGHT, 5);
	bs_toolbar_code->Add(b_save_code);
	bs_toolbar_code->Add(b_to_clipboard_code);

	tc_source_code = new wxTextCtrl(p_code, -1, "", wxDefaultPosition, wxSize(10, 100), wxTE_READONLY | wxTE_MULTILINE);
	tc_source_code->SetEditable(false);

	wxBoxSizer* bs_code = new wxBoxSizer(wxVERTICAL);
	bs_code->Add(bs_toolbar_code, 0, 0, 0);
	bs_code->Add(tc_source_code, 1, wxEXPAND, 0);

	p_code->SetSizer(bs_code);
}
//-----------------------------------------------------------------------------------------
void t_main_window::build_runs_evolution_panel(void)
{
	splitter_stats_evolution = new wxSplitterWindow(p_runs);
	splitter_stats_evolution->SetSplitMode(wxSPLIT_HORIZONTAL);
	splitter_stats_evolution->SetMinimumPaneSize(100);

	// stats
	wxPanel* p_stats = new wxPanel(splitter_stats_evolution, -1, wxDefaultPosition, wxSize(350, 100));

	// menu
	st_runs_errors = new wxStaticText(p_stats, -1, s_runs_errors_label_classification);
	b_save_stats = new wxButton(p_stats, -1, "Save");
	wxBitmap bmp_save(save_16x16_xpm);
	b_save_stats->SetBitmap(bmp_save);
	b_save_stats->Bind(wxEVT_BUTTON, &t_main_window::on_save_stats_button_clicked, this);

	sizer_toolbar_stats = new wxBoxSizer(wxHORIZONTAL);
	sizer_toolbar_stats->Add(st_runs_errors, 0, wxCENTER | wxLEFT | wxRIGHT, 5);
	sizer_toolbar_stats->Add(b_save_stats);//, 0, wxEXPAND);
	// stats list view
	g_stats = new t_list_view_stats_errors(p_stats, &run_errors);


	g_stats->Bind(wxEVT_LIST_ITEM_SELECTED, &t_main_window::on_stats_row_change, this);
	wxBoxSizer* sizer_stats = new wxBoxSizer(wxVERTICAL);
	sizer_stats->Add(sizer_toolbar_stats, 0, wxEXPAND, 0);
	sizer_stats->Add(g_stats, 1, wxEXPAND, 0);

	p_stats->SetSizer(sizer_stats);

	// evolution chart
	wxPanel* p_chart_evolution_with_menu = new wxPanel(splitter_stats_evolution, -1, wxDefaultPosition, wxSize(350, 100));
	// menu

	wxStaticText* st_evolution = new wxStaticText(p_chart_evolution_with_menu, -1, "Error evolution");
	cb_pop_average_evolution = new wxCheckBox(p_chart_evolution_with_menu, -1, "Average");
	cb_validation_evolution = new wxCheckBox(p_chart_evolution_with_menu, -1, "Validation");
	cb_pop_average_evolution->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_evolution_clicked, this);
	cb_validation_evolution->Bind(wxEVT_CHECKBOX, &t_main_window::on_chart_evolution_clicked, this);

	wxBoxSizer* sizer_toolbar_evolution = new wxBoxSizer(wxHORIZONTAL);
	sizer_toolbar_evolution->Add(st_evolution, 0, wxLEFT | wxRIGHT, 5);
	sizer_toolbar_evolution->Add(cb_pop_average_evolution, 0, wxLEFT | wxRIGHT, 5);
	sizer_toolbar_evolution->Add(cb_validation_evolution);
	// evolution panel
	p_chart_evolution = new wxPanel(p_chart_evolution_with_menu, -1, wxDefaultPosition, wxSize(350, 100));
	p_chart_evolution->SetCursor(*wxCROSS_CURSOR);
	p_chart_evolution->Bind(wxEVT_SIZE, &t_main_window::on_resize_chart_evolution, this);
	p_chart_evolution->Bind(wxEVT_PAINT, &t_main_window::on_paint_chart_evolution, this);

	wxBoxSizer* sizer_evolution = new wxBoxSizer(wxVERTICAL);
	sizer_evolution->Add(sizer_toolbar_evolution, 0, 0, 0);
	sizer_evolution->Add(p_chart_evolution, 1, wxEXPAND, 0);

	p_chart_evolution_with_menu->SetSizer(sizer_evolution);

	splitter_stats_evolution->SplitHorizontally(p_stats, p_chart_evolution_with_menu);

	wxBoxSizer* sizer_stats_evolution = new wxBoxSizer(wxVERTICAL);
	sizer_stats_evolution->Add(splitter_stats_evolution, 1, wxEXPAND, 0);

	p_runs->SetSizer(sizer_stats_evolution);
}
//-----------------------------------------------------------------------------------------
void t_main_window::build_code_chart_panel(wxPanel* p_code_chart)
{
	splitter_code_graphics = new wxSplitterWindow(p_code_chart);
	splitter_code_graphics->SetSplitMode(wxSPLIT_HORIZONTAL);
	splitter_code_graphics->SetMinimumPaneSize(100);

	wxPanel* p_code = new wxPanel(splitter_code_graphics, -1, wxDefaultPosition, wxSize(350, 100));

	build_panel_code(p_code);

	wxPanel* p_chart_with_menu = new wxPanel(splitter_code_graphics, -1, wxDefaultPosition, wxSize(350, 100));

	build_panel_chart(p_chart_with_menu);

	splitter_code_graphics->SplitHorizontally(p_code, p_chart_with_menu);

	wxBoxSizer* bs_code_chart = new wxBoxSizer(wxVERTICAL);
	bs_code_chart->Add(splitter_code_graphics, 1, wxEXPAND, 0);

	p_code_chart->SetSizer(bs_code_chart);
}
//-----------------------------------------------------------------------------------------

void t_main_window::build_results_model_code_chart_panel(void)
{
	splitter_charts_code = new wxSplitterWindow(p_results);
	splitter_charts_code->SetSplitMode(wxSPLIT_VERTICAL);
	splitter_charts_code->SetMinimumPaneSize(100);

	wxPanel* p_errors_table = new wxPanel(splitter_charts_code, -1, wxDefaultPosition, wxSize(300, -1));

	build_panel_error_tables(p_errors_table);


	wxPanel* p_code_chart = new wxPanel(splitter_charts_code, -1, wxDefaultPosition, wxSize(300, 500));
	// panel generated code

	build_code_chart_panel(p_code_chart);

	splitter_charts_code->SplitVertically(p_errors_table, p_code_chart);

	wxBoxSizer* bs_results_tables_code = new wxBoxSizer(wxHORIZONTAL);
	bs_results_tables_code->Add(splitter_charts_code, 1, wxEXPAND, 0);
	p_results->SetSizer(bs_results_tables_code);

}
//-----------------------------------------------------------------------------------------
void t_main_window::create_results_ui(void)
{
	///////////////////////////////////////////////////////////////////////////////
	//results
	///////////////////////////////////////////////////////////////////////////////
	w_results = new wxWindow(n_settings, -1);

	splitter_runs_results = new wxSplitterWindow(w_results);
	splitter_runs_results->SetSplitMode(wxSPLIT_VERTICAL);
	splitter_runs_results->SetMinimumPaneSize(100);

	p_runs = new wxPanel(splitter_runs_results, -1, wxDefaultPosition, wxSize(300, 500));
	// panel runs

	build_runs_evolution_panel();

	// panel results
	p_results = new wxPanel(splitter_runs_results, -1, wxDefaultPosition, wxSize(300, 500));
	build_results_model_code_chart_panel();

	splitter_runs_results->SplitVertically(p_runs, p_results);

	wxBoxSizer* bs_results_main = new wxBoxSizer(wxVERTICAL);
	bs_results_main->Add(splitter_runs_results, 1, wxEXPAND, 0);

	w_results->SetSizer(bs_results_main);
}
//-----------------------------------------------------------------------------------------
