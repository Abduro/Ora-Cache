#ifndef _TEST_ADAP_$D$_PROG_H_INCLUDED
#define _TEST_ADAP_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jan-2026 at 22:01:05.284, UTC+4, Batumi, Friday;
	This is OpenGL tutorials' program wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.prog.h"

namespace test { namespace open_gl { namespace prog {

	using CTstGraph = test::open_gl::context::arb::CTstGraph;
	/* creating device context and graphics must be made before creating a program object;
	   important:
	   these test cases will not be passed due to the renderer pipeline is not used by graphics object;
	   it is made for testing projection matrices by OpenGL ver 1.1 and this does not require the arb or above rendering pipline;
	*/
	__class (c_prog) {
	public:
		  c_prog (void) = default; c_prog (const c_prog&) = delete; c_prog (c_prog&&) = delete;
		 ~c_prog (void) = default;

		 __method (Grid); // this test case sets the appropriate target to program that may be inconsistent with the target of this test class;
		 __method (Tria); // this test case sets the appropriate target to program that may be inconsistent with the target of this test class;

		 const
		 TPipe& operator ()(void) const;
		 TPipe& operator ()(void) ;

	private:
		c_prog& operator = (const c_prog&) = delete; c_prog& operator = (c_prog&&) = delete;
		TPipe m_pipe;
	};
}}}

#endif/*_TEST_ADAP_$D$_PROG_H_INCLUDED*/