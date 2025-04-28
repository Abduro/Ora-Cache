/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 8:37:53.978 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack UM test project on 14-Jan-2021 at 12:03:27.692 pm, UTC+7, Novosibirsk, Thursday;
	Adopted to Ebo Pack render project desktop GUI app on 26-Apr-2025 at 22:49:56.686, UTC+4, Batumi, Saturday;
*/
#include "ebo.sha.gui.theme.h"

using namespace ebo::sha::theme;
using namespace ebo::sha::theme::colors;

using CTheme = ebo::sha::theme::CTheme;
/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace sha { namespace gui { namespace format { namespace _impl {

}}}}}
using namespace ebo::sha::gui::format::_impl;
/////////////////////////////////////////////////////////////////////////////

TColorMarker:: CColor_Marker (void) : m_palette(TThemePalette::e_none), m_ui_part(TThemePart::e_none), m_ui_state(TThemeState::e_default) {}
TColorMarker:: CColor_Marker (const TColorMarker& _ref) : TColorMarker() { *this = _ref; }
TColorMarker:: CColor_Marker (const TThemePalette _palette, const TThemePart _part, const TThemeElement _element, const TThemeState _state) : TColorMarker() {
	*this << _palette << _part << _element << _state;
}
TColorMarker::~CColor_Marker (void) {}

/////////////////////////////////////////////////////////////////////////////

const TThemeElement   TColorMarker::Element (void) const { return m_element ; }
const TThemePalette   TColorMarker::Palette (void) const { return m_palette ; }
const TThemePart      TColorMarker::Part    (void) const { return m_ui_part ; }
const TThemeState     TColorMarker::State   (void) const { return m_ui_state; }

/////////////////////////////////////////////////////////////////////////////

const bool TColorMarker::Is (void) const { return !(TThemePalette::e_none == m_palette || TThemePart::e_none == m_ui_part || TThemeElement::e_none == m_element); }

/////////////////////////////////////////////////////////////////////////////

TColorMarker& TColorMarker::operator = (const CColor_Marker& _ref) { *this << _ref.Palette() << _ref.Part() << _ref.State() << _ref.Element(); return *this; }
TColorMarker& TColorMarker::operator <<(const CTheme_Element _element) { this->m_element = _element; return *this; }
TColorMarker& TColorMarker::operator <<(const CTheme_Palette _palette) { this->m_palette = _palette; return *this; }
TColorMarker& TColorMarker::operator <<(const CTheme_Part _part) { this->m_ui_part = _part; return *this; }
TColorMarker& TColorMarker::operator <<(const CTheme_State _state) { this->m_ui_state = _state; return *this; }

/////////////////////////////////////////////////////////////////////////////

TColorMatrix:: CColor_Matrix (void) {
	// ToDo: of course, this is not the best approach to defining theme colors in this way;
	//       it would be better to use XML or JSON files as the source of theme colors;
	m_palettes = {
		{
			TThemePalette::e_dark, {
				{ TThemePart::e_button , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  70,  70,  70) }, { TThemeState::e_hovered , RGB( 102,  90,  71) }, { TThemeState::e_selected, RGB(  70,  70,  70) }} },
				                          { TThemeElement::e_border, {{ TThemeState::e_default, RGB( 115, 115, 115) }, { TThemeState::e_hovered , RGB( 229, 183,  66) },
				                                                      { TThemeState::e_disable, RGB( 115, 115, 115) }, { TThemeState::e_selected, RGB( 229, 183,  66) }} },
				                          { TThemeElement::e_fore  , {{ TThemeState::e_default, RGB( 230, 230, 230) }, { TThemeState::e_hovered , RGB( 229, 183,  66) },
				                                                      { TThemeState::e_disable, RGB( 115, 115, 115) }, { TThemeState::e_selected, RGB( 183, 163,  66) }} }}},
				{ TThemePart::e_caption, {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  70,  70,  70) }} },
				                          { TThemeElement::e_fore  , {{ TThemeState::e_default, RGB( 230, 230, 230) }} } }},
				{ TThemePart::e_edit   , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  70,  70,  70) }, { TThemeState::e_disable , RGB(  70,  70,  70) }} },
				                          { TThemeElement::e_border, {{ TThemeState::e_default, RGB( 115, 115, 115) }, { TThemeState::e_disable , RGB( 115, 115, 115) }} },
				                          { TThemeElement::e_fore  , {{ TThemeState::e_default, RGB( 230, 230, 230) }, { TThemeState::e_disable , RGB( 230, 230, 230) }} }}},
				{ TThemePart::e_form   , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  39,  39,  39) }} },     // 61, 61, 61
				                          { TThemeElement::e_border, {{ TThemeState::e_default, RGB( 229, 183,  66) }} },     // #e5b742
				                          { TThemeElement::e_fore  , {{ TThemeState::e_default, RGB( 230, 230, 230) }} } }},
				{ TThemePart::e_label  , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  70,  70,  70) }} },
				                          { TThemeElement::e_fore  , {{ TThemeState::e_default, RGB( 230, 230, 230) }} } }},
				{ TThemePart::e_panel  , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB(  61,  61,  61) }} },
				                          { TThemeElement::e_border, {{ TThemeState::e_default, RGB( 229, 183,  66) }, { TThemeState::e_disable , RGB( 115, 115, 115) }} }}}//,
			//	{ TThemePart::, {{, {{ }} }} }
			}
		},
		{
			TThemePalette::e_light, {
				{ TThemePart::e_form   , {{ TThemeElement::e_back  , {{ TThemeState::e_default, RGB( 249, 249, 249) }} }
				}}
			}
		}
	};
}
TColorMatrix:: CColor_Matrix (const TColorMatrix& _ref) : TColorMatrix() { *this = _ref; }
TColorMatrix::~CColor_Matrix (void) {}

/////////////////////////////////////////////////////////////////////////////

#ifndef CLR_NONE
#define CLR_NONE 0xFFFFFFFFL
#endif

TColorMatrix&  TColorMatrix::operator = (const TColorMatrix& _ref) { this->m_palettes = _ref.m_palettes; return *this; }
const COLORREF TColorMatrix::operator <<(const CColor_Marker& _marker) const {

	COLORREF clr_result = CLR_NONE;
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
					}
				}
			}
		}
	}

	return clr_result;
}

/////////////////////////////////////////////////////////////////////////////

bool CClr_Simple::Is_light(const clr_type _clr) {
	return (((5 * get_g_value(_clr)) + (2 * get_r_value(_clr)) + get_b_value(_clr)) > (8 * 128));
}

/////////////////////////////////////////////////////////////////////////////

TTheme:: CTheme (void) {
	if (CTheme::IsDark())
		m_current = TThemePalette::e_dark;
	else
		m_current = TThemePalette::e_light;
}
TTheme:: CTheme (const TTheme& _ref) : TTheme() { *this = _ref; }
TTheme::~CTheme (void) {}

/////////////////////////////////////////////////////////////////////////////

const TColorMatrix&  TTheme::Matrix  (void) const { return m_clr_mtx; }
const TThemePalette  TTheme::Palette (void) const { return m_current; }

/////////////////////////////////////////////////////////////////////////////

clr_type TTheme::Get (const TThemePart _part, const TThemeElement _el, const TThemeState _state) const {
	return ((const clr_type)(m_clr_mtx << TColorMarker(this->Palette(), _part, _el, _state)));
}

bool CTheme::IsDark (void) {
	return !CDwmSettings().SystemUsesLightTheme();
}

/////////////////////////////////////////////////////////////////////////////

TTheme&  TTheme::operator = (const TTheme& _ref) { this->m_clr_mtx = _ref.Matrix(); this->m_current = _ref.Palette();  return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace shared {
	
	TTheme&   Get_Theme (void) {
		static TTheme the_theme;
		return the_theme;
	}

}

/////////////////////////////////////////////////////////////////////////////

using namespace ebo::sha::theme::direct_x;

CClr_Float CUI_Parts::Bkg (void) const {

	return CClr_Float(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));

}