#ifndef _WND_BASE_H_INCLUDED
#define _WND_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Oct-2021 at 10:11:04.4118880 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window adapter base interface declaration file.
*/
#include <atlbase.h>
#include <atlwin.h>
#include <set>

#include "sys.error.h"
#include "handlers.h"

#include "shared.types.h"

namespace ex_ui { namespace popup {

	using namespace shared::types;

	// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features ;
	// https://www.equestionanswers.com/vcpp/client-non-client-area.php ;

	using namespace ex_ui::message::handlers;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassexa ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-unregisterclassa ;
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

	class CWndBase : public ::ATL::CWindowImpl<CWndBase> {
	public:         typedef ::ATL::CWindowImpl<CWndBase> TWindow;
	public:
		 CWndBase (_pc_sz _p_cls_name = nullptr);
		 CWndBase (const CWndBase&) = delete; CWndBase (CWndBase&&) = delete;
		~CWndBase (void);

	public:
		DECLARE_WND_CLASS(__CLASS__);

		BEGIN_MSG_MAP(CWndBase)
			CHAIN_MSG_MAP_MEMBER(m_handlers);
		END_MSG_MAP()

	public:
		const
		CAtom&   Atom  (void) const;
		CAtom&   Atom  (void) ;
		TError&  Error (void) const;
		const
		TMsgHandlers& Handlers(void) const;
		TMsgHandlers& Handlers(void) ;

	protected:
		TMsgHandlers  m_handlers; // message handler set is eccential for an operating window properly; thus handlers must exist always;
		CError  m_error;
		CAtom   m_atom ;
	};
}}

typedef ex_ui::popup::CWndBase TWndBase;

#endif/*_WND_BASE_H_INCLUDED*/