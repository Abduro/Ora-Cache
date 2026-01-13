#ifndef _GL_$_LOG_H_INCLUDED
#define _GL_$_LOG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jan-2026 at 01:40:08.984, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL shader log wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	using namespace ex_ui::draw::open_gl;

	class CLog {
	public:
		CLog (void); ~CLog (void) = default; CLog (const CLog&) = delete; CLog (CLog&&) = delete;

		TError& Error (void) const;
		_pc_sz    Get (void) const;                    // returns log info string stored in the buffer ;
		err_code  Set (const uint32_t _u_prog_id) ;    // retrieves the log info from current state of the program by '_u_prog_id' to string buffer;

	private:
		CLog& operator = (const CLog&) = delete; CLog& operator = (CLog&&) = delete;
		mutable
		CError   m_error ;
		CString  m_buffer;
	};
}}}}

#endif/*_GL_$_LOG_H_INCLUDED*/