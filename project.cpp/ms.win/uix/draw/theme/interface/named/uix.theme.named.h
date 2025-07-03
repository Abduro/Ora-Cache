#ifndef _UIX_THEME_NAMED_H_INCLUDED
#define _UIX_THEME_NAMED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 12:40:47.449, UTC+4, Batumi, Saturday;
	This is Ebo Pack generic custom color theme named interface declaration file.
*/
#include "uix.theme.inc.h"
#include "uix.theme.h"

namespace ex_ui { namespace theme {

	using namespace ex_ui::theme::colors;
	using CHex = ex_ui::color::rgb::CHex;

	class CCurrent : public TColorMarker { typedef TColorMarker TBase;
	public:
		 CCurrent (void); CCurrent (const CCurrent&); CCurrent (CCurrent&&);
		~CCurrent (void);

	public:
		void      Default    (void) ;

		uint32_t  ThemeIndex (void) const;     // gets currently selected theme index;
		bool      ThemeIndex (const uint32_t); // sets selected theme index; in most cases it is used by registry storage;

	public:
		CCurrent& operator = (const CCurrent&);
		CCurrent& operator = (CCurrent&&);
		
		CCurrent& operator <<(const uint32_t _ndx);

	private:
		uint32_t   m_theme_ndx;
	};

	class CBase {
	public:
		 CBase (void); CBase (_pc_sz _p_name, const bool _b_valid); CBase (const CBase&); CBase (CBase&&);
		~CBase (void);

	public:
		bool   Is_valid (void) const;  // returns 'true' if this class object is successfully loaded from the registry;
		void   Is_valid (const bool);  // sets the validity flag of this class object, for example, in case when the registry has no data of this object;

		_pc_sz Name (void) const;
		bool   Name (_pc_sz)    ;      // sets the base name, returns 'true' if the name is changed;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		bool   Set (_pc_sz _p_name, const bool _b_valid);
	public:
		CBase& operator = (const CBase&);
		CBase& operator = (CBase&&);
		CBase& operator <<(_pc_sz _p_name);
		CBase& operator <<(const bool _b_valid);
	protected:
		bool    m_valid;
		CString m_name ;
	};

	class CState : public CBase { typedef CBase TBase;
	public:
		 CState (const TThemeState = TThemeState::e_default); CState (const CState&); CState (CState&&);
		~CState (void);

	public:
		bool      Clear (void) ; // changes color to transparent 'black' and sets 'valid' flag to false;
		rgb_color Color (void) const;
		bool      Color (const rgb_color);

		TThemeState  Id (void) const;
		const bool   Id (const TThemeState, const bool b_update_name); // sets the state identifier and updates the name;

		const
		CHex&  Hex  (void) const;
		CHex&  Hex  (void) ;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CState& operator = (const CState&);
		CState& operator = (CState&&);        // no move or swap operation, just copying data;
		CState& operator <<(const TThemeState _e_id);
		CState& operator <<(const rgb_color);

	private:
		TThemeState  m_state_id;
		CHex    m_color;
	};

	typedef ::std::array<CState, 4> TRawStates; // 0: e_normal; 1: e_disabled; 2: e_hovered; 3: e_selected;

	class CElement : public CBase { typedef CBase TBase;
	public:
		 CElement (const TThemeElement = TThemeElement::e_none); CElement (const CElement&); CElement (CElement&&);
		~CElement (void);
	public:
		const bool Clear (void); // resets all states to be invalid; sets 'validity' flag to false for this class object; 
		TThemeElement Id (void) const;
		const bool    Id (const TThemeElement, const bool b_update_name); // sets the element identifier and updates the name; clears its states;
		const
		TRawStates&   States (void) const;
		TRawStates&   States (void) ;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CElement& operator = (const CElement&);
		CElement& operator = (CElement&&);

		CElement& operator <<(const TRawStates&);
		CElement& operator <<(const TThemeElement& _e_id);

	private:
		TThemeElement m_el_id;
		TRawStates    m_states;
	};

	typedef ::std::array<CElement, 3> TRawElements;  // 0: e_back; 1: e_fore; 2: e_border;

	class CPart : public CBase { typedef CBase TBase;
	public:
		 CPart (const TThemePart = TThemePart::e_none); CPart (const CPart&); CPart (CPart&&);
		~CPart (void);

	public:
		const bool    Clear (void);  // clears all elements and sets 'validity' flag of this class object to 'false';
		const
		TRawElements& Elements (void) const;
		TRawElements& Elements (void) ;

		TThemePart  Id (void) const;
		const bool  Id (const TThemePart, const bool b_update_name);
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	public:
		CPart& operator = (const CPart&);
		CPart& operator = (CPart&&);
		CPart& operator <<(const TThemePart _e_id);
		CPart& operator <<(const TRawElements&);

	private:
		TThemePart   m_part_id ;
		TRawElements m_elements;
	};

	typedef ::std::array<CPart, 6> TRawParts; // 0: e_form; 1: e_panel; 2: e_edit; 3: e_label; 4: e_caption; 5: e_button;

	class CNamed : public CBase { typedef CBase TBase;
	public:
		 CNamed (void); CNamed (const CNamed&); CNamed (CNamed&&);
		~CNamed (void);

	public:
		_pc_sz  Desc (void) const;
		bool    Desc (_pc_sz) ;

		bool Is_valid(void) const; // returns 'true' if one of the parts is loaded successfully;
		bool Is_valid(const bool);

		const
		TRawParts& Parts (void) const;
		TRawParts& Parts (void) ;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CNamed& operator = (const CNamed&);
		CNamed& operator = (CNamed&&) = delete;
		CNamed& operator <<(_pc_sz _p_name);
		CNamed& operator >>(_pc_sz _p_desc);
		CNamed& operator <<(const TRawParts&);

	private:
		CString   m_desc ;
		TRawParts m_parts;
	};

	typedef ::std::vector<CNamed> TRawNamed;

	class CPalette : public CBase { typedef CBase TBase;
	public:
		 CPalette (const TThemePalette = TThemePalette::e_none); CPalette (const CPalette&); CPalette (CPalette&&);
		~CPalette (void);

	public:
		const bool Clear (void);  // clears all elements and sets 'validity' flag of this class object to 'false';
		const
		TRawNamed& Themes(void) const;
		TRawNamed& Themes(void) ;

		TThemePalette Id (void) const;
		const bool    Id (const TThemePalette, const bool b_update_name);

#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CPalette&  operator = (const CPalette&);
		CPalette&  operator = (CPalette&&);

		CPalette&  operator <<(const TRawNamed&);
		CPalette&  operator <<(const TThemePalette _e_id);

	private:
		TThemePalette m_pal_id;
		TRawNamed     m_themes;
	};

	typedef ::std::array<CPalette, 2> TRawPalettes; // 0: e_dark; 1: e_light;

	class CNamed_Enum {
	public:
		 CNamed_Enum (void); CNamed_Enum (const CNamed_Enum&) = delete; CNamed_Enum (CNamed_Enum&&) = delete;
		~CNamed_Enum (void);

	public:
		TError& Error (void) const;
		err_code Load (const TThemePalette);  // loads custom color themes of specified palette only;
		err_code Load (void);                 // loads custom color themes of all available palettes from system registry;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TRawPalettes& Palettes (void) const;
		TRawPalettes& Palettes (void) ;

		const
		CPalette&     PaletteOf (const TThemePalette) const;

	public:
		CNamed_Enum& operator = (const CNamed_Enum&) = delete;
		CNamed_Enum& operator = (CNamed_Enum&&) = delete;

	private:
		CError m_error;
		TRawPalettes m_palettes;
	};

}}

#endif/*_UIX_THEME_NAMED_H_INCLUDED*/