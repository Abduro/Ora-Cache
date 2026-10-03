/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Oct-2026 at 22:55:13.178, (GMT+4), Batumi;
	This is MS Internet Explorer registry entries' wrapper interfsace implementation file;
*/
#include "web.ie.reg.h"

using namespace ::ex_ui::web::IE::storage;
using namespace ::ex_ui::web::IE::storage::route;

#pragma region cls::CEmulation{}

_pc_sz CEmulation::Path (void) const {

	return nullptr;
}

#pragma endregion
#pragma region cls::CRoot{}

_pc_sz  CRoot::Path (void) const {
	
	static _pc_sz p_root = _T("SOFTWARE\\Microsoft\\Internet Explorer");
	return p_root;
}

const
CRoot_base& CRoot::operator ()(void) const { return (TBase&)*this; }
CRoot_base& CRoot::operator ()(void)       { return (TBase&)*this; }

#pragma endregion