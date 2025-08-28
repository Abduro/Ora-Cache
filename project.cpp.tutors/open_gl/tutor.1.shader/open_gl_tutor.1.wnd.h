#ifndef _OPEN_GL_TUTOR_1_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_1_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 02:53:28.276, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface declaration file;
*/
#include "shared.wnd.base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shade {

	using TWindow = ex_ui::popup::CWnd;

	class CWnd : public TWindow {
	public:
		 CWnd (void);
		~CWnd (void);
	};

}}}}

#endif/*_OPEN_GL_TUTOR_1_WND_H_INCLUDED*/