/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 9:42:03a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control tab items interface implementation file;
*/
#include "sfx.tabs.ext.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace _impl {
#if (0)
#include "sys.sync_obj.h"

shared::sys_core::CSyncObject sync_ob;

#define Safe_Guard Safe_Lock(sync_ob)
#endif

}}}}}
using namespace ex_ui::controls::sfx::tabbed;
/////////////////////////////////////////////////////////////////////////////

CPage:: CPage (void) : m_p_ctrl(0) {
	TWindow::Handlers().Draw().Subscribe (this);
	TWindow::Handlers().Live().Subscribe (this); TWindow::Handlers().Frame().Subscribe(this);
}
CPage::~CPage (void) {
	TWindow::Handlers().Draw().Unsubscribe (this);
	TWindow::Handlers().Live().Unsubscribe (this); TWindow::Handlers().Frame().Unsubscribe(this);

	if (this->Is_valid())
		this->Destroy();
}

#pragma region __msg_handler_callbacks__

err_code CPage::IEvtDraw_OnErase (const HDC _dev_ctx) {
	_dev_ctx;
	err_code n_result = __s_false;
#if (0) // trying to remove incorrect drawing the borders on handling window size message, when the window size is decreased;
	if (this->Get_ptr() == nullptr)
		return n_result;

	const ex_ui::controls::sfx::tabbed::CControl& ctrl_ref = *(this->Get_ptr());

	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);

	ex_ui::draw::memory::CMode(_dev_ctx).Set(ex_ui::draw::memory::CMode::e_advanced);
	CZBuffer z_buffer(_dev_ctx, rc_area);

	z_buffer.Draw(rc_area, ctrl_ref.Format().Bkgnd().Solid().ToRgb());

	const rgb_color clr_border = ctrl_ref.Format().Border().Color().Normal();

	using ex_ui::controls::borders::TRawBorders;

	for (TRawBorders::const_iterator iter_ = TPane::Borders().Raw().begin(); iter_ != TPane::Borders().Raw().end(); ++iter_) {
		const CBorder& border = iter_->second;
		z_buffer.Draw( border, clr_border);
	}
#endif	
	return n_result;
}
// https://learn.microsoft.com/en-us/windows/win32/gdi/the-wm-paint-message
// https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint ;
err_code CPage::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	err_code n_result = __s_false;  // this message is handled;

	if (this->Get_ptr() == nullptr)
		return n_result;

	const ex_ui::controls::sfx::tabbed::CControl& ctrl_ref = *(this->Get_ptr());
	// using BeginPaint() and EndPaint() solves the problem of incorrect draw of borders that takes a place on handling erase background message;
	using WTL::CPaintDC;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-paintstruct ;
	CPaintDC dc_(*this);

	t_rect& rc_paint = dc_.m_ps.rcPaint;

	ex_ui::draw::memory::CMode(dc_).Set(ex_ui::draw::memory::CMode::e_advanced);
	CZBuffer z_buffer(dc_, rc_paint);

	z_buffer.Draw(rc_paint, ctrl_ref.Format().Bkgnd().Solid().ToRgb());

	const rgb_color clr_border = ctrl_ref.Format().Border().Color().Normal();

	using ex_ui::controls::borders::TRawBorders;

	for (TRawBorders::const_iterator iter_ = TPane::Borders().Raw().begin(); iter_ != TPane::Borders().Raw().end(); ++iter_) {
		const CBorder& border = iter_->second;
		z_buffer.Draw( border, clr_border);
	}

	return   n_result;
}

err_code CPage::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code CPage::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CPage::IEvtFrame_OnSize   (const eState _e_state, const t_size _rect) {
	_e_state;

	t_rect rc_area = {0, 0, _rect.cx, _rect.cy};

	TPane::Borders() << rc_area;

	err_code n_result = __s_false;
	return   n_result;
}

err_code CPage::IEvtFrame_OnSizing (const eEdges _edges, t_rect* _p_rect) { // it looks like the child window cannot be sizing by the pointing device, e.g. a mouse;
	_edges; _p_rect;

	if (_p_rect)
		TPane::Borders() << *_p_rect;
	else {
		bool b_break_point = false;
		b_break_point = !b_break_point;
	}

	err_code n_result = __s_false;
	return   n_result;
}

#pragma endregion

err_code CPage::Create (const HWND hParent, const t_rect& _rect, const bool _b_visible, const uint32_t _page_id) {
	hParent; _rect; _b_visible; _page_id;
	err_code n_result = __s_ok;

	if (nullptr == hParent || false == !!::IsWindow(hParent))
		return n_result = __e_hwnd;

	if (this->Is_valid())
		return n_result = (err_code) TErrCodes::eObject::eExists;

	const uint32_t n_style = WS_CHILD|(_b_visible ? WS_VISIBLE : 0)|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	t_rect rect_ = _rect;
	
	TWindow::Create(
		hParent, rect_, TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), n_style, 0, _page_id
	);

	if (this->Is_valid() == false)
		n_result = __LastErrToHresult();
	else {
		TPane::Id(_page_id);
		this->Layout().Rect() = _rect;
		TPane::Borders().Set(_rect);
	}

	return n_result;
}

err_code CPage::Destroy(void) {

	err_code n_result = __s_ok;

	if (this->Is_valid() == false)
		return n_result;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
	if (0 == TWindow::DestroyWindow())
		n_result = __LastErrToHresult();

	return  n_result;
}

const
HWND     CPage::Handle (void) const { return TWindow::m_hWnd; }

bool     CPage::Is_valid (void) const { return !!TWindow::IsWindow(); }

const
ex_ui::controls::pane::CLayout& CPage::Layout (void) const { return this->m_layout; }
ex_ui::controls::pane::CLayout& CPage::Layout (void)       { return this->m_layout; }

err_code CPage::Is_visible (const bool _state) {
	_state;
	err_code n_result = __s_ok;

	if (false == this->Is_valid())
		return n_result = __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-animatewindow ;

	CWindow(this->Handle()).ShowWindow(_state ? SW_SHOW : SW_HIDE);

	return n_result;
}

TCtrlPtr CPage::Get_ptr (void) const { return this->m_p_ctrl; }
bool  CPage::Set_ptr (TCtrlPtr _ptr) {
	_ptr;
	const bool b_changed = this->Get_ptr() != _ptr;
	if (b_changed)
		this->m_p_ctrl = _ptr;
	return b_changed;
}

err_code CPage::MoveTo (const t_rect& _rect, const bool _b_redraw) {
	_rect;
	err_code n_result = __s_ok;
	if (::IsRectEmpty(&_rect))
		return n_result = __e_rect;

	if (this->Is_valid() == false)
		return n_result = __e_not_inited;

	const bool b_result = !!TWindow::MoveWindow(&_rect, _b_redraw);
	if (false == b_result)
		n_result = __LastErrToHresult();

	return n_result;
}

CPage&   CPage::operator <<(TCtrlPtr _ptr) { this->Set_ptr(_ptr); return *this; }

/////////////////////////////////////////////////////////////////////////////

CTab:: CTab (const uint16_t _id, _pc_sz _lp_sz_cap) : m_id(0), m_strip{0}, m_fake(false), m_index(0) {*this << _lp_sz_cap << _id; }
CTab:: CTab (const CTab& _tab) : CTab() { *this = _tab; }
CTab:: CTab (CTab&& _victim) : CTab() { *this = _victim; }
CTab::~CTab (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz     CTab::Caption (void) const { return this->m_cap.GetString(); }
CString&   CTab::Caption (void)       { return this->m_cap; }

uint16_t   CTab::Id (void) const { return this->m_id; }
uint16_t&  CTab::Id (void)       { return this->m_id; }

uint16_t   CTab::Index (void) const { return this->m_index; }

const bool CTab::Is_fake(void) const { return this->m_fake; } // this can be set by 
const
TLayersEx& CTab::Layers (void) const { return this->m_layers; }
TLayersEx& CTab::Layers (void)       { return this->m_layers; }

const
CPage&     CTab::Page (void) const { return this->m_page; }
CPage&     CTab::Page (void)       { return this->m_page; }

const
t_rect&    CTab::Strip (void) const { return this->m_strip; }
t_rect&    CTab::Strip (void)       { return this->m_strip; }

const bool CTab::Strip (const _long _left, const _long _top, const _long _right, const _long _bottom) {
	_left; _top; _right; _bottom;
	bool b_changed = false;

	if (_bottom != this->m_strip.bottom) { this->m_strip.bottom = _bottom; b_changed = true; }
	if (_left   != this->m_strip.left)   { this->m_strip.left = _left; b_changed = true; }
	if (_right  != this->m_strip.right)  { this->m_strip.right = _right; b_changed = true; }
	if (_top    != this->m_strip.top)    { this->m_strip.top = _top; b_changed = true; }

	return b_changed;
}

const
TState& CTab::State  (void) const { return this->m_state; }
TState& CTab::State  (void)       { return this->m_state; }

/////////////////////////////////////////////////////////////////////////////

CTab&   CTab::operator =  (const CTab& _tab) {
	 this->Page() << _tab.Page().Get_ptr(); // the page is not copyable due to window messages' handlers, just copying the control pointer;
	*this << _tab.Caption() << _tab.Id() << _tab.State();
	 this->m_index = _tab.m_index;  // no direct assigning of the index value;
	return *this;
}
CTab&   CTab::operator =  (CTab&& _victim) { *this = (const CTab&)_victim; return *this; }

CTab&   CTab::operator << (_pc_sz _lp_sz_cap) { this->Caption() = _lp_sz_cap; return *this; }
CTab&   CTab::operator << (const CString& _cs_cap) { this->Caption() = _cs_cap; return *this; }
CTab&   CTab::operator << (const uint16_t _tab_id) { this->Id() = _tab_id; return *this; }
CTab&   CTab::operator << (const TState& _state) { this->State() = _state; return *this; }

/////////////////////////////////////////////////////////////////////////////

CTab&  Get_fake_tab (void) { static CTab fake; return fake; }

CTabs:: CTabs (CControl& _ctrl) : m_ctrl(_ctrl),  m_sink(nullptr) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; Get_fake_tab().m_fake = true; }
CTabs:: CTabs (const CTabs& _src) : CTabs(_src.m_ctrl) { *this = _src; }
CTabs::~CTabs (void) {}

/////////////////////////////////////////////////////////////////////////////
int16_t  CTabs::Active (void) const {

	for (int16_t i_ = 0; i_ < this->Count() ; i_++) {

		const CTab& tab_ = m_tabs[i_];

		if (tab_.State().IsSelected())
			return i_;
	}
	return CTabs::not_avbl;
}

err_code CTabs::Active (const int16_t _ndx) {
	_ndx;
	this->m_error << __METHOD__ << __s_ok;

	if (_ndx < 0 || _ndx >= static_cast<int16_t>(this->Count()))
		return this->m_error << DISP_E_BADINDEX;

	for (uint16_t i_ = 0; i_ < this->Count() ; i_++) {

		CTab& tab_ = m_tabs.at(i_);

		tab_.State().Modify(TState::eSelected, i_ == _ndx );
		tab_.Page().Is_visible(i_ == _ndx);
	}
	((ITabEvents&)this->m_ctrl).ITabEvent_OnSelect(this->Active());
	return this->Error();
}

err_code CTabs::Append (const uint16_t _id, _pc_sz _lp_sz_cap) { CTab c_tab(_id, _lp_sz_cap); return this->Append(c_tab); }

err_code CTabs::Append (const CTab& _tab) {
	_tab;
	this->m_error << __METHOD__ << __s_ok;

	try {
		m_tabs.push_back(_tab);

		const uint16_t n_index = this->Count() - 1; // on this line of the code it is expected that 'push_back' is succeeded;

		if (this->Active() == CTabs::not_avbl)
			this->Active(n_index);

		m_tabs.at(n_index).Page().Set_ptr(&this->m_ctrl);
		m_tabs.at(n_index).m_index = n_index;

		((ITabEvents&)this->m_ctrl).ITabEvent_OnAppend(_tab);
	}
	catch (const ::std::bad_alloc&) { m_error << __e_no_memory; }

	return this->Error();
}

err_code CTabs::Append (_pc_sz _lp_sz_cap) {
	_lp_sz_cap;
	const uint16_t n_id = !!this->Count() ? this->Tab(this->Count() - 1).Id() + 1 : this->Count() + 1; // just creates new identifier with the next value;

	CTab c_tab(n_id, _lp_sz_cap); return this->Append(c_tab);
}

uint16_t CTabs::Count (void) const { return static_cast<uint16_t>(this->m_tabs.size()); }

const
CTab&    CTabs::Current(void) const { if (CTabs::not_avbl == this->Active()) return Get_fake_tab(); else return this->Tab(this->Active()); }
CTab&    CTabs::Current(void)       { if (CTabs::not_avbl == this->Active()) return Get_fake_tab(); else return this->Tab(this->Active()); }

TError&  CTabs::Error (void) const { return this->m_error; }

void     CTabs::Events(ITabEvents* _p_snk) { this->m_sink = _p_snk; }

ITabEvents* CTabs::Events (void) const {
	return this->m_sink;
}

int16_t  CTabs::Has (const t_point& _pt) const {

	for (size_t i_ = 0; i_ < m_tabs.size(); i_++) {

		const CTab&  tab_ = m_tabs.at(i_);
		const t_rect& rc_ = tab_.Strip();

		if (::PtInRect(&rc_, _pt)) {
			return static_cast<int16_t>(i_);
		}
	}
	return CTabs::not_avbl;
}

const
CTab&    CTabs::Tab (const int16_t _ndx) const {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		return Get_fake_tab();
	}
	else
		return m_tabs[_ndx];
}

CTab&    CTabs::Tab (const int16_t _ndx) {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		return Get_fake_tab();
	}
	else
		return m_tabs[_ndx];
}

err_code CTabs::Remove(const uint16_t _id) {
	_id;
	this->m_error << __METHOD__ << __s_ok;

	for (uint16_t i_ = 0; i_ < this->Raw().size(); i_++) {
		if (this->Raw().at(i_).Id() != _id)
			continue;
		else {
			this->m_tabs.erase(this->m_tabs.begin() + i_);
			((ITabEvents&)this->m_ctrl).ITabEvent_OnRemove(_id);
			return this->Error();
		}
	}
	return this->m_error << (err_code)TErrCodes::eData::eNotFound;
}

const
TTabArray&CTabs::Raw (void) const { return m_tabs; }

err_code  CTabs::Reset (void) {
	this->m_error << __METHOD__ << __s_ok;
	try {
		if (m_tabs.empty() == false)
			m_tabs.clear();
	}
	catch (...) {
		this->m_error << __e_no_memory;
	}
	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CTabs& CTabs::operator = (const CTabs& _src) { *this << _src.Raw() << _src.Events() << _src.Active(); return *this; }
CTabs& CTabs::operator = (CTabs&& _victim) {
	*this = (const CTabs&)_victim; return *this;
}

CTabs& CTabs::operator <<(const int16_t _active_ndx) { this->Active(_active_ndx); return *this; }

CTabs& CTabs::operator <<(const TTabArray& _tabs) {
	_tabs;
	if (this->m_tabs.empty() == false)
		this->Reset();

	try {
		this->m_tabs = _tabs;
	} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }

	return *this;
}

CTabs& CTabs::operator <<(ITabEvents* _p_events) {

	this->Events(_p_events); return *this;
}

CTabs& CTabs::operator +=(_pc_sz _lp_sz_cap) { this->Append(0, _lp_sz_cap); return *this; }
CTabs& CTabs::operator +=(const CTab& _tab ) { this->Append(_tab); return *this; }

CTabs& CTabs::operator -=(const uint16_t _id) { this->Remove(_id); return *this; }