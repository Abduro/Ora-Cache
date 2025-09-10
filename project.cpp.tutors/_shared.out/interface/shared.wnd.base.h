#ifndef _SHARED_WND_BASE_H_INCLUDED
#define _SHARED_WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:39:32.292, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface declaration file;
*/
#include "shared.defs.h"

namespace ex_ui { namespace popup {

	using namespace shared::defs;
	
	interface IMsg_Handler {
		static const int32_t _n_not_handled = -1;
		virtual err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) { // possibly, 'const' to w_param/l_param must be removed;
			_u_code;                // message code, e.g. WM_CREATE;
			return _n_not_handled;  // __s_ok|__s_false - depending on the message code, otherwise the error code; 
		}
	};
	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure#avoiding-bottlenecks-in-your-window-procedure ;
	class CMsgRouter {
	public:
		CMsgRouter (void); ~CMsgRouter (void) = default;

	public:
		bool ApplyTo (WNDCLASSEX&); // sets the pointer to address of the internal message handler/window procedure; returns 'true' in case of data changed;
		TError& Error (void) const;

		err_code Subscribe (const HWND, IMsg_Handler&);
		err_code Unsubscribe (const HWND);

	private:
		CError m_error;

		CMsgRouter (const CMsgRouter&) = delete; CMsgRouter (CMsgRouter&&) = delete;
		CMsgRouter& operator = (const CMsgRouter&) = delete; CMsgRouter& operator = (CMsgRouter&&) = delete;

		friend CMsgRouter& Get_router(void); // it is not necessary for the current implementation of this class;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-unregisterclassa ;
	/*
		*important*: the window class style must have CS_OWNDC flag, otherwise there is not way to create OpenGL renderer context;
	*/
	class CWndCls {
	public:
		enum e_type : uint32_t {
		e_cfg_ctrl = 0x1, // user control window class cfg type;
		e_cfg_over = 0x0, // overlapped window class cfg type; it's default;
		};

		static const int32_t n_cls_name_max = 256; // the maximum length of the class name as it's defined in one of the above URLs;
	public:
		 CWndCls (void); CWndCls (const CWndCls&) = delete; CWndCls (CWndCls&&) = delete;
		~CWndCls (void);

	public:
		err_code Cfg  (const e_type); // sets the default settings for specified input type of the configuration;

		TError& Error (void) const;
		bool Is_valid (void) const;
		// checks the input class name for registration, the status of the error object is updated;
		bool Is_exist (_pc_sz _p_cls_name) const;
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/about-window-classes#class-name ;
		// excerpt from above article: ... should keep class name strings as short as possible ...;
		_pc_sz   Name (void) const;      // returns  window class name; *max* length is 256 chars, otherwise the registration will fail;
		bool     Name (_pc_sz) ;         // sets the window class name, returns true in case of name change; assigns the input to the cached name first;

		err_code Register (_pc_sz _cls_name) ; // window procedure pointer is assigned automatically to the message router's procedure;
		err_code Unregister (void);      // unregisters the class; it is not necessary due to operating system makes it on app process termination;

		const
		WNDCLASSEXW&  Ref (void) const;
		WNDCLASSEXW&  Ref (void) ;       // there is the possible problem: direct assigning class name may be not sync with cached one;

		uint32_t Style (void) const;     // gets window class style flags;
		bool     Style (const uint32_t); // sets window class style flags; returns 'true' in case of flags' set value change;

	public:
		CWndCls& operator = (const CWndCls&) = delete;
		CWndCls& operator = (CWndCls&&) = delete;
		const
		CWndCls& operator >>(CString& _cls_name) const;

		operator ATOM (void) const;
		const
		WNDCLASSEXW&  operator ()(void) const;
		WNDCLASSEXW&  operator ()(void) ;

	private:
		mutable
		CError  m_error;    // the error state of the last operation;
		ATOM    m_atom ;    // this is the result of the window class registration; in other words this is this class identifier;
		WNDCLASSEXW m_wnd_cls;
		CString m_name ;    // this is cached class name; it is required due to the registration of the class may be deferred;
	};

	// ToDo: Window builder must be involeved into creating new window; the builder must have window style, layout, etc.;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassname ; getting class name from the window;

	class CWndBase : private IMsg_Handler {
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

typedef ex_ui::popup::CMsgRouter TRouter;

TRouter& Get_router (void);

#endif/*_SHARED_WND_BASE_H_INCLUDED*/