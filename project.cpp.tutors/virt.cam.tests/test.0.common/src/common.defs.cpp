/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 09:06:47.362, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' common definition file;
*/
#include "common.defs.h"

using namespace ::test::draw::defs;

namespace test { namespace draw { namespace defs { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

static TViewEvtHandler* p_handler = nullptr;

TViewEvtHandler* const ::Get_view_evt_handler (void) {
	TSafe_Lock();
	return p_handler;
}

void  ::Set_view_evt_handler (TViewEvtHandler* const _p_handler) {
	TSafe_Lock();
	p_handler = _p_handler;
}