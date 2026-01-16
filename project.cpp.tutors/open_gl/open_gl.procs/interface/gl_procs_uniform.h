#ifndef _GL_PROCS_UNIFORM_H_INCLUDED
#define _GL_PROCS_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Dec-2025 at 22:16:53.975, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL uniform variable related functions' loader interface declaration file;
*/
#include "gl_procs_base.h"
namespace ex_ui { namespace draw { namespace open_gl { namespace procs {
namespace vars {
	class CUniform : public CBase {
	typedef int32_t (__stdcall *pfn_Locate) (const uint32_t _prog_id, const char* _p_name); // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniformLocation.xhtml ;
	public:
		static const int32_t u_na_locate = -1;
		CUniform (void); ~CUniform (void) = default;

		err_code Get_all (void) ;
		int32_t  Locate (const uint32_t _prog_id, _pc_sz _p_name); // returns the location of a uniform variable;

	private:
		CUniform& operator = (const CUniform&) = delete; CUniform& operator = (CUniform&&) = delete;
	};

	typedef ::std::array<float, 2u> t_uniform_2f;
	typedef ::std::array<float, 3u> t_uniform_3f;
	typedef ::std::array<float, 4u> t_uniform_4f;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetUniform.xhtml ; >> gets uniform variable value;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml ;    << sets uniform variable value;
	class CUni_value : public CBase {
	typedef void (__stdcall *pfn_Get_fv ) (const uint32_t _prog_id, const int32_t _n_locate, float* _p_values);      // gets float value(s); glGetUniformfv();
	typedef void (__stdcall *pfn_Get_nfv) (const uint32_t _prog_id, const int32_t _n_locate, const uint32_t _buf_size, float* _p_values);  // gets n-float value(s) through buffer; glGetnUniformfv();
	typedef void (__stdcall *pfn_Set_4fs) (const int32_t _n_locate, float _f_0, float _f_1, float _f_2, float _f_3); // for setting scalar values;
	typedef void (__stdcall *pfn_Set_4fv) (const int32_t _n_locate, const uint32_t _u_count, const float* _p_value); // for setting values to vector and matrix;
	public:
		CUni_value (void); ~CUni_value (void) = default;

		err_code Get_all (void);

		err_code Get_3fs (const uint32_t _prog_id, const uint32_t _n_locate, t_uniform_3f& _arr_values); // gets vec3 data;
		err_code Get_4fs (const uint32_t _prog_id, const uint32_t _n_locate, t_uniform_4f& _arr_values); // gets vec3 data;

		err_code Set_4fs (const int32_t _n_locate, const t_uniform_4f&); // for setting scalar values;
		err_code Set_4fv (const int32_t _n_locate, const t_uniform_4f&); // for setting vector values;

	private:
		CUni_value& operator = (const CUni_value&) = delete; CUni_value& operator = (CUni_value&&) = delete;
	};
}}}}}

typedef ex_ui::draw::open_gl::procs::vars::CUniform    TUniformProcs;  TUniformProcs&  __get_uni_procs (void);
typedef ex_ui::draw::open_gl::procs::vars::CUni_value  TUniValueProcs; TUniValueProcs& __get_uni_val_procs (void);

#endif/*_GL_PROCS_UNIFORM_H_INCLUDED*/