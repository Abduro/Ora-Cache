/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:13:58.859, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface implementation file; 
*/
#include "gl_procs.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_1 { void __warning_lnk_4006 (void) {}}}}}

procs::CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<< __e_not_inited; }

TError&  procs::CBase::Error (void) const { return this->m_error; }

PROC procs::CBase::Get (_pc_sz _p_proc_name) {
	_p_proc_name;
	if (nullptr == _p_proc_name || 0 == ::_tcslen(_p_proc_name)) {
		this->m_error <<__METHOD__<< __e_inv_arg; return nullptr;
	}
	TProcCache::const_iterator found_ = this->m_cached.find(_p_proc_name);
	if (found_ != this->m_cached.end())
		return found_->second;

	CStringA cs_ansi(_p_proc_name);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglgetprocaddress?source=docs ;
	PROC p_proc = ::wglGetProcAddress(cs_ansi.GetString());
	if ( p_proc ) {
		try {
			this->m_cached.insert(::std::make_pair(CString(_p_proc_name), p_proc));
		}
		catch (const ::std::bad_alloc&) {
			this->m_error << __e_no_memory;
		}
	}
	// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;
	else if ( 0 == p_proc || (void*)0x1 == p_proc || (void*)0x2 == p_proc || (void*)0x3 == p_proc || (void*)-1 == p_proc )
	{		// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya ;
		HMODULE h_module = ::LoadLibrary(_T("opengl32.dll"));
		if (0 ==h_module)
			this->m_error.Last();
		else {
			// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress ;
			p_proc = ::GetProcAddress(h_module, cs_ansi.GetString());
			if (0 == p_proc) {
				this->m_error.Last(); this->m_error = TString().Format(_T("Get address of '%s' failed"), _p_proc_name);
			}
		}
	}
	else {
		this->m_error << (err_code) TErrCodes::eExecute::eFunction = TString().Format(_T("the proc '%s' is not found"), _p_proc_name);
	}
	return p_proc;
}

err_code procs::CBase::Get_all (void) { return __e_not_impl; }

CString  procs::CBase::Print (void) const {

	if (this->m_cached.empty()) {
		return CString(_T("#empty"));
	}
	
	CString cs_out;

	for (TProcCache::const_iterator it_ = this->m_cached.begin(); it_ != this->m_cached.end(); ++it_) {
		cs_out += _T("\t");
		cs_out += it_->first;
		cs_out += _T(";\n");
	}

	return cs_out;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz buf_fun_names[] = {
	_T("glBindBuffer"), _T("glBufferData"), _T("glDeleteBuffers"), _T("glGenBuffers"), _T("glNamedBufferData")
};

CBuffer:: CBuffer (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
err_code CBuffer::Bind (uint32_t _u_tgt_id, uint32_t _u_buff_id) {
	_u_tgt_id; _u_buff_id;
	/* Possible errors:
		GL_INVALID_ENUM  : _u_tgt_id is not one of the allowable values ;
		GL_INVALID_VALUE : _u_buff_id is not an identifier of data buffer that is previously returned from a call to glGenBuffers() ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Bind p_fun = reinterpret_cast<pfn_Bind>(CBase::Get(buf_fun_names[0]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_tgt_id, _u_buff_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
err_code CBuffer::Data (uint32_t _u_tgt_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage) {
	_u_tgt_id; _n_size; _p_data; _u_usage;
	/* Possible errors:
		GL_INVALID_ENUM      : _u_tgt_id is not one of the accepted buffer targets ;
		GL_INVALID_VALUE     : _n_size is negative ;
		GL_INVALID_OPERATION : the reserved buffer object of identifier 0 is bound to target ;
		GL_OUT_OF_MEMORY     : the GL is unable to create a data store with the specified size ;
		GL_INVALID_ENUM      : _u_usage is not one of the following tokens ::
			GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Data p_fun = reinterpret_cast<pfn_Data>(CBase::Get(buf_fun_names[1]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_tgt_id, _n_size, _p_data, _u_usage);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml ;
err_code CBuffer::Delete (int32_t _n_count, const uint32_t* _p_buffers) {
	_n_count; _p_buffers;
	// GL_INVALID_VALUE : _n_count is negative ;
	// ToDo: but what is about the pointer to buffers' array ? for example, the count of the buffers that are going to be deleted > 0, but the pointer is 0;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(buf_fun_names[2]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_buffers);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml ;
err_code CBuffer::GenerateIds (int32_t _n_count, uint32_t* _p_buff_ids) {
	_n_count; _p_buff_ids;
	// GL_INVALID_VALUE : _n_count is negative ;
	// ToDo: what is about pointer to the buffer identifiers' array?
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_GenIds p_fun = reinterpret_cast<pfn_GenIds>(CBase::Get(buf_fun_names[3]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_buff_ids);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
err_code CBuffer::Named (uint32_t _u_buff_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage) {
	_u_buff_id; _n_size; _p_data; _u_usage;
	/* Possible errors:
		GL_INVALID_VALUE     : _n_size is negative.
		GL_INVALID_OPERATION : _u_buff_id is zero (0) that is the identifier of the reserved buffer object;
		GL_INVALID_OPERATION : _u_buff_id is not the identifier of an existing buffer object ;
		GL_INVALID_OPERATION : GL_BUFFER_IMMUTABLE_STORAGE flag of the buffer object is GL_TRUE ; i.e. the buffer is *read-only*;
		GL_OUT_OF_MEMORY     : the GL is unable to create a data store with the specified _n_size ;
		GL_INVALID_ENUM      : _u_usage is *not* one of the acceptable values ::
			GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Named p_fun = reinterpret_cast<pfn_Named>(CBase::Get(buf_fun_names[4]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_buff_id, _n_size, _p_data, _u_usage);

	return CBase::Error();
}

err_code CBuffer::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(buf_fun_names); i_++) {
		if (nullptr == CBase::Get(buf_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

#define GL_SHADER_COMPILER 0x8dfa // from glcorearb.h ;

CCompiler:: CCompiler (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

bool CCompiler::Is_supported (void) const {

	CBase::m_error <<__METHOD__<<__s_ok;

	bool b_result = false;

	CParam param;
	b_result = param.GetBool(GL_SHADER_COMPILER);

	if (param.Error().Is()) {
		if (GL_INVALID_ENUM == CError_ex().Get_last())
			CBase::m_error << __e_inv_arg = TString().Format(_T("The param id (0x%04x) is undefined"), GL_SHADER_COMPILER);
		else
			CBase::m_error = param.Error();
	}

	return b_result;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz ctx_fun_names[] = { _T("wglChoosePixelFormatARB"), _T("wglCreateContextAttribsARB"), _T("wglSwapIntervalEXT") };

CContext:: CContext (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ;
int32_t  CContext::ChoosePxFormatArb (HDC _h_dc, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count) {
	_h_dc; _p_atts_i; _p_atts_f; _u_max_fmts; _p_fmts; _p_fmt_count;
	// it returns: 0 - this is the failure, otherwise the result value > 0, that means success;
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0; // this is the failure result; in case of unsuccessful loading the function it will be returned to the caller;
	
	// this is the function for creating draw renderer context;
	pfn_ChoosePxFormatArb p_fun = reinterpret_cast<pfn_ChoosePxFormatArb>(CBase::Get(ctx_fun_names[0]));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure; (done)

	n_result = p_fun(_h_dc, _p_atts_i, _p_atts_f, _u_max_fmts, _p_fmts, _p_fmt_count);
	return n_result;
}
// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
HGLRC    CContext::CreateCtxAttsArb (HDC _h_dc, HGLRC _h_shared_ctx, const int* p_att_lst) {
	_h_dc; _h_shared_ctx; p_att_lst;
	// on failure returns nullptr; extended error information can be obtained with GetLastError() ;
	/* Possible error codes:
		ERROR_DC_NOT_FOUND        : _h_dc is not a valid device context handle ;
		ERROR_INVALID_PIXEL_FORMAT: the pixel format associated with _h_dc does not support OpenGL contexts providing the requested API major and minor version, forward-compatible flag ;
		ERROR_INVALID_OPERATION   : _h_shared_ctx is neither zero nor a valid context handle ;
		ERROR_INVALID_OPERATION   : _h_shared_ctx was created on a different device context than the one referenced by _h_dc ; or if the contexts are otherwise incompatible ;
		ERROR_NO_SYSTEM_RESOURCES : the OpenGL server does not have enough resources to allocate the new context ;
		ERROR_INVALID_PARAMETER   : an unrecognized attribute is present in attribute list p_att_lst ;
		ERROR_INVALID_VERSION_ARB : the major and minor attributes of the version with compatible bit specify non-exist version ;
		ERROR_INVALID_PROFILE_ARB : WGL_CONTEXT_PROFILE_MASK_ARB has no bits set;
			it has any bits set other than WGL_CONTEXT_CORE_PROFILE_BIT_ARB and WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	HGLRC h_render = nullptr;

	pfn_CreateCtxAttsArb p_fun = reinterpret_cast<pfn_CreateCtxAttsArb>(CBase::Get(ctx_fun_names[1]));
	if (nullptr == p_fun)
		return h_render;

	h_render = p_fun(_h_dc, _h_shared_ctx, p_att_lst);

	return h_render;
}
// https://www.khronos.org/opengl/wiki/Swap_Interval ;
bool  CContext::SwapIntervalExt (const int _n_interval) {
	_n_interval;
	/* Possible error reasons:
		- PFD_DOUBLEBUFFER must be set, but it is not;
		- the required OpenGL is not installed;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0;

	pfn_SwapIntervalExt p_fun = reinterpret_cast<pfn_SwapIntervalExt>(CBase::Get(ctx_fun_names[2]));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure;

	n_result = p_fun(_n_interval);
	return !!n_result;
}

err_code CContext::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(ctx_fun_names); i_++) {
		if (nullptr == CBase::Get(ctx_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

/////////////////////////////////////////////////////////////////////////////
static _pc_sz param_fun_names[] = {
	_T("glGetBooleanv"), _T("glGetFloatv"), _T("glGetIntegerv")
};

CParam:: CParam (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGet.xml ;
bool    CParam::GetBool (uint32_t _u_param_id) {
	_u_param_id;
	// GL_INVALID_ENUM : _u_param_id has unknown value;
	CBase::m_error << __METHOD__ << __s_ok;

	uint32_t u_result = 0;

	pfn_GetBool p_fun = reinterpret_cast<pfn_GetBool>(CBase::Get(param_fun_names[0]));
	if (nullptr == p_fun) { // the error is set by parent class;
		return !!u_result;
	}

	p_fun(_u_param_id, &u_result);

	return !!u_result;
}

float   CParam::GetFloat (uint32_t _u_param_id) {
	_u_param_id;
	// GL_INVALID_ENUM : _u_param_id has unknown value;
	CBase::m_error << __METHOD__ << __s_ok;

	float f_result = 0.0f;

	pfn_GetFloat p_fun = reinterpret_cast<pfn_GetFloat>(CBase::Get(param_fun_names[1]));
	if (nullptr == p_fun) {
		return f_result;
	}

	p_fun(_u_param_id, &f_result);

	return f_result;
}

int32_t CParam::GetInt (uint32_t _u_param_id) {
	_u_param_id;
	// GL_INVALID_ENUM : _u_param_id has unknown value;
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0;

	pfn_GetFInt p_fun = reinterpret_cast<pfn_GetFInt>(CBase::Get(param_fun_names[1]));
	if (nullptr == p_fun) {
		return n_result;
	}

	p_fun(_u_param_id, &n_result);

	switch (CErr_ex().Get_last()) {
	case GL_INVALID_ENUM: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: '_u_param_id' (%u) is invalid;"), _u_param_id);
	default:;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz prog_fun_names[] = {
	_T("glAttachShader"), _T("glGetAttribLocation"), _T("glCreateProgram"), _T("glDeleteProgram"), _T("glGetProgramInfoLog"), _T("glLinkProgram"),
	_T("glGetProgramiv"), _T("glUseProgram"), _T("glValidateProgram")
};

CProg:: CProg (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
err_code CProg::Attach (uint32_t _prog_id, uint32_t _shader_id) {
	_prog_id; _shader_id;
	/* Possible errors:
		GL_INVALID_VALUE : either _prog_id or _shader_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not an identifier of program object ;
		GL_INVALID_OPERATION : _shader_id is not an identifier of shader object ;
		GL_INVALID_OPERATION : the shader of _shader_id identifier is already attached to the program object of _prog_id ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Attach p_fun = reinterpret_cast<pfn_Attach>(CBase::Get(prog_fun_names[0]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _shader_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
int32_t  CProg::AttLocate (uint32_t _prog_id, char* _p_name) {
	_prog_id; _p_name;
	/* Possible errors, the one error code is for several specific cases:
		GL_INVALID_OPERATION : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : the object of _prog_id is not a program object ;
		GL_INVALID_OPERATION : the program of _prog_id has not been successfully linked ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	static const int32_t n_err_result = -1;

	int32_t n_result = n_err_result;

	pfn_AttLocate  p_fun = reinterpret_cast<pfn_AttLocate>(CBase::Get(prog_fun_names[1]));
	if (nullptr == p_fun)
		return n_result;

	p_fun(_prog_id, _p_name);

	return n_result;
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
uint32_t CProg::Create (void){
	// the returned result value is zero (0) if an error occurs creating the program object ;
	// calling glGetProgramInfoLog() may provides actual error details, otherwise the error code is generic GL_OUT_OF_MEMORY ;
	CBase::m_error << __METHOD__ << __s_ok;

	static const uint32_t n_err_result = 0;

	uint32_t n_result = n_err_result;

	pfn_Create  p_fun = reinterpret_cast<pfn_Create>(CBase::Get(prog_fun_names[2]));
	if (nullptr == p_fun)
		return n_result;

	n_result = p_fun();
	if (0 == n_result) {
		switch (CErr_ex().Get_last()) {
		case GL_OUT_OF_MEMORY: CBase::m_error << __e_no_memory = _T("#__e_no_mem: generic error;"); break;
		default:; // keeps the error state in 'no error', but program id still equals to zero, the caller needs to call glGetProgramInfoLog();
		}
	}

	return n_result;
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
err_code CProg::Delete  (uint32_t _prog_id){
	_prog_id;
	// GL_INVALID_VALUE : _prog_id is not a value generated by OpenGL ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(prog_fun_names[3]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	switch (CErr_ex().Get_last()) {
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is not valid;"), _prog_id);
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
err_code CProg::InfoLog (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log){
	_prog_id; _buf_size; _log_len; _p_log;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not an identifier of program object ;
		GL_INVALID_VALUE     : _buf_size is less than 0 ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_InfoLog p_fun = reinterpret_cast<pfn_InfoLog>(CBase::Get(prog_fun_names[4]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _buf_size, _log_len, _p_log);

	switch (CErr_ex().Get_last()) {
	case GL_INVALID_OPERATION: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program object"), _prog_id); break;
	case GL_INVALID_VALUE: {
			if (0 > _buf_size)
			     CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_buf_size' (%d) is negative;"), _buf_size);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id);
		} break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml ;
err_code CProg::Link    (uint32_t _prog_id){
	_prog_id;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : the object of _prog_id is not a program one ;
		GL_INVALID_OPERATION : _prog_id is identifier of the currently active program object and transform feedback mode is active ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Link p_fun = reinterpret_cast<pfn_Link>(CBase::Get(prog_fun_names[5]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
err_code CProg::Params  (uint32_t _prog_id, uint32_t _param_id, int32_t* _p_params){
	_prog_id; _param_id; _p_params;
	/* Possible errors:
		GL_INVALID_ENUM      : _param_id is not an accepted value ;
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not the identifier of a program object ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Params p_fun = reinterpret_cast<pfn_Params>(CBase::Get(prog_fun_names[6]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _param_id, _p_params);

	switch (CErr_ex().Get_last()) {
	case GL_INVALID_ENUM: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: '_param_id' (%u) is not accepted;"), _param_id); break;
	case GL_INVALID_OPERATION: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program;"), _prog_id); break;
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
err_code CProg::Use (uint32_t _prog_id){
	_prog_id;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is neither 0 nor a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not the identifier of a program object ;
		GL_INVALID_OPERATION : the program object of _prog_id could not be made part of current state ;
		GL_INVALID_OPERATION : transform feedback mode is active ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Use p_fun = reinterpret_cast<pfn_Use>(CBase::Get(prog_fun_names[7]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
err_code CProg::Validate (uint32_t _prog_id){
	_prog_id;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not the identifier of a program object ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Validate p_fun = reinterpret_cast<pfn_Validate>(CBase::Get(prog_fun_names[8]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	return CBase::Error();
}

err_code CProg::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(prog_fun_names); i_++) {
		if (nullptr == CBase::Get(prog_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

#define GL_COMPILE_STATUS        0x8B81 // from glcorearb.h ;
#define GL_INFO_LOG_LENGTH       0x8B84 // from glcorearb.h ;
#define GL_SHADER_SOURCE_LENGTH  0x8B88 // from glcorearb.h ;

#define __err_no_support DXGI_ERROR_UNSUPPORTED

static _pc_sz shader_fun_names[] = {
	// 0                     1                      2                      3                          4                    5                 6  
	_T("glCompileShader"),  _T("glCreateShader"),  _T("glDeleteShader"),  _T("glGetShaderInfoLog"),  _T("glGetShaderiv"), _T("glIsShader"), _T("glShaderSource")
};

CShader:: CShader (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml ;
err_code  CShader::Compile (uint32_t _shader_id) {
	_shader_id;
	/* Possible errors:
		GL_INVALID_VALUE     : _shader_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _shader_id does not refer to a shader object ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Compile p_fun = reinterpret_cast<pfn_Compile>(CBase::Get(shader_fun_names[0]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_shader_id);

	switch (CErr_ex().Get_last()) {
	case GL_INVALID_VALUE:  CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: _shader_id (%u) is not valid;"), _shader_id); break;
	case GL_INVALID_OPERATION:  CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: _shader_id (%u) refers to not shader;"), _shader_id); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
uint32_t  CShader::Create  (uint32_t _u_type) {
	_u_type;
	/* Possible errors:
		the retult is 0 : an error occurs creating the shader object; it very looks like a call to glGetShaderInfoLog() must be made for getting error desc ;
		GL_INVALID_ENUM : is not an accepted value ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	static const uint32_t n_err_result = 0;

	uint32_t n_result = n_err_result;

	pfn_Create p_fun = reinterpret_cast<pfn_Create>(CBase::Get(shader_fun_names[1]));
	if (nullptr == p_fun) // the error object is set by parent class 'CBase';
		return n_result;

	n_result = p_fun(_u_type);

	return n_result;
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml ;
err_code  CShader::Delete  (uint32_t _shader_id) {
	_shader_id;
	// GL_INVALID_VALUE : _shader_id is not a value generated by OpenGL ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(shader_fun_names[2]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_shader_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml ;
err_code  CShader::InfoLog (uint32_t _shader_id, int32_t _n_max_length, int32_t* _p_log_len, char* _p_log) {
	_shader_id; _n_max_length; _p_log_len; _p_log;
	/* Possible errors:
		GL_INVALID_VALUE     : _shader_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _shader_id does not refer to a shader object ;
		GL_INVALID_VALUE     : _n_max_length is less than 0 ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_InfoLog p_fun = reinterpret_cast<pfn_InfoLog>(CBase::Get(shader_fun_names[3]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_shader_id, _n_max_length, _p_log_len, _p_log);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glIsShader.xml ;
bool   CShader::Is_valid  (uint32_t _shader_id) {
	_shader_id;
	// no error is generated if _shader_id is not a valid shader object identifier ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_IsValid p_fun = reinterpret_cast<pfn_IsValid>(CBase::Get(shader_fun_names[5]));
	if (nullptr == p_fun) {
		return false;
	}

	const uint32_t b_result = !!p_fun(_shader_id);

	return b_result;
}

// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml ;
err_code  CShader::Params  (uint32_t _shader_id, uint32_t _param_type, int32_t* _p_params) {
	_shader_id; _param_type; _p_params;
	CBase::m_error << __METHOD__ << __s_ok;
	/* Possible errors:
		GL_INVALID_ENUM : _param_type is not an accepted value ;
		GL_INVALID_VALUE : _shader_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _param_type is GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH, or GL_SHADER_SOURCE_LENGTH, but a shader compiler is not supported ;
		GL_INVALID_OPERATION : _shader_id does not refer to a shader object ;
	*/
	pfn_Params p_fun = reinterpret_cast<pfn_Params>(CBase::Get(shader_fun_names[4]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_shader_id, _param_type, _p_params);
	
	switch (CError_ex().Get_last()) {
	case GL_INVALID_ENUM : { CBase::m_error << (err_code)TErrCodes::eData::eNotFound = TString().Format(_T("_param_type (%u) is invalid"), _param_type); } break;
	case GL_INVALID_VALUE : { CBase::m_error << (err_code)TErrCodes::eData::eInvalid = TString().Format(_T("_shader_id (%u) is invalid"), _shader_id); } break;
	case GL_INVALID_OPERATION : {
		if (false) {}
		else if (GL_COMPILE_STATUS == _param_type) { CBase::m_error << __err_no_support = TString().Format(_T("No support for compiler: __compile_status (0x%04%x) #na"), _param_type); }
		else if (GL_INFO_LOG_LENGTH == _param_type) { CBase::m_error << __err_no_support = TString().Format(_T("No support for compiler: __info_log_len (0x%04%x) #na"), _param_type); }
		else if (GL_SHADER_SOURCE_LENGTH == _param_type) { CBase::m_error << __err_no_support = TString().Format(_T("No support for compiler: __shader_src_len (0x%04%x) #na"), _param_type); }
		else {
			CBase::m_error << __e_inv_arg = TString().Format(_T("_shader_id (%u) refers to no shader"), _shader_id); } break;
		}
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml ;
err_code  CShader::Source  (uint32_t _shader_id, int32_t _n_count, const char** const _p_string, const int32_t* _p_length) {
	_shader_id; _n_count; _p_string; _p_length;
	/* Possible errors:
		GL_INVALID_OPERATION : _shader_id does not refer to a shader object ;
		GL_INVALID_VALUE     : _shader_id is not a value generated by OpenGL ;
		GL_INVALID_VALUE     : _n_count is less than 0 ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Source p_fun = reinterpret_cast<pfn_Source>(CBase::Get(shader_fun_names[6]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_shader_id, _n_count, _p_string, _p_length);

	switch (CErr_ex().Get_last()){
	case GL_INVALID_OPERATION: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_shader_id'(%u) refers to not shader object;"), _shader_id); break;
	case GL_INVALID_VALUE: {
			if (0 > _n_count)
			     CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_n_count'(%d) cannot be negative;"), _n_count);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: '_shader_id'(%u) is invalid;"), _shader_id);
		} break;
	default:;
	}
	return CBase::Error();
}

err_code CShader::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(shader_fun_names); i_++) {
		if (nullptr == CBase::Get(shader_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz vtx_fun_names[] = {
	_T("glVertexAttribPointer"), _T("glVertexAttribIPointer"), _T("glVertexAttribLPointer"), _T("glBindVertexArray"), _T("glDeleteVertexArrays"),
	_T("glDisableVertexAttribArray"), _T("glDisableVertexArrayAttrib"), _T("glEnableVertexAttribArray"), _T("glEnableVertexArrayAttrib"), _T("glGenVertexArrays")
};

CVertex:: CVertex (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
/*
https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
Error codes that may be returned:
	GL_INVALID_VALUE : the index '_u_ndx' is greater than or equal to GL_MAX_VERTEX_ATTRIBS ;
	GL_INVALID_VALUE : the size '_n_size' is not 1, 2, 3, 4 or (for glVertexAttribPointer), GL_BGRA ;
	GL_INVALID_ENUM  : tye type '_u_type' is not an accepted value ;
	GL_INVALID_VALUE : '_n_stride' is negative value ;
	GL_INVALID_OPERATION : the size is GL_BGRA and type is not GL_UNSIGNED_BYTE, GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV ;
	GL_INVALID_OPERATION : the type is GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV and size is not 4 or GL_BGRA ;
	GL_INVALID_OPERATION : the type is GL_UNSIGNED_INT_10F_11F_11F_REV and size is not 3 ;
	GL_INVALID_OPERATION : the size is GL_BGRA and normalized is GL_FALSE ; (glVertexAttribPointer)
	GL_INVALID_OPERATION : zero is bound to the GL_ARRAY_BUFFER buffer object binding point and the pointer argument is not NULL ;
*/
err_code CVertex::AttPtr (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void** _ptr) {
	_u_ndx; _n_size; _u_type; _b_norm; _n_stride; _ptr;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr p_fun = reinterpret_cast<pfn_AttPtr>(CBase::Get(vtx_fun_names[0]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx, _n_size, _u_type, _b_norm, _n_stride, _ptr);

	return CBase::Error();
}

err_code CVertex::AttPtr_I (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr) {
	_u_ndx; _n_size; _u_type; _n_stride; _ptr;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr_I p_fun = reinterpret_cast<pfn_AttPtr_I>(CBase::Get(vtx_fun_names[1]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx, _n_size, _u_type, _n_stride, _ptr);

	return CBase::Error();
}

err_code CVertex::AttPtr_L (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr) {
	_u_ndx; _n_size; _u_type; _n_stride; _ptr;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_AttPtr_L p_fun = reinterpret_cast<pfn_AttPtr_L>(CBase::Get(vtx_fun_names[2]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx, _n_size, _u_type, _n_stride, _ptr);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
err_code CVertex::Bind   (uint32_t _arr_id) {
	_arr_id;
	// GL_INVALID_OPERATION : _arr_id is not zero or is the same with previously returned from a call to glGenVertexArrays ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Bind p_fun = reinterpret_cast<pfn_Bind>(CBase::Get(vtx_fun_names[3]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
err_code CVertex::Delete (int32_t _n_count, const uint32_t* _p_arrays) {
	_n_count; _p_arrays;
	// GL_INVALID_VALUE : _n_count is negative;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(vtx_fun_names[4]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_arrays);

	return CBase::Error();
}
/*
https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
the error codes that may be returned by these functions:
	GL_INVALID_OPERATION is generated by glEnableVertexAttribArray and glDisableVertexAttribArray if no vertex array object is bound.
	GL_INVALID_OPERATION is generated by glEnableVertexArrayAttrib and glDisableVertexArrayAttrib if vaobj is not the name of an existing vertex array object.
	GL_INVALID_VALUE is generated if '_u_ndx' is greater than or equal to GL_MAX_VERTEX_ATTRIBS.
*/
err_code CVertex::DisableAttArr (uint32_t _u_ndx) {
	_u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_DisableAttArr p_fun = reinterpret_cast<pfn_DisableAttArr>(CBase::Get(vtx_fun_names[5]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx);

	return CBase::Error();
}

err_code CVertex::DisableArrAtt (uint32_t _arr_id, uint32_t _u_ndx) {
	_arr_id; _u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_DisableArrAtt p_fun = reinterpret_cast<pfn_DisableArrAtt>(CBase::Get(vtx_fun_names[6]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id, _u_ndx);

	return CBase::Error();
}

err_code CVertex::EnableAttArr (uint32_t _u_ndx) {
	_u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_EnableAttArr p_fun = reinterpret_cast<pfn_EnableAttArr>(CBase::Get(vtx_fun_names[7]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_ndx);

	return CBase::Error();
}

err_code CVertex::EnableArrAtt (uint32_t _arr_id, uint32_t _u_ndx) {
	_arr_id; _u_ndx;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_EnableArrAtt p_fun = reinterpret_cast<pfn_EnableArrAtt>(CBase::Get(vtx_fun_names[8]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_arr_id, _u_ndx);

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
err_code CVertex::GenerateIds (int32_t _n_count, uint32_t* _p_ids) {
	_n_count; _p_ids;
	// GL_INVALID_VALUE is generated if _n_count is negative ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_GenIds p_fun = reinterpret_cast<pfn_GenIds>(CBase::Get(vtx_fun_names[9]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_n_count, _p_ids);

	return CBase::Error();
}

err_code CVertex::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(vtx_fun_names); i_++) {
		if (nullptr == CBase::Get(vtx_fun_names[i_]))
			break;
	}

	return CBase::Error();
}