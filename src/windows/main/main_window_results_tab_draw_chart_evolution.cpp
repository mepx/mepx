// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include "windows/main_window.h"
#include "mepx_project.h"
//---------------------------------------------------------------------
void t_main_window::on_resize_chart_evolution(wxSizeEvent&)
{
	//draw_evolution();
	p_chart_evolution->Refresh();
}
//---------------------------------------------------------------------
void t_main_window::on_paint_chart_evolution(wxPaintEvent&)
{
	wxPaintDC dc(p_chart_evolution);

	//int chart_height = p_chart_evolution->GetSize().GetY();
	get_evolution_chart_options(mepx_settings.evolution_chart_options);

	if (mep_engine.is_running()) {
		if (last_processed_generation == 0) {
			do_draw_first_generation(dc, last_processed_run); // first generation
		}
		else {
			if (last_processed_generation != -1 &&
				last_processed_run != -1) {
				
				dc.SetBackground(*wxWHITE_BRUSH);
				dc.Clear();

				do_draw_first_generation(dc, last_processed_run); // first generation
				for (int g = 1; g <= last_processed_generation; g++) {
					do_draw_next_generations(dc, last_processed_run, g);
				}
			}
		}
	}
	else {

		// it is stopped ... so I have to draw from the currently selected run

		draw_evolution(dc);
	}
//	event.Skip(false);

}
//---------------------------------------------------------------------
void t_main_window::draw_evolution(wxClientDC &dc)
{
	// compute scale
	if (last_processed_generation > -1) {
		do_draw_first_generation(dc, last_processed_run);

		// now for the rest of generations

		for (int g = 1; g <= last_processed_generation; g++) {
			do_draw_next_generations(dc, last_processed_run, g);
		}
	}
	else { // clear
		dc.SetBackground(*wxWHITE_BRUSH);
		dc.Clear();
	}
}
//---------------------------------------------------------------------
void t_main_window::do_draw_legend_evolution(wxClientDC& dc)
{
	// aici scriu average si best
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	int text_height = dc.GetTextExtent("A").GetHeight();
	
	// average
	int average_width = dc.GetTextExtent("Average").GetWidth();
	//int average_height = dc.GetTextExtent("Average").GetHeight();

	// best
	int best_width = dc.GetTextExtent("Best").GetWidth();
	//int best_height = dc.GetTextExtent("Best").GetHeight();

	int iteration_width = dc.GetTextExtent("Generation").GetWidth();
	
	int error_width = dc.GetTextExtent("Error").GetWidth();

	int dc_width = dc.GetSize().GetWidth();
	int dc_height = dc.GetSize().GetHeight();

	int circle_radius = 3;
	
	// draw 0 point
	int left_magin = text_height + circle_radius;
	int bottom_margin = text_height + circle_radius;
	// axis
	int axix_length = 7;
	dc.SetPen(wxPen(wxColor(0x22, 0x8C, 0x22), 1));
	// horizontal line
	dc.DrawLine(left_magin, dc_height - bottom_margin,
				left_magin + axix_length, dc_height - bottom_margin);
	// vertical line
	dc.DrawLine(left_magin, dc_height - bottom_margin,
				left_magin, dc_height - bottom_margin - axix_length );
	
	// 0 value on vertical axix
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawRotatedText("0", 0, dc_height - bottom_margin, 90);
	
	// legend
	//best text
	dc.SetPen(wxPen(wxColor(0xFF, 0, 0), 1));
	dc.DrawCircle(text_height + 10, text_height / 2, circle_radius);
	dc.SetTextForeground(wxColor(0xFF, 0, 0));
	dc.DrawText("Best", text_height + 20, 0);

	// average
	if (mepx_settings.evolution_chart_options.cb_pop_average_evolution){
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
		dc.DrawCircle(text_height + 20 + best_width + 10, text_height / 2, circle_radius);
		dc.SetTextForeground(wxColor(0, 0, 0));
		dc.DrawText("Average", text_height + 20 + best_width + 20, 0);
	}

	// validation
	if (mepx_settings.evolution_chart_options.cb_validation_evolution){
		dc.SetPen(wxPen(wxColor(0, 0, 0xFF), 1));
		dc.DrawCircle(text_height + 20 + best_width + mepx_settings.evolution_chart_options.cb_pop_average_evolution*(20 + average_width) + 10, text_height / 2, circle_radius);
		dc.SetTextForeground(wxColor(0, 0, 0xFF));
		dc.DrawText("Validation", text_height + 20 + best_width + 20 + mepx_settings.evolution_chart_options.cb_pop_average_evolution*(average_width + 20), 0);
	}
	// axis X
	//dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawText("Generation", (dc_width - iteration_width) / 2, dc_height - text_height);
	// axis Y
	dc.SetTextForeground(wxColor(0, 0, 0));
	//dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dc.DrawRotatedText("Error", 0, (dc_height + error_width) / 2, 90);

	// left X limit
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawText("1", text_height + circle_radius, dc_height - text_height);
	
	// right limit
	wxString num_data_as_string = wxString() << mep_engine.get_parameters_ptr()->get_num_generations();
	int num_data_width = dc.GetTextExtent(num_data_as_string).GetWidth();
	dc.DrawText(num_data_as_string,
		dc_width - num_data_width - circle_radius - text_height,
		dc_height - text_height);
}
//---------------------------------------------------------------------
void t_main_window::do_draw_first_generation(wxClientDC& dc, int run_index)
{
	// here I calculate the evolution_scale_x .. this is why this function is separate from the next one
	int circle_radius = 3;
	int text_height = dc.GetTextExtent("A").GetHeight();
	
	int chart_width = dc.GetSize().GetWidth() - 2 * text_height - 2 * circle_radius;
	int chart_height = dc.GetSize().GetHeight() - 2 * text_height - 2 * circle_radius;

//	int left_magin = text_height + circle_radius;
//	int bottom_margin = text_height + circle_radius;
	int top_margin = text_height + circle_radius;
	
	double last_best_training_error = mep_engine.get_stats_ptr()->get_best_training_error(run_index, 0);
	double worst_error = last_best_training_error;
	double last_average_error = -1;
	
	if (mepx_settings.evolution_chart_options.cb_pop_average_evolution){
		last_average_error = mep_engine.get_stats_ptr()->get_average_training_error(run_index, 0);
		if (worst_error < last_average_error)
			worst_error = last_average_error;
	}
	
	double last_validation_error = -1;
	if (mepx_settings.evolution_chart_options.cb_validation_evolution){
		last_validation_error = mep_engine.get_stats_ptr()->get_validation_error(run_index, 0);
		if (worst_error < last_validation_error)
			worst_error = last_validation_error;
	}
	
	if (worst_error < 0.0000001)
		scale_evolution_y = 1;
	else
		scale_evolution_y = chart_height / worst_error;
	

	if (mep_engine.get_parameters_ptr()->get_num_generations() <= 1)
		scale_evolution_x = 1;
	else
		scale_evolution_x = chart_width / (double)(mep_engine.get_parameters_ptr()->get_num_generations() - 1);
	
	do_draw_legend_evolution(dc);
	
	// draw max value on Y axis
	wxString s_worst = wxString().Format("%lg", worst_error);
	int worst_string_width = dc.GetTextExtent(s_worst).GetWidth();
	dc.SetTextForeground(wxColor(0, 0, 0));
	dc.DrawRotatedText(s_worst, 0, top_margin + worst_string_width, 90);

	// fist point
	wxCoord x_current = int(0 * scale_evolution_x + text_height + circle_radius);
	//best
	wxCoord y_current_best = int(chart_height - last_best_training_error * scale_evolution_y + text_height + circle_radius);
	dc.SetPen(wxPen(wxColor(0xFF, 0, 0), 1));
	dc.DrawCircle(x_current, y_current_best, circle_radius);

	// average
	if (mepx_settings.evolution_chart_options.cb_pop_average_evolution){
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
		wxCoord y_current_average = int(chart_height - last_average_error * scale_evolution_y + text_height + circle_radius);
		dc.DrawCircle(x_current, y_current_average, circle_radius);
	}

	//validation
	if (mepx_settings.evolution_chart_options.cb_validation_evolution && last_validation_error > 0){
		wxCoord y_current_validation = int(chart_height - last_validation_error * scale_evolution_y + text_height + circle_radius);
		dc.SetPen(wxPen(wxColor(0, 0, 0xFF), 1));
		dc.DrawCircle(x_current, y_current_validation, circle_radius);
	}
}
//----------------------------------------------------------------------------
void t_main_window::do_draw_next_generations(wxClientDC& dc, int run_index, int gen_index)
{
	int circle_radius = 3;
	int text_height = dc.GetTextExtent("A").GetHeight();
	//int dc_width = dc.GetSize().GetWidth() - 2 * text_height - 2 * circle_radius;
	int dc_height = dc.GetSize().GetHeight() - 3 * text_height - 2 * circle_radius;


	wxCoord x_prev = int((gen_index - 1) * scale_evolution_x + text_height + circle_radius);
	wxCoord x_current = int(gen_index * scale_evolution_x + text_height + circle_radius);

	// best
	double previous_best_error = mep_engine.get_stats_ptr()->get_best_training_error(run_index, gen_index - 1);
	double g_best_error = mep_engine.get_stats_ptr()->get_best_training_error(run_index, gen_index);

	wxCoord y_prev_best = int(dc_height - previous_best_error * scale_evolution_y + 2 * text_height + circle_radius);
	wxCoord y_current_best = int(dc_height - g_best_error * scale_evolution_y + 2 * text_height + circle_radius);

	dc.SetPen(wxPen(wxColor(0xFF, 0, 0), 1));
	dc.DrawLine(x_prev, y_prev_best, x_current, y_current_best);
	dc.DrawCircle(x_current, y_current_best, 3);

	// average
	if (mepx_settings.evolution_chart_options.cb_pop_average_evolution){
		double previous_average_error = mep_engine.get_stats_ptr()->get_average_training_error(run_index, gen_index - 1);
		double g_average_error = mep_engine.get_stats_ptr()->get_average_training_error(run_index, gen_index);
		
		wxCoord y_prev_average = int(dc_height - previous_average_error * scale_evolution_y + 2 * text_height + circle_radius);
		wxCoord y_current_average = int(dc_height - g_average_error * scale_evolution_y + 2 * text_height + circle_radius);
		
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
		dc.DrawLine(x_prev, y_prev_average, x_current, y_current_average);
		// also draw a small circle
		dc.DrawCircle(x_current, y_current_average, 3);
	}

	// validation
	if (mepx_settings.evolution_chart_options.cb_validation_evolution){
		double previous_validation_error = mep_engine.get_stats_ptr()->get_validation_error(run_index, gen_index - 1);
		double g_validation_error = mep_engine.get_stats_ptr()->get_validation_error(run_index, gen_index);
		
		if (previous_validation_error > 0 && g_validation_error > 0){
			wxCoord y_prev_validation = int(dc_height - previous_validation_error * scale_evolution_y + 2 * text_height + circle_radius);
			wxCoord y_current_validation = int(dc_height - g_validation_error * scale_evolution_y + 2 * text_height + circle_radius);
			
			dc.SetPen(wxPen(wxColor(0, 0, 0xFF), 1));
			dc.DrawLine(x_prev, y_prev_validation, x_current, y_current_validation);
			// also draw a small circle
			dc.DrawCircle(x_current, y_current_validation, 3);
		}
	}
}
//----------------------------------------------------------------------------
