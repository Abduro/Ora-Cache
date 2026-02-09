#ifndef _SHARED_MENU_POPUP_H_INCLUDED
#define _SHARED_MENU_POPUP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Feb-2026 at 13:47:56.650, UTC+4, Batumi, Monday;
	This is Ebo Pack shared window popup menu wrapper interface declaration file;
*/
#include "shared.menu.item.h"

namespace shared { namespace gui { namespace menus { using namespace shared::defs;

	// this is popup menu wrapper class;
	class CMenu : public CBase { typedef CBase TBase;
	public:
		/**important*:
		   a menu/submenu can have a numeric ID, just like each item has a command ID, but it's useless;
		 ::GetMenuItemID() returns (-1) because submenu is not command menu item;
		*/
		CMenu (const HMENU = nullptr, _pc_sz _p_caption = _T("")); ~CMenu (void);
		CMenu (const CMenu&) = delete; CMenu (CMenu&&);

		err_code Append (const HMENU _h_sub_menu, _pc_sz _p_caption); // appends the submenu to this popup;
		const
		CString& Caption (void) const;
		CString& Caption (void);

		err_code Create  (_pc_sz _p_caption = nullptr); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createpopupmenu ;
		err_code Destroy (void);        // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;

		const
		HMENU& Handle (void) const;     // gets the reference to the menu handle; (ro)
		HMENU& Handle (void);           // gets the reference to the menu handle; (rw) *important*: if the handle is set directly, the items must be reset too;

		bool   Is_valid (void) const;   // checks the validity of the menu handle;
		const
		CItem_Coll& Items (void) const;
		CItem_Coll& Items (void) ;

		const
		HMENU& operator ()(void) const; // gets the reference to the menu handle; (ro)
		HMENU& operator ()(void) ;      // gets the reference to the menu handle; (rw)

		CMenu& operator = (const CMenu&) = delete; CMenu& operator = (CMenu&&);

		CMenu& operator <<(const HMENU);//*important*: if the handle is set directly, the items must be reset too;
		CMenu& operator <<(_pc_sz _p_caption);
		CMenu& operator <<(const CString& _cs_caption);
		CMenu& operator <<(const CItem_Coll&);

	private:
		HMENU    m_h_menu ;
		CString  m_caption;
		CItem_Coll m_items;
	};

}}}

#endif/*_SHARED_MENU_POPUP_H_INCLUDED*/