/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2009 at 10:22:22pm, GMT+3, Rostov-on-Don, Monday;
	This is ST Status Bar Control interface implementation file.
	-----------------------------------------------------------------------------
	Reincarnation to Ebo Pack is made on 22-Aug-2020 at 7:38:34a, UTC+7, Novosibirsk, Saturday;
*/
#include "sfx.status.ctrl.h"
#include "sfx.status.wnd.h"

using namespace ex_ui::controls::sfx::status;

#define _wnd_ptr(_pvoid)   (reinterpret_cast<CWnd*>(_pvoid))
#define _wnd_ref(_pvoid) (*(reinterpret_cast<CWnd*>(_pvoid)))

/////////////////////////////////////////////////////////////////////////////

CControl:: CControl (void) : m_ctrl_id(0), m_wnd_ptr(nullptr), m_layout(*this), m_format(*this) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	try { m_wnd_ptr = new CWnd(); } catch (::std::bad_alloc&){ this->m_error << __e_no_memory; }
}
CControl::~CControl (void) {
	if (_wnd_ptr(m_wnd_ptr)) {
		try { _wnd_ptr(m_wnd_ptr)->~CWnd(); delete m_wnd_ptr; m_wnd_ptr = nullptr;} catch(...){ ATLASSERT(FALSE); }
	}
}

/////////////////////////////////////////////////////////////////////////////
const
CBorders& CControl::Borders (void) const { return m_borders; }
CBorders& CControl::Borders (void)       { return m_borders; }

err_code  CControl::Create (const HWND hParent, const uint32_t _ctrl_id) {
	hParent; _ctrl_id;
	this->m_error << __METHOD__ << __s_ok;

	if (false == ::IsWindow(hParent)) return this->m_error << __e_hwnd = _T("Invalid parent window handle;");
	if (nullptr == m_wnd_ptr)         return this->m_error << __e_not_inited;

	this->m_ctrl_id = _ctrl_id;
	t_rect  rc_area = {0};

	if (false == ::GetClientRect(hParent, &rc_area)) {
		return this->m_error.Last();
	}

	t_rect rc_ = (this->Layout() = rc_area);
	_wnd_ref(m_wnd_ptr).Create(
		hParent, rc_, TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 0, _ctrl_id
	);

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error.Last();
	
	if (__failed(this->Layout().Update()))
		this->m_error = this->Layout().Error();

	return this->Error();
}
err_code  CControl::Destroy(void) {

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == m_wnd_ptr)
		return this->m_error << __e_pointer;

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error << __e_hwnd;

	_wnd_ref(m_wnd_ptr).SendMessage(WM_CLOSE); // ToDo: perhaps the calling ::DestroyWindow() would be better and faster?

	return this->Error();
}

TError&   CControl::Error  (void) const { return this->m_error; }

const
CFormat&  CControl::Format (void) const { return this->m_format; }
CFormat&  CControl::Format (void)       { return this->m_format; }
const
CLayout&  CControl::Layout (void) const { return this->m_layout; }
CLayout&  CControl::Layout (void)       { return this->m_layout; }

err_code  CControl::Refresh (void) {

	if (nullptr == m_wnd_ptr)
		return __e_pointer;

	if (false == _wnd_ref(m_wnd_ptr).RedrawWindow(0, 0, RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_NOCHILDREN)) {
		return (this->m_error << __METHOD__).Last();
	}
	else return __s_ok;
}

CWindow   CControl::Window (void) const {
	if (nullptr == m_wnd_ptr)
		return CWindow();
	else
		return _wnd_ref(m_wnd_ptr);
}

#if (0)
/////////////////////////////////////////////////////////////////////////////

namespace ST_Ctrls { namespace _impl {

	TStatusFmt&  StatusBar_Format (void) {
		static TStatusFmt format_;
		return format_;
	}

}}
using namespace ST_Ctrls::_impl;


CStatusBar:: CStatusBar(IStatusEvents& _snk) : m_wnd_ptr(NULL), m_evt_snk(_snk), m_ctrl_id(0), m_layout(*this) {
	m_borders.Top().Thickness() = 1;
	m_borders.Top().Color().Create(::GetSysColor(COLOR_3DDKSHADOW));
}

/////////////////////////////////////////////////////////////////////////////

const
TStatusFmt&  CStatusBar::Format  (void) const { return StatusBar_Format(); }
TStatusFmt&  CStatusBar::Format  (void)       { return StatusBar_Format(); }

const
CPanels&     CStatusBar::Panels  (void) const { return m_panels; }
CPanels&     CStatusBar::Panels  (void)       { return m_panels; }
HRESULT      CStatusBar::Renderer(IRenderer*  const _renderer) {
	if (NULL == m_wnd_ptr)
		return OLE_E_BLANK;

	_wnd_ref(m_wnd_ptr).ParentRenderer(_renderer);

	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////

HRESULT  CStatusBar::IStatusEvt_OnAppend (const CPanel& _added) { _added; return S_OK; }
HRESULT  CStatusBar::IStatusEvt_OnFormat (const TStatusFmt&) { return S_OK; }
HRESULT  CStatusBar::IStatusEvt_OnRemove (const DWORD _panel_ndx) {_panel_ndx; return S_OK; }

/////////////////////////////////////////////////////////////////////////////

ex_ui::controls::IControlEvent&   CStatusBar::MouseEvtSink(void) { return m_evt_snk; }
#endif