#ifndef _SHARED_WND_ATOM_H_INCLUDED
#define _SHARED_WND_ATOM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Sep-2025 at 21:48:22.580, UTC+4, Batumi, Tuesday;
	This is Ebo Pack system window atom wrapper interface declaration file;
*/
#include "shared.defs.h"
#include "shared.dbg.h"

namespace ex_ui { namespace popup {

	using namespace shared::defs;

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
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t"), _pc_sz _p_sfx = _T("\n")) const; // looks like useless;
#endif
		const
		WNDCLASSEX&  Ref (void) const;
		WNDCLASSEX&  Ref (void) ;        // there is the possible problem: direct assigning class name may be not sync with cached one;

		uint32_t Style (void) const;     // gets window class style flags;
		bool     Style (const uint32_t); // sets window class style flags; returns 'true' in case of flags' set value change;

	public:
		CWndCls& operator = (const CWndCls&) = delete;
		CWndCls& operator = (CWndCls&&) = delete;
		const
		CWndCls& operator >>(CString& _cls_name) const;

		operator ATOM (void) const;
		const
		WNDCLASSEX&  operator ()(void) const;
		WNDCLASSEX&  operator ()(void) ;

	protected:
		mutable
		CError  m_error;    // the error state of the last operation;
		ATOM    m_atom ;    // this is the result of the window class registration; in other words this is this class identifier;
		WNDCLASSEX m_wnd_cls;
		CString m_name ;    // this is cached class name; it is required due to the registration of the class may be deferred;
	};

	// https://learn.microsoft.com/en-us/previous-versions/windows/it-pro/windows-2000-server/cc978570(v=technet.10) ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalfindatoma ;

	class CCon_cls : public CWndCls { typedef CWndCls TBase;
	public:
		CCon_cls (void); ~CCon_cls (void);

		err_code Get (void);   // tries to get properties of the system class 'ConsoleWindowClass';
	};

}}

#endif/*_SHARED_WND_ATOM_H_INCLUDED*/