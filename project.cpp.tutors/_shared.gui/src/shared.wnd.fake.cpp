/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Oct-2025 at 10:18:55.143, (UTC+4), Batumi, Sunday;
	This is Ebo Pack shared message-only (i.e. fake) window interface implementation file; 
*/
#include "shared.wnd.fake.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::popup;

CMsgWnd:: CMsgWnd (void) : TWindow(), m_h_dc(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	TWindow::Create(HWND_MESSAGE);

	if (false == TWindow::IsWindow()) {
		this->m_error.Last();
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return;
	}
	else {
		this->m_error << __s_ok;
		this->m_h_dc = TWindow::GetDC();
	//	__empty_ln();
		__trace_info_3(_T("context device: handle=%s;\n"),  TString()._addr_of(this->Get_ctx()));
	}
}

CMsgWnd::~CMsgWnd (void) {
	this->m_error << __METHOD__ << __s_ok;

	// (1) destroys device context handle;
	if (nullptr != this->m_h_dc) {
		TWindow::ReleaseDC(this->m_h_dc); this->m_h_dc = nullptr; // error code is not analized here yet;
	}
	// (2) destroys the fake window itself;
	if (TWindow::IsWindow())
		TWindow::DestroyWindow(); // the error code is not important yet;
}

TError& CMsgWnd::Error (void) const { return this->m_error; }
bool    CMsgWnd::Is_valid (void) const { return false == this->Error(); }

const
HDC& CMsgWnd::Get_ctx (void) const { return this->m_h_dc; }
HDC& CMsgWnd::Get_ctx (void)       { return this->m_h_dc; }

#if defined(_DEBUG)
	CString CMsgWnd::To_str (void) const {
		CString cs_out;

		if (this->Error())
			cs_out = this->Error().Print(TError::e_print::e_req);
		else
			cs_out = TString().Format(_T("cls::[%s::%s].%s() >> context device: handle=%s;"), 
				(_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, (_pc_sz) __METHOD__, TString()._addr_of(this->Get_ctx())
			);

		return  cs_out;
	}
#endif

CMsgWnd::operator const HDC& (void) const { return this->Get_ctx(); }