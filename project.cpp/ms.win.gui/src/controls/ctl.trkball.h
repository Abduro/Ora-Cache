#ifndef _CTL_TRKBALL_H_INCLUDED
#define _CTL_TRKBALL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 12:01:30.859, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx trackball user control wrapper interface declaration file;
*/
#include "win.gui.inc.h"
#include "sfx.trkball.ctrl.h"

namespace ebo { namespace boo { namespace gui { namespace ctl {

	using namespace ebo::boo::gui;

	using CTrkball = ex_ui::controls::sfx::track::CControl;

	class CTracker {
	public:
		 CTracker (void); CTracker (const CTracker&) = delete; CTracker (CTracker&&) = delete;
		~CTracker (void);

	public:
		err_code  At_1st(void);
		TError&   Error (void) const;
		const
		CTrkball& Get (void) const;
		CTrkball& Get (void) ;

		err_code  OnCreate (const HWND _h_page) ;
		err_code  OnDestroy(void) ;

	public:
		const
		CTrkball& operator ()(void) const;
		CTrkball& operator ()(void);

	private:
		CTracker& operator = (const CTracker&) = delete; CTracker& operator = (CTracker&&) = delete;
		CError   m_error ;
		CTrkball m_tracker;
	};
}}}}

#endif/*_CTL_TRKBALL_H_INCLUDED*/