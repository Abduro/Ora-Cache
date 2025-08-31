#ifndef _GL_ERROR_H_INCLUDED
#define _GL_ERROR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 11:47:47.855, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL error handler adapter interface declaration file;
*/
#include "shared.defs.h"
#include "sys.err.trim.h"

namespace ex_ui { namespace draw { namespace open_gl {

	using namespace shared::defs;

	// https://learn.microsoft.com/en-us/windows/win32/opengl/error-handling ;

	class CErr_src {
	public:
		 CErr_src (void) = default; CErr_src (const CErr_src&) = delete; CErr_src (CErr_src&&) = delete;
		~CErr_src (void) = default;

	static CString Src_to_str (const uint32_t _u_cat) ;

	private:
		 CErr_src& operator = (const CErr_src&) = delete; CErr_src& operator = (CErr_src&&) = delete;
	};


	// https://docs.gl/gl4/glDebugMessageCallback ;
	// https://www.khronos.org/opengl/wiki/Example/OpenGL_Error_Testing_with_Message_Callbacks ;
	// https://stackoverflow.com/questions/60486285/gldebugmessagecallback-doesnt-get-called-despite-of-error ; << example of usage;


	class CError_ex : public shared::sys_core::CError { typedef shared::sys_core::CError TBase;
	public:
		 CError_ex (void);
		~CError_ex (void);

	public:
		const
		CError& operator ()(void) const;
		CError& operator ()(void) ;
	};
}}}

#endif/*_GL_ERROR_H_INCLUDED*/