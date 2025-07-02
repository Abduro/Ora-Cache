#ifndef _UIX_THEME_REG_H_INCLUDED
#define _UIX_THEME_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.con) on 29-Jun-2025 at 07:36:53.5666, UTC+4, Batumi, Sunday;
	This is Ebo Pack custom theme registry storage base interface declaration file;
*/
#include "uix.theme.inc.h"
#include "uix.theme.named.h"

namespace ex_ui { namespace theme { namespace storage {

	using namespace ex_ui::theme;

	class CReg_router {
	public:
		 CReg_router (void) ; CReg_router (const CReg_router&) = delete; CReg_router (CReg_router&&);
		~CReg_router (void) ;

	public:
		const
		CCurrent&  CurrentTheme (void) const;
		CCurrent&  CurrentTheme (void) ;

		_pc_sz Element (void) const;                // composes the registry path to the UI element by using currently selected theme;
		_pc_sz Element (const TThemePalette, const TThemePart, const TThemeElement) const;
		_pc_sz Marker  (const TColorMarker&) const; // composes the registry path in accordance with input color marker;

		_pc_sz Palette (void) const;                // composes the registry path for input palette by using currently selected theme;
		_pc_sz Palette (const TThemePalette) const; // composes the registry path for input palette;

		_pc_sz Part    (void) const;                // composes the path to the part by using currently selected theme;
		_pc_sz Part    (const TThemePalette, const TThemePart) const;

		_pc_sz State   (void) ;                     // composes the path to the element state by using currently selected theme;
		_pc_sz State   (const TThemePalette, const TThemePart, const TThemeElement, const TThemeState) const;

		_pc_sz Theme   (const TThemePalette) const;                      // returns the path to currently selected theme node;
		_pc_sz Theme   (const TThemePalette, const uint32_t _ndx) const; // returns the path of the theme node by specified index;

		HKEY   Root    (void) const;
		_pc_sz Themes  (void) const;                // this is the path to the root node of the named/custom themes; the entry point;

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;
	private:
		HKEY     m_root;
		CCurrent m_current;  // the currently selected theme;
	};

	CReg_router&  Get_router (void);  // returns the reference to the singleton of the router object;

	class CRegistry {
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

	public:
		TError&  Error (void) const;
		err_code Load  (CNamed_Enum&);

		err_code Node  (_pc_sz _p_path, CElement&);
		err_code Node  (_pc_sz _p_path, const TThemeElement, CElement&);
		err_code Value (_pc_sz _p_path, CState&);    // it is supposed the state identifier is already set;
		err_code Value (TRawStates&);                // gets values of all states by using currently selected theme;
		err_code Value (_pc_sz _p_path, const TThemeState, CState&);

	public:
		CRegistry& operator = (const CRegistry&) = delete;
		CRegistry& operator = (CRegistry&&) = delete;

	private:
		CError   m_error;
	};

}}}

#endif/*_UIX_THEME_REG_H_INCLUDED*/