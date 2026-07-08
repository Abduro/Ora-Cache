#ifndef _OBJ_PARSER_SELF_H_INCLUDED
#define _OBJ_PARSER_SELF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jul-2026 at 19:13:25.947, UTC+4, Batumi, Wednesday;
	This is 3D module object file parser interface declaration file;
*/
#include "obj_parser.defs.h"

namespace shared { namespace parsers { namespace obj {

	// https://en.wikipedia.org/wiki/Wavefront_.obj_file ;
	// https://www.songho.ca/opengl/gl_obj.html ;

	class CParser {
	public:
		CParser (void); CParser (const CParser&) = delete; CParser (CParser&&) = delete; ~CParser (void) = default;

		err_code Do (const FILE*);   // it is supposed the input file stream is already checked for text data type;
		TError& Error (void) const;

	private:
		CParser& operator = (const CParser&) = delete; CParser& operator = (CParser&&) = delete;
		CError m_error;
	};

	enum class e_pfx_type : uint32_t {
		e_comm = 0, e_face, e_group, e_mtl, e_norm, e_space, e_tex_uv, e_vert, e_use_mtl, e_undef
	};

	class CPrefx {
	public:
		 CPrefx (void) = default; CPrefx (const CPrefx&) = delete; CPrefx (CPrefx&&) = delete;
		 CPrefx (const e_pfx_type, _pc_sz _p_spec);
		~CPrefx (void) = default;

		e_pfx_type Type (void) const;

	private:
		CPrefx& operator = (CPrefx&) = delete; CPrefx& operator = (CPrefx&&) = delete;
		e_pfx_type    m_type;
		::std::string m_spec;
	};

	class CSpecifier {
	public:
		 CSpecifier (void) = default; CSpecifier (const CSpecifier&) = delete; CSpecifier (CSpecifier&&) = delete;
		~CSpecifier (void) = default;

		static constexpr char* p_prfx[] = {
			"#", "f", "g", "mtllib", "vn", "vp", "vt", "v", "usemtl",
		};

		enum e_type : uint32_t {
		e_comm = 0, e_face, e_group, e_mtl, e_norm, e_space, e_tex_uv, e_vert, e_use_mtl, e_undef
		};

		e_type Get (FILE* const) const;


	private:
		CSpecifier& operator = (CSpecifier&) = delete; CSpecifier& operator = (CSpecifier&&) = delete;
	};

}}}

#endif/*_OBJ_PARSER_SELF_H_INCLUDED*/