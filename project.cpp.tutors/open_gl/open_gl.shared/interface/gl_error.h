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
#pragma region __refs_d
	// https://docs.gl/gl4/glDebugMessageCallback ;
	// https://www.khronos.org/opengl/wiki/Example/OpenGL_Error_Testing_with_Message_Callbacks ;
	// https://stackoverflow.com/questions/60486285/gldebugmessagecallback-doesnt-get-called-despite-of-error ; << example of usage;
#pragma endregion
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgeterror ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml ;
	// https://www.khronos.org/opengl/wiki/OpenGL_Error ; << this is descriptive information of the error codes and how to use the error;

	class CError_ex : public shared::sys_core::CError { typedef shared::sys_core::CError TBase;
	public:
		 CError_ex (void);
		~CError_ex (void);

		uint32_t Get_code (void) const; // *important*: this must be used for getting the last error code that is returned by OpenGL;

		// in the most cases the DirectX error code is used for compliance with operating system error codes: winerror.h ln.55898;
		// input arg is for keeping original error description i.e. that is defined by OpenGL, but the error may have WinAPI system error desc too;

		err_code Get_last (const bool _b_origin = true) const;  // calls the glGetError() function for getting the last error code;

		// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluErrorString.xml ;
		// https://learn.microsoft.com/en-us/windows/win32/opengl/gluerrorstring ; << this page the same content as above one, but is much better formatted;

	public:
		const
		CError& operator ()(void) const;
		CError& operator ()(void) ;

	private:
		mutable
		uint32_t m_err_code; // this is native error code that is provided by OpenGL; two-byte number (i.e. unsigned short) is enough, but for some special cases 4-bytes can be better;
	};
}}}

#endif/*_GL_ERROR_H_INCLUDED*/