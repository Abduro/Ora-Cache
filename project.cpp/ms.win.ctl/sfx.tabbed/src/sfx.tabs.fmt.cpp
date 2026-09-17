/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Aug-2020 at 5:30:33a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Sfx tab control format interface implementation file.
*/
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::format;

#pragma region cls::CBorder{}

using CFmtBorder = format::CBorder;

CFmtBorder:: CBorder (void) : m_thick(1) {} CFmtBorder::CBorder (const CFmtBorder& _src) : CFmtBorder() { *this = _src; }
CFmtBorder::~CBorder (void) {}

const
CColor&  CFmtBorder::Color (void) const { return this->m_color; }
CColor&  CFmtBorder::Color (void)       { return this->m_color; }

uint8_t  CFmtBorder::Thickness (void) const { return this->m_thick; }
bool     CFmtBorder::Thickness (const uint8_t _value) {
	const bool b_changed = this->Thickness() != _value; if (b_changed) this->m_thick = _value; return b_changed;
}

CFmtBorder& CFmtBorder::operator = (const CFmtBorder& _src) { *this << _src.Color() << _src.Thickness(); return *this; }
CFmtBorder& CFmtBorder::operator <<(const CColor& _clr) { this->Color() = _clr; return *this; }
CFmtBorder& CFmtBorder::operator <<(uint8_t _u_thick) { this->Thickness(_u_thick); return *this; }

#pragma endregion
#pragma region cls::CColor{}

rgb_color CColor::Get (const TStateValue _e_state) const {
	_e_state;
	using namespace ex_ui::theme;
	rgb_color clr = (rgb_color)0;

	switch (_e_state) {
	case TStateValue::eDisabled : clr = Get_current().Form().Border().States().Disabled().Color(); break;
	case TStateValue::eNormal   : clr = Get_current().Form().Border().States().Normal().Color();   break;
	case TStateValue::eSelected : clr = Get_current().Form().Border().States().Selected().Color(); break;
	default:;
	}
	return clr;
}

rgb_color CColor::Disabled (void) const { return this->Get(TStateValue::eDisabled); }
rgb_color CColor::Normal   (void) const { return this->Get(TStateValue::eNormal); }
rgb_color CColor::Selected (void) const { return this->Get(TStateValue::eSelected); }

#pragma endregion
#pragma region cls::CFormat{}

CFormat:: CFormat (CControl& _ctrl) : m_ctrl(_ctrl) { this->Default(); }
CFormat::~CFormat (void) {}

const
format::CBorder&  CFormat::Border (void) const { return this->m_border; }

void CFormat::Default (void) {

	this->m_ctrl.Borders() << (uint8_t)1;
	this->m_ctrl.Borders().Base() << TRgbQuad(this->Border().Color().Normal());

	TBase::Bkgnd().Solid() << ex_ui::theme::Get_current().Form().Bkgnd().States().Normal().Color();

	static _pc_sz pc_sz_fnt_names[] = {
		_T("Pirulen Rg"), _T("Verdana"), _T("Age Normal"), _T("Trebuchet MS")
		//       0               1               2                 3
	};

	TBase::Font().Family(pc_sz_fnt_names[0]); // the exact name is very important, otherwise the other system font will be created (default for GUI);
	TBase::Font().Fore() = this->Border().Color().Selected();
	TBase::Font().Size() = -12;
	TBase::Font().Options() += TFontOpts::eExactSize;
}

#pragma endregion
#pragma region cls::CPage{}

using CFmtPage = format::CPage;

CFmtPage::CPage (void) {}
CFmtPage::CPage (const CFmtPage& _src) : CFmtPage() { *this = _src; }

const
CFmtBorder& CFmtPage::Border (void) const { return this->m_border; }
CFmtBorder& CFmtPage::Border (void)       { return this->m_border; }

CFmtPage& CFmtPage::operator = (const CFmtPage& _src) { *this << _src.Border(); return *this; }
CFmtPage& CFmtPage::operator <<(const CFmtBorder& _border) { this->Border() = _border; return *this; }

#pragma endregion