/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 17:06:23.568, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object/drafter interface implementation file;
*/
#include "drawable.drafter.h"

using namespace shared::drawable;

#pragma region cls::CDrafter{}

CDrafter:: CDrafter (void) : TBase(), m_surface(0) { TBase::m_error >>__CLASS__; }
//CDrafter:: CDrafter (const CDrafter& _src) : CDrafter() { *this = _src; }
CDrafter::~CDrafter (void) {}

err_code   CDrafter::OnCreate (const HWND _h_surface) {
	_h_surface;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Model().Create(_h_surface))) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error());
	} else
	if (__failed(this->View().Create(_h_surface))) {
		__trace_err_ex_2(TBase::m_error = this->View().Error());
	}

	this->m_surface = _h_surface; // important: otherwise there is no grid drawn;

	return TBase::Error();
}

err_code   CDrafter::OnDestroy (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Model().Destroy())) {
		__trace_err_ex_2(TBase::m_error = this->Model().Error());
	} else 
	if (__failed(this->View().Destroy())) {
		__trace_err_ex_2(TBase::m_error = this->View().Error());
	} else {}

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
		t_rect rc_client = {0};
		::GetClientRect(this->m_surface, &rc_client);
		this->Model().ViewPort().Set(rc_client);

		::glViewport(0, 0, rc_client.right - rc_client.left, rc_client.bottom - rc_client.top);
	}

//	::glClearColor(0.152f, 0.152f, 0.152f, 1.0f); // must to go before glClear();
	
	while (false == ((TBase&)(*this))().Is_stopped()) {
		delay.Wait();
		if (false == delay.Elapsed())
			continue;

		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // must be called before rendering each frame;

		delay.Reset();
		this->Model().Grid().Draw();

		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-swapbuffers ;
		if (false == !!::SwapBuffers(this->View().Device())) {
			TBase::m_error.Last();
			__trace_err_2(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_print::e_req));
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

#pragma endregion