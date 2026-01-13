#ifndef _GL_STATUS_H_INCLUDED
#define _GL_STATUS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Sep-2025 at 18:46:36.062, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL program status wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_prog_id.h"
#include "gl_prog_log.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {

	class CStatus : private no_copy  {
	public:
		using CLog = program::CLog;
		CStatus (const uint32_t _prog_id = 0); ~CStatus (void);

		TError&  Error (void) const;
		static
		bool     Get (const uint32_t _param_id, const uint32_t _prog_id, CError&);
		bool     Get (const uint32_t _param_id) const;

		static  uint32_t GetActiveProg (CError&); // returns the prog_id of currently active program, otherwise 0 (zero) is returned;
		static
		bool  Is_linked (const uint32_t _u_prog_id, CError&);
		bool  Is_linked (void) const;       // if result is 'false' the details can be received by calling the log info function;
		static
		bool  Is_valid  (const uint32_t _u_prog_id, CError&);
		bool  Is_valid  (void) const;
		static
		bool  Is_used (const uint32_t _prog_id, CError&);
		bool  Is_used (void) const;

		const
		CLog& Log (void) const;
		CLog& Log (void) ;

		const
		CProgId& ProgId (void) const;
		CProgId& ProgId (void) ;

		CStatus& operator <<(const CProgId&);

	private:
		mutable
		CError   m_error;
		CProgId  m_prog_id;
		CLog     m_log;
	};

}}}}

#endif/*_GL_STATUS_H_INCLUDED*/