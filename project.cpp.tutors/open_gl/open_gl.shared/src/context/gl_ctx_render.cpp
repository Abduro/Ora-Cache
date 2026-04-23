/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 23:41:07.887, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL draw renderer context interface implementation file;
*/
#include "gl_ctx_render.h"
#include "sys.registry.h"

using namespace ex_ui::draw::open_gl::context;

#pragma region cls::CPersistent

static CString cs_ctx_root = TString().Format(_T("%s\\Context"), (_pc_sz) ::Get_reg_router().Root().Path());
static CString cs_ctx_vers = TString().Format(_T("%s\\Version"), (_pc_sz) cs_ctx_root);

CPersistent::CPersistent (void) : m_use_core(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; this->Load(); }

TError&  CPersistent::Error (void) const { return this->m_error; }

err_code CPersistent::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// (1) loads the preferable version of OpenGL;
	TRegKeyEx reg_key;
	this->m_pref_ver.m_major = reg_key.Value().GetDword((_pc_sz) cs_ctx_vers, _T("major")); if (reg_key.Error()) { __trace_err_ex_2(this->m_error = reg_key.Error()); }
	this->m_pref_ver.m_minor = reg_key.Value().GetDword((_pc_sz) cs_ctx_vers, _T("minor")); if (reg_key.Error()) { __trace_err_ex_2(this->m_error = reg_key.Error()); }

	this->m_use_core = !!reg_key.Value().GetDword((_pc_sz) cs_ctx_vers, _T("core")); if (reg_key.Error()) { __trace_err_ex_2(this->m_error = reg_key.Error()); }

	return this->Error();
}
const
s_version& CPersistent::Prefer (void) const { return this->m_pref_ver; }

err_code CPersistent::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	return this->Error();
}

bool CPersistent::Use_core (void) const { return this->m_use_core; }

#pragma endregion

TCtxPers& ::Get_CtxPers (void) {
	static TCtxPers ctx_pers;
	return ctx_pers;
}