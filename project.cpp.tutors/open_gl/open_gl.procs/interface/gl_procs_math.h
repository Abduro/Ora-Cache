#ifndef _GL_PROCS_MATH_H_INCLUDED
#define _GL_PROCS_MATH_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jan-2026 at 21:32:27.495, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL math functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
#include "matrix\gl_procs_mtx.mode.h"
#include "matrix\gl_procs_mtx.oper.h"
#include "matrix\gl_procs_mtx.stack.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace math { using namespace ex_ui::draw::open_gl::procs::matrix;

	class CMatrix : public CBase {
	typedef void (__stdcall *pfn_Identity)(void); // https://docs.gl/gl3/glLoadIdentity ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadIdentity.xml ;
	typedef void (__stdcall *pfn_Load)(const float*); // https://docs.gl/gl3/glLoadMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadMatrix.xml ;
	typedef void (__stdcall *pfn_Orpho)(
		double _left, double _right, double _bottom, double _top, double _near, double _far
	); // https://docs.gl/gl3/glOrtho ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml ;
	public:
		CMatrix (void); ~CMatrix (void) = default;

		err_code Get_all (void);

		err_code Identity (void);  // replaces the current matrix with the identity matrix;
		err_code Load (const float* _p_mat4x4, const bool _b_transp = false); // replaces the current matrix with the specified matrix; the input pointer is checked for null only;

	private:
		CMatrix& operator = (const CMatrix&) = delete; CMatrix& operator = (CMatrix&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::math::CMatrix TMatrixProcs; TMatrixProcs& __get_matrix_procs (void);

#endif/*_GL_PROCS_MATH_H_INCLUDED*/