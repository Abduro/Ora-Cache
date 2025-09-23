#ifndef _OPEN_GL_TUTOR_2_WND_H_INCLUDED
#define _OPEN_GL_TUTOR_2_WND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 02:53:28.276, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface declaration file;
*/
#include "open_gl_tutor.1.wnd.h"
#include "gl_shader.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	using namespace shared::defs;
	using namespace shared::types;

	using namespace ex_ui::popup;
	using namespace ex_ui::popup::layout;

	using TCtxWindow = ex_ui::draw::open_gl::context::CWnd;

	class CWnd : public TCtxWindow { typedef TCtxWindow TParent;
	public:
		 CWnd (void);
		~CWnd (void);

		err_code Create (const HWND _h_parent, const t_rect&, const bool _b_visible = true);
		const
		CShader& Shader (void) const;
		CShader& Shader (void) ;

	protected:
		CShader m_shader;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_2_WND_H_INCLUDED*/