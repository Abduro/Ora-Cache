#ifndef _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
#define _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:16:48.217, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum unit test adapter interface declaration file; 
*/
#include "test_case_$m$.frustum.h"
#include "test_case_$m$.project.h"
#include "test_case_$p$.viewport.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1;
*/
namespace test { namespace open_gl { namespace frustum {
#if (0)
	__class (c_frustum) {
	public:
		c_frustum (void) = default; c_frustum (const c_frustum&) = delete; c_frustum (c_frustum&&) = delete; ~c_frustum (void) = default;

		__method (Get_perspect); // calculates perspective projection matrix; (this is manual calculation);
		__method (Set_aspect);   // sets pre-defined surface window size;
		__method (Set_defaults); // gets default configuration values;

	private:
		c_frustum& operator = (const c_frustum&) = delete; c_frustum& operator = (c_frustum&&) = delete;
	};
#endif
	__class (c_project) {
	public:
		c_project (void) = default; c_project (const c_project&) = delete; c_project (c_project&&) = delete; ~c_project (void) = default;

		__method (Get);  // gets the projection perspective matrix;
		__method (Set);  // sets the projection perspective matrix; important: matrix stack mode object is in CPerspect class, it must be used;

	private:
		c_project& operator = (const c_project&) = delete; c_project& operator = (c_project&&) = delete;
	};

	__class (c_stk_mode) {
	public:
		c_stk_mode (void) = default; c_stk_mode (const c_stk_mode&) = delete; c_stk_mode (c_stk_mode&&) = delete; ~c_stk_mode (void) = default;

		__method (Get);
		__method (Set);

	private:
		c_stk_mode& operator = (const c_stk_mode&) = delete; c_stk_mode& operator = (c_stk_mode&&) = delete;
	};
}}}

#endif/*_TEST_ADAP_$M$_FRUSTUM_H_INCLUDED*/