#ifndef _SHARED_WND_BASE_H_INCLUDED
#define _SHARED_WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:39:32.292, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface declaration file;
*/
#include "shared.defs.h"
//#include "shared.wnd.layout.h"

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
	class CAtom {
	public:
		 CAtom (void); CAtom (const CAtom&) = delete; CAtom (CAtom&&) = delete;
		~CAtom (void);

	public:
		TError& Error (void) const;
		bool Is_valid (void) const;

		bool Is_exist (_pc_sz _p_cls_name) const; // checks the input class name for registration, the status of the error object is updated;

		err_code Register (_pc_sz _cls_name) ; // window procedure pointer is assigned automatically to the message router's procedure;
		err_code Unregister (void); // unregisters the class; it is not necessary due to operating system makes it on app process termination;

	public:
		CAtom& operator = (const CAtom&) = delete;
		CAtom& operator = (CAtom&&) = delete;
		const
		CAtom& operator >>(CString& _cls_name) const;

		operator ATOM (void) const;

	private:
		mutable
		CError  m_error;
		ATOM    m_atom;
		CString m_cls_name;
	};
	// ToDo: Window builder must be involeved into creating new window; the builder must have window style, layout, etc.;
	class CWnd : private IMsg_Handler {
	public:
		 CWnd (void); CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void);

	public:
		/* the input parameters are placed in such order specifically in accordance with default values they have;
		   also, taking into account that in the most tutorials the window being created has the desktop as its parent, so it is the last param;
		*/
		err_code Create (_pc_sz _p_cls_name, _pc_sz _p_title, const t_rect&, const bool _b_vidible = true, const HWND _h_parent = 0);
		err_code Destroy(void); // https://learn.microsoft.com/en-us/windows/win32/learnwin32/closing-the-window ;
		/*
			the excerpt from the article which is referred by the link given above:
			...
			The WM_CLOSE message gives you an opportunity to prompt the user before closing the window.
			If you really do want to close the window, call the DestroyWindow function.
			...
			in this case, no prompt to the user, but just the destroying the window;
		*/

		TError&  Error (void) const;
		HWND     Handle (void) const;
		bool  Is_valid (void) const;

	public:
		bool operator == (const CWnd&) const;
		bool operator == (const HWND) const;
		operator const HWND (void) const;

		CWnd& operator = (const CWnd&) = delete;
		CWnd& operator = (CWnd&&) = delete;

	protected:
		mutable
		CError m_error;
		HWND   m_h_wnd;
	};
}}

typedef ex_ui::popup::CMsgRouter TRouter;

TRouter& Get_router (void);

#endif/*_SHARED_WND_BASE_H_INCLUDED*/