#ifndef _OBJ_PARSER_DEFS_H_INCLUDED
#define _OBJ_PARSER_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jun-2026 at 10:38:31.531, UTC+4, Batumi, Tuesday;
	This is 3D module object parser common interface declaration file;
*/
#include "shared.defs.h"

namespace shared { namespace parsers { namespace obj { using namespace shared::defs;

	struct s_color {
		uint16_t _r, _g, _b;

		s_color (const uint16_t _u_r = 0, const uint16_t _u_g = 0, const uint16_t _u_b = 0);
	};

	struct s_face { // this structure is used for indexing into the vertex and texture coordinate arrays;
		uint32_t _vert_ndx[3]; // indicies for the verts that make up a triangle;
		uint32_t _tex_ndx[3];  // indicies for the coords to texture a face;

		s_face (void);
	};

	struct s_vec_2 { // this is our 2D point struct for using to store the UV coordinates;
		float _x, _y;

		s_vec_2 (const float _f_x = 0.0f, const float _f_y = 0.0f); ~s_vec_2 (void) = default;

		CString To_str (void) const;
	};

	struct s_vec_3 : s_vec_2 {  // this is our 2D point struct for using to store the vertices of a model;
		float _z;

		s_vec_3 (const float _f_x = 0.0f, const float _f_y = 0.0f, const float _f_z = 0.0f); ~s_vec_3 (void) = default;

		CString To_str (void) const;
	};

	struct t_tex_info {
		uint32_t _id;       // a texture identifier;
		s_color  _clr;      // a color of an object;
		s_vec_2  _offset;   // texture UV offset;
		s_vec_2  _tile;     // texture UV tiling;

		CString  _name;     // texture name;
		CString  _path;     // texture file path (optional, if it is set it's a texture map);

		t_tex_info (void); ~t_tex_info (void) = default;
	};

}}}

#endif/*_OBJ_PARSER_DEFS_H_INCLUDED*/