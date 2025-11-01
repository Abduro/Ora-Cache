#ifndef _GL_RENDERER_H_INCLUDED
#define _GL_RENDERER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:40:16.148, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface declaration file;
*/
#include "gl_defs.h"
#include "gl_scene.h"
#include "gl_viewport.h"

namespace ex_ui { namespace draw { namespace open_gl {

	class CRenderer {
	private: CRenderer (const CRenderer&) = delete;  CRenderer (CRenderer&&) = delete;
	public : CRenderer (void); ~CRenderer (void);

		TError& Error (void) const;
		const
		CScene& Scene (void) const;
		CScene& Scene (void) ;
		const
		CViewPort& View (void) const;
		CViewPort& View (void) ;

	private: CRenderer& operator = (const CRenderer&) = delete; CRenderer& operator = (CRenderer&&) = delete;
	mutable  CError m_error;
		CScene    m_scene;
		CViewPort m_view ;
	};

}}}

#endif/*_GL_RENDERER_H_INCLUDED*/