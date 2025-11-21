/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Nov-2025 at 09:22:38.084, (UTC+4) Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw surface class interface implementation file;
*/
#include "gl_procs_surface.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

namespace ex_ui { namespace draw { namespace open_gl { namespace procs { namespace _impl {

	uint32_t _get_unk_flag_value (const uint32_t _value) {
		_value;
		using e_clear_ops = CEraser::e_clear_ops;
		uint32_t u_unk = _value;
		
		if (!!u_unk) u_unk &= ~e_clear_ops::e_color;
		if (!!u_unk) u_unk &= ~e_clear_ops::e_depth;
		if (!!u_unk) u_unk &= ~e_clear_ops::e_stencil;

		return u_unk;
	}

}}}}}
using namespace _impl;

static _pc_sz erase_fun_names[] = {
	_T("glClear"), _T("glClearColor"), _T("glClearDepthf"), _T("glClearStencil")
};

enum class e_erase_fun_ndx : uint32_t {
	e_all = 0x0, e_clr = 0x1, e_depth = 0x2, e_stencil = 0x3
};

CEraser:: CEraser (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClear.xml ;
err_code CEraser::All (const uint32_t _u_mask) {
	_u_mask;
	/* Possible error code(s):
	GL_INVALID_VALUE : '_u_mask' contains a bit that is not pre-defined one;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfnAll p_fun = reinterpret_cast<pfnAll>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_all]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_mask);

	const uint32_t u_result = CErr_ex().Get_code();

	switch(u_result) {
	case GL_INVALID_VALUE : {
		const uint32_t u_unk = _get_unk_flag_value(_u_mask);
		CBase::m_error << __e_inv_arg = TString().Format(_T("#__e_inv_val: '_u_mask' has unknown flag value (%u)"), u_unk); } break;
	default:;
	}

	return CBase::Error();
}
// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glClearColor.xml ;
// https://learn.microsoft.com/en-us/windows/win32/opengl/glclearcolor ;
err_code CEraser::Clr (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnClr p_fun = reinterpret_cast<pfnClr>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_clr]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_r, _g, _b, _a);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code) {
		CString cs_rgba; cs_rgba.Format(_T("rgba:{%s|%s|%s|%s}"),
			TString().Float(_r, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_g, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_b, t_fmt_spec::e_decimal, _T("%.2f")),
			TString().Float(_a, t_fmt_spec::e_decimal, _T("%.2f"))
		);
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; clr = %s"), u_err_code, (_pc_sz) cs_rgba);
	}
	return CBase::Error();
}

err_code CEraser::Depth (const float _f_z) {
	_f_z;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnDepth p_fun = reinterpret_cast<pfnDepth>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_depth]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_f_z);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code)
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; z_value = %s"), u_err_code, TString().Float(_f_z));

	return CBase::Error();
}

err_code CEraser::Stencil (const uint32_t _u_bits) {
	_u_bits;
	CBase::m_error << __METHOD__ << __s_ok;

	pfnStencil p_fun = reinterpret_cast<pfnStencil>(CBase::Get(erase_fun_names[(uint32_t)e_erase_fun_ndx::e_stencil]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_u_bits);

	const uint32_t u_err_code = CErr_ex().Get_code();

	if (!!u_err_code)
		CBase::m_error << (err_code) TErrCodes::eExecute::eInternal = TString().Format(_T("__e_int: err_code = %u; '_u_bits' = %u"), u_err_code, _u_bits);

	return CBase::Error();
}

err_code CEraser::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(erase_fun_names); i_++) {
		if (nullptr == CBase::Get(erase_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TEraserProcs&  ::__get_eraser_procs (void) {
	static TEraserProcs procs;
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

static _pc_sz render_fun_names[] = {
	_T("glDrawArrays")
};

enum class e_render_fun_ndx : uint32_t {
	e_arrays = 0x0
};

CRenderer:: CRenderer (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}