#ifndef _GL_SHD_TYPE_H_INCLUDED
#define _GL_SHD_TYPE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 20:02:22.895, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader type wrapper interface declaration file;
*/
#include "gl_defs.h"
#include "gl_procs_shader.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	// https://en.wikipedia.org/wiki/Shader ;
	class CType {
	public:
		using e_value = procs::e_shader_types;
		CType (void); CType (const CType&); CType (CType&&) = delete; ~CType (void) = default;

		TError& Error (void) const;

		e_value Get (void) const;
		bool    Set (const e_value);

		bool Is_fragment (void) const;
		bool Is_vertex (void) const;

		operator uint32_t (void) const; // returns currently set value of the shader type;

		static CString To_str(const uint32_t _u_type); // the data type is intentionally changed for avoiding unnecessary casts;
		static e_value Get_type (const uint32_t _u_shader_id, CError&);

	public:
		CType& operator = (const CType&); CType& operator = (CType&&) = delete;
	private:
		e_value m_value;
		CError  m_error;
	};

}}}}

typedef ex_ui::draw::open_gl::shader::CType::e_value $Type;

#endif/*_GL_SHD_TYPE_H_INCLUDED*/