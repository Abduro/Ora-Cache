#ifndef _GL_PROCS_PROG_H_INCLUDED
#define _GL_PROCS_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Oct-2025 at 01:17:24.959, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL program functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

namespace program {
	/*	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
		the excerpt from the above article:
		...queries the previously *linked* program object specified by program for the attribute variable specified by name
		   and returns the index of the generic vertex attribute that is bound to that attribute variable ...
	*/
	class CAttr : public CBase {
	typedef int32_t  (__stdcall *pfn_GetIndex)(uint32_t _prog_id, const char* _p_att_name);
	typedef void     (__stdcall *pfn_SetIndex)(uint32_t _prog_id, uint32_t _u_ndx, const char* _p_att_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindAttribLocation.xhtml ;
	public:
		CAttr (void); ~CAttr (void) = default;

		int32_t  GetIndex (const uint32_t _prog_id, _pc_sz _p_att_name); // returns the location (i.e. the index) of an attribute variable ; *after* the link;
		err_code SetIndex (const uint32_t _prog_id, _pc_sz _p_att_name, const uint32_t _u_ndx); // sets the index *before* the link, otherwise no effect;

	private:
		CAttr& operator = (const CAttr&) = delete; CAttr& operator = (CAttr&&) = delete;
	};

	class CShaders : public CBase {
	typedef void     (__stdcall *pfn_Attach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
	typedef void     (__stdcall *pfn_Attached) (uint32_t _prog_id, uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttachedShaders.xhtml ;
	typedef void     (__stdcall *pfn_Detach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml ;
	public:
		CShaders (void); ~CShaders (void) = default;

		err_code Attach  (const uint32_t _prog_id, const uint32_t _shader_id); // attaches the shader object specified by '_shader_id' to the program object specified by '_prog_id' ;
		err_code Detach  (const uint32_t _prog_id, const uint32_t _shader_id); // detaches a shader object from a program object to which it is attached ;
		err_code Attached(const uint32_t _prog_id, const uint32_t _u_max_cnt, uint32_t* _p_count, uint32_t* _p_shaders); // returns the identifiers of the shader objects attached to a program object;

	private:
		CShaders& operator = (const CShaders&) = delete; CShaders& operator = (CShaders&&) = delete;
	};
}

	class CProg : public CBase {
	typedef uint32_t (__stdcall *pfn_Create)   (void); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
	typedef void     (__stdcall *pfn_Delete)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)  (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
	typedef uint32_t (__stdcall *pfn_IsProg)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glIsProgram.xhtml ;
	typedef void     (__stdcall *pfn_Params)   (uint32_t _prog_id, uint32_t _param_id, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
	typedef void     (__stdcall *pfn_Use)      (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
	typedef void     (__stdcall *pfn_Validate) (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
	public:
		CProg (void); ~CProg (void) = default;

		uint32_t Create  (void);  // creates an empty program object and returns a non-zero value by which it can be referenced ;
		err_code Delete  (const uint32_t _prog_id);  // frees the memory and invalidates the name associated with the program object specified by _prog_id ;
		err_code InfoLog (const uint32_t _prog_id, const int32_t _buf_size, int32_t* _log_len, char* _p_log); // returns the information log for the specified program object ;
		bool     IsProg  (const uint32_t _prog_id);  // determines '_prog_id' refers to a program object or doesn't;
		err_code Params  (const uint32_t _prog_id, const uint32_t _param_id, int32_t* _p_params); // returns the requested object parameter ;
		err_code Use (const uint32_t _prog_id);      // installs the program object specified by program as part of current rendering state ;
		err_code Validate (const uint32_t _prog_id); // checks to see whether the executables contained in program can execute given the current OpenGL state ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
	};
}}}}

#endif/*_GL_PROCS_PROG_H_INCLUDED*/