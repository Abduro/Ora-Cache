#ifndef _SHARED_MENU_BASE_H_INCLUDED
#define _SHARED_MENU_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 10:47:28.069, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu wrapper base interface declaration file;
*/
#include "shared.defs.h"

namespace shared { namespace gui { namespace menus { using namespace shared::defs;
#pragma region __refs
	// https://learn.microsoft.com/en-us/windows/win32/menurc/menus ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenuex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-tpmparams ;
	// https://learn.microsoft.com/en-us/windows/win32/menurc/using-menus#example-of-owner-drawn-menu-items ;
#pragma endregion
	typedef MENUITEMINFO TItemInfo;

	class CBase {
	protected:
		CBase (void); CBase (const CBase&); CBase (CBase&&); ~CBase (void);
	public:
		TError& Error (void) const;
	protected:
		CBase& operator = (const CBase&); CBase& operator = (CBase&&);
		mutable CError m_error;
	};

}}}

#endif/*_SHARED_MENU_BASE_H_INCLUDED*/