#ifndef _GL_PROCS_ORTHO_H_INCLUDED
#define _GL_PROCS_ORTHO_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jun-2026 at 23:38:19.118, UTC+4, Batumi, Sunday;
	This is OpenGL v.1.1 orthographic matrix related function set wrapper interface declaration file;
*/
#include "gl_procs_project.h"

namespace open_gl { namespace procs { namespace projection { namespace ver_1_1 {

	// https://learn.microsoft.com/en-us/windows/win32/opengl/glortho ;
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml ; supported versions of OpenGL 1.1 ... 2.1;

	using namespace ::open_gl::procs::projection;

	/* the query to Google AI:
	   what coordinates should be sent to glOrtho? in window coordinate system or in normalized device coordinates?

	   You should use window coordinates (or "world coordinates" representing your specific game/application dimensions).
	   Do *not* use Normalized Device Coordinates (NDC) directly in glOrtho; (details: !notes\__read_me_ortho.txt)

	   https://stackoverflow.com/questions/59262874/how-can-i-use-screen-space-coordinates-directly-with-opengl ;
	*/
	class COrtho : public CBasic { typedef CBasic TBase;
	public:
		COrtho (void); COrtho (const COrtho&) = delete; COrtho (COrtho&&) = delete; ~COrtho (void) = default;
		/* set to origin (0|0) at the top-left window corner: glOrtho (0.0, width, *height*, 0.0, -1.0f, 1.0f);
		   set a camera to center (0|0): glOrtho (-width/2.0, width/2.0, -height/2.0, height/2.0, -1.0f, 1.0f);
		*/
		err_code Set (const t_rect& _clip, const f_planes&); // clip rectangle is in window client area coordinate system;

	private:
		COrtho& operator = (const COrtho&) = delete; COrtho& operator = (COrtho&&) = delete;
	};

}}}}

#endif/*_GL_PROCS_ORTHO_H_INCLUDED*/