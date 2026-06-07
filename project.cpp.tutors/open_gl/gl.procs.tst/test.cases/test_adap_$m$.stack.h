#ifndef _TEST_ADAP_$M$_STACK_H_INCLUDED
#define _TEST_ADAP_$M$_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2026 at 09:28:16.577, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix stack uint test adapter interface declaration file; 
*/
#include "test_case_$m$.stack.h"

namespace test { namespace open_gl { namespace ver_1_1 {

	/* The matrix stack functionality (glMatrixMode, glGetFloatv, glLoadIdentity, etc.) is part of the "fixed-function pipeline" and has been deprecated since OpenGL 3.1.
	   OpenGL (3.1+ Core Profile, OpenGL ES 2.0+) requires to manage matrices in application code and pass them to shaders using uniforms;
	   Thus, testing functionality of classes below is useless in case if base version 1.1 of the OpenGL is not used:
	   cls::[CError]>>{code=0x0502;result=0x80070502;desc='#__e_state: Invalid state for getting the pointer';context=CBase::CParam::Get_ptr()}
	*/
	__class (c_stk_mode) {
	public:
		 c_stk_mode (void) = default; c_stk_mode (const c_stk_mode&) = delete; c_stk_mode (c_stk_mode&&) = delete; ~c_stk_mode (void) = default;

		__method (Get);
		__method (Set);

	private:
		c_stk_mode& operator = (const c_stk_mode&) = delete; c_stk_mode& operator = (c_stk_mode&&) = delete;
	};

	__class (c_mat_stack) {
	public:
		 c_mat_stack (void) = default; c_mat_stack (const c_mat_stack&) = delete; c_mat_stack (c_mat_stack&&) = delete; ~c_mat_stack (void) = default;

		__method (Get);
		__method (Pop);
		__method (Push);

	private:
		c_mat_stack& operator = (const c_mat_stack&) = delete; c_mat_stack& operator = (c_mat_stack&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$M$_STACK_H_INCLUDED*/