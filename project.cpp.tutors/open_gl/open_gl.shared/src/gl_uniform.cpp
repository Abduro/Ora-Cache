/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:29:19.429, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface implementation file;
*/
#include "gl_uniform.h"
#include "gl_renderer.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "gl_procs_prog.h"
#include "gl_procs_uniform.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::vars;

using CValue = CUniform::CValue;

#pragma region cls::CUniform::CValue{}

CValue::CValue (CUniform* _p_form) : m_p_form(_p_form) {}

TError& CValue::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::vars::CUniform{}

CUniform:: CUniform (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform::~CUniform (void) {}

TError&    CUniform::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::vars::CUniform_enum{}

CUniform_enum:: CUniform_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform_enum::~CUniform_enum (void) {}

uint32_t CUniform_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	const CProgram& prog = ::Get_renderer().Scene().Progs().GetActive();
#if (0)
	if (false == prog.Is_valid()) {
		this->m_error = ::Get_renderer().Scene().Progs().Error(); // the error is traced;
		return 0;
	}
#endif
	return CUniform_enum::Count(prog.Id().Get(), this->m_error);
}

uint32_t CUniform_enum::Count (const uint32_t prog_id,  CError& _err) {
	prog_id; _err;
	uint32_t u_result = 0;

	if (false == program::CProgId::Is_valid(prog_id, _err))
		return u_result;

#define __use_prior_ver 0
	// this is the approach of getting program uniform variables' count in:
	// OpenGL 3.0+ version;
#if (__use_prior_ver != 0)
	using e_uni_params = procs::program::e_uniform_params;

	if (__failed(::__get_prog_procs().Params(prog_id, (uint32_t)e_uni_params::e_active, &u_result))) {
		_err = ::__get_prog_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
#else
	// OpenGL 4.3+ or ARB_program_interface_query extension;
	using e_interface = procs::program::e_interface;
	using e_property  = procs::program::e_property;

	if (__failed(::__get_iface_procs().Get(prog_id, e_interface::e_uniform, e_property::e_active_res, u_result))) {
		_err = __get_iface_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
#endif
	return u_result;
}

TError&  CUniform_enum::Error (void) const { return this->m_error; }

err_code CUniform_enum::Get (const uint32_t prog_id, TUniVars& _vars, CError& _err) {
	prog_id; _vars; _err;

	if (_vars.empty() == false)
		_vars.clear();

	// (1) gets uniform variables number through the program interface object;
	uint32_t u_vars_count = CUniform_enum::Count(prog_id, _err);
	if (0 == u_vars_count)
		return _err; // no errors and no variables;

	return _err;
}

#pragma endregion