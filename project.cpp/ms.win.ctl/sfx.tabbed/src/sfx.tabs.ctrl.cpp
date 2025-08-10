/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2012 at 12:15:54pm, GMT+3, Rostov-on-Don, Monday;
	This is Pulsepay Shared Tab Control class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 12-Jul-2020 at 8:42:59p, UTC+7, Novosibirsk, Sunday;
*/
#include "sfx.tabs.ctrl.h"
#include "sfx.tabs.wnd.h"

using namespace ex_ui::controls::sfx::tabbed;

#define _wnd_ptr(_pvoid)   (reinterpret_cast<CWnd*>(_pvoid))
#define _wnd_ref(_pvoid) (*(reinterpret_cast<CWnd*>(_pvoid)))

/////////////////////////////////////////////////////////////////////////////

CControl:: CControl (void) : m_ctrl_id(0), m_wnd_ptr(nullptr), m_format(*this), m_layout(*this), m_tabs(*this) {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	try { m_wnd_ptr = new CWnd(*this); } catch (::std::bad_alloc&){ this->m_error << __e_no_memory; }
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
#if (1)
	const uint32_t n_style = WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	t_rect rc_ = (this->Layout() = rc_area);
	_wnd_ref(m_wnd_ptr).Create(
		hParent, rc_, TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), n_style, 0, _ctrl_id
	);

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error.Last();

	// looks through the tabs that were added *before* this control window creation and tries to create internal window of each tab page;
	for (int16_t i_ = 0; i_ < this->Tabs().Count(); i_++) {
		CTab& tab = this->Tabs().Tab(i_);
		if (tab.Page().Is_valid())
			continue;
		const err_code n_result = tab.Page().Create(_wnd_ref(m_wnd_ptr), rc_, this->Tabs().Active() == i_, i_);
		if (__failed(n_result)) {
			ATLASSERT(false==true);
			this->m_error = n_result; break;
		}
	}

	if (__failed(this->Layout().Update()))
		this->m_error = this->Layout().Error();
#endif
	return this->Error();
}
err_code  CControl::Destroy(void) {

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == m_wnd_ptr)
		return this->m_error << __e_pointer;

	if (false == _wnd_ref(m_wnd_ptr).IsWindow())
		return this->m_error << __e_hwnd;

	// before destroying the main window of this tabbed control it is necessary to destroy internal window of each tab page;
	for (int16_t i_ = 0; i_ < this->Tabs().Count(); i_++) {
		CTab& tab = this->Tabs().Tab(i_);
		if (tab.Page().Is_valid() == false)
			continue;
		const err_code n_result = tab.Page().Destroy();
		if (__failed(n_result)) { // nothing to do on error throw, just for debug purposes;
			ATLASSERT(false==true);
		}
	}

	_wnd_ref(m_wnd_ptr).SendMessage(WM_CLOSE); // ToDo: perhaps the calling ::DestroyWindow() would be better and faster?

	return this->Error();
}

TError&   CControl::Error  (void) const { return this->m_error ; }
const
CFormat&  CControl::Format (void) const { return this->m_format; }
CFormat&  CControl::Format (void)       { return this->m_format; }

bool      CControl::Is_valid (void) const {
	return nullptr != m_wnd_ptr && true == !!_wnd_ref(m_wnd_ptr).IsWindow();
}

const
CLayout&  CControl::Layout (void) const { return this->m_layout; }
CLayout&  CControl::Layout (void)       { return this->m_layout; }

err_code  CControl::Refresh(void) {

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

const CTabs& CControl::Tabs(void) const { return this->m_tabs; }
      CTabs& CControl::Tabs(void)       { return this->m_tabs; }

/////////////////////////////////////////////////////////////////////////////

err_code CControl::ITabEvent_OnAppend (const CTab& _added) {_added;
	this->m_error << __METHOD__ << __s_ok;

	CWindow win_ = this->Window();
	if (false == win_.IsWindow() ) // not created yet;
		return this->Error();

	err_code n_result = m_layout.Update();
	if (__failed(n_result))
		this->m_error = m_layout.Error();

	return this->Error();
}
err_code CControl::ITabEvent_OnFormat (const CFormat&) { return __s_ok; }
err_code CControl::ITabEvent_OnRemove (const uint16_t _tab_id) { _tab_id; return __s_ok; }
err_code CControl::ITabEvent_OnSelect (const int16_t _tab_ndx) { _tab_ndx; return __s_ok; }

/////////////////////////////////////////////////////////////////////////////
#if (0)

HRESULT       TTabCtrl::ParentRenderer (IRenderer*  const _renderer) {
	if (NULL == m_wnd_ptr)
		return OLE_E_BLANK;

	_wnd_ref(m_wnd_ptr).ParentRenderer(_renderer);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

HRESULT  TTabCtrl::IControlEvent_OnClick(const UINT ctrlId) { return m_evt_snk.IControlEvent_OnClick(ctrlId); }
HRESULT  TTabCtrl::IControlEvent_OnClick(const UINT ctrlId, const LONG_PTR nData) { return m_evt_snk.IControlEvent_OnClick(ctrlId, nData); }
#endif