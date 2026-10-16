#ifndef _COMMON_DEFS_H_INCLUDED
#define _COMMON_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 09:03:48.398, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' common declaration file;
*/
#include <atlbase.h>      // https://learn.microsoft.com/en-us/cpp/atl/reference/atl-classes ;
#include <atlwin.h>       // https://learn.microsoft.com/en-us/cpp/atl/reference/cwindow-class ;
#include <atlstr.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class ;
#include <cstdint>
#include <tchar.h>

#include "shared.dbg.h"
#include "shared.types.h"
#include "sys.error.h"

#include "web.ie.browser.h"
#include "web.ie.locator.h"

namespace test { namespace draw { namespace defs {

	using namespace ::shared::types;
	using namespace ::shared::sys_core;
	using CError  = ::shared::sys_core::CError;
	using TError  = const CError;

	interface IViewEvtHandler {
		virtual err_code IViewEvt_OnMessage (const MSG&) { return __e_not_impl; }
	};

}}}

typedef ::test::draw::defs::IViewEvtHandler TViewEvtHandler; typedef ::std::shared_ptr<TViewEvtHandler> TViewEvtHandlerPtr;

TViewEvtHandler* const Get_view_evt_handler (void); // uses raw pointer, because it is dependable on app main view object; so there is no need to use smart pointers;
void  Set_view_evt_handler (TViewEvtHandler* const);

#include <mutex>

namespace shared { namespace sys_core {
	// https://en.cppreference.com/cpp/thread/recursive_mutex/lock;
	// https://en.cppreference.com/cpp/thread/recursive_mutex/try_lock ;
	// https://en.cppreference.com/cpp/thread/recursive_mutex/unlock ;
	typedef ::std::lock_guard<std::recursive_mutex> TGuard;
	static  ::std::recursive_mutex the_lock;
}}
#define TSafe_Lock() shared::sys_core::TGuard locker(shared::sys_core::the_lock);

#endif/*_COMMON_DEFS_H_INCLUDED*/