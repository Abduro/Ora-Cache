#ifndef _GL_PROCS_MATH_H_INCLUDED
#define _GL_PROCS_MATH_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jan-2026 at 21:32:27.495, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL math functions' loader interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace math {
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetActiveUniform.xhtml >> for getting info of active uniform variable;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml >> for getting location of a uniform variable;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml >> for setting the value of a uniform variable or a uniform variable array;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniform.xhtml >> for getting a value of a uniform variable;
	
	class CUniform : public CBase {
	public:
		CUniform (void); ~CUniform (void) = default;
	private:
		CUniform& operator = (const CUniform&) = delete; CUniform& operator = (CUniform&&) = delete;
	};

}}}}}
#endif/*_GL_PROCS_MATH_H_INCLUDED*/