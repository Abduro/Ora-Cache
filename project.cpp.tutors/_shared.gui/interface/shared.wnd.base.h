#ifndef _SHARED_WND_BASE_H_INCLUDED
#define _SHARED_WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:39:32.292, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface declaration file;
*/
#include "shared.defs.h"
#include "shared.wnd.atom.h"
#include "shared.wnd.msg.h"

namespace ex_ui { namespace popup {

	using namespace shared::defs;

	// ToDo: Window builder must be involeved into creating new window; the builder must have window style, layout, etc.;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname ; getting class name from the window;

	class CWndBase : protected IMsg_Handler {
	public:
		 CWndBase (void); CWndBase (const CWndBase&) = delete; CWndBase (CWndBase&&) = delete;
		~CWndBase (void);
	protected: // IMsg_Handler impl;
		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override; // goes first due to its virtuality;

	public:
		/* the input parameters are placed in such order specifically in accordance with default values they have;
		   also, taking into account that in the most tutorials the window being created has the desktop as its parent, so it is the last param;
		*/
		err_code Create (_pc_sz _p_cls_name, _pc_sz _p_title, const t_rect&, const bool _b_vidible/* = true*/, const HWND _h_parent/* = 0*/);

		/*
			https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
			https://learn.microsoft.com/en-us/windows/win32/learnwin32/closing-the-window ;
			...
			the excerpt from the destroy window article:
			DestroyWindow() automatically destroys the associated child or owned windows when it destroys the parent or owner window;
			...
			it is the reason why the child window does not unsubcribe from the message queue; this fact must be taken into account;
		*/

		err_code Destroy(void);
		/*
			the excerpt from the article which is referred by the link given above:
			...
			The WM_CLOSE message gives you an opportunity to prompt the user before closing the window.
			If you really do want to close the window, call the DestroyWindow function.
			...
			in this case, no prompt to the user, but just the destroying the window;
		*/

		TError&  Error  (void) const;	
		HWND     Handle (void) const;
		bool  Is_valid  (void) const;

		bool  Is_top (void) const; // checks it is the top window, i.e. is the main window of the app or not; ToDo: possibly the name must be changed;

		void  Set_visible (const bool) const;

	public:
		bool operator == (const CWndBase&) const;
		bool operator == (const HWND) const;
		operator const HWND (void) const;

		CWndBase& operator = (const CWndBase&) = delete;
		CWndBase& operator = (CWndBase&&) = delete;

	protected:
		mutable
		CError  m_error;
		HWND    m_h_wnd;
		
	public:
		class CLayout {
		public:
			class CSize {
			public:
				CSize (const uint32_t _u_cx = 0, const uint32_t _u_cy = 0); CSize (const CSize&) = delete; CSize (CSize&&) = delete; ~CSize (void) = default;

				bool  Is_locked (void) const;
				bool  Is_locked (const bool); // returns 'true' in case of changing lock mode option;

				const
				t_size& Ref (void) const;
				t_size& Ref (void) ;

			private:
				CSize& operator = (const CSize&) = delete; CSize& operator = (CSize&&) = delete;
			private:
				t_size m_size; // stores the currently size of the window;
				bool   m_lock; // the flags for indicating the locking size change;
			};

		public:
			CLayout (void);  CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete; ~CLayout (void) = default;

			const
			CSize&  Size (void) const;
			CSize&  Size (void) ;

		private:
			CLayout& operator = (const CLayout&) = delete; CLayout& operator = (CLayout&&) = delete;

			CSize  m_size;
		};

		class CStyles {
		public:
			 CStyles (void) ; CStyles (const CStyles&) = delete; CStyles (CStyles&&) = delete;
			~CStyles (void) ;

			 bool Default_for_app (void); // sets default flags' set either to extended and standard flags' values; returns 'true' in case of change;
			 bool Default_for_kid (void); // sets default flags' set either to extended and standard flags' values; returns 'true' in case of change;

			 uint32_t Extended (void) const;     uint32_t Ext (void) const;      // gets extended style of the window;
			 bool     Extended (const uint32_t); bool     Ext (const uint32_t);  // sets extended style of the window; this works before creating the window;

			 uint32_t Standard (void) const;     uint32_t Std (void) const;      // gets standard style of the window;
			 bool     Standard (const uint32_t); bool     Std (const uint32_t);  // sets standard style of the window; this works before creating the window;

		private:
			 CStyles& operator = (const CStyles&) = delete; CStyles& operator = (CStyles&&) = delete;
		private:
			uint32_t m_ext;
			uint32_t m_std;
		};

	public:
		const
		CLayout&  Layout (void) const;
		CLayout&  Layout (void) ;
		const
		CStyles&  Styles (void) const;
		CStyles&  Styles (void) ;

		_pc_sz    Cls_name (void) const;

	protected:
		CLayout   m_layout;
		CStyles   m_styles;
		CString   m_cls_name;  // this is the name of this class, i.e. the name this class is declared; for debug purposes only;
	};
}}

#endif/*_SHARED_WND_BASE_H_INCLUDED*/