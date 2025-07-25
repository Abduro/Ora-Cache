#ifndef _WIN_GUI_FRAME_H_INCLUDED
#define _WIN_GUI_FRAME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Nov-2024 at 0:59:33.0970970, UTC+4, Batumi, Wednesday;
	This is Ebo Pack draw renderer test app main frame interface declration file;
*/
#include "win.gui.inc.h"
#include "win.gui.res.h"
#include "win.gui_wnd.h"

#include "shared.timer.h"

namespace ebo { namespace boo { namespace gui {

	using CError = shared::sys_core::CError;
	using TError = const CError;
#if (0)
#define _ATL_NO_AUTOMATIC_NAMESPACE // https://learn.microsoft.com/en-us/cpp/atl/reference/compiler-options-macros ;
#endif

	using CAtom = ex_ui::popup::CAtom;
	using CWnd  = ebo::boo::gui::CWnd;

	using IWaitable_Events = shared::common::IWaitable_Events;
	using CStdTimer = shared::common::CStdTimer;

	using TString = TStringEx;

	class CFrame : public IWaitable_Events {
	public:
		class CIcon : public ex_ui::resource::CIcon { typedef ex_ui::resource::CIcon TBase;
		public:
			 CIcon (const CFrame&);
			 CIcon (void) = delete;
			 CIcon (const CIcon&) = delete; CIcon (CIcon&&) = delete;
			~CIcon (void);

		public:
			err_code Set (const uint16_t _u_res_id); // sets icons of both sizes (small & large) to main frame window;

		private:
			CIcon& operator = (const CIcon&) = delete;
			CIcon& operator = (CIcon&&) = delete;

		private:
			const CFrame& m_frame;
		};

	public:
		 CFrame (void);
		 CFrame (const CFrame&) = delete;
		 CFrame (CFrame&&) = delete;
		~CFrame (void);

	public:
		err_code Create (void);
		err_code Destroy(void);
		TError&  Error  (void) const;

		const
		CIcon&   Icon (void) const;
		CIcon&   Icon (void) ;

		const
		CWnd&    Window (void) const; // gets a reference to main window; (ro)
		CWnd&    Window (void) ;      // gets a reference to main window; (rw)

	private:
		CFrame&  operator = (const CFrame&) = delete;
		CFrame&  operator = (CFrame&&) = delete;

		virtual void IWaitable_OnComplete(void) override final;

	private:
		CError   m_error;
		CIcon    m_icon ;
		CWnd     m_wnd  ;

		CStdTimer m_wait;
	};

}}}

#endif/*_WIN_GUI_FRAME_H_INCLUDED*/