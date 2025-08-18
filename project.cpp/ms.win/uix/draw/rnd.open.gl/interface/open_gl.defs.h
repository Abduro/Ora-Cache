#ifndef _OPEN_GL_DEFS_H_INCLUDED
#define _OPEN_GL_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Aug-2025 at 23:56:27.465, (UTC+4) Batumi, Friday;
	This is Ebo Pack OpenGL based draw renderer generic definitions' declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "shared.types.h"
#include "sys.error.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

namespace ex_ui { namespace draw { namespace open_gl {

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	class CVersion {
	public:
		 CVersion (void); CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete;
		~CVersion (void);

		TError& Error (void) const;

	private:
		 CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;
		 CError m_error;
	};

}}}

#endif/*_OPEN_GL_DEFS_H_INCLUDED*/