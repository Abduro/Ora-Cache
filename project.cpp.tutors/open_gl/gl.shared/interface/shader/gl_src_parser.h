#ifndef _GL_SRC_PARCER_H_INCLUDED
#define _GL_SRC_PARCER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Oct-2025 at 23:20:08.046, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL generic shader source code parcer interface declaration file;
*/
#include "gl_defs.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

namespace parse {
	class CAttr {
	public: enum class e_cat : uint32_t { e_none = 0x0, e_in = 0x1, e_out = 0x2 };
	public: enum class e_type : uint32_t { e_none = 0x0, e_vec3 = 0x0, e_vec4 = 0x2 }; // can be extended if necessary;
	public:
		CAttr (void); CAttr (const CAttr&) = delete; CAttr (CAttr&&) = delete; ~CAttr (void);

		e_cat Cat (void) const;
		bool  Cat (const e_cat);

		bool Is_valid (void) const;

		_pc_sz Name (void) const;
		bool   Name (_pc_sz);

		e_type Type (void) const;
		bool   Type (const e_type);

	private:
		CAttr& operator = (const CAttr&) = delete; CAttr& operator = (CAttr&&) = delete;
		e_cat m_cat;
		e_type m_type;
		CString m_name;
	};
}
	class CParser {
	public:
		CParser (void); CParser (const CParser&) = delete; CParser (CParser&&) = delete; ~CParser (void);

		TError&  Error (void) const;
		err_code Parse (_pc_sz _p_src); // parses argument declaration in format: in/out|data type|name;

	private:
		CParser& operator = (const CParser&) = delete; CParser& operator = (CParser&&) = delete;
		mutable
		CError  m_error;
	};
}}}}

#endif/*_GL_SRC_PARCER_H_INCLUDED*/