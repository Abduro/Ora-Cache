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

	using CStringA = ::ATL::CStringA;

	class CParser {
	public:
		CParser (void); CParser (const CParser&) = delete; CParser (CParser&&) = delete; ~CParser (void) = default;

		err_code Do (const s_cache&);   // parses the cached line of text;
		TError& Error (void) const;

	private:
		CParser& operator = (const CParser&) = delete; CParser& operator = (CParser&&) = delete;
		CError m_error;
	};

	enum class e_pfx_type : uint32_t {
		e_desc = 0, e_face, e_group, e_mtl, e_norm, e_space, e_tex_uv, e_vert, e_use_mtl, e_undef
	};

	class CPrefx {
	public:
		 CPrefx (void); CPrefx (const CPrefx&); CPrefx (CPrefx&&) = delete;
		 CPrefx (const e_pfx_type, _pc_sz _p_spec);
		~CPrefx (void) = default;

		bool Is_valid (void) const;

		const
		CStringA&  Spec (void) const;  // gets specifier reference; (ro)
		CStringA&  Spec (void) ;       // gets specifier reference; (rw);
		e_pfx_type Type (void) const;  // gets prefix type, i.e. its identifier;
		err_code   Type (const e_pfx_type); // sets prefix type, returns err_code if input arg value is e_pfx_type::e_undef;

		CPrefx& operator = (const CPrefx&); CPrefx& operator = (CPrefx&&) = delete;
		CPrefx& operator <<(const char* _p_spec);
		CPrefx& operator <<(const e_pfx_type);

		CString To_str (void) const;

	private:
		e_pfx_type m_type;
		CStringA   m_spec; // the class CStringA makes a conversion from wchar_t to char automatically;
	};

	typedef ::std::array<CPrefx, size_t(e_pfx_type::e_undef)> prefx_arr_t;

	class CPrefx_enum {
	public:
		CPrefx_enum (void); CPrefx_enum (const CPrefx_enum&) = delete; CPrefx_enum (CPrefx_enum&&) = delete; ~CPrefx_enum (void) = default;

		static constexpr char* p_prfx[] = {
			"#", "f", "g", "mtllib", "vn", "vp", "vt", "v", "usemtl",
		};

		const
		CPrefx&  Get (const s_cache&); // gets the prefix from the beginning of current line of the source object file;

		err_code Init (void); // fills the array of prefexes by predefined prefex class objects;

	private:
		CPrefx_enum& operator = (const CPrefx_enum&) = delete;  CPrefx_enum& operator = (CPrefx_enum&&) = delete;
		prefx_arr_t  m_prefxs;
	};

}}}

typedef shared::parsers::obj::CPrefx_enum TPrefxs; TPrefxs& Get_prefxs (void); 

#endif/*_OBJ_PARSER_SELF_H_INCLUDED*/