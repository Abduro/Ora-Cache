#ifndef _GL_PROGRAM_H_INCLUDED
#define _GL_PROGRAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:45:33.548, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_buffer.h"
#include "gl_logs.h"
#include "gl_procs.h"
#include "procs\gl_procs_prog.h"
#include "program\gl_$_cache.h"
#include "program\gl_prog_id.h"
#include "program\gl_prog_status.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {
}
	class CProgram  {
	using CProgId = program::CProgId;
	using CStatus = program::CStatus;
	public:
		 CProgram (void) ;  CProgram (const CProgram&) = delete; CProgram (CProgram&&) = delete;
		~CProgram (void) ;

		 const
		 CBuffer_4_vert& Buffer (void) const;
		 CBuffer_4_vert& Buffer (void) ;

		 static procs::CProg& Procs (void) ;
		 static CString  Class (void);       // returns this class name for debug purposes;

		 err_code Create (void);
		 err_code Delete (void);

		 TError&  Error (void) const;

		 const
		 CProgId& Id (void) const;
		 CProgId& Id (void) ;

		 /* the validation of a program is determined by the target that is required to be valid:
			(a) program identifier (aka symbolic name); glIsProgram() is used by CProgId::Is_valid();
			(b) program status; glGetProgramiv() is used by CStatus::Get();
		 */
		 static
		 bool Is_valid (const uint32_t _n_prog_id, CError&); // there is not way to check program identifier as it can be made for shader;
		 bool Is_valid (void) const; // checks the identifier that stored in this class object;

		 err_code Link (void) ;      // it is assumed all attached shaders is already compiled; this method calls CLinker::Link(this->Prog_id());

		 const
		 program::CCache& Shaders (void) const;
		 program::CCache& Shaders (void) ;
		 const
		 program::CStatus& Status (void) const;
		 program::CStatus& Status (void) ;

		 err_code Use (void);        // sets this program to be current in draw pipeline;
		 err_code Validate (void);   // mimics the validation operation that OpenGL implementations must perform when rendering commands are issued ;

		 CProgram& operator <<(const CProgId&);

	private:
		 CProgram& operator = (const CProgram&) = delete; CProgram& operator = (CProgram&&) = delete;
		 program::CProgId m_prog_id;
		 mutable
		 CError   m_error;
		 CBuffer_4_vert   m_buffer;
		 program::CCache  m_shaders;
		 program::CStatus m_status;
	};
}}}

#endif/*_GL_PROGRAM_H_INCLUDED*/