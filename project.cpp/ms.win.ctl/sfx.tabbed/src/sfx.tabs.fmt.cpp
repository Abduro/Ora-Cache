/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Aug-2020 at 5:30:33a, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Sfx tab control format interface implementation file.
*/
#include "sfx.tabs.fmt.h"
#include "sfx.tabs.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::format;

/////////////////////////////////////////////////////////////////////////////

format::CBorder:: CBorder (void) {}
format::CBorder::~CBorder (void) {}

const
CColor&  format::CBorder::Color (void) const { return this->m_color; }
CColor&  format::CBorder::Color (void)       { return this->m_color; }

CColor:: CColor (void) {}
CColor::~CColor (void) {}

/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CControl& _ctrl) : m_ctrl(_ctrl) { this->Default(); }
CFormat::~CFormat (void) {}

/////////////////////////////////////////////////////////////////////////////
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