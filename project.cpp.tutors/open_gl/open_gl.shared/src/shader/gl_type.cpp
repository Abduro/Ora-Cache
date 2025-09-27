/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 20:04:07.574, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader type wrapper interface implementation file;
*/
#include "gl_type.h"
#include "gl_procs.h"
#include "gl_shader.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

CType:: CType (void) : m_value(e_value::e_undef) { this->m_error()>>__CLASS__<<__METHOD__<<__e_not_inited; }

TErr_ex& CType::Error (void) const { return this->m_error; }

TType   CType::Get (void) const { return this->m_value; }
bool    CType::Set (const e_value _e_type) {
	_e_type;
	const bool b_changed = this->Get() != _e_type;
	if (b_changed)
		this->m_value = _e_type;
	return b_changed;
}

CString CType::To_str(const uint16_t _u_type) {
	_u_type;
	CString cs_out;
	switch (_u_type) {
	case e_value::e_compute   : cs_out = _T("__compute"); break;
	case e_value::e_fragment  : cs_out = _T("__fragment"); break;
	case e_value::e_geometry  : cs_out = _T("__geometry"); break;
	case e_value::e_tess_ctrl : cs_out = _T("__tess_ctrl"); break;
	case e_value::e_tess_eval : cs_out = _T("__tess_eval"); break;
	case e_value::e_vertex    : cs_out = _T("__vertex"); break;
	default:
		cs_out.Format(_T("#undef(%u)"), _u_type);
	}
	return  cs_out;
}

#define __gl_shader_type 0x8B4F // GL_SHADER_TYPE ;

CType::e_value CType::Get_type (const uint32_t _u_shader_id,  CError& _err) {
	_u_shader_id;

	procs::CShader& procs = CShader::Cache();

	int32_t n_type = CType::e_value::e_undef;

	if (__failed(procs.Params(_u_shader_id, __gl_shader_type, &n_type))) {
		_err = procs.Error();
	}

	return  CType::e_value(n_type);
}

CType::operator uint16_t (void) const { return this->Get(); }