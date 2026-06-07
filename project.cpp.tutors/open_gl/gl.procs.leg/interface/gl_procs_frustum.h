#ifndef _GL_PROCS_FRUSTUM_H_INCLUDED
#define _GL_PROCS_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jun-2026 at 23:42:01.952, UTC+4, Batumi, Monday;
	This is OpenGL v.1.1 frustum related function set wrapper interface declaration file;
*/
#include "gl_procs_project.h"

namespace open_gl { namespace procs { namespace projection {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glfrustum ;
	class CFrustum : public CBasic { typedef CBasic TBase;
	public:
		CFrustum (void); CFrustum (const CFrustum&) = delete; CFrustum (CFrustum&&) = delete; ~CFrustum (void) = default;

		err_code Set (const f_rect& _clip, const f_planes&); // the sides values of d_rect must be in acceptable range [-1.0 ... 1.0];
		err_code Set (const t_rect& _clip, const f_planes&); // clip rectangle requires a conversion to normalized device space [-1.0 ... 1.0];

	private:
		CFrustum& operator = (const CFrustum&) = delete; CFrustum& operator = (CFrustum&&) = delete;
	};

}}}

#endif/*_GL_PROCS_FRUSTUM_H_INCLUDED*/