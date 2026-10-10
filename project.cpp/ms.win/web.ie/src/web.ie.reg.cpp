/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Oct-2026 at 22:55:13.178, (GMT+4), Batumi;
	This is MS Internet Explorer registry entries' wrapper interfsace implementation file;
*/
#include "web.ie.reg.h"

using namespace ::ex_ui::web::IE::storage;
using namespace ::ex_ui::web::IE::storage::route;
using CVersion = CRoot::CVersion;

#pragma region cls::CEmulation{}

_pc_sz CEmulation::Path (void) const {

	static _pc_sz p_pattern = _T("%s\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION");
	static CString cs_path;
	if (cs_path.IsEmpty())
		cs_path = TString().Format(p_pattern, ::Get_web_router().Root().Path());
	return nullptr;
}

#pragma endregion
#pragma region cls::CRoot{}

_pc_sz  CRoot::Path (void) const {
	
	static _pc_sz p_root = _T("SOFTWARE\\Microsoft\\Internet Explorer");
	return p_root;
}
const
CVersion& CRoot::Version (void) const { return this->m_version; }

const
CRoot_base& CRoot::operator ()(void) const { return (TBase&)*this; }
CRoot_base& CRoot::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CVersion{}

_pc_sz CVersion::Value (void) const { static _pc_sz p_value_name = _T("svcVersion"); return p_value_name; }

#pragma endregion
#pragma region cls::CWeb_router{}
const
CRoot& CWeb_router::Root (void) const { return this->m_root; }
CRoot& CWeb_router::Root (void)       { return this->m_root; }

#pragma endregion

TWebRouter& ::Get_web_router (void) {
	static TWebRouter router;
	return router;
}