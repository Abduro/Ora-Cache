/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 03:01:10.215, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' camera window interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to OpenGL tutorials' camera project on 27-Nov-2025 at 00:42:54.941, UTC+4, Batumi, Thursday;
*/
#include "open_gl_tutor.3.wnd.h"
#include "open_gl_tutor.3.res.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::camera;

namespace ex_ui { namespace draw { namespace open_gl { namespace camera {

camera::CWnd:: CWnd (void) : TBase() { CString cs_cls = TString().Format(_T("camera::%s"),(_pc_sz)__CLASS__); TBase::m_error >> cs_cls;

	if (this->m_fak_wnd.Is_valid() == false) {
		TBase::m_error = m_fak_wnd.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
		__trace::Out_2(__trace::e_err, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}

	context::CDevice& dev_ref = this->Renderer().Scene().Ctx().Device();
	dev_ref.Target().Source((_pc_sz)cs_cls);

	if (__failed(dev_ref.Create(m_fak_wnd.m_hWnd))) {
		TBase::m_error = dev_ref.Error();
		__trace_err_3(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}
#if (0)
	if (__failed(__get_$_procs().Get_all())) {
		TBase::m_error = __get_$_procs().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}
#endif
}
camera::CWnd::~CWnd (void) { // parent class object will destroy window created automatically on its (parent) destruction;
	if (this->Renderer().Scene().Ctx().Device().Is_valid())
	    this->Renderer().Scene().Ctx().Device().Destroy();
}

err_code camera::CWnd::Create (const HWND _h_parent, const t_rect& _rc_wnd_pos, const bool _b_visible) {
	_h_parent; _rc_wnd_pos; _b_visible;
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	static _pc_sz p_cls_name = _T("__open_gl_shader_wnd");

	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(p_cls_name))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}

	TBase::Styles().Default_for_kid();

	if (__failed(TBase::Create(
		p_cls_name, TString().Format(_T("cls::[%s:%s]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), _rc_wnd_pos, _b_visible, _h_parent
	))) {
		return TBase::Error();
	}/* else if (__failed(TBase::Ctx().Create(*this, 4, 6))) {
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Ctx().Error()().Print(TError::e_req));
	}*/
	this->IMsg_OnMessage (WM_SIZE, 0, 0); // just sends the messege identifier, the handler takes all required steps itself;

	return TBase::Error();
}
err_code camera::CWnd::PostCreate (void) {
	TBase::m_error << __METHOD__ << __s_ok;

	// at the first step the opengl draw renderer must be created;
	// it is supposed the regular device context for getting opengl function loading is already created for fake window in the constructor of this class;

	CString cs_cls = TString().Format(_T("camera::%s"),(_pc_sz)__CLASS__); // stupid approach and must be reviewed;
	this->Renderer().Scene().Ctx().Draw().Target().Source((_pc_sz)cs_cls);
	this->Renderer().Scene().Ctx().Draw().Target() << *this;
	if (__failed(this->Renderer().Scene().Ctx().Draw().Create(4, 6))) { // ToDo: the version numbers (major & minor) must be set from version query not hardcoded;
		this->m_error = this->Renderer().Scene().Ctx().Draw().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->m_error.Print(TError::e_print::e_req));
	}
#if (0)
	// the fake window and its device handle can not be destroyed at this time; because not all opengl functions are loaded yet;
	context::CDevice& dev_ref = this->Renderer().Scene().Ctx().Device();
	if (__failed(dev_ref.Destroy())) {
		this->m_error = dev_ref.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->m_error.Print(TError::e_print::e_req));
	}
#endif

#if (0)
	// for better debugging and in order do not re-compile the executable, this section is disabled;
	// sets resource identifiers for loading shaders' source code;
	if (__failed(this->Renderer().Scene().Prog().Shaders().Fragment().Src().Cfg().ResId(IDS_TUTOR_2_SHADER_FRAG_0, e_res_types::e_string)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) this->Renderer().Scene().Prog().Shaders().Fragment().Src().Cfg().Error().Print(TError::e_print::e_req));
	if (__failed(this->Renderer().Scene().Prog().Shaders().Vertex().Src().Cfg().ResId(IDS_TUTOR_2_SHADER_VERT_0, e_res_types::e_string)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) this->Renderer().Scene().Prog().Shaders().Vertex().Src().Cfg().Error().Print(TError::e_print::e_req));
#else
	// sets the option of the camera source configuration to use external camera source files;
	CProgram& prog = this->Renderer().Scene().Prog();
	if (__failed(prog.Shaders().Fragment().Src().Cfg().Path($Type::e_fragment)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Fragment().Src().Cfg().Error().Print(TError::e_print::e_req));
	if (__failed(prog.Shaders().Vertex().Src().Cfg().Path($Type::e_vertex)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) prog.Shaders().Vertex().Src().Cfg().Error().Print(TError::e_print::e_req));
#endif
	
#if (0) // the scene preparation cannot be called at this point, because there is no vertex array is defined, the shape must be set first;
	if (__failed(this->Renderer().Scene().Prepare()))
		return TBase::m_error = this->Renderer().Scene().Error();
#endif
	if (__failed(this->Renderer().View().Grid().Create()))
	    __trace_err_2(_T("%s\n"), (_pc_sz) this->Renderer().View().Grid().Error().Print(TError::e_print::e_req));

	this->Renderer().Is_allowed(true);     // allows the draw opereation of the renderer;

#define _test_case_lvl -1
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	this->Renderer().Scene().Destroy();
#endif
	return TBase::Error();
}

err_code camera::CWnd::Destroy (void) {
	this->Renderer().Is_allowed(false);     // stops draw operation of the renderer;
	if (__failed(this->Renderer().View().Grid().Destroy()))
	    __trace_err_2(_T("%s\n"), (_pc_sz) this->Renderer().View().Grid().Error().Print(TError::e_print::e_req));
	this->Renderer().Scene().Destroy();     // the error output to the trace is made by the method being called;
	this->Renderer().Scene().Ctx().Clear(); // it is required to release the GDI objects being retrieved per each window handle;
	return __s_ok;
}

err_code camera::CWnd::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	switch (_u_code) {
	// this message is very important for required cleaning up of the draw pipeline components, the result is kept as unhandled;
	case WM_DESTROY: {
		this->Destroy();
		__trace_warn_3(_T("The window handle = %s is being destroyed;\n"), TString()._addr_of(this->Handle(), _T("0x%08x"))); 
		} break;
	case WM_PAINT  : { // https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint ; returned result: 0 - handled; otherwise not handled;
#if (0)
			PAINTSTRUCT ps = {0};
			const HDC h_dc = ::BeginPaint(TBase::Handle(), &ps);
			::FillRect(h_dc, &ps.rcPaint, (HBRUSH) (COLOR_ACTIVEBORDER + 1));
			::EndPaint(TBase::Handle(), &ps);
#endif
			if (__failed(this->Renderer().Draw()))
				__trace_err_3(_T("%s;\n"), (_pc_sz) this->Renderer().Error().Print(TError::e_req));

			return 0; // in any case, this message is considered as handled one;
		} break;
	case WM_SIZE   :
	case WM_SIZING :
		t_rect rect = {0};
		if (::GetClientRect((*this)(), &rect))  { // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
			this->Renderer().View() << rect;
		}
		else {
			TBase::m_error.Last();
			__trace_err_3(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
		} break;
	}
	return TBase::IMsg_OnMessage(_u_code, _w_param, _l_param);
}

const
CRenderer&  camera::CWnd::Renderer (void) const { return this->m_renderer; }
CRenderer&  camera::CWnd::Renderer (void)       { return this->m_renderer; }

}}}}