#ifndef _CTL_TABBED_H_INCLUDED
#define _CTL_TABBED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 11:58:34.492, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx tabbed user control wrapper interface declaration file;
*/
#include "win.gui.inc.h"
#include "sfx.tabs.ctrl.h"
#include "ctl.trkball.h"

namespace ebo { namespace boo { namespace gui { namespace ctl {

	using namespace ebo::boo::gui;

	using CTabbed  = ex_ui::controls::sfx::tabbed::CControl;

	class CPages {
	public:
		 CPages (void); CPages (const CPages&) = delete; CPages (CPages&&) = delete;
		~CPages (void);

	public:
		err_code  At_1st(void) ;     // this is just *before* creating tabbed control window: all tabs and their pages must be formatted and added;
		TError&   Error (void) const;
		const
		CTabbed&  Get (void) const;
		CTabbed&  Get (void) ;

		bool Is_valid (void) const;  // validates each page window handle;

		err_code  OnCreate (void) ;
		err_code  OnDestroy(void) ;

		const
		CTrackers& Trackers(void) const;
		CTrackers& Trackers(void) ;

	private:
		CPages& operator = (const CPages&) = delete; CPages& operator = (CPages&&) = delete;
		mutable
		CError    m_error ;
		CTabbed   m_tabbed;
		CTrackers m_tracks;
	};

}}}}

#endif/*_CTL_TABBED_H_INCLUDED*/