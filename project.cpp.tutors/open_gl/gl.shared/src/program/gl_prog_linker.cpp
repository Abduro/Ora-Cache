/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 09:12:35.620, UTC+4, Batumi, Wednesday;
	This Ebo Pack OpenGL program linker wrapper interface implementation file;
*/
#include "gl_prog_linker.h"
#include "shared.preproc.h"
#include "gl_program.h"
#include "gl_procs.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;


CLinker:: CLinker (const uint32_t _u_prog_id) : m_prog_id(0) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (_u_prog_id) *this << _u_prog_id;
}
CLinker::~CLinker (void) {}

CString   CLinker::Class (void) { return __CLASS__; }

TError&   CLinker::Error (void) const { return this->m_error; }

err_code  CLinker::Link (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err; // the error contains info of error details related to program identifier validity;

	if (__failed(__get_lnk_procs().Link(_u_prog_id)))   // makes all required checks and sets the error if necessary;
		_err = __get_lnk_procs().Error();

	return _err;
}

err_code CLinker::Link (const uint32_t _u_prog_id, CLog& _log, CError& _err) {
	_u_prog_id; _log; _err;
	if (false == CProgram::Is_valid(_u_prog_id, _err))
		return _err; // the error contains info of error details related to program identifier validity;

	if (__failed(__get_lnk_procs().Link(_u_prog_id)))   // makes all required checks and sets the error if necessary;
		_err = __get_lnk_procs().Error();

	if (__failed(_log.Set(_u_prog_id))) // to-do: this error shouldn't be taken into account because it is not linker error, but program log one;
		_err = _log.Error();

	return _err;
}

err_code  CLinker::Link (void) {
	return CLinker::Link(this->ProgId(), this->Log(), this->m_error);
}

const
CLog& CLinker::Log (void) const { return this->m_log; }
CLog& CLinker::Log (void)       { return this->m_log; }

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