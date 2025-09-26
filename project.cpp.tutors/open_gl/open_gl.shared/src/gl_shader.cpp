/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2025 at 23:18:06.457, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' shader base interface implementation file;
*/
#include "gl_shader.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

#define GL_COMPILE_STATUS  0x8B81

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

CCompiler:: CCompiler (const uint32_t _u_shader_id) : m_shader_id(_u_shader_id) { this->m_error()>>__CLASS__<<__METHOD__<<__e_not_inited; }
CCompiler::~CCompiler (void) {}

err_code CCompiler::Compile (void) {

	this->m_error() <<__METHOD__<<__s_ok;

	if (false == this->ShaderId())
		return this->m_error()<<__e_not_inited = _T("Shader id is not valid");

	procs::CShader& procs = CShader::Cache();

	if (__failed(procs.Compile(this->ShaderId()))) {
		this->Log().Set(this->ShaderId());        // gets log info for this complilation; the log error code can be retrieved by direct call to log error; 
		return this->m_error() = procs.Error();
	}

	return this->Error()();
}

TErr_ex& CCompiler::Error (void) const { return this->m_error; }

bool  CCompiler::Is_compiled (void) const {
	this->m_error() <<__METHOD__<<__s_ok;

	if (false == this->ShaderId())
		return this->m_error()<<__e_not_inited = _T("Shader id is not valid");

	procs::CShader& procs = CShader::Cache();
	
	int32_t n_result = 0;
	if (__failed(procs.Params(this->ShaderId(), GL_COMPILE_STATUS, &n_result))) {
		this->m_error() = procs.Error();
		return !!n_result;
	}

	return !!n_result;
}

bool  CCompiler::Is_supported (void) const {

	this->m_error() <<__METHOD__<<__s_ok;

	procs::CCompiler cmpl;
	const bool b_support = cmpl.Is_supported();

	if (cmpl.Error().Is())
		this->m_error() = cmpl.Error();
	else
		this->m_error() <<__e_not_inited = _T("Shader compiler is not supported");
	return b_support;
}

const
CLog&    CCompiler::Log (void) const { return this->m_log; }
CLog&    CCompiler::Log (void)       { return this->m_log; }

uint32_t CCompiler::ShaderId  (void) const { return this->m_shader_id; }
err_code CCompiler::ShaderId  (const uint32_t _u_shader_id) {
	_u_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;

	if (false == CShader::Is_valid(_u_shader_id, this->m_error()))
		return this->Error()();

	this->m_shader_id = _u_shader_id;

	return this->Error()();
}

CCompiler& CCompiler::operator <<(const uint32_t _u_shader_id) { this->ShaderId(_u_shader_id); return *this; }

/////////////////////////////////////////////////////////////////////////////

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

#define GL_DELETE_STATUS   0x8B80
#define GL_SHADER_TYPE     0x8B4F
#define GL_INFO_LOG_LEN    0x8B84
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

	shader::CCompiler cmpl(this->Id());

	const bool b_compiled = cmpl.Is_compiled();
	if (false == b_compiled)
		this->m_error() = cmpl.Error()();

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
	if (false == b_valid && CShader::Cache().Error().Is())
		_err = CShader::Cache().Error();

	return b_valid;
}

const
shader::CSource& CShader::Src (void) const { return this->m_src; }
shader::CSource& CShader::Src (void)       { return this->m_src; }

const
CType& CShader::Type (void) const { return this->m_type; }
CType& CShader::Type (void)       { return this->m_type; }

/////////////////////////////////////////////////////////////////////////////

CLog:: CLog (void) { 
	this->m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited;
}
CLog::~CLog (void) {}

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
	if (__failed(procs.Params(_u_shader_id, GL_INFO_LOG_LEN, &n_length))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	if (0 == n_length) {
		this->m_buffer + _T("#no_info");
		return this->Error()();
	}
	// retrieves the actual data from the log;
	::std::vector<char> buffer(n_length + 1, 0);
	if (__failed(procs.InfoLog(_u_shader_id, n_length, &n_length, buffer.data()))) {
		this->m_buffer = _T("#error");
		return this->m_error() = procs.Error();
	}

	this->m_buffer = buffer.data(); // ATL::CString makes the auto-conversion from 'char' to 'tchar';

	return this->Error()();
}

/////////////////////////////////////////////////////////////////////////////

CSource:: CSource (void) { this->m_error() >> TString().Format(_T("%s::%s"), (_pc_sz) CShader::Class(), (_pc_sz)__CLASS__)<<__METHOD__<<__e_not_inited; }
CSource::~CSource (void) {}

TErr_ex& CSource::Error (void) const { return this->m_error; }

err_code CSource::Set (_pc_sz _p_source, const uint32_t _u_shader_id) {
	_p_source; _u_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;

	if (nullptr == _p_source || CString(_p_source).IsEmpty())
		return this->m_error() << __e_inv_arg = _T("Source code is empty");

	if (false == CShader::Is_valid(_u_shader_id, this->m_error())) {
		return this->Error()();
	}
	this->m_buffer = _p_source; m_buffer.Trim();

	CStringA src_a((_pc_sz) this->m_buffer); // converts to ansi-char from unicode if necessary;
	int32_t n_len = src_a.GetLength();

	const char* p_buffer = src_a.GetBuffer();

	procs::CShader& procs = CShader::Cache();
	if (__failed(procs.Source(_u_shader_id, 1, &p_buffer, &n_len)))
		return this->m_error() = procs.Error();

	return this->Error()();
}

err_code CSource::Set (const uint16_t _res_id, const uint32_t _n_shader_id) {
	_res_id; _n_shader_id;
	this->m_error()<<__METHOD__<<__s_ok;
	if (0 == _res_id)
		return this->m_error() << __e_inv_arg = _T("String resource identifier is invalid");

	CString cs_src;
	cs_src.LoadString(_res_id);

	return this->Set((_pc_sz) cs_src, _n_shader_id);
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