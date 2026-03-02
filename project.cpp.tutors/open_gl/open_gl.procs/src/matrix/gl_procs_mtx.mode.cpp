/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 12:28:44.767, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface implementation file;
*/
#include "gl_procs_mtx.mode.h"
#include "gl_procs.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::matrix;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace matrix {

	_pc_sz _mat_mode_2_str(const e_mat_mode _e_mode) {
		_e_mode;
		static CString cs_out;
		switch (_e_mode) {
		case e_mat_mode::e_color    : cs_out = _T("e_color"); break;
		case e_mat_mode::e_modelview: cs_out = _T("e_modelview"); break;
		case e_mat_mode::e_project  : cs_out = _T("e_projection"); break;
		case e_mat_mode::e_texture  : cs_out = _T("e_texture"); break;
		default: cs_out = _T("#e_undef");
		}
		return (_pc_sz) cs_out;
	}

}}}}}

#pragma region cls::CMode

static _pc_sz mode_fun_names[] = {
	_T("glMatrixMode")
};

enum class e_mode_fun_ndx : uint32_t {
	e_set = 0x0
};

CMode:: CMode (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

e_mat_mode CMode::Get (void) const {

	e_mat_mode e_mode = (e_mat_mode)__get_param_procs().GetInt(GL_MATRIX_MODE);
	if (__get_param_procs().Error()) {
		CBase::m_error = __get_param_procs().Error(); e_mode = e_mat_mode::e_undef;
	}
	return e_mode;
}

err_code CMode::Set (const e_mat_mode _e_mode) {
	_e_mode;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_e_mode' is not an accepted value;
	GL_INVALID_OPERATION : glMatrixMode() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (false == CMode::Is_code(_e_mode))
		return (CBase::m_error = (dword)GL_INVALID_VALUE) = TString().Format(_T("'_e_mode' {'%s'(0x%04x)} is invalid"), CMode::To_str(_e_mode), _e_mode);

	pfn_Set p_fun = reinterpret_cast<pfn_Set>(CBase::Get(mode_fun_names[(uint32_t)e_mode_fun_ndx::e_set]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun((uint32_t)_e_mode);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_VALUE : (CBase::m_error = (dword)u_err_code) = TString().Format(_T("'_e_mode' 0x%04x (%u) is invalid"), _e_mode, _e_mode); break;
	case GL_INVALID_OPERATION : (CBase::m_error = (dword)u_err_code) = _T("#__e_state: Invalid state for setting matrix mode"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}
	return CBase::Error();
}

err_code CMode::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(mode_fun_names); i_++) {
		if (nullptr == CBase::Get(mode_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

bool     CMode::Is_code (const e_mat_mode _e_type) {
	_e_type;
	switch (_e_type) {
	case e_mat_mode::e_color    :
	case e_mat_mode::e_modelview:
	case e_mat_mode::e_project  :
	case e_mat_mode::e_texture  : return true;
	default: return false;
	}
}
_pc_sz   CMode::To_str (const e_mat_mode _e_mode) { return _mat_mode_2_str(_e_mode); }

#pragma endregion

TMatModeProcs& ::__get_mat_mode_procs (void) {
	static TMatModeProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}