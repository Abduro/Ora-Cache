/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Oct-2025 at 23:22:22.851, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL generic shader source code parcer interface implementation file;
*/
#include "gl_src_parser.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	class CTokens : private no_copy {
	public:
		static inline _pc_sz _p_in    = _T("in" );
		static inline _pc_sz _p_out   = _T("out");
		static inline _pc_sz _p_row   = _T("\n" );
		static inline _pc_sz _p_sep   = _T(" ");
		static inline _pc_sz _p_vec3  = _T("vec3");
		static inline _pc_sz _p_vec4  = _T("vec4");
	};

	class CParser_Helper {
	using CAttr = parse::CAttr;
	CParser_Helper (const CParser_Helper&) = delete; CParser_Helper (CParser_Helper&&) = delete;
	public:
		CParser_Helper (void) { m_error >>__CLASS__<<__METHOD__<<__s_ok; } ~CParser_Helper (void) = default;

		err_code Attr (_pc_sz _p_line) {
			this->m_error <<__METHOD__<<__s_ok;
#if (0)
			if (0 == _p_line || 0 == _tcslen(_p_line))
				return this->m_error << __e_inv_arg;
#endif
			CString cs_line(_p_line); cs_line.Trim();
			if (cs_line.IsEmpty())
				return this->m_error << __e_inv_arg;

			int n_pos = cs_line.Find(CTokens::_p_in, 0);
			if (n_pos >= 0) {
				m_attr.Cat (CAttr::e_cat::e_in); cs_line.Replace(CTokens::_p_in, _T("")); cs_line.Trim();
			}
			else if ((n_pos = cs_line.Find(CTokens::_p_out, 0)) >= 0) {
				m_attr.Cat (CAttr::e_cat::e_out); cs_line.Replace(CTokens::_p_out, _T("")); cs_line.Trim();
			}
			else
				return this->m_error <<__e_inv_arg = _T("#__e_inv_dat: there is no 'in'|'out'");
			if (false) {}
			else if ((n_pos = cs_line.Find(CTokens::_p_vec3, 0)) >= 0) {
				m_attr.Type(CAttr::e_type::e_vec3); cs_line.Replace(CTokens::_p_vec3, _T("")); cs_line.Trim();
			}
			else if ((n_pos = cs_line.Find(CTokens::_p_vec4, 0)) >= 0) {
				m_attr.Type(CAttr::e_type::e_vec4); cs_line.Replace(CTokens::_p_vec4, _T("")); cs_line.Trim();
			}
			else
				return this->m_error <<__e_inv_arg = _T("#__e_inv_dat: there is no data type def");
			// it is supposed the name of attr remains in this line of code; the line is trimmed, so removing semicolons from the right side is enough;
			cs_line = cs_line.Left(cs_line.GetLength() - 1);
			this->m_attr.Name((_pc_sz) cs_line);
				
			return this->Error();
		}

		TError& Error (void) const { return this->m_error; }
	private:
		CParser_Helper& operator = (const CParser_Helper) = delete; CParser_Helper& operator = (CParser_Helper&&) = delete;
		mutable
		CError m_error;
		CAttr  m_attr ;
	};

}}}}
using namespace ex_ui::draw::open_gl::_impl;

parse::CAttr:: CAttr (void) : m_cat(e_cat::e_none), m_type(e_type::e_none) {}
parse::CAttr::~CAttr (void) {}

parse::CAttr::e_cat parse::CAttr::Cat (void) const { return this->m_cat; }
bool  parse::CAttr::Cat (const e_cat _e_val) {
	_e_val;
	const bool b_changed = _e_val != this->Cat(); if (b_changed) this->m_cat = _e_val; return b_changed;
}

bool  parse::CAttr::Is_valid (void) const {
	return (e_cat::e_none != this->Cat() && e_type::e_none != this->Type() && !!this->Name());
}

_pc_sz parse::CAttr::Name (void) const { return (_pc_sz)this->m_name; }
bool parse::CAttr::Name (_pc_sz _p_name) {
	_p_name;
	CString cs_name(_p_name); cs_name.Trim();
	const bool b_changed = !!cs_name.Compare(this->Name());

	if (b_changed)
		this->m_name = cs_name;

	return b_changed;
}

parse::CAttr::e_type parse::CAttr::Type (void) const { return this->m_type; }
bool parse::CAttr::Type (const e_type _e_val) {
	_e_val;
	const bool b_changed = _e_val != this->Type(); if (b_changed) this->m_type = _e_val; return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CParser:: CParser (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CParser::~CParser (void) {}

TError&   CParser::Error (void) const { return this->m_error; }

err_code  CParser::Parse (_pc_sz _p_src) {
	_p_src;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_src || 0 == ::_tcslen(_p_src))
		return this->m_error << __e_inv_arg = _T("The source code string is empty");

	int n_pos[2] = {0}; // 0 - position of row; 1 - position of row part;

	CString cs_src(_p_src);
	CString cs_row = cs_src.Tokenize(CTokens::_p_row, n_pos[0]);

	while (false == cs_row.IsEmpty()) {
		parse::CAttr attr;

		uint32_t u_ndx = 0; // this is some sort of an index that counts what part of the expression is being gotten;

		n_pos[1] = 0;
		CString cs_part = cs_row.Tokenize(CTokens::_p_sep, n_pos[1]);
		while (false == cs_part.IsEmpty()) {
			CString cs_el = cs_part; cs_el.Trim();
			// in this position (0) the attr category is expected: input or output;
			if (0 == u_ndx) {
			if (0 == cs_el.CompareNoCase(_T("#version"))) {}
			if (0 == cs_el.CompareNoCase(_T("in"))) { attr.Cat(parse::CAttr::e_cat::e_in); }
			if (0 == cs_el.CompareNoCase(_T("out"))) { attr.Cat(parse::CAttr::e_cat::e_out); }
			}

			if (1 == u_ndx) {
			if (0 == cs_el.CompareNoCase(_T("vec3"))) { attr.Type(parse::CAttr::e_type::e_vec3); }
			if (0 == cs_el.CompareNoCase(_T("vec4"))) { attr.Type(parse::CAttr::e_type::e_vec4); }
			}

			if (2 == u_ndx) {
				// the semicolon must be removed from the end of string;
				cs_part = cs_part.Left(cs_part.GetLength() - 1);
				attr.Name((_pc_sz)cs_part);
			}
			cs_part = cs_row.Tokenize(CTokens::_p_sep, n_pos[1]); u_ndx += 1;
		}

		cs_row = cs_src.Tokenize(CTokens::_p_row, n_pos[0]);
	}

	return this->Error();
}