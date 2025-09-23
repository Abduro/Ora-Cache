/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:18:06.457, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface implementation file;
*/
#include "gl_shader.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

CType:: CType (void) : m_value(e_value::e_undef) {}

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

CType::operator uint16_t (void) const { return this->Get(); }
}}}}
/////////////////////////////////////////////////////////////////////////////

#define GL_COMPILE_STATUS  0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84

CShader:: CShader (void) : m_id(0) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CShader::~CShader (void) {}

procs::CShader& CShader::Cache (void) {
	static procs::CShader m_fn_cache;
	return m_fn_cache;
}

CString CShader::Class (void) { return __CLASS__; }

err_code CShader::Create (const TType _e_type) {
	_e_type;
	this->m_error() <<__METHOD__<<__s_ok;

	this->m_id = this->Cache().Create(_e_type);
	if (0 == this->m_id) { // the error has occurred;
		if (this->Cache().Error()) // looks like function pointer is not created;
			return (this->m_error() = this->Cache().Error());
		if (GL_INVALID_ENUM == this->m_error.Get_last())
			return this->m_error() << __e_inv_arg = TString().Format(_T("Undefined shader type: %u"), _e_type);
		else
			return this->m_error() << __e_fail = TString().Format(_T("Creating the shader of type '%s' failed"), (_pc_sz) CType::To_str(_e_type));
	}
	__trace::Use_con(true);
	__trace_impt_3(_T("Creating the shader of type '%s' succeeded;"), (_pc_sz) CType::To_str(_e_type));

	return this->Error()();
}

err_code CShader::Destroy (void) {
	this->m_error() <<__METHOD__<<__s_ok;

	if (0 == this->m_id)
		return this->Error()(); // the shader is not created yet; returns no error for such a case;

	if (__failed(this->Cache().Delete(this->Id())))
		return (this->m_error() = this->Cache().Error()); // sets function cache error is required, otherwise the state of this shared remains the same;

	if (GL_INVALID_VALUE == this->Error().Get_last())
		return (this->m_error() << (err_code) TErrCodes::eData::eInvalid = TString().Format(_T("The ID=%u is not valid"), this->Id()));

	this->m_id = 0;
	__trace::Use_con(true);
	__trace_warn_3(_T("The shader: id=%u, type='%s' is deleted;"), this->Id(), (_pc_sz) CType::To_str(this->Type().Get()));

	return this->Error()();
}

TErr_ex& CShader::Error (void) const { return this->m_error; }
uint32_t CShader::Id (void) const { return this->m_id; }

bool  CShader::Is_compiled (void) const {
	this->m_error() <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->Error()();

	return this->Error()();
}

bool  CShader::Is_valid (void) const {
	this->m_error() <<__METHOD__<<__s_ok;
	bool b_valid = false;

	if (0 == this->Id())
		return false == (this->m_error() << __e_not_inited).Is();

	return b_valid;
}

const
CType& CShader::Type (void) const { return this->m_type; }
CType& CShader::Type (void)       { return this->m_type; }

/////////////////////////////////////////////////////////////////////////////

CLog:: CLog (void) { 
	this->m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited;
}

TErr_ex& CLog::Error (void) const { return this->m_error; }

_pc_sz   CLog::Get (void) const { return (_pc_sz) this->m_buffer; }

err_code CLog::Set (const uint32_t _u_shader_id) {
	_u_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;

	if (0 == _u_shader_id)
		return this->m_error() <<__e_inv_arg = TString().Format(_T("Invalid shader id (%u)"), _u_shader_id);

	procs::CShader& procs = CShader::Cache();
	// (1) gets the shader log length;
	int32_t n_length = 0;
	if (__failed(procs.Params(_u_shader_id, GL_INFO_LOG_LENGTH, &n_length)))
		return this->m_error() = procs.Error();

	if (0 == n_length) {
		this->m_buffer + _T("#no_info");
		return this->Error()();
	}
	// retrieves the actual data from the log;
	::std::vector<char> buffer(n_length + 1, 0);
	if (__failed(procs.InfoLog(_u_shader_id, n_length, &n_length, buffer.data())))
		return this->m_error() = procs.Error();

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';

	return this->Error()();
}