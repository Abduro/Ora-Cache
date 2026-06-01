#ifndef _GL_PROCS_FRUSTUM_H_INCLUDED
#define _GL_PROCS_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jun-2026 at 23:42:01.952, UTC+4, Batumi, Monday;
	This is OpenGL v.1.1 frustum related function set wrapper interface declaration file;
*/
#include "gl_procs_basic.h"

namespace open_gl { namespace procs { namespace projection {
	using namespace open_gl::procs::ver_1_1;

	class CFrustum : public CBasic { typedef CBasic TBase;
	public:
		CFrustum (void); CFrustum (const CFrustum&) = delete; CFrustum (CFrustum&&) = delete; ~CFrustum (void) = default;
	private:
		CFrustum& operator = (const CFrustum&) = delete; CFrustum& operator = (CFrustum&&) = delete;
	};

}}}

#endif/*_GL_PROCS_FRUSTUM_H_INCLUDED*/