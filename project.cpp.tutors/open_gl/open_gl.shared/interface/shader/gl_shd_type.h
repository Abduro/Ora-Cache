#ifndef _GL_SHD_TYPE_H_INCLUDED
#define _GL_SHD_TYPE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 20:02:22.895, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader type wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

#pragma region __shader_types
/* copied from glcorearb.h */
#define __t_compute    0x91B9 // GL_COMPUTE_SHADER ;
#define __t_fragment   0x8B30 // GL_FRAGMENT_SHADER ;
#define __t_geometry   0x8DD9 // GL_GEOMETRY_SHADER ;
#define __t_tess_ctrl  0x8E88 // GL_TESS_CONTROL_SHADER ;
#define __t_tess_eval  0x8E87 // GL_TESS_EVALUATION_SHADER ;
#define __t_vertex     0x8B31 // GL_VERTEX_SHADER ;
#pragma endregion
	// https://en.wikipedia.org/wiki/Shader ;
	class CType {
	public:
		enum e_value : uint16_t {    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateShader.xhtml ;
		     e_undef     = 0x0,
		     e_compute   = __t_compute  ,
		     e_fragment  = __t_fragment , // for manipulating properties such as position, color and texture coordinates, but cannot create new vertices;
		     e_geometry  = __t_geometry , // for generating new graphics primitives;
		     e_tess_ctrl = __t_tess_ctrl,
		     e_tess_eval = __t_tess_eval,
		     e_vertex    = __t_vertex   , // https://www.khronos.org/opengl/wiki/Vertex_Shader ;
		};
		CType (void); CType (const CType&); CType (CType&&) = delete; ~CType (void) = default;

		TErr_ex& Error (void) const;

		e_value Get (void) const;
		bool    Set (const e_value);

		bool Is_fragment (void) const;
		bool Is_vertex (void) const;

		operator uint16_t (void) const; // returns currently set value of the shader type;

		static CString To_str(const uint32_t _u_type); // the data type is intentionally changed for avoiding unnecessary casts;
		static e_value Get_type (const uint32_t _u_shader_id, CError&);

	public:
		CType& operator = (const CType&); CType& operator = (CType&&) = delete;
	private:
		e_value m_value;
		CErr_ex m_error;
	};

}}}}

typedef ex_ui::draw::open_gl::shader::CType::e_value TType;

#endif/*_GL_SHD_TYPE_H_INCLUDED*/