#ifndef __SHARED_CTX_MENU_H_INCLUDED
#define __SHARED_CTX_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2026 at 11:08:38.461, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared window context menu wrapper interface declaration file;
*/
#include "shared.defs.h"

namespace shared { namespace gui { namespace menus {

	using namespace shared::defs;
	// https://learn.microsoft.com/en-us/windows/win32/menurc/menus ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenuex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-tpmparams ;

	class CBase {
	protected:
		CBase (void); CBase (const CBase&); CBase (CBase&&); ~CBase (void);
		TError& Error (void) const;
	protected:
		CBase& operator = (const CBase&); CBase& operator = (CBase&&);
		mutable CError m_error;
	};

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

	public:
		CItem& operator = (const CItem&); CItem& operator = (CItem&&);
		CItem& operator <<(const uint32_t _u_cmd_id);
		CItem& operator <<(_pc_sz _p_caption);
	private:
		uint32_t m_cmd_id;
		CString  m_cs_cap;
		uint32_t m_mask;
	};

	typedef ::std::vector<CItem> TItems;

	class CItem_Coll : public CBase { typedef CBase TBase;
	public:
		CItem_Coll (HMENU = nullptr); CItem_Coll (const CItem_Coll&) = delete; CItem_Coll (CItem_Coll&&) = delete; ~CItem_Coll (void);

		bool Is_valid (void) const;  // checks the handle of the manu for validity;

		err_code Append (const CItem&);
		err_code Insert (const uint32_t _u_before, const CItem&);

		HMENU    Menu (void) const;
		err_code Menu (const HMENU);

		CItem_Coll& operator <<(const HMENU);
		HMENU operator ()(void) const;

	private:
		CItem_Coll& operator = (const CItem_Coll&) = delete; CItem_Coll& operator = (CItem_Coll&&) = delete;
		HMENU   m_menu ;
		TItems  m_items;
	};
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
		const
		CItem_Coll& Items (void) const;
		CItem_Coll& Items (void) ;

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