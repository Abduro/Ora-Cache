/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Nov-2025 at 22:56:47.613, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared custom theme interface implementation file;
*/
#include "shared.theme.h"
#include "sys.registry.h"
#include "color.rgb.h"

using namespace shared::gui::theme;
using namespace shared::sys_core::storage;
using namespace ex_ui::color::rgb;

using e_element = CReg_router::CTheme::e_element;

CTheme::CTheme (void) : m_bkgnd(4, 0.0f) {}

const rgb_color CTheme::Bkgnd_rgb (void) const { return (rgb_color)CHex((_pc_sz)Get_registry().Value(e_element::e_bkgnd)); }
const v_color&  CTheme::Bkgnd_flt (void) const {

	const rgb_color clr = this->Bkgnd_rgb();

	if (0 < this->m_bkgnd.size()) {
		this->m_bkgnd.at(0) = CConvert::CConvert::ToFloat(get_r_value(clr));
		if (1 < this->m_bkgnd.size()) {
			this->m_bkgnd.at(1) = CConvert::CConvert::ToFloat(get_g_value(clr));
			if (2 < this->m_bkgnd.size()) {
				this->m_bkgnd.at(2) = CConvert::CConvert::ToFloat(get_b_value(clr));
				if (3 < this->m_bkgnd.size()) {
					this->m_bkgnd.at(3) = CConvert::CConvert::ToFloat(get_a_value(clr)); // it is not necessary because it eaquals to 0 always;
					this->m_bkgnd.at(3) = 1.0f;
	}	}	}	}
	return this->m_bkgnd;
}

const rgb_color CTheme::Border (void) const {
	return (rgb_color)CHex((_pc_sz)Get_registry().Value(e_element::e_border));
}

TTheme&  ::Get_theme (void) {
	static TTheme theme;
	return theme;
}