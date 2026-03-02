#ifndef _GL_PROCS_MTX_STACK_H_INCLUDED
#define _GL_PROCS_MTX_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 19:21:28.597, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace matrix {
	// the matrix defines its data as t_seq_4x4 that is the same with t_arr_4x4,
	// but for creating a weak dependency between projects, typedefs are defined separately;
	typedef ::std::array<float, 0x10u> t_arr_4x4;
#pragma region _refs_0xa
	// unfortunately, this is outdated code, 'fixed-function' pipeline state, as they say these days;
	// https://stackoverflow.com/questions/4202456/how-do-you-get-the-modelview-and-projection-matrices-in-opengl ;
	// https://stackoverflow.com/questions/4202456/how-do-you-get-the-modelview-and-projection-matrices-in-opengl#comment50800529_4203639 ;
	// https://stackoverflow.com/questions/4202456/how-do-you-get-the-modelview-and-projection-matrices-in-opengl#comment140090901_4203639 ;
#pragma endregion
	enum class e_mat_type : uint32_t {
	/* alias    | value    | OpenGL symbolic defs(gl.h)| brief description ;
	------------+----------+---------------------------+-------------------*/
	e_color     = 0x80B1,  // GL_COLOR_MATRIX          | GL_ARB_imaging extension, used to manipulate the color transformation matrix;
	e_modelview = 0x0BA6,  // GL_MODELVIEW_MATRIX      | the modelview matrix on the top of the modelview matrix stack; initially is set to identity;
	e_project   = 0x0BA7,  // GL_PROJECTION_MATRIX     | the projection matrix on the top of the projection matrix stack; initially is set to identity;
	e_texture   = 0x0BA8,  // GL_TEXTURE_MATRIX        | the texture matrix on the top of the texture matrix stack; initially is set to identity;
	e_undef     = 0x0,     // for error case;          | no complains;
	};

	class CStack : public CBase {
	typedef void (__stdcall *pfn_Pop)(void);  // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml ;
	typedef void (__stdcall *pfn_Push)(void); // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml ;
	public:
		CStack (void); CStack (const CStack&) = delete; CStack (CStack&&) = delete; ~CStack (void) = default;

		err_code Get_all (void);
		err_code Get  (const e_mat_type, t_arr_4x4&); // fills the input array by matrix data (array of 16 floats); in case of error input array data is not changed;
		err_code Pop  (void); // pops the current matrix stack, replacing the current matrix with the one below it on the stack;
		err_code Push (void); // pushes the current matrix stack down by one, duplicating the current matrix;

		static
		_pc_sz   To_str (const e_mat_type);

	private:
		CStack& operator = (const CStack&) = delete; CStack& operator = (CStack&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::matrix::CStack TStackProcs; TStackProcs& __get_stack_procs (void);

#endif/*_GL_PROCS_MTX_STACK_H_INCLUDED*/