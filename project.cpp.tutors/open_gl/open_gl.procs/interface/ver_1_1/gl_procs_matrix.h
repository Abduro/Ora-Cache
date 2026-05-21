#ifndef _GL_PROCS_MATRIX_H_INCLUDED
#define _GL_PROCS_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 16:13:11.611, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 matrix related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"
#include "math.matrix.h"
/*
	These procedure wrappers are espacially intended for OpenGL vers 1.1 API (aka legacy);
*/
namespace open_gl { namespace procs { namespace ver_1_1 {
namespace matrix {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glmatrixmode ;
	enum e_modes : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_modelview = 0x1700,  // GL_MODELVIEW             | applies subsequent matrix operations to the modelview matrix stack; (default mode);
	e_project   = 0x1701,  // GL_PROJECTION            | applies subsequent matrix operations to the projection matrix stack;
	e_texture   = 0x1702,  // GL_TEXTURE               | applies subsequent matrix operations to the texture matrix stack;
	};

	class CMode : public CBasic { typedef CBasic TBase;
	public:
		CMode (void); CMode (const CMode&) = delete; CMode (CMode&&) = delete; ~CMode (void) = default;

		e_modes  Get (void) const;    // returns e_mat_mode::e_modelview in case of error, because it is the default mode;
		err_code Get (void) ;         // queries OpenGL driver for currend matrix state;
		err_code Set (const e_modes); // sets the current mode of the matrix stack;
		const
		CMode& operator >>(e_modes&) const; // gets the current mode of the matrix stack;
		CMode& operator <<(const e_modes);  // sets the current mode of the matrix stack;

		bool   Is_model   (void) const;  // returns 'true' if the current mode is 'modelview';
		bool   Is_project (void) const;  // returns 'true' if the current mode is 'projection';
		bool   Is_textrue (void) const;  // returns 'true' if the current mode is 'texture';

		static _pc_sz To_str (const e_modes);

	private:
		CMode& operator = (const CMode&) = delete; CMode& operator = (CMode&&) = delete;
		e_modes m_current;
	};
}
	using c_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;
	enum e_mat_type : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_modelview = GL_MODELVIEW_MATRIX , // the modelview matrix on the top of the modelview matrix stack;
	e_project   = GL_PROJECTION_MATRIX, // the projection matrix on the top of the projection matrix stack;
	e_texture   = GL_TEXTURE_MATRIX   , // the texture matrix on the top of the texture matrix stack;
	};

	class CMatrix : public CBasic { typedef CBasic TBase;
	public:
		CMatrix (void); CMatrix (const CMatrix&) = delete; CMatrix (CMatrix&&) = delete; ~CMatrix (void) = default;

		err_code Get (const e_mat_type, c_mat4x4&); // gets current matrix from the matrix stack;
		err_code To_self (void); // loads matrix identity to stack;

	private:
		CMatrix& operator = (const CMatrix&) = delete; CMatrix& operator = (CMatrix&&) = delete;
	};

}}}

typedef ::open_gl::procs::ver_1_1::matrix::CMode TMatMode;

#endif/*_GL_PROCS_MATRIX_H_INCLUDED*/