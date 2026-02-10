#ifndef _OPEN_GL_TUTOR_3_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_3_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 02:53:28.276, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to OpenGL tutorials' camera project on 27-Nov-2025 at 00:36:54.670, UTC+4, Batumi, Thursday;
*/
#include "gl_context.h"
#include "shared.wnd.fake.h"
#include "shared.wnd.base.h" 
#include "shared.ctx.menu.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace camera {

	using namespace shared::defs;
	using namespace shared::types;
	using namespace ex_ui::popup;

	using CFakeWnd = ex_ui::popup::CMsgWnd;
	using CCtxMenu = shared::gui::CCtxMenu;

	class CWnd : public ex_ui::popup::CWndBase, public messages::IMouse_Handler { typedef ex_ui::popup::CWndBase TBase;
	using CDevice = context::CDevice;
	public:
		 CWnd (void);
		~CWnd (void);

		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final;
		TError&  IMouse_Error (void) const override final;
		err_code IMouse_OnEvent (const CEvent&) override final;

		err_code Create (const HWND _h_parent, const t_rect&, const bool _b_visible = true);
		err_code Destroy (void);
		err_code PostCreate (void);

	protected:
		CFakeWnd  m_fak_wnd; // message-only window (aka fake) is created in its constructor;
		CCtxMenu  m_ctx_mnu;
	};

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
		class CGrid {
		public:
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
		public:
			CGrid (void); CGrid (const CGrid&) = delete; CGrid (CGrid&&) = delete; ~CGrid (void) = default;
		private:
			CGrid& operator = (const CGrid&) = delete; CGrid& operator = (CGrid&&) = delete;
		};
	public:
		COrganizer (void); COrganizer (const COrganizer&) = delete; COrganizer (COrganizer&&) = delete; ~COrganizer (void) = default;

	private:
		COrganizer& operator = (const COrganizer&) = delete; COrganizer& operator = (COrganizer&&) = delete;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_3_WND_H_INCLUDED*/