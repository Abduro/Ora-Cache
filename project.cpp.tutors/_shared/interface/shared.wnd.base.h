#ifndef _SHARED_WND_BASE_H_INCLUDED
#define _SHARED_WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:39:32.292, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface declaration file;
*/
#include "shared.defs.h"
#include "sys.err.trim.h"

namespace ex_ui { namespace popup {

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

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

		err_code Register (_pc_sz _cls_name, const WNDPROC = nullptr) ;
		err_code Unregister (void); // unregisters the class; it is not necessary due to operating system makes it on app process termination;

	public:
		CAtom& operator = (const CAtom&) = delete;
		CAtom& operator = (CAtom&&) = delete;
		const
		CAtom& operator >>(CString& _cls_name) const;

		operator ATOM (void) const;

	private:
		ATOM    m_atom;
		CError  m_error;
		CString m_cls_name;
	};
	// needs to be reviewed for how to apply other functionality to base window class by avoiding atlthunk intermediate component;
	// https://learn.microsoft.com/en-us/answers/questions/1330903/a-curiosity-question-on-atl-cwindowimpl-class ;
	// https://learn.microsoft.com/en-us/windows/win32/api/atlthunk/nf-atlthunk-atlthunk_initdata ;
	// https://learn.microsoft.com/en-us/windows/win32/api/atlthunk/nf-atlthunk-atlthunk_allocatedata ;
	// https://learn.microsoft.com/en-us/windows/win32/api/atlthunk/nf-atlthunk-atlthunk_datatocode ;
	// https://learn.microsoft.com/en-us/windows/win32/api/atlthunk/nf-atlthunk-atlthunk_freedata ;
}}

#endif/*_SHARED_WND_BASE_H_INCLUDED*/