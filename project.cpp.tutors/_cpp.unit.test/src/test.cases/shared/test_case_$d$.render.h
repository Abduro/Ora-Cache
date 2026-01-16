#ifndef _TEST_CASE_$D$_RENDER_H_INCLUDED
#define _TEST_CASE_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:16:30.545, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL draw renderer wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.prog.h"
#include "test_case_$d$.shape.2d.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	class CFake_renderer : public TPipe {
	public:
		CFake_renderer (const e_object = e_object::e_none);
		CFake_renderer (const CFake_renderer&) = delete; CFake_renderer (CFake_renderer&&) = delete; ~CFake_renderer (void) = default;

		const
		CCtx_auto& Ctx (void) const;
		CCtx_auto& Ctx (void) ;

		static
		err_code  Draw  (const e_object, CError&);
		err_code  Draw  (void) ;
		TError&   Error (void) const;
		// the process of drawing must be interrupted on the middle point, otherwise the testing uniform variables is not applicable;
		err_code  On_draw_begin (void); // this method calls open_gl draw funtion(s) for running shaders' script;
		err_code  On_draw_end (void);   // just cleans all objects related to draw operation above;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		CFake_renderer& operator = (const CFake_renderer&) = delete; CFake_renderer& operator = (CFake_renderer&&) = delete;
		CError    m_error;
		CCtx_auto m_ctx_auto; // this context object must be kept for calling On_draw_begin() and then On_draw_end(), otherwise context handles are different;
	};
}}}}}

#endif/*_TEST_CASE_$D$_RENDER_H_INCLUDED*/