#ifndef _GL_PROCS_MTX_OPER_H_INCLUDED
#define _GL_PROCS_MTX_OPER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 18:26:20.598, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace matrix {
namespace ver_1_1 {
	using namespace ::open_gl::procs::ver_1_1;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glmultmatrixf ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glscalef ; what matrix mode must be applied before calling glScale opengl version 1.1? (ModelView|Projection)
	// https://learn.microsoft.com/en-us/windows/win32/opengl/gltranslate ;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/gltranslatef ;

	class COpers : public CBasic { typedef CBasic TBase;
	public:
		COpers (void); COpers (const COpers&) = delete; COpers (COpers&&) = delete; ~COpers (void) = default;

		err_code Multiply (const f_mat_4x4& _by);
		err_code Scale (const f_set_3& _to);     // scales current matrix in 'model-view' matrix stack;

		err_code Rotate (float _f_angle, float _x, float _y, float _z); // https://learn.microsoft.com/en-us/windows/win32/opengl/glrotatef ;
		err_code Rotate (float _f_angle, const f_set_3& _where); // input f_set_3 >> x|y|z;

		/* the query to Google AI: what error can be thrown by glTranslatef opengl?
		The glTranslatef function in OpenGL can only throw one specific runtime error: GL_INVALID_OPERATION;
		Logical errors:
		Matrix Mode: translating while the projection matrix is active instead of the modelview matrix;
		Camera / Frustum Clipping: translating an object out of the visible viewing volume (e.g., translating too far along the positive Z-axis, which pushes it behind the camera);
		State Order: translating after other transformations (like glRotatef) in the wrong sequence; OpenGL transforms operate in *reverse order* of how you type them.
		*/
		err_code Translate (const float _x, const float _y, const float _z); // input _x, _y, and _z is coordinates of a translation vector;
		err_code Translate (const f_set_3& _what); // input f_set_3 >> x|y|z;

	private:
		COpers& operator = (const COpers&) = delete; COpers& operator = (COpers&&) = delete;
	};
}
namespace arb {}

}}}
#if (0)
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
#endif
#endif/*_GL_PROCS_MTX_OPER_H_INCLUDED*/