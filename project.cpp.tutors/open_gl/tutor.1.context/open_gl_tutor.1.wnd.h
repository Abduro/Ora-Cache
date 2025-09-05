#ifndef _OPEN_GL_TUTOR_1_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_1_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 13:17:17.613, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' context window interface declaration file;
*/
#include "shared.wnd.base.h"    // is declared in shared.trim_v15.lib project;
#include "shared.wnd.layout.h"  // the same as above;

namespace ex_ui { namespace draw { namespace open_gl { namespace context {

	using namespace shared::defs;
	using namespace shared::types;

	using namespace ex_ui::popup;
	using namespace ex_ui::popup::layout;

	using TWindow = ex_ui::popup::CWndBase;
	// it is not the main window of this tutor app, it is just the child of it for creating the OpenGL draw context, i.e. it is the target window;
	class CWnd : public TWindow { typedef TWindow TBase;
	public:
		 CWnd (void);
		~CWnd (void);

		err_code Create (const HWND _h_parent, const t_rect&, const bool _b_visible = true); // this window position rectangle is defined by parent window layout;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_1_WND_H_INCLUDED*/