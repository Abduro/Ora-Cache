#ifndef _GL_PROCS_MTX_DEFS_H_INCLUDED
#define _GL_PROCS_MTX_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jun-2026 at 22:33:35.441, UTC+4, Batumi, Saturday;
	This is OpenGL matrix related procedures' common declarations' file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace matrix {
namespace ver_1_1 { using namespace ::open_gl::procs::ver_1_1;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glmatrixmode ;
	enum class e_mode : uint32_t {
	/* alias    | value    | Symbolic defs (gl.h)  | brief description ;
	------------+----------+-----------------------+-------------------*/
	e_modelview = 0x1700,  // GL_MODELVIEW         | applies subsequent matrix operations to the modelview matrix stack; (default mode);
	e_project   = 0x1701,  // GL_PROJECTION        | applies subsequent matrix operations to the projection matrix stack;
	e_texture   = 0x1702,  // GL_TEXTURE           | applies subsequent matrix operations to the texture matrix stack;
	};
	enum class e_mat_type : uint32_t {
	/* alias    | value    | Symbolic defs (gl.h)  | brief description ;
	------------+----------+-----------------------+-------------------*/
	e_modelview = 0x0BA6,  // GL_MODELVIEW_MATRIX  | the modelview matrix on the top of the modelview matrix stack; (default);
	e_project   = 0x0BA7,  // GL_PROJECTION_MATRIX | the projection matrix on the top of the projection matrix stack;
	e_texture   = 0x0BA8,  // GL_TEXTURE_MATRIX    | the texture matrix on the top of the texture matrix stack;
	};

	using e_mat_type = ::open_gl::procs::matrix::ver_1_1::e_mat_type;
	using e_stk_mode = ::open_gl::procs::matrix::ver_1_1::e_mode;

	class CEnum {
	public:
		CEnum (void); CEnum (const CEnum&) = delete; CEnum (CEnum&&) = delete; ~CEnum (void) = default;
		CEnum (const e_mat_type);
		CEnum (const e_stk_mode);

		e_stk_mode Get (const e_mat_type _from) const;
		e_mat_type Get (const e_stk_mode _from) const;

		e_stk_mode operator <<(const e_mat_type) const;
		e_mat_type operator <<(const e_stk_mode) const;

		operator e_stk_mode (void) const;
		operator e_mat_type (void) const;

		static _pc_sz To_str (const e_mat_type);
		static _pc_sz To_str (const e_stk_mode);

	private:
		CEnum& operator = (const CEnum&) = delete; CEnum& operator = (CEnum&&) = delete;
		mutable e_mat_type m_type;
		mutable e_stk_mode m_mode;
	};

	/* the query to Google AI: if casting a value to enumeration does not equal to any enumeration element what cast operation returns?
	   When you cast an out-of-range value to an enumeration, the cast operation returns the exact numeric value you passed it,
	   even though that value does not map to any defined enum element.
	   The cast returns the literal value.
	   In C++, doing this with an out-of-range value can result in *undefined* behavior if the enum does not have a fixed underlying type.
	   ...
	   Who would doubt that :-D
	*/

}}}}

#endif/*_GL_PROCS_MTX_DEFS_H_INCLUDED*/