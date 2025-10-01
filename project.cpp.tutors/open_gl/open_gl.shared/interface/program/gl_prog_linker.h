#ifndef _GL_PROG_LINKER_H_INCLUDED
#define _GL_PROG_LINKER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 09:10:09.244, UTC+4, Batumi, Wednesday;
	This Ebo Pack OpenGL program linker wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace program {

	class CLinker : private no_copy {
	public:
		// it is assumed the '_u_prog_id' is provided, otherwise ProgId(...) must be called;
		CLinker (const uint32_t _u_prog_id = 0); ~CLinker (void);

		static
		err_code Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Attach (const uint32_t _u_shader_id);
		static
		err_code Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Detach (const uint32_t _u_shader_id);
		static
		err_code Detach_all (const uint32_t _u_prog_id, CError&);
		err_code Detach_all (void);

		static
		err_code Link (const uint32_t _u_prog_id, CError&);
		err_code Link (void);               // assumes the program identifier is set;

		static procs::CLinker& Cache (void) ;
		static CString  Class (void);       // returns this class name for debug purposes;

		TError&  Error  (void) const;
		uint32_t ProgId (void) const;       // returns currently set program identifier;
		err_code ProgId (const uint32_t);   // returns error code if the input prog_id is not valid, s_false: no change, otherwise: s_ok;

		CLinker& operator <<(const uint32_t _u_prog_id);
		CLinker& operator +=(const uint32_t _u_shader_id); // it is assumed the program identifier is already set to this linker;
		CLinker& operator -=(const uint32_t _u_shader_id); // detaches the shader from linker (i.e. the program) by '_u_shader_id';

	private:
		mutable
		CError    m_error;    // using CError_Ex looks like not necessary due to in the most cases this class is required;
		uint32_t  m_prog_id;
	};

}}}}
#endif/*_GL_PROG_LINKER_H_INCLUDED*/