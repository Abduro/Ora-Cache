#ifndef _WIN_GUI_FRAME_H_INCLUDED
#define _WIN_GUI_FRAME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Nov-2024 at 0:59:33.0970970, UTC+4, Batumi, Wednesday;
	This is window popup test app main frame interface declration file;
*/
#include "sys.error.h"
#include "wnd.layout.h"
#include "wnd.res.h"

#include "win.gui.res.h"
#include "win.gui_wnd.h"

namespace ebo { namespace boo { namespace gui {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using CView  = ebo::boo::gui::CWindow;

	class CFrame {
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
		CView&   View (void) const;
		CView&   View (void) ;

	private:
		CFrame&  operator = (const CFrame&) = delete;
		CFrame&  operator = (CFrame&&) = delete;

	private:
		CError   m_error;
		CIcon    m_icon ;
		CWindow  m_window;
	};

}}}

#endif/*_WIN_GUI_FRAME_H_INCLUDED*/