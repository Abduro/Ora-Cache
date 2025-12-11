#ifndef _GL_RENDERER_H_INCLUDED
#define _GL_RENDERER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:40:16.148, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface declaration file;
*/
#include "gl_defs.h"
#include "gl_scene.h"
#include "gl_viewport.h"

#include "shared.wnd.msg.h"
#include "shared.theme.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace render {
	class CCfg : private no_copy {
	public:
		CCfg (void); ~CCfg (void) = default;

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
}
	using IKbrd_Handler = ex_ui::popup::IKbrd_Handler;
	using CTheme = shared::gui::theme::CTheme;

	class CRenderer : public IKbrd_Handler {
	using CCfg = render::CCfg;
	private: CRenderer (const CRenderer&) = delete;  CRenderer (CRenderer&&) = delete;
	public : CRenderer (void); ~CRenderer (void);

		TError&  IKbrd_Error (void) const;
		err_code IKbrd_OnKeyDown (const uint32_t _v_key, const bool _b_repeat, const bool _b_extend) override final;

		const
		CCfg& Cfg (void) const;
		CCfg& Cfg (void) ;

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
		CTheme      m_theme;
		CViewPort   m_view ;
		CCfg  m_cfg;
		bool  m_b_allowed; 
	};

}}}

typedef ex_ui::draw::open_gl::CRenderer TRenderer; TRenderer&  Get_renderer (void);

#endif/*_GL_RENDERER_H_INCLUDED*/