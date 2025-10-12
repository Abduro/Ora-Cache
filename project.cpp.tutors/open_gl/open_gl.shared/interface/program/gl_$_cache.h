#ifndef _GL_$_CACHE_H_INCLUDED
#define _GL_$_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:49:23.402, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface declaration file;
*/
#include "gl_defs.h"
#include "gl_shader.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace program {

	typedef ::std::set<uint32_t> TShaderIds; // it possibly must be used in order to avoid calling glGetAttachedShaders();
	// this class is intended to store of shader(s) being used by a program linking;
	class CCache : private no_copy {
	public:
		CCache (const uint32_t _prog_id = 0); ~CCache (void);
#if (0)
		static
		err_code Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Attach (const uint32_t _u_shader_id);
		static
		err_code Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Detach (const uint32_t _u_shader_id); // *important:* a shader should be detached from an OpenGL program before being deleted;
		/*Google AI Overview:
		...a shader should be detached from an OpenGL program before being deleted,
		as the shader object is not truly deleted until it's detached from all programs it's attached to...
		*/
		static
		err_code Delete_all (const uint32_t _u_prog_id, CError&); // this method is called after the program links these shaders;
		err_code Delete_all (void);

		static
		err_code Detach_all (const uint32_t _u_prog_id, CError&); // before deleting shader(s) they (shaders) must be detached;
		err_code Detach_all (void);
#endif
		const
		shader::CFragment& Fragment (void) const;
		shader::CFragment& Fragment (void) ;

		TError&  Error (void) const;

		uint32_t ProgId (void) const;      // returns a 'prog_id' value;
		err_code ProgId (const uint32_t);  // 'prog_id' value is just checked for 0 value and that's all;
		const
		shader::CVertex& Vertex (void) const;
		shader::CVertex& Vertex (void) ;

		CCache& operator <<(const uint32_t _prog_id);
#if (0)
		CCache& operator +=(const uint32_t _u_shader_id); // it is assumed the program identifier is already set to this linker;
		CCache& operator -=(const uint32_t _u_shader_id); // detaches the shader from linker (i.e. the program) by '_u_shader_id';
#endif
	private:
		mutable
		CError   m_error;
		uint32_t m_prog_id;
		shader::CFragment m_$_frag;
		shader::CVertex   m_$_vert;
	};

}}}}


#endif/*_GL_$_CACHE_H_INCLUDED*/