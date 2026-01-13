/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Sep-2025 at 20:05:37.059, UTC+4, Batumi, Monday;
	This Ebo Pack OpenGL program identifier (aka symbolic name) interface implementation file;
*/
#include "gl_prog_id.h"
#include "gl_procs.h"
#include "shared.preproc.h"
#include "gl_procs_prog.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::program;
using namespace ex_ui::draw::open_gl::procs;

/////////////////////////////////////////////////////////////////////////////

CProgId:: CProgId (const uint32_t _prog_id) : m_value(0) { this->m_error>>__CLASS__<<__METHOD__<<__e_not_inited; if (_prog_id) *this << _prog_id; }
CProgId::~CProgId (void) {}

TError&   CProgId::Error (void) const { return this->m_error; }

uint32_t  CProgId::Get (void) const { return this->m_value; }
err_code  CProgId::Set (const uint32_t _u_value) {
	_u_value;
	this->m_error<<__METHOD__<<__s_ok;

	if (0 == _u_value) {
		this->Reset(); // the error object state is set to __e_not_inited and it shouldn't be returned, because it is intended state of identifier;
		return __s_ok; // possibly __s_false may be returned, but it looks like unnecessary;
	}
	if (false == CProgId::Is_valid(_u_value, this->m_error))
		return this->Error();

	if (this->Get() == _u_value) // the check of input '_u_prog_id' is already made by above statement, thus '0==0' is avoided;
		return this->m_error << __s_false = TString().Format(_T("The '_u_prog_id' 0x%04x (%u) is already assigned;"), _u_value, _u_value);

	this->m_value = _u_value;

	return this->Error();
}

#define __gl_curr_prog 0x8B8D // GL_CURRENT_PROGRAM ;

bool CProgId::Is_valid (void) const {
	return CProgId::Is_valid( this->m_value, this->m_error);
}

bool CProgId::Is_valid (const uint32_t _u_prog_id, CError& _err) {
	_u_prog_id; _err;
	static _pc_sz p_sz_pat_err = _T("'_u_prog_id' 0x%04x (%u) is invalid");

	if (0 == _u_prog_id) {
		return false == (_err << __e_inv_arg = TString().Format(p_sz_pat_err, _u_prog_id, _u_prog_id)).Is();
	}
#if (0) // this for getting active (i.e. set by glUseProgram()), it can be applied for check active program identifier ;
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
#else // it is intended for check of program identifier regardless the program of such identifier is active or not;
	const bool b_valid = __get_prog_procs().IsProg(_u_prog_id);
	if (false == b_valid)
		if (__get_prog_procs().Error())
			_err = __get_prog_procs().Error();
		else
			_err << __e_inv_arg = TString().Format(_T("'_u_prog_id' 0x%04x (%u) refers to not the program"), _u_prog_id, _u_prog_id);

	return b_valid;
#endif
}

void CProgId::Reset (void) { this->m_error<<__METHOD__<<__e_not_inited;  this->m_value = 0; }

CProgId& CProgId::operator <<(const uint32_t _prog_id) { this->Set(_prog_id); return *this; }

CProgId::operator uint32_t (void) const { return this->Get(); }

uint32_t CProgId::operator () (void) const { return this->Get(); }