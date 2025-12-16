#ifndef _GL_UNIFORM_H_INCLUDED
#define _GL_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Dec-2025 at 11:28:10.278, UTC+4, Batumi, Tuesday;
	This Ebo Pack OpenGL shader variable uniform data type wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace vars {

	class CUniform : no_copy {
	public:
		CUniform (void); ~CUniform (void);

		TError& Error (void) const;

	private:
		CError  m_error;
	};

	class CUniform_enum : no_copy {
	public:
		CUniform_enum (void); ~CUniform_enum (void);

		uint32_t Count (void) const;  // gets count of uniforms in the active/bound program object;
		TError&  Error (void) const;
	
	private:
		mutable
		CError  m_error;
	};

}
}}}

#endif/*_GL_UNIFORM_H_INCLUDED*/