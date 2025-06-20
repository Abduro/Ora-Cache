/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 9:42:03a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control tab items interface implementation file;
*/
#include "sfx.tabs.ext.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;

/////////////////////////////////////////////////////////////////////////////

CTab:: CTab (const uint16_t _id, _pc_sz _lp_sz_cap) : m_id(0), m_rect{0} { *this << _lp_sz_cap << _id; }
CTab:: CTab (const CTab& _tab) : CTab() { *this = _tab; }
CTab:: CTab (CTab&& _victim) : CTab() { *this = _victim; }
CTab::~CTab (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz     CTab::Caption (void) const { return this->m_cap.GetString(); }
CString&   CTab::Caption (void)       { return this->m_cap; }

uint16_t   CTab::Id (void) const { return this->m_id; }
uint16_t&  CTab::Id (void)       { return this->m_id; }

const
TLayersEx& CTab::Layers (void) const { return this->m_layers; }
TLayersEx& CTab::Layers (void)       { return this->m_layers; }

const
t_rect&    CTab::Rect (void) const { return this->m_rect; }
t_rect&    CTab::Rect (void)       { return this->m_rect; }
const bool CTab::Rect (const _long _left, const _long _top, const _long _right, const _long _bottom) {
	_left; _top; _right; _bottom;
	bool b_changed = false;

	if (_bottom != this->m_rect.bottom) { this->m_rect.bottom = _bottom; b_changed = true; }
	if (_left   != this->m_rect.left)   { this->m_rect.left = _left; b_changed = true; }
	if (_right  != this->m_rect.right)  { this->m_rect.right = _right; b_changed = true; }
	if (_top    != this->m_rect.top)    { this->m_rect.top = _top; b_changed = true; }

	return b_changed;
}

const
TState& CTab::State  (void) const { return this->m_state; }
TState& CTab::State  (void)       { return this->m_state; }

/////////////////////////////////////////////////////////////////////////////

CTab&   CTab::operator =  (const CTab& _tab) { *this << _tab.Caption() << _tab.Id() << _tab.State(); return *this; }
CTab&   CTab::operator =  (CTab&& _victim) { *this = (const CTab&)_victim; return *this; }

CTab&   CTab::operator << (_pc_sz _lp_sz_cap) { this->Caption() = _lp_sz_cap; return *this; }
CTab&   CTab::operator << (const CString& _cs_cap) { this->Caption() = _cs_cap; return *this; }
CTab&   CTab::operator << (const uint16_t _tab_id) { this->Id() = _tab_id; return *this; }
CTab&   CTab::operator << (const TState& _state) { this->State() = _state; return *this; }

/////////////////////////////////////////////////////////////////////////////

CTabs:: CTabs (CControl& _ctrl) : m_ctrl(_ctrl),  m_sink(nullptr) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CTabs:: CTabs (const CTabs& _src) : CTabs(_src.m_ctrl) { *this = _src; }
CTabs::~CTabs (void) {}

/////////////////////////////////////////////////////////////////////////////
int16_t  CTabs::Active (void) const {

	for (int16_t i_ = 0; i_ < this->Count() ; i_++) {

		const CTab& tab_ = m_tabs[i_];

		if (tab_.State().IsSelected())
			return i_;
	}
	return -1;
}

err_code CTabs::Active (const int16_t _ndx) {
	_ndx;
	this->m_error << __METHOD__ << __s_ok;

	if (_ndx < 0 || _ndx >= static_cast<int16_t>(this->Count()))
		return this->m_error << DISP_E_BADINDEX;

	for (uint16_t i_ = 0; i_ < this->Count() ; i_++) {

		CTab& tab_ = m_tabs.at(i_);

		tab_.State().Modify(TState::eSelected, i_ == _ndx );
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
		if (this->Active() == -1)
			this->Active(this->Count() - 1);
#if (0)
		if (m_sink)
			m_sink->ITabEvent_OnAppend(_tab);
#endif
		((ITabEvents&)this->m_ctrl).ITabEvent_OnAppend(_tab);
	}
	catch (const ::std::bad_alloc&) { m_error << __e_no_memory; }

	return this->Error();
}

int16_t  CTabs::Count (void) const { return static_cast<int16_t>(this->m_tabs.size()); }

TError&  CTabs::Error (void) const { return this->m_error; }

void     CTabs::Events(ITabEvents* _p_snk) { this->m_sink = _p_snk; }

ITabEvents* CTabs::Events (void) const {
	return this->m_sink;
}

int16_t  CTabs::Has (const t_point& _pt) const {

	for (size_t i_ = 0; i_ < m_tabs.size(); i_++) {

		const CTab&  tab_ = m_tabs.at(i_);
		const t_rect& rc_ = tab_.Rect();

		if (::PtInRect(&rc_, _pt)) {
			return static_cast<int16_t>(i_);
		}
	}
	return -1;
}

const
CTab&    CTabs::Tab (const int16_t _ndx) const {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		static CTab inv_tab; return inv_tab;
	}
	else
		return m_tabs[_ndx];
}

CTab&    CTabs::Tab (const int16_t _ndx) {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		static CTab inv_tab; return inv_tab;
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