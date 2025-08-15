#ifndef _CTL_TRKBALL_H_INCLUDED
#define _CTL_TRKBALL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 12:01:30.859, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx trackball user control wrapper interface declaration file;
*/
#include "win.gui.inc.h"
#include "sfx.tabs.ctrl.h"   // is required for getting ex_ui::controls::sfx::tabbed::CTab class interface;
#include "sfx.trkball.ctrl.h"

namespace ebo { namespace boo { namespace gui { namespace ctl {

	using namespace ebo::boo::gui;

	using CTrkball = ex_ui::controls::sfx::track::CControl;

	class CTracker {
		using CTab = ex_ui::controls::sfx::tabbed::CTab;
	public:
		 CTracker (void); CTracker (const CTracker&) = delete; CTracker (CTracker&&) = delete;
		~CTracker (void);

	public:
		err_code  At_1st(void);
		TError&   Error (void) const;
		const
		CTrkball& Get (void) const;
		CTrkball& Get (void) ;

		err_code  OnCreate (const CTab&) ;
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

	class CTrackers {
	public:
		 CTrackers (void); CTrackers (const CTrackers&) = delete; CTrackers (CTrackers&&) = delete;
		~CTrackers (void);

		err_code  At_1st(void);
		TError&   Error (void) const;

		err_code  OnCreate (void) ;
		err_code  OnDestroy(void) ;

#if (0)
		// returning the reference to fake object in case of invalid input index looks like to be not good approach;
		const
		CTracker& Get(const uint16_t _n_index) const; // gets the reference to the tracker that is associated with the page on input index;
		CTracker& Get(const uint16_t _n_index)      ; // gets the reference to the tracker that is associated with the page on input index;
#else
		const
		CTracker* Get (const uint16_t _n_index) const; // returns nullptr in case if input index is out of acceptable range;
		CTracker* Get (const uint16_t _n_index)      ; // returns nullptr in case if input index is out of acceptable range;
#endif

	private:
		CTracker  m_trackers[cfg::n_page_count];
		CError    m_error ;
	};
}}}}

#endif/*_CTL_TRKBALL_H_INCLUDED*/