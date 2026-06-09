/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 20:04:07.574, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader type wrapper interface implementation file;
*/
#include "gl_shd_type.h"
#include "gl_procs.h"
#include "gl_shader.h"
#include "shared.preproc.h"

#include "gl_procs_shader.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CType:: CType (void) : m_value(e_value::e_undef) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CType:: CType (const CType& _src) : CType() { *this = _src; }

TError& CType::Error (void) const { return this->m_error; }

$Type   CType::Get (void) const { return this->m_value; }
bool    CType::Set (const e_value _e_type) {
	_e_type;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_changed = this->Get() != _e_type;
	if (b_changed)
		this->m_value = _e_type;

	if (this->Get() == e_value::e_undef) this->m_error << __e_not_inited = _T("The type is not set");

	return b_changed;
}

bool CType::Is_fragment (void) const { return e_value::e_fragment == this->Get(); }
bool CType::Is_vertex (void) const { return e_value::e_vertex == this->Get(); }

CString CType::To_str(const uint32_t _u_type) {
	return  procs::$_type_to_str(_u_type);
}

#define __gl_shader_type 0x8B4F // GL_SHADER_TYPE ;

CType::e_value CType::Get_type (const uint32_t _u_shader_id,  CError& _err) {
	_u_shader_id;

	int32_t n_type = (uint32_t)CType::e_value::e_undef;

	if (__failed(__get_$_procs().Params(_u_shader_id, __gl_shader_type, &n_type))) {
		_err = __get_$_procs().Error();
	}

	return  CType::e_value(n_type);
}

CType::operator uint32_t (void) const { return (uint32_t) this->Get(); }

CType& CType::operator = (const CType& _src) { this->Set(_src.Get()); return *this; }