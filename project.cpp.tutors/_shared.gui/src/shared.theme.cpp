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

using e_element = route::CTheme::e_element;

#pragma region str::s_flt_clr{}

s_flt_clr::s_flt_clr (const float _r, const float _g,  const float _b, const float _a) : _red(_r), _green(_g), _blue(_b), _alpha(_a) {}
s_flt_clr::s_flt_clr (const s_flt_clr& _src) : s_flt_clr() { *this = _src; }

s_flt_clr& s_flt_clr::operator = (const s_flt_clr& _src) {
	this->_red = _src._red; this->_green = _src._green; this->_blue = _src._blue; this->_alpha = _src._alpha;
	return *this;
}

s_flt_clr::operator f_clr_t (void) const { return {this->_red, this->_green, this->_blue, this->_alpha}; }

CString s_flt_clr::To_str (void) const {
	static _pc_sz p_clr_pat = _T("{r=%.7f;g=%.7f;b=%.7f;a=%.7f}");
	CString cs_out; cs_out.Format(p_clr_pat, this->_red, this->_green, this->_blue, this->_alpha);
	return  cs_out;
}

#pragma endregion
namespace shared { namespace gui { namespace theme {

CTheme::CTheme (void) : m_bkgnd(4, 0.0f), m_is_read(false) {}

const rgb_color  CTheme::Bkgnd_rgb (void) const { return (rgb_color)CHex((_pc_sz)Get_registry().Value(e_element::e_bkgnd)); }
const s_flt_clr& CTheme::Bkgnd_flt (void) const {

	if (this->m_is_read)
		return this->m_bkgnd;

	const rgb_color clr = this->Bkgnd_rgb();

	this->m_bkgnd._red   = CConvert::CConvert::ToFloat(get_r_value(clr));
	this->m_bkgnd._green = CConvert::CConvert::ToFloat(get_g_value(clr));
	this->m_bkgnd._blue  = CConvert::CConvert::ToFloat(get_b_value(clr));
	this->m_bkgnd._alpha = CConvert::CConvert::ToFloat(get_a_value(clr));
	this->m_bkgnd._alpha = 1.0f; // it is not necessary because it eaquals to 0 always;
	
	this->m_is_read = true;
	return this->m_bkgnd;
}

const rgb_color CTheme::Border (void) const {
	return (rgb_color)CHex((_pc_sz)Get_registry().Value(e_element::e_border));
}

}}}

TTheme& ::Get_theme (void) {
	static TTheme theme; // a constructor of this class may be called twice, because it is not plain data, but user defined class;
	return theme;
}