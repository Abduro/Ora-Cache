/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 9:42:03a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control tab items interface implementation file;
*/
#include "sfx.tabs.ext.h"
#include "sfx.tabs.ctrl.h"
#if (0)
using namespace ST_Ctrls;

/////////////////////////////////////////////////////////////////////////////

CTab:: CTab (void) : m_id(0) {}
CTab:: CTab (const CTab& _tab) : CTab() { *this = _tab; }
CTab:: CTab (LPCWSTR _lp_sz_cap) : CTab() { m_layers.Text().String() = _lp_sz_cap; }
CTab::~CTab (void) {}

/////////////////////////////////////////////////////////////////////////////

LPCWSTR    CTab::Caption(void) const { return m_layers.Text().String(); }
CStringW&  CTab::Caption(void)       { return m_layers.Text().String(); }
DWORD      CTab::Id     (void) const { return m_id   ; }
DWORD&     CTab::Id     (void)       { return m_id   ; }
const
TLayersEx& CTab::Layers (void) const { return m_layers;}
TLayersEx& CTab::Layers (void)       { return m_layers;}
const
CState&    CTab::State  (void) const { return m_state; }
CState&    CTab::State  (void)       { return m_state; }

/////////////////////////////////////////////////////////////////////////////

CTab&      CTab::operator << (const CState& _state) { this->State() = _state; return *this; }
CTab&      CTab::operator << (const CStringW& _cs_cap) { this->Caption() = _cs_cap; return *this; }
CTab&      CTab::operator << (const DWORD _tab_id) { this->Id() = _tab_id; return *this; }
CTab&      CTab::operator << (LPCWSTR _lp_sz_cap) { this->Caption() = _lp_sz_cap; return *this; }
CTab&      CTab::operator =  (const CTab& _tab) {
	this->Layers() = _tab.Layers(); *this << _tab.Caption() << _tab.Id() << _tab.State(); 
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CTabs:: CTabs (void) : m_sink(NULL) { m_error << __MODULE__ << S_OK >> __MODULE__; }
CTabs:: CTabs (const CTabs& _tabs) : CTabs() { *this = _tabs; }
CTabs::~CTabs (void) { this->Reset(); }

/////////////////////////////////////////////////////////////////////////////

const INT CTabs::Active (void) const {
	for (INT i_ = 0; i_ < this->Count() ; i_++) {
		const CTab& tab_ = m_tabs[i_];
		if (tab_.State().IsSelected())
			return i_;
	}
	return _na::e_na;
}
HRESULT   CTabs::Active (const INT _ndx) {
	m_error << __MODULE__ << S_OK;

	if (_ndx < 0 || _ndx >= static_cast<INT>(this->Count()))
		/*return*/ (m_error << DISP_E_BADINDEX);

	for (INT i_ = 0; i_ < this->Count() ; i_++) {
		CTab& tab_ = m_tabs[i_];
		tab_.State().Modify(ex_ui::controls::CState::eSelected, i_ == _ndx );
	}

	return m_error;
}
HRESULT   CTabs::Append (const CTab& _tab) {
	m_error << __MODULE__ << S_OK;

	try {
		m_tabs.push_back(_tab);
		if (m_sink)
			m_sink->ITabEvent_OnAppend(_tab);
	}
	catch (const ::std::bad_alloc&) { m_error << E_OUTOFMEMORY; }

	return m_error;
}

HRESULT   CTabs::Append (LPCWSTR _lp_sz_cap) { CTab c_tab(_lp_sz_cap); return this->Append(c_tab); }
size_t    CTabs::Count  (void) const { return m_tabs.size(); }
TErrorRef CTabs::Error  (void) const { return m_error; }
VOID      CTabs::Events (ITabEvents* _p_snk) { this->m_sink = _p_snk; }
const INT CTabs::Has    (const POINT& pt) const {

	for (size_t i_ = 0; i_ < m_tabs.size(); i_++) {
		const CTab& tab_ = m_tabs[i_];
		const RECT&  rc_ = tab_.Layers().Rect();

		if (::PtInRect(&rc_, pt)) {
			return static_cast<INT>(i_);
		}
	}
	return _na::e_na;
}
const
CTab&     CTabs::Tab    (const INT _ndx) const {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		static CTab inv_tab; return inv_tab;
	}
	else
		return m_tabs[_ndx];
}
CTab&     CTabs::Tab    (const INT _ndx) {
	if (_ndx < 0 || _ndx >= static_cast<INT>(m_tabs.size())) {
		static CTab inv_tab; return inv_tab;
	}
	else
		return m_tabs[_ndx];
}
const
TTabArray&CTabs::RawTabs(void) const { return m_tabs; }
HRESULT   CTabs::Reset  (void) {
	m_error << __MODULE__ << S_OK;
	if (m_tabs.empty() == false)
		m_tabs.clear();
	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CTabs&    CTabs::operator = (const CTabs& _tabs) {
	*this << _tabs.m_sink << _tabs.Active();
	for (size_t i_ = 0; i_ < _tabs.RawTabs().size(); i_++)
		if (FAILED(this->Append(_tabs.RawTabs()[i_])))
			break;
	return *this ;
}

CTabs&    CTabs::operator <<(const CTab& _tab) { this->Append(_tab); return *this; }
CTabs&    CTabs::operator <<(const DWORD _active_ndx) { this->Active(_active_ndx); return *this; }
CTabs&    CTabs::operator <<(ITabEvents* _p_snk) { this->Events(_p_snk); return *this; }
CTabs&    CTabs::operator <<(LPCWSTR _lp_sz_cap)  { this->Append(_lp_sz_cap); return *this; }
#endif