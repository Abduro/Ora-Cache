#ifndef _GL_PROGRAM_H_INCLUDED
#define _GL_PROGRAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Sep-2025 at 17:45:33.548, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' shader program base interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"
#include "gl_logs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {

	class CLinker : private no_copy {
	public:
		// it is assumed the '_u_prog_id' is provided, otherwise ProgId(...) must be called;
		CLinker (const uint32_t _u_prog_id = 0); ~CLinker (void);

		static
		err_code Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Attach (const uint32_t _u_shader_id);

		TError&  Error  (void) const;
		uint32_t ProgId (void) const;       // returns currently set program identifier;
		err_code ProgId (const uint32_t);   // returns error code if the input prog_id is not valid, s_false: no change, otherwise: s_ok;

		CLinker& operator <<(const uint32_t _u_prog_id);
		CLinker& operator +=(const uint32_t _u_shader_id); // it is assumed the program identifier is already set to this linker;

	private:
		mutable
		CError   m_error;    // using CError_Ex looks like not necessary due to in the most cases this class is required;
		uint32_t m_prog_id;
	};
}
	class CProgram  {
	public:
		 CProgram (void) ;  CProgram (const CProgram&) = delete; CProgram (CProgram&&) = delete;
		~CProgram (void) ;

		 static procs::CProg& Cache (void) ;
		 static CString  Class (void);       // returns this class name for debug purposes;

		 err_code Create (void);
		 err_code Delete (void);

		 TError& Error (void) const;

		 uint32_t Id (void) const;
		 static
		 bool Is_valid (const uint32_t _n_prog_id, CError&); // there is not way to check program identifier as it can be made for shader;
		 bool Is_valid (void) const; // checks the identifier that stored in this class object;

	private:
		 CProgram& operator = (const CProgram&) = delete; CProgram& operator = (CProgram&&) = delete;
		 uint32_t  m_id;
		 mutable
		 CError m_error;
	};
}}}

#endif/*_GL_PROGRAM_H_INCLUDED*/