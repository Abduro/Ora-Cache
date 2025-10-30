#ifndef _GL_$_CACHE_H_INCLUDED
#define _GL_$_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Oct-2025 at 16:49:23.402, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL shader collection or cache (used by program) interface declaration file;
*/
#include "gl_defs.h"
#include "gl_shader.h"
#include "program\gl_prog_id.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace program {

	typedef ::std::set<uint32_t> TShaderIds; // it possibly must be used in order to avoid calling glGetAttachedShaders();
	// this class is intended to store of shaders being used by a program linking;
	class CCache : private no_copy {
	public:
		CCache (const uint32_t _prog_id = 0); ~CCache (void);

		err_code Attach (void);   // attaches all shaders to the program; it is assumed the program identifier is already set;
		static
		err_code Attach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Attach (const uint32_t _u_shader_id);

		err_code Compile(void);  // compiles all shaders; it is assumed the shader sources are already set;
		err_code Create (void);  // creates all shaders; it is assumed the program is already created and its identifier is set to each shader;
		/*Google AI Overview:
		...a shader should be detached from an OpenGL program before being deleted,
		as the shader object is not truly deleted until it's detached from all programs it's attached to...
		*/
		err_code Delete (void);   // deletes all shaders; shaders must be detached first;
#if (0) // it is not necessary because the CShader has its own Delete() method;
		static
		err_code Delete (const uint32_t _u_shader_id, CError&); // this method is called after the program links these shaders;
		err_code Delete (const uint32_t _u_shader_id);          // before deleting shader(s) they (shaders) must be detached;
#endif
		err_code Detach (void);  // detaches all shaders from the program;
		static
		err_code Detach (const uint32_t _u_shader_id, const uint32_t _u_prog_id, CError&);
		err_code Detach (const uint32_t _u_shader_id); // *important:* a shader should be detached from an OpenGL program before being deleted;
		const
		shader::CFragment& Fragment (void) const;
		shader::CFragment& Fragment (void) ;

		TError&  Error (void) const;

		err_code Load  (void);             // load source code for each shader;
		const
		CProgId& ProgId (void) const;
		CProgId& ProgId (void) ;

		const
		shader::CVertex& Vertex (void) const;
		shader::CVertex& Vertex (void) ;

		CCache& operator <<(const CProgId&);
#if (0)
		CCache& operator +=(const uint32_t _u_shader_id); // it is assumed the program identifier is already set to this linker;
		CCache& operator -=(const uint32_t _u_shader_id); // detaches the shader from linker (i.e. the program) by '_u_shader_id';
#endif
	private:
		mutable
		CError   m_error;
		CProgId  m_prog_id;
		shader::CFragment m_$_frag;
		shader::CVertex   m_$_vert;
	};

}}}}

#endif/*_GL_$_CACHE_H_INCLUDED*/