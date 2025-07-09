/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 8:37:53.978 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack custom color theme project on 07-Jun-2025 at 18:49:21.514, UTC+4, Batumi, Saturday;
*/
#include "uix.theme.h"
#include "sys.shell.dwm.h"

using namespace shared::sys_core::shell;

using namespace ex_ui::theme;
using namespace ex_ui::theme::colors;

using CTheme = ex_ui::theme::CTheme;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace theme { namespace colors {
#if defined(_DEBUG)
CString  CTheme_Printer::Out (const CTheme_Element& _element) {
	_element;
	CString cs_out;
	switch (_element) {
	case CTheme_Element::e_back  : cs_out = _T("Back"); break;
	case CTheme_Element::e_fore  : cs_out = _T("Fore"); break;
	case CTheme_Element::e_border: cs_out = _T("Border"); break;
	default:
		cs_out = _T("e_none");
	}
	return  cs_out;
}

CString  CTheme_Printer::Out (const CTheme_Palette& _palette) {
	_palette;
	CString cs_out;
	switch (_palette) {
	case CTheme_Palette::e_dark  : cs_out = _T("Dark"); break;
	case CTheme_Palette::e_light : cs_out = _T("Light"); break;
	default:
		cs_out = _T("e_none");
	}
	return  cs_out;
}

CString  CTheme_Printer::Out (const CTheme_Part& _part) {
	_part;
	CString cs_out;
	switch (_part) {
	case CTheme_Part::e_form    : cs_out = _T("Form" );   break;
	case CTheme_Part::e_panel   : cs_out = _T("Panel");   break;
	case CTheme_Part::e_edit    : cs_out = _T("Edit" );   break;
	case CTheme_Part::e_label   : cs_out = _T("Label");   break;
	case CTheme_Part::e_caption : cs_out = _T("Caption"); break;
	case CTheme_Part::e_button  : cs_out = _T("Button");  break;
	default:
		cs_out = _T("e_none");
	}
	return  cs_out;
}

CString  CTheme_Printer::Out (const CTheme_State& _state) {
	_state;
	CString cs_out;
	switch (_state) {
	case CTheme_State::e_normal   : cs_out = _T("Normal"  ); break;
	case CTheme_State::e_disabled : cs_out = _T("Disabled"); break;
	case CTheme_State::e_hovered  : cs_out = _T("Hovered" ); break;
	case CTheme_State::e_selected : cs_out = _T("Selected"); break;
	default:
		cs_out = _T("Default");
	}
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CColor_Marker:: CColor_Marker (void) : m_palette(TThemePalette::e_none), m_ui_part(TThemePart::e_none), m_ui_state(TThemeState::e_default) {}
CColor_Marker:: CColor_Marker (const CColor_Marker& _ref) : CColor_Marker() { *this = _ref; }
CColor_Marker:: CColor_Marker (
	const CTheme_Palette _palette, const CTheme_Part _part, const CTheme_Element _element, const CTheme_State _state) : CColor_Marker() {
	*this << _palette << _part << _element << _state;
}
CColor_Marker::~CColor_Marker (void) {}

/////////////////////////////////////////////////////////////////////////////

const CTheme_Element CColor_Marker::Element (void) const { return m_element ; } CTheme_Element& CColor_Marker::Element (void) { return m_element ; }
const CTheme_Palette CColor_Marker::Palette (void) const { return m_palette ; } CTheme_Palette& CColor_Marker::Palette (void) { return m_palette ; }
const CTheme_Part    CColor_Marker::Part    (void) const { return m_ui_part ; } CTheme_Part&    CColor_Marker::Part    (void) { return m_ui_part ; }
const CTheme_State   CColor_Marker::State   (void) const { return m_ui_state; } CTheme_State&   CColor_Marker::State   (void) { return m_ui_state; }

/////////////////////////////////////////////////////////////////////////////

const bool CColor_Marker::Is (void) const {
	return !(TThemePalette::e_none == m_palette || TThemePart::e_none == m_ui_part || TThemeElement::e_none == m_element);
}

#if defined(_DEBUG)
CString    CColor_Marker::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {pallete=%s;part=%s;element=%s;state=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {pallete=%s;part=%s;element=%s;state=%s}");
	static _pc_sz pc_sz_pat_r = _T("{pallete=%s;part=%s;element=%s;state=%s}");

	CString cs_out;

	if (e_print::e_all == _e_opt) {
		cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			(_pc_sz) TPrint::Out(this->Palette()), (_pc_sz) TPrint::Out(this->Part()),
			(_pc_sz) TPrint::Out(this->Element()), (_pc_sz) TPrint::Out(this->State())
		);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
			(_pc_sz) TPrint::Out(this->Palette()), (_pc_sz) TPrint::Out(this->Part()),
			(_pc_sz) TPrint::Out(this->Element()), (_pc_sz) TPrint::Out(this->State())
		);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r,
			(_pc_sz) TPrint::Out(this->Palette()), (_pc_sz) TPrint::Out(this->Part()),
			(_pc_sz) TPrint::Out(this->Element()), (_pc_sz) TPrint::Out(this->State())
		);
	}
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CColor_Marker& CColor_Marker::operator = (const CColor_Marker& _ref) { *this << _ref.Palette() << _ref.Part() << _ref.State() << _ref.Element(); return *this; }
CColor_Marker& CColor_Marker::operator <<(const CTheme_Element _element) { this->m_element = _element; return *this; }
CColor_Marker& CColor_Marker::operator <<(const CTheme_Palette _palette) { this->m_palette = _palette; return *this; }
CColor_Marker& CColor_Marker::operator <<(const CTheme_Part _part) { this->m_ui_part = _part; return *this; }
CColor_Marker& CColor_Marker::operator <<(const CTheme_State _state) { this->m_ui_state = _state; return *this; }

/////////////////////////////////////////////////////////////////////////////

CColor_Matrix:: CColor_Matrix (void) {
	// ToDo: of course, this is not the best approach to defining theme colors in this way;
	//       it would be better to use XML or JSON files as the source of theme colors;
	m_palettes = {
	{
		TThemePalette::e_dark, {
			{ TThemePart::e_button , {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  70,  70,  70) }, { TThemeState::e_hovered , RGB( 102,  90,  71) }, { TThemeState::e_selected, RGB(  70,  70,  70) }} },
			                          { TThemeElement::e_border, {{ TThemeState::e_default , RGB( 115, 115, 115) }, { TThemeState::e_hovered , RGB( 229, 183,  66) },
			                                                      { TThemeState::e_disabled, RGB( 115, 115, 115) }, { TThemeState::e_selected, RGB( 229, 183,  66) }} },
			                          { TThemeElement::e_fore  , {{ TThemeState::e_default , RGB( 230, 230, 230) }, { TThemeState::e_hovered , RGB( 229, 183,  66) },
			                                                      { TThemeState::e_disabled, RGB( 115, 115, 115) }, { TThemeState::e_selected, RGB( 183, 163,  66) }} }}},
			{ TThemePart::e_caption, {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  70,  70,  70) }} },
			                          { TThemeElement::e_fore  , {{ TThemeState::e_default , RGB( 230, 230, 230) }} } }},
			{ TThemePart::e_edit   , {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  70,  70,  70) }, { TThemeState::e_disabled, RGB(  70,  70,  70) }} },
			                          { TThemeElement::e_border, {{ TThemeState::e_default , RGB( 115, 115, 115) }, { TThemeState::e_disabled, RGB( 115, 115, 115) }} },
			                          { TThemeElement::e_fore  , {{ TThemeState::e_default , RGB( 230, 230, 230) }, { TThemeState::e_disabled, RGB( 230, 230, 230) }} }}},
			{ TThemePart::e_form   , {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  39,  39,  39) }} },
			                          { TThemeElement::e_border, {{ TThemeState::e_default , RGB(  61,  61,  61) }, { TThemeState::e_selected, RGB( 229, 183,  66) }} },
			                          { TThemeElement::e_fore  , {{ TThemeState::e_default , RGB( 230, 230, 230) }} } }},
			{ TThemePart::e_label  , {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  70,  70,  70) }} },
			                          { TThemeElement::e_fore  , {{ TThemeState::e_default , RGB( 230, 230, 230) }} } }},
			{ TThemePart::e_panel  , {{ TThemeElement::e_back  , {{ TThemeState::e_default , RGB(  61,  61,  61) }} },
			                          { TThemeElement::e_border, {{ TThemeState::e_default , RGB( 229, 183,  66) }, { TThemeState::e_disabled, RGB( 115, 115, 115) }} }}}//,
		//	{ TThemePart:: , {{ TThemeElement:: , {{ TThemeState:: , RGB()}} }} }
		}
	},
	{
		TThemePalette::e_light, {
			{ TThemePart::e_form   , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB( 249, 249, 249) }} }
			}}
		}
	}};
}
CColor_Matrix:: CColor_Matrix (const CColor_Matrix& _ref) : CColor_Matrix() { *this = _ref; }
CColor_Matrix::~CColor_Matrix (void) {}

/////////////////////////////////////////////////////////////////////////////

#ifndef __clr_none
#define __clr_none 0xFFFFFFFFL
#endif

CColor_Matrix&  CColor_Matrix::operator = (const CColor_Matrix& _ref) { this->m_palettes = _ref.m_palettes; return *this; }
const COLORREF  CColor_Matrix::operator <<(const CColor_Marker& _marker) const {

	COLORREF clr_result = __clr_none;
	if (_marker.Is()) {
		TColor_Palette::const_iterator it_palette = m_palettes.find(_marker.Palette());
		if (it_palette != m_palettes.end() ) {
			TColor_Part::const_iterator it_part = it_palette->second.find(_marker.Part());
			if (it_part != it_palette->second.end()) {
				TColor_Element::const_iterator it_element = it_part->second.find(_marker.Element());
				if (it_element != it_part->second.end()) {
					TColor_State::const_iterator it_state = it_element->second.find(_marker.State());
					if (it_state != it_element->second.end()) {
						clr_result = it_state->second;
	}	}	}	}	}

	return clr_result;
}

}}}

namespace ex_ui { namespace theme {
/////////////////////////////////////////////////////////////////////////////

bool CClr_Simple::Is_light(const clr_type _clr) {
	return (((5 * get_g_value(_clr)) + (2 * get_r_value(_clr)) + get_b_value(_clr)) > (8 * 128));
}

/////////////////////////////////////////////////////////////////////////////

CTheme:: CTheme (void) {
	if (CTheme::IsDark())
		m_current = TThemePalette::e_dark;
	else
		m_current = TThemePalette::e_light;
}
CTheme:: CTheme (const CTheme& _ref) : TTheme() { *this = _ref; }
CTheme::~CTheme (void) {}

/////////////////////////////////////////////////////////////////////////////

const TColorMatrix&  CTheme::Matrix  (void) const { return m_clr_mtx; }
const TThemePalette  CTheme::Palette (void) const { return m_current; }

/////////////////////////////////////////////////////////////////////////////

#ifndef rgb_value_max
#define rgb_value_max (0xff)
#endif

clr_type CTheme::Get (const TThemePart _part, const TThemeElement _el, const TThemeState _state, clr_value _alpha) const {

	clr_type clr_result = (const clr_type)(m_clr_mtx << TColorMarker(this->Palette(), _part, _el, _state));

	if (/*rgb_value_max*/0x0 != _alpha) {
		clr_result = CQuad(clr_result, _alpha).ToRgbA();
	}
	return clr_result;
}

bool CTheme::IsDark (void) {
	return !CDwmSettings().SystemUsesLightTheme();
}

/////////////////////////////////////////////////////////////////////////////

CTheme&  CTheme::operator = (const CTheme& _ref) { this->m_clr_mtx = _ref.Matrix(); this->m_current = _ref.Palette();  return *this; }

/////////////////////////////////////////////////////////////////////////////
}}

namespace shared {
	
	TTheme&   Get_Theme (void) {
		static TTheme the_theme;
		return the_theme;
	}

}

/////////////////////////////////////////////////////////////////////////////

using namespace ex_ui::theme::direct_x;

CFloat CUI_Parts::Bkg (clr_value _alpha) const {
#if (1)
	if (0x0 != _alpha) {
		CQuad quad(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back), _alpha);
		return CFloat(quad.ToRgbA());
	}
	else
		return CFloat(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
#else
	return CFloat(_r_g_b_a(255, 140, 0, 255));
#endif
}