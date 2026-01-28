// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------
#include "mepx_interface_layout.h"
//---------------------------------------------------------
t_mepx_interface_layout::t_mepx_interface_layout(void)
{
	init();
}
//---------------------------------------------------------
void t_mepx_interface_layout::init(void)
{
	stats_table_width = stats_table_height = errors_table_width = code_box_height = 300;
}
//---------------------------------------------------------
void t_mepx_interface_layout::to_xml_node(pugi::xml_node parent) const
{
	char tmp_str[15];
	pugi::xml_node node = parent.append_child("stats_table_width");
	pugi::xml_node data = node.append_child(pugi::node_pcdata);
	snprintf(tmp_str, 15, "%d", stats_table_width);
	data.set_value(tmp_str);

	node = parent.append_child("stats_table_height");
	data = node.append_child(pugi::node_pcdata);
	snprintf(tmp_str, 15, "%d", stats_table_height);
	data.set_value(tmp_str);

	node = parent.append_child("errors_table_width");
	data = node.append_child(pugi::node_pcdata);
	snprintf(tmp_str, 15, "%d", errors_table_width);
	data.set_value(tmp_str);

	node = parent.append_child("code_box_height");
	data = node.append_child(pugi::node_pcdata);
	snprintf(tmp_str, 15, "%d", code_box_height);
	data.set_value(tmp_str);
}
//---------------------------------------------------------
bool t_mepx_interface_layout::from_xml_node(pugi::xml_node parent)
{
	pugi::xml_node node = parent.child("stats_table_width");
	if (node){
		const char *value_as_cstring = node.child_value();
		stats_table_width = atoi(value_as_cstring);
	}

	node = parent.child("stats_table_height");
	if (node){
		const char *value_as_cstring = node.child_value();
		stats_table_height = atoi(value_as_cstring);
	}

	node = parent.child("errors_table_width");
	if (node){
		const char *value_as_cstring = node.child_value();
		errors_table_width = atoi(value_as_cstring);
	}

	node = parent.child("code_box_height");
	if (node) {
		const char* value_as_cstring = node.child_value();
		code_box_height = atoi(value_as_cstring);
	}

	return true;
}
//---------------------------------------------------------
