#ifndef _EBOSHAGUITHEME_H_INCLUDED
#define _EBOSHAGUITHEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Dec-2020 at 7:50:01.682 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Sha Optima Tool GUI generic format color theme interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack UM test project on 14-Jan-2021 at 12:03:27.717 pm, UTC+7, Novosibirsk, Thursday;
	Adopted to Ebo Pack render project desktop GUI app on 26-Apr-2025 at 22:49:56.695, UTC+4, Batumi, Saturday; 
*/
#include "win.gui_module.h"
#include "color.rgb.h"

namespace ebo { namespace sha { namespace theme { namespace colors {

	using namespace ex_ui::color::rgb;

	enum class CTheme_Palette { e_none   , e_dark, e_light };
	enum class CTheme_Part    { e_none   , e_form, e_panel, e_edit, e_label, e_caption, e_button };
	enum class CTheme_State   { e_default, e_disable, e_hovered, e_selected}; // actually, default must be treated as used for normal state;
	enum class CTheme_Element { e_none   , e_back, e_fore , e_border };

	typedef ::std::map <CTheme_State  , uint32_t      > TColor_State  ;
	typedef ::std::map <CTheme_Element, TColor_State  > TColor_Element;
	typedef ::std::map <CTheme_Part   , TColor_Element> TColor_Part   ;
	typedef ::std::map <CTheme_Palette, TColor_Part   > TColor_Palette;

	class CColor_Marker {
	protected:
		CTheme_Palette m_palette ;
		CTheme_Part    m_ui_part ;
		CTheme_State   m_ui_state;
		CTheme_Element m_element ;

	public:
		 CColor_Marker (void);
		 CColor_Marker (const CColor_Marker&);
		 CColor_Marker (const CTheme_Palette, const CTheme_Part, const CTheme_Element, const CTheme_State = CTheme_State::e_default);
		~CColor_Marker (void);

	public:
		const CTheme_Element   Element (void) const;
		const CTheme_Palette   Palette (void) const;
		const CTheme_Part      Part    (void) const;
		const CTheme_State     State   (void) const;

	public:
		const bool Is (void) const;  // returns true if all attributes are assigned (there is no e_none value);

	public:
		CColor_Marker& operator = (const CColor_Marker&);
		CColor_Marker& operator <<(const CTheme_Element);
		CColor_Marker& operator <<(const CTheme_Palette);
		CColor_Marker& operator <<(const CTheme_Part );
		CColor_Marker& operator <<(const CTheme_State);
	};

	class CColor_Matrix {
	protected:
		TColor_Palette   m_palettes;

	public:
		 CColor_Matrix (void);
		 CColor_Matrix (const CColor_Matrix&);
		~CColor_Matrix (void);

	public:
		 CColor_Matrix& operator = (const CColor_Matrix&);
		 const COLORREF operator <<(const CColor_Marker&) const;   // returns CLR_NONE if marker does not match any value;
	};

}}}}

typedef ebo::sha::theme::colors::CTheme_Element    TThemeElement;
typedef ebo::sha::theme::colors::CTheme_Palette    TThemePalette;
typedef ebo::sha::theme::colors::CTheme_Part       TThemePart ;
typedef ebo::sha::theme::colors::CTheme_State      TThemeState;
typedef ebo::sha::theme::colors::CColor_Marker     TColorMarker;
typedef ebo::sha::theme::colors::CColor_Matrix     TColorMatrix;

namespace ebo { namespace sha { namespace theme {

	// https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/b0z6b513

	class CTheme {
	protected:
		TThemePalette  m_current; // current theme palette;
		TColorMatrix   m_clr_mtx; // current color matrix ;  

	public:
		 CTheme (void);
		 CTheme (const CTheme&);
		~CTheme (void);

	public:
		const TColorMatrix&  Matrix  (void) const;
		const TThemePalette  Palette (void) const;

	public:
		COLORREF Get (const TThemePart, const TThemeElement, const TThemeState = TThemeState::e_default) const;

	public:
		CTheme& operator = (const CTheme&);
	};

}}}

typedef ebo::sha::theme::CTheme  TTheme;

namespace shared {

	TTheme&   Get_Theme (void);
}

#endif/*_EBOSHAGUITHEME_H_INCLUDED*/