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
#include "gl_vertex_arr.obj.h"
#include "vertex\gl_vertex_attr.h"
#include "vertex\gl_vertex_data.h"

namespace ex_ui { namespace draw { namespace open_gl {

	class CScene {
	public:
	using CDevCtx  = context::CDevice;
	using CDrwCtx  = CContext;
	using CArrObjects = vertex::CArrObj_enum;
	using CProgs   = CProg_enum;
	public:
		class CContext {
		public:
			CContext (void); CContext (const CContext&) = delete; CContext (CContext&&) = delete; ~CContext (void) = default;

			err_code Clear (void); // destroys target GDI context that is retrieved from particular window handle; is called on window destroy message;
			const
			CDevCtx& Device (void) const;
			CDevCtx& Device (void) ;
			const
			CDrwCtx& Draw (void) const;
			CDrwCtx& Draw (void) ;

			TError&  Error (void) const;
		private:
			CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;
			CDevCtx m_dev_ctx;
			CDrwCtx m_drw_ctx;
			CError  m_error;
		};
	
	public:
		CScene (void); CScene (const CScene&) = delete; CScene (CScene&&) = delete; ~CScene (void);

		const
		CArrObjects& ArrObjects (void) const; // returns the reference to vertex array objects (aka vao); (ro)
		CArrObjects& ArrObjects (void) ;      // returns the reference to vertex array objects (aka vao); (rw)
		const
		CContext& Ctx (void) const;
		CContext& Ctx (void) ;

		TError&  Destroy (void);
		TError&  Error   (void) const;
		err_code Prepare (void);
		const
		CProgs&  Progs (void) const;
		CProgs&  Progs (void) ;

	private:
		CScene& operator = (const CScene&) = delete; CScene& operator =  (CScene&&) = delete;
		CArrObjects m_objects;
		CContext    m_ctx;
		CError      m_error;
		CProgs      m_progs;
	};

}}}
#endif/*_GL_SCENE_H_INCLUDED*/