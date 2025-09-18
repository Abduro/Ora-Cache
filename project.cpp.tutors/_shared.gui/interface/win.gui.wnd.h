#ifndef _WIN_GUI_WND_H_INCLUDED
#define _WIN_GUI_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Sep-2025 at 18:26:16.505, UTC+4, Batumi, Thursday;
	This is Ebo_Pack tutorials' shared app/main window interace declaration file;
*/
#include "shared.wnd.base.h"
#include "shared.wnd.res.h"
#include "shared.wnd.layout.h"

#include "win.gui.wnd.layout.h"

namespace shared { namespace gui {

	using namespace shared::defs;
	using namespace shared::types;

	using namespace ex_ui::popup;
//	using namespace ex_ui::popup::layout;

	using CWindow = ::ATL::CWindow;

	class CFrame {
	public:
		class CIcons { // declaration this class here is just trying to create an illusion of the object-oriented programming;
		public:
			CIcons (CFrame* const = 0); CIcons (const CIcons&) = delete; CIcons (CIcons&&) = delete; ~CIcons (void) = default;

			err_code Set (const uint16_t _u_res_id); // sets icons of both sizes (small & large) to the window handle;

		private:
			CIcons& operator = (const CIcons&) = delete; CIcons& operator = (CIcons&&) = delete;
			CFrame* const m_p_frm;
		};
		
	public:
		 CFrame (void); CFrame (const CFrame&) = delete; CFrame (CFrame&&) = delete;
		~CFrame (void);

		const
		CIcons& Icons (void) const;
		CIcons& Icons (void) ;

		const
		CWindow& Window (void) const;
		CWindow& Window (void) ;

	private:
		CIcons  m_icons;
		CWindow m_owner; // this is window handle wrapper which this frame belongs to;

	private:
		CFrame& operator = (const CFrame&) = delete;
		CFrame& operator = (CFrame&&) = delete;
	};

	class CAppWnd : public ex_ui::popup::CWndBase { typedef ex_ui::popup::CWndBase TBase;
	public:
		 CAppWnd (void); CAppWnd (const CAppWnd&) = delete; CAppWnd (CAppWnd&&) = delete;
		~CAppWnd (void);

	public: // IMsg_Handler impl;
		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final; // goes first due to its virtuality;

		// window class name should be unique for better distuingwishing between tutorials, e.g. '__direct_x_ctx' or '__open_gl_ctx';
		// https://www.geeksforgeeks.org/cpp/function-overloading-vs-function-overriding-in-cpp/ ;
		// no window position rectangle is provided in this version yet; it is assigned automatically by this function;

		err_code Create (_pc_sz _p_cls_name, _pc_sz _p_title, const bool _b_visible); // overloads CWndBase::Create();
		err_code Destroy(void); // overrides the parent class destroy() method too, for managing the frame window internal handle;

		const
		CFrame&  Frame (void) const;
		CFrame&  Frame (void) ;
		// overriding the methods of the base class hides the specifics of the layouts to which the reference is returned; must be reviewed;
		const
		shared::gui::CLayout& Layout (void) const;
		shared::gui::CLayout& Layout (void) ;

		const
		TBase& operator ()(void) const;
		TBase& operator ()(void) ;

	private:
		CAppWnd& operator = (const CAppWnd&) = delete; CAppWnd& operator = (CAppWnd&&) = delete;

		CFrame  m_frame ;
		shared::gui::CLayout m_layout;
	};

}}

// the main window in any application can be the only one:
shared::gui::CAppWnd&  Get_app_wnd (void);

#endif/*_WIN_GUI_WND_H_INCLUDED*/