#ifndef _OPEN_GL_TUTOR_1_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_1_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 02:53:28.276, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface declaration file;
*/
#include "shared.wnd.base.h"
#include "shared.wnd.layout.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	using namespace shared::defs;
	using namespace shared::types;

	using namespace ex_ui::popup;
	using namespace ex_ui::popup::layout;

	using TWindow = ex_ui::popup::CWndBase;

	class CWnd : public TWindow { typedef TWindow TBase;
	public:
		 CWnd (void);
		~CWnd (void);

		err_code Create (void);
	};

}}}}

#endif/*_OPEN_GL_TUTOR_1_WND_H_INCLUDED*/