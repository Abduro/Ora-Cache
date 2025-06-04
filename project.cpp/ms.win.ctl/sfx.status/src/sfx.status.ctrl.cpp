/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2009 at 10:22:22pm, GMT+3, Rostov-on-Don, Monday;
	This is ST Status Bar Control interface implementation file.
	-----------------------------------------------------------------------------
	Reincarnation to Ebo Pack is made on 22-Aug-2020 at 7:38:34a, UTC+7, Novosibirsk, Saturday;
*/
#include "sfx.status.ctrl.h"
#include "sfx.status.wnd.h"
#if (0)
using namespace ST_Ctrls;
using namespace ST_Ctrls::_impl;
using namespace shared::sys_core;

#define _wnd_ptr(_pvoid)   (reinterpret_cast<CStatus_Wnd*>(_pvoid))
#define _wnd_ref(_pvoid) (*(reinterpret_cast<CStatus_Wnd*>(_pvoid)))

/////////////////////////////////////////////////////////////////////////////

namespace ST_Ctrls { namespace _impl {

	TStatusFmt&  StatusBar_Format (void) {
		static TStatusFmt format_;
		return format_;
	}

}}
using namespace ST_Ctrls::_impl;

/////////////////////////////////////////////////////////////////////////////

CStatusBar:: CStatusBar(IStatusEvents& _snk) : m_wnd_ptr(NULL), m_evt_snk(_snk), m_ctrl_id(0), m_layout(*this) {
	m_error << __MODULE__ << S_OK >> __MODULE__;
	try { m_wnd_ptr = new _impl::CStatus_Wnd(*this, *this); } catch (::std::bad_alloc&){ m_error = E_OUTOFMEMORY; }
	m_borders.Top().Thickness() = 1;
	m_borders.Top().Color().Create(::GetSysColor(COLOR_3DDKSHADOW));
}
CStatusBar::~CStatusBar(void) {
	if (_wnd_ptr(m_wnd_ptr)) {
		try { _wnd_ptr(m_wnd_ptr)->~CStatus_Wnd(); delete m_wnd_ptr; m_wnd_ptr = NULL;} catch(...){ ATLASSERT(FALSE); }
	}
}

/////////////////////////////////////////////////////////////////////////////
const
CBorders&    CStatusBar::Borders (void) const { return m_borders; }
CBorders&    CStatusBar::Borders (void)       { return m_borders; }
HRESULT      CStatusBar::Create  (const HWND hParent, const UINT _ctrl_id) {
	m_error << __FUNCTIONW__ << S_OK;

	if (FALSE == ::IsWindow(hParent)) return (m_error = OLE_E_INVALIDHWND);
	if (NULL  == m_wnd_ptr)           return (m_error = OLE_E_BLANK);

	RECT rc_area = {0};
	m_ctrl_id = _ctrl_id;

	const BOOL b_result = ::GetClientRect(hParent, &rc_area);
	if (FALSE == b_result) {
		m_error.Last(); return m_error;
	}

	RECT rc_ = (m_layout = rc_area);
	_wnd_ref(m_wnd_ptr).Create(
		hParent, rc_, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 0, _ctrl_id
	);

	if (FALSE == _wnd_ref(m_wnd_ptr).IsWindow())
		m_error = __LastErrToHresult();
	else
		m_layout.Update();

	return m_error;
}

HRESULT      CStatusBar::Destroy (void) {
	m_error << __MODULE__ << S_OK;

	if (NULL == m_wnd_ptr)
		return (m_error = OLE_E_BLANK);

	if (FALSE == _wnd_ref(m_wnd_ptr).IsWindow())
		return (m_error = __DwordToHresult(ERROR_INVALID_WINDOW_HANDLE));

	_wnd_ref(m_wnd_ptr).SendMessage(WM_CLOSE);

	return m_error;
}

TErrorRef    CStatusBar::Error   (void) const { return m_error ; }
const
TStatusFmt&  CStatusBar::Format  (void) const { return StatusBar_Format(); }
TStatusFmt&  CStatusBar::Format  (void)       { return StatusBar_Format(); }
const
TStatusLay&  CStatusBar::Layout  (void) const { return m_layout; }
TStatusLay&  CStatusBar::Layout  (void)       { return m_layout; }
const
CPanels&     CStatusBar::Panels  (void) const { return m_panels; }
CPanels&     CStatusBar::Panels  (void)       { return m_panels; }
HRESULT      CStatusBar::Renderer(IRenderer*  const _renderer) {
	if (NULL == m_wnd_ptr)
		return OLE_E_BLANK;

	_wnd_ref(m_wnd_ptr).ParentRenderer(_renderer);

	return S_OK;
}
HRESULT      CStatusBar::Refresh (void) {
	if (NULL == m_wnd_ptr)
		return OLE_E_BLANK;

	const BOOL b_result = _wnd_ref(m_wnd_ptr).RedrawWindow(0, 0, RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_NOCHILDREN);
	if (FALSE == b_result)
		return __LastErrToHresult();
	else
		return S_OK;
}
CWindow      CStatusBar::Window  (void) const {
	if (NULL == m_wnd_ptr)
		return CWindow();
	else
		return _wnd_ref(m_wnd_ptr);
}

/////////////////////////////////////////////////////////////////////////////

HRESULT  CStatusBar::IStatusEvt_OnAppend (const CPanel& _added) { _added; return S_OK; }
HRESULT  CStatusBar::IStatusEvt_OnFormat (const TStatusFmt&) { return S_OK; }
HRESULT  CStatusBar::IStatusEvt_OnRemove (const DWORD _panel_ndx) {_panel_ndx; return S_OK; }

/////////////////////////////////////////////////////////////////////////////

ex_ui::controls::IControlEvent&   CStatusBar::MouseEvtSink(void) { return m_evt_snk; }
#endif