/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:06:23.568, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface implementation file;
*/
#include "drawable.drafter.h"
#include "gl_procs_light.h"
#include "gl_procs_clear.h"
#include "utils\gl_procs_vsync.h"
#include "mouse.cache.h"

using namespace ::shared::drawable;
using namespace ::open_gl::procs::ver_1_1;
using namespace ::open_gl::procs::utils::ver_1_1;

#pragma region cls::CDrafter{}

CDrafter:: CDrafter (void) : TBase(), m_surface(0) { TBase::m_error >>__CLASS__; }
CDrafter::~CDrafter (void) {}
const
CCamera& CDrafter::Camera (void) const { return this->m_camera; }
CCamera& CDrafter::Camera (void)       { return this->m_camera; }

err_code CDrafter::OnCreate (const HWND _h_surface) {
	_h_surface;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == ::Get_version().Is_base()) {
		static _pc_sz p_err_ver_unsupp = _T("#__e_vers: OpenGL ver %s is not supported");
		__trace_err_ex_2(
			this->m_error <<(err_code)TErrCodes::eExecute::eState = TString().Format(p_err_ver_unsupp, (_pc_sz) ::Get_version().Data().To_str() )
		);
		return this->Error();
	}

	if (__failed(::Get_mouse() << this)) { __trace_err_ex_2(this->m_error = ::Get_mouse().Error()); }
	if (__failed(this->Camera().Create())) { __trace_err_ex_2(this->m_error = this->Camera().Error()); }

	if (__failed(this->Model().Create(_h_surface))) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error());
	} else
	if (__failed(this->View().Create(_h_surface))) {
		__trace_err_ex_2(TBase::m_error = this->View().Error());
	}

	this->m_surface = _h_surface; // important: otherwise there is no grid drawn;
	if (__failed(::Get_ViewPorts().Add(this->m_surface)))
		__trace_err_ex_2(TBase::m_error = ::Get_ViewPorts().Error());
	else {
	}

	CVSync v_sync;
	const int32_t n_intervals = v_sync.Get();
	if (v_sync.Error()) { __trace_err_ex_2(v_sync.Error()); }
	else {
		__trace_warn_2(_T("vsync: currently set intevals is %d;\n"), n_intervals);
	}

	this->m_tria.Format();

	return TBase::Error();
}

err_code CDrafter::OnDestroy (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Camera().Destroy())) __trace_err_ex_2(this->m_error = this->Camera().Error());
	if (__failed(::Get_mouse() >> this)) { __trace_err_ex_2(this->m_error = ::Get_mouse().Error()); }

	if (__failed(this->Model().Destroy())) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error());
	} else 
	if (__failed(this->View().Destroy())) {
		__trace_err_ex_2(TBase::m_error = this->View().Error());
	} else {}

	if (__failed(::Get_ViewPorts().Remove(this->m_surface)))
		__trace_err_ex_2(TBase::m_error = ::Get_ViewPorts().Error());

	this->m_surface = 0;

	return TBase::Error();
}

void CDrafter::Run (void) {

	((TBase&)(*this)).Id(::GetCurrentThreadId()); // there is no necessaty to set the thread wrapper identifier to current value, because it is useless;

	__trace_impt_2(_T("drafter started: thread ID = %u;\n"), ((TBase&)(*this)).Id());

	CDelay delay(10, 30);
#if (1)
	// this *must* to be here: worker thread requires to set the current renderer;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
	if (0 == ::wglMakeCurrent(this->View().Device(), this->View().Graphs().Renderer())) {
		__trace_err_ex_2(TBase::m_error(CError::e_cmds::e_get_last) = _T("#__e_exec: making draw context current is failed"));
	}
#endif
	if (__failed(this->View().Init())) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error()); return;  // nothing to draw; this is critical error;
	} else {

		t_size sz_client = ::Get_ViewPorts().Active().Get();
		t_rect rc_client = {0, 0, sz_client.cx, sz_client.cy};
		
		this->View().Grid().Layout() << rc_client;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/glscissor ;
		::glViewport(0, 0, sz_client.cx, sz_client.cy);
		::glScissor (0, 0, sz_client.cx, sz_client.cy);
	}

	::open_gl::procs::ver_1_1::CClear clear;
	::open_gl::procs::matrix::ver_1_1::CStack stack;

#if (1)
	while (false == ((TBase&)(*this))().Is_stopped()) {
		delay.Wait();
		if (false == delay.Elapsed())
			continue;
#endif
		clear.All(); // must be called before rendering each frame;

		this->View().Grid().Draw();
		this->m_tria.Draw();

	//	::glFinish(); // https://learn.microsoft.com/en-us/windows/win32/opengl/glfinish ;
		glFlush();    // https://learn.microsoft.com/en-us/windows/win32/opengl/glflush ;
		
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-swapbuffers ;
		if (false == !!::SwapBuffers(this->View().Device())) {
			TBase::m_error.Last();
			__trace_err_2(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_print::e_req));
		}
		delay.Reset();
#if (1)
	}
#endif
	::wglMakeCurrent(this->View().Device(), 0); // it must be set before marking event as signaled; ::wglMakeCurrent(0, 0) >> does not work!
	(*this)().Event() << true; // sets the event to signal state, i.e. the job is done;
	__trace_impt_2(_T("drafter ended: thread ID = %u;\n"), ((TBase&)(*this)).Id());
}

const
CModel& CDrafter::Model (void) const { return this->m_model; }
CModel& CDrafter::Model (void)       { return this->m_model; }
const
CView&  CDrafter::View (void) const { return this->m_view; }
CView&  CDrafter::View (void)       { return this->m_view; }

//CDrafter& CDrafter::operator = (const CDrafter& _src) { _src; return *this; }

TError&   CDrafter::IMouse_Error (void) const { return this->Error(); }

err_code  CDrafter::IMouse_OnButton (const CEvent& _event) {
	_event;
	if (_event.Buttons().The_last().What() != e_button::e_left) return __s_false;
	if (_event.Buttons().The_last().Is_pressed() == false) return __s_false; // not handled;

	t_point pt_curs = _event.Coords() << this->m_surface;
	::Get_cursor() << pt_curs;

//	__trace_info_2(_T("cursor pos >> [x = %04d; y = %04d];\n"), pt_curs.x, pt_curs.y);

	return __s_ok; // handled;
}

err_code  CDrafter::IMouse_OnMove  (const CEvent& _event) {
	_event;
	if (_event.Buttons().The_last().What() != e_button::e_left) return __s_false;   // is hold for moving a draw object;
	if (_event.Buttons().The_last().Is_pressed() == false)  return __s_false;

	t_point pt_curs = _event.Coords() << this->m_surface;
	::Get_cursor() << pt_curs;

	this->m_tria.Move().Update();
	this->m_tria.Rotate().Set(_event);

//	__trace_info_2(_T("cursor pos >> [x = %04d; y = %04d];\n"), pt_curs.x, pt_curs.y);

	return __s_ok; // not handled;
}

err_code  CDrafter::IMouse_OnWheel (const CEvent& _event, const int32_t _delta) {
	_event; _delta;
	static int32_t n_delta_prev = 0;
	if (n_delta_prev != _delta) {
	//	__trace_warn_2(_T("zoom delta: %d;\n"), _delta);
		n_delta_prev = _delta;
	}

	this->View().Grid().Scale().Set(_delta);

	return __s_ok; // handled;
}

#pragma endregion