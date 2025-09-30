/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Sep-2025 at 09:00:17.628, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL shader identifier wrapper interface implementation file.
*/
#include "gl_shd_id.h"
#include "shared.preproc.h"
#include "gl_procs.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

/////////////////////////////////////////////////////////////////////////////

CShaderId:: CShaderId (const uint32_t _shader_id) : m_value(0) { this->m_error>>__CLASS__<<__METHOD__<<__e_not_inited; if (_shader_id) *this << _shader_id; }
CShaderId::~CShaderId (void) {}

TError& CShaderId::Error (void) const { return this->m_error; }
uint32_t  CShaderId::Get (void) const { return this->m_value; }

bool CShaderId::Is_valid (void) const {
	return CShaderId::Is_valid( this->m_value, this->m_error);
}

bool CShaderId::Is_valid (const uint32_t _shader_id, CError& _err) {
	_shader_id; _err;
	static _pc_sz p_sz_pat_err = _T("'_shader_id' (%u) is invalid");

	if (0 == _shader_id) {
		return false == (_err << __e_inv_arg = TString().Format(p_sz_pat_err, _shader_id)).Is();
	}
	procs::CShader procs;

	const bool b_valid = procs.Is_valid(_shader_id);
	if (procs.Error())
		_err = procs.Error();

	return b_valid;
}

err_code  CShaderId::Set (const uint32_t _u_value) {
	_u_value;
	this->m_error<<__METHOD__<<__s_ok;

	if (false == CShaderId::Is_valid(_u_value, this->m_error))
		return this->Error();

	if (this->Get() == _u_value) // the check of input '_u_prog_id' is already made by above statement, thus '0==0' is avoided;
		return this->m_error << __s_false = TString().Format(_T("The '_u_prog_id' (%u) is already assigned;"), _u_value);

	this->m_value = _u_value;

	return this->Error();
}

CShaderId& CShaderId::operator <<(const uint32_t _shader_id) { this->Set(_shader_id); return *this; }

CShaderId::operator uint32_t (void) const { return this->Get(); }