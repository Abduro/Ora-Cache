#ifndef _GL_PROCS_H_INCLUDED
#define _GL_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:09:31.015, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface declaration file; 
*/
#include "procs\gl_procs_base.h"

namespace ex_ui { namespace draw { namespace open_gl {
	
namespace procs {
	using namespace ex_ui::draw::open_gl;

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
	typedef void     (__stdcall *pfn_Attach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
	typedef void     (__stdcall *pfn_Detach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml ;
	typedef void     (__stdcall *pfn_Attached) (uint32_t _prog_id, uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttachedShaders.xhtml ;
	typedef void     (__stdcall *pfn_Link)     (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml ;
	public:
		CLinker (void); ~CLinker (void) = default;

		err_code Attach  (const uint32_t _prog_id, const uint32_t _shader_id); // attaches the shader object specified by '_shader_id' to the program object specified by '_prog_id' ;
		err_code Detach  (const uint32_t _prog_id, const uint32_t _shader_id); // detaches a shader object from a program object to which it is attached ;
		err_code Attached(const uint32_t _prog_id, const uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // returns the identifiers of the shader objects attached to a program object;
		err_code Link    (const uint32_t _prog_id);  // links the program object specified by _prog_id ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CLinker& operator = (const CLinker&) = delete; CLinker& operator = (CLinker&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGet.xml ; this document contains all parameter identifiers that is recognized by glGet*();
	class CParam : public CBase {
	typedef void   (__stdcall *pfn_GetBool) (uint32_t _u_param_id, uint32_t* _p_result);
	typedef void   (__stdcall *pfn_GetFloat) (uint32_t _u_param_id, float* _p_result);
	typedef void   (__stdcall *pfn_GetFInt) (uint32_t _u_param_id, int32_t* _p_result);
	public:
		CParam (void); ~CParam (void) = default;

		err_code Get_all (void) ;

		bool    GetBool (uint32_t _u_param_id);  // returns parameter value as boolean ;
		float   GetFloat (uint32_t _u_param_id); // returns parameter value as float number;
		int32_t GetInt (uint32_t _u_param_id);   // returns parameter value as integer ;

	private:
		CParam& operator = (const CParam&) = delete; CParam& operator = (CParam&&) = delete;
	};

	class CShader : public CBase {
	typedef uint32_t (__stdcall *pfn_Create) (uint32_t _u_type);    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
	typedef void     (__stdcall *pfn_Delete) (uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)(uint32_t _shader_id, int32_t _n_max_length, int32_t* _p_log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml ;
	typedef uint32_t (__stdcall *pfn_IsValid)(uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glIsShader.xml ;
	typedef void     (__stdcall *pfn_Params) (uint32_t _shader_id, uint32_t _param_type, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml ;
	typedef void     (__stdcall *pfn_Source) (uint32_t _shader_id, int32_t _n_count, const char** const _p_string, const int32_t* _p_length); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml ;
	public:
		CShader (void); ~CShader (void) = default;

		uint32_t Create  (uint32_t _u_type);    // creates an empty shader object and returns a non-zero value by which it can be referenced ;
		err_code Delete  (uint32_t _shader_id); // frees the memory and invalidates the name associated with the shader object specified by _shader_id ;
		err_code InfoLog (uint32_t _shader_id, int32_t _n_max_length, int32_t* _p_log_len, char* _p_log); // returns the information log for the specified shader object ;
		bool   Is_valid  (uint32_t _shader_id); //  determines if _shader_id corresponds to a shader object, i.e. returns 'true' if the shader object with such identifier exists;
		err_code Params  (uint32_t _shader_id, uint32_t _param_type, int32_t* _p_params); // returns a parameter from a shader object ; the error object is updated in case of this function failure;
		err_code Source  (uint32_t _shader_id, int32_t _n_count, const char** const _p_string, const int32_t* _p_length); // sets the source code in shader to the source code in the array of strings specified by _p_string ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CShader& operator = (const CShader&) = delete; CShader& operator = (CShader&&) = delete;
	};
}}}}

#endif/*_GL_PROCS_H_INCLUDED*/