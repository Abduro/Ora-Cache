/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:06:23.568, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface implementation file;
*/
#include "drawable.drafter.h"

using namespace shared::drawable;

#pragma region cls::CDrafter{}

CDrafter:: CDrafter (void) : TBase(), m_surface(0), m_mouse{0} { TBase::m_error >>__CLASS__; }
//CDrafter:: CDrafter (const CDrafter& _src) : CDrafter() { *this = _src; }
CDrafter::~CDrafter (void) {}
const
CCamera& CDrafter::Camera (void) const { return this->m_camera; }
CCamera& CDrafter::Camera (void)       { return this->m_camera; }

err_code CDrafter::OnCreate (const HWND _h_surface) {
	_h_surface;
	TBase::m_error <<__METHOD__<<__s_ok;

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

	CDelay delay(10, 100);
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
	if (0 == ::wglMakeCurrent(this->View().Device(), this->View().Graphs().Renderer())) {
		__trace_err_ex_2(TBase::m_error(CError::e_cmds::e_get_last) = _T("#__e_exec: making draw context current is failed"));
	}
	if (__failed(this->Model().Init())) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error());
	} else {

		t_size sz_client = ::Get_ViewPorts().Active().Get();
		t_rect rc_client = {0, 0, sz_client.cx, sz_client.cy};
		
		this->Model().Grid().Layout() << rc_client;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/glviewport ;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/glscissor ;
		::glViewport(0, 0, rc_client.right - rc_client.left, rc_client.bottom - rc_client.top);
		::glScissor(0, 0, rc_client.right - rc_client.left, rc_client.bottom - rc_client.top);
	}

	while (false == ((TBase&)(*this))().Is_stopped()) {
		delay.Wait();
		if (false == delay.Elapsed())
			continue;

		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // must be called before rendering each frame;

		const bool b_scaled = this->m_scale.Is_changed();
		if (b_scaled) {
		//	shared::sys_core::the_lock.lock();
			::glMatrixMode(GL_MODELVIEW);
			::glPushMatrix();
#if (0)
			const c_scaled scaled = this->m_scale();
			::glMultMatrixf(&scaled); // https://learn.microsoft.com/en-us/windows/win32/opengl/glmultmatrixf ;
#else
			/* warning: when using glScalef() with lighting, enable GL_NORMALIZE to ensure lighting calculations remain correct.
			*/
			const float f_factor = this->m_scale.Get();
			::glScalef(f_factor, f_factor, f_factor); // https://learn.microsoft.com/en-us/windows/win32/opengl/glscalef ;
#endif
		}
		delay.Reset();
		this->Model().Grid().Draw();

		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-swapbuffers ;
		if (false == !!::SwapBuffers(this->View().Device())) {
			TBase::m_error.Last();
			__trace_err_2(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_print::e_req));
		}
		if (b_scaled) {
		//	shared::sys_core::the_lock.unlock();
			::glPopMatrix();
		}
	}
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

err_code  CDrafter::IMouse_OnEvent (const CEvent& _event) {
	_event;
	if (_event.Buttons().The_last().What() != e_button::e_left)
		return __s_false; // not handled;

	const int32_t x_delta = _event.Coords().Get().x - this->m_mouse.x;
	const int32_t y_delta = _event.Coords().Get().y - this->m_mouse.y;

	this->m_mouse = _event.Coords().Get();

	return __s_ok; // handled;
}

err_code  CDrafter::IMouse_OnWheel (const CEvent& _event, const int32_t _delta) {
	_event; _delta;
	static int32_t n_delta_prev = 0;
	if (n_delta_prev != _delta) {
		__trace_warn_2(_T("zoom delta: %d;\n"), _delta);
		n_delta_prev = _delta;
	}

	this->m_scale.Set(_delta);

	return __s_ok; // handled;
}

#pragma endregion
#pragma region cls::CScale{}

CScale::CScale (void) : m_changed(false), m_factor(f_def_scale) {}

bool CScale::Is_changed (void) const { TSafe_Lock(); const bool b_changed = this->m_changed; return b_changed; }
void CScale::Is_changed (const bool _b_state) { TSafe_Lock(); this->m_changed = _b_state; }

float CScale::Get (void) const { TSafe_Lock(); const float f_value = this->m_factor;  return f_value; }
void  CScale::Set (const int32_t _n_factor) {
	_n_factor;
	static float f_factor_prev = f_def_scale;

	using namespace ex_ui::draw::open_gl::math::defs;

	TSafe_Lock();
	if (false) {}
	else if (_n_factor > 0) { this->m_factor += float(_n_factor) * f_delta; }
	else if (_n_factor < 0) { this->m_factor += float(_n_factor) * f_delta; if (this->m_factor < f_epsilon) this->m_factor = 0.1f; }
	else { return; }

	if (f_epsilon > this->m_factor - f_factor_prev)
		return;
	else
		f_factor_prev = this->m_factor;

	__trace_warn_2(_T("scale factor: %.7f;\n"), this->m_factor);

	this->m_scaled.Set(this->m_factor);
	this->m_changed = true;
	return;
}

c_scaled CScale::operator ()(void) const {
	TSafe_Lock();
	c_scaled scaled = this->m_scaled;
	return scaled;
}

#pragma endregion