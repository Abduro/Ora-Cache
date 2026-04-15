#ifndef _CTX_MENU_WRAPPER_H_INCLUDED
#define _CTX_MENU_WRAPPER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 23:31:33.965, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials'main window context menu wrapper interface declaration file;
*/
#include "shared.ctx.menu.h"

namespace ex_ui { namespace draw { namespace gui {
	using namespace shared::defs;
	using CCtxMenu = shared::gui::CCtxMenu;
namespace menus {
	class CCell {
	public:
		CCell (void) = default; CCell (const CCell&) = delete; CCell (CCell&&) = delete; ~CCell (void) = default;

		static uint32_t CmdToHeight (const uint32_t _u_cmd_id);
		static uint32_t CmdToWidth  (const uint32_t _u_cmd_id);

		static uint32_t HeightToCmd (const uint32_t _u_height);
		static uint32_t WidthToCmd  (const uint32_t _u_width );

	private:
		CCell& operator = (const CCell&) = delete; CCell& operator = (CCell&&) = delete;
	};

	class CConsole {
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void) = default;
	private:
		CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
	};

	class CGrid {
	public:
		 CGrid (void); CGrid (const CGrid&) = delete; CGrid (CGrid&&) = delete;
		~CGrid (void) = default;
	private:
		CGrid& operator = (const CGrid&) = delete; CGrid& operator = (CGrid&&) = delete;
	};
}
	// https://en.wikipedia.org/wiki/Memento_pattern ;
	class CCaretaker {
	public:
		CCaretaker (void); CCaretaker (const CCaretaker&) = delete; CCaretaker (CCaretaker&&) = delete; ~CCaretaker (void) = default;

		err_code ApplyTo (CCtxMenu&);
		TError&  Error (void) const;

	private:
		CCaretaker& operator = (const CCaretaker&) = delete; CCaretaker& operator = (CCaretaker&&) = delete;
		CError m_error;
	};

	class COrganizer {
	public:
		COrganizer (void); COrganizer (const COrganizer&) = delete; COrganizer (COrganizer&&) = delete; ~COrganizer (void) = default;

	private:
		COrganizer& operator = (const COrganizer&) = delete; COrganizer& operator = (COrganizer&&) = delete;
	};

}}}

#endif/*_CTX_MENU_WRAPPER_H_INCLUDED*/