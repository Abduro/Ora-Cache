/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 21:19:58.639, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer memory accessor interface implementation file;
*/
#include "gl_procs_buf.mem.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::buffer;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace _impl {
#if (0)
	class CMem_alloca {
	public:
		CMem_alloca (void) = default; CMem_alloca (const CMem_alloca&) = delete; CMem_alloca (CMem_alloca&&) = delete; ~CMem_alloca (void) = default;

		static err_code Alloc (const e_bnd_tgts e_target, TRawData& _data, CError& _err) {
			e_target; _data; _err;
			if (__failed(CMem_alloca::Data_Prepare(_data, _err))) return _err;

			const uint32_t u_size = CData_Accessor::Get_Size(e_target, _err);
			if (_err)
				return _err;
			if (0 == u_size)
				return _err << (err_code) TErrCodes::eData::eInvalid = _T("Required memory size is zero (0)");

			if (__failed(_data.Create(u_size)))
				_err = _data.Error();
			return _err;
		}

	private:
		CMem_alloca& operator = (const CMem_alloca&) = delete; CMem_alloca& operator = (CMem_alloca&&) = delete;

		static err_code Data_Prepare (TRawData& _data, CError& _err) {
			_data; _err; if (_data.IsValid()) if (__failed(_data.Free())) _err = _data.Error();
			return _err;
		}
	};
#endif
}}}}}

#pragma region cls::CData_Accessor{}

static _pc_sz dat_acc_fun_names[] = {
	_T("glMapBuffer"), _T("glMapNamedBuffer"), _T("glMapBufferRange"), _T("glMapNamedBufferRange"), _T("glUnmapBuffer"), _T("glUnmapNamedBuffer")
};

enum class e_dat_acc_fun_ndx : uint32_t {
	e_map_bound = 0x0, e_map_named, e_range, e_range_named, e_unmap_bound, e_unmap_named
};

CData_Accessor::CData_Accessor (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code CData_Accessor::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(dat_acc_fun_names); i_++) {
		if (nullptr == CBase::Get(dat_acc_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glMapBuffer.xhtml ;
err_code CData_Accessor::Get_Ptr (const e_bnd_tgts e_target, const e_data_access e_access, TRawData& _data) {
	e_target; e_access; _data;
	/* Possible errors:
	GL_INVALID_ENUM  : 'e_target' is not one of the buffer binding acceptable targets;
	GL_INVALID_ENUM  : 'e_access' is not GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE; taking into account the input enumeration, such error cannot occur;
	GL_INVALID_OPERATION : default buffer (id == 0) is bound to target;
	GL_INVALID_OPERATION : the buffer object is in a mapped state;
	GL_OUT_OF_MEMORY : the GL is unable to map the buffer object's data store; virtual memory is also used;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (_data.IsValid())
		if (__failed(_data.Free()))
			return CBase::m_error = _data.Error();

	const uint32_t u_size = CData_Accessor::Get_Size(e_target, CBase::m_error);
	if (CBase::Error())
		return CBase::Error();

	pfn_Map p_fun = reinterpret_cast<pfn_Map>(CBase::Get(dat_acc_fun_names[(uint32_t)e_dat_acc_fun_ndx::e_map_bound]));
	if (nullptr == p_fun)
		return CBase::Error();

	void* p_data = p_fun(static_cast<const uint32_t>(e_target), static_cast<const uint32_t>(e_access));

	const
	uint32_t u_err_code = CErr_ex().Get_code(); 
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_e_target' (0x%04x) is not accepted"), e_target); break;
	case GL_OUT_OF_MEMORY : CBase::m_error << __e_no_memory = TString().Format(_T("#__e_no_mem: memory of size %u (bytes) cannot be allocated"), u_size); break;
	case GL_INVALID_OPERATION : {
		if (0 == TBufferProcs::Get_bound(e_target, CBase::m_error)) CBase::m_error <<__e_inv_arg = _T("#__e_oper: the default buffer (id = 0) is bound;");
		else if (CData_Accessor::Is_mapped(e_target, CBase::m_error)) {
			CBase::m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_oper: the target buffer is mapped;");
		}
	} break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}
	// makes data copy;
	if (false == CBase::Error() && nullptr != p_data) {
		if (u_size)
			if (__failed(_data.Create((const shared::memory::byte*)p_data, u_size)))
				CBase::m_error = _data.Error();
	}

	return CBase::Error();
}

err_code CData_Accessor::Get_Ptr (const uint32_t _u_buf_id, const e_data_access e_access, TRawData& _data) {
	_u_buf_id; e_access; _data;
	/* Possible errors:
	GL_INVALID_ENUM  : 'e_access' is not GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE; taking into account the input enumeration, such error cannot occur;
	GL_INVALID_OPERATION : '_u_buf_id' does not refer to the buffer object;
	GL_INVALID_OPERATION : the buffer object is in a mapped state;
	GL_OUT_OF_MEMORY : the GL is unable to map the buffer object's data store; virtual memory is also used;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (_data.IsValid())
		if (__failed(_data.Free()))
			return CBase::m_error = _data.Error();

	const uint32_t u_size = CData_Accessor::Get_Size(_u_buf_id, CBase::m_error);
	if (CBase::Error())
		return CBase::Error();

	pfn_Map_nm p_fun = reinterpret_cast<pfn_Map_nm>(CBase::Get(dat_acc_fun_names[(uint32_t)e_dat_acc_fun_ndx::e_map_named]));
	if (nullptr == p_fun)
		return CBase::Error();

	void* p_data = p_fun(_u_buf_id, static_cast<const uint32_t>(e_access));
	const
	uint32_t u_err_code = CErr_ex().Get_code(); 
	switch ( u_err_code ) {
	case GL_OUT_OF_MEMORY : CBase::m_error << __e_no_memory = TString().Format(_T("#__e_no_mem: memory of size %u (bytes) cannot be allocated"), u_size); break;
	case GL_INVALID_OPERATION : 
		if (false == ::__get_buf_procs().Is_Buffer(_u_buf_id)) {
			if (::__get_buf_procs().Error())
				CBase::m_error = ::__get_buf_procs().Error();
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: buffer id = 0x%02x is invalid"), _u_buf_id); break;
		}
		else if (CData_Accessor::Is_mapped(_u_buf_id, CBase::m_error)) {
			CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_oper: the buffer (id = 0x%02x) is already mapped;"), _u_buf_id); break;
		} // error code is unknown at this point, just keeping go to the 'default' section;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}

	// makes data copy;
	if (false == CBase::Error() && nullptr != p_data) {
		if (u_size)
			if (__failed(_data.Create((const shared::memory::byte*)p_data, u_size)))
				CBase::m_error = _data.Error();
	}

	return CBase::Error();
}

uint32_t CData_Accessor::Get_Size (const e_bind_targets e_target, CError& _err) {
	e_target; _err;
	uint32_t u_size = 0;
	if (__failed(::__get_buf_prop_procs().Get(e_target, e_buf_params::e_size, u_size))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return u_size;
}

uint32_t CData_Accessor::Get_Size (const uint32_t _u_buf_id, CError& _err) {
	_u_buf_id; _err;
	uint32_t u_size = 0;
	if (__failed(::__get_buf_prop_procs().Get(_u_buf_id, e_buf_params::e_size, u_size))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return u_size;
}

bool CData_Accessor::Is_mapped (const e_bind_targets e_target, CError& _err) {
	e_target; _err;
	uint32_t u_mapped = 0;
	if (__failed(::__get_buf_prop_procs().Get(e_target, e_buf_params::e_mapped, u_mapped))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return !!u_mapped;
}

bool CData_Accessor::Is_mapped (const uint32_t u_buf_id, CError& _err) {
	u_buf_id; _err;
	uint32_t u_mapped = 0;
	if (__failed(::__get_buf_prop_procs().Get(u_buf_id, e_buf_params::e_mapped, u_mapped))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return !!u_mapped;
}

err_code CData_Accessor::Unmap (const e_bnd_tgts e_target) {
	e_target;
	/* Possible errors:
	GL_INVALID_ENUM      : 'e_target' is not one of the buffer binding targets;
	GL_INVALID_OPERATION : default buffer of zero identifier is bound to target;
	GL_INVALID_OPERATION : the buffer object is not in a mapped state;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Unmap p_fun = reinterpret_cast<pfn_Unmap>(CBase::Get(dat_acc_fun_names[(uint32_t)e_dat_acc_fun_ndx::e_unmap_bound]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(static_cast<uint32_t>(e_target));
	const
	uint32_t u_err_code = CErr_ex().Get_code(); 
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: bound target (id = 0x%04x) is not acceptable"), e_target); break;
	case GL_INVALID_OPERATION :
		if (0 == TBufferProcs::Get_bound(e_target, CBase::m_error)) CBase::m_error <<__e_inv_arg = _T("#__e_oper: the default buffer (id = 0) is bound;");
		else if (false == CData_Accessor::Is_mapped(e_target, CBase::m_error)) {
			CBase::m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_oper: the target buffer is *not* mapped;");
		}
		break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}

	return CBase::Error();
}

err_code CData_Accessor::Unmap (const uint32_t _u_buf_id) {
	_u_buf_id;
	/* Possible errors:
	GL_INVALID_ENUM      : '_u_buf_id' is not one of the buffer binding targets;
	GL_INVALID_OPERATION : default buffer of zero identifier is bound to target;
	GL_INVALID_OPERATION : the buffer object is not in a mapped state;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Unmap_nm p_fun = reinterpret_cast<pfn_Unmap_nm>(CBase::Get(dat_acc_fun_names[(uint32_t)e_dat_acc_fun_ndx::e_unmap_named]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_buf_id);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_enum: '_u_buf_id' (0x%02x) is invalid"), _u_buf_id); break;
	case GL_INVALID_OPERATION :
		if (false == ::__get_buf_procs().Is_Buffer(_u_buf_id)) {
			if (::__get_buf_procs().Error())
				CBase::m_error = ::__get_buf_procs().Error();
			else CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_oper: buffer id = 0x%02x is invalid"), _u_buf_id); break;
		}
		else if (CData_Accessor::Is_mapped(_u_buf_id, CBase::m_error) == false) {
			CBase::m_error << (err_code) TErrCodes::eExecute::eState = TString().Format(_T("#__e_oper: the buffer (id = 0x%02x) is not mapped;"), _u_buf_id); break;
		}
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%u)"), u_err_code, u_err_code);
	}

	return CBase::Error();
}

TBufAccessor&  __get_buf_acc_procs (void) {
	static TBufAccessor procs;
	static bool b_loaded = false;

	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
			b_loaded = true;
	}
	return procs;
}

#pragma endregion