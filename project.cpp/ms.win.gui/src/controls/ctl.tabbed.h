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
	static const uint16_t n_count = 2; // how many tabs will be appended to the tabbed control;
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
#if (0)
		// returning the reference to fake object in case of invalid input index looks like to be not good approach;
		const
		CTracker& Tracker (const uint16_t _n_index) const; // gets the reference to the tracker that is associated with the page on input index;
		CTracker& Tracker (const uint16_t _n_index)      ; // gets the reference to the tracker that is associated with the page on input index;
#else
		const
		CTracker* Tracker (const uint16_t _n_index) const; // returns nullptr in case if input index is out of acceptable range;
		CTracker* Tracker (const uint16_t _n_index)      ; // returns nullptr in case if input index is out of acceptable range;
#endif
	private:
		CPages& operator = (const CPages&) = delete; CPages& operator = (CPages&&) = delete;
		mutable
		CError   m_error ;
		CTabbed  m_tabbed;
		CTracker m_trackers[CPages::n_count];
	};

}}}}

#endif/*_CTL_TABBED_H_INCLUDED*/