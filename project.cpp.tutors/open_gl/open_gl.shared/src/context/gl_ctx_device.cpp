/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Apr-2026 at 22:22:42.306, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' graphics device interface (GDI) and device context (DC) wrappers' interface implementation file;
*/
#include "gl_ctx_device.h"

using namespace ex_ui::draw::open_gl::context;
using CFormat = ex_ui::draw::open_gl::CFormat;

#pragma region cls::CMode{}

CMode:: CMode (void) : m_value(e_mode::e__undef), m_hdc(nullptr) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CMode:: CMode (const HDC& _h_dc) : CMode() { *this << _h_dc; }
CMode::~CMode (void) {}

uint32_t  CMode::Current (void) const { return this->m_value; }
TError&   CMode::Error (void) const { return this->m_error; }

// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getgraphicsmode ;
uint32_t  CMode::Get (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	
	if (false == CDevice::Is_DC(this->m_hdc)) {
		this->m_value = e_mode::e__undef;
		this->m_error << (err_code) TErrCodes::eObject::eHandle = _T("The device handle is invalid");
	}
	else {
		this->m_value = ::GetGraphicsMode(this->m_hdc);
		if (e_mode::e__undef == this->m_value)
			this->m_error.Last();
	}

	return this->m_value;
}

// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setgraphicsmode ;
err_code CMode::Set (const e_mode _e_value) {
	_e_value;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == CDevice::Is_DC(this->m_hdc)) {
		this->m_value = e_mode::e__undef;
		this->m_error << (err_code) TErrCodes::eObject::eHandle = _T("The device handle is invalid");
	}
	else if (e_mode::e__undef == ::SetGraphicsMode(this->m_hdc, _e_value)) {
		this->m_error.Last();
	}
	else {
		this->m_value = _e_value;
		__trace_impt_3(_T("The device mode of handle = %s is set to '%s';\n"), TString()._addr_of(this->m_hdc, _T("0x%08x")), (_pc_sz) CMode::To_str(_e_value));
	}
	return this->Error();
}

CString CMode::To_str (void) const {  return CMode::To_str(this->m_value); }
CString CMode::To_str (const uint32_t _u_mode) {
	_u_mode;
	CString cs_out;
	switch (_u_mode) {
	case e_mode::e_advanced  : cs_out = _T("advanced"); break;
	case e_mode::e_compatible: cs_out = _T("compatible"); break;
	default: cs_out = _T("#undef");
	}

	return cs_out;
}

bool CMode::IsAdvanced (void) const { return this->m_value == e_mode::e_advanced; }
bool CMode::Is_valid (void) const { return this->m_value != e_mode::e__undef; }

CMode&  CMode::operator << (const HDC& _h_dc) { this->m_hdc = _h_dc; return *this; }
CMode&  CMode::operator << (const e_mode _e_mode) { this->m_value = _e_mode; return *this; }
const
CMode&  CMode::operator >> (uint32_t& _n_out) const { _n_out = this->Current(); return *this; }

#pragma endregion
#pragma region cls::CDevice{}

CDevice:: CDevice (void) : CBase() { CBase::m_error <<__CLASS__; }

CDevice:: CDevice (const HWND _h_target) : CDevice() { *this << _h_target; }

CDevice::~CDevice (void) { this->Destroy(); }
#if (0)
err_code CDevice::Create (void) {

	class CFakeWnd : public ::ATL::CWindowImpl<CFakeWnd> { typedef ::ATL::CWindowImpl<CFakeWnd> TBase;
	public:
		DECLARE_WND_CLASS_EX(_T("open_gl::fake::CWnd"), CS_DBLCLKS | CS_OWNDC, COLOR_ACTIVECAPTION);
		DECLARE_EMPTY_MSG_MAP();

		HWND Create (void) { TBase::Create(HWND_MESSAGE); return TBase::Detach(); }
	};

	CBase::m_error  <<__METHOD__<<__s_ok;

	const HWND h_fake = CFakeWnd().Create();
	if (0 == h_fake) {
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error (CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	if (__succeeded(this->Create(h_fake))) {
		CBase::Target().Is_managed(true);
	}
	else
		::DestroyWindow(h_fake);

	return CBase::Error();
}
#endif

_pc_sz   CDevice::Class (void) {
	static CString cs_cls;
	if (cs_cls.IsEmpty()) cs_cls = __CLASS__;
	return (_pc_sz) cs_cls;
}

err_code CDevice::Create (const HWND _h_target) {
	_h_target;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (CBase::Target().Is_valid())
		return CBase::m_error = CBase::Target().Error();

	if (CBase::Target().Source().IsEmpty()) // the source class name can be set outside of this procedure;
		CBase::Target().Source(TString().Format(_T("%s::%s()"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__));

	if (__failed(CBase::Set(_h_target))) {
		return CBase::Error();
	}
	
	this->Mode() << CBase::Target().Get();
	if (__failed(this->Mode().Set(CMode::e_mode::e_advanced)))
		return this->m_error  = this->Mode().Error();
#if (0) // this approach provides limited description of the pixel format descriptor, in other words, the found descriptor is not the best one;
	px_fmt_desc_t px_fmt_desc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) << there is the example of how to do that;
	px_fmt_desc.nSize      = sizeof(px_fmt_desc_t);
	px_fmt_desc.nVersion   = 1;
	px_fmt_desc.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	px_fmt_desc.iPixelType = PFD_TYPE_RGBA;
	px_fmt_desc.cColorBits = 32; // colordepth of the framebuffer;
	px_fmt_desc.cAlphaBits = 8;  // the number of bits for the stencilbuffer;
	px_fmt_desc.cDepthBits = 24; // the number of bits for the depthbuffer;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat ;
	int32_t n_px_format = ::ChoosePixelFormat(CBase::Target().Get(), &px_fmt_desc);
	if (0== n_px_format) {
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(CBase::Target().Get(), n_px_format, &px_fmt_desc)) {
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}
#else
	CFormat the_best_fmt; the_best_fmt << CBase::Target().Get(); uint32_t u_found_ndx = 0;
	if (__failed(the_best_fmt.Find({32, 24, 8}, u_found_ndx))) {
		__trace_err_ex_2(CBase::m_error = the_best_fmt.Error()); return CBase::Error();
	}
	else
		this->Format() = the_best_fmt; // takes a copy of the found descriptor;

	if (false == !!::SetPixelFormat(CBase::Target().Get(), u_found_ndx, &the_best_fmt.Get())) {
		CBase::m_error.Last();
		__trace_err_ex_2(CBase::Error()); return CBase::Error();
	}
#endif
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_drw_ctx = ::wglCreateContext(CBase::Target().Get());
	if ( 0 == this->m_drw_ctx) {
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	if (0 == ::wglMakeCurrent(CBase::Target().Get(), this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error(CError::e_cmds::e_get_last)).Print(TError::e_req));
	}

	if (false == CBase::Error()) {
		__trace_impt_3(_T("%s\n"), _T("*result*: success;"));
	}
	return CBase::Error();
}

bool CDevice::Is_DC (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type || OBJ_DC == d_type);
}

bool CDevice::Is_DC_mem (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type/* || OBJ_DC == d_type*/);
}

const
CMode& CDevice::Mode (void) const { return this->m_mode; }
CMode& CDevice::Mode (void)       { return this->m_mode; }
const
CFormat& CDevice::Format (void) const { return this->m_format; }
CFormat& CDevice::Format (void)       { return this->m_format; }

CDevice& CDevice::operator <<(const HWND _h_target) {
	_h_target;
	this->Create(_h_target);
	return *this; // for getting the result of creation the error state should be checked;
}

CDevice::operator const HDC (void) const { return CBase::Target().Get(); }

#pragma endregion
#pragma region cls::CFake_Ctx{}

using CFake_Ctx = ex_ui::draw::open_gl::CFake_Ctx;

CFake_Ctx:: CFake_Ctx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: fake device context is not created"); this->Create(); }
CFake_Ctx::~CFake_Ctx (void) { this->Destroy(); }

err_code CFake_Ctx::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_fk_wnd.Is_valid() == false) {
		::__trace_err_ex_2(this->m_error = this->m_fk_wnd.Error()); return this->Error();
	}
	if (__failed(this->m_device.Create(m_fk_wnd.m_hWnd))) {
		__trace_err_ex_2(this->m_error = this->m_device.Error());
	}
	return this->Error();
}

err_code CFake_Ctx::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_device.Is_valid())
		if (__failed(this->m_device.Destroy()))
			__trace_err_ex_2(this->m_error = this->m_device.Error());

	return this->Error();
}

TError&  CFake_Ctx::Error (void) const { return this->m_error; }

const
CDevice& CFake_Ctx::operator ()(void) const { return this->m_device; }

#pragma endregion
#pragma region cls::CSelector{}

CSelector:: CSelector (void) : m_renderer(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CSelector::~CSelector (void) { if (this->Is_used()) this->Unset(); }
CSelector:: CSelector (const HDC& _to_set) : CSelector() { this->Set(_to_set); }

TError&  CSelector::Error (void) const { return this->m_error; }

bool  CSelector::Is_used  (void) const { return nullptr != this->m_renderer; }

err_code CSelector::Set (const HDC _h_dc) {
	_h_dc;
	this->m_error << __METHOD__<<__s_ok;

	if (this->Is_used())
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: selector is already applied");

	if (false == CDevice::Is_DC(_h_dc))
		return this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input device context is invalid");

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_renderer = ::wglCreateContext(_h_dc);
	if ( 0 == this->m_renderer) {
		return this->m_error(CError::e_cmds::e_get_last)/* = _T("#__e_exec: draw context creation is failed")*/;
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
	if (0 == ::wglMakeCurrent(_h_dc, this->m_renderer)) {
		return this->m_error(CError::e_cmds::e_get_last) = _T("#__e_exec: making draw context current is failed");
	}

	return this->Error();
}

err_code CSelector::Unset (void) {
	this->m_error << __METHOD__<<__s_ok;
	if (0 == this->m_renderer)
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: the current context is not set");

	if (0 == ::wglMakeCurrent(0, 0)) {
		this->m_error(CError::e_cmds::e_get_last) = _T("#__e_exec: resetting current context is failed");
		__trace_err_ex_2(this->Error());
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wgldeletecontext ;
	if (0 == ::wglDeleteContext(this->m_renderer)) {
		this->m_error.Last();
		__trace_err_ex_2(this->Error());
	}
	this->m_renderer = 0; // sets to 0 anyway;

	return this->Error();
}

#pragma endregion