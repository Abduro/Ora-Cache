/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2020 at 6:37:00a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack shared status bar control panel interface implementation file.
*/
#include "sfx.status.ext.h"

namespace ex_ui { namespace controls { namespace sfx { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

#if (0)
using namespace ST_Ctrls;

/////////////////////////////////////////////////////////////////////////////

TPanelChild:: CPanel_Child (void) : m_child (NULL) { m_style += SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER; }
TPanelChild:: CPanel_Child (const TPanelChild& _ref) : TPanelChild() { *this = _ref; }
TPanelChild::~CPanel_Child (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TAlign& TPanelChild::Align (void) const { return m_align; }
TAlign& TPanelChild::Align (void)       { return m_align; }
HWND    TPanelChild::Handle(void) const { return m_child; }
HWND&   TPanelChild::Handle(void)       { return m_child; }
bool    TPanelChild::Is    (void) const { return(m_child != NULL && !!::IsWindow(m_child)); }
const
CStyle& TPanelChild::Style (void) const { return m_style; }
CStyle& TPanelChild::Style (void)       { return m_style; }

/////////////////////////////////////////////////////////////////////////////

TPanelChild&   TPanelChild::operator = (const TPanelChild& _ref) { *this << _ref.Align() << _ref.Handle() << _ref.Style();  return *this; }
TPanelChild&   TPanelChild::operator <<(const CAlign& _align) { this->Align() = _align; return *this; }
TPanelChild&   TPanelChild::operator <<(const CStyle& _style) { this->Style() = _style; return *this; }
TPanelChild&   TPanelChild::operator <<(const HWND  _h_child) { this->Handle() = _h_child; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanel:: CPanel (void) : m_id (0), m_img_ndx(-1) {}
CPanel:: CPanel (const CPanel& _ref) : CPanel() { *this = _ref; }
CPanel:: CPanel (const DWORD _id, LPCWSTR _lp_sz_text) : CPanel() { *this << _id << _lp_sz_text; }
CPanel::~CPanel (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBorders_Ex& CPanel::Borders (void) const { return m_borders; }
CBorders_Ex& CPanel::Borders (void)       { return m_borders; }
const
TPanelChild& CPanel::Child   (void) const { return m_child; }
TPanelChild& CPanel::Child   (void)       { return m_child; }
DWORD        CPanel::ID      (void) const { return m_id; }
DWORD&       CPanel::ID      (void)       { return m_id; }

INT         CPanel::Image_Ndx(void) const { return m_img_ndx; }
INT&        CPanel::Image_Ndx(void)       { return m_img_ndx; }
const
TPanelLay&   CPanel::Layout  (void) const { return m_layout; }
TPanelLay&   CPanel::Layout  (void)       { return m_layout; }

LPCWSTR      CPanel::Text (void) const { return m_layout.Text().String(); }
CStringW&    CPanel::Text (void)       { return m_layout.Text().String(); }

/////////////////////////////////////////////////////////////////////////////

CPanel&    CPanel::operator = (const CPanel& _ref) {
	this->m_layout = _ref.m_layout; *this << _ref.Text() << _ref.ID() << _ref.Borders() << _ref.Child(); this->Image_Ndx() = _ref.Image_Ndx();
	return *this;
}
CPanel&    CPanel::operator <<(const CBorders_Ex& _borders) { this->Borders() = _borders; return *this; }
CPanel&    CPanel::operator <<(const TPanelChild& _child) { this->Child() = _child; return *this; }
CPanel&    CPanel::operator <<(const CStringW& _cs_text) { this->Text() = _cs_text; return *this; }
CPanel&    CPanel::operator <<(const DWORD _panel_id) { this->ID() = _panel_id; return *this; }
CPanel&    CPanel::operator <<(LPCWSTR _lp_sz_text) { this->Text() = _lp_sz_text; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanels:: CPanels (void) { m_error << __MODULE__ << S_OK >> __MODULE__; }
CPanels:: CPanels (const CPanels& _ref) : CPanels() { *this = _ref; }
CPanels::~CPanels (void) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT   CPanels::Add   (const CPanel& _pan) {
	m_error << __MODULE__ << S_OK;
	try {
		m_panels.push_back(_pan);
	}
	catch (const ::std::bad_alloc&) { m_error << E_OUTOFMEMORY; }
	return m_error;
}

HRESULT   CPanels::Add   (const DWORD _id, LPCWSTR _lp_sz_text) {
	CPanel panel(_id, _lp_sz_text);
	return this->Add(panel);
}

UINT      CPanels::Count (void) const { return static_cast<UINT>(m_panels.size()); }

INT       CPanels::Has   (const DWORD _id) const {
	for (size_t i_ =0; i_ < m_panels.size(); i_++)
		if (m_panels[i_].ID() == _id)
			return static_cast<INT>(i_);

	return CPanels::e_na;
}

TErrorRef CPanels::Error (void) const { return m_error ; }

const
CPanel&   CPanels::Panel (const DWORD _ndx) const { if (m_panels.empty() || _ndx >= m_panels.size()) { static CPanel na_; return na_; } else return m_panels[_ndx]; }
CPanel&   CPanels::Panel (const DWORD _ndx)       { if (m_panels.empty() || _ndx >= m_panels.size()) { static CPanel na_; return na_; } else return m_panels[_ndx]; }

const
TPanels&  CPanels::Raw   (void) const { return m_panels; }
TPanels&  CPanels::Raw   (void)       { return m_panels; }

HRESULT   CPanels::Remove(const CPanel& _pan) { return this->Remove(_pan.ID());
}
HRESULT   CPanels::Remove(const DWORD _id) {
	m_error << __MODULE__ << S_OK;

	const INT n_ndx = this->Has(_id);
	if (CPanels::e_na == n_ndx)
		return (m_error << TYPE_E_ELEMENTNOTFOUND);

	m_panels.erase(m_panels.begin() + n_ndx);

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CPanels&  CPanels::operator = (const CPanels& _ref) {
	for (size_t i_ = 0; i_ < _ref.Raw().size(); i_++) {
		if (FAILED(this->Add(_ref.Raw()[i_])))
			break;
	}
	return *this;
}

CPanels&  CPanels::operator+= (const CPanel& _pan) { this->Add(_pan); return *this; }
CPanels&  CPanels::operator-= (const CPanel& _pan) { this->Remove(_pan); return *this; }
CPanels&  CPanels::operator-= (const DWORD _id) { this->Remove(_id);  return *this; }
bool      CPanels::operator== (const DWORD _id) { return (this->Has(_id) != CPanels::e_na); }

/////////////////////////////////////////////////////////////////////////////

INT CPanels::operator << (const DWORD _id) const { return this->Has(_id); }
#endif