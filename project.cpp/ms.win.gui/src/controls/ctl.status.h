#ifndef _CTL_STATUS_H_INCLUDED
#define _CTL_STATUS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 11:56:29.569, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx status bar user control wrapper interface declaration file;
*/
#include "win.gui.inc.h"
#include "sys.gen.time.h"      // data_&_time wrappers';
#include "shared.timer.h"      // system timers' wrappers;
#include "sfx.status.ctrl.h"   // statusbar user control;

namespace ebo { namespace boo { namespace gui { namespace ctl {

	using CSta_bar = ex_ui::controls::sfx::status::CControl;

	class CStatus : private shared::common::IWaitable_Events {
	public:
		 CStatus (void); CStatus (const CStatus&) = delete; CStatus (CStatus&&) = delete;
		~CStatus (void);

	public:
		err_code  At_1st(void) ;     // this is just *before* creating status bar control window: all sections/panes must be defined;
		TError&   Error (void) const;
		const
		CSta_bar& Get (void) const;
		CSta_bar& Get (void) ;

		err_code  OnCreate  (void) ; // this method must be called from main window on 'create' event handler; *status bar* must be ready;
		err_code  OnDestroy (void) ;

		void  SetText(_pc_sz _p_text, const uint16_t _pane_ndx = 1);
		const
		CSta_bar& operator ()(void) const;
		CSta_bar& operator ()(void);

	private:
		void IWaitable_OnComplete (void) override final;

	private:
		CStatus& operator = (const CStatus&) = delete; CStatus& operator = (CStatus&&) = delete;
		CError   m_error;
		CSta_bar m_status;
		shared::common::CStdTimer m_timer;
	};

}}}}

#endif/*_CTL_STATUS_H_INCLUDED*/