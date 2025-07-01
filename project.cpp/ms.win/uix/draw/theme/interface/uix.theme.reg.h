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
		_pc_sz Element (const TThemePalette, const TThemePart, const TThemeElement) const;
		_pc_sz Marker  (const TColorMarker&) const; // composes the registry path in accordance with input color marker;
		_pc_sz Palette (const TThemePalette) const; // composes the registry path for input palette;
		_pc_sz Part    (const TThemePalette, const TThemePart) const;
		_pc_sz State   (const TThemePalette, const TThemePart, const TThemeElement, const TThemeState) const;

		HKEY   Root    (void) const;
		_pc_sz Themes  (void) const;                // this is the path to the root node of the named/custom themes; the entry point;

	private:
		CReg_router& operator = (const CReg_router&) = delete;
		CReg_router& operator = (CReg_router&&) = delete;
	private:
		HKEY  m_root;
	};

	class CRegistry {
	public:
		 CRegistry (void); CRegistry (const CRegistry&) = delete; CRegistry (CRegistry&&) = delete;
		~CRegistry (void);

	public:
		TError&  Error (void) const;
		err_code Load  (CNamed_Enum&);

		err_code Value (_pc_sz _path, const TThemeState, CState&); // loads the registry key value specified by path for theme state;

	public:
		CRegistry& operator = (const CRegistry&) = delete;
		CRegistry& operator = (CRegistry&&) = delete;

	private:
		CError   m_error;
	};

}}}

#endif/*_UIX_THEME_REG_H_INCLUDED*/