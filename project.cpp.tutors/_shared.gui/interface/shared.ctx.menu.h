#ifndef __SHARED_CTX_MENU_H_INCLUDED
#define __SHARED_CTX_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2026 at 11:08:38.461, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared window context menu wrapper interface declaration file;
*/
#include "shared.defs.h"
#include "menu\shared.menu.enum.h"
#include "menu\shared.menu.item.h"
#include "menu\shared.menu.state.h"
#include "menu\shared.menu.popup.h"

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

	class CCtxMenu : public menus::CMenu { typedef menus::CMenu TMenu;
	public:
		CCtxMenu (void); CCtxMenu (const CCtxMenu&) = delete; CCtxMenu (CCtxMenu&&) = delete; ~CCtxMenu (void);

		uint32_t Track (const HWND _h_owner, const t_point _pt_screen); // tracks popup menu; returns selected menu item command or 0;
		const
		menus::CMenu& operator ()(void) const;
		menus::CMenu& operator ()(void) ;

	private:
		CCtxMenu& operator = (const CCtxMenu&) = delete; CCtxMenu& operator = (CCtxMenu&&) = delete;
	};

}}

#endif/*__SHARED_CTX_MENU_H_INCLUDED*/