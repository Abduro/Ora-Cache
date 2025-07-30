/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 1:00:18p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control format interface implementation file.
*/
#include "sfx.status.fmt.h"
#include "sfx.status.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::status;
using namespace ex_ui::controls::sfx::status::format;

#include "uix.theme.h"
#include "uix.theme.named.h"

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CControl& _ctrl) : m_ctrl(_ctrl) { this->Default(); }
CFormat::~CFormat (void) {}

/////////////////////////////////////////////////////////////////////////////

void CFormat::Default (void) {

	CBorder& top = this->m_ctrl.Borders().Top();
	top.Thickness(1);
#if (1)
//	top.Color() << shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_border, TThemeState::e_default);
	top.Color() << ex_ui::theme::Get_current().Form().Border().States().Normal().Color();
#else
	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow);
	top.Color() = TRgbQuad(set_.Light());
#endif
//	TBase::Bkgnd().Solid() << shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back);
	TBase::Bkgnd().Solid() << ex_ui::theme::Get_current().Form().Bkgnd().States().Normal().Color();
}

#if (0)

CPane:: CPane (void) {}
CPane:: CPane (const CPane& _ref) : CPane () { *this = _ref; }
CPane::~CPane (void) {} 

/////////////////////////////////////////////////////////////////////////////
const
CBorder& CPane::Border (void) const { return m_border; }
CBorder& CPane::Border (void)       { return m_border; }

/////////////////////////////////////////////////////////////////////////////

CPane&   CPane::operator = (const CPane& _ref) { *this << _ref.Border(); return *this; }
CPane&   CPane::operator <<(const CBorder& _border) { this->Border() = _border; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanes:: CPanes (void) {}
CPanes:: CPanes (const CPanes& _ref) : CPanes() { *this = _ref; }
CPanes::~CPanes (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CPane&   CPanes::Normal (void) const { return m_normal; }
CPane&   CPanes::Normal (void)       { return m_normal; }

/////////////////////////////////////////////////////////////////////////////

CPanes&  CPanes::operator = (const CPanes& _ref) { this->Normal() = _ref.Normal(); return *this; }

/////////////////////////////////////////////////////////////////////////////

CStatus:: CStatus (void) : m_img_res(0) {}
CStatus:: CStatus (const CStatus& _ref) : CStatus() { *this = _ref; }
CStatus::~CStatus (void) {}

/////////////////////////////////////////////////////////////////////////////

DWORD     CStatus::Images  (void) const { return m_img_res; }
DWORD&    CStatus::Images  (void)       { return m_img_res; }
const
CPanes&   CStatus::Panes (void) const { return m_panes; }
CPanes&   CStatus::Panes (void)       { return m_panes; }

/////////////////////////////////////////////////////////////////////////////

CStatus&  CStatus::operator = (const CStatus& _ref) {
	(TFormat&)*this = (TFormat&)_ref; *this << _ref.Panes() << _ref.Images(); return *this;
}
CStatus&  CStatus::operator <<(const CPanes& _panes) { this->Panes() = _panes; return *this; }
CStatus&  CStatus::operator <<(const DWORD _img_res) { this->Images() = _img_res; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSymantec_NA_Sta:: CSymantec_NA_Sta (void) : TBase() {

	TBase::Borders().Top().Color ().Create(RGB(42, 45, 47));
	TBase::Borders().Top().Shadow().Create(RGB(92, 95, 97));
	TBase::Borders().Top().Thickness() = 1;

	TBase::Bkgnd().Solid().Create(RGB(61,  61,  61));

	TBase::Bkgnd().Gradient().c0().Create(RGB(42,  42,  42));
	TBase::Bkgnd().Gradient().c1().Create(RGB(84,  84,  84));

	TBase::Font ().Fore() = RGB(200, 200, 200);
	TBase::Font ().Size() = 18;

	TBase::Bkgnd().Gradient().c0().Create(RGB(61,  61,  61));
	TBase::Bkgnd().Gradient().c1().Create(RGB(61,  61,  61));
}
CSymantec_NA_Sta::~CSymantec_NA_Sta (void) {}

/////////////////////////////////////////////////////////////////////////////

CWhitespread_Sta:: CWhitespread_Sta (void) : TBase() {

	TBase::Bkgnd().Solid().Create(RGB(244, 244, 244));
	TBase::Borders().Top().Thickness() = 1;
	TBase::Borders().Top().Color().Create(RGB( 49,  145, 203));

	TBase::Font ().Fore() = RGB(61, 61, 61);
	TBase::Font ().Size() = 18;
}
CWhitespread_Sta::~CWhitespread_Sta (void) {}
#endif