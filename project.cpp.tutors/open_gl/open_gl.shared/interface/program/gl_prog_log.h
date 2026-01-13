#ifndef _GL_PROG_LOG_H_INCLUDED
#define _GL_PROG_LOG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jan-2026 at 23:39:03.456, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL program log wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace program {

	using namespace ex_ui::draw::open_gl;
	// unfortunately, the base class of log info cannot be used due to reference restriction, i.e. the project architecture;
	class CLog {
	public:
		CLog (void); ~CLog (void) = default; CLog (const CLog&); CLog (CLog&&) = delete;
		const
		CString&  Buffer (void) const;

		TError& Error (void) const;
		_pc_sz    Get (void) const;                    // returns log info string stored in the buffer ;
		err_code  Set (const uint32_t _u_prog_id) ;    // retrieves the log info from current state of the program by '_u_prog_id' to string buffer;

		CLog& operator = (const CLog&); CLog& operator = (CLog&&) = delete;
	private:
		mutable
		CError   m_error ;
		CString  m_buffer;
	};
}}}}

#endif/*_GL_PROG_LOG_H_INCLUDED*/