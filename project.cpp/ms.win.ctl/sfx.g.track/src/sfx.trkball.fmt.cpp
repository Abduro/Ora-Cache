/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:48:26.839,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control format interface implementation file;
*/
#include "sfx.trkball.fmt.h"
#include "sfx.trkball.ctrl.h"

using namespace ex_ui::controls::sfx::track;
using namespace ex_ui::controls::sfx::track::format;

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

const
format::CBorder&  CFormat::Border (void) const { return this->m_border; }

void CFormat::Default (void) {
	this->m_ctrl.Borders() << (uint8_t)1;
	this->m_ctrl.Borders().Base() << TRgbQuad(this->Border().Color().Normal());

	TBase::Bkgnd().Solid() << ex_ui::theme::Get_current().Form().Bkgnd().States().Normal().Color();
}