#ifndef _EBO_TEST_$M$_STACK_H_INCLUDED
#define _EBO_TEST_$M$_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2026 at 09:28:16.577, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix stack uint test interface declaration file; 
*/
#include "test_case_$d$.ctx.h"     // for using OpenGL API draw context must be created first;
#include "test_case_$m$.stack.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	/* The matrix stack functionality (glMatrixMode, glGetFloatv, glLoadIdentity, etc.) is part of the "fixed-function pipeline" and has been deprecated since OpenGL 3.1.
	   OpenGL (3.1+ Core Profile, OpenGL ES 2.0+) requires to manage matrices in application code and pass them to shaders using uniforms;
	   Thus, testing functionality of classes below is useless:
	   cls::[CError]>>{code=0x0502;result=0x80070502;desc='#__e_state: Invalid state for getting the pointer';context=CBase::CParam::Get_ptr()}
	*/
	__class (c_stk_current) {
	public:
		 c_stk_current (void);
		~c_stk_current (void) = default;

		__method (Get);
		__method (Set);
	};

	__class (c_mat_stack) {
	public:
		 c_mat_stack (void);
		~c_mat_stack (void) = default;

		__method (Get);
		__method (Pop);
		__method (Push);
	};

}}}}}

#endif/*_EBO_TEST_$M$_STACK_H_INCLUDED*/