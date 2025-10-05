#ifndef _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_FAKE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:16:27.485, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL fake (message-only) window interface declaration file;
*/
#include "open_gl_tutor.0.defs.h"
#include "shared.wnd.fake.h"

namespace ex_ui { namespace draw { namespace open_gl {  namespace fake {

	using namespace ex_ui::draw::open_gl;

	class CWnd : public ex_ui::popup::CMsgWnd { typedef ex_ui::popup::CMsgWnd TWindow;
	public:
		 CWnd (void); CWnd (const CWnd&) = delete; CWnd (CWnd&&) = delete;
		~CWnd (void);
	};

}}}}

typedef ex_ui::draw::open_gl::fake::CWnd  TFakeWnd;

#endif/*_OPEN_GL_TUTOR_0_FAKE_H_INCLUDED*/