// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef MEPX_INTERFACE_LAYOUT_H
#define MEPX_INTERFACE_LAYOUT_H

//-------------------------------------------------------------------------
#include "utils/pugixml.hpp"
//-------------------------------------------------------------------------
class t_mepx_interface_layout{
public:
	int stats_table_width, stats_table_height, errors_table_width;
	int code_box_height;

	t_mepx_interface_layout(void);
	void init(void);
	void to_xml_node(pugi::xml_node parent) const;
	bool from_xml_node(pugi::xml_node parent);
};
//-------------------------------------------------------------------------

#endif
