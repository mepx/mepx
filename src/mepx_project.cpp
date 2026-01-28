// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <cstring>
//-----------------------------------------------------------------
#include "mepx_project.h"
//-----------------------------------------------------------------
t_mepx_settings mepx_settings;

t_model_target_error_data_provider training_data_error_provider, validation_data_error_provider, test_data_error_provider, prediction_data_provider;

char s_runs_errors_label_regression[100];
char s_runs_errors_label_classification[100];

t_mep_run_errors_array run_errors;
//-----------------------------------------------------------------
t_mepx_settings::t_mepx_settings()
{
}
//-----------------------------------------------------------------
t_mepx_settings::~t_mepx_settings()
{
}
//-----------------------------------------------------------------
int t_mepx_settings::to_xml_file(const char *filename)
{
	char* old_locale = setlocale(LC_NUMERIC, NULL);
	char* saved_locale = strdup (old_locale);

	setlocale(LC_NUMERIC, "C");

	pugi::xml_document doc;
	// add node with some name
	pugi::xml_node body = doc.append_child("settings");

	pugi::xml_node interface_node = body.append_child("interface");
	interface_layout.to_xml_node(interface_node);

	bool save_result = false;
#ifdef _WIN32
	int count_chars = MultiByteToWideChar(CP_UTF8, 0, filename, -1, NULL, 0);
	wchar_t *w_filename = new wchar_t[count_chars];
	MultiByteToWideChar(CP_UTF8, 0, filename, -1, w_filename, count_chars);

	save_result = doc.save_file(w_filename);
	delete[] w_filename;
#else
	save_result = doc.save_file(filename);
#endif

	// restore locale
	setlocale (LC_NUMERIC, saved_locale);
	free (saved_locale);

	return save_result;
}
//-----------------------------------------------------------------
int t_mepx_settings::from_xml_file(const char* _filename)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result;

#ifdef _WIN32
	int count_chars = MultiByteToWideChar(CP_UTF8, 0, _filename, -1, NULL, 0);
	wchar_t *w_filename = new wchar_t[count_chars];
	MultiByteToWideChar(CP_UTF8, 0, _filename, -1, w_filename, count_chars);

	result = doc.load_file(w_filename);
	delete[] w_filename;
#else
	result = doc.load_file(_filename);
#endif

	if (result.status != pugi::status_ok) {
		return false;
	}

	char* old_locale = setlocale(LC_NUMERIC, NULL);
	char* saved_locale = strdup (old_locale);
	setlocale(LC_NUMERIC, "C");

	pugi::xml_node body_node = doc.child("settings");

	if (!body_node) {
		setlocale(LC_NUMERIC, saved_locale);
		free (saved_locale);
		return false;
	}

	pugi::xml_node interface_node = body_node.child("interface");

	if (interface_node)
		interface_layout.from_xml_node(interface_node);

	setlocale(LC_NUMERIC, saved_locale);
	free (saved_locale);

	return true;
}
//-----------------------------------------------------------------
bool to_xml_file(const char *filename,
		   const char *version)
{
	char* old_locale = setlocale(LC_NUMERIC, NULL);
	char* saved_locale = strdup (old_locale);
	setlocale(LC_NUMERIC, "C");
	
	pugi::xml_document doc;
	// add node with some name
	pugi::xml_node project_node = doc.append_child("project");
	/*
	pugi::xml_node version_node = project_node.append_child("mepx_version");
	pugi::xml_node data_node = version_node.append_child(pugi::node_pcdata);
	data_node.set_value(version);
	*/
	/*
	if (mepx_interface_settings) {
		pugi::xml_node interface_settings_node = body.append_child("interface_settings");
		mepx_interface_settings->to_xml_node(interface_settings_node);
	}
	*/

	pugi::xml_node problem_description_node = project_node.append_child("problem_description");
	pugi::xml_node data_node = problem_description_node.append_child(pugi::node_pcdata);
	data_node.set_value(mep_engine.get_problem_description());

	pugi::xml_node alg_node = project_node.append_child("algorithm");
	mep_engine.to_xml_node(alg_node);
	
	bool save_result = false;
#ifdef _WIN32
	int count_chars = MultiByteToWideChar(CP_UTF8, 0, filename, -1, NULL, 0);
	wchar_t *w_filename = new wchar_t[count_chars];
	MultiByteToWideChar(CP_UTF8, 0, filename, -1, w_filename, count_chars);

	save_result = doc.save_file(w_filename);
	delete[] w_filename;
#else
	save_result = doc.save_file(filename);
#endif
	setlocale(LC_NUMERIC, saved_locale);
	free (saved_locale);

	return save_result;
}
//-----------------------------------------------------------------
bool from_xml_file(const char* filename)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result;

#ifdef _WIN32
	int count_chars = MultiByteToWideChar(CP_UTF8, 0, filename, -1, NULL, 0);
	wchar_t *w_filename = new wchar_t[count_chars];
	MultiByteToWideChar(CP_UTF8, 0, filename, -1, w_filename, count_chars);

	result = doc.load_file(w_filename);
	delete[] w_filename;
#else
	result = doc.load_file(filename);
#endif

	if (result.status != pugi::status_ok) {
		return false;
	}

	char* old_locale = setlocale(LC_NUMERIC, NULL);
	char* saved_locale = strdup (old_locale);
	setlocale(LC_NUMERIC, "C");

	pugi::xml_node project_node = doc.child("project");

	if (!project_node) {
		setlocale(LC_NUMERIC, saved_locale);
		free (saved_locale);
		return false;
	}

	//pugi::xml_node settings_node = project_node.child("settings");
	//if (settings_node)
	//mepx_interface_settings.from_xml_file(settings_node);

	pugi::xml_node node = project_node.child("problem_description");
	if (node) {
		const char *value_as_cstring = node.child_value();
		if (strlen(value_as_cstring)) {
			mep_engine.set_problem_description(value_as_cstring);
		}
	}
	else {
		mep_engine.set_problem_description("Problem description here ...");
	}

	pugi::xml_node alg_node = project_node.child("algorithm");

	if (!alg_node) {
		setlocale(LC_NUMERIC, saved_locale);
		free (saved_locale);

		return false;
	}

	mep_engine.from_xml_node(alg_node);

	setlocale(LC_NUMERIC, saved_locale);
	free (saved_locale);

	return true;
}
//-----------------------------------------------------------------
unsigned int compute_num_data_to_draw(void)
{
	unsigned int num_data = 0;
	if (!mepx_settings.target_output_chart_options.cb_chart_target &&
		!mepx_settings.target_output_chart_options.cb_chart_output)
		return 0;

	if (mepx_settings.target_output_chart_options.cb_chart_training_target_output)
		num_data += mep_engine.get_training_data_ptr()->get_num_rows();
	if (mepx_settings.target_output_chart_options.cb_chart_validation_target_output)
		num_data += mep_engine.get_validation_data_ptr()->get_num_rows();
	if (mepx_settings.target_output_chart_options.cb_chart_testing_target_output)
		num_data += mep_engine.get_test_data_ptr()->get_num_rows();
	if (mepx_settings.target_output_chart_options.cb_chart_predictions_target_output &&
		mepx_settings.target_output_chart_options.cb_chart_output)
		num_data += mep_engine.get_parameters_ptr()->get_num_predictions();

	return num_data;
}
//---------------------------------------------------------------------
