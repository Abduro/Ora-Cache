#ifndef _GL_PROCS_H_INCLUDED
#define _GL_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:09:31.015, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface declaration file; 
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {
	// https://www.khronos.org/opengl/wiki/OpenGL_Type ;
namespace procs {
	using namespace ex_ui::draw::open_gl;

	typedef ::std::map<CString, PROC> TProcCache;  // the key is the procedure name, the value is the pointer to the address of procefure function/method;

	// ToDo: it would be better in case if the cache is global and static for all functions; it looks very like OpenGL functions do not have the same names;
	class CBase { // not thread safe yet;
	public:
		CBase (void) ; CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;

		TError&  Error (void) const;
		PROC     Get (_pc_sz _p_fun_name); // https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions#Windows ;
		err_code Get_all (void); // get all functions pointers; in this base class it does nothing, must be implemented in a child class if necessary;

		CString  Print (void) const; // enumerates all loaded function(s); the output string is formatted for message box (i.e. multilined);

	private:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;

	protected:
		mutable
		CError m_error;
		TProcCache m_cached; // every child class will have its own cache of the functions pointers;
	};

	/**important*:
	if original function of the OpenGL returns 'void' the wrapper will return 'err_code' for indicating 'success' or 'failure' of loading a function pointer;
	*/

	// https://www.abbreviations.com/abbreviation/Target >> tgt ;
	class CBuffer : public CBase {
	typedef void (__stdcall *pfn_Bind) (uint32_t _u_tgt_id, uint32_t _u_buff_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
	typedef void (__stdcall *pfn_Data) (uint32_t _u_tgt_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	typedef void (__stdcall *pfn_Delete) (int32_t _n_count, const uint32_t* _p_buffers); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml ;
	typedef void (__stdcall *pfn_GenIds) (int32_t _n_count, uint32_t* _p_buff_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml ;
	typedef void (__stdcall *pfn_Named) (uint32_t _u_name, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	public:
		CBuffer (void); ~CBuffer (void) = default;

		err_code Bind (uint32_t _u_tgt_id, uint32_t _u_buff_id); // binds a buffer object to the specified buffer binding point ;
		err_code Data (uint32_t _u_tgt_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage); // creates and initializes a buffer object's data store currently bound to target is used ;
		err_code Delete (int32_t  _n_count, const uint32_t* _p_buffers); // deletes _n_count buffer objects named by the elements of the array _p_buffers ;
		err_code GenerateIds (int32_t _n_count, uint32_t* _p_buff_ids); // returns _n_count buffer object names in _p_names array ;
		err_code Named (uint32_t _u_buff_id, ptrdiff_t _n_size, const void* _p_data, uint32_t _u_usage);  // creates and initializes a buffer object associated with ID specified by the caller in buffer will be used instead ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator = (CBuffer&&) = delete;
	};

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

	// https://www.abbreviations.com/abbreviation/Format >> fmt ;
	class CContext : public CBase {
	typedef int32_t (__stdcall *pfn_ChoosePxFormatArb) (HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	typedef HGLRC   (__stdcall *pfn_CreateCtxAttsArb)  (HDC, HGLRC _h_shared_ctx, const int* p_att_lst);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	typedef int32_t (__stdcall *pfn_SwapIntervalExt) (int _n_interval); // https://www.khronos.org/opengl/wiki/Swap_Interval ;
	public:
		CContext (void); ~CContext (void) = default;

		err_code Get_all (void) ; // in the most cases this method is very useful for testing purposes;
		
		int32_t ChoosePxFormatArb (HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count); // selects pixel formats to return based on the attribute values specified in _p_atts_i and _p_atts_f ;
		HGLRC   CreateCtxAttsArb  (HDC, HGLRC _h_shared_ctx, const int* p_att_lst); // creates an OpenGL rendering context ;
		bool    SwapIntervalExt   (const int _n_interval); // controls vertical sync; specifies minimum number of frames before each buffer swap (back and front);

	private:
		CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;
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

	class CProg : public CBase {
	typedef int32_t  (__stdcall *pfn_AttLocate)(uint32_t _prog_id, char* _p_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
	typedef uint32_t (__stdcall *pfn_Create)   (void); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
	typedef void     (__stdcall *pfn_Delete)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)  (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
	typedef void     (__stdcall *pfn_Params)   (uint32_t _prog_id, uint32_t _param_id, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
	typedef void     (__stdcall *pfn_Use)      (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
	typedef void     (__stdcall *pfn_Validate) (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
	public:
		CProg (void); ~CProg (void) = default;

		int32_t  AttLocate (uint32_t _prog_id, char* _p_name);     // returns the location of an attribute variable ;
		uint32_t Create  (void);  // creates an empty program object and returns a non-zero value by which it can be referenced ;
		err_code Delete  (uint32_t _prog_id);  // frees the memory and invalidates the name associated with the program object specified by _prog_id ;
		err_code InfoLog (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log); // returns the information log for the specified program object ;
		err_code Params  (uint32_t _prog_id, uint32_t _param_id, int32_t* _p_params); // returns the requested object parameter ;
		err_code Use (uint32_t _prog_id);      // installs the program object specified by program as part of current rendering state ;
		err_code Validate (uint32_t _prog_id); // checks to see whether the executables contained in program can execute given the current OpenGL state ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
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

	class CVertex : public CBase {
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	typedef void (__stdcall *pfn_AttPtr)   (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_AttPtr_I) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_AttPtr_L) (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_Bind) (uint32_t _arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
	typedef void (__stdcall *pfn_Delete) (int32_t _n_count, const uint32_t* _p_arrays); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	typedef void (__stdcall *pfn_DisableArrAtt)(uint32_t _arr_id, uint32_t _n_ndx);
	typedef void (__stdcall *pfn_DisableAttArr)(uint32_t _u_ndx); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void (__stdcall *pfn_EnableArrAtt) (uint32_t _arr_id, uint32_t _n_ndx);
	typedef void (__stdcall *pfn_EnableAttArr) (uint32_t _u_ndx);
	typedef void (__stdcall *pfn_GenIds) (int32_t _n_count, uint32_t* _p_ids); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
	public:
		CVertex (void); ~CVertex (void) = default;

		err_code AttPtr (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, uint16_t _b_norm, int32_t _n_stride, const void** _ptr); // defines an array of generic vertex attribute data (signed & unsigned) ;
		err_code AttPtr_I (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr); // the integer types GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT ;
		err_code AttPtr_L (uint32_t _u_ndx, int32_t _n_size, uint32_t _u_type, int32_t _n_stride, const void** _ptr); // specifies state for a generic vertex attribute array associated with a shader attribute variable declared with 64-bit double precision components ;
		err_code Bind (uint32_t _arr_id); // binds the vertex array object with name array ;
		err_code Delete (int32_t _n_count, const uint32_t* _p_arrays); // deletes vertex array objects ;
		err_code DisableArrAtt (uint32_t _arr_id, uint32_t _n_ndx);    // disables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code DisableAttArr (uint32_t _u_ndx);                      // disables currently bound vertex array object for the operation ;
		err_code EnableArrAtt  (uint32_t _arr_id, uint32_t _n_ndx);    // enables an attribute by index and updates state of the vertex array object with _arr_id ;
		err_code EnableAttArr  (uint32_t _u_ndx);                      // enables currently bound vertex array object for the operation ;
		err_code GenerateIds   (int32_t _n_count, uint32_t* _p_ids);   // generates vertex array object names and guarantees that none of the returned names was in use immediately before the call to it ;

		err_code Get_all (void) ; // gets all functions' pointers at once;

	private:
		CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;
	};

	class CViewport : public CBase {
	typedef void (__stdcall *pfn_DepthFun) (uint32_t _u_type); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml ;
	typedef void (__stdcall *pfn_DepthRng_dbl) (double _d_near, double _d_far);// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthRange.xhtml ;
	typedef void (__stdcall *pfn_DepthRng_flt) (float _f_near, float _f_far);  // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDepthRange.xhtml ;
	typedef void (__stdcall *pfn_Scale)(float _f_factor, float _f_units); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glPolygonOffset.xhtml ;
	typedef void (__stdcall *pfn_Set) (int32_t _x, int32_t _y, uint32_t _u_width, uint32_t _u_height); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml ;
	public:
		CViewport (void); ~CViewport (void) = default;
		// https://en.wikipedia.org/wiki/Affine_transformation ;
		err_code Set (const int32_t _x, const int32_t _y, const uint32_t _u_width, const uint32_t _u_height); // specifies the affine transformation of x and y from normalized device coordinates to window coordinates;
	public:
		class CDepth : no_copy {
		public:
			CDepth (void); ~CDepth (void) = default;

		};

	private:
		CViewport& operator = (const CViewport&) = delete; CViewport& operator = (CViewport&&) = delete;
		friend class CViewport::CDepth;
	};

}}}}

#endif/*_GL_PROCS_H_INCLUDED*/