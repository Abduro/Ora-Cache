#ifndef __SHARED_CTX_MENU_H_INCLUDED
#define __SHARED_CTX_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2026 at 11:08:38.461, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared window context menu wrapper interface declaration file;
*/
#include "shared.defs.h"
#include "menu\shared.menu.enum.h"
#include "menu\shared.menu.item.h"

namespace shared { namespace gui { namespace menus { using namespace shared::defs;

#if (0) // not used;
	class CCtxCfg : public CBase { typedef CBase TBase;
	public:
		enum class e_h_align : uint32_t { e_left = 0x0, e_right = 0x1 };
		enum class e_v_align : uint32_t { e_top = 0x0, e_bottom = 0x1 };
	public:
		CCtxCfg (void); CCtxCfg (const CCtxCfg&) = delete; CCtxCfg (CCtxCfg&&) = delete; ~CCtxCfg (void) = default;

		err_code  Get (void);  // reads system metrics related to tracking a popup menu;

	private:
		CCtxCfg& operator = (const CCtxCfg&) = delete; CCtxCfg& operator = (CCtxCfg&&) = delete;
		e_h_align m_h_align;
		e_v_align m_v_align;
	};
#endif
}
	using namespace shared::defs;

	class CCtxMenu {
	public:
		using CItem_Coll = menus::CItem_Coll;
		CCtxMenu (void); CCtxMenu (const CCtxMenu&) = delete; CCtxMenu (CCtxMenu&&) = delete; ~CCtxMenu (void);

		err_code Create (void);  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createpopupmenu ;
		err_code Destroy (void); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;

		TError&  Error (void) const;
		bool  Is_valid (void) const;

		HMENU Handle (void) const;

		const
		CItem_Coll& Items (void) const;
		CItem_Coll& Items (void) ;

		err_code Load  (uint16_t _res_id); // loads a menu from resource of the executable by given resource identifier; menu items are not created!

		uint32_t Track (const HWND _h_owner, const t_point _pt_screen); // tracks popup menu; returns selected menu item command or 0;

		operator HMENU (void) const;
		HMENU operator ()(void) const;

	private:
		CCtxMenu& operator = (const CCtxMenu&) = delete; CCtxMenu& operator = (CCtxMenu&&) = delete;
		CError     m_error;
		HMENU      m_menu ;
		CItem_Coll m_items;
	};

}}

#endif/*__SHARED_CTX_MENU_H_INCLUDED*/