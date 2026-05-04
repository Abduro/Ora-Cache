#ifndef _GL_PROCS_BASIC_H_INCLUDED
#define _GL_PROCS_BASIC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 20:04:02.817, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 common basic interface declaration file;
*/
#include "shared.defs.h"
#include <gl/gl.h>       // the headers' include order is important: windows.h must go first;
#include "gl_error.h"

#pragma comment(lib, "opengl32.lib")
/*
	https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-reference ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/state-variables ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/gl-functions ;
	https://learn.microsoft.com/en-us/windows/win32/opengl/glu-functions ;
*/
#include "shared.preproc.h"
#include "shared.dbg.h"

namespace open_gl { namespace procs { namespace ver_1_1 {

	using namespace shared::defs;
	using namespace ATL;

	using ::ex_ui::draw::open_gl::CError_ex;
	using CErr_ex = CError_ex;
	using TErr_ex = const CErr_ex;

	class CBasic {
	public:
		TError&  Error (void) const;

	protected:
		CBasic (void); CBasic (const CBasic&) = delete; CBasic (CBasic&&) = delete; ~CBasic (void) = default;
		mutable
		CError  m_error;
	private:
		CBasic& operator = (const CBasic&) = delete; CBasic& operator = (CBasic&&) = delete;
	};

}}}

#endif/*_GL_PROCS_BASIC_H_INCLUDED*/