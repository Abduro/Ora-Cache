/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:48:34.237, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface implementation file;
*/
#include "gl_program.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;

CLinker:: CLinker (const uint32_t _u_prog_id) : m_prog_id(0) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (_u_prog_id) *this << _u_prog_id;
}
CLinker::~CLinker (void) {}

err_code  CLinker::Attach (const uint32_t _u_shader_id) {
	return CLinker::Attach(_u_shader_id, this->ProgId(), this->m_error);
}

err_code  CLinker::Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError& _err) {
	_u_shader_id; _u_prog_id; _err;
	procs::CProg& procs = CProgram::Cache();
	if (__failed( procs.Attach(_u_prog_id, _u_shader_id )))
		_err = procs.Error();

	return _err.Result();
}

TError&   CLinker::Error (void) const { return this->m_error; }

err_code  CLinker::Link (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err;

	procs::CProg& procs = CProgram::Cache();
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

	if (this->ProgId() == _u_prog_id) // the check of input '_u_prog_id' is already made by above statement, thus '0==0' is avoided;
		return this->m_error << __s_false = TString().Format(_T("The '_u_prog_id' (%u) is already assigned;"), _u_prog_id);

	this->m_prog_id = _u_prog_id;

	return this->Error();
}

CLinker&  CLinker::operator <<(const uint32_t _u_prog_id) { this->ProgId(_u_prog_id); return *this; }

CLinker&  CLinker::operator +=(const uint32_t _u_shader_id) {
	this->Attach(_u_shader_id);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

#define __gl_curr_prog 0x8B8D // GL_CURRENT_PROGRAM ;

CProgram:: CProgram (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProgram::~CProgram (void) { this->Delete(); }

procs::CProg& CProgram::Cache (void) {
	static procs::CProg m_fn_cache;
	return m_fn_cache;
}

CString   CProgram::Class (void) { return __CLASS__; }

TError&   CProgram::Error (void) const { return this->m_error; }

err_code  CProgram::Create (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (!!this->Id())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists = TString().Format(_T("Program object (id=%u) already exists"), this->Id().Get());

	procs::CProg& procs = CProgram::Cache();
	this->Id() << procs.Create();
	if (0 == this->Id()) {
		if (procs.Error().Is())
			return this->m_error = procs.Error();
		program::CLog log;
		if (__failed(log.Set(0))) {}
	}

	return this->Error();
 }

err_code  CProgram::Delete (void) {
	this->m_error<<__METHOD__<<__s_ok;

	if (false == !!this->Id())
		return this->Error();  // returns __s_ok; there is nothing to destroy;

	procs::CProg& procs = CProgram::Cache();

	if (__failed(procs.Delete(this->Id())))
		return this->m_error = procs.Error();

	this->Id().Reset();
	return this->Error();
}

const
program::CProgId& CProgram::Id (void) const { return this->m_prog_id; }
program::CProgId& CProgram::Id (void)       { return this->m_prog_id; }

bool CProgram::Is_valid (void) const {
	return CProgram::Is_valid(this->Id(), this->m_error<<__METHOD__<<__s_ok);
}

bool CProgram::Is_valid (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	static _pc_sz p_sz_pat_err = _T("'_u_prog_id' (%u) is invalid");

	if (0 == _u_prog_id) {
		return false == (_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id)).Is();
	}
	procs::CParam param;

	const uint32_t n_curr_prog = param.GetInt(__gl_curr_prog); // if a negative result is returned, the input '_u_prog_id' will still be different;

	if (0 == n_curr_prog) {
		if (param.Error())
			return false == (_err = param.Error()).Is(); // Error.Is() returns 'true' in such case, thus 'false == true' is valid return result;
	}
	else if (_u_prog_id != n_curr_prog) {
		_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id);
	}

	return false == _err.Is();
}

err_code CProgram::Validate (void) {
	this->m_error<<__METHOD__<<__s_ok;

	procs::CProg& procs = CProgram::Cache();

	if (__failed(procs.Validate(this->Id())))
		return this->m_error = procs.Error();

	return this->Error();
}