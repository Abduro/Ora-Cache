#ifndef _GL_PROCS_MTX_OPER_H_INCLUDED
#define _GL_PROCS_MTX_OPER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 18:26:20.598, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace matrix {

		class COpers : public CBase {
		typedef void (__stdcall *pfn_Multiply)(const float*); // https://docs.gl/gl3/glMultMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMultMatrix.xml ;
		typedef void (__stdcall *pfn_MultTransp)(const float*); // https://docs.gl/gl3/glMultTransposeMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMultTransposeMatrix.xml ;
		typedef void (__stdcall *pfn_Rotate)(float _f_angle, float _x, float _y, float _z); // https://docs.gl/gl3/glRotate ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml ;
		typedef void (__stdcall *pfn_Translate)(float _x, float _y, float _z); // https://docs.gl/gl3/glTranslate ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml ;
		public:
			COpers (void); COpers (const COpers&) = delete; COpers (COpers&&) = delete; ~COpers (void) = default;

			err_code Get_all (void);
			err_code Multiply (const float* _p_mat4x4, const bool _b_transp = false);  // multiplies the current matrix with the specified matrix;
			err_code Translate (const float _x, const float _y, const float _z); // input _x, _y, and _z is coordinates of a translation vector;

		private:
			COpers& operator = (const COpers&) = delete; COpers& operator = (COpers&&) = delete;
		};

}}}}}

#endif/*_GL_PROCS_MTX_OPER_H_INCLUDED*/