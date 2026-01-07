#ifndef _GL_LOGS_H_INCLUDED
#define _GL_LOGS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2025 at 16:54:50.185, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL log functions' wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {

	class CLog_Base {
	protected:
		CLog_Base (void); ~CLog_Base (void);
	public:
		TError& Error (void) const;   // the error class being returned needs to be as the reference to the base error class, otherwise it's possible do not detect the error on the caller side;

		_pc_sz   Get (void) const;    // returns log info string stored in the buffer ;

	private:
		CLog_Base (const CLog_Base&) = delete; CLog_Base (CLog_Base&&) = delete;
		CLog_Base& operator = (const CLog_Base&) = delete; CLog_Base& operator = (CLog_Base&&) = delete;
	protected:
		mutable
		CError   m_error ;
		CString  m_buffer;  // stores the log info;
	};

namespace program {

	class CLog : public CLog_Base { typedef CLog_Base TBase;
	public: CLog (void); ~CLog (void);

		err_code Set (const uint32_t _u_prog_id) ;    // retrieves the log info from current state of the program by _u_prog_id to string buffer;
	};
}
namespace shader {

	class CLog : public CLog_Base { typedef CLog_Base TBase;
	public: CLog (void); ~CLog (void);

		err_code Set (const uint32_t _u_shader_id) ;  // retrieves the log info from current state of the shader by _u_shader_id to string buffer;
	};
}
}}}

#endif/*_GL_LOGS_H_INCLUDED*/