#ifndef _GL_PROCS_CTX_H_INCLUDED
#define _GL_PROCS_CTX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 17:35:20.265, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL context functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {

	// https://www.abbreviations.com/abbreviation/Format >> fmt ;
	class CContext : public CBase {
	typedef int32_t (__stdcall *pfn_ChoosePxFormatArb) (HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ;
	typedef HGLRC   (__stdcall *pfn_CreateCtxAttsArb)  (HDC, HGLRC _h_shared_ctx, const int* p_att_lst);  // https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	typedef int32_t (__stdcall *pfn_SwapIntervalExt) (int _n_interval); // https://www.khronos.org/opengl/wiki/Swap_Interval ;
	public:
		CContext (void); ~CContext (void) = default;
		
		int32_t ChoosePxFormatArb (HDC, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count); // selects pixel formats to return based on the attribute values specified in _p_atts_i and _p_atts_f ;
		HGLRC   CreateCtxAttsArb  (HDC, HGLRC _h_shared_ctx, const int* p_att_lst); // creates an OpenGL rendering context ;
		bool    SwapIntervalExt   (const int _n_interval); // controls vertical sync; specifies minimum number of frames before each buffer swap (back and front);

		err_code Get_all (void) ; // in the most cases this method is very useful for testing purposes;

	private:
		CContext& operator = (const CContext&) = delete; CContext& operator = (CContext&&) = delete;
	};

}}}}
#endif/*_GL_PROCS_CTX_H_INCLUDED*/