// Multi Expression Programming X
// Author: Mihai Oltean, mihai.oltean@gmail.com
// https://mepx.org
// https://github.com/mepx
// License: MIT
//-----------------------------------------------------------------
#ifndef mepx_app_H
#define mepx_app_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
// -----------------------------------------------------------------
class t_MEPX : public wxApp{
public:
	wxString settings_path;
	bool run_from_command_line;
	
	virtual bool OnInit();
	virtual int OnExit();
	virtual int OnRun();
	void optimize_from_command_line(void);

	t_MEPX(void);
};
// -----------------------------------------------------------------
#endif
