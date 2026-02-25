#ifndef _GL_PROCS_MATH_H_INCLUDED
#define _GL_PROCS_MATH_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jan-2026 at 21:32:27.495, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL math functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace math {
	// https://docs.gl/gl3/glMatrixMode;
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMatrixMode.xml ;
	enum e_mat_mode : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_color     = 0x1800,  // GL_COLOR                 | applies subsequent matrix operations to the color matrix stack;
	e_modelview = 0x1700,  // GL_MODELVIEW             | applies subsequent matrix operations to the modelview matrix stack;
	e_project   = 0x1701,  // GL_PROJECTION            | applies subsequent matrix operations to the projection matrix stack;
	e_texture   = 0x1702,  // GL_TEXTURE               | applies subsequent matrix operations to the texture matrix stack;
	e_undef     = 0x0,     // for error case;
	};
	_pc_sz _mat_mode_2_str(const e_mat_mode);

	typedef e_mat_mode e_mat_type;
	typedef ::std::array<float, 0x10u> t_arr_4x4; // the matrix defines its data as t_seq_4x4 that is the same with t_arr_4x4, but for creating a weak dependency between projects, typedefs are defined separately;

	class CMatrix : public CBase {
	typedef void (__stdcall *pfn_Identity)(void); // https://docs.gl/gl3/glLoadIdentity ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadIdentity.xml ;
	typedef void (__stdcall *pfn_Multiply)(const float*); // https://docs.gl/gl3/glMultMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMultMatrix.xml ;
	typedef void (__stdcall *pfn_MultTransp)(const float*); // https://docs.gl/gl3/glMultTransposeMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMultTransposeMatrix.xml ;
	typedef void (__stdcall *pfn_Load)(const float*); // https://docs.gl/gl3/glLoadMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadMatrix.xml;
	typedef void (__stdcall *pfn_Pop)(void); // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml
	typedef void (__stdcall *pfn_Push)(void); // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml
	typedef void (__stdcall *pfn_Transpose)(const float*); // https://docs.gl/gl3/glLoadTransposeMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadTransposeMatrix.xml ;
	public:
		class CMode : public CBase {
		typedef void (__stdcall *pfn_Set)(const uint32_t u_mode);
		public:
			CMode (void); ~CMode (void) = default;

			err_code   Get_all (void);

			e_mat_mode Get (void) const;       // returns e_mat_mode::e_undef in case of error;
			err_code   Set (const e_mat_mode); // sets the current mode of the matrix stack;

		private:
			CMode& operator = (const CMode&) = delete; CMode& operator = (CMode&&) = delete;
		};
	public:
		CMatrix (void); ~CMatrix (void) = default;

		err_code Get_all (void);
		err_code Get (const e_mat_type, t_arr_4x4&); // fills the input array by matrix data (array of 16 floats); in case of error input array data is not changed;

		err_code Identity (void);  // replaces the current matrix with the identity matrix;
		err_code Multiply (const float* _p_mat4x4, const bool _b_transp = false);  // multiplies the current matrix with the specified matrix; 
		err_code Load (const float* _p_mat4x4, const bool _b_transp = false);      // replaces the current matrix with the specified matrix; the input pointer is checked for null only;
		err_code Pop  (void); // pops the current matrix stack, replacing the current matrix with the one below it on the stack;
		err_code Push (void); // pushes the current matrix stack down by one, duplicating the current matrix;

	private:
		CMatrix& operator = (const CMatrix&) = delete; CMatrix& operator = (CMatrix&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::math::CMatrix TMatrixProcs; TMatrixProcs& __get_matrix_procs (void);
typedef ex_ui::draw::open_gl::procs::math::CMatrix::CMode TMatModeProcs; TMatModeProcs& __get_mat_mode_procs (void);

#endif/*_GL_PROCS_MATH_H_INCLUDED*/