/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 11:58:23.255, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader compiler wrapper interface implementation file;
*/
#include "gl_compiler.h"
#include "gl_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CCompiler:: CCompiler (const uint32_t _u_shader_id) : m_shader_id(_u_shader_id) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CCompiler::~CCompiler (void) {}

procs::CCompiler& CCompiler::Procs (void) {
	static procs::CCompiler procs;
	return procs;
}

err_code CCompiler::Compile (void) {

	this->m_error <<__METHOD__<<__s_ok;

	const uint32_t $_id = this->ShaderId();

	if (0 == $_id)
		return this->m_error <<__e_not_inited = TString().Format(_T("Shader id (%d) is not valid"), $_id);

	procs::CCompiler& procs = CCompiler::Procs();

	if (__failed(procs.Compile($_id))) {
		return this->m_error = procs.Error();
	}

	if (__failed(this->Log().Set($_id))) // gets log info for this complilation in any case; the log error code can be retrieved by direct call to log error; 
		this->m_error = this->Log().Error();

	return this->Error();
}

TError& CCompiler::Error (void) const { return this->m_error; }
#if (0)
#define __gl_cmpl_status  0x8B81 // GL_COMPILE_STATUS;

bool  CCompiler::Is_compiled (void) const {
	this->m_error() <<__METHOD__<<__s_ok;

	if (false == this->ShaderId())
		return this->m_error()<<__e_not_inited = _T("Shader id is not valid");

	procs::CShader& procs = CShader::Cache();
	
	int32_t n_result = 0;
	if (__failed(procs.Params(this->ShaderId(), __gl_cmpl_status, &n_result))) {
		this->m_error() = procs.Error();
		return !!n_result;
	}

	return !!n_result;
}
#endif
bool  CCompiler::Is_supported (void) const {

	this->m_error <<__METHOD__<<__s_ok;

	procs::CCompiler cmpl;
	const bool b_support = cmpl.Is_supported();

	if (cmpl.Error().Is())
		this->m_error = cmpl.Error();
	else
		this->m_error <<__e_not_inited = _T("Shader compiler is not supported");
	return b_support;
}

const
CLog&    CCompiler::Log (void) const { return this->m_log; }
CLog&    CCompiler::Log (void)       { return this->m_log; }

err_code CCompiler::Release (void) {
	this->m_error <<__METHOD__<<__s_ok;

	procs::CCompiler& procs = CCompiler::Procs();

	if (__failed(procs.Release())) {
		this->m_error = procs.Error();
	}
	return this->Error();
}

uint32_t CCompiler::ShaderId  (void) const { return this->m_shader_id; }
err_code CCompiler::ShaderId  (const uint32_t _u_shader_id) {
	_u_shader_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == CShader::Is_valid(_u_shader_id, this->m_error))
		return this->Error();

	this->m_shader_id = _u_shader_id;

	return this->Error();
}

CCompiler& CCompiler::operator <<(const uint32_t _u_shader_id) { this->ShaderId(_u_shader_id); return *this; }