#ifndef _GL_SHD_TYPE_H_INCLUDED
#define _GL_SHD_TYPE_H_INCLUDED
/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 27-Sep-2025 at 20:02:22.895, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL shader type wrapper interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

	// https://en.wikipedia.org/wiki/Shader ;
	class CType {
	public:
		enum e_value : uint16_t { // this enumeration must be declared in procs loader class;
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
		/* tesselation shaders are for simpler meshes to be subdivided into finer meshes at run-time; for viewing camera to allow active level-of-detail scaling;*/
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

typedef ex_ui::draw::open_gl::shader::CType::e_value $Type;

#endif/*_GL_SHD_TYPE_H_INCLUDED*/