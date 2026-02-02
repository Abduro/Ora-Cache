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

#include "gl_renderer.h"
#include "gl_scene.h"
#include "gl_shader.h"
#include "shader\gl_compiler.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::camera;

camera::CWnd:: CWnd (void) : TBase() { CString cs_cls = TString().Format(_T("camera::%s"),(_pc_sz)__CLASS__); TBase::m_error >> cs_cls;

	if (this->m_fak_wnd.Is_valid() == false) {
		TBase::m_error = m_fak_wnd.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
		__trace::Out_2(__trace::e_err, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _T("%s\n"), (_pc_sz)TBase::m_error.Print(TError::e_req));
	}

	context::CDevice& dev_ref = ::Get_renderer().Scene().Ctx().Device();
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
	if (::Get_renderer().Scene().Ctx().Device().Is_valid())
	    ::Get_renderer().Scene().Ctx().Device().Destroy();
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

	// creates the context menu and subscribes to mouse use events;
	if (false){}
	else if (__failed(this->m_ctx_mnu.Load(IDR_TUTOR_3_CTX_MENU_0))) {
		TBase::m_error = this->m_ctx_mnu.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
	}
	else if (__failed(::Get_mouse() << this)) {
		TBase::m_error = ::Get_mouse().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
	}

	return TBase::Error();
}

err_code camera::CWnd::Destroy (void) {
	// unsubscribes from mouse use events and destroys shortcut/context menu;
	if (__failed(::Get_mouse() >> this)) {
		TBase::m_error = ::Get_mouse().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
	}
	if (__failed(this->m_ctx_mnu.Destroy())) {
		TBase::m_error = this->m_ctx_mnu.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
	}

	TRenderer& renderer = ::Get_renderer();

	renderer.Is_allowed(false);     // stops draw operation of the renderer;
	if (__failed(renderer.View().Grid().Destroy()))
	    __trace_err_2(_T("%s\n"), (_pc_sz) renderer.View().Grid().Error().Print(TError::e_print::e_req));
	renderer.Scene().Destroy();     // the error output to the trace is made by the method being called;
	renderer.Scene().Ctx().Clear(); // it is required to release the GDI objects being retrieved per each window handle;
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
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-fillrect ;
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush ;
		class CBrush {
		public:
			 CBrush (const rgb_color _clr) : m_brush(nullptr) { this->m_brush = ::CreateSolidBrush(_clr); }
			~CBrush (void) { if (this->m_brush){ ::DeleteObject(this->m_brush); this->m_brush = nullptr; }}
			HBRUSH  Get (void) const { return this->m_brush; }
		private:
			HBRUSH m_brush;
		};

		// https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint ; returned result: 0 - handled; otherwise not handled;
		PAINTSTRUCT ps = {0};
		const HDC h_dc = ::BeginPaint(TBase::Handle(), &ps);
		::FillRect(h_dc, &ps.rcPaint, CBrush(::Get_theme().Border()).Get());
		::EndPaint(TBase::Handle(), &ps);
#els (true == false) // if this is able then something goes wrong way: binding of required object(s) is dropped out and triangle goes away;
		::Get_renderer().Is_allowed(true);
		if (__failed(::Get_renderer().Graphics()))
			__trace_err_3(_T("%s;\n"), (_pc_sz) ::Get_renderer().Error().Print(TError::e_req));
#endif
			return 0; // in any case, this message is considered as handled one;
		} break;
	case WM_SIZE   :
	case WM_SIZING :
		t_rect rect = {0};
		if (::GetClientRect((*this)(), &rect)) { // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
			::Get_renderer().View() << rect;     // at this point the open_gl components/wrappers are not ready yet, thus only storing the rect of the view is possible;
		}
		else {
			TBase::m_error.Last();
			__trace_err_3(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_req));
		} break;
	}
	return TBase::IMsg_OnMessage(_u_code, _w_param, _l_param);
}

TError&  camera::CWnd::IMouse_Error (void) const { return TBase::m_error; }
err_code camera::CWnd::IMouse_OnEvent (const CEvent& _evt) {
	_evt;
	TBase::m_error <<__METHOD__<<__s_false;

	__trace_info(_T("%s\n"), (_pc_sz)_evt.To_str());
	// the shortcut menu appears on releasing/unpressing the right mouse button;
	if (_evt.Action() != e_action::e_released) return TBase::Error();
	if (_evt.Button() != e_button::e_right) return TBase::Error();

	const uint32_t u_cmd_id = this->m_ctx_mnu.Track(*this, _evt.Coords().Get());
	__trace_info(_T("selected cmd_id: %u;\n"), u_cmd_id);

	TRenderer& renderer = ::Get_renderer();
	CViewPort& viewport = renderer.View();
	view::CGrid& grid = viewport.Grid();

	switch (u_cmd_id) {
	case IDR_TUTOR_3_GRD_CELL_H_025 : grid.Cell().H(025); break; case IDR_TUTOR_3_GRD_CELL_H_050 : grid.Cell().H(050); break;
	case IDR_TUTOR_3_GRD_CELL_H_075 : grid.Cell().H(075); break; case IDR_TUTOR_3_GRD_CELL_H_100 : grid.Cell().H(100); break;
	case IDR_TUTOR_3_GRD_CELL_W_025 : grid.Cell().W(025); break; case IDR_TUTOR_3_GRD_CELL_W_050 : grid.Cell().W(050); break;
	case IDR_TUTOR_3_GRD_CELL_W_075 : grid.Cell().W(075); break; case IDR_TUTOR_3_GRD_CELL_W_100 : grid.Cell().W(100); break;
	default:
		return this->Error();
	}

	if (__failed(grid.Update(viewport.Get()))) { // re-calculates the grid lines' layout;
		return TBase::m_error = grid.Error();
	}
	
	renderer.Is_allowed(true);
	if (__failed(renderer.Draw()))
		TBase::m_error = renderer.Error();
	renderer.Is_allowed(false);

	return TBase::Error();
}


err_code camera::CWnd::PostCreate (void) {
	TBase::m_error << __METHOD__ << __s_ok;

	shader::CCompiler cmpl;
	if (false == cmpl.Is_supported()) {
		 __trace_err_2(_T("%s\n"), (_pc_sz) cmpl.Error().Print(TError::e_print::e_req));
		return this->m_error = cmpl.Error();
	}
	else
		__trace_warn_2(_T("%s\n"), _T("Shader compiler is supported;"));

	// at the first step the opengl draw renderer must be created;
	// it is supposed the regular device context for getting opengl function loading is already created for fake window in the constructor of this class;

	TRenderer& renderer = Get_renderer();

	CString cs_cls = TString().Format(_T("camera::%s"),(_pc_sz)__CLASS__); // stupid approach and must be reviewed;
	renderer.Scene().Ctx().Graphics().Target() << *this;
	renderer.Scene().Ctx().Graphics().Target().Source((_pc_sz)cs_cls);

	const uint32_t u_major = renderer.Scene().Ctx().Graphics().Version().Major();
	const uint32_t u_minor = renderer.Scene().Ctx().Graphics().Version().Minor();

	if (__failed(renderer.Scene().Ctx().Graphics().Create(u_major, u_minor))) {
		this->m_error = renderer.Scene().Ctx().Graphics().Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->m_error.Print(TError::e_print::e_req));
	}
#if (0)
	// the fake window and its device handle can not be destroyed at this time; because not all opengl functions are loaded yet;
	context::CDevice& dev_ref = renderer.Scene().Ctx().Device();
	if (__failed(dev_ref.Destroy())) {
		this->m_error = dev_ref.Error();
		__trace_err_2(_T("%s\n"), (_pc_sz) this->m_error.Print(TError::e_print::e_req));
	}
#endif
#if (0)
	// for better debugging and in order do not re-compile the executable, this section is disabled;
	// sets resource identifiers for loading shaders' source code;
	if (__failed(renderer.Scene().Prog().Shaders().Fragment().Src().Cfg().ResId(IDS_TUTOR_2_SHADER_FRAG_0, e_res_types::e_string)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) renderer.Scene().Prog().Shaders().Fragment().Src().Cfg().Error().Print(TError::e_print::e_req));
	if (__failed(renderer.Scene().Prog().Shaders().Vertex().Src().Cfg().ResId(IDS_TUTOR_2_SHADER_VERT_0, e_res_types::e_string)))
	    __trace_err_2(_T("%s\n"), (_pc_sz) renderer.Scene().Prog().Shaders().Vertex().Src().Cfg().Error().Print(TError::e_print::e_req));
#else
	// loading external files of shaders' sources is moved to program_enum::load();
#endif
	
#if (0) // the scene preparation cannot be called at this point, because there is no vertex array is defined, the shape must be set first;
	if (__failed(renderer.Scene().Prepare()))
		return TBase::m_error = this->Renderer().Scene().Error();
#endif
	if (__failed(renderer.View().Grid().Create()))
	    __trace_err_2(_T("%s\n"), (_pc_sz) renderer.View().Grid().Error().Print(TError::e_print::e_req));

	renderer.Is_allowed(true);     // allows the draw opereation of the renderer;

#define _test_case_lvl -1
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	renderer.Scene().Destroy();
#endif
	return TBase::Error();
}