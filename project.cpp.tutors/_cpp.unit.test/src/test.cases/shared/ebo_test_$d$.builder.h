#ifndef _EBO_TEST_$D$_BUILDER_H_INCLUDED
#define _EBO_TEST_$D$_BUILDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jan-2026 at 12:46:41.758, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' draw context builder interface declaration file;
*/
#include "_log.h"
#include "gl_context.h"
#include "gl_renderer.h"
#include "gl_program.h"
#include "gl_shader.h"
#include "shared.wnd.fake.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw { using namespace ex_ui::draw::open_gl;

	using namespace ex_ui::draw::open_gl;
	
	using CFakeWnd  = ex_ui::popup::CMsgWnd;
	using CGraphics = ex_ui::draw::open_gl::CGraphics;
	using CDevice   = ex_ui::draw::open_gl::context::CDevice;
	using CProgram  = ex_ui::draw::open_gl::CProgram;
	using $Fragment = ex_ui::draw::open_gl::shader::CFragment;
	using $Vertex   = ex_ui::draw::open_gl::shader::CVertex;

	// all draw objects use the global renderer singleton;
	class CBuilder {
	public:
		CBuilder (void) ;
		CBuilder (const CBuilder&) = delete; CBuilder (CBuilder&&) = delete; ~CBuilder (void) = default;

		class CDevCtx {
		public:
			CDevCtx (void);
			CDevCtx (const CDevCtx&) = delete; CDevCtx (CDevCtx&&) = delete; ~CDevCtx (void) = default;

			err_code Create (void);
			err_code Delete (void);
			TError&  Error  (void) const;
			const
			CFakeWnd& Window (void) const;
			CFakeWnd& Window (void) ;

		private:
			CDevCtx& operator = (const CDevCtx&) = delete; CDevCtx& operator = (CDevCtx&&) = delete;
			CError   m_error ;
			CFakeWnd m_fk_wnd;
		};
		const
		CDevCtx& Device (void) const;
		CDevCtx& Device (void) ;

		TError&  Error  (void) const;

		class CGraphCtx {
		public:
			CGraphCtx (void) ;
			CGraphCtx (const CGraphCtx&) = delete; CGraphCtx (CGraphCtx&&) = delete; ~CGraphCtx (void) = default;

			err_code Create (const HWND _h_target); // for the test cases the fake window handle is used;
			err_code Delete (void);

			TError&  Error  (void) const;
		private:
			CGraphCtx& operator = (const CGraphCtx&) = delete; CGraphCtx& operator = (CGraphCtx&&) = delete;
			CError m_error;
		};
		const
		CGraphCtx& Graph (void) const;
		CGraphCtx& Graph (void) ;

		class CProg : public CPipeline { typedef CPipeline TBase; // the pipline helps to identify the target draw object;
		public:
			CProg (const e_object = e_object::e_grid); // creates grid program by default for testing matrices throug shaders;
			CProg (const CProg&) = delete; CProg (CProg&&) = delete; ~CProg (void) = default;

			err_code Create (void);
			err_code Delete (void);
			TError&  Error  (void) const;

		private:
			CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
			CError   m_error;
		};
		const
		CProg& Prog (void) const;
		CProg& Prog (void) ;

		err_code Release (void);  // deletes the graphics object first and then the device context second;

		// the shaders class uses program shader cache that is declared in gl_$_cache.h;
		class CShaders : public CPipeline { typedef CPipeline TBase;
		public:
			CShaders (const e_object = e_object::e_grid);
			CShaders (const CShaders&) = delete; CShaders (CShaders&&) = delete; ~CShaders (void) = default;

			err_code Create (void); // creates all shaders;

			const
			$Fragment& Fragment (void) const; // gets the reference to fragment shader of the program by given object type;
			$Fragment& Fragment (void) ;      // gets the reference to fragment shader of the program by given object type;

			TError&  Error  (void) const;
			const
			$Vertex& Vertex (void) const; // gets the reference to vertex shader of the program by given object type;
			$Vertex& Vertex (void)      ; // gets the reference to vertex shader of the program by given object type;
		private:
			CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
			CError   m_error;
		};
		const
		CShaders& Shaders (void) const;
		CShaders& Shaders (void) ;

	private:
		CBuilder& operator = (const CBuilder&) = delete; CBuilder& operator = (CBuilder&&) = delete;
		CDevCtx   m_device;
		CError    m_error;
		CGraphCtx m_graph;
		CProg     m_prog ;
		CShaders  m_shaders;
	};
}}}}}

#endif/*_EBO_TEST_$D$_BUILDER_H_INCLUDED*/