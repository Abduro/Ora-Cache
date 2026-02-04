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

	using CWindow = ::ATL::CWindow;

	class CFrame {
	public:
		class CIcons { // declaration this class here is just trying to create an illusion of the object-oriented programming;
		public:
			CIcons (void); CIcons (const CIcons&) = delete; CIcons (CIcons&&) = delete; ~CIcons (void) = default;

			TError&  Error (void) const;
			err_code Set (const uint16_t _u_res_id); // sets icons of both sizes (small: 16x16px & large: 32x32px) to the app window;

		private:
			CIcons& operator = (const CIcons&) = delete; CIcons& operator = (CIcons&&) = delete;
			CError  m_error;
		};
		class CPosition { // *note*: 'position' is the state of being, while 'placement' is the action of placing;
		public:
			CPosition (void); CPosition (const CPosition&) = delete; CPosition (CPosition&&) = delete; ~CPosition (void);

			TError&  Error(void) const;
			err_code Load (void); // loads the app/main window position from the regestry;
			err_code Save (void); // saves the app/main window position in the regestry; *note*: 'in'-'position'(where), 'into'-'direction/motion'(where to);

			const
			t_rect&  Get (void) const;    // gets the reference to the rectangle of the main window frame position on the screen; (ro);
			bool     Set (const t_rect&); // sets the window rectangle;

			const
			t_rect&  operator ()(void) const;
			t_rect&  operator ()(void) ;

			CPosition& operator <<(const t_rect&);

		private:
			CPosition& operator = (const CPosition&) = delete; CPosition& operator = (CPosition&&) = delete;
			t_rect m_rect;
			CError m_error;
		};
		class CSize {
		public:
			CSize (void); CSize (const CSize&) = delete; CSize (CSize&&) = delete; ~CSize (void) = default;
			bool Is_locked (void) const;           // returns the lock state of the main window frame size, if it is 'true' the window size cannot be changed;
			bool Is_locked (const bool _b_state);  // sets the lock state of the main window frame rectangle (not its position, the window is still moveable); 
		private:
			CSize& operator = (const CSize&) = delete; CSize& operator = (CSize&&);
			bool   m_locked;
		};
		
	public:
#pragma region iface::CFrame{}
		 CFrame (void); CFrame (const CFrame&) = delete; CFrame (CFrame&&) = delete;
		~CFrame (void);

		const
		CIcons& Icons (void) const;
		CIcons& Icons (void) ;
		const
		CPosition& Position (void) const;
		CPosition& Position (void) ;
		const
		CSize&  Size (void) const;
		CSize&  Size (void) ;
#pragma endregion
	private:
		CFrame& operator = (const CFrame&) = delete; CFrame& operator = (CFrame&&) = delete;
		CIcons    m_icons;
		CPosition m_pos;
		CSize     m_size;
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

shared::gui::CAppWnd&  Get_app_wnd (void); // the main window of any desktop application can be the only one;

#endif/*_WIN_GUI_WND_H_INCLUDED*/