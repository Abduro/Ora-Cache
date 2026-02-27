#ifndef _GL_PROCS_MTX_STACK_H_INCLUDED
#define _GL_PROCS_MTX_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 19:21:28.597, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace matrix {

	class CStack : public CBase {
	typedef void (__stdcall *pfn_Pop)(void); // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml ;
	typedef void (__stdcall *pfn_Push)(void); // https://docs.gl/gl3/glPushMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml ;
	public:
		CStack (void); CStack (const CStack&) = delete; CStack (CStack&&) = delete; ~CStack (void) = default;

		err_code Get_all (void);
		err_code Pop  (void); // pops the current matrix stack, replacing the current matrix with the one below it on the stack;
		err_code Push (void); // pushes the current matrix stack down by one, duplicating the current matrix;

	private:
		CStack& operator = (const CStack&) = delete; CStack& operator = (CStack&&) = delete;
	};

}}}}}

typedef ex_ui::draw::open_gl::procs::matrix::CStack TStackProcs; TStackProcs& __get_stack_procs (void);

#endif/*_GL_PROCS_MTX_STACK_H_INCLUDED*/