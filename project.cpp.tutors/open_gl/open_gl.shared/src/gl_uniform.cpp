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

#pragma region cls::vars::CUniform{}

CUniform:: CUniform (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform::~CUniform (void) {}

TError&    CUniform::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::vars::CUniform_enum{}

CUniform_enum:: CUniform_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CUniform_enum::~CUniform_enum (void) {}

uint32_t   CUniform_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	uint32_t u_result = 0;

	using e_uni_params = procs::program::e_uniform_params;
	const CProgram& prog = ::Get_renderer().Scene().Progs().GetActive();

	if (false == prog.Is_valid()) {
		this->m_error = ::Get_renderer().Scene().Progs().Error(); // the error is traced;
		return u_result;
	}

	if (__failed(::__get_prog_procs().Params(prog.Id().Get(), (uint32_t)e_uni_params::e_active, &u_result))) {
		this->m_error = ::__get_prog_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return u_result;
	}

	return u_result;
}

TError&    CUniform_enum::Error (void) const { return this->m_error; }

#pragma endregion