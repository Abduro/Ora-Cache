#ifndef _TEST_CASE_$M$_PROJECT_H_INCLUDED
#define _TEST_CASE_$M$_PROJECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2026 at 12:11:24.861, UTC+4, Batumi, Thursday;
	This is OpenGL projection matrix wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_procs_matrix.h"
#include "gl_procs_project.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1;
*/
namespace test { namespace open_gl { namespace ver_1_1 {

	using namespace ::open_gl::procs::projection::ver_1_1;
	using CMatMode    = ::open_gl::procs::matrix::ver_1_1::CMode;
	using CMatrix     = ::open_gl::procs::matrix::ver_1_1::CMatrix;
	using e_mat_types = ::open_gl::procs::matrix::ver_1_1::e_mat_type;
	using e_stk_modes = ::open_gl::procs::matrix::ver_1_1::e_modes;
	using f_seq_4x4   = ::open_gl::procs::f_seq_4x4;

	static s_pers_args g_pers_arg(60.0f, 1.0f, 1.0f, 10.0f);

	class CTstMatMode {
	public:
		CTstMatMode (const bool _b_verbose); CTstMatMode (const CTstMatMode&) = delete; CTstMatMode (CTstMatMode&&) = delete; ~CTstMatMode (void) = default;

		err_code Get (void);  // gets current mode of the matrix stack;
		err_code Set (const e_stk_modes); // sets the input matrix stack mode;

		const
		CMatMode& operator ()(void) const;
		CMatMode& operator ()(void) ;

	private:
		CTstMatMode& operator = (const CTstMatMode&) = delete; CTstMatMode& operator = (CTstMatMode&&) = delete;
		CMatMode m_mode;
		bool     m_verbose;
	};

	class CTstMatrix {
	public:
		CTstMatrix (const bool _b_verbose); CTstMatrix (const CTstMatrix&) = delete; CTstMatrix (CTstMatrix&&) = delete; ~CTstMatrix (void) = default;

		err_code Get (const e_mat_types);  // gets a matrix that is currently set in selected matrix stack;
		err_code To_self (void);           // sets identity mode to the top matrix of current matrix stack;

		const
		CMatrix& operator ()(void) const;
		CMatrix& operator ()(void) ;

	private:
		CTstMatrix& operator = (const CTstMatrix&) = delete; CTstMatrix& operator = (CTstMatrix&&) = delete;
		CMatrix m_matrix;
		bool    m_verbose;
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