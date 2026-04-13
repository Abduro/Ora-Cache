#ifndef _GL_PROCS_EXT_H_INCLUDED
#define _GL_PROCS_EXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2026 at 14:28:53.565, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL extension wrapper interface declaration file;
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

	class CExtension {
	public:
		CExtension (void); CExtension (const CExtension&) = delete; CExtension (CExtension&&) = delete; ~CExtension (void) = default;
		TError& Error (void) const;

		err_code Load (void);
		err_code Unload (void);

	private:
		CExtension& operator = (const CExtension&) = delete; CExtension& operator = (CExtension&&) = delete;
		CError m_error;
	};

}}}}

typedef ex_ui::draw::open_gl::procs::CExtension TProcsExt; TProcsExt&  Get_ProcExt (void);

#endif/*_GL_PROCS_EXT_H_INCLUDED*/