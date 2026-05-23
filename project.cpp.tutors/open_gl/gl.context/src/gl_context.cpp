/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface implementation file;
*/
#include "gl_context.h"
#include "gl_procs_ctx.h"
#include "gl_procs_ext.h"

#include "gl_px_format_att.h"
#include "gl_version.h"

using namespace open_gl;

namespace open_gl { namespace _impl { }} using namespace open_gl::_impl;

static _pc_sz p_err_not_inited = _T("__e_not_inited: graphics context is not created");
static _pc_sz p_err_wnd_not_set = _T("Surface window handle is not set");
static _pc_sz p_err_dc_invalid = _T("#__e_inv_arg: input device context is invalid");

namespace open_gl { namespace context {
namespace ver_1_1 {

#pragma region cls::CGraphics{}

using namespace win_api::format;

CGraphics:: CGraphics (void) : TBase() { TBase::m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_not_inited; }
CGraphics::~CGraphics (void) {}

_pc_sz   CGraphics::Class (void) {
	static CString cs_cls;
	if (cs_cls.IsEmpty()) cs_cls = __CLASS__;
	return (_pc_sz) cs_cls;
}

err_code CGraphics::Create (void) {
	TBase::m_error <<__METHOD__<< __s_ok;

	if (false == TBase::Surface().Is_valid()) {
		__trace_err_ex_2(TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_err_wnd_not_set);
		return TBase::Error();
	}

	return this->Create(TBase::Surface().Get());
}

err_code CGraphics::Create (const HDC _hdc) {
	_hdc;
	TBase::m_error <<__METHOD__<< __s_ok;
	if (false == CDevice::Is_DC(_hdc)) {
		__trace_err_ex_2(TBase::m_error <<__e_inv_arg = p_err_dc_invalid); return TBase::Error();
	}
	// it is supposed the surface window is already set to the base class, no check for that at this point;

	CPxFormat the_best_fmt; the_best_fmt << _hdc;

	// and the required pixcel format descriptor is already set to device context;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	if (__failed(the_best_fmt.Find({32, 24, 8, 8}))) {
		__trace_err_ex_2(TBase::m_error = the_best_fmt.Error()); return TBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(_hdc, the_best_fmt.Index(), &the_best_fmt.Get())) {
		TBase::m_error.Last();
		__trace_err_ex_2(TBase::Error()); return TBase::Error();
	}

	TBase::m_drw_ctx = ::wglCreateContext(_hdc);
	if (0 == TBase::m_drw_ctx) {
		TBase::m_error.Last();
		__trace_err_ex_2(TBase::Error());
	}
	return TBase::Error();
}

err_code CGraphics::MakeCurrent (const bool _yes_or_no) {
	_yes_or_no;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == TBase::Surface().Is_valid()) return TBase::m_error = TBase::Surface().Error();
	if (false == TBase::Is_valid()) return TBase::m_error <<(err_code)TErrCodes::eExecute::eState = _T("rendering context is not created");

	if (0 == ::wglMakeCurrent(TBase::Surface().Get(), _yes_or_no ? TBase::Renderer() : 0)) {
		TBase::m_error.Last();
		__trace_err_ex_2(CBase::Error());
	}
	
	return TBase::Error();
}

#pragma endregion
}
namespace arb {

CGraphics:: CGraphics (void) : TBase() { TBase::m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_not_inited; }
CGraphics::~CGraphics (void) {}

err_code CGraphics::Create (void) {
	TBase::m_error <<__METHOD__<< __s_ok;

	if (false == TBase::Surface().Is_valid()) {
		__trace_err_ex_2(TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_err_wnd_not_set);
		return TBase::Error();
	}

	return this->Create(TBase::Surface().Get());
}

err_code CGraphics::Create (const HDC _hdc) {
	_hdc;
	TBase::m_error <<__METHOD__<< __s_ok;

	const bool b_arb_support = ::Get_ProcExt().Is_arb();
	if (false == b_arb_support) {
		return TBase::m_error <<(err_code) TErrCodes::eExecute::eFunction = _T("#__e_oper: ARB extension is not supported");
	}

	if (false == CDevice::Is_DC(_hdc)) {
		__trace_err_ex_2(TBase::m_error <<__e_inv_arg = p_err_dc_invalid); return TBase::Error();
	}
	// it is supposed the surface window is already set to the base class, no check for that at this point;

	CPxFormat the_best_fmt; the_best_fmt << _hdc;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	if (__failed(the_best_fmt.Find({32, 24, 8, 8}))) {
		__trace_err_ex_2(TBase::m_error = the_best_fmt.Error()); return TBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(_hdc, the_best_fmt.Index(), &the_best_fmt.Get())) {
		TBase::m_error.Last();
		__trace_err_ex_2(TBase::Error()); return TBase::Error();
	}

#if (1)
	::open_gl::arb::format::CAtt_set_ctx ctx_atts(::Get_version().Major(), ::Get_version().Minor());

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	TBase::m_drw_ctx = __get_ctx_procs().CreateCtxAttsArb(_hdc, 0, ctx_atts.IAtt_Get_Int_Ptr());
	if (nullptr == TBase::m_drw_ctx) {
		return TBase::m_error .Last(); // the excerpt: Extended error information can be obtained with GetLastError().
	}
#endif
	if (0 == ::wglMakeCurrent(_hdc, TBase::m_drw_ctx)) { // it is required, otherwise nothing will work;
		TBase::m_error.Last();
		__trace_err_ex_2(CBase::Error());
	}

	return TBase::Error();
}

}}}