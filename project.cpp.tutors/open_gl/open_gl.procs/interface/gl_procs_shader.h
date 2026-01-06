#ifndef _GL_SHADER_BUFFER_H_INCLUDED
#define _GL_SHADER_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Oct-2025 at 16:20:00.933, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL shader functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl {
namespace procs {

	enum class e_shader_types : uint32_t {
		/* alias    | value    | OpenGL symbolic def       | brief description ;
		------------+----------+---------------------------+-------------------*/
		e_undef     = 0x0000,  // the type is not set;     |
		e_compute   = 0x91B9,  // GL_COMPUTE_SHADER        | for additional stages in animation or lighting algorithms (e.g. tiled forward rendering);
		e_fragment  = 0x8B30,  // GL_FRAGMENT_SHADER       | for manipulating properties such as position, color and texture coordinates, but cannot create new vertices;
		e_geometry  = 0x8DD9,  // GL_GEOMETRY_SHADER       | for generating new graphics primitives; executed after vertex shaders;
		e_tess_ctrl = 0x8E88,  // GL_TESS_CONTROL_SHADER   | tessellation control shader (also known as hull shader);
		e_tess_eval = 0x8E87,  // GL_TESS_EVALUATION_SHADER| evaluation shader (also known as domain shader); 
		e_vertex    = 0x8B31,  // GL_VERTEX_SHADER         | transforms vertex's 3D position in virtual space to the 2D coords of the screen (as well as a depth value for the Z-buffer); https://www.khronos.org/opengl/wiki/Vertex_Shader ;
	};

	CString $_type_to_str (const uint32_t _u_$_type); // converts a shader type constant to string for trace output;

	class CShader : public CBase {
	typedef uint32_t (__stdcall *pfn_Create) (uint32_t _u_type);    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
	typedef void     (__stdcall *pfn_Delete) (uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)(uint32_t _shader_id, int32_t _n_max_length, int32_t* _p_log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml ;
	typedef uint32_t (__stdcall *pfn_IsValid)(uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glIsShader.xml ;
	typedef void     (__stdcall *pfn_Params) (uint32_t _shader_id, uint32_t _param_type, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml ;
	typedef void     (__stdcall *pfn_Source) (uint32_t _shader_id, int32_t _n_count, const char** const _p_string, const int32_t* _p_length); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml ;
	public:
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShader.xhtml ;
		enum e_param_types : uint32_t {
		/* alias     | value    | OpenGL symbolic defs     | brief description ;
		-------------+----------+--------------------------+--------------------------*/
		e_compiled   = 0x8B81, // GL_COMPILE_STATUS        | returns 'true' if the last compile operation on shader was successful, and 'false' otherwise;
		e_deleted    = 0x8B80, // GL_DELETE_STATUS         | returns 'true' if shader is currently flagged for deletion, and 'false' otherwise;
		e_info_len   = 0x8B84, // GL_INFO_LOG_LENGTH       | returns the number of characters in the information log for shader including the null termination character;
		e_src_len    = 0x8B88, // GL_SHADER_SOURCE_LENGTH  | returns the length of the concatenation of the source strings that make up the shader source for the shader, including the null termination character;
		e_$_type     = 0x8B4F, // GL_SHADER_TYPE           | returns GL_VERTEX_SHADER, GL_GEOMETRY_SHADER and GL_FRAGMENT_SHADER if shader is one of those types;
		};
		CShader (void); ~CShader (void) = default;

		uint32_t Create  (const uint32_t _u_type);    // creates an empty shader object and returns a non-zero value by which it can be referenced ;
		err_code Delete  (const uint32_t _shader_id); // frees the memory and invalidates the name associated with the shader object specified by _shader_id ;
		err_code InfoLog (const uint32_t _shader_id, const uint32_t _u_max_len, int32_t* _p_log_len, char* _p_log); // returns the information log for the specified shader object ;
		bool   Is_valid  (const uint32_t _shader_id); //  determines if _shader_id corresponds to a shader object, i.e. returns 'true' if the shader object with such identifier exists;
		err_code Params  (const uint32_t _shader_id, const uint32_t _param_type, int32_t* _p_params); // returns a parameter from a shader object ; the error object is updated in case of this function failure;
		err_code Source  (const uint32_t _shader_id, const int32_t _n_count, const char** const _p_string, const int32_t* _p_length); // sets the source code in shader to the source code in the array of strings specified by _p_string ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CShader& operator = (const CShader&) = delete; CShader& operator = (CShader&&) = delete;
	};

}}}}

typedef ex_ui::draw::open_gl::procs::CShader TShaderProcs; TShaderProcs&  __get_$_procs (void);

#endif/*_GL_SHADER_BUFFER_H_INCLUDED*/