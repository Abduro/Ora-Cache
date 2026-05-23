/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 21:33:22.637, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' base draw context interface implementation file;
*/
#include "gl_ctx_base.h"
#include "gl_ctx_device.h"

using namespace open_gl::context;

namespace open_gl { namespace context { namespace _impl {

	class CHelper {
	public:
		CHelper (void) = default; CHelper (const CHelper&) = delete; CHelper (CHelper&&) = delete; ~CHelper (void) = default;

		static err_code Is_valid (const HWND _hwnd, CError& _error) {
			_hwnd; _error;
			if (nullptr == _hwnd || false == !!::IsWindow(_hwnd)) {
				_error << __e_hwnd = _T("Surface window handle is invalid");
				__trace_err_ex_2(_error);
			}
			return _error;
		}

	private:
		CHelper& operator = (const CHelper&) = delete; CHelper& operator = (CHelper&&) = delete;
	};

}}} using namespace open_gl::context::_impl;

#pragma region cls::CSurface{}

static _pc_sz p_err_not_inited = _T("#__e_state: target not inited");

CSurface:: CSurface (void) :  m_dc_src(0), m_surface(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_not_inited; }
CSurface:: CSurface (const HWND _h_wnd) : CSurface() { *this << _h_wnd; }
CSurface::~CSurface (void) {
	this->Free ();
}

err_code CSurface::Free (void) {

	// https://stackoverflow.com/questions/3945721/win32-why-does-releasedc-say-my-dc-is-not-found ; good answer is >>
	// https://stackoverflow.com/a/3948202/4325555 ; the excerpt : ...Lots of OpenGl samples do rather (to my mind) weired things with device contexts... ;
	
	if (this->Is_valid() == false) {
		this->m_dc_src = nullptr; // for cases when handle of the device context has invalid state, i.e. is closed outside of this class instance;
		return this->Error();     // returns possibly the error state that is set by this::Is_valid();
	}

	this->m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-releasedc ;
	const int n_result = ::ReleaseDC(this->m_surface, this->m_dc_src);
	if (1 != n_result) {
		__trace_err_ex_2(this->m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_state: releasing source device context failed"));
	}
	else
		this->m_dc_src = nullptr;

	return this->Error();
}

TError& CSurface::Error (void) const { return this->m_error; }

bool CSurface::Is_valid (void) const {

	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	if (__failed(CHelper::Is_valid(this->m_surface, this->m_error)))
		return false;
#endif
	if (nullptr == this->m_dc_src) {
		this->m_error << __e_not_inited = p_err_not_inited;  // the error object set to error state (i.e. error == true);
		return false;
	}
	
	if (false == CDevice::Is_DC(this->m_dc_src)) // not sure that the source device context may be an in-memory one, but anyway it is okay;
		this->m_error << __e_inv_arg = _T("#__e_inv_arg: source device context handle is not valid");

	return false == this->Error().Is(); // returns 'true' due to the error state is not set to err_code, i.e. everything is '__s_ok';
}

const HDC CSurface::Get (void) const { return this->m_dc_src; }
err_code  CSurface::Set (const HWND _h_wnd) {
	_h_wnd;

	if (this->Is_valid()) {
		this->m_error << (err_code) TErrCodes::eObject::eInited = _T("#__e_state: source device context is already set");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
#if (0)
	if (!!this->m_surface) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Surface window is not destroyed yet");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
#endif
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(CHelper::Is_valid(/*this->m_surface*/_h_wnd, this->m_error))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
	// for debug purpose only;
	if (this->m_cls_src.IsEmpty()) {
		bool b_break = false;
		b_break = !b_break;
	}

	this->m_surface = _h_wnd;
	this->m_dc_src = ::GetDC(_h_wnd);
//	__empty_ln(); // https://www.allacronyms.com/handle/abbreviated ;
	__trace_info_3(
		_T("#ctx_dev : {handle=%s;src=%s}\n"), TString()._addr_of(this->m_dc_src), TString().Format(_T("%s"), this->m_cls_src.IsEmpty() ? _T("#unset") : (_pc_sz)this->Source())
	);

	return this->Error();
}

_pc_sz CSurface::Source (void) const { return (_pc_sz) this->m_cls_src; }
bool   CSurface::Source (_pc_sz _p_cls_name) {
	_p_cls_name;
	CString cs_cls(_p_cls_name); cs_cls.Trim();

	const bool b_changed = 0 != this->m_cls_src.CompareNoCase(cs_cls);
	if (b_changed)
		this->m_cls_src = cs_cls;

	return b_changed;
}

CString&  CSurface::Source (void) { return this->m_cls_src; }

CSurface& CSurface::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid() && __failed(this->Free())) { // releasing the source device context handle is failed;
		return *this; 
	}
	this->Set(_h_wnd); return *this; // for getting the result of retreiving the device context the error state should be checked;
}

CSurface::operator const HWND (void) const { return this->m_surface; }

#pragma endregion
#pragma region cls::CBase{}

static _pc_sz p_err_base_not_init = _T("context base is not inited yet");

CBase:: CBase (void) : m_drw_ctx(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_base_not_init; }
CBase::~CBase (void) { this->Destroy(); }

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// (1) destroys the renderer handle first;
	if (nullptr != this->m_drw_ctx) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(this->Surface().Get(), 0)) {
			__trace_err_3(_T("%s\n"), (_pc_sz) (this->m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wgldeletecontext ;
		if (0 == ::wglDeleteContext(this->m_drw_ctx)) {
			__trace_err_3(_T("%s\n"), (_pc_sz) (this->m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		else
			this->m_drw_ctx = nullptr;
	}
	// (2) destroys device context handle; https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-releasedc ;
	if (__failed(this->Surface().Free()))
		this->m_error  = this->Surface().Error();

	if (false == this->Error()) {
		__trace_info_2(_T("Unbinding renderer ctx and releasing GDI ctx succeeded;\n"));
	}

	return this->Error();
}

TError& CBase::Error (void) const { return this->m_error; }

bool   CBase::Is_valid (void) const {
	return !!this->m_drw_ctx;
}

HGLRC  CBase::Renderer (void) const {
	return this->m_drw_ctx;
}

err_code CBase::Set (const HWND _h_target) {
	_h_target;

	if (this->Is_valid()) {
		this->m_error  << (err_code) TErrCodes::eObject::eInited = _T("Draw renderer exists");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}

	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Surface().Set(_h_target))) {
		return this->m_error  = this->Surface().Error();
	}

	return this->Error();
}

const
CSurface& CBase::Surface (void) const { return this->m_surface; }
CSurface& CBase::Surface (void)       { return this->m_surface; }    

CBase& CBase::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid())
		this->Destroy();
	if (this->Error()) // the destruction is failed;
		return *this;
	this->Set(_h_wnd); return *this;
}

#pragma endregion