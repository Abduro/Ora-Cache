#ifndef _GL_SCENE_H_INCLUDED
#define _GL_SCENE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Oct-2025 at 23:55:15.876, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL generic scene wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_context.h"
#include "gl_program.h"
#include "gl_shader.h"
#include "shapes\gl_vertex.h"
#include "shapes\gl_vertex_arr.h"

namespace ex_ui { namespace draw { namespace open_gl {

	class CScene {
	public:
	using CArray = vertex::CArray;
	using CDevCtx = context::CDevice;
	using CDrwCtx = CContext;
	public:
		class CContext {
		public:
			CContext (void) = default; CContext (const CContext&) = delete; CContext (CContext&&) = delete; ~CContext (void) = default;
			const
			CDevCtx& Device (void) const;
			CDevCtx& Device (void) ;
			const
			CDrwCtx& Draw (void) const;
			CDrwCtx& Draw (void) ;
		private:
			CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;
			CDevCtx m_dev_ctx;
			CDrwCtx m_drw_ctx;
		};
	
	public:
		CScene (void); CScene (const CScene&) = delete; CScene (CScene&&) = delete; ~CScene (void);
		const
		CArray&  Array (void) const;
		CArray&  Array (void) ;
		const
		CContext& Ctx (void) const;
		CContext& Ctx (void) ;

		TError&  Destroy (void);
		TError&  Error (void) const;
		err_code Prepare (void);
		const
		CProgram& Prog (void) const;
		CProgram& Prog (void) ;

	private:
		CScene& operator = (const CScene&) = delete; CScene& operator =  (CScene&&) = delete;
		mutable
		CError   m_error;
		CProgram m_prog ;
		CArray   m_array;
		CContext m_ctx;
	};

}}}
#endif/*_GL_SCENE_H_INCLUDED*/