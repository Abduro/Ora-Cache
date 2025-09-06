#ifndef _GL_PROCS_H_INCLUDED
#define _GL_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 13:09:31.015, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' procedures loader wrapper interface declaration file; 
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl {

namespace procs {
	using namespace ex_ui::draw::open_gl;

	typedef ::std::map<CString, PROC> TProcCache;  // the key is the procedure name, the value is the pointer to the address of procefure function/method;

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
		TProcCache m_cached; // every child class will have its own cache of the functions pointers;
		CError m_error;
	};

	class CBuffer : public CBase {
	typedef void (__stdcall *pfn_Bind) (uint32_t _n_target, uint32_t _buff_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml ;
	typedef void (__stdcall *pfn_Data) (uint32_t _n_target, ptrdiff_t _n_size, const void* _p_data, uint32_t _n_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	typedef void (__stdcall *pfn_Delete) (int32_t _n_count, const uint32_t* _p_buffers); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml ;
	typedef void (__stdcall *pfn_GenNames) (int32_t _n_count, uint32_t* _p_names); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml ;
	typedef void (__stdcall *pfn_Named) (uint32_t _n_name, ptrdiff_t _n_size, const void* _p_data, uint32_t _n_usage); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml ;
	public:
		CBuffer (void) = default; ~CBuffer (void) = default;

	private:
		CBuffer& operator = (const CBuffer&) = delete; CBuffer& operator = (CBuffer&&) = delete;
	};

	class CContext : public CBase {
	typedef int32_t  (__stdcall *pfn_ChoosePxFormatArb) (
		HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _n_max_formats, int* _p_formats, uint32_t* _p_fmt_count
	);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	typedef HGLRC    (__stdcall *pfn_CreateCtxAttsArb) (
		HDC, HGLRC _h_shared_ctx, const int* p_att_lst
	);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	typedef int32_t  (__stdcall *pfn_SwapIntervalExt) (int _n_interval);
	public:
		CContext (void); ~CContext (void) = default;

		err_code Get_all (void) ; // in the most cases this method is very useful for testing purposes;

		int32_t ChoosePxFormatArb (HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _n_max_formats, int* _p_formats, uint32_t* _p_fmt_count);
		HGLRC   CreateCtxAttsArb  (HDC, HGLRC _h_shared_ctx, const int* p_att_lst);
		int32_t SwapIntervalExt   (const int _n_interval);

	private:
		CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;
	};

	class CProg : public CBase {
	typedef void     (__stdcall *pfn_Attach)   (uint32_t _prog_id, uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml ;
	typedef int32_t  (__stdcall *pfn_AttLocate)(uint32_t _prog_id, char* _p_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetAttribLocation.xhtml ;
	typedef uint32_t (__stdcall *pfn_Create)   (void); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml ;
	typedef void     (__stdcall *pfn_Delete)   (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)  (uint32_t _prog_id, int32_t _buf_size, int32_t* _log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml ;
	typedef void     (__stdcall *pfn_Link)     (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml ;
	typedef void     (__stdcall *pfn_Params)   (uint32_t _prog_id, uint32_t _p_name, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetProgramiv.xml ;
	typedef void     (__stdcall *pfn_Use)      (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml ;
	typedef void     (__stdcall *pfn_Validate) (uint32_t _prog_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glValidateProgram.xhtml ;
	public:
		CProg (void) = default; ~CProg (void) = default;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
	};

	class CShader : public CBase {
	typedef void     (__stdcall *pfn_Compile)(uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCompileShader.xhtml ;
	typedef uint32_t (__stdcall *pfn_Create) (uint32_t _type);      // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
	typedef void     (__stdcall *pfn_Delete) (uint32_t _shader_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml ;
	typedef void     (__stdcall *pfn_InfoLog)(uint32_t _shader_id, int32_t _n_max_length, int32_t* _p_log_len, char* _p_log); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml ;
	typedef void     (__stdcall *pfn_Params) (uint32_t _shader_id, uint32_t _param_type, int32_t* _p_params); // https://registry.khronos.org/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml ;
	typedef void     (__stdcall *pfn_Source) (uint32_t _handle, int32_t _n_count, const char** const _p_string, const int32_t* _p_length); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
	public:
		CShader (void) = default; ~CShader (void) = default;
	private:
		CShader& operator = (const CShader&) = delete; CShader& operator = (CShader&&) = delete;
	};

	class CVertex : public CBase {
		// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml ;
	typedef void (__stdcall *pfn_AttPtr)   (uint32_t _n_ndx, int32_t _n_size, uint32_t _n_type, uint16_t _b_norm, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_AttPtr_I) (uint32_t _n_ndx, int32_t _n_size, uint32_t _n_type, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_AttPtr_L) (uint32_t _n_ndx, int32_t _n_size, uint32_t _n_type, int32_t _n_stride, const void** _ptr);
	typedef void (__stdcall *pfn_Bind) (uint32_t _arr_id); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml ;
	typedef void (__stdcall *pfn_Delete) (int32_t _n_count, const uint32_t* _p_arrays); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml ;
	typedef void (__stdcall *pfn_DisableAttArr)  (uint32_t _n_ndx); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml ;
	typedef void (__stdcall *pfn_DisableAttArr_2)(uint32_t _arr_id, uint32_t _n_ndx);
	typedef void (__stdcall *pfn_EnableAttArr )  (uint32_t _n_ndx);
	typedef void (__stdcall *pfn_EnableAttArr_2) (uint32_t _arr_id, uint32_t _n_ndx);
	typedef void (__stdcall *pfn_GenNames) (int32_t _n_count, uint32_t* _p_names); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml ;
	public:
		CVertex (void) = default; ~CVertex (void) = default;
	private:
		CVertex& operator = (const CVertex&) = delete; CVertex& operator = (CVertex&&) = delete;
	};

}}}}

#endif/*_GL_PROCS_H_INCLUDED*/