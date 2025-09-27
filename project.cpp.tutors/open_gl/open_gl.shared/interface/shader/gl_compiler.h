#ifndef _GL_COMPILER_H_INCLUDED
#define _GL_COMPILER_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 11:56:49.011, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader compiler wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_logs.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace shader {

	class CCompiler {
	public:
		CCompiler (const uint32_t _u_shader_id = 0); CCompiler (const CCompiler&) = delete; CCompiler (CCompiler&&) = delete; ~CCompiler (void);

		err_code Compile (void);              // tries to compile source code of the shader;

		TErr_ex& Error (void) const;

		bool  Is_compiled  (void) const;      // checks compilation status of the shader; if it is false, either no compilation was made or getting log info is required for details;
		bool  Is_supported (void) const;
		const
		CLog&    Log (void) const;
		CLog&    Log (void) ;

		uint32_t ShaderId  (void) const;
		err_code ShaderId  (const uint32_t);  // returns an error code in case if input shader identifier is not valid;

		CCompiler& operator <<(const uint32_t _u_shader_id);

	private:
		CCompiler& operator = (const CCompiler&) = delete; CCompiler& operator = (CCompiler&&) = delete;
		mutable
		CError_ex  m_error;
		uint32_t   m_shader_id;
		CLog  m_log;
	};

}}}}

#endif/*_GL_COMPILER_H_INCLUDED*/