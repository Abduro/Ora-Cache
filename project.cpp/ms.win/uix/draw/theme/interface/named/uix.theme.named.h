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

	class CState {
	public:
		 CState (const TThemeState = TThemeState::e_default); CState (const CState&); CState (CState&&);
		~CState (void);

	public:
		rgb_color Color (void) const;
		bool      Color (const rgb_color);

		bool   Is_valid (void) const;  // returns 'true' if color is not transparent; 'alpha' channel value must be zero;

		TThemeState  Id (void) const;
		const bool   Id (const TThemeState, const bool b_update_name); // sets the state identifier and updates the name;

		const
		CHex&  Hex  (void) const;
		CHex&  Hex  (void) ;

		_pc_sz Name (void) const;
		bool   Name (_pc_sz)    ;  // sets the state name, returns 'true' if the name is changed;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		CState& operator = (const CState&);
		CState& operator = (CState&&);        // no move or swap operation, just copying data;
		CState& operator <<(_pc_sz _p_name);
		CState& operator <<(const TThemeState _e_id);
		CState& operator <<(const rgb_color);

	private:
		TThemeState  m_state_id;
		CHex    m_color;
		CString m_name ;
	};

	typedef ::std::array<CState, 4> TRawStates;

	class CPart {
	public:
		 CPart (const TThemePart = TThemePart::e_none); CPart (const CPart&); CPart (CPart&&);
		~CPart (void);

	public:
		TThemePart  Id (void) const;
		bool Id (const TThemePart) ;

		bool Is_valid (void) const ;

	public:
		CPart& operator = (const CPart&);
		CPart& operator = (CPart&&);

	private:
		TThemePart  m_part_id;
	};

	typedef ::std::vector<CPart> TRawParts;

	class CNamed {
	public:
		 CNamed (const TThemePalette = TThemePalette::e_none); CNamed (const CNamed&); CNamed (CNamed&&);
		~CNamed (void);

	public:
		_pc_sz  Desc (void) const;
		bool    Desc (_pc_sz) ;
		_pc_sz  Name (void) const;
		bool    Name (_pc_sz) ;

		bool Is_valid(void) const; // returns false is its palette set to e_none;

		TThemePalette Palette (void) const;
		const bool    Palette (const TThemePalette);

		const
		TRawParts&  Parts (void) const;
		TRawParts&  Parts (void) ;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif

	public:
		CNamed& operator = (const CNamed&);
		CNamed& operator = (CNamed&&) = delete;
		CNamed& operator <<(const TThemePalette);
		CNamed& operator <<(_pc_sz _p_name);
		CNamed& operator >>(_pc_sz _p_desc);
		CNamed& operator <<(const TRawParts&);

	private:
		CString m_desc;
		CString m_name;
		TThemePalette m_palette;
		TRawParts m_parts;
	};

	typedef ::std::vector<CNamed> TRawNamed;

	class CNamed_Enum {
	public:
		 CNamed_Enum (void); CNamed_Enum (const CNamed_Enum&) = delete; CNamed_Enum (CNamed_Enum&&) = delete;
		~CNamed_Enum (void);

	public:
		TError& Error (void) const;
		err_code Load (void);         // loads custom color themes from system registry;

#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TRawNamed& Raw (void) const;
		TRawNamed& Raw (void) ;

	public:
		CNamed_Enum& operator = (const CNamed_Enum&) = delete;
		CNamed_Enum& operator = (CNamed_Enum&&) = delete;

	private:
		CError m_error;
		TRawNamed m_themes;
	};

}}

#endif/*_UIX_THEME_NAMED_H_INCLUDED*/