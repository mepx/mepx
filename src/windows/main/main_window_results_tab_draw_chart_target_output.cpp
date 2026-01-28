// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <float.h>
//---------------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//---------------------------------------------------------------------
void t_main_window::on_resize_chart_target_output(wxSizeEvent&)
{
	p_chart_target_output->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_paint_chart_output_target(wxPaintEvent&)
{
	wxPaintDC dc(p_chart_target_output);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	if (mep_engine.is_running()) {
		// do nothing
	}
	else{
		if (last_processed_run != -1) {
			// get chart options
			wxWindow::SetCursor(wxCURSOR_WAIT);
			get_target_output_chart_options(mepx_settings.target_output_chart_options);
			
			do_draw_legend_target_output(dc);
			int selected_target = cb_target_for_chart->GetCurrentSelection();
			if (selected_target >= 0){
				int offset = draw_output_and_target(dc, selected_target);
				draw_chart_separators(dc, offset);
			}
			wxWindow::SetCursor(wxNullCursor);
		}
	}
}
//---------------------------------------------------------------------
void t_main_window::do_draw_legend_target_output(wxClientDC& dc)
{
	// aici scriu average si best
	// average
	//  int target_width = dc.GetTextExtent("Target").GetWidth();
	//int output_width = dc.GetTextExtent("Output").GetWidth();
	int target_width = dc.GetTextExtent("Target").GetWidth();
	
	int index_width = dc.GetTextExtent("Data index").GetWidth();
	int value_width = dc.GetTextExtent("Value").GetWidth();

	int target_height = dc.GetTextExtent("Target").GetHeight();

	int dc_width = dc.GetSize().GetWidth();
	int dc_height = dc.GetSize().GetHeight();

	// legend
	/*
	// legend rectangle
	dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dc.DrawRectangle(1, 1, 20 + output_width + 1, 2 * target_height);
	*/
	 // target
	dc.SetPen(wxPen(wxColor(0xFF, 0, 0), 1));
	dc.DrawCircle(10, target_height / 2, 3);
	dc.SetTextForeground(wxColor(0xFF, 0, 0));
	dc.DrawText("Target", 20, 0);
	// output
	dc.SetPen(wxPen(wxColor(0, 0, 0xFF), 1));
	dc.DrawRectangle(30 + target_width + 10 - 3,
					target_height / 2 - 3,
					6,
					6);
	dc.SetTextForeground(wxColor(0, 0, 0xFF));
	dc.DrawText("Output", 30 + 20 + target_width, 0);

	// axis X
	dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawText("Data index", (dc_width - index_width) / 2, dc_height - target_height);

	// axis Y
	dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawRotatedText("Value", 0, (dc_height + value_width) / 2, 90);

}
//---------------------------------------------------------------------
void t_main_window::draw_chart_separators(wxClientDC& dc, int offset)
{
	unsigned int num_data = compute_num_data_to_draw();

	if (!num_data)
		return;

	int text_height = dc.GetTextExtent("A").GetHeight();
	int circle_radius = 3;

	int dc_height = dc.GetSize().GetY();
	int dc_width = dc.GetSize().GetX();

	//int chart_height = dc_height - 4 * text_height - 2 * circle_radius;
	int chart_width = dc_width - text_height - offset - circle_radius;


	dc.SetPen(wxPen(wxColor(0, 0, 0), 1));

	//int space_between_consecutive_data = 1 / (double)(num_data - 1) * chart_width / 2.0;

	if (mepx_settings.target_output_chart_options.cb_chart_show_separator) {
		// first line
		int x = offset;
		dc.DrawLine(x, 2 * text_height, x, dc_height - text_height);
	}

	int num_total_data = 0;
	if (mepx_settings.target_output_chart_options.cb_chart_training_target_output) {
		
		int num_local_data = mep_engine.get_training_data_ptr()->get_num_rows();
		if (mepx_settings.target_output_chart_options.cb_chart_show_separator) {
			int x = int(offset + (num_local_data + num_total_data - 1) / (double)(num_data - 1) * chart_width);
			dc.DrawLine(x, 2 * text_height, x, dc_height - text_height);
		}

		int data_width = dc.GetTextExtent("Training").GetWidth();
		dc.SetTextForeground(wxColor(0, 0, 0));
		dc.DrawText("Training", int(offset + (num_total_data - 1) / (double)(num_data - 1) * chart_width + (num_local_data)/ (double)(num_data - 1) * chart_width / 2.0 - data_width / 2.0), 2 * text_height);
		num_total_data += num_local_data;
	}
	if (mepx_settings.target_output_chart_options.cb_chart_validation_target_output) {
		int num_local_data = mep_engine.get_validation_data_ptr()->get_num_rows();
		if (mepx_settings.target_output_chart_options.cb_chart_show_separator) {
			int x = int(offset + (num_local_data + num_total_data - 1) / (double)(num_data - 1) * chart_width);
			dc.DrawLine(x, 2 * text_height, x, dc_height - text_height);
		}

		int data_width = dc.GetTextExtent("Validation").GetWidth();
		dc.SetTextForeground(wxColor(0, 0, 0));
		dc.DrawText("Validation", int(offset + (num_total_data - 1) / (double)(num_data - 1) * chart_width + (num_local_data) / (double)(num_data - 1) * chart_width / 2.0 - data_width / 2.0), 2 * text_height);
		num_total_data += num_local_data;
	}
	if (mepx_settings.target_output_chart_options.cb_chart_testing_target_output) {
		int num_local_data = mep_engine.get_test_data_ptr()->get_num_rows();
		if (mepx_settings.target_output_chart_options.cb_chart_show_separator) {
			int x = int(offset + (num_local_data + num_total_data - 1) / (double)(num_data - 1) * chart_width);
			dc.DrawLine(x, 2 * text_height, x, dc_height - text_height);
		}

		int data_width = dc.GetTextExtent("Test").GetWidth();
		dc.SetTextForeground(wxColor(0, 0, 0));
		dc.DrawText("Test", int(offset + (num_total_data - 1) / (double)(num_data - 1) * chart_width + (num_local_data) / (double)(num_data - 1) * chart_width / 2 - data_width / 2), 2 * text_height);
		num_total_data += num_local_data;
	}

	if (mepx_settings.target_output_chart_options.cb_chart_predictions_target_output && 
		mepx_settings.target_output_chart_options.cb_chart_output) {
		int num_local_data = mep_engine.get_parameters_ptr()->get_num_predictions();
		if (mepx_settings.target_output_chart_options.cb_chart_show_separator) {
			int x = int(offset + (num_local_data + num_total_data - 1) / (double)(num_data - 1) * chart_width);
			dc.DrawLine(x, 2 * text_height, x, dc_height - text_height);
		}

		int data_width = dc.GetTextExtent("Predict").GetWidth();
		dc.SetTextForeground(wxColor(0, 0, 0));
		dc.DrawText("Predict", int(offset + (num_total_data - 1) / (double)(num_data - 1) * chart_width + (num_local_data) / (double)(num_data - 1) * chart_width / 2 - data_width / 2), 2 * text_height);
		num_total_data += num_local_data;
	}
}
//---------------------------------------------------------------------

int t_main_window::draw_output_and_target(wxClientDC& dc,
										  int current_selected_target)
{
	if (!mepx_settings.target_output_chart_options.cb_chart_output &&
		!mepx_settings.target_output_chart_options.cb_chart_target) {
		return 0;
	}

	unsigned int num_data = compute_num_data_to_draw();
	unsigned int num_outputs = mep_engine.get_parameters_ptr()->get_num_outputs();

	if (!num_data)
		return 0;


	// compute min, max
	double *min_data = new double[num_outputs];
	double *max_data = new double[num_outputs];

	for (unsigned int o = 0; o < num_outputs; o++){
		min_data[o] = DBL_MAX;
		max_data[o] = -DBL_MAX;
	}
	
	double** target_double = NULL;

	char* has_target = NULL;

	if (mepx_settings.target_output_chart_options.cb_chart_target) {
		target_double = new double*[num_data];
		for (unsigned int i = 0; i < num_data; i++)
			target_double[i] = new double[num_outputs];
		has_target = new char[num_data];
		
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_DOUBLE){
			mep_engine.get_target_for_all_data(mepx_settings.target_output_chart_options.cb_chart_training_target_output,
											mepx_settings.target_output_chart_options.cb_chart_validation_target_output,
											mepx_settings.target_output_chart_options.cb_chart_testing_target_output,
											mepx_settings.target_output_chart_options.cb_chart_predictions_target_output &&
											mepx_settings.target_output_chart_options.cb_chart_output,
											target_double, has_target,
										   min_data, max_data);
		}
		else{// long
			long long *min_data_long = new long long[num_outputs];
			long long *max_data_long = new long long[num_outputs];
			for (unsigned int o = 0; o < num_outputs; o++){
				min_data_long[o] = LLONG_MAX;
				max_data_long[o] = LLONG_MIN;
			}
			
			long long** target_long = new long long*[num_data];
			for (unsigned int i = 0; i < num_data; i++)
				target_long[i] = new long long[num_outputs];
			
			mep_engine.get_target_for_all_data(mepx_settings.target_output_chart_options.cb_chart_training_target_output,
											mepx_settings.target_output_chart_options.cb_chart_validation_target_output,
											mepx_settings.target_output_chart_options.cb_chart_testing_target_output,
											mepx_settings.target_output_chart_options.cb_chart_predictions_target_output &&
											mepx_settings.target_output_chart_options.cb_chart_output,
											target_long, has_target,
										   min_data_long, max_data_long);
			
			// make it double
			for (unsigned int o = 0; o < num_outputs; o++){
				if (min_data[o] > min_data_long[o])
					min_data[o] = min_data_long[o];
				if (max_data[o] < max_data_long[o])
					max_data[o] = max_data_long[o];
				for (unsigned int i = 0; i < num_data; i++)
					target_double[i][o] = target_long[i][o];
			}
			for (unsigned int i = 0; i < num_data; i++)
				delete[] target_long[i];
			delete[] target_long;
			delete[] min_data_long;
			delete[] max_data_long;
		}
    }
//--------------------------------------------------------
	double** output_double = NULL;

	char* valid_output = NULL;

	if (mepx_settings.target_output_chart_options.cb_chart_output) {
		output_double = new double*[num_data];
		for (unsigned int i = 0; i < num_data; i++)
			output_double[i] = new double[num_outputs];
		
		valid_output = new char[num_data];
		if (mep_engine.get_parameters_ptr()->get_data_type() == MEP_DATA_DOUBLE){
			mep_engine.compute_output_on_all_data(mepx_settings.target_output_chart_options.cb_chart_training_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_validation_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_testing_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_predictions_target_output &&
											   mepx_settings.target_output_chart_options.cb_chart_output,
										   last_processed_run,
										   output_double, valid_output,
										   min_data, max_data);
		}
		else{//long
			long long *min_data_long = new long long[num_outputs];
			long long *max_data_long = new long long[num_outputs];
			for (unsigned int o = 0; o < num_outputs; o++){
				min_data_long[o] = LLONG_MAX;
				max_data_long[o] = LLONG_MIN;
			}
			
			long long** output_long = new long long*[num_data];
			for (unsigned int i = 0; i < num_data; i++)
				output_long[i] = new long long[num_outputs];
			
			mep_engine.compute_output_on_all_data(mepx_settings.target_output_chart_options.cb_chart_training_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_validation_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_testing_target_output,
											   mepx_settings.target_output_chart_options.cb_chart_predictions_target_output &&
											   mepx_settings.target_output_chart_options.cb_chart_output,
											   last_processed_run,
											   output_long, valid_output,
											   min_data_long, max_data_long);
				
			// make it double
			for (unsigned int o = 0; o < num_outputs; o++){
				if (min_data[o] > min_data_long[o])
					min_data[o] = min_data_long[o];
				if (max_data[o] < max_data_long[o])
					max_data[o] = max_data_long[o];
				for (unsigned int i = 0; i < num_data; i++)
					output_double[i][o] = output_long[i][o];
			}
			for (unsigned int i = 0; i < num_data; i++)
				delete[] output_long[i];
			delete[] output_long;
			
			delete[] min_data_long;
			delete[] max_data_long;
		}
	}

	int text_height = dc.GetTextExtent("A").GetHeight();
	int circle_radius = 3;
	//int dc_height = dc.GetSize().GetY();
	//int dc_width = dc.GetSize().GetX();
	// draw limits for axis
	int max_value_width = 0;
	


	wxString min_y_string = wxString::Format(wxT("%.2lg"), min_data[current_selected_target]);
	wxString max_y_string = wxString::Format(wxT("%.2lg"), max_data[current_selected_target]);
	wxString mean_y_string = wxString::Format(wxT("%.2lg"), (max_data[current_selected_target] + min_data[current_selected_target]) / 2.0);

	int min_y_width = dc.GetTextExtent(min_y_string).GetWidth();
	int max_y_width = dc.GetTextExtent(max_y_string).GetWidth();
	int mean_y_width = dc.GetTextExtent(max_y_string).GetWidth();

	max_value_width = min_y_width;
	if (max_value_width < max_y_width)
		max_value_width = max_y_width;
	if (max_value_width < mean_y_width)
		max_value_width = mean_y_width;
	
	int dc_height = dc.GetSize().GetY() - 4 * text_height - 2 * circle_radius;
	int dc_width = dc.GetSize().GetX() - 2 * text_height - max_value_width - 2 * circle_radius;
	// limits for X axis
	// left limit
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawText("1", 
		max_value_width + text_height + circle_radius, 
		dc_height + 3 * text_height + 2 * circle_radius);
	// right limit
	wxString num_data_as_string = wxString() << num_data;
	int num_data_width = dc.GetTextExtent(num_data_as_string).GetWidth();
	dc.DrawText(num_data_as_string,
		dc_width - num_data_width + text_height + max_value_width + circle_radius,
		dc_height + 3 * text_height + 2 * circle_radius);
// limits for Y axis
	dc.DrawText(min_y_string, text_height, dc_height + 3 * text_height - text_height / 2);
	dc.DrawText(mean_y_string, text_height, dc_height / 2 + 3 * text_height - text_height / 4);
	dc.DrawText(max_y_string, text_height, 2 * text_height);

	//
	int prev_x = 0;
	int prev_y = 0;
	// draw target
	if (mepx_settings.target_output_chart_options.cb_chart_target) {
		dc.SetPen(wxPen(wxColor(0xFF, 0, 0), 1));
		bool first_correct = true;
		for (unsigned int i = 0; i < num_data; i++)
			if (has_target[i]) {
				int x = int(i / (double)(num_data - 1) * dc_width);
				int y;
				if (max_data[current_selected_target] > min_data[current_selected_target])
					y = int((target_double[i][current_selected_target] - min_data[current_selected_target]) / (max_data[current_selected_target] - min_data[current_selected_target]) * dc_height);
				else
					y = int(dc_height / 2.0);

				dc.DrawCircle(
					circle_radius + max_value_width + text_height + x,
					dc_height - y + 3 * text_height + circle_radius,
					circle_radius);
				if (!first_correct)
					if (mepx_settings.target_output_chart_options.cb_chart_show_lines)
						dc.DrawLine(
							circle_radius + max_value_width + text_height + prev_x,
							dc_height - prev_y + 3 * text_height + circle_radius,
							circle_radius + max_value_width + text_height + x,
							dc_height - y + 3 * text_height + circle_radius);
				prev_x = x;
				prev_y = y;
				first_correct = false;
			}
		for (unsigned int i = 0; i < num_data; i++)
			delete[] target_double[i];
		delete[] target_double;
		delete[] has_target;
	}
	// draw output
	if (mepx_settings.target_output_chart_options.cb_chart_output) {
		dc.SetPen(wxPen(wxColor(0, 0, 0xFF), 1));
		bool first_correct = true;
		for (unsigned int i = 0; i < num_data; i++)
			if (valid_output[i] == valid_output_OK) {
				int x = int(i / (double)(num_data - 1) * dc_width);
				int y;
				if (max_data[current_selected_target] > min_data[current_selected_target])
					y = int((output_double[i][current_selected_target] - min_data[current_selected_target]) / (max_data[current_selected_target] - min_data[current_selected_target]) * dc_height);
				else
					y = dc_height / 2;

				dc.DrawRectangle(
					circle_radius + max_value_width + text_height + x - 3,
					dc_height - y + 3 * text_height + circle_radius - 3,
					6, 6);
				if (!first_correct)
					if (mepx_settings.target_output_chart_options.cb_chart_show_lines)
						dc.DrawLine(
							circle_radius + max_value_width + text_height + prev_x,
							dc_height - prev_y + 3 * text_height + circle_radius,
							circle_radius + max_value_width + text_height + x,
							dc_height - y + 3 * text_height + circle_radius);
				prev_x = x;
				prev_y = y;
				first_correct = false;
			}
		for (unsigned int i = 0; i < num_data; i++)
			delete[] output_double[i];
		delete[] output_double;
		delete[] valid_output;
	}

	delete[] min_data;
	delete[] max_data;
	

	return circle_radius + max_value_width + text_height;
}
//---------------------------------------------------------------------
void t_main_window::on_cb_target_for_chart_change(wxCommandEvent& /*event*/)
{
	//cb_target_for_chart->GetSelection();
	p_chart_target_output->Refresh();
}
//---------------------------------------------------------------------
