// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef MEPX_main_window_H
#define MEPX_main_window_H

//-------------------------------------------------------------------------
#include "wx/wxprec.h"
#include <wx/log.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
//#include <wx/listbox.h>

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include <wx/listctrl.h>
//-------------------------------------------------------------------------
#include "components/lv_input_data.h"
#include "components/lv_output_target_errors.h"
#include "components/lv_stats_errors.h"
#include "mepx_interface_layout.h"
#include "mepx_chart_options.h"
#include "libmep.h"
//-------------------------------------------------------------------------
#define TRAINING_ERRORS_PAGE 0
#define VALIDATION_ERRORS_PAGE 1
#define TEST_ERRORS_PAGE 2
#define PREDICTIONS_PAGE 3
//-------------------------------------------------------------------------
#define INPUT_PAGE 0
#define PARAMETERS_PAGE 1
#define RESULTS_PAGE 2
//-------------------------------------------------------------------------
#define TRAINING_DATA_PAGE 0
#define VALIDATION_DATA_PAGE 1
#define TEST_DATA_PAGE 2
//-------------------------------------------------------------------------
#define STATUSBAR_GENERATION_INDEX 0
#define STATUSBAR_BEST_TRAINING_ERROR_INDEX 1
#define STATUSBAR_BEST_VALIDATION_ERROR_INDEX 2
//-------------------------------------------------------------------------
#define FIND_REPLACE_EVERYWHERE 0
#define FIND_REPLACE_SELECTED_COLUMN 1
//-------------------------------------------------------------------------
#define wxMENUBASE 1100
//-------------------------------------------------------------------------
class t_main_window : public wxFrame{
public:
    // ctor(s)
	t_main_window(const wxString& title);
	void do_new_project(void);

	wxSplitterWindow *splitter_stats_evolution;
	wxSplitterWindow* splitter_runs_results, * splitter_charts_code;
	wxSplitterWindow* splitter_code_graphics;

private:
	wxCheckBox* cb_chart_training_target_output, * cb_chart_validation_target_output, * cb_chart_testing_target_output, * cb_chart_predictions_target_output;
	wxCheckBox* cb_chart_target, * cb_chart_output;
	wxCheckBox* cb_chart_show_lines, * cb_chart_show_separator;

	wxComboBox* cb_target_for_chart;
	void on_cb_target_for_chart_change(wxCommandEvent& event);
	
	wxPanel *p_runs, *p_results;

    wxNotebook *n_settings, *n_data, *n_parameters;

	// data
    wxWindow *w_data, *w_results;

	wxCheckBox* cb_addition, * cb_subtraction, * cb_multiplication, * cb_division,
		* cb_power, * cb_sqrt, * cb_exp, * cb_pow10, * cb_ln, * cb_log10, * cb_log2,
		* cb_floor, * cb_ceil, * cb_abs, * cb_inv, * cb_neg, * cb_x2, * cb_min, * cb_max,
		* cb_sin, * cb_cos, * cb_tan, * cb_asin, * cb_acos, * cb_atan,
		* cb_ifalbcd, * cb_iflz, * cb_if_a_or_b_cd, * cb_if_a_xor_b_cd,
		* cb_fmod;
		//, *cb_min_gen, *cb_max_gen;

	wxButton* b_load_training_data, * b_clear_training_data, * b_save_training_data,
		* b_move_training_to_validation, * b_move_training_to_test,
		* b_replace_symbol_training, * b_find_symbol_training, * b_shuffle_training,
		* b_paste_from_clipboard_training, *b_set_num_outputs_training;

	//wxButton * b_to_time_series, *b_change_window_size;

	wxTextCtrl* tc_num_predictions;
	wxStaticText* st_num_predictions;

	wxTextCtrl* tc_window_size;
	wxStaticText* st_window_size;

	wxButton* b_load_validation_data, * b_clear_validation_data, * b_save_validation_data,
		* b_replace_symbol_validation, * b_find_symbol_validation, * b_paste_from_clipboard_validation;

	wxButton *b_load_test_data, *b_clear_test_data, *b_save_test_data, 
			*b_replace_symbol_test, *b_find_symbol_test, * b_paste_from_clipboard_test;

	wxButton *b_move_validation_to_training, *b_move_test_to_training;
	
	t_list_view_data* g_training_data, *g_test_data, *g_validation_data;
	wxTextCtrl *tc_problem_description;

	wxButton* b_save_all_data;

	
	// settings and params
	wxWindow *w_parameters;
	wxButton *b_settings;

	wxButton *b_to_numeric_data, *b_scale_data;

	wxNotebook* n_error_tables;

	t_lv_output_target_error *g_error_training, *g_error_testing, *g_error_validation, *g_predictions;

	wxButton* b_save_error_tables;// , * b_copy_error_table;
	wxButton *b_save_code, *b_to_clipboard_code;
	wxStaticText *st_code;

    wxButton *b_new_project, *b_load_project, *b_save_project, *b_save_as_project, *b_about, * tb_update;
	wxStaticText *st_runs_errors;

	wxBoxSizer *bs_main_toolbar;

    wxTextCtrl *sc_deme_size, *sc_code_length, *sc_num_generations, *sc_tournament_size, *sc_random_seed, *sc_num_runs, *sc_num_demes, *tc_num_cores;
    wxStaticText *st_deme_size, *st_code_length, *st_num_generations, *st_tournament_size, *st_random_seed, *st_num_runs, *st_num_demes, *st_mutation_prob, *st_crossover_prob, *st_num_cores;
	wxRadioBox *rb_problem_type;
	wxRadioBox *rb_data_type;
	wxTextCtrl *tc_mutation_prob, *tc_crossover_prob;

	wxTextCtrl *tc_operators_probability, *tc_variables_probability, *tc_constants_probability;
	wxStaticText *st_operators_probability, *st_variables_probability, *st_constants_probability;

	wxCheckBox *cb_use_validation_set;

	wxStaticText *st_num_constants;
	wxTextCtrl *sc_num_constants;

	wxRadioBox *rb_constants_type;
	wxTextCtrl *tc_min_interval_constants, *tc_max_interval_constants;
	wxStaticText *st_min_interval_constants, *st_max_interval_constants;

	wxListBox *lv_constants;
	wxButton *b_add_constant;
	wxButton *b_delete_constant;

	wxCheckBox *cb_evolve_constants;
	wxStaticText *st_stddev;
	wxTextCtrl *tc_stddev;

	wxStaticText *st_language, *st_expression;

	wxRadioBox *rb_crossover_type;
		
	wxTextCtrl *tc_source_code;
	wxComboBox *cb_language;
	wxCheckBox *cb_simplified_code;

	wxTextCtrl *tc_subset_size;
	wxStaticText * st_subset_size;

	wxPanel* p_chart_target_output;

	// result

	wxCheckBox* cb_pop_average_evolution, *cb_validation_evolution;
	wxPanel* p_chart_evolution;
	t_list_view_stats_errors *g_stats;

	wxButton* b_save_stats;// , * b_copy_stats;

    wxButton *b_start, *b_stop;

	double scale_evolution_y, scale_evolution_x;
	wxRadioBox *rb_error_measure;

	wxFileDialog *fd_open_data;
	wxFileDialog *fd_open_project;

	bool is_on_timer_running;

	wxStatusBar *sb_status;

	wxTextCtrl *tc_num_generations_for_which_random_subset_is_kept_fixed;
	wxStaticText * st_num_generations_for_which_random_subset_is_kept_fixed;

	t_seed random_seed;

	wxString best_num_incorrectly_classified_percent, average_num_incorrectly_classified_percent, 
			num_incorrectly_classified;

	bool saved_to_numeric_state;
	bool saved_to_time_series_state;

	wxRadioBox* rb_time_series_mode;
	wxCheckBox* cb_evolve_constants_outside_initial_interval;
	
private:

	wxImageList* il_notebook;

	std::thread *mep_engine_thread;
	wxTimer *t_timer;
	//int chart_margin;
	
	void start(void);

    void create_interface(void);
	void create_data_ui(void);
	void create_params_ui(void);
	void create_results_ui(void);

    void OnExitMenuClicked(wxCommandEvent&);
	void on_save_project_button_clicked(wxCommandEvent &event);
	void on_save_as_project_button_clicked(wxCommandEvent &event);
	void on_load_project_button_clicked(wxCommandEvent &event);
	void on_new_project_button_clicked(wxCommandEvent &event);

	void on_settings_button_clicked(wxCommandEvent &event);

	void on_load_training_data_button_clicked(wxCommandEvent &event);
	void on_load_validation_data_button_clicked(wxCommandEvent& event);
	void on_load_test_data_button_clicked(wxCommandEvent& event);

	void on_clear_training_data_button_clicked(wxCommandEvent &event);
	void on_clear_validation_data_button_clicked(wxCommandEvent &event);
	void on_clear_test_data_button_clicked(wxCommandEvent &event);

	void on_save_data_button_clicked(wxCommandEvent &event);
	void on_save_all_data_button_clicked(wxCommandEvent& event);
	void on_to_numeric_data_button_clicked(wxCommandEvent &event);
	void on_scale_data_button_clicked(wxCommandEvent &event);

	void on_move_training_to_validation_button_clicked(wxCommandEvent &event);
	void on_move_training_to_test_button_clicked(wxCommandEvent &event);
	void on_move_validation_to_training_button_clicked(wxCommandEvent &event);
	void on_move_test_to_training_button_clicked(wxCommandEvent &event);

	void on_paste_from_clipboard_training_button_clicked(wxCommandEvent& event);
	void on_paste_from_clipboard_validation_button_clicked(wxCommandEvent& event);
	void on_paste_from_clipboard_test_button_clicked(wxCommandEvent& event);

	void on_replace_symbol_button_clicked(wxCommandEvent &event);
	void on_find_symbol_button_clicked(wxCommandEvent &event);
	void on_shuffle_data_button_clicked(wxCommandEvent &event);

	void on_num_outputs_training_button_clicked(wxCommandEvent& event);

	
	void on_start_button_clicked(wxCommandEvent &event);
	void on_stop_button_clicked(wxCommandEvent &event);
	void on_about_button_clicked(wxCommandEvent &event);

	void on_close_window_clicked(wxCloseEvent&);

	void clear_results(void);
	void disable_when_start(void);
	void enable_when_stop(void);

	void do_problem_type_changed(void);
	void do_data_type_changed(void);
	void on_constants_type_change(wxCommandEvent& event);
	void on_selection_operators_clicked(wxCommandEvent& event);
	void on_use_constants_clicked(wxCommandEvent& event);

	wxString get_project_filename_to_save(void);
	bool do_save_project(const char*);

	void on_stats_row_change(wxListEvent& event);
	
	void on_operator_clicked(wxCommandEvent& event);
	void on_evolve_constants_clicked(wxCommandEvent& event);

	void on_paint_chart_evolution(wxPaintEvent & evt);
	void on_paint_chart_output_target(wxPaintEvent& evt);

	void on_change_value_spin_ctrl(wxSpinEvent& event);
	void on_change_param_value(wxCommandEvent& event);
	void on_change_num_predictions_value(wxCommandEvent& event);
	void on_problem_type_change_rb_clicked(wxCommandEvent& event);
	void on_change_data_type_rb_clicked(wxCommandEvent& event);
	void on_error_measure_change_rb_clicked(wxCommandEvent& event);
	void on_time_series_mode_change_rb_clicked(wxCommandEvent& event);
	void on_update_button_clicked(wxCommandEvent& event);
	void on_add_constant_button_clicked(wxCommandEvent& event);
	void on_delete_constant_button_clicked(wxCommandEvent& event);

	void show_errors_in_grids(int run);
	void show_predictions_in_grid(int run);
	void show_program(int run);

	void set_run_stats(int run);
	void set_status_bar_info(int run, int generation);

	int last_processed_run;
	int last_processed_generation;

	void set_results(void);

	bool loading_data;

	bool validate_project(char * error_message);
	void on_save_code_button_clicked(wxCommandEvent &);
	void on_to_clipboard_code_button_clicked(wxCommandEvent&);

	void on_save_errors_button_clicked(wxCommandEvent &);
	//void on_copy_to_clipboard_errors_button_clicked(wxCommandEvent&);
	void on_save_stats_button_clicked(wxCommandEvent &);
	//void on_copy_stats_to_clipboard_button_clicked(wxCommandEvent &);

	void draw_evolution(wxClientDC& dc);
	void do_draw_legend_evolution(wxClientDC& dc);
	void do_draw_legend_target_output(wxClientDC& dc);

	void on_change_selected_constants(wxCommandEvent& event);

	void on_operators_probabilities_change(wxFocusEvent& event);

	void on_simplified_code_clicked(wxCommandEvent &);

	void on_change_problem_description(wxCommandEvent& event);
	void on_change_data_page(wxBookCtrlEvent& event);

	//void on_sort_stats_grid(wxGridEvent& event);

	//void on_stats_grid_header_right_clicked(wxGridEvent& event);
	void on_training_grid_header_right_clicked(wxListEvent& event);
	void on_code_language_changed(wxCommandEvent& event);

	void on_chart_target_output_clicked(wxCommandEvent& event);
	void on_chart_evolution_clicked(wxCommandEvent& event);

	wxMenu *m_training_columns;

	void on_use_columns_clicked(wxCommandEvent& event);
	void on_rename_column_clicked(wxCommandEvent& event);

	void on_training_col_move(wxGridEvent& event);
    
	wxMenuItem *mi_use_column, *mi_rename_column;

	int right_clicked_col;

	void on_timer(wxTimerEvent& event);
	void on_resize_chart_evolution(wxSizeEvent& event);
	void on_resize_chart_target_output(wxSizeEvent& event);
	void do_draw_first_generation(wxClientDC& dc, int run_index);
	void do_draw_next_generations(wxClientDC& dc, int run_index, int gen_index);
	void process_on_stats_row_change(int row_index);
	int draw_output_and_target(wxClientDC& dc, int current_selected_target);
	void build_panel_error_tables(wxPanel* p_error_tables);
	void build_panel_chart(wxPanel* p_target_output);
	void build_panel_code(wxPanel* p_code_chart_target_output);
	void build_runs_evolution_panel(void);
	void build_results_model_code_chart_panel(void);
	void build_code_chart_panel(wxPanel* p_code_chart);

	bool load_project(void);
	void set_language(void);

	void update_training_buttons(void);
	void update_validation_buttons(void);
	void update_test_buttons(void);

	void set_project_info(void);

	void set_functions_to_UI(const t_mep_functions* mep_operators, int data_type);
	void set_enabled_functions_to_UI(const t_mep_functions * mep_operators,
									 int data_type);
	void get_functions_from_UI(t_mep_functions* mep_operators);

	void set_parameters_to_UI(const t_mep_parameters* mep_parameters);
	bool get_parameters_from_UI(t_mep_parameters* mep_parameters, char* error_string);

	void set_interface_layout(const t_mepx_interface_layout* p);
	void get_interface_layout(t_mepx_interface_layout* p);

	bool get_constants_from_UI(t_mep_constants* mep_constants, char* error_message, char data_type);
	void set_constants_to_UI(double constants_probability, const t_mep_constants* mep_constants, char data_type);
	void set_enable_constants(double constants_probability, const t_mep_constants* mep_constants);
	void update_results(void);

	void update_results_buttons(void);

	void OnShow(wxShowEvent& event);

	void update_advance_commands_buttons(void);

	void on_change_main_notebook_page(wxBookCtrlEvent& event);
	//unsigned int compute_num_data_to_draw(void);
	/*
	void compute_target_to_draw(double* target, char* has_target, double& min_data, double& max_data);
	void compute_output_to_draw(double* output, char* correct_output, double& min_data, double& max_data);
	void compute_output_to_draw_time_series(double* output, char* correct_output, double& min_data, double& max_data);
	void compute_output_to_draw_regression_and_classification(double* output, char* correct_output, double& min_data, double& max_data);
	*/
	void draw_chart_separators(wxClientDC& dc, int offset);
	void set_target_output_chart_options(const t_mepx_target_output_chart_options& p);
	void get_target_output_chart_options(t_mepx_target_output_chart_options& p);
	void on_change_errors_notebook_page(wxBookCtrlEvent& event);
	
	void set_evolution_chart_options(const t_mepx_evolution_chart_options& p);
	void get_evolution_chart_options(t_mepx_evolution_chart_options& p);

	void set_enabled_grid_columns(void);
	void get_enabled_grid_columns(void);
	
	wxBoxSizer* sizer_toolbar_stats;
	
	void update_target_combobox(void);
	void update_num_target_cols_to_data_grids(void);
};
//-------------------------------------------------------------------------
extern t_main_window* f_main_window;
//-------------------------------------------------------------------------
#endif
