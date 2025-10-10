#ifndef _GL_SHADER_BUFFER_H_INCLUDED
#define _GL_SHADER_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Oct-2025 at 16:20:00.933, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL shader functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl {
namespace procs {

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

#endif/*_GL_SHADER_BUFFER_H_INCLUDED*/