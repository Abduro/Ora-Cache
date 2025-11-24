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

	class CRender_Cfg : private no_copy {
	public:
		CRender_Cfg (void); ~CRender_Cfg (void) = default;

		uint32_t Count (void) const;              // returns how many vertices must be drawn;
		bool     Count (const uint32_t);          // returns 'true' in case of count number of vertices is changed;

		uint32_t Primitive (void) const;          // returns the draw mode value, i.e. what type of primitives must be drawn; procs::CPrimitives::e_others::e_points is default;
		bool     Primitive (const uint32_t);      // returns 'true' in case of draw mode value is changed;

		uint32_t StartAt (void) const;            // returns the vertex arrey index to start from for drawing;
		bool     StartAt (const uint32_t _u_ndx); // returns 'true' in case of start index value change;

	private:
		uint32_t m_count_ndx;
		uint32_t m_prim_mode;
		uint32_t m_start_ndx;
	};

	class CRenderer {
	private: CRenderer (const CRenderer&) = delete;  CRenderer (CRenderer&&) = delete;
	public : CRenderer (void); ~CRenderer (void);

		const
		CRender_Cfg&  Cfg (void) const;
		CRender_Cfg&  Cfg (void) ;

		err_code Draw (void) ;

		TError& Error (void) const;

		bool  Is_allowed (void) const; // returns the value of the flag for the availability of the drawing operation; by default is set to 'false';
		bool  Is_allowed (const bool); // sets the flag value of the availability of the drawing operation; e.g. is set to 'false' on app exit process;

		const
		CScene& Scene (void) const;
		CScene& Scene (void) ;
		const
		CViewPort& View (void) const;
		CViewPort& View (void) ;

	private: CRenderer& operator = (const CRenderer&) = delete; CRenderer& operator = (CRenderer&&) = delete;
	mutable  CError m_error;
		CScene      m_scene;
		CViewPort   m_view ;
		CRender_Cfg m_cfg;
		bool  m_b_allowed; 
	};

}}}

#endif/*_GL_RENDERER_H_INCLUDED*/