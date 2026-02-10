#ifndef _SHARED_MENU_ITEM_H_INCLUDED
#define _SHARED_MENU_ITEM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 11:09:32.922, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu item wrapper interface declaration file;
*/
#include "shared.menu.base.h"
#include "shared.menu.state.h"

namespace shared { namespace gui { namespace menus {

	class CItem : public CBase { typedef CBase TBase;
	public:
		CItem (const uint32_t _u_cmd_id = 0, _pc_sz _p_caption = nullptr);
		CItem (const CItem&); CItem (CItem&&); ~CItem (void);

		const
		CString& Caption (void) const;
		CString& Caption (void) ;
		bool     Caption (_pc_sz);         // returns 'true' in case of item caption string change;

		uint32_t CmdId (void) const;
		bool     CmdId (const uint32_t);   // returns 'true' in case of command identifier change;

		bool  Is_valid (void) const;
		uint32_t Mask  (void) const;       // this is the flag mask for appending or inserting menu item;

	//	static err_code Disable (const uint32_t _itm_id, CError&);
	//	static err_code Enable (const uint32_t _itm_id, CError&);
		const
		CState&  State (void) const;
		CState&  State (void) ;

		_pc_sz To_str (void) const;        // converts this class object to string representation for debug output;

	public:
		CItem& operator = (const CItem&); CItem& operator = (CItem&&);
		CItem& operator <<(const uint32_t _u_cmd_id);
		CItem& operator <<(_pc_sz _p_caption);
		CItem& operator <<(const CState&);

	private:
		uint32_t m_cmd_id;
		CString  m_cs_cap;
		uint32_t m_mask;
		CState   m_state;
	};

	typedef ::std::vector<CItem> TItems;

	class CItem_Coll : public CBase { typedef CBase TBase;
	public:
		CItem_Coll (HMENU = nullptr); CItem_Coll (const CItem_Coll&); CItem_Coll (CItem_Coll&&); ~CItem_Coll (void);

		bool Is_valid (void) const;  // checks the handle of the manu for validity;

		err_code Append (const CItem&);
		err_code Insert (const uint32_t _u_before, const CItem&);

		const
		CItem&   Find (const uint32_t _cmd_id) const; // finds the menu item by given command identifier, if not found the reference to unvalid item is returned;
		CItem&   Find (const uint32_t _cmd_id) ;	  // finds the menu item by given command identifier, if not found the reference to unvalid item is returned;

		HMENU    Menu (void) const;
		err_code Menu (const HMENU);
		const
		TItems&  Raw (void) const;
		TItems&  Raw (void) ;
		static
		err_code Set  (const HMENU, TItems&, CError&); // enumerates all items that are contained in the menu of given handle;

		CItem_Coll& operator <<(const TItems&);
		CItem_Coll& operator <<(const HMENU);
		HMENU operator ()(void) const;

		CItem_Coll& operator+= (const CItem&);
		CItem_Coll& operator = (const CItem_Coll&); CItem_Coll& operator = (CItem_Coll&&);

	private:
		HMENU   m_menu ;
		TItems  m_items;
	};
}}}

#endif/*_SHARED_MENU_ITEM_H_INCLUDED*/