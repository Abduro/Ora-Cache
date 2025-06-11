/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Aug-2020 at 5:30:33a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Sfx tab control format interface implementation file.
*/
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::format;

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CControl& _ctrl) : m_ctrl(_ctrl) { this->Default(); }
CFormat::~CFormat (void) {}

/////////////////////////////////////////////////////////////////////////////

void CFormat::Default (void) {

	this->m_ctrl.Borders() << (uint8_t)1;
	this->m_ctrl.Borders().Base() << TRgbQuad(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_border));
}
#if(0)
using namespace ST_Ctrls::format;

/////////////////////////////////////////////////////////////////////////////

CTab_Base:: CTab_Base (void) : TFmtBase() {}
CTab_Base:: CTab_Base (const CTab_Base& _ref) : CTab_Base() { *this = _ref; }
CTab_Base::~CTab_Base (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBorders&   CTab_Base::Borders (void) const { return m_borders; }
CBorders&   CTab_Base::Borders (void)       { return m_borders; }

/////////////////////////////////////////////////////////////////////////////

CTab_Base&  CTab_Base::operator = (const CTab_Base& _ref) { *this << _ref.Borders(); (TFmtBase&)*this = (TFmtBase&)_ref; return *this; }
CTab_Base&  CTab_Base::operator <<(const CBorders& _brds) { this->Borders() = _brds; return *this; }

/////////////////////////////////////////////////////////////////////////////

CTab:: CTab(void) : TTab() {}
CTab:: CTab(const CTab& _ref) : CTab() { *this = _ref; }
CTab::~CTab(void) {}

/////////////////////////////////////////////////////////////////////////////

CTab&  CTab::operator = (const CTab& _fmt) {
	((TTab&)*this) = (TTab&)_fmt;
	return  *this;
}

/////////////////////////////////////////////////////////////////////////////

CTabs:: CTabs (void) {}
CTabs:: CTabs (const CTabs& _ref) : CTabs() { *this = _ref; }
CTabs::~CTabs (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CTab&   CTabs::Active (void) const { return m_active; }
CTab&   CTabs::Active (void)       { return m_active; }
const
CTab&   CTabs::Disabled (void) const { return m_disabled; }
CTab&   CTabs::Disabled (void)       { return m_disabled; }
const
CTab&   CTabs::Normal (void) const { return m_normal; }
CTab&   CTabs::Normal (void)       { return m_normal; }

/////////////////////////////////////////////////////////////////////////////

CTabs&  CTabs::operator = (const CTabs& _ref) {
	this->Active() = _ref.Active();
	this->Disabled() = _ref.Disabled();
	this->Normal() = _ref.Normal();

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CTabFormat:: CTabFormat (void) : TFormat() {}
CTabFormat:: CTabFormat (const CTabFormat& _ref) : CTabFormat() { *this = _ref; }
CTabFormat::~CTabFormat (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBorders&   CTabFormat::Borders (void) const { return m_borders; }
CBorders&   CTabFormat::Borders (void)       { return m_borders; }
const
CTabs&      CTabFormat::Tabs  (void) const { return m_tabs; }
CTabs&      CTabFormat::Tabs  (void)       { return m_tabs; }

/////////////////////////////////////////////////////////////////////////////

CTabFormat& CTabFormat::operator = (const CTabFormat& _ref) {
	*this << _ref.Borders() << _ref.Tabs(); (TFormat&)*this = (TFormat&)_ref;
	return *this;
}
CTabFormat& CTabFormat::operator <<(const CBorders& _borders) { this->Borders() = _borders; return *this; }
CTabFormat& CTabFormat::operator <<(const CTabs& _tabs) { this->Tabs() = _tabs; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSymantec_NA_Tab:: CSymantec_NA_Tab (void)  : TBase() {

	TBase::Bkgnd().Solid().Create(RGB(61,  61,  61));
	TBase::Bkgnd().Gradient().c0().Create(RGB(42,  42,  42));
	TBase::Bkgnd().Gradient().c1().Create(RGB(84,  84,  84));

	TBase::Borders().Color(RGB(42, 45, 47));
	TBase::Borders().Thickness(  1);

	TBase::Tabs().Normal().Font().Fore() = RGB(200, 200, 200);
	TBase::Tabs().Normal().Bkgnd().Gradient().c0().Create(RGB(61,  61,  61));
	TBase::Tabs().Normal().Bkgnd().Gradient().c1().Create(RGB(61,  61,  61));  TBase::Tabs().Disabled() = TBase::Tabs().Normal();

	TBase::Tabs().Disabled().Font().Fore() = RGB(255, 255, 128);

	TBase::Tabs().Active().Font().Fore() = RGB(200, 200, 200);
	TBase::Tabs().Active().Bkgnd().Gradient().c0().Create(RGB(255, 215, 100));
	TBase::Tabs().Active().Bkgnd().Gradient().c1().Create(RGB(249, 178, 000));
}

CSymantec_NA_Tab::~CSymantec_NA_Tab (void) {}

/////////////////////////////////////////////////////////////////////////////

CWhitespread_Tab:: CWhitespread_Tab(void) : TBase () {

	TBase::Bkgnd().Solid().Create(RGB(244, 244, 244));
	TBase::Bkgnd().Gradient().c0().Create(RGB(244,  244,  244));
	TBase::Bkgnd().Gradient().c1().Create(RGB(244,  244,  244));

	TBase::Borders().Color(RGB(  1, 115, 116));
	TBase::Borders().Thickness(  1);
	TBase::Borders().Top().Thickness() = 1;
	TBase::Borders().Top().Color().Create(RGB( 49,  145, 203));

	TBase::Font ().Fore() = RGB(61, 61, 61);
	TBase::Font ().Size() = 18;

	TBase::Tabs().Normal().Font ().Fore() = RGB(200, 200, 200);
	TBase::Tabs().Normal().Bkgnd().Gradient().c0().Create(RGB( 42, 158, 245));
	TBase::Tabs().Normal().Bkgnd().Gradient().c1().Create(RGB( 17, 103, 178));  TBase::Tabs().Disabled() = TBase::Tabs().Normal();

	TBase::Tabs().Active().Font ().Fore() = RGB(  0,   0,   0);
	TBase::Tabs().Active().Bkgnd().Gradient().c0().Create(RGB(  3, 218, 198));
	TBase::Tabs().Active().Bkgnd().Gradient().c1().Create(RGB(  1, 115, 116));
}
CWhitespread_Tab::~CWhitespread_Tab(void) {}
#endif