#ifndef _GL_PROGRAM_H_INCLUDED
#define _GL_PROGRAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:45:33.548, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_error.h"

namespace ex_ui { namespace draw { namespace open_gl {

	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

namespace program {

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		 TErr_ex& Error (void) const;

	private:
		 CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
	protected:
		 CError_ex m_error;
	};

}}}

}

#endif/*_GL_PROGRAM_H_INCLUDED*/