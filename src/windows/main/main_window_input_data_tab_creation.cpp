// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//---------------------------------------------------------------------
#include "open_16x16.xpm"
#include "delete_16x16.xpm"
#include "save_16x16.xpm"
#include "replace_16x16.xpm"
#include "arrow-left_16x16.xpm"
#include "arrow-right_16x16.xpm"
#include "numbers.xpm"
#include "resize.xpm"
#include "find_16x16.xpm"
#include "shuffle_16x16.xpm"
//#include "clipboard_16x16.xpm"
#include "paste_16.xpm"
#include "time_serie2_16.xpm"
#include "three_dots_16.xpm"
//---------------------------------------------------------------------
void t_main_window::create_data_ui(void)
{
	m_training_columns = new wxMenu;
	mi_use_column = m_training_columns->AppendCheckItem(wxMENUBASE + 0, "Utilized");
	//mi_rename_column = m_training_columns->AppendCheckItem(wxMENUBASE + 1, "Rename...");

	Connect(wxMENUBASE + 0, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(t_main_window::on_use_columns_clicked));
	//Connect(wxMENUBASE + 1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(t_main_window::on_rename_column_clicked));

	
	//data
	w_data = new wxWindow(n_settings, -1);

	n_data = new wxNotebook(w_data, -1);
	n_data->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &t_main_window::on_change_data_page, this);

	wxPanel* p_training = new wxPanel(n_data);

	wxPanel* p_advanced_data = new wxPanel(n_data);

	b_load_training_data = new wxButton(p_training, -1, "Load training data");
	wxBitmap bmp_load(open_16x16_xpm);
	b_load_training_data->SetBitmap(bmp_load);
	b_load_training_data->Bind(wxEVT_BUTTON, &t_main_window::on_load_training_data_button_clicked, this);

	b_clear_training_data = new wxButton(p_training, -1, "Delete training data");
	wxBitmap bmp_new(delete_16x16_xpm);
	b_clear_training_data->SetBitmap(bmp_new);
	b_clear_training_data->Bind(wxEVT_BUTTON, &t_main_window::on_clear_training_data_button_clicked, this);

	b_save_training_data = new wxButton(p_training, -1, "Export training data");
	wxBitmap bmp_save(save_16x16_xpm);
	b_save_training_data->SetBitmap(bmp_save);
	b_save_training_data->Bind(wxEVT_BUTTON, &t_main_window::on_save_data_button_clicked, this);


	b_find_symbol_training = new wxButton(p_training, -1, "Find values");
	wxBitmap bmp_find(find_16x16_xpm);
	b_find_symbol_training->SetBitmap(bmp_find);
	b_find_symbol_training->SetToolTip("Search for a particular value in the dataset");
	b_find_symbol_training->Bind(wxEVT_BUTTON, &t_main_window::on_find_symbol_button_clicked, this);

	b_replace_symbol_training = new wxButton(p_training, -1, "Replace values");
	wxBitmap bmp_replace(replace_16x16_xpm);
	b_replace_symbol_training->SetBitmap(bmp_replace);
	b_replace_symbol_training->SetToolTip("Replace a value with another value");
	b_replace_symbol_training->Bind(wxEVT_BUTTON, &t_main_window::on_replace_symbol_button_clicked, this);

	b_shuffle_training = new wxButton(p_training, -1, "Shuffle");
	wxBitmap bmp_shuffle(shuffle_16x16_xpm);
	b_shuffle_training->SetBitmap(bmp_shuffle);
	b_shuffle_training->SetToolTip("Randomly re-order the rows in the dataset");
	b_shuffle_training->Bind(wxEVT_BUTTON, &t_main_window::on_shuffle_data_button_clicked, this);

	b_move_training_to_test = new wxButton(p_training, -1, "Move to test");
	wxBitmap bmp_arrow_right(arrow_right_16x16_xpm);
	b_move_training_to_test->SetBitmap(bmp_arrow_right);
	b_move_training_to_test->SetToolTip("Move some data to training set");
	b_move_training_to_test->Bind(wxEVT_BUTTON, &t_main_window::on_move_training_to_test_button_clicked, this);

	b_move_training_to_validation = new wxButton(p_training, -1, "Move to validation");
	b_move_training_to_validation->SetBitmap(bmp_arrow_right);
	b_move_training_to_validation->SetToolTip("Move some data to validation set");
	b_move_training_to_validation->Bind(wxEVT_BUTTON, &t_main_window::on_move_training_to_validation_button_clicked, this);

	b_paste_from_clipboard_training = new wxButton(p_training, -1, "Paste from Clipboard");
	wxBitmap bmp_paste(paste_16_xpm);
	b_paste_from_clipboard_training->SetBitmap(bmp_paste);
	b_paste_from_clipboard_training->SetToolTip("Paste from Clipboard containing data separated by Tab.");
	b_paste_from_clipboard_training->Bind(wxEVT_BUTTON, &t_main_window::on_paste_from_clipboard_training_button_clicked, this);

	b_set_num_outputs_training = new wxButton(p_training, -1, "Num. outputs");
	wxBitmap bmp_three_dots(three_dots_16_xpm);
	b_set_num_outputs_training->SetBitmap(bmp_three_dots);
	b_set_num_outputs_training->SetToolTip("Set the number of outputs.");
	b_set_num_outputs_training->Bind(wxEVT_BUTTON, &t_main_window::on_num_outputs_training_button_clicked, this);


	wxBoxSizer* bs_training_data_commands = new wxBoxSizer(wxVERTICAL);

	bs_training_data_commands->Add(b_load_training_data, 0, wxEXPAND | wxTOP, 10);
	bs_training_data_commands->Add(b_clear_training_data, 0, wxEXPAND | wxTOP, 2);
	bs_training_data_commands->Add(b_save_training_data, 0, wxEXPAND | wxTOP, 2);

	bs_training_data_commands->Add(b_find_symbol_training, 0, wxEXPAND | wxTOP, 10);
	bs_training_data_commands->Add(b_replace_symbol_training, 0, wxEXPAND | wxTOP, 2);

	bs_training_data_commands->Add(b_shuffle_training, 0, wxEXPAND | wxTOP, 10);

	bs_training_data_commands->Add(b_move_training_to_test, 0, wxEXPAND | wxTOP, 10);
	bs_training_data_commands->Add(b_move_training_to_validation, 0, wxEXPAND | wxTOP, 2);

	bs_training_data_commands->Add(b_paste_from_clipboard_training, 0, wxEXPAND | wxTOP, 10);
	bs_training_data_commands->Add(b_set_num_outputs_training, 0, wxEXPAND | wxTOP, 10);
	
	//bs_training_data_commands->Add(b_to_time_serie_training, 0, wxEXPAND | wxTOP, 10);

	g_training_data = new t_list_view_data(p_training,
										   mep_engine.get_training_data_ptr(),
										   true);

	g_training_data->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &t_main_window::on_training_grid_header_right_clicked, this);

	wxPanel* p_validation = new wxPanel(n_data);

	// validation
	b_load_validation_data = new wxButton(p_validation, -1, "Load validation data");
	b_load_validation_data->SetBitmap(bmp_load);
	b_load_validation_data->Bind(wxEVT_BUTTON, &t_main_window::on_load_validation_data_button_clicked, this);

	b_clear_validation_data = new wxButton(p_validation, -1, "Delete validation data");
	b_clear_validation_data->SetBitmap(bmp_new);
	b_clear_validation_data->Bind(wxEVT_BUTTON, &t_main_window::on_clear_validation_data_button_clicked, this);

	b_save_validation_data = new wxButton(p_validation, -1, "Export validation data");
	b_save_validation_data->SetBitmap(bmp_save);
	b_save_validation_data->Bind(wxEVT_BUTTON, &t_main_window::on_save_data_button_clicked, this);

	b_find_symbol_validation = new wxButton(p_validation, -1, "Find values");
	b_find_symbol_validation->SetBitmap(bmp_find);
	b_find_symbol_validation->SetToolTip("Search for a particular value in the dataset");
	b_find_symbol_validation->Bind(wxEVT_BUTTON, &t_main_window::on_find_symbol_button_clicked, this);

	b_replace_symbol_validation = new wxButton(p_validation, -1, "Replace values");
	b_replace_symbol_validation->SetBitmap(bmp_replace);
	b_replace_symbol_validation->SetToolTip("Replace a value with another value");
	b_replace_symbol_validation->Bind(wxEVT_BUTTON, &t_main_window::on_replace_symbol_button_clicked, this);

	b_move_validation_to_training = new wxButton(p_validation, -1, "Move to training");
	wxBitmap bmp_arrow_left(arrow_left_16x16_xpm);
	b_move_validation_to_training->SetBitmap(bmp_arrow_left);
	b_move_validation_to_training->SetToolTip("Move some data to training set");
	b_move_validation_to_training->Bind(wxEVT_BUTTON, &t_main_window::on_move_validation_to_training_button_clicked, this);

	b_paste_from_clipboard_validation = new wxButton(p_validation, -1, "Paste from Clipboard");
	b_paste_from_clipboard_validation->SetBitmap(bmp_paste);
	b_paste_from_clipboard_validation->SetToolTip("Paste from Clipboard containing data separated by Tab.");
	b_paste_from_clipboard_validation->Bind(wxEVT_BUTTON, &t_main_window::on_paste_from_clipboard_validation_button_clicked, this);

	wxBoxSizer* bs_validation_data_commands = new wxBoxSizer(wxVERTICAL);

	bs_validation_data_commands->Add(b_load_validation_data, 0, wxEXPAND | wxTOP, 10);
	bs_validation_data_commands->Add(b_clear_validation_data, 0, wxEXPAND | wxTOP, 2);
	bs_validation_data_commands->Add(b_save_validation_data, 0, wxEXPAND | wxTOP, 2);

	bs_validation_data_commands->Add(b_find_symbol_validation, 0, wxEXPAND | wxTOP, 10);
	bs_validation_data_commands->Add(b_replace_symbol_validation, 0, wxEXPAND | wxTOP, 2);

	bs_validation_data_commands->Add(b_move_validation_to_training, 0, wxEXPAND | wxTOP, 10);

	bs_validation_data_commands->Add(b_paste_from_clipboard_validation, 0, wxEXPAND | wxTOP, 10);
	//bs_validation_data_commands->Add(cb_use_validation_set, 0, wxEXPAND | wxTOP, 10);

	g_validation_data = new t_list_view_data(p_validation,
											 mep_engine.get_validation_data_ptr(),
											 false);


	wxPanel* p_test = new wxPanel(n_data);

	// validation
	b_load_test_data = new wxButton(p_test, -1, "Load test data");
	b_load_test_data->SetBitmap(bmp_load);
	b_load_test_data->Bind(wxEVT_BUTTON, &t_main_window::on_load_test_data_button_clicked, this);

	b_clear_test_data = new wxButton(p_test, -1, "Delete test data");
	b_clear_test_data->SetBitmap(bmp_new);
	b_clear_test_data->Bind(wxEVT_BUTTON, &t_main_window::on_clear_test_data_button_clicked, this);

	b_save_test_data = new wxButton(p_test, -1, "Export test data");
	b_save_test_data->SetBitmap(bmp_save);
	b_save_test_data->Bind(wxEVT_BUTTON, &t_main_window::on_save_data_button_clicked, this);

	b_find_symbol_test = new wxButton(p_test, -1, "Find values");
	b_find_symbol_test->SetBitmap(bmp_find);
	b_find_symbol_test->SetToolTip("Search for a particular value in the dataset");
	b_find_symbol_test->Bind(wxEVT_BUTTON, &t_main_window::on_find_symbol_button_clicked, this);

	b_replace_symbol_test = new wxButton(p_test, -1, "Replace values");
	b_replace_symbol_test->SetBitmap(bmp_replace);
	b_replace_symbol_test->Bind(wxEVT_BUTTON, &t_main_window::on_replace_symbol_button_clicked, this);
	b_replace_symbol_test->SetToolTip("Replace a value with another value");

	b_move_test_to_training = new wxButton(p_test, -1, "Move to training");
	b_move_test_to_training->SetBitmap(bmp_arrow_left);
	b_move_test_to_training->Bind(wxEVT_BUTTON, &t_main_window::on_move_test_to_training_button_clicked, this);
	b_move_test_to_training->SetToolTip("Move some data to training data.");

	b_paste_from_clipboard_test = new wxButton(p_test, -1, "Paste from Clipboard");
	b_paste_from_clipboard_test->SetBitmap(bmp_paste);
	b_paste_from_clipboard_test->SetToolTip("Paste from Clipboard containing data separated by Tab.");
	b_paste_from_clipboard_test->Bind(wxEVT_BUTTON, &t_main_window::on_paste_from_clipboard_test_button_clicked, this);

	wxBoxSizer* bs_test_data_commands = new wxBoxSizer(wxVERTICAL);

	bs_test_data_commands->Add(b_load_test_data, 0, wxEXPAND | wxTOP, 10);
	bs_test_data_commands->Add(b_clear_test_data, 0, wxEXPAND | wxTOP, 2);
	bs_test_data_commands->Add(b_save_test_data, 0, wxEXPAND | wxTOP, 2);

	bs_test_data_commands->Add(b_find_symbol_test, 0, wxEXPAND | wxTOP, 10);
	bs_test_data_commands->Add(b_replace_symbol_test, 0, wxEXPAND | wxTOP, 2);

	bs_test_data_commands->Add(b_move_test_to_training, 0, wxEXPAND | wxTOP, 10);

	bs_test_data_commands->Add(b_paste_from_clipboard_test, 0, wxEXPAND | wxTOP, 10);

	g_test_data = new t_list_view_data(p_test,
									   mep_engine.get_test_data_ptr(),
									   false);

	// advanced commands

	b_to_numeric_data = new wxButton(p_advanced_data, -1, "To numeric");
	wxBitmap bmp_numbers(numbers_xpm);
	b_to_numeric_data->SetBitmap(bmp_numbers);
	b_to_numeric_data->SetToolTip("Convert alpha-numerical data to a numerical values.");
	b_to_numeric_data->Bind(wxEVT_BUTTON, &t_main_window::on_to_numeric_data_button_clicked, this);

	b_scale_data = new wxButton(p_advanced_data, -1, "Scale");
	wxBitmap bmp_resize(resize_xpm);
	b_scale_data->SetBitmap(bmp_resize);
	b_scale_data->SetToolTip("Scale data to a given interval.");
	b_scale_data->Bind(wxEVT_BUTTON, &t_main_window::on_scale_data_button_clicked, this);

	b_save_all_data = new wxButton(p_advanced_data, -1, "Export all data");
	b_save_all_data->SetBitmap(bmp_save);
	b_save_all_data->Bind(wxEVT_BUTTON, &t_main_window::on_save_all_data_button_clicked, this);

	/*
	b_to_time_series = new wxButton(p_advanced_data, -1, "To time serie");
	wxBitmap bmp_time_serie(time_serie2_16_xpm);
	b_to_time_series->SetBitmap(bmp_time_serie);
	b_to_time_series->Bind(wxEVT_BUTTON, &t_main_window::on_time_serie_button_clicked, this);
	b_to_time_series->SetToolTip("Transform a vector data to a matrix based on the <<window size>> parameter.");

	b_change_window_size = new wxButton(p_advanced_data, -1, "Change window size");
	//wxBitmap bmp_time_serie(time_serie2_16_xpm);
	b_change_window_size->SetBitmap(bmp_time_serie);
	b_change_window_size->Bind(wxEVT_BUTTON, &t_main_window::on_change_window_size_button_clicked, this);
	b_change_window_size->SetToolTip("Change the window size of a time serie.");
	*/
	wxBoxSizer* bs_advanced_data_commands = new wxBoxSizer(wxVERTICAL);

	bs_advanced_data_commands->Add(b_to_numeric_data, 0, wxEXPAND | wxTOP, 10);
	bs_advanced_data_commands->Add(b_scale_data, 0, wxEXPAND | wxTOP, 10);
	bs_advanced_data_commands->Add(b_save_all_data, 0, wxEXPAND | wxTOP, 10);

	tc_problem_description = new wxTextCtrl(n_data, -1, "Problem description here ...", wxDefaultPosition, wxSize(-1, 200), wxTE_MULTILINE | wxTE_PROCESS_TAB);
	tc_problem_description->Bind(wxEVT_TEXT, &t_main_window::on_change_problem_description, this);

	wxBoxSizer* bs_training = new wxBoxSizer(wxHORIZONTAL);
	bs_training->Add(bs_training_data_commands, 0, wxRIGHT, 3);
	bs_training->Add(g_training_data, 1, wxEXPAND, 0);
	p_training->SetSizer(bs_training);

	n_data->AddPage(p_training, "Training data", true, -1);

	wxBoxSizer* bs_validation = new wxBoxSizer(wxHORIZONTAL);
	bs_validation->Add(bs_validation_data_commands, 0, wxRIGHT, 3);
	bs_validation->Add(g_validation_data, 1, wxEXPAND, 0);
	p_validation->SetSizer(bs_validation);

	n_data->AddPage(p_validation, "Validation data", false, -1);

	wxBoxSizer* bs_test = new wxBoxSizer(wxHORIZONTAL);
	bs_test->Add(bs_test_data_commands, 0, wxRIGHT, 3);
	bs_test->Add(g_test_data, 1, wxEXPAND, 0);
	p_test->SetSizer(bs_test);

	n_data->AddPage(p_test, "Test data", false, -1);

	wxBoxSizer* bs_advanced_data = new wxBoxSizer(wxHORIZONTAL);
	bs_advanced_data->Add(bs_advanced_data_commands, 0, 0, 0);
	p_advanced_data->SetSizer(bs_advanced_data);

	n_data->AddPage(p_advanced_data, "Advanced commands", false, -1);

	n_data->AddPage(tc_problem_description, "Problem description", false, -1);

	wxBoxSizer* sizer_data = new wxBoxSizer(wxVERTICAL);
	//sizer_data->Add(bs_data_commands, 0, 0, 0);
	sizer_data->Add(n_data, 1, wxEXPAND, 0);

	w_data->SetSizer(sizer_data);
}
