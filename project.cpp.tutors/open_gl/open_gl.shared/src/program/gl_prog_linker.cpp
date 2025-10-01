/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 09:12:35.620, UTC+4, Batumi, Wednesday;
	This Ebo Pack OpenGL program linker wrapper interface implementation file;
*/
#include "gl_prog_linker.h"
#include "shared.preproc.h"
#include "gl_program.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;


CLinker:: CLinker (const uint32_t _u_prog_id) : m_prog_id(0) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (_u_prog_id) *this << _u_prog_id;
}
CLinker::~CLinker (void) {
	this->Detach_all();
}

procs::CLinker& CLinker::Cache (void) {
	static procs::CLinker m_fn_cache;
	return m_fn_cache;
}

CString   CLinker::Class (void) { return __CLASS__; }

err_code  CLinker::Attach (const uint32_t _u_shader_id) {
	return CLinker::Attach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code  CLinker::Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed( procs.Attach(_u_prog_id, _u_shader_id )))
		_err = procs.Error();

	return _err.Result();
}

err_code CLinker::Detach (const uint32_t _u_shader_id) {
	return CLinker::Detach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code CLinker::Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed( procs.Detach(_u_prog_id, _u_shader_id )))
		_err = procs.Error();

	return _err;
}

err_code  CLinker::Detach_all (void) {
	return  CLinker::Detach_all(this->ProgId(), this->m_error);
}

err_code  CLinker::Detach_all (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	static const uint32_t u_max_count = 32;

	uint32_t shader_ids[u_max_count] = {0};
	uint32_t u_count = 0;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed(procs.Attached(_u_prog_id, u_max_count, &u_count, shader_ids)))
		return _err = procs.Error();

	for (uint32_t i_ = 0; i_ < u_count && i_ < u_max_count; i_++) {
		if (__failed(procs.Detach(_u_prog_id, shader_ids[i_]))) {
			_err = procs.Error(); break;
		}
	}

	return _err;
}

TError&   CLinker::Error (void) const { return this->m_error; }

err_code  CLinker::Link (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	procs::CLinker& procs = CLinker::Cache();
	if (__failed( procs.Link(_u_prog_id)))   // makes all required checks and sets the error if necessary;
		_err = procs.Error();

	return _err;
}

err_code  CLinker::Link (void) {
	return CLinker::Link(this->ProgId(), this->m_error);
}

uint32_t  CLinker::ProgId (void) const { return this->m_prog_id; }
err_code  CLinker::ProgId (const uint32_t _u_prog_id) {
	_u_prog_id;
	this->m_error<<__METHOD__<<__s_ok;

	if (false == CProgram::Is_valid(_u_prog_id, this->m_error))
		return this->Error();
#if (0)
	if (this->ProgId() == _u_prog_id) // the check of input '_u_prog_id' is already made by above statement, thus '0==0' is avoided;
		return this->m_error << __s_false = TString().Format(_T("The '_u_prog_id' (%u) is already assigned;"), _u_prog_id);
#endif
	this->m_prog_id = _u_prog_id;

	return this->Error();
}

CLinker&  CLinker::operator <<(const uint32_t _u_prog_id) { this->ProgId(_u_prog_id); return *this; }

CLinker&  CLinker::operator +=(const uint32_t _u_shader_id) {
	this->Attach(_u_shader_id);
	return *this;
}

CLinker&  CLinker::operator -=(const uint32_t _u_shader_id) {
	this->Detach(_u_shader_id);
	return *this;
}