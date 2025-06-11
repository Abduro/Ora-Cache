/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Dec-2023 at 01:13:48.1380302, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack draw renderer test app main frame interface implementation file;
*/
#include "win.gui_frame.h"

using namespace ex_ui::popup::layout;
using namespace ebo::boo::gui;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace gui { namespace _impl {

}}}}
using namespace ebo::boo::gui::_impl;

/////////////////////////////////////////////////////////////////////////////

using TIcon = CFrame::CIcon;

CFrame::CIcon:: CIcon (const CFrame& _frame) : TBase(), m_frame(_frame) { TBase::m_error >> __CLASS__; }
CFrame::CIcon::~CIcon (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code TIcon::Set (const uint16_t _u_res_id) {
	_u_res_id;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == !!_u_res_id)
		return TBase::m_error << __e_invalid_arg;

	if (false == !!m_frame.Window().IsWindow())
		return TBase::m_error << __e_hwnd;
	// no error handling of icon assignment through sending the message; 
	::SendMessage(m_frame.Window(), WM_SETICON, 0, (l_param)TBase::Load(_u_res_id, 0));
	::SendMessage(m_frame.Window(), WM_SETICON, 1, (l_param)TBase::Load(_u_res_id, 1));

	return TBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

CFrame:: CFrame (void) : m_icon(*this), m_wnd(TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__)) {this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CFrame::~CFrame (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CFrame::Create (void) {

	this->m_error << __METHOD__ << __s_ok;

	if (m_wnd.IsWindow())
		return (this->m_error << (err_code) TErrCodes::eObject::eExists);

//	RECT rc_ = CWndLayout().Centered(CWndLayout().Default());
	RECT rc_ = CWndLayout().Autosize();

	_pc_sz pc_sz_title = _T("Window Popup GUI Test App-%s"); // no loading string from resources yet;
#if defined(WIN64)
	CString cs_bits; cs_bits.Format(pc_sz_title, _T("64-bit"));
#else // duplication code lines is made intentionally;
	CString cs_bits; cs_bits.Format(pc_sz_title, _T("32-bit"));
#endif

	if (::IsRectEmpty(&rc_))
		return (m_error << __e_rect);
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles ; WS_EX_COMPOSITED|WS_EX_NOPARENTNOTIFY|WS_EX_TRANSPARENT;
	static const DWORD std_style = WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	static const DWORD ext_style = WS_EX_NOPARENTNOTIFY;

#if (0)
	m_wnd.Atom().Register(TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, m_wnd.GetWindowProc()));
	if (m_wnd.Atom().Is_valid()) {

		::ATL::CWindowImplBaseT<>& base = (::ATL::CWindowImplBaseT<>&)m_wnd;

		HWND hView = base.Create(HWND_DESKTOP, &rc_, (_pc_sz) cs_bits, dw_style, 0u, 0u, (ATOM)m_wnd.Atom(), nullptr);
		if (!hView)
			return m_error.Last();
	}
	else {
		HWND hView = m_wnd.Create(HWND_DESKTOP, &rc_, (_pc_sz) cs_bits, dw_style);
		if (!hView)
			return m_error.Last();
	}
#else
	HWND hView = m_wnd.Create(HWND_DESKTOP, &rc_, (_pc_sz) cs_bits, std_style, ext_style);
	if (!hView)
		return m_error.Last();
#endif

	if (false == m_error) {
		
		const err_code n_result = this->m_icon.Set(IDR_WINGUI_ICO);
		if (__failed(n_result))
			this->m_error = this->m_icon.Error(); // just for debug purpose;

		m_wnd.ShowWindow(SW_SHOW);
	}
	
	return this->Error();
}

err_code CFrame::Destroy(void) {
	m_error << __METHOD__ << __s_ok;

	if (m_wnd.IsWindow())
		m_wnd.SendMessage(WM_CLOSE);
	else
		m_error << (err_code) TErrCodes::eExecute::eState;

	return this->Error();
}

TError&  CFrame::Error (void) const { return this->m_error; }
const
CFrame::CIcon& CFrame::Icon (void) const { return this->m_icon; }
CFrame::CIcon& CFrame::Icon (void)       { return this->m_icon; }

const
CWnd& CFrame::Window (void) const { return this->m_wnd; }
CWnd& CFrame::Window (void)       { return this->m_wnd; }

/////////////////////////////////////////////////////////////////////////////