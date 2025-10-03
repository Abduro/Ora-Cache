#ifndef _GL_$_CACHE_H_INCLUDED
#define _GL_$_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:49:23.402, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace program {

	typedef ::std::vector<uint32_t> TShaderIds;
	// this class is intended for store of shader(s) being used by a program linking;
	class CCache : private no_copy {
	public:
		CCache (const uint32_t _prog_id = 0); ~CCache (void);

		static
		err_code Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Attach (const uint32_t _u_shader_id);
		static
		err_code Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Detach (const uint32_t _u_shader_id);
		static
		err_code Detach_all (const uint32_t _u_prog_id, CError&);
		err_code Detach_all (void);

		TError& Error (void) const;

		uint32_t ProgId (void) const;      // returns a 'prog_id' value;
		err_code ProgId (const uint32_t);  // 'prog_id' value is just checked for 0 value and that's all;

		CCache& operator <<(const uint32_t _prog_id);

		CCache& operator +=(const uint32_t _u_shader_id); // it is assumed the program identifier is already set to this linker;
		CCache& operator -=(const uint32_t _u_shader_id); // detaches the shader from linker (i.e. the program) by '_u_shader_id';

	private:
		mutable
		CError   m_error;
		uint32_t m_prog_id;
	};

}}}}


#endif/*_GL_$_CACHE_H_INCLUDED*/