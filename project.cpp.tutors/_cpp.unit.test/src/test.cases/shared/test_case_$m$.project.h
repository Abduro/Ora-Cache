#ifndef _TEST_CASE_$M$_PROJECT_H_INCLUDED
#define _TEST_CASE_$M$_PROJECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2026 at 12:11:24.861, UTC+4, Batumi, Thursday;
	This is OpenGL projection matrix wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$m$.defs.h"
#include "test_case_$m$.mat4x4.h"
#include "ver_1_1\gl_procs_proj.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1;
*/
namespace test { namespace open_gl { namespace ver_1_1 { using namespace test::open_gl::math;

	using CPerspect = ::open_gl::procs::ver_1_1::projection::CPerspect;
	using s_pers_args = ::open_gl::procs::ver_1_1::projection::s_pers_args;
	using e_stk_modes = ::open_gl::procs::ver_1_1::matrix::e_modes;

	static s_pers_args g_pers_arg(60.0f, 1.0f, 1.0f, 10.0f);

	class CTstMatMode {
	public:
		CTstMatMode (const bool _b_verbose); CTstMatMode (const CTstMatMode&) = delete; CTstMatMode (CTstMatMode&&) = delete; ~CTstMatMode (void) = default;

		err_code Get (void);  // gets current mode of the matrix stack;
		err_code Set (const e_stk_modes); // sets the input matrix stack mode;

		const
		TMatMode& operator ()(void) const;
		TMatMode& operator ()(void) ;

	private:
		CTstMatMode& operator = (const CTstMatMode&) = delete; CTstMatMode& operator = (CTstMatMode&&) = delete;
		TMatMode m_mode;
		bool     m_verbose;
	};

	class CTstPerspect {
	public:
		CTstPerspect (const bool _b_verbose); CTstPerspect (const CTstPerspect&) = delete; CTstPerspect (CTstPerspect&&) = delete; ~CTstPerspect (void) = default;

		err_code Get (void);
		err_code Set (const s_pers_args&);

		const
		CPerspect& operator ()(void) const;
		CPerspect& operator ()(void) ;

	private:
		CTstPerspect& operator = (const CTstPerspect&) = delete; CTstPerspect& operator = (CTstPerspect&&) = delete;
		CPerspect m_perspect;
		bool      m_verbose;
	};

}}}

#endif/*_TEST_CASE_$M$_PROJECT_H_INCLUDED*/