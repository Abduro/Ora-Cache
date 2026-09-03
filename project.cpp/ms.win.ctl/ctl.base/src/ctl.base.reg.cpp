/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 12:01:58.524, UTC+4, Batumi, Thursday;
	The is base control registry storage wrapper interface interface implementation file;
*/
#include "ctl.base.reg.h"

using namespace ::ex_ui::controls::storage;

#pragma region cls::CRoot{}

_pc_sz  CRoot::Path (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Controls"), TBase::Path());
	}
	return (_pc_sz) cs_root;
}

#pragma endregion