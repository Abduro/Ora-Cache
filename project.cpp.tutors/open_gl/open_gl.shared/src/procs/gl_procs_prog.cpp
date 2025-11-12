/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 01:21:58.588, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL program functions' loader interface implementation file;
*/
#include "gl_procs_prog.h"
#include "gl_procs.h"
#include "gl_procs_shader.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::program;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace _impl {

	using namespace ex_ui::draw::open_gl::procs::program;

	_pc_sz e_iface_to_str (const e_interface _e_iface) {
		_e_iface;
		static CString  cs_out;
		switch (_e_iface) {
		case e_interface::e_buff_var : cs_out = _T("e_buff_var"); break;
		case e_interface::e_prog_in  : cs_out = _T("e_prog_in"); break;
		case e_interface::e_prog_out : cs_out = _T("e_prog_out"); break;
		case e_interface::e_uniform  : cs_out = _T("e_uniform"); break;
		default:
			cs_out.Format(_T("#iface (%u) is #unk"), _e_iface);
		}
		return (_pc_sz) cs_out;
	}

	_pc_sz e_prop_to_str (const e_property _e_prop) {
		_e_prop;
		static CString  cs_out;
		switch (_e_prop) {
		case e_property::e_arr_size   : cs_out = _T("e_arr_size"); break;
		case e_property::e_arr_stride : cs_out = _T("e_arr_stride"); break;
		case e_property::e_type       : cs_out = _T("e_type"); break;
		default:
			cs_out.Format(_T("#prop (%u) is #unk"), _e_prop);
		}
		return (_pc_sz) cs_out;
	}

	_pc_sz e_prop_set_to_str (const TRawProps& _props) {
		_props;
		static CString cs_out; cs_out.Empty();

		cs_out += _T("{");
		for (size_t i_ = 0; i_ < _props.size(); i_++) {
			cs_out += TString().Dword(static_cast<dword>(_props[i_]));
			if (i_ < _props.size() - 1) cs_out += _T(";");
		}
		cs_out += _T("}");
		return (_pc_sz) cs_out;
	}

}}}}}

using namespace _impl;
/////////////////////////////////////////////////////////////////////////////

static _pc_sz iface_fun_names[] = { _T("glGetProgramInterfaceiv") };

enum class e_iface_fun_ndx : uint32_t { e_get = 0x0 };

CInterface:: CInterface (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

const ::std::vector<e_property>& CInterface::GetProps (const e_interface _iface) {
	_iface;
	static TIface_assoc assoc;
	if (assoc.empty()) { // one time to set the content;
		try {
			assoc.insert(::std::make_pair(e_iface::e_buff_var, ::std::vector<e_prop>{e_prop::e_arr_size, e_prop::e_name_len, e_prop::e_type, e_prop::e_offset, e_prop::e_arr_stride}));
			assoc.insert(::std::make_pair(e_iface::e_prog_in , ::std::vector<e_prop>{e_prop::e_arr_size, e_prop::e_name_len, e_prop::e_type, e_prop::e_location}));
		}
		catch (const ::std::bad_alloc&) {}
	}
	TIface_assoc::const_iterator found = assoc.find(_iface);
	if (assoc.end() == found) {
		static ::std::vector<e_property> no_props;
		return no_props;
	}
	else
		return found->second;
}

const bool CInterface::Is_acceptable (const uint32_t _u_interface) {
	_u_interface;
	return (
	(uint32_t) e_interface::e_buff_var == _u_interface ||
	(uint32_t) e_interface::e_prog_in  == _u_interface ||
	(uint32_t) e_interface::e_prog_out == _u_interface ||
	(uint32_t) e_interface::e_uniform  == _u_interface
	);
}

const bool CInterface::Is_related (const e_interface _e_iface, const e_property _e_prop) {
	_e_iface; _e_prop;
	return false == CInterface::GetProps(_e_iface).empty();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInterface.xhtml ;
err_code CInterface::Get (const uint32_t _prog_id, const e_interface _e_iface, const e_property _e_prop, uint32_t& _u_value) {
	_prog_id; _e_iface; _e_prop; _u_value;
	/* Possible errors:
	GL_INVALID_ENUM      : '_e_iface' is not applicable to '_e_prop';
	GL_INVALID_OPERATION : '_e_prop|_e_iface' pair is 
	                        {GL_MAX_NAME_LENGTH|GL_ATOMIC_COUNTER_BUFFER} or
	                        {GL_MAX_NAME_LENGTH|GL_TRANSFORM_FEEDBACK_BUFFER};
	GL_INVALID_OPERATION : '_e_prop|_e_iface' pair is
	                        {GL_MAX_NUM_ACTIVE_VARIABLES|~GL_UNIFORM_BLOCK} or
	                        {GL_MAX_NUM_ACTIVE_VARIABLES|GL_SHADER_STORAGE_BLOCK} or
	                        {GL_ATOMIC_COUNTER_BUFFER|GL_TRANSFORM_FEEDBACK_BUFFER};
	GL_INVALID_OPERATION : '_e_prop|_e_iface' pair is
	                        {GL_MAX_NAME_LENGTH|GL_ATOMIC_COUNTER_BUFFER}; the such pair may lead to undefined behavior and process termination;
	GL_INVALID_VALUE     : '_prog_id' is not the identifier of an existing sync object;
	GL_INVALID_VALUE     : 'bufSize' is zero << ToDo: have to be clear what the 'buffer size' does mean in the context of this function;
	                        it looks like be related to glGetProgramResource();
	*/
	CBase::m_error << __METHOD__ << __s_ok;
#if (0)
	if (false == CInterface::Is_applicable((uint32_t)_e_iface)) {
		CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_e_iface' value (%u) is not applicable"), _e_iface);
		return CBase::Error();
	}
#endif
	pfn_Get p_fun = reinterpret_cast<pfn_Get>(CBase::Get(iface_fun_names[(uint32_t)e_iface_fun_ndx::e_get]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, (uint32_t)_e_iface, (uint32_t)_e_prop, (int32_t*)&_u_value);

	// not applicable pairs of the property value with the interface one are taking into account yet;
	switch (CErr_ex().Get_code()) {
	case GL_INVALID_ENUM : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: '_e_iface'{'%s' (%u)} is not applicable to '_e_prop'{'%s' (%u)}"), e_iface_to_str(_e_iface), _e_iface, e_prop_to_str(_e_prop), _e_prop); break;
	case GL_INVALID_OPERATION : {
			 CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u), '_e_iface' '%s' (%u), '_e_prop' '%s' (%u)"), _prog_id, e_iface_to_str(_e_iface), _e_iface, e_prop_to_str(_e_prop), _e_prop); break;
		} break;
	case GL_INVALID_VALUE : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' cannot be 0"));
			else if (false == __get_prog_procs().IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) refers to no program"), _prog_id);
			else CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: the mystical buffer size is %u;"), 0);
		} break;
	default:;
	}

	return CBase::Error();
}

err_code CInterface::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(iface_fun_names); i_++) {
		if (nullptr == CBase::Get(iface_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TIfaceProcs&  ::__get_iface_procs (void) {
	static TIfaceProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

const bool CProperty::Is_checked (const e_interface _e_iface, const ::std::vector<e_property>& _props, ::std::vector<e_property>& _error) {
	_e_iface; _props; _error;
	bool b_result = false;
	if (_props.empty())
		return b_result;

	if (_error.empty() == false)
	    _error.clear();

	try {
		for (uint32_t i_ = 0; i_ < static_cast<uint32_t>(_props.size()); i_++) {
			if (false == CInterface::Is_related(_e_iface, _props[i_]))
				_error.push_back(_props[i_]);
		}
	} catch(const ::std::bad_alloc&){}
	return b_result = _error.empty();
}

const ::std::vector<e_interface>& CProperty::Find (const e_property _e_prop) {
	_e_prop;
	static TProp_assoc assoc;
	if (assoc.empty()) { // one time to set the content;
		try {
			assoc.insert(::std::make_pair(e_prop::e_arr_size, ::std::vector<e_iface>{e_iface::e_buff_var, e_iface::e_prog_in, e_iface::e_prog_out}));
			assoc.insert(::std::make_pair(e_prop::e_name_len, ::std::vector<e_iface>{e_iface::e_buff_var, e_iface::e_prog_in, e_iface::e_prog_out}));
			assoc.insert(::std::make_pair(e_prop::e_type    , ::std::vector<e_iface>{e_iface::e_buff_var, e_iface::e_prog_in, e_iface::e_prog_out}));
		}
		catch (const ::std::bad_alloc&) {}
	}
	TProp_assoc::const_iterator found = assoc.find(_e_prop);
	if (assoc.end() == found) {
		static ::std::vector<e_interface> no_ifaces;
		return no_ifaces;
	}
	else
		return found->second;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz res_fun_names[] = { _T("glGetProgramResourceLocation"), _T("glGetProgramResourceiv"), _T("glGetProgramResourceName") };

enum class e_res_fun_ndx : uint32_t { e_get_loc = 0x0, e_get_values = 0x1, e_get_name = 0x2 };

CResource:: CResource (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

#define __gl_atom_counter   0x92C0 // GL_ATOMIC_COUNTER_BUFFER;
#define __gl_trans_feedback 0x8C8E // GL_TRANSFORM_FEEDBACK_BUFFER;

int32_t  CResource::GetLocate (const uint32_t _prog_id, const e_interface _e_iface, const char* _p_att_name) {
	_prog_id; _e_iface; _p_att_name;
	/* Possible error codes:
	*/
	CBase::m_error << __METHOD__ << __s_ok;
	int32_t n_result  = -1;

	return n_result;
}

err_code CResource::GetName (const uint32_t _prog_id, const e_interface _e_iface, const uint32_t _u_ndx, CString& _name) {
	_prog_id; _e_iface; _u_ndx; _name;
	/* Possible error codes:
	GL_INVALID_ENUM  : '_e_iface' is not one of the accepted interface types.
	GL_INVALID_ENUM  : '_e_iface' is GL_ATOMIC_COUNTER_BUFFER or GL_TRANSFORM_FEEDBACK_BUFFER,
	                   since active atomic counter and transform feedback buffer resources are not assigned name strings;
	GL_INVALID_VALUE : '_prog_id' is not the name of an existing program;
	GL_INVALID_VALUE : '_u_ndx' is greater than or equal to the number of entries in the active resource list for programInterface;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_GetName p_fun = reinterpret_cast<pfn_GetName>(CBase::Get(res_fun_names[(uint32_t)e_res_fun_ndx::e_get_name]));
	if (nullptr == p_fun)
		return CBase::Error();

	const uint32_t n_size = 64;
	char sz_buffer[n_size] = {0};

	uint32_t u_length = 0; // receives length of the resource; the terminate zero is included;

	p_fun(_prog_id, (uint32_t)_e_iface, _u_ndx, n_size, &u_length, sz_buffer);

	const uint32_t u_err_code = CErr_ex().Get_code();
	switch (u_err_code) {
	case GL_INVALID_ENUM  : {
			if (false) {}
			else if (false == CInterface::Is_acceptable((uint32_t)_e_iface)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: '_e_iface' (%u) is not accepted"), _e_iface);
			else if (__gl_atom_counter == (uint32_t)_e_iface || __gl_trans_feedback == (uint32_t)_e_iface)
			     CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_inv_enum: '_e_iface' (%u) is not named"), _e_iface);
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: err_code (%u)"), u_err_code);
		} break;
	case GL_INVALID_VALUE : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' cannot be 0"));
			else if (false == __get_prog_procs().IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) refers to no program"), _prog_id);
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: err_code (%u)"), u_err_code);
		} break;
	default:;
	}

	if (false == CBase::Error()) {
		_name = sz_buffer;
	}

	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramResource.xhtml ;
err_code CResource::GetValues (const uint32_t _prog_id, const e_interface _e_iface, const uint32_t _u_ndx, const TRawProps& _e_props, TRawValues& _result) {
	_prog_id; _e_iface; _u_ndx; _e_props; _result;
	/* Possible error codes:
	GL_INVALID_ENUM  : '_e_iface'is not one of the accepted interface types;
	                   *note*: this case is unavailable due to the input argument value is already set properly by enumeration;
	GL_INVALID_ENUM  : any value in '_e_prop' is not one of the accepted tokens for the interface '_e_iface';
	GL_INVALID_VALUE : '_prog_id' doesn't refer to existing program object;
	GL_INVALID_VALUE : '_e_prop' size is zero;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_GetRes p_fun = reinterpret_cast<pfn_GetRes>(CBase::Get(res_fun_names[(uint32_t)e_res_fun_ndx::e_get_values]));
	if (nullptr == p_fun)
		return CBase::Error();

	const uint32_t u_prop_count = static_cast<uint32_t>(_e_props.size());
	const uint32_t u_result_count = static_cast<uint32_t>(_result.size());
	uint32_t u_lenght = 0;

	p_fun(_prog_id, (uint32_t)_e_iface, _u_ndx, u_prop_count, (uint32_t*)_e_props.data(), u_result_count, &u_lenght, (int32_t*)_result.data());

	const uint32_t u_err_code = CErr_ex().Get_code();
	switch (u_err_code) {
	case GL_INVALID_ENUM  : {
			TRawProps v_error;
			if (false) {}
			else if (false == CProperty::Is_checked(_e_iface, _e_props, v_error)) {
			     CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_assoc: '_iface' %u('%s') refers to invalid props: %s"), _e_iface, e_iface_to_str(_e_iface), e_prop_set_to_str(v_error));}
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: '_e_iface' (%u) is not accepted"), _e_iface);
		} break;
	case GL_INVALID_VALUE : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' cannot be 0"));
			else if (false == __get_prog_procs().IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) refers to no program"), _prog_id);
			else if (0 == u_prop_count) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_e_props' set is empty"));
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: err_code (%u)"), u_err_code);
		} break;
	default:;
	}

	return CBase::Error();
}

err_code CResource::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(res_fun_names); i_++) {
		if (nullptr == CBase::Get(res_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TResProcs&  ::__get_res_procs (void) {
	static TResProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz prog_fun_names[] = {
	_T("glCreateProgram"), _T("glDeleteProgram"), _T("glGetProgramInfoLog"), _T("glGetProgramiv"),
	_T("glIsProgram"), _T("glUseProgram"), _T("glValidateProgram"),
};

enum class e_prog_fun_ndx : uint32_t {
	e_create = 0x0, e_delete = 0x1, e_info_log = 0x2, e_params = 0x3, e_is_prog = 0x4, e_use = 0x5, e_valid = 0x6,
};

CProg:: CProg (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

#define __gl_curr_prog  0x8B8D // GL_CURRENT_PROGRAM ;
#define __gl_lnk_status 0x8B82 // GL_LINK_STATUS ;

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
uint32_t CProg::Create (void){
	// the returned result value is zero (0) if an error occurs creating the program object ;
	// possibly the error code may be generic GL_OUT_OF_MEMORY ;
	CBase::m_error << __METHOD__ << __s_ok;

	static const uint32_t n_err_result = 0;

	uint32_t n_result = n_err_result;

	pfn_Create  p_fun = reinterpret_cast<pfn_Create>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_create]));
	if (nullptr == p_fun)
		return n_result;

	n_result = p_fun();

	if (0 == n_result) {
		switch (CErr_ex().Get_code()) {
		case GL_OUT_OF_MEMORY: CBase::m_error << __e_no_memory = _T("#__e_no_mem: generic error;"); break;
		default:
			CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = _T("#__e_inv_oper: a program cannot be created");
		}
	}
	return n_result;
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
err_code CProg::Delete (const uint32_t _prog_id){
	_prog_id;
	// GL_INVALID_VALUE : _prog_id is not a value generated by OpenGL ;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Delete p_fun = reinterpret_cast<pfn_Delete>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_delete]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is not valid;"), _prog_id);
	default:;
	}
	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
err_code CProg::InfoLog (const uint32_t _prog_id, const int32_t _buf_size, int32_t* _log_len, char* _p_log){
	_prog_id; _buf_size; _log_len; _p_log;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not an identifier of program object ;
		GL_INVALID_VALUE     : _buf_size is less than 0 ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_InfoLog p_fun = reinterpret_cast<pfn_InfoLog>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_info_log]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _buf_size, _log_len, _p_log);

	switch (CErr_ex().Get_code()) {
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
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsProgram.xhtml ;
bool     CProg::IsProg  (const uint32_t _prog_id) {
	_prog_id;
	// no error is thrown/generated by this function;
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_IsProg p_fun = reinterpret_cast<pfn_IsProg>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_is_prog]));
	if (nullptr == p_fun)
		return false;
	else
		return !!p_fun(_prog_id);
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
err_code CProg::Params  (const uint32_t _prog_id, const uint32_t _param_id, int32_t* _p_params){
	_prog_id; _param_id; _p_params;
	/* Possible errors:
		GL_INVALID_ENUM      : _param_id is not an accepted value ;
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not the identifier of a program object ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Params p_fun = reinterpret_cast<pfn_Params>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_params]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _param_id, _p_params);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_ENUM: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_enum: '_param_id' (%u) is not accepted;"), _param_id); break;
	case GL_INVALID_OPERATION: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program;"), _prog_id); break;
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id); break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
err_code CProg::Use (const uint32_t _prog_id){
	_prog_id;
	/* Possible errors:
		GL_INVALID_VALUE     : '_prog_id' is neither 0 nor a value generated by OpenGL ;
		GL_INVALID_OPERATION : '_prog_id' is not the identifier of a program object ;
		GL_INVALID_OPERATION : the program object of '_prog_id' could not be made part of current state ;
		GL_INVALID_OPERATION : transform feedback mode is active ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Use p_fun = reinterpret_cast<pfn_Use>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_use]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_VALUE: CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id); break;
	case GL_INVALID_OPERATION : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' cannot be 0"));
			else if (false == this->IsProg(_prog_id)) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program"), _prog_id);
			else CBase::m_error << (err_code) TErrCodes::eExecute::eOperate
				= TString().Format(_T("#__e_inv_oper: the program of '_prog_id' (%u) is out of current state or feedback mode is active"), _prog_id);
		} break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
err_code CProg::Validate (const uint32_t _prog_id){
	_prog_id;
	/* Possible errors:
		GL_INVALID_VALUE     : _prog_id is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : _prog_id is not the identifier of a program object ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Validate p_fun = reinterpret_cast<pfn_Validate>(CBase::Get(prog_fun_names[(uint32_t)e_prog_fun_ndx::e_valid]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) refers to no program;"), _prog_id); break;
	case GL_INVALID_VALUE : CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id); break;
	default:;
	}

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

TProgProcs& ::__get_prog_procs (void) {
	static TProgProcs procs;
	static bool b_loaded = false;
	// it is better to try to load all functions in cache at once and to indicate an error of loading if any occurs,
	// otherwise if the sequence of calls of open_gl draw pipeline procedures is not correct, the global error state will not allow to load procs later;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}

/////////////////////////////////////////////////////////////////////////////

static _pc_sz $_fun_names[] = { _T("glAttachShader"), _T("glDetachShader"), _T("glGetAttachedShaders") };
enum class  e_$_fun_ndx : uint32_t {
	e_attach = 0x0, e_detach = 0x1, e_attached = 0x2
};

CShaders:: CShaders (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
err_code CShaders::Attach (const uint32_t _prog_id, const uint32_t _shader_id) {
	_prog_id; _shader_id;
	/* Possible errors:
		GL_INVALID_VALUE : either '_prog_id' or '_shader_id' is not a value generated by OpenGL ;
		GL_INVALID_OPERATION : '_prog_id' is not an identifier of program object ;
		GL_INVALID_OPERATION : '_shader_id' is not an identifier of shader object ;
		GL_INVALID_OPERATION : the shader of '_shader_id' identifier is already attached to the program object of '_prog_id' ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Attach p_fun = reinterpret_cast<pfn_Attach>(CBase::Get($_fun_names[(uint32_t)e_$_fun_ndx::e_attach]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _shader_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION:
	case GL_INVALID_VALUE: {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id);
			else if (0 == _shader_id) CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_val: '_shader_id' (%u) is invalid;"), _shader_id);
			else if (0 != _prog_id) {
				if (static_cast<int32_t>(_prog_id) != CParam().GetInt(__gl_curr_prog)) // ToDo: this must be moved to CProg implementation, but not used here like this;
					CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) is invalid;"), _prog_id);
			}
			else if (0 != _shader_id) {
				CShader shader;
				if (false == shader.Is_valid(_shader_id))
					CBase::m_error = shader.Error();
				else
					CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_oper: '_shader_id' (%u) is attached;"), _shader_id);
			}
		} break;
	default:;
	}
	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttachedShaders.xhtml ;
// *important* the signed integer data types is changed to unsigned one intentionally;
err_code CShaders::Attached (const uint32_t _prog_id, const uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders) {
	_prog_id; _u_max_cnt; _p_count; _p_shaders;
	/* Possible error coders:
		GL_INVALID_VALUE     : '_prog_id' is not a value generated by OpenGL;
		GL_INVALID_OPERATION : '_prog_id' is not a program object;
		GL_INVALID_VALUE     : '_u_max_cnt' is less than 0 (zero); actually it is not possible taking into account the changed data type to unsigned one;
	*/
	CBase::m_error << __METHOD__ << __s_ok;
	if (nullptr == _p_count) return CBase::m_error <<__e_pointer = _T("'_p_count' is nullptr");
	if (nullptr == _p_shaders) return CBase::m_error <<__e_pointer = _T("'_p_shaders' is nullptr");

	pfn_Attached p_fun = reinterpret_cast<pfn_Attached>(CBase::Get($_fun_names[(uint32_t)e_$_fun_ndx::e_attach]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _u_max_cnt, _p_count, _p_shaders);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION:
	case GL_INVALID_VALUE: {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id);
			else if (0 == _u_max_cnt) CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_val: '_u_max_cnt' (%u) is invalid;"), _u_max_cnt); // ToDo: not sure that this is correct regarding the 0 value;
			else if (0 != _prog_id) {
				if (static_cast<int32_t>(_prog_id) != CParam().GetInt(__gl_curr_prog)) // ToDo: this must be moved to CProg implementation, but not used here like this;
					CBase::m_error <<__e_inv_arg << TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) is invalid;"), _prog_id);
			}
		} break;
	default:;
	}

	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
err_code CShaders::Detach (const uint32_t _prog_id, const uint32_t _shader_id) {
	_prog_id; _shader_id;
	/* Possible error codes:
	GL_INVALID_VALUE     : either '_prog_id' or '_shader_id' is a value that was not generated by OpenGL;
	GL_INVALID_OPERATION : '_prog_id' does not refer to a program object';
	GL_INVALID_OPERATION : '_shader_id' does not refer to a shader object;
	GL_INVALID_OPERATION : a shader object of '_shader_id' is not attached to a program of '_prog_id';
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Detach p_fun = reinterpret_cast<pfn_Detach>(CBase::Get($_fun_names[(uint32_t)e_$_fun_ndx::e_detach]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_prog_id, _shader_id);

	switch (CErr_ex().Get_code()) {
	case GL_INVALID_OPERATION :
	case GL_INVALID_VALUE : {
			if (false) {}
			else if (0 == _prog_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_prog_id' (%u) is invalid;"), _prog_id);
			else if (0 == _shader_id) CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: '_shader_id' (%u) is invalid;"), _shader_id);
			else if (0 != _prog_id) {
				if (static_cast<int32_t>(_prog_id) != CParam().GetInt(__gl_curr_prog))
					CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_prog_id' (%u) is invalid;"), _prog_id);
			}
			else if (0 != _shader_id) {
				CShader shader;
				if (false == shader.Is_valid(_shader_id))
					CBase::m_error = shader.Error();
				else
					CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: '_shader_id' (%u) is attached;"), _shader_id);
			}
			else {
				CBase::m_error <<(err_code)TErrCodes::eExecute::eOperate = TString().Format(_T("#__e_inv_oper: '_shader_id' (%u) is not attached to '_prog_id' (%u);"), _shader_id, _prog_id);
			}
		} break;
	default:;
	}
	return CBase::Error();
}

err_code CShaders::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof($_fun_names); i_++) {
		if (nullptr == CBase::Get($_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TProgShaders& ::__get_$_bind_procs (void) {
	static TProgShaders procs;
	static bool b_loaded = false;
	// it is better to try to load all functions in cache at once and to indicate an error of loading if any occurs,
	// otherwise if the sequence of calls of open_gl draw pipeline procedures is not correct, the global error state will not allow to load procs later;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s\n;"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}