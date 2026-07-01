#ifndef _OBJ_PARSER_DEFS_H_INCLUDED
#define _OBJ_PARSER_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jun-2026 at 10:38:31.531, UTC+4, Batumi, Tuesday;
	This is 3D module object parser common interface declaration file;
*/
#include "shared.defs.h"
#include "shared.preproc.h"
#include "shared.dbg.h"
#include "shared.theme.h"
#include "sys.registry.h"

namespace shared { namespace parsers { namespace obj { using namespace shared::defs;

	/* https://en.wikipedia.org/wiki/Big_O_notation ;
	// https://www.geeksforgeeks.org/dsa/understanding-time-complexity-simple-examples/ ;
	// https://en.wikipedia.org/wiki/Epoll ;
	// https://en.wikipedia.org/wiki/POSIX ;
	// https://en.wikipedia.org/wiki/Wavefront_.obj_file;
	// https://stackoverflow.com/questions/4262503/whats-the-difference-between-material-and-texture ;
	*/

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
#if (0)
		CString To_str (void) const;
#endif
	};

	struct s_vec_3 : s_vec_2 {  // this is our 2D point struct for using to store the vertices of a model;
		float _z;

		s_vec_3 (const float _f_x = 0.0f, const float _f_y = 0.0f, const float _f_z = 0.0f); ~s_vec_3 (void) = default;
#if (0)
		CString To_str (void) const;
#endif
	};

	struct s_tex_info {     // this structure holds the information for a material;
		uint32_t _id;       // texture identifier;
		s_vec_2  _offset;   // texture UV offset;
		s_vec_2  _tile;     // texture UV tiling;

		CString  _name;     // texture name;
		CString  _path;     // texture file path (optional, if it is set it's a texture map);

		s_tex_info (void); ~s_tex_info (void) = default;
	};

	struct s_mat_info {     // this structure holds the information for a material;
		s_tex_info _tex;    // a texture information;
		s_color    _clr;    // a color of an object;

		s_mat_info (void); ~s_mat_info (void) = default;
	};

	struct s_draw_obj {

		::std::vector<s_vec_3> _vertices;   // object's vertices;
		::std::vector<s_vec_3> _normals;    // object's normals;
		::std::vector<s_vec_2> _uv_coord;   // texture's UV coordinates;
		::std::vector<s_face>  _faces;      // faces' info;

		s_draw_obj (void); ~s_draw_obj (void) = default;
	};

	struct s_model {

		::std::vector<s_mat_info> _materials;
		::std::vector<s_draw_obj> _objects;

		s_model (void); ~s_model (void) = default;
	};
}}}

#endif/*_OBJ_PARSER_DEFS_H_INCLUDED*/