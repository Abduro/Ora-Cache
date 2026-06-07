#ifndef _TEST_CASE_$M$_MATRIX_H_INCLUDED
#define _TEST_CASE_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 12:40:50.196, UTC+4, Batumi, Friday;
	This is OpenGL projection matrix wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_procs_matrix.h"
/*
	These test cases are espacially intended for OpenGL vers 1.1;
*/
namespace test { namespace open_gl { namespace ver_1_1 {

	using namespace ::open_gl::procs::matrix::ver_1_1;

	class CTstMatrix {
	public:
		CTstMatrix (const bool _b_verbose); CTstMatrix (const CTstMatrix&) = delete; CTstMatrix (CTstMatrix&&) = delete; ~CTstMatrix (void) = default;

		err_code Get (const e_mat_type);  // gets a matrix that is currently set in selected matrix stack;
		err_code To_self (void);          // sets identity mode to the top matrix of current matrix stack;

		const
		CMatrix& operator ()(void) const;
		CMatrix& operator ()(void) ;

	private:
		CTstMatrix& operator = (const CTstMatrix&) = delete; CTstMatrix& operator = (CTstMatrix&&) = delete;
		CMatrix m_matrix;
		bool    m_verbose;
	};

}}}

#endif/*_TEST_CASE_$M$_MATRIX_H_INCLUDED*/