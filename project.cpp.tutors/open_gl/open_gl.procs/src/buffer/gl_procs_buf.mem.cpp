/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 21:19:58.639, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer memory accessor interface implementation file;
*/
#include "gl_procs_buf.mem.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::buffer;

#pragma region cls::CData_Accessor{}

static _pc_sz dat_acc_fun_names[] = {
	_T("glMapBuffer"), _T("glMapNamedBuffer")
};

enum class e_dat_acc_fun_ndx : uint32_t {
	e_map_bound = 0x0, e_map_named,
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

uint32_t CData_Accessor::Get_Size (const e_bind_targets _e_target, CError& _err) {
	_e_target; _err;
	uint32_t u_size = 0;
	if (__failed(::__get_buf_prop_procs().Get(_e_target, e_buf_params::e_size, u_size))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return u_size;
}

uint32_t CData_Accessor::Get_Size_nm (const uint32_t _u_buf_id, CError& _err) {
	_u_buf_id; _err;
	uint32_t u_size = 0;
	if (__failed(::__get_buf_prop_procs().Get_nm(_u_buf_id, e_buf_params::e_size, u_size))) {
		_err = ::__get_buf_prop_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) _err.Print(TError::e_print::e_req));
	}
	return u_size;
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