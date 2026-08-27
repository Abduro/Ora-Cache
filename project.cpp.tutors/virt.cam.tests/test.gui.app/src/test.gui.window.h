#ifndef _TEST_GUI_WINDOW_H_INCLUDED
#define _TEST_GUI_WINDOW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2026 at 08:31:06.800, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' desktop GUI main window interface declaration file;
*/
#include "common.defs.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	// https://learn.microsoft.com/en-us/cpp/atl/implementing-a-window-with-cwindowimpl ;
	class CMainWnd  : public ::ATL::CWindowImpl<CMainWnd> { typedef ::ATL::CWindowImpl<CMainWnd> TWindow;
	public:
		 CMainWnd (void); CMainWnd (const CMainWnd&) = delete; CMainWnd (CMainWnd&&) = delete;
		~CMainWnd (void);

		static
		const uint32_t u_style = CS_DBLCLKS/*| CS_OWNDC*/; // cs_owndc is not required: OpenGL rendering context is not used in this project;

		DECLARE_WND_CLASS_EX(_T("test::app::CMainWnd"), u_style, COLOR_ACTIVECAPTION);

		BEGIN_MSG_MAP(CMainWnd)
			MESSAGE_HANDLER (WM_CREATE , OnCreate ) // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-create  ;
			MESSAGE_HANDLER (WM_DESTROY, OnDestroy) // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-destroy ;
		END_MSG_MAP()
	private:
		l_result OnCreate  (const uint32_t, const l_param, const w_param, bool_t& _b_handled);
		l_result OnDestroy (const uint32_t, const l_param, const w_param, bool_t& _b_handled);
	public:
		err_code Create (void);
		err_code Destroy (void);
	};

}}


#endif/*_TEST_GUI_WINDOW_H_INCLUDED*/