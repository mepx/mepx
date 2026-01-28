// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "windows/replace_symbol_window.h"
#include "windows/scale_limits_window.h"
//--------------------------------------------------------------------------
#include "mepx_project.h"
//--------------------------------------------------------------------------
void t_main_window::on_find_symbol_button_clicked(wxCommandEvent&)
{
	f_replace_symbol_window->SetLabel("Find");
	f_replace_symbol_window->rb_replace_where->SetLabel("Find where");

	f_replace_symbol_window->st_replace_with->Show(false);
	f_replace_symbol_window->tc_replace_with->Show(false);

	f_replace_symbol_window->cb_column->Clear();

	switch (n_data->GetSelection()) {
	case TRAINING_DATA_PAGE:// training
		for (unsigned int v = 0; v < mep_engine.get_training_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	case VALIDATION_DATA_PAGE:// validation
		for (unsigned int v = 0; v < mep_engine.get_validation_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	case TEST_DATA_PAGE:// test
		for (unsigned int v = 0; v < mep_engine.get_test_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	}

	f_replace_symbol_window->rb_replace_where->SetSelection(0);

	if (f_replace_symbol_window->cb_column->GetCount())
		f_replace_symbol_window->cb_column->SetSelection(0);

	f_replace_symbol_window->cb_column->Enable(false);

	f_replace_symbol_window->CenterOnParent();
	if (f_replace_symbol_window->ShowModal() != wxID_OK)
		return;

	wxString s_find_what;
	s_find_what = f_replace_symbol_window->tc_find_what->GetValue().Trim();

	int replace_where = f_replace_symbol_window->rb_replace_where->GetSelection();
	int replace_col = f_replace_symbol_window->cb_column->GetSelection();

	bool use_regular = f_replace_symbol_window->cb_use_regular->IsChecked();

	int _data_type = MEP_DATA_DOUBLE;
	switch (n_data->GetSelection()) {
	case TRAINING_DATA_PAGE:// training
		_data_type = mep_engine.get_training_data_ptr()->get_data_type();
		break;
	case VALIDATION_DATA_PAGE:// validation
		_data_type = mep_engine.get_validation_data_ptr()->get_data_type();
		break;
	case TEST_DATA_PAGE:// test
		_data_type = mep_engine.get_test_data_ptr()->get_data_type();
		break;
	}
	if (_data_type == MEP_DATA_DOUBLE) {// double
		if (s_find_what == "") {
			wxMessageBox("<<find what>> cannot be empty", "Error");
			return;
		}

		double d;
		if (!s_find_what.ToCDouble(&d)) {
			wxMessageBox(s_find_what + " is not a real number", "Error");
			return;
		}
	}

	wxWindow::SetCursor(wxCURSOR_WAIT);

	int num_found = 0;
	//		int result_error = 0;

	switch (n_data->GetSelection()) {
	case TRAINING_DATA_PAGE:// training
		switch (replace_where) {
		case FIND_REPLACE_EVERYWHERE:// find everywhere
			num_found = mep_engine.get_training_data_ptr()->find_symbol_everywhere(s_find_what.utf8_str(), use_regular);
			//	g_training->Refresh();

			break;
		case FIND_REPLACE_SELECTED_COLUMN:// find in selected col
			num_found = mep_engine.get_training_data_ptr()->find_symbol_from_selected_col(s_find_what.utf8_str(), replace_col, use_regular);
			//	g_training->Refresh();
			break;
		}
		update_training_buttons();
		break;
	case VALIDATION_DATA_PAGE:// validation
		switch (replace_where) {
		case FIND_REPLACE_EVERYWHERE:// find in  everywhere
			num_found = mep_engine.get_validation_data_ptr()->find_symbol_everywhere(s_find_what.utf8_str(), use_regular);
			//	g_validation->Refresh();
			break;
		case FIND_REPLACE_SELECTED_COLUMN:// find in  selected variable
			num_found = mep_engine.get_validation_data_ptr()->find_symbol_from_selected_col(s_find_what.utf8_str(), replace_col, use_regular);
			//	g_validation->Refresh();
			break;

		}

		update_validation_buttons();
		break;

	case TEST_DATA_PAGE:// test
		switch (replace_where) {
		case FIND_REPLACE_EVERYWHERE:// find in  everywhere
			num_found = mep_engine.get_test_data_ptr()->find_symbol_everywhere(s_find_what.utf8_str(), use_regular);
			//	g_test->Refresh();
			break;
		case FIND_REPLACE_SELECTED_COLUMN:// find in  selected variable
			num_found = mep_engine.get_test_data_ptr()->find_symbol_from_selected_col(s_find_what.utf8_str(), replace_col, use_regular);
			//	g_test->Refresh();
			break;
		}

		update_test_buttons();
		break;
	}
	wxWindow::SetCursor(wxNullCursor);

	wxMessageBox((wxString() << num_found) + " found", "Info");

	//clear_results();

	b_save_project->Enable(true);
	//st_project_name->SetForegroundColour(wxColour(0x0000FF));
	//st_project_name->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_replace_symbol_button_clicked(wxCommandEvent&)
{
	f_replace_symbol_window->SetLabel("Replace");
	f_replace_symbol_window->rb_replace_where->SetLabel("Replace where");

	f_replace_symbol_window->st_replace_with->Show(true);
	f_replace_symbol_window->tc_replace_with->Show(true);

	f_replace_symbol_window->cb_column->Clear();

	switch (n_data->GetSelection()) {
	case TRAINING_DATA_PAGE:// training
		for (unsigned int v = 0; v < mep_engine.get_training_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	case VALIDATION_DATA_PAGE:// validation
		for (unsigned int v = 0; v < mep_engine.get_validation_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	case TEST_DATA_PAGE:// test
		for (unsigned int v = 0; v < mep_engine.get_test_data_ptr()->get_num_cols(); v++)
			f_replace_symbol_window->cb_column->AppendString(wxString() << v);
		break;
	}

	f_replace_symbol_window->rb_replace_where->SetSelection(0);

	if (f_replace_symbol_window->cb_column->GetCount())
		f_replace_symbol_window->cb_column->SetSelection(0);

	f_replace_symbol_window->cb_column->Enable(false);

	f_replace_symbol_window->CenterOnParent();
	if (f_replace_symbol_window->ShowModal() == wxID_OK) {

		wxString s_find_what;
		s_find_what = f_replace_symbol_window->tc_find_what->GetValue().Trim();

		wxString s_replace_with;
		s_replace_with = f_replace_symbol_window->tc_replace_with->GetValue().Trim();

		int replace_where = f_replace_symbol_window->rb_replace_where->GetSelection();
		int replace_col = f_replace_symbol_window->cb_column->GetSelection();

		bool use_regular = f_replace_symbol_window->cb_use_regular->IsChecked();

		int _data_type = MEP_DATA_DOUBLE;
		switch (n_data->GetSelection()) {
		case TRAINING_DATA_PAGE:// training
			_data_type = mep_engine.get_training_data_ptr()->get_data_type();
			break;
		case VALIDATION_DATA_PAGE:// validation
			_data_type = mep_engine.get_validation_data_ptr()->get_data_type();
			break;
		case TEST_DATA_PAGE:// test
			_data_type = mep_engine.get_test_data_ptr()->get_data_type();
			break;
		}
		if (_data_type == MEP_DATA_DOUBLE) {// double
			if (s_find_what == "") {
				wxMessageBox("<<find what>> cannot be empty", "Error");
				return;
			}

			if (s_replace_with == "") {
				wxMessageBox("<<replace with>> cannot be empty", "Error");
				return;
			}
			double d;
			if (!s_find_what.ToCDouble(&d)) {
				wxMessageBox(s_find_what + " is not a real number", "Error");
				return;
			}
			if (!s_replace_with.ToCDouble(&d)) {
				wxMessageBox(s_replace_with + " is not a real number", "Error");
				return;
			}
		}

		wxWindow::SetCursor(wxCURSOR_WAIT);

		int num_replaced = 0;

		switch (n_data->GetSelection()) {
		case TRAINING_DATA_PAGE:// training
			switch (replace_where) {
			case FIND_REPLACE_EVERYWHERE:// replace everywhere
				num_replaced = mep_engine.get_training_data_ptr()->replace_symbol_everywhere(s_find_what.utf8_str(), s_replace_with.utf8_str(), use_regular);
				g_training_data->Refresh();

				break;
			case FIND_REPLACE_SELECTED_COLUMN:// replace selected variable
				num_replaced = mep_engine.get_training_data_ptr()->replace_symbol_from_selected_col(s_find_what.utf8_str(), s_replace_with.utf8_str(), replace_col, use_regular);
				g_training_data->Refresh();
				break;
			}
			update_training_buttons();
			break;
		case VALIDATION_DATA_PAGE:// validation
			switch (replace_where) {
			case FIND_REPLACE_EVERYWHERE:// replace everywhere
				num_replaced = mep_engine.get_validation_data_ptr()->replace_symbol_everywhere(s_find_what.utf8_str(), s_replace_with.utf8_str(), use_regular);
				g_validation_data->Refresh();

				break;

			case FIND_REPLACE_SELECTED_COLUMN:// replace selected variable
				num_replaced = mep_engine.get_validation_data_ptr()->replace_symbol_from_selected_col(s_find_what.utf8_str(), s_replace_with.utf8_str(), replace_col, use_regular);
				g_validation_data->Refresh();
				break;
			}

			update_validation_buttons();
			break;

		case TEST_DATA_PAGE:// test
			switch (replace_where) {
			case FIND_REPLACE_EVERYWHERE:// replace everywhere
				num_replaced = mep_engine.get_test_data_ptr()->replace_symbol_everywhere(s_find_what.utf8_str(), s_replace_with.utf8_str(), use_regular);
				g_test_data->Refresh();
				break;

			case FIND_REPLACE_SELECTED_COLUMN:// replace selected variable
				num_replaced = mep_engine.get_test_data_ptr()->replace_symbol_from_selected_col(s_find_what.utf8_str(), s_replace_with.utf8_str(), replace_col, use_regular);
				g_test_data->Refresh();
				break;
			}

			update_test_buttons();
			break;
		}

		wxMessageBox((wxString() << num_replaced) + " replacements", "Info");

		clear_results();

		b_save_project->Enable(true);
		//st_project_name->SetForegroundColour(wxColour(0x0000FF));
		//st_project_name->Refresh();

		wxWindow::SetCursor(wxNullCursor);
	}

}
//---------------------------------------------------------------------
void t_main_window::on_scale_data_button_clicked(wxCommandEvent&)
{
	f_scale_limits_window->cb_column->Clear();
	if (mep_engine.get_training_data_ptr()->get_num_cols() > 0)
		for (unsigned int v = 0; v < mep_engine.get_training_data_ptr()->get_num_cols(); v++)
			f_scale_limits_window->cb_column->AppendString(wxString() << v);

	f_scale_limits_window->rb_scale_where->SetSelection(0);

	if (f_scale_limits_window->cb_column->GetCount())
		f_scale_limits_window->cb_column->SetSelection(0);

	f_scale_limits_window->cb_column->Enable(false);

	f_scale_limits_window->CenterOnParent();
	if (f_scale_limits_window->ShowModal() == wxID_OK) {

		double min_interval;
		f_scale_limits_window->tc_min->GetValue().Trim().ToDouble(&min_interval);

		double max_interval;
		f_scale_limits_window->tc_max->GetValue().Trim().ToDouble(&max_interval);

		int scale_where = f_scale_limits_window->rb_scale_where->GetSelection();
		int scale_col = f_scale_limits_window->cb_column->GetSelection();

		wxWindow::SetCursor(wxCURSOR_WAIT);

		int result = E_MEP_OK;

		switch (scale_where) {
		case FIND_REPLACE_EVERYWHERE:// replace everywhere
			result = mep_engine.get_training_data_ptr()->scale_to_double_interval_everywhere(min_interval, max_interval, mep_engine.get_validation_data_ptr(), mep_engine.get_test_data_ptr());
			switch (result) {
			case E_MEP_OK:

				g_training_data->Refresh();
				g_test_data->Refresh();
				g_validation_data->Refresh();

				break;
			case E_MEP_NO_DATA:
				wxMessageBox("No data!", "Info");
				break;
			case E_MEP_DATA_MUST_HAVE_REAL_TYPE:
				wxMessageBox("Some data do not have a real type! Please replace all string values with real ones.", "Info");
				break;
			}
			break;

		case FIND_REPLACE_SELECTED_COLUMN: //selected col
			result = mep_engine.get_training_data_ptr()->scale_to_double_interval_selected_col(min_interval, max_interval, scale_col, mep_engine.get_validation_data_ptr(), mep_engine.get_test_data_ptr());
			switch (result) {
			case E_MEP_OK:

				g_training_data->Refresh();
				g_validation_data->Refresh();
				g_test_data->Refresh();

				break;
			case E_MEP_NO_DATA:
				wxMessageBox("No data!", "Info");
				break;
			case E_MEP_DATA_MUST_HAVE_REAL_TYPE:
				wxMessageBox("Some data do not have a real type! Please replace all string values with real ones.", "Info");
				break;

			}
			break;
		}

		if (result == E_MEP_OK) {
			update_training_buttons();
			update_validation_buttons();
			update_test_buttons();

			clear_results();

			b_save_project->Enable(true);
			//st_project_name->SetForegroundColour(wxColour(0x0000FF));
			//st_project_name->Refresh();
		}
		wxWindow::SetCursor(wxNullCursor);
	}
}
//---------------------------------------------------------------------
