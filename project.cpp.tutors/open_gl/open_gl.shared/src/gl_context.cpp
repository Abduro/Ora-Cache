/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface implementation file;
*/
#include "gl_context.h"
#include "gl_procs_ctx.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {


}}}}

using namespace ex_ui::draw::open_gl::_impl;

#pragma region cls::CGraphics{}

using namespace ex_ui::draw::open_gl::format;

CGraphics:: CGraphics (void) : TBase() { TBase::m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("__e_not_inited: graphics context is not created"); }
CGraphics::~CGraphics (void) {}

err_code CGraphics::Create (void) {
	TBase::m_error <<__METHOD__<< __s_ok;

	if (false == TBase::Target().Is_valid()) {
		__trace_err_ex_2(TBase::m_error << (err_code)TErrCodes::eExecute::eState = _T("Target window handle is not set"));
		return TBase::Error();
	}

	return this->Create(TBase::Target().Get());
}

err_code CGraphics::Create (const HDC _hdc) {
	_hdc;
	TBase::m_error <<__METHOD__<< __s_ok;
	if (false == CDevice::Is_DC(_hdc)) {
		__trace_err_ex_2(TBase::m_error <<__e_inv_arg = _T("#__e_inv_arg: input device context is not valid")); return TBase::Error();
	}
	// (0) it is supposed the target window is already set to the base class, no check for that at this point;
	// (1) gets the current available version of OpenGL;

	if (::Get_version().Is_base()) { // OpenGL version 1.1 is available only;
		
		// it is assumed the required pixcel format descriptor is already set to device context;
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;

		this->m_drw_ctx = ::wglCreateContext(_hdc);
		if (0 == this->m_drw_ctx) {
			TBase::m_error.Last();
			__trace_err_ex_2(TBase::Error());
		}
		return TBase::Error();
	}
	else {}

	CFormat the_best_fmt; the_best_fmt << _hdc;

	if (__failed(the_best_fmt.Find({32, 24, 8, 8}))) {
		__trace_err_ex_2(TBase::m_error = the_best_fmt.Error()); return TBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(_hdc, the_best_fmt.Index(), &the_best_fmt.Get())) {
		TBase::m_error.Last();
		__trace_err_ex_2(TBase::Error()); return TBase::Error();
	}
	const s_version& pref_vers = ::Get_CtxPers().Prefer();
	CAtt_set_ctx ctx_atts(pref_vers.m_major, pref_vers.m_minor);

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	this->m_drw_ctx = __get_ctx_procs().CreateCtxAttsArb(_hdc, 0, ctx_atts.IAtt_Get_Int_Ptr());
	if (nullptr == this->m_drw_ctx) {
		return TBase::m_error .Last(); // the excerpt: Extended error information can be obtained with GetLastError().
	}

	if (0 == ::wglMakeCurrent(_hdc, this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		TBase::m_error.Last();
		__trace_err_ex_2(CBase::Error());
	}

	return TBase::Error();
}

#pragma endregion