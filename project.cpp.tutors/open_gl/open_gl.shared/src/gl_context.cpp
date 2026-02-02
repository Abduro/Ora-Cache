/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface implementation file;
*/
#include "gl_context.h"
#include "gl_procs_ctx.h"
#include "shared.preproc.h"
#include "shared.dbg.h"
#include "sys.registry.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

}}}}

using namespace ex_ui::draw::open_gl::_impl;

#pragma region cls::context::CBase{}

context::CBase:: CBase (void) : m_drw_ctx(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
context::CBase::~CBase (void) { this->Destroy(); }

err_code context::CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// (1) destroys the renderer handle first;
	if (nullptr != this->m_drw_ctx) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(this->Target().Get(), 0)) {
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
	if (__failed(this->Target().Free()))
		this->m_error  = this->Target().Error();

	if (false == this->Error()) {
		__trace_info_2(_T("Unbinding renderer ctx and releasing GDI ctx succeeded;\n"));
	}

	return this->Error();
}

TError& context::CBase::Error (void) const { return this->m_error; }

bool   context::CBase::Is_valid (void) const {
	return !!this->m_drw_ctx;
}

HGLRC  context::CBase::Renderer (void) const {
	return this->m_drw_ctx;
}

err_code context::CBase::Set (const HWND _h_target) {
	_h_target;

	if (this->Is_valid()) {
		this->m_error  << (err_code) TErrCodes::eObject::eInited = _T("Draw renderer exists");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}

	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Target().Set(_h_target))) {
		return this->m_error  = this->Target().Error();
	}

	return this->Error();
}

const
CTarget& context::CBase::Target (void) const { return this->m_target; }
CTarget& context::CBase::Target (void)       { return this->m_target; }    

CBase& context::CBase::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid())
		this->Destroy();
	if (this->Error()) // the destruction is failed;
		return *this;
	this->Set(_h_wnd); return *this;
}

#pragma endregion
#pragma region cls::context::CTarget{}

context::CTarget:: CTarget (void) :  m_dc_src(0), m_target(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
context::CTarget:: CTarget (const HWND _h_wnd) : CTarget() { *this << _h_wnd; }
context::CTarget::~CTarget (void) {
	this->Free ();
}

err_code context::CTarget::Free (void) {
	// https://stackoverflow.com/questions/3945721/win32-why-does-releasedc-say-my-dc-is-not-found ; good answer is >>
	// https://stackoverflow.com/a/3948202/4325555 ; the excerpt : ...Lots of OpenGl samples do rather (to my mind) weired things with device contexts... ;
	
	if (this->Is_valid() == false) {
		this->m_dc_src = nullptr; // for cases when handle of the device context has invalid state, i.e. is closed outside of this class instance;
		return this->Error();    // returns possibly the error state that is set by this::Is_valid();
	}

	this->m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-releasedc ;
	const int n_result = ::ReleaseDC(this->m_target, this->m_dc_src);
	if (1 != n_result) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Releasing source device context failed");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req));
	}
	else
		this->m_dc_src = nullptr;

	return this->Error();
}

TError& context::CTarget::Error (void) const { return this->m_error; }

bool context::CTarget::Is_valid (void) const {

	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == this->m_dc_src) {
		this->m_error << __e_not_inited;  // the error object set to error state (i.e. error == true);
		return false;
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobjecttype ;
	const uint32_t u_dc_type = ::GetObjectType(this->m_dc_src);

	if (OBJ_DC != u_dc_type && OBJ_MEMDC != u_dc_type) // not sure that the source device context may be an in-memory one, but anyway it is okay;
		return false != (this->m_error << __e_inv_arg = _T("Source device context is not valid")).Is();

	return false == this->Error().Is(); // returns 'true' due to the error state is not set to err_code, i.e. everything is '__s_ok';
}

const HDC context::CTarget::Get (void) const { return this->m_dc_src; }
err_code  context::CTarget::Set (const HWND _h_wnd) {
	_h_wnd;

	if (this->Is_valid()) {
		this->m_error << (err_code) TErrCodes::eObject::eInited = _T("Source device context is already set");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
#if (0)
	if (!!this->m_target) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Target window is not destroyed yet");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
#endif
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_wnd || false == !!::IsWindow(_h_wnd)) {
		this->m_error << __e_hwnd = _T("Target window handle is invalid");
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}
	// for debug purpose only;
	if (this->m_cls_src.IsEmpty()) {
		bool b_break = false;
		b_break = !b_break;
	}

	this->m_target = _h_wnd;
	this->m_dc_src = ::GetDC(_h_wnd);
//	__empty_ln(); // https://www.allacronyms.com/handle/abbreviated ;
	__trace_info_3(
		_T("#ctx_dev : {handle=%s;src=%s}\n"), TString()._addr_of(this->m_dc_src), TString().Format(_T("%s"), this->m_cls_src.IsEmpty() ? _T("#unset") : this->Source())
	);

	return this->Error();
}

_pc_sz context::CTarget::Source (void) const { return (_pc_sz) this->m_cls_src; }
bool   context::CTarget::Source (_pc_sz _p_cls_name) {
	_p_cls_name;
	CString cs_cls(_p_cls_name); cs_cls.Trim();

	const bool b_changed = 0 != this->m_cls_src.CompareNoCase(cs_cls);
	if (b_changed)
		this->m_cls_src = cs_cls;

	return b_changed;
}

context::CTarget&  context::CTarget::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid() && __failed(this->Free())) { // releasing the source device context handle is failed;
		return *this; 
	}
	this->Set(_h_wnd); return *this; // for getting the result of retreiving the device context the error state should be checked;
}

context::CTarget::operator const HWND (void) const { return this->m_target; }

#pragma endregion
#pragma region cls::context::CDevice::CMode{}

context::CDevice::CMode:: CMode (void) : m_value(e_mode::e__undef), m_hdc(nullptr) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
context::CDevice::CMode:: CMode (const HDC& _h_dc) : CMode() { *this << _h_dc; }
context::CDevice::CMode::~CMode (void) {}

uint32_t  context::CDevice::CMode::Current (void) const { return this->m_value; }
TError&   context::CDevice::CMode::Error (void) const { return this->m_error; }

// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getgraphicsmode ;
uint32_t  context::CDevice::CMode::Get (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	
	if (false == context::CDevice::Is_DC(this->m_hdc)) {
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
err_code context::CDevice::CMode::Set (const e_mode _e_value) {
	_e_value;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == context::CDevice::Is_DC(this->m_hdc)) {
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

CString context::CDevice::CMode::To_str (void) const {  return CMode::To_str(this->m_value); }
CString context::CDevice::CMode::To_str (const uint32_t _u_mode) {
	_u_mode;
	CString cs_out;
	switch (_u_mode) {
	case e_mode::e_advanced  : cs_out = _T("advanced"); break;
	case e_mode::e_compatible: cs_out = _T("compatible"); break;
	default: cs_out = _T("#undef");
	}

	return cs_out;
}

bool context::CDevice::CMode::IsAdvanced (void) const { return this->m_value == e_mode::e_advanced; }
bool context::CDevice::CMode::Is_valid (void) const { return this->m_value != e_mode::e__undef; }

context::CDevice::CMode&  context::CDevice::CMode::operator << (const HDC& _h_dc) { this->m_hdc = _h_dc; return *this; }
context::CDevice::CMode&  context::CDevice::CMode::operator << (const e_mode _e_mode) { this->m_value = _e_mode; return *this; }
const
context::CDevice::CMode&  context::CDevice::CMode::operator >> (uint32_t& _n_out) const { _n_out = this->Current(); return *this; }

#pragma endregion
#pragma region cls::context::CDevice{}

context::CDevice:: CDevice (void) : CBase() { CBase::m_error <<__CLASS__; }

context::CDevice:: CDevice (const HWND _h_target) : CDevice() { *this << _h_target; }

context::CDevice::~CDevice (void) { this->Destroy(); }
#if (0)
err_code context::CDevice::Create (void) {

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
err_code context::CDevice::Create (const HWND _h_target) {
	_h_target;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (nullptr == CBase::Target().Source()) // the source class name can be set outside of this procedure;
		CBase::Target().Source(TString().Format(_T("%s::%s()"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__));

	if (__failed(CBase::Set(_h_target))) {
		return CBase::Error();
	}
	
	this->Mode() << CBase::Target().Get();
	if (__failed(this->Mode().Set(CMode::e_mode::e_advanced)))
		return this->m_error  = this->Mode().Error();

	PIXELFORMATDESCRIPTOR px_fmt_desc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) << there is the example of how to do that;
	px_fmt_desc.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
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

bool context::CDevice::Is_DC (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type || OBJ_DC == d_type);
}

bool context::CDevice::Is_DC_mem (const HDC _hdc) {
	_hdc;
	if (nullptr == _hdc) return false;
	const dword d_type = ::GetObjectType(_hdc); return (OBJ_MEMDC == d_type/* || OBJ_DC == d_type*/);
}

const
context::CDevice::CMode& context::CDevice::Mode (void) const { return this->m_mode; }
context::CDevice::CMode& context::CDevice::Mode (void)       { return this->m_mode; }

CDevice& context::CDevice::operator <<(const HWND _h_target) {
	_h_target;
	this->Create(_h_target);
	return *this; // for getting the result of creation the error state should be checked;
}

#pragma endregion
#pragma region cls::CGraphics{}

#include "shared.wnd.fake.h"
#include "gl_format.h"

using CFakeWnd = ex_ui::popup::CMsgWnd;
using namespace ex_ui::draw::open_gl::format;

CGraphics:: CGraphics (void) : TBase() { TBase::m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CGraphics::~CGraphics (void) {}

err_code   CGraphics::Create (const uint32_t _u_gl_major_ver, const uint32_t _u_gl_minor_ver) {
	_u_gl_major_ver; _u_gl_minor_ver;
	TBase::m_error <<__METHOD__<< __s_ok;

	if (false == TBase::Target().Is_valid()) {
		TBase::m_error << (err_code)TErrCodes::eExecute::eState = _T("Target window handle is not set");
		__trace_err_2(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_print::e_req));
		return TBase::Error();
	}

	// (4.b) chooses the pixel format;
	CAtt_set_pixels pxl_atts; // no error check for this time yet;

	uint32_t n_count = 0;
	int32_t p_formats = 0;

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ; this file contains the function description;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ; << there is the example of how to use the function;

	const int32_t n_result = __get_ctx_procs().ChoosePxFormatArb(
		TBase::Target().Get(), pxl_atts.IAtt_Get_Int_Ptr(), nullptr, 1, &p_formats, &n_count
	);

	bool b_can_go_ahead = false;

	if (0 == n_result) { // the failure has occurred: the format cannot be chosen for creating the context;
		if (__get_ctx_procs().Error()) { // checks for failure of loading the function pointer;
			__get_ctx_procs().Error().Show();
			TBase::m_error  = __get_ctx_procs().Error();
		}
		else { // otherwise checks the OpenGL error that has been thrown; to-do: expect to do not work, it requires a re-view of this code block;
			TBase::m_error.Last();
			TBase::m_error.Show();
		}
	}
	else if (nullptr != &p_formats && true == !!n_count) { b_can_go_ahead = true; }
	else { b_can_go_ahead = true; }

	if (false == b_can_go_ahead)
		return TBase::Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-describepixelformat ;
	PIXELFORMATDESCRIPTOR pfd = {0};
	if (0 == ::DescribePixelFormat(TBase::Target().Get(), p_formats, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
		return TBase::m_error .Last();
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false ==!!::SetPixelFormat(TBase::Target().Get(), p_formats, &pfd))
		return TBase::m_error .Last();

	CAtt_set_ctx ctx_atts(_u_gl_major_ver, _u_gl_minor_ver);
	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	this->m_drw_ctx = __get_ctx_procs().CreateCtxAttsArb(TBase::Target().Get(), 0, ctx_atts.IAtt_Get_Int_Ptr());
	if (nullptr == this->m_drw_ctx) {
		return TBase::m_error .Last(); // the excerpt: Extended error information can be obtained with GetLastError().
	}

	if (0 == ::wglMakeCurrent(CBase::Target().Get(), this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s\n"), (_pc_sz) (CBase::m_error (CError::e_cmds::e_get_last)).Print(TError::e_req));
	}

	if (false == CBase::Error()) {
		__trace_impt_3(_T("%s\n"), _T("*result*: success;"));
	}

	return TBase::Error();
}

using CRegVer  = shared::sys_core::storage::route::CCtx::CVersion;
using CVersion = CGraphics::CVersion;

const
CVersion& CGraphics::Version (void) const { return this->m_ver; }

#pragma endregion
#pragma region cls::CVersion

CVersion::CVersion (void) : m_major(0), m_minor (0), m_use_core(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; this->Load(); }

TError&   CVersion::Error (void) const { return this->m_error; }

uint32_t  CVersion::Major (void) const { return this->m_major; }
uint32_t  CVersion::Minor (void) const { return this->m_minor; }

bool   CVersion::Use_core (void) const { return this->m_use_core; }

err_code  CVersion::Load  (void) {
	this->m_error <<__METHOD__<<__s_ok;
	const CRegVer& ver = ::Get_reg_router().Ctx().Version();

	TRegKeyEx reg_key;
	this->m_major = reg_key.Value().GetDword(ver.Root(), (_pc_sz) ver.Name(CRegVer::e_major)); if (reg_key.Error()) __trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	this->m_minor = reg_key.Value().GetDword(ver.Root(), (_pc_sz) ver.Name(CRegVer::e_minor)); if (reg_key.Error()) __trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));

	this->m_use_core = !!reg_key.Value().GetDword(ver.Root(), (_pc_sz) ver.Name(CRegVer::e_core));
	if (reg_key.Error()) __trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));

	return this->Error();
}

#pragma endregion