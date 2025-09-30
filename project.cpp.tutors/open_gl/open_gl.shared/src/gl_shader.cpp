/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:18:06.457, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface implementation file;
*/
#include "gl_shader.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

#include "shader\gl_compiler.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {}}}}

/////////////////////////////////////////////////////////////////////////////

#define GL_DELETE_STATUS   0x8B80
#define GL_SHADER_TYPE     0x8B4F
#define GL_SHADER_SRC_LEN  0x8B88
#if (0)
enum e_params : uint32_t {
     e_compile  = GL_COMPILE_STATUS , // GL_TRUE if the last compile operation on shader was successful;
     e_delete   = GL_DELETE_STATUS  , // GL_TRUE if shader is currently flagged for deletion, and GL_FALSE otherwise;
     e_type     = GL_SHADER_TYPE    , // GL_VERTEX_SHADER if shader is a vertex shader object, and GL_FRAGMENT_SHADER if shader is a fragment shader object;
     e_info_len = GL_INFO_LOG_LEN   , // the size of the character buffer required to store the information log ;
     e_src_len  = GL_SHADER_SRC_LEN , // the size of the character buffer required to store the shader source ;
};
#endif
CShader:: CShader (void) : m_id(0) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CShader::~CShader (void) {}

procs::CShader& CShader::Cache (void) {
	static procs::CShader m_fn_cache;
	return m_fn_cache;
}

CString  CShader::Class (void) { return __CLASS__; }

err_code CShader::Create (const TType _e_type) {
	_e_type;
	this->m_error() <<__METHOD__<<__s_ok;

	this->m_id = CShader::Cache().Create(_e_type);
	if (0 == this->m_id) { // the error has occurred;
		if (CShader::Cache().Error()) // looks like function pointer is not created;
			return (this->m_error() = CShader::Cache().Error());
		if (GL_INVALID_ENUM == this->m_error.Get_last())
			return this->m_error() << __e_inv_arg = TString().Format(_T("Undefined shader type: %u"), _e_type);
		else
			return this->m_error() << __e_fail = TString().Format(_T("Creating the shader of type '%s' failed"), (_pc_sz) CType::To_str(_e_type));
	}
	__trace::Use_con(true);
	__trace_impt_3(_T("The shader: id=%u, type='%s' is created;\n"), this->Id(), (_pc_sz) CType::To_str(this->Type().Get()));

	return this->Error()();
}

err_code CShader::Destroy (void) {
	this->m_error() <<__METHOD__<<__s_ok;

	if (0 == this->m_id)
		return this->Error()(); // the shader is not created yet; returns no error for such a case;

	if (__failed(CShader::Cache().Delete(this->Id())))
		return (this->m_error() = CShader::Cache().Error()); // sets function cache error is required, otherwise the state of this shared remains the same;

	if (GL_INVALID_VALUE == this->Error().Get_last())
		return (this->m_error() << (err_code) TErrCodes::eData::eInvalid = TString().Format(_T("The ID=%u is not valid"), this->Id()));

	__trace::Use_con(true);
	__trace_warn_3(_T("The shader: id=%u, type='%s' is deleted;\n"), this->Id(), (_pc_sz) CType::To_str(this->Type().Get()));
	this->m_id = 0;

	return this->Error()();
}

TErr_ex& CShader::Error (void) const { return this->m_error; }
uint32_t CShader::Id (void) const { return this->m_id; }

bool   CShader::Is_compiled (void) const {

	this->m_error()<<__METHOD__<<__s_ok;

	shader::CStatus status(this->Id());

	const bool b_compiled = shader::CStatus(this->Id()).Is_compiled();
	if (status.Error())
		this->m_error() = status.Error();

	return b_compiled;
}

bool   CShader::Is_valid (void) const {
	this->m_error() <<__METHOD__<<__s_ok;
	return CShader::Is_valid(this->Id(), this->m_error());
}

bool   CShader::Is_valid (const uint32_t _u_shader_id, CError& _err) {
	_u_shader_id; _err;
	if (0 == _u_shader_id) {
		_err <<__METHOD__<<__e_inv_arg;
		return false;
	}
	bool b_valid = CShader::Cache().Is_valid(_u_shader_id);
	if (false == b_valid) {
		if (CShader::Cache().Error().Is())
			_err = CShader::Cache().Error();
		else
			_err <<__e_inv_arg = TString().Format(_T("'_u_shader_id' (%u) does not refer to shader object;"), _u_shader_id);
	}
	return b_valid;
}

const
shader::CSource& CShader::Src (void) const { return this->m_src; }
shader::CSource& CShader::Src (void)       { return this->m_src; }

const
CType& CShader::Type (void) const { return this->m_type; }
CType& CShader::Type (void)       { return this->m_type; }

/////////////////////////////////////////////////////////////////////////////

CFragment:: CFragment (void) : TBase() { TBase::m_error >>__CLASS__; TBase::Type().Set(TType::e_fragment); }
CFragment::~CFragment (void) {}

err_code CFragment::Create (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(TBase::Create(TBase::Type().Get())))
		return TBase::Error();

	return TBase::Error();
}

CVertex:: CVertex (void) : TBase() { TBase::m_error >>__CLASS__; TBase::Type().Set(TType::e_vertex); }
CVertex::~CVertex (void) {}

err_code CVertex::Create (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(TBase::Create(TBase::Type().Get())))
		return TBase::Error();

	return TBase::Error();
}