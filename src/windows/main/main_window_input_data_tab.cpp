// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <wx/numdlg.h>
#include <wx/filename.h>
#include <wx/clipbrd.h>
//---------------------------------------------------------------------
#include "windows/main_window.h"
#include "windows/import_data_window.h"
#include "windows/decimal_separator_selector_window.h"
#include "mepx_project.h"
#include "utils/data_separators.h"
#include "utils/time_utils.h"
//---------------------------------------------------------------------
void t_main_window::update_num_target_cols_to_data_grids(void)
{
	g_training_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	g_training_data->update_num_rows_cols();
	
	g_validation_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	g_validation_data->update_num_rows_cols();
	
	if (mep_engine.get_training_data_ptr()->get_num_cols() ==
		mep_engine.get_test_data_ptr()->get_num_cols())
		g_test_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	else
		g_test_data->num_outputs = 0;
	g_test_data->update_num_rows_cols();
}
//---------------------------------------------------------------------
void t_main_window::on_move_training_to_validation_button_clicked(wxCommandEvent&)
{
	int num_moved = (int)wxGetNumberFromUser("Min 1; Max " + wxString() << mep_engine.get_training_data_ptr()->get_num_rows(), "Last: ", "How many to move", 1, 1, mep_engine.get_training_data_ptr()->get_num_rows());
	if (num_moved != -1) {
		int result = mep_engine.get_training_data_ptr()->move_to(mep_engine.get_validation_data_ptr(), num_moved);
		switch (result) {
		case E_MEP_OK:
			wxWindow::SetCursor(wxCURSOR_WAIT);
			g_training_data->update_num_rows_cols();
			g_validation_data->update_num_rows_cols();

			update_validation_buttons();
			update_training_buttons();

			clear_results();

			b_save_project->Enable(true);
			//st_project_name->SetForegroundColour(wxColour(0x0000FF));
			//st_project_name->Refresh();

			wxWindow::SetCursor(wxNullCursor);
			break;
		case E_MEP_CANNOT_MOVE_DATA_OF_DIFFERENT_TYPES:
			wxMessageBox("Data have different type (string or numeric)", "Error");
			break;
		case E_MEP_NOT_ENOUGH_DATA_TO_MOVE:
			wxMessageBox("E_NOT_ENOUGH_DATA_TO_MOVE", "Error");
			break;
		case E_MEP_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_COLUMNS:
			wxMessageBox("E_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_OUTPUTS", "Error");
			break;
		}
	}
}
//---------------------------------------------------------------------
void t_main_window::on_move_training_to_test_button_clicked(wxCommandEvent&)
{
	int num_moved = (int)wxGetNumberFromUser("Min 1; Max " + wxString() << mep_engine.get_training_data_ptr()->get_num_rows(), "Last: ", "How many to move", 1, 1, mep_engine.get_training_data_ptr()->get_num_rows());
	if (num_moved != -1) {
		int result = mep_engine.get_training_data_ptr()->move_to(mep_engine.get_test_data_ptr(), num_moved);
		switch (result) {
		case E_MEP_OK:
			wxWindow::SetCursor(wxCURSOR_WAIT);

			g_training_data->update_num_rows_cols();
				
			if (mep_engine.get_training_data_ptr()->get_num_cols() ==
				mep_engine.get_test_data_ptr()->get_num_cols())
				g_test_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
			else
				g_test_data->num_outputs = 0;
				
			g_test_data->update_num_rows_cols();

			update_test_buttons();
			update_training_buttons();

			clear_results();

			b_save_project->Enable(true);
			//st_project_name->SetForegroundColour(wxColour(0x0000FF));
			//st_project_name->Refresh();

			wxWindow::SetCursor(wxNullCursor);
			break;
		case E_MEP_CANNOT_MOVE_DATA_OF_DIFFERENT_TYPES:
			wxMessageBox("Data have different type (string or numeric)", "Error");
			break;
		case E_MEP_NOT_ENOUGH_DATA_TO_MOVE:
			wxMessageBox("E_NOT_ENOUGH_DATA_TO_MOVE", "Error");
			break;
		case E_MEP_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_COLUMNS:
			wxMessageBox("E_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_OUTPUTS", "Error");
			break;
		}
	}
}
//---------------------------------------------------------------------
void t_main_window::on_move_validation_to_training_button_clicked(wxCommandEvent&)
{
	int num_moved = (int)wxGetNumberFromUser("Min 1; Max " + wxString() << mep_engine.get_validation_data_ptr()->get_num_rows(), "Last: ", "How many to move", 1, 1, mep_engine.get_validation_data_ptr()->get_num_rows());
	if (num_moved != -1) {
		int result = mep_engine.get_validation_data_ptr()->move_to(mep_engine.get_training_data_ptr(), num_moved);

		switch (result) {
		case E_MEP_OK:
			wxWindow::SetCursor(wxCURSOR_WAIT);

			if (mep_engine.get_num_total_variables() != mep_engine.get_training_data_ptr()->get_num_cols() - mep_engine.get_parameters_ptr()->get_num_outputs()) {
				mep_engine.init_enabled_variables();
				set_enabled_grid_columns();
			}

			g_training_data->update_num_rows_cols();
			g_validation_data->update_num_rows_cols();

			update_validation_buttons();
			update_training_buttons();

			clear_results();

			b_save_project->Enable(true);
			//st_project_name->SetForegroundColour(wxColour(0x0000FF));
			//st_project_name->Refresh();

			wxWindow::SetCursor(wxNullCursor);
			break;
		case E_MEP_CANNOT_MOVE_DATA_OF_DIFFERENT_TYPES:
			wxMessageBox("Data have different type (string or numeric)", "Error");
			break;
		case E_MEP_NOT_ENOUGH_DATA_TO_MOVE:
			wxMessageBox("E_NOT_ENOUGH_DATA_TO_MOVE", "Error");
			break;
		case E_MEP_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_COLUMNS:
			wxMessageBox("E_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_OUTPUTS", "Error");
			break;
		}
	}
}
//---------------------------------------------------------------------
void t_main_window::on_move_test_to_training_button_clicked(wxCommandEvent&)
{
	int num_moved = (int)wxGetNumberFromUser("Min 1; Max " + wxString() << mep_engine.get_test_data_ptr()->get_num_rows(), "Last: ", "How many to move", 1, 1, mep_engine.get_test_data_ptr()->get_num_rows());
	if (num_moved != -1) {
		int result = mep_engine.get_test_data_ptr()->move_to(mep_engine.get_training_data_ptr(), num_moved);
		switch (result) {
		case E_MEP_OK:
			wxWindow::SetCursor(wxCURSOR_WAIT);

			if (mep_engine.get_num_total_variables() != mep_engine.get_training_data_ptr()->get_num_cols() -
													mep_engine.get_parameters_ptr()->get_num_outputs()){
				mep_engine.init_enabled_variables();
				set_enabled_grid_columns();
			}

			g_training_data->update_num_rows_cols();
			g_test_data->update_num_rows_cols();

			update_test_buttons();
			update_training_buttons();

			clear_results();

			b_save_project->Enable(true);
			//st_project_name->SetForegroundColour(wxColour(0x0000FF));
			//st_project_name->Refresh();

			wxWindow::SetCursor(wxNullCursor);
			break;
		case E_MEP_CANNOT_MOVE_DATA_OF_DIFFERENT_TYPES:
			wxMessageBox("Data have different type (string or numeric)", "Error");
			break;
		case E_MEP_NOT_ENOUGH_DATA_TO_MOVE:
			wxMessageBox("E_NOT_ENOUGH_DATA_TO_MOVE", "Error");
			break;
		case E_MEP_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_COLUMNS:
			wxMessageBox("E_DEST_AND_SOURCE_MUST_HAVE_THE_SAME_NUMBER_OF_OUTPUTS", "Error");
			break;
		}
	}
}
//------------------------------------------------------------------
void t_main_window::on_to_numeric_data_button_clicked(wxCommandEvent&)
{
	struct lconv* lc;
	lc = localeconv();
	char system_decimal_separator = '.';
	if (lc->decimal_point && lc->decimal_point[0])
		system_decimal_separator = lc->decimal_point[0];
	
	if (system_decimal_separator == '.')
		f_decimal_separator_selector_window->rb_decimal_separator->SetSelection(DECIMAL_SEPARATOR_DOT);
	else
		f_decimal_separator_selector_window->rb_decimal_separator->SetSelection(DECIMAL_SEPARATOR_SYSTEM);

	f_decimal_separator_selector_window->CenterOnParent();
	if (f_decimal_separator_selector_window->ShowModal() != wxID_OK)
		return;

	char decimal_separator;
	f_decimal_separator_selector_window->get_separator(decimal_separator);

	wxWindow::SetCursor(wxCURSOR_WAIT);
	int result = mep_engine.get_training_data_ptr()->from_string_automatic_replace_to_numeric_per_column_all(
																					   mep_engine.get_validation_data_ptr(),
															 mep_engine.get_test_data_ptr(),
															 decimal_separator,
																					   mep_engine.get_parameters_ptr()->get_data_type());

	switch (result) {
	case E_MEP_DATA_MUST_HAVE_STRING_TYPE:
		wxMessageBox("Data have different type (string or numeric)", "Error");
		break;
	}

	g_training_data->Refresh();
	g_test_data->Refresh();
	g_validation_data->Refresh();

	update_advance_commands_buttons();

	update_training_buttons();
	update_validation_buttons();
	update_test_buttons();

	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();

	wxWindow::SetCursor(wxNullCursor);
}
//---------------------------------------------------------------------
void t_main_window::on_clear_test_data_button_clicked(wxCommandEvent&)
{
	mep_engine.get_test_data_ptr()->clear_data();
	update_test_buttons();
	clear_results(); // here I should only update the results on test !!!!!!!!!!!! not delete them completelly

	g_test_data->update_num_rows_cols();
}
//---------------------------------------------------------------------
void t_main_window::on_clear_training_data_button_clicked(wxCommandEvent&)
{
	mep_engine.get_training_data_ptr()->clear_data();
	update_training_buttons();
	clear_results();

	g_training_data->update_num_rows_cols();

}
//---------------------------------------------------------------------
void t_main_window::on_clear_validation_data_button_clicked(wxCommandEvent&)
{
	mep_engine.get_validation_data_ptr()->clear_data();
	update_validation_buttons();
	clear_results();

	g_validation_data->update_num_rows_cols();
}
//---------------------------------------------------------------------
void t_main_window::set_project_info(void)
{
	update_training_buttons();
	update_validation_buttons();
	update_test_buttons();
}
//-----------------------------------------------------------
void t_main_window::update_training_buttons(void)
{
	b_load_training_data->Enable(true);
	b_paste_from_clipboard_training->Enable(true);

	if (mep_engine.get_training_data_ptr()->get_num_rows() == 0) {
		b_replace_symbol_training->Enable(false);
		b_find_symbol_training->Enable(false);
		b_move_training_to_validation->Enable(false);
		b_move_training_to_test->Enable(false);
		b_save_training_data->Enable(false);
		b_clear_training_data->Enable(false);
		b_shuffle_training->Enable(false);
		b_set_num_outputs_training->Enable(false);
	}
	else {
		if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
			b_shuffle_training->Enable(true);
		}
		else {
			b_shuffle_training->Enable(false);
		}
		b_move_training_to_validation->Enable(true);
		b_move_training_to_test->Enable(true);
		b_save_training_data->Enable(true);
		b_clear_training_data->Enable(true);

		b_replace_symbol_training->Enable(true);
		b_find_symbol_training->Enable(true);
		b_set_num_outputs_training->Enable(true);
	}
	//b_to_time_serie_training->Enable(mep_engine.get_training_data_ptr()->is_time_serie());
}
//-----------------------------------------------------------
void t_main_window::update_validation_buttons(void)
{
	b_load_validation_data->Enable(true);
	b_paste_from_clipboard_validation->Enable(true);
	//cb_use_validation_set->Enable(true);

	if (mep_engine.get_validation_data_ptr()->get_num_rows() == 0) {
		b_replace_symbol_validation->Enable(false);
		b_find_symbol_validation->Enable(false);
		b_move_validation_to_training->Enable(false);
		b_save_validation_data->Enable(false);
		b_clear_validation_data->Enable(false);
	}
	else {
		b_move_validation_to_training->Enable(true);

		b_save_validation_data->Enable(true);
		b_clear_validation_data->Enable(true);

		b_replace_symbol_validation->Enable(true);
		b_find_symbol_validation->Enable(true);
	}
}
//-----------------------------------------------------------
void t_main_window::update_test_buttons(void)
{
	b_load_test_data->Enable(true);
	b_paste_from_clipboard_test->Enable(true);

	if (mep_engine.get_test_data_ptr()->get_num_rows() == 0) {
		b_replace_symbol_test->Enable(false);
		b_find_symbol_test->Enable(false);
		b_move_test_to_training->Enable(false);
		b_save_test_data->Enable(false);
		b_clear_test_data->Enable(false);
	}
	else {
		b_move_test_to_training->Enable(true);

		b_save_test_data->Enable(true);
		b_clear_test_data->Enable(true);

		b_replace_symbol_test->Enable(true);
		b_find_symbol_test->Enable(true);
	}
}
//-----------------------------------------------------------
void t_main_window::on_load_training_data_button_clicked(wxCommandEvent&)
{
	if (fd_open_data->ShowModal() != wxID_OK)
		return;     // the user changed idea...

	wxString file_name = fd_open_data->GetPath();
	wxFileName fname;
	fname.Assign(file_name);

	wxString ext = fname.GetExt();

	if (ext.Upper() == "XML") {
		wxMessageBox("This looks like a file containing a project! We suggest to load it by pressing the <<Load Project>> button.", "Info", wxOK);
		return;
	}

	f_import_data_window->file_name = file_name;
	f_import_data_window->data_as_string = NULL;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	// txt, csv, etc
	wxWindow::SetCursor(wxCURSOR_WAIT);
	mep_engine.get_training_data_ptr()->swap_data(f_import_data_window->data);
	
	clear_results();
	mep_engine.get_parameters_ptr()->set_num_outputs(1);
	
	update_num_target_cols_to_data_grids();

	switch (mep_engine.get_training_data_ptr()->get_num_classes()) {
	case 0: // regression
		rb_problem_type->SetSelection(MEP_PROBLEM_REGRESSION);
		break;
	case 2:
		rb_problem_type->SetSelection(MEP_PROBLEM_BINARY_CLASSIFICATION);
		break;
	default:
		rb_problem_type->SetSelection(MEP_PROBLEM_MULTICLASS_CLASSIFICATION);
		break;
	}
	mep_engine.get_parameters_ptr()->set_problem_type(rb_problem_type->GetSelection());
	do_problem_type_changed();

	g_error_training->SetItemCount(mep_engine.get_training_data_ptr()->get_num_rows());
	g_error_training->Refresh();

	wxWindow::SetCursor(wxNullCursor);

	mep_engine.init_enabled_variables();
	set_enabled_grid_columns();

	update_training_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_load_validation_data_button_clicked(wxCommandEvent&)
{
	if (fd_open_data->ShowModal() != wxID_OK)
		return;     // the user changed idea...

	wxString file_name = fd_open_data->GetPath();
	wxFileName fname;
	fname.Assign(file_name);

	wxString ext = fname.GetExt();

	if (ext.Upper() == "XML") {
		wxMessageBox("This looks like a file containing a project! We suggest to load it by pressing the <<Load Project>> button.", "Info", wxOK);
		return;
	}

	f_import_data_window->file_name = file_name;
	f_import_data_window->data_as_string = NULL;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);
	
	mep_engine.get_validation_data_ptr()->swap_data(f_import_data_window->data);

	clear_results();

	g_validation_data->update_num_rows_cols();

	g_error_validation->SetItemCount(mep_engine.get_training_data_ptr()->get_num_rows());
	g_error_validation->Refresh();

	wxWindow::SetCursor(wxNullCursor);

	update_validation_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_load_test_data_button_clicked(wxCommandEvent&)
{
	if (fd_open_data->ShowModal() != wxID_OK)
		return;     // the user changed idea...

	wxString file_name = fd_open_data->GetPath();
	wxFileName fname;
	fname.Assign(file_name);

	wxString ext = fname.GetExt();

	if (ext.Upper() == "XML") {
		wxMessageBox("This looks like a file containing a project! We suggest to load it by pressing the <<Load Project>> button.", "Info", wxOK);
		return;
	}

	f_import_data_window->file_name = file_name;
	f_import_data_window->data_as_string = NULL;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();
	mep_engine.get_test_data_ptr()->swap_data(f_import_data_window->data);
	
	if (mep_engine.get_training_data_ptr()->get_num_cols() ==
		mep_engine.get_test_data_ptr()->get_num_cols())
		g_test_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	else
		g_test_data->num_outputs = 0;

	g_test_data->update_num_rows_cols();

	g_error_testing->SetItemCount(mep_engine.get_training_data_ptr()->get_num_rows());
	g_error_testing->Refresh();

	wxWindow::SetCursor(wxNullCursor);

	update_test_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_change_problem_description(wxCommandEvent&)
{
	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_save_data_button_clicked(wxCommandEvent&)
{
	wxFileDialog
		fd_save_data(this, _("Save files"), "", "",
			"csv files (.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	char* tmp_s = current_time_to_string();

	switch (n_data->GetSelection()) {
		case TRAINING_DATA_PAGE:// training
			fd_save_data.SetFilename("training_data_" + wxString(tmp_s));
			break;
		case VALIDATION_DATA_PAGE:// validation
			fd_save_data.SetFilename("validation_data_" + wxString(tmp_s));
			break;
		case TEST_DATA_PAGE:// testing
			fd_save_data.SetFilename("test_data_" + wxString(tmp_s));
			break;
	}

	delete[]tmp_s;

	if (fd_save_data.ShowModal() != wxID_OK)
		return;

	wxFileName fname;
	fname.Assign(fd_save_data.GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		fname.SetExt("txt");
		ext = "txt";
	}

	switch (n_data->GetSelection()) {
	case TRAINING_DATA_PAGE:// training
		if (mep_engine.get_training_data_ptr()->get_num_rows())
			mep_engine.get_training_data_ptr()->to_tabular_file(fname.GetFullPath().utf8_str(), ' ');
		break;
	case VALIDATION_DATA_PAGE:// validation
		if (mep_engine.get_validation_data_ptr()->get_num_rows())
			mep_engine.get_validation_data_ptr()->to_tabular_file(fname.GetFullPath().utf8_str(), ' ');
		break;
	case TEST_DATA_PAGE:// testing
		if (mep_engine.get_test_data_ptr()->get_num_rows())
			mep_engine.get_test_data_ptr()->to_tabular_file(fname.GetFullPath().utf8_str(), ' ');
		break;
	}
}
//---------------------------------------------------------------------
void t_main_window::on_save_all_data_button_clicked(wxCommandEvent&)
{
	wxFileDialog
		fd_save_data(this, _("Save files"), "", "",
			"csv files (.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	char* tmp_s = current_time_to_string();

	fd_save_data.SetFilename("all_data_" + wxString(tmp_s));

	delete[]tmp_s;

	if (fd_save_data.ShowModal() != wxID_OK)
		return;

	wxFileName fname;
	fname.Assign(fd_save_data.GetPath());

	wxString ext = fname.GetExt();
	if (ext == "") {
		fname.SetExt("txt");
		ext = "txt";
	}

	FILE* f = NULL;
#ifdef _WIN32
	int count_chars = MultiByteToWideChar(CP_UTF8, 0, fname.GetFullPath().utf8_str(), -1, NULL, 0);
	wchar_t* w_filename = new wchar_t[count_chars];
	MultiByteToWideChar(CP_UTF8, 0, fname.GetFullPath().utf8_str(), -1, w_filename, count_chars);

	f = _wfopen(w_filename, L"w");
	delete[] w_filename;

#else
	f = fopen(fname.GetFullPath().utf8_str(), "w");
#endif

	if (!f) {
		wxMessageBox("Cannot save file!", "Error");
		return;
	}

	mep_engine.get_training_data_ptr()->to_tabular_open_file(f, ' ');
	mep_engine.get_validation_data_ptr()->to_tabular_open_file(f, ' ');
	mep_engine.get_test_data_ptr()->to_tabular_open_file(f, ' ');

	fclose(f);
}
//---------------------------------------------------------------------
void t_main_window::on_rename_column_clicked(wxCommandEvent&)
{

}
//---------------------------------------------------------------------
void t_main_window::on_shuffle_data_button_clicked(wxCommandEvent&)
{
	mep_engine.get_training_data_ptr()->shuffle(random_seed);
	g_training_data->Refresh();

	clear_results();


	update_advance_commands_buttons();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_use_columns_clicked(wxCommandEvent&)
{
	wxListItem col;
	col.SetMask(wxLIST_MASK_TEXT);
	g_training_data->GetColumn(right_clicked_col, col);

	if (mi_use_column->IsChecked())
		col.SetText("+x" + wxString::Format("%d", right_clicked_col - 1));
	else
		col.SetText("-x" + wxString::Format("%d", right_clicked_col -1));
    g_training_data->SetColumn(right_clicked_col, col);
	clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_training_grid_header_right_clicked(wxListEvent& event)
{
	if (!mep_engine.get_training_data_ptr()->get_num_rows())
		return;

	right_clicked_col = event.GetColumn();
	wxListItem col;
	col.SetMask(wxLIST_MASK_TEXT);
	//col = event.GetItem();
	if (right_clicked_col > 0 &&
		right_clicked_col <= (int)mep_engine.get_training_data_ptr()->get_num_cols()-
							(int)mep_engine.get_parameters_ptr()->get_num_outputs()) { // ignore target
		mi_use_column->Enable(true);

		if (g_training_data->GetColumn(right_clicked_col, col)) {
			wxString text = col.GetText();
			if (!text.IsEmpty() && text[0] == '-')
				mi_use_column->Check(false);
			else
				mi_use_column->Check(true);

			g_training_data->PopupMenu(m_training_columns);
		}
	}
	else
		mi_use_column->Enable(false);
}
//---------------------------------------------------------------------
void t_main_window::disable_when_start(void)
{
	b_start->Enable(false);
	b_stop->Enable(true);

	b_new_project->Enable(false);
	b_load_project->Enable(false);
	b_save_as_project->Enable(false);
	b_save_project->Enable(false);

	w_parameters->Enable(false);
	/*
	b_load_data->Enable(false);
	b_clear_data->Enable(false);
	*/
	b_save_code->Enable(false);
	b_to_clipboard_code->Enable(false);
	b_save_error_tables->Enable(false);
	//b_copy_error_table->Enable(false);
	b_save_stats->Enable(false);
	//b_copy_stats->Enable(false);
	cb_language->Enable(false);

	cb_simplified_code->Enable(false);

	b_load_training_data->Enable(false);
	b_clear_training_data->Enable(false);
	b_move_training_to_validation->Enable(false);
	b_move_training_to_test->Enable(false);
	b_replace_symbol_training->Enable(false);
	b_shuffle_training->Enable(false);
	b_paste_from_clipboard_training->Enable(false);
	b_set_num_outputs_training->Enable(false);

	b_load_validation_data->Enable(false);
	b_clear_validation_data->Enable(false);
	b_replace_symbol_validation->Enable(false);
	b_move_validation_to_training->Enable(false);
	b_paste_from_clipboard_validation->Enable(false);
	//cb_use_validation_set->Enable(false);

	b_load_test_data->Enable(false);
	b_clear_test_data->Enable(false);
	b_replace_symbol_test->Enable(false);
	b_move_test_to_training->Enable(false);
	b_paste_from_clipboard_test->Enable(false);

	//saved_to_numeric_state = b_to_numeric_data->IsEnabled();
	b_to_numeric_data->Enable(false);
	//saved_to_time_series_state = b_to_time_series->IsEnabled();

	b_scale_data->Enable(false);
}
//-------------------------------------------------------------------------
void t_main_window::enable_when_stop(void)
{
	b_start->Enable(true);
	b_stop->Enable(false);

	b_new_project->Enable(true);
	b_load_project->Enable(true);
	b_save_as_project->Enable(true);
	b_save_project->Enable(true);

	w_parameters->Enable(true);
	/*
	b_load_data->Enable(true);
	b_clear_data->Enable(true);
	*/
	b_save_code->Enable(true);
	b_to_clipboard_code->Enable(true);
	b_save_error_tables->Enable(true);
	//b_copy_error_table->Enable(true);
	b_save_stats->Enable(true);
	//b_copy_stats->Enable(true);

	cb_simplified_code->Enable(true);
	cb_language->Enable(true);

	/*
	b_load_training_data->Enable(true);
	b_clear_training_data->Enable(true);
	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE) {
		b_move_training_to_validation->Enable(true);
		b_move_training_to_test->Enable(true);
	}
	else {
		b_move_training_to_validation->Enable(false);
		b_move_training_to_test->Enable(false);
	}
	b_replace_symbol_training->Enable(true);
	b_shuffle_training->Enable(true);
	b_paste_from_clipboard_training->Enable(true);

	b_load_validation_data->Enable(true);
	b_clear_validation_data->Enable(true);
	b_replace_symbol_validation->Enable(true);
	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE)
		b_move_validation_to_training->Enable(true);
	else
		b_move_validation_to_training->Enable(false);

	b_paste_from_clipboard_validation->Enable(true);

	b_load_test_data->Enable(true);
	b_clear_test_data->Enable(true);
	b_replace_symbol_test->Enable(true);

	if (mep_engine.get_parameters_ptr()->get_problem_type() != MEP_PROBLEM_TIME_SERIE)
		b_move_test_to_training->Enable(true);
	else
		b_move_test_to_training->Enable(false);

	b_paste_from_clipboard_test->Enable(true);
	*/
	update_training_buttons();
	update_validation_buttons();
	update_test_buttons();
	update_advance_commands_buttons();

	b_scale_data->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_paste_from_clipboard_training_button_clicked(wxCommandEvent& )
{
	if (!wxTheClipboard->Open())
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);

	wxTextDataObject text_data;
	wxTheClipboard->GetData(text_data);

	wxTheClipboard->Close();
	wxWindow::SetCursor(wxNullCursor);

	if (!text_data.GetDataSize()) {
		wxMessageBox("No data in Clipboard!", "Info");
		return;
	}

	wxString wx_copied_data(text_data.GetText());

	f_import_data_window->file_name = "";
	f_import_data_window->data_as_string = &wx_copied_data;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);
	
	mep_engine.get_training_data_ptr()->swap_data(f_import_data_window->data);
	
	mep_engine.get_parameters_ptr()->set_num_outputs(1);
	update_num_target_cols_to_data_grids();

	wxWindow::SetCursor(wxNullCursor);

	wxWindow::SetCursor(wxCURSOR_WAIT);

	clear_results();
	wxWindow::SetCursor(wxNullCursor);

	mep_engine.init_enabled_variables();
	set_enabled_grid_columns();

	update_training_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_paste_from_clipboard_validation_button_clicked(wxCommandEvent& )
{
	if (!wxTheClipboard->Open())
		return;

	wxTextDataObject text_data;
	wxTheClipboard->GetData(text_data);

	wxTheClipboard->Close();

	if (!text_data.GetDataSize()) {
		wxMessageBox("No data in Clipboard!", "Info");
		return;
	}

	clear_results();
	wxString wx_copied_data(text_data.GetText());

	f_import_data_window->file_name = "";
	f_import_data_window->data_as_string = &wx_copied_data;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);
	
	mep_engine.get_validation_data_ptr()->swap_data(f_import_data_window->data);

	g_validation_data->update_num_rows_cols();
	wxWindow::SetCursor(wxNullCursor);

	update_validation_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::on_paste_from_clipboard_test_button_clicked(wxCommandEvent& )
{
	if (!wxTheClipboard->Open())
		return;

	wxTextDataObject text_data;
	wxTheClipboard->GetData(text_data);

	wxTheClipboard->Close();

	if (!text_data.GetDataSize()) {
		wxMessageBox("No data in Clipboard!", "Info");
		return;
	}

	clear_results();
	wxString wx_copied_data(text_data.GetText());

	f_import_data_window->file_name = "";
	f_import_data_window->data_as_string = &wx_copied_data;

	f_import_data_window->CenterOnParent();
	if (f_import_data_window->ShowModal() != wxID_OK)
		return;

	wxWindow::SetCursor(wxCURSOR_WAIT);

	mep_engine.get_test_data_ptr()->swap_data(f_import_data_window->data);
	
	if (mep_engine.get_training_data_ptr()->get_num_cols() ==
		mep_engine.get_test_data_ptr()->get_num_cols())
		g_test_data->num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();
	else
		g_test_data->num_outputs = 0;
	
	g_test_data->update_num_rows_cols();
	wxWindow::SetCursor(wxNullCursor);

	update_test_buttons();

	update_advance_commands_buttons();

	b_save_project->Enable(true);
}
//-------------------------------------------------------------------------
void t_main_window::update_advance_commands_buttons(void)
{
	// to numeric
	if ((mep_engine.get_training_data_ptr()->get_num_rows() &&
		mep_engine.get_training_data_ptr()->get_data_type() == MEP_DATA_STRING) ||
		(mep_engine.get_validation_data_ptr()->get_num_rows() &&
		mep_engine.get_validation_data_ptr()->get_data_type() == MEP_DATA_STRING) ||
		(mep_engine.get_test_data_ptr()->get_num_rows() &&
		 mep_engine.get_test_data_ptr()->get_data_type() == MEP_DATA_STRING)){
		b_to_numeric_data->Enable(true);
	}
	else
		b_to_numeric_data->Enable(false);

	// scale
	if ((!mep_engine.get_training_data_ptr()->get_num_rows() ||
		(mep_engine.get_training_data_ptr()->get_num_rows() &&
		mep_engine.get_training_data_ptr()->get_data_type() == MEP_DATA_DOUBLE)) &&

		(!mep_engine.get_validation_data_ptr()->get_num_rows()||
			(mep_engine.get_validation_data_ptr()->get_num_rows() &&
		mep_engine.get_validation_data_ptr()->get_data_type() == MEP_DATA_DOUBLE)) &&

		(!mep_engine.get_test_data_ptr()->get_num_rows() ||
			(mep_engine.get_test_data_ptr()->get_num_rows() &&
		mep_engine.get_test_data_ptr()->get_data_type() == MEP_DATA_DOUBLE))
		){
		b_scale_data->Enable(true);
	}
	else
		b_scale_data->Enable(false);

	if (!mep_engine.get_training_data_ptr()->get_num_rows() &&
		!mep_engine.get_validation_data_ptr()->get_num_rows()&&
		!mep_engine.get_test_data_ptr()->get_num_rows())
		b_scale_data->Enable(false);
}
//-------------------------------------------------------------------------
void t_main_window::on_num_outputs_training_button_clicked(wxCommandEvent& /*event*/)
{
	int num_outputs = (int)wxGetNumberFromUser("Min 1; Max " + wxString() << mep_engine.get_training_data_ptr()->get_num_cols(),
											   "Number: ", "Number of outputs",
											    mep_engine.get_parameters_ptr()->get_num_outputs(),
											   1, mep_engine.get_training_data_ptr()->get_num_cols());
	if (num_outputs != -1) {
		mep_engine.get_parameters_ptr()->set_num_outputs(num_outputs);
		
		update_num_target_cols_to_data_grids();
		
		clear_results();
		b_save_project->Enable(true);
	}
}
//-------------------------------------------------------------------------
