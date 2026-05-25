#ifndef _TEST_CASE_$D$_RENDER_H_INCLUDED
#define _TEST_CASE_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:16:30.545, UTC+4, Batumi, Thursday;
	This is OpenGL draw renderer wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.prog.h"
#include "test_case_$d$.shape.2d.h"

namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;
	using CTstDev   = test::open_gl::context::CTstDevice;
	using CTstGraph = test::open_gl::context::arb::CTstGraph;
	/* note:
	   this test cases will not be passed successfully because the draw pipeline of the renderer is not used for creating graphics object;
	   graphics object is created independently for testing projection matrix transformation by OpenGL version 1.1;
	   these test cases will be reviewed in order to restore both use cases of the graphics object;
	*/
	class CTstRenderer : public TPipe {
	public:
		CTstRenderer (const e_object = e_object::e_none);
		CTstRenderer (const CTstRenderer&) = delete; CTstRenderer (CTstRenderer&&) = delete; ~CTstRenderer (void) = default;

		err_code  Draw  (void) ;
		// the process of drawing must be interrupted on the middle point, otherwise the testing uniform variables is not applicable;
		err_code  On_draw_begin (void); // this method calls open_gl draw funtion(s) for running shaders' script;
		err_code  On_draw_end (void);   // just cleans all objects related to draw operation above;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		CTstRenderer& operator = (const CTstRenderer&) = delete; CTstRenderer& operator = (CTstRenderer&&) = delete;
		CTstGraph m_graph; // this context object must be kept for calling On_draw_begin() and then On_draw_end(), otherwise context handles are different;
	};
}}}

#endif/*_TEST_CASE_$D$_RENDER_H_INCLUDED*/