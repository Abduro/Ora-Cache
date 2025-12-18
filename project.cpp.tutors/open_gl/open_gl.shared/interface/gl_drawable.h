#ifndef _GL_DRAWABLE_H_INCLUDED
#define _GL_DRAWABLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:49:12.456, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {

	class CBkgnd : private no_copy {
	public:
		CBkgnd (void); ~CBkgnd (void);

		err_code Draw  (void);
		TError&  Error (void) const;

	private:
		CError m_error;
	};

}}}

#endif/*_GL_DRAWABLE_H_INCLUDED*/