#ifndef _CTX_MENU_WRAPPER_H_INCLUDED
#define _CTX_MENU_WRAPPER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 23:31:33.965, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials'main window context menu wrapper interface declaration file;
*/
#include "shared.ctx.menu.h"
#include "gl_drawable.h"

namespace ex_ui { namespace draw { namespace gui {
	using namespace shared::defs;
	using CCtxMenu = shared::gui::CCtxMenu;
namespace menus {
	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		TError& Error (void) const;
	protected:
		CError m_error;
	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	};

	class CCell : public CBase { typedef CBase TBase;
	public:
		CCell (void);

		err_code ApplyTo (CCtxMenu&);

		static uint32_t CmdToHeight (const uint32_t _u_cmd_id);
		static uint32_t CmdToWidth  (const uint32_t _u_cmd_id);

		static uint32_t HeightToCmd (const uint32_t _u_height);
		static uint32_t WidthToCmd  (const uint32_t _u_width );
	};

	class CConsole : public CBase { typedef CBase TBase;
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void) = default;

		err_code ApplyTo (CCtxMenu&);
		bool On_command (const uint32_t _u_cmd_id); // returns 'true' if command is handled; error object state is set if necessary;

	private:
		CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
	};

	class CGrid : public CBase { typedef CBase TBase;
	public:
		 CGrid (void); CGrid (const CGrid&) = delete; CGrid (CGrid&&) = delete;
		~CGrid (void) = default;

		bool On_command (const uint32_t _u_cmd_id); // returns 'true' if command is handled; error object state is set if necessary;

	private:
		CGrid& operator = (const CGrid&) = delete; CGrid& operator = (CGrid&&) = delete;
	};
}
	// https://en.wikipedia.org/wiki/Memento_pattern ;
	class CCaretaker : public menus::CBase { typedef menus::CBase TBase;
	public:
		CCaretaker (void); CCaretaker (const CCaretaker&) = delete; CCaretaker (CCaretaker&&) = delete; ~CCaretaker (void) = default;

		err_code ApplyTo (CCtxMenu&);

	private:
		CCaretaker& operator = (const CCaretaker&) = delete; CCaretaker& operator = (CCaretaker&&) = delete;
	};

	class COrganizer : public menus::CBase { typedef menus::CBase TBase;
	public:
		COrganizer (void); COrganizer (const COrganizer&) = delete; COrganizer (COrganizer&&) = delete; ~COrganizer (void) = default;

		err_code On_command (const uint32_t _u_cmd_id);

	private:
		COrganizer& operator = (const COrganizer&) = delete; COrganizer& operator = (COrganizer&&) = delete;
	};

}}}

#endif/*_CTX_MENU_WRAPPER_H_INCLUDED*/