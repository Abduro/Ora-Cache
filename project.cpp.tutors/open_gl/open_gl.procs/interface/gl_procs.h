#ifndef _GL_PROCS_H_INCLUDED
#define _GL_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:09:31.015, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface declaration file; 
*/
#include "gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl {
namespace procs {
	/* https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml ;
		the excerpt from above document:
		Shader compiler support is optional, and thus must be queried before use by calling glGet with argument GL_SHADER_COMPILER.
	*/
	class CCompiler : public CBase {
	typedef void (__stdcall *pfn_Compile)(uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml ;
	typedef void (__stdcall *pfn_Release)(void); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glReleaseShaderCompiler.xhtml ;
	public:
		CCompiler (void); ~CCompiler (void) = default;

		err_code Compile (uint32_t _shader_id); // compiles the source code strings that have been stored in the shader object specified by '_shader_id';
		bool Is_supported (void) const; // returns 'true' if the compiler is supported; class CParam is used for getting support value;
		err_code Release (void); // provides a hint to the implementation that it may free internal resources associated with its shader compiler;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CCompiler& operator = (const CCompiler&) = delete; CCompiler& operator = (CCompiler&&) = delete;
	};

	// it is a loader of functions that are related to the program layout process; this class is intended for functional modularity only;
	// ToDo: it very looks like the linker must do the only one operation: to link and nothing more;
	class CLinker : public CBase {
	typedef void     (__stdcall *pfn_Link)     (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml ;
	public:
		CLinker (void); ~CLinker (void) = default;

		err_code Link    (const uint32_t _prog_id);  // links the program object specified by _prog_id ;

	private:
		CLinker& operator = (const CLinker&) = delete; CLinker& operator = (CLinker&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGet.xml ; this document contains all parameter identifiers that is recognized by glGet*();
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
	class CParam : public CBase {
	typedef void   (__stdcall *pfn_GetBool)  (uint32_t _u_param_id, uint32_t* _p_result);
	typedef void   (__stdcall *pfn_GetFloat) (uint32_t _u_param_id, float* _p_result);
	typedef void   (__stdcall *pfn_GetInt)   (uint32_t _u_param_id, int32_t* _p_result);
	public:
		CParam (void); ~CParam (void) = default;

		err_code Get_all (void);

		bool    GetBool  (const uint32_t _u_param_id); // returns parameter value as boolean ;
		float   GetFloat (const uint32_t _u_param_id); // returns parameter value as float number;
		int32_t GetInt   (const uint32_t _u_param_id); // returns parameter value as integer ;

	private:
		CParam& operator = (const CParam&) = delete; CParam& operator = (CParam&&) = delete;
	};
}}}}

typedef ex_ui::draw::open_gl::procs::CParam TParam; TParam& __get_param_procs (void);

#endif/*_GL_PROCS_H_INCLUDED*/