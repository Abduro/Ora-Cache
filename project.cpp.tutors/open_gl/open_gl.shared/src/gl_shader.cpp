/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:18:06.457, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface implementation file;
*/
#include "gl_shader.h"
#include "gl_logs.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

#include "shader\gl_compiler.h"
#include "procs\gl_procs_shader.h"

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
CShader:: CShader (void) : m_id(0), m_attached(false) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
CShader:: CShader (const CShader& _src) : CShader() { *this= _src; }
CShader:: CShader (CShader&& _victim) : CShader() { *this = _victim; }
CShader::~CShader (void) { this->Delete(); }

CString  CShader::Class (void) { return __CLASS__; }

err_code CShader::Create (const TType _e_type) {
	_e_type;
	this->m_error() <<__METHOD__<<__s_ok;

	__trace::Use_con(true); // ToDo: possibly it is not necessary and must be removed;

	this->m_id = __get_$_procs().Create(_e_type);
	if (0 == this->m_id) {
		this->m_error() = __get_$_procs().Error();
	__trace_err_2(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	} else {
	__trace_impt_2(_T("The shader: id = %u, type='%s' is created;\n"), this->Id(), (_pc_sz) CType::To_str(this->Type().Get()));
	this->Src() << this->Id();
	}
	return this->Error()();
}

err_code CShader::Delete (void) {
	this->m_error() <<__METHOD__<<__s_ok;

	if (0 == this->m_id)
		return this->Error()(); // the shader is not created yet; returns no error for such a case;

	if (__failed(__get_$_procs().Delete(this->Id())))
		return (this->m_error() = __get_$_procs().Error()); // sets function cache error is required, otherwise the state of this shared remains the same;

	if (GL_INVALID_VALUE == this->Error().Get_last())
		return (this->m_error() << (err_code) TErrCodes::eData::eInvalid = TString().Format(_T("The shader id = %u is not valid"), this->Id()));

	__trace::Use_con(true);
	__trace_warn_3(_T("The shader: id = %u, type='%s' is deleted;\n"), this->Id(), (_pc_sz) CType::To_str(this->Type().Get()));
	this->m_id = 0;

	return this->Error()();
}

TErr_ex& CShader::Error (void) const { return this->m_error; }
uint32_t CShader::Id (void) const { return this->m_id; }

bool   CShader::Is_attached (bool _b_state) { const bool b_changed = (_b_state != this->Is_attached()); if (b_changed) this->m_attached = _b_state; return b_changed; }
bool   CShader::Is_attached (void) const { return this->m_attached; }

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
	bool b_valid = __get_$_procs().Is_valid(_u_shader_id);
	if (false == b_valid) {
		if (__get_$_procs().Error().Is())
			_err = __get_$_procs().Error();
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

CShader& CShader::operator = (const CShader& _src) {
	this->m_id = _src.Id(); // ToDo: perhaps the source identifier must be set to zero in order to avoid shader identifier;
	this->Is_attached(_src.Is_attached());
	this->Src() = _src.Src();
	this->Type() = _src.Type();
	return *this;
}

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