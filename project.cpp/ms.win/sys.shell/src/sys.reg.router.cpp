/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 11:20:21.223, UTC+4, Batumi, Thursday;
	This Ebo Pack commom registry paths' router class interface implementation file;
*/
#include "sys.reg.router.h"

using namespace shared::sys_core::storage;

#define RootKey HKEY_CURRENT_USER

#pragma region cls::CRoot{}

CRoot::CRoot (void) {}
const
HKEY    CRoot::Key  (void) const { static HKEY h_key = RootKey; return h_key; }
_pc_sz  CRoot::Path (void) const { static _pc_sz p_path = _T("Software\\ebo::pack"); return p_path; }

#pragma endregion