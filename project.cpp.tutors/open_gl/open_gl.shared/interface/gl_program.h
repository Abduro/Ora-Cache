#ifndef _GL_PROGRAM_H_INCLUDED
#define _GL_PROGRAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:45:33.548, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"
#include "gl_logs.h"
#include "program\gl_prog_id.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {}
	class CProgram  {
	public:
		 CProgram (void) ;  CProgram (const CProgram&) = delete; CProgram (CProgram&&) = delete;
		~CProgram (void) ;

		 static procs::CProg& Cache (void) ;
		 static CString  Class (void);       // returns this class name for debug purposes;

		 err_code Create (void);
		 err_code Delete (void);

		 TError& Error (void) const;

		 const
		 program::CProgId& Id (void) const;
		 program::CProgId& Id (void) ;

		 /* the validation of a program is determined by the target that is required to be valid:
			(a) program identifier (aka symbolic name); glGetIntegerv();
			(b) program status; glGetProgramiv();
		 */
		 static
		 bool Is_valid (const uint32_t _n_prog_id, CError&); // there is not way to check program identifier as it can be made for shader;
		 bool Is_valid (void) const; // checks the identifier that stored in this class object;

		 err_code Validate (void);   // mimics the validation operation that OpenGL implementations must perform when rendering commands are issued ;

	private:
		 CProgram& operator = (const CProgram&) = delete; CProgram& operator = (CProgram&&) = delete;
		 program::CProgId m_prog_id;
		 mutable
		 CError  m_error;
	};
}}}

#endif/*_GL_PROGRAM_H_INCLUDED*/