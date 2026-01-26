/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jan-2026 at 09:40:22.178, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex buffer property getter interface implementation file;
*/
#include "gl_procs_buf.prop.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::buffer;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace buffer {

bool is_buf_param (const uint32_t _u_param) {
	return (uint32_t) e_buf_params::e_access     == _u_param
		|| (uint32_t) e_buf_params::e_acc_flags  == _u_param
		|| (uint32_t) e_buf_params::e_immutable  == _u_param
		|| (uint32_t) e_buf_params::e_mapped     == _u_param
		|| (uint32_t) e_buf_params::e_map_len    == _u_param
		|| (uint32_t) e_buf_params::e_map_offset == _u_param
		|| (uint32_t) e_buf_params::e_size       == _u_param
		|| (uint32_t) e_buf_params::e_stg_flags  == _u_param;
}
}}}}}

#pragma region cls::CProperty{}

static _pc_sz prop_fun_names[] = { _T("glGetBufferParameteriv"), _T("glGetNamedBufferParameteriv") };

enum class e_prop_fun_ndx : uint32_t { e_get = 0x0, e_get_named };

CProperty::CProperty (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetBufferParameter.xhtml ;
err_code CProperty::Get (const e_bind_targets _e_target, const e_buf_params _e_param, uint32_t& _u_value) {
	_e_target; _e_param; _u_value;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_e_target' is not one of the accepted buffer targets;
	GL_INVALID_ENUM      : '_e_param' is not one of the buffer object parameter names; 
	GL_INVALID_OPERATION : default buffer is bound to target;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	uint32_t u_result = 0;

	pfn_Get p_fun = reinterpret_cast<pfn_Get>(CBase::Get(prop_fun_names[(uint32_t)e_prop_fun_ndx::e_get]));
	if (nullptr == p_fun)
		return u_result;

	int32_t n_result = 0; // actually uint32_t is also okay, because it has the same size in memory;

	p_fun(static_cast<uint32_t>(_e_target), static_cast<uint32_t>(_e_param), &n_result);
	const
	uint32_t u_err_code = CErr_ex().Get_code(); 
	switch ( u_err_code ) {
	case GL_INVALID_ENUM :{
		if (false) {}
		else if (false == ::is_bind_target((uint32_t)_e_target)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: '_e_target' (0x%04x) is not accepted"), _e_target);
		else if (false == ::is_buf_param((uint32_t)_e_param)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: '_e_param' (0x%04x) is not accepted"), _e_param);
		else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__inv_unk: '_e_param' (0x%04x) is unknown"), _e_param);
	} break;
	case GL_INVALID_OPERATION : CBase::m_error <<__e_inv_arg = _T("#__e_oper: the default buffer (id = 0) is bound;"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}

	if (false == CBase::Error())
		_u_value = abs(n_result);

	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetBufferParameter.xhtml ;
err_code CProperty::Get (const uint32_t _u_buf_id, const e_buf_params _e_param, uint32_t& _u_value) {
	_u_buf_id; _e_param; _u_value;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_e_param' is not one of the buffer object parameter names; 
	GL_INVALID_OPERATION : '_u_buf_id' does not refer to buffer object;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	uint32_t u_result = 0;

	pfn_Get_nm p_fun = reinterpret_cast<pfn_Get_nm>(CBase::Get(prop_fun_names[(uint32_t)e_prop_fun_ndx::e_get_named]));
	if (nullptr == p_fun)
		return u_result;

	int32_t n_result = 0;

	p_fun(_u_buf_id, static_cast<uint32_t>(_e_param), &n_result);
	const
	uint32_t u_err_code = CErr_ex().Get_code(); 
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: '_e_param' (0x%04x) is not accepted"), _e_param); break;
	case GL_INVALID_OPERATION : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: '_u_buf_id' (0x%04x) does not refer to buffer"), _u_buf_id); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}

	if (false == CBase::Error())
		_u_value = abs(n_result);

	return CBase::Error();
}

err_code CProperty::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(prop_fun_names); i_++) {
		if (nullptr == CBase::Get(prop_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TBufPropProcs&  __get_buf_prop_procs (void) {
	static TBufPropProcs procs;
	static bool b_loaded = false;

	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
			b_loaded = true;
	}
	return procs;
}
#pragma endregion