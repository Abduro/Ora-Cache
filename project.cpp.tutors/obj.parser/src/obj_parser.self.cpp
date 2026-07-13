/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jul-2026 at 19:15:48.811, UTC+4, Batumi, Wednesday;
	This is 3D module object file parser interface implementation file;
*/
#include "obj_parser.self.h"

using namespace shared::parsers::obj;

namespace shared { namespace parsers { namespace _impl {

	/* https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/scanf-s-scanf-s-l-wscanf-s-wscanf-s-l ;
	   https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l ;
	   https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sscanf-s-sscanf-s-l-swscanf-s-swscanf-s-l ; << this one is used;
	*/
	struct s_face_fmt {
		char* p_pat  = 0;   // format pattern;
		int   expect = 0;   // expected format result: how many variables is gotten;

		s_face_fmt (char* const _p_pat, const int _exp) : p_pat(_p_pat), expect(_exp) {}
	};

	static s_face_fmt p_face_fmts[] = {
		{"%d//%d %d//%d %d//%d", 6}, {"%d %d %d", 3} // '%u' is okay because an index is always positive, but if the face string is wrong formatted;
	};

	struct s_vert_fmt {
		char* p_pat  = 0;
		int   expect = 0;
	};

	static s_vert_fmt p_vert_fmts[] = {
		{"%f %f %f %f", 4}, {"%f %f %f", 3} // the precise float format can be specified like this: %9.7f;
	};

	class CConverter {
	public:
		CConverter (void) {} CConverter (const CConverter&) = delete; CConverter (CConverter&&) = delete; ~CConverter (void) = default;

		bool Get_desc (const CPrefx& _pfx, const s_cache& _cached, CString& _desc) {
			_desc; _pfx; _cached;
			CString cs_cmnt = (_cached.buffer + _pfx.Spec().GetLength()); cs_cmnt.Trim();
			if (false == cs_cmnt.IsEmpty()) {
				if (false == _desc.IsEmpty()) _desc += _T("; "); _desc += cs_cmnt;
			}
			return (false == cs_cmnt.IsEmpty());
		}

		bool Get_face (const CPrefx& _pfx, const s_cache& _cached, const bool _norms, s_face& _face) {
			_pfx; _cached; _face; _norms;
			if (false){}
			else if (_norms) {
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), p_face_fmts[0].p_pat,
					&_face._indices.at(0).first, &_face._indices.at(0).second,
					&_face._indices.at(1).first, &_face._indices.at(1).second,
					&_face._indices.at(2).first, &_face._indices.at(2).second
				);
				return (vars == p_face_fmts[0].expect);
			} else {
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), p_face_fmts[1].p_pat,
					&_face._indices.at(0).first,
					&_face._indices.at(1).first,
					&_face._indices.at(2).first
				);
				return (vars == p_face_fmts[1].expect);
			}
			return false;
		}

		bool Get_name (const CPrefx& _pfx, const s_cache& _cached, CString& _name) {
			_name; _pfx; _cached;
			_name = (_cached.buffer + _pfx.Spec().GetLength()); _name.Trim();
			return true;
		}

		bool Get_norm (const CPrefx& _pfx, const s_cache& _cached, normal_t& _norm) {
			_pfx; _cached; _norm;
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), "%f %f %f", &_norm._x, &_norm._y, &_norm._z); // the format is "vn x y z";
			return (vars == 3);
		}

		bool Get_quad (const CPrefx& _pfx, const s_cache& _cached, quad_t& _quad) {
			_pfx; _cached; _quad;
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), p_vert_fmts[0].p_pat, &_quad._x, &_quad._y, &_quad._z, &_quad._w);
			return (vars == p_vert_fmts[0].expect);
		}

		bool Get_vert (const CPrefx& _pfx, const s_cache& _cached, s_vec_3& _vert) {
			_pfx; _cached; _vert;
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), "%f %f %f", &_vert._x, &_vert._y, &_vert._z); // the format is "v x y (z)";
			return (vars == 3);
		}

		static
		uint32_t Get_vert_fmt_ndx (const CPrefx& _pfx, const s_cache& _cached) {
			_pfx; _cached;
			// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class#tokenize ;
			static _pc_sz p_sep = _T(" ");
			int n_ndx = 0;
			int n_cnt = 0;
			CString cs_data(_cached.buffer + _pfx.Spec().GetLength());
			CString cs_token = cs_data.Tokenize(p_sep, n_ndx);
			while ( cs_token.IsEmpty() == false) {
				n_cnt += 1;
				cs_token = cs_data.Tokenize(p_sep, n_ndx);
			}
			return n_cnt > 3 ? 0 : 1;
		}

	private:
		CConverter& operator = (const CConverter&) = delete; CConverter& operator = (CConverter&&) = delete;
	};

	CConverter& Converter (void) {
		static CConverter conv;
		return conv;
	}

}}} using namespace shared::parsers::_impl;

#pragma region cls::CParser{}

CParser::CParser (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CParser::Do (const s_cache& _cached) {
	_cached;
	this->m_error <<__METHOD__<<__s_ok;
	
	TPrefxs& prefxs = ::Get_prefxs();
	const CPrefx& prefx = prefxs.Get(_cached);
	if ( false == prefx.Is_valid() ) {
	}
	else {
		s_draw_obj& drw_obj = ::Get_model()._objects.at(0);
		switch (prefx.Type()) {
		case e_pfx_type::e_desc : {
			if (::Converter().Get_desc(prefx, _cached, drw_obj._desc))
			__trace_info_$(_T("# %s\n"), (_pc_sz) drw_obj._desc);
		} break;
		case e_pfx_type::e_face : { s_face  face;
			if (::Converter().Get_face(prefx, _cached, false == drw_obj._normals.empty(), face)) drw_obj._faces.push_back(face);
			__trace_info_$(_T("%s\n"), (_pc_sz) CPrint::Face(face));
		} break;
		case e_pfx_type::e_group: {
			CString cs_name; if (::Converter().Get_name(prefx, _cached, cs_name)) drw_obj._name = cs_name;
			__trace_info_$(_T("%s\n"), (_pc_sz) TString().Format(_T("group name: %s"), (_pc_sz)cs_name));
		} break;
		case e_pfx_type::e_norm : { normal_t norm; if (::Converter().Get_norm(prefx, _cached, norm)) drw_obj._normals.push_back(norm);
			__trace_info_$(_T("%s\n"), (_pc_sz) CPrint::Norm(norm));
		} break;
		case e_pfx_type::e_vert : {
			if (this->m_state._vert_fmt_def == false) {
				m_state._vert_fmt_ndx = CConverter::Get_vert_fmt_ndx(prefx, _cached);
				m_state._vert_fmt_def = true;
			}
			if (m_state._vert_fmt_ndx == 0) { // this is the index of long length format for quads, i.e. s_vec_4;
				quad_t quad;
				if (::Converter().Get_quad(prefx, _cached, quad)) drw_obj._quads.push_back(quad);
				__trace_info_$(_T("%s\n"), (_pc_sz) CPrint::Quad(quad));
			}
			else {
				vertex_t vert;
				if (::Converter().Get_vert(prefx, _cached, vert)) drw_obj._vertices.push_back(vert);
				__trace_info_$(_T("%s\n"), (_pc_sz) CPrint::Vert(vert));
			}
		} break;
		}
	}

	return this->Error();
}

TError&  CParser::Error (void) const { return this->m_error; }

err_code CParser::Reset (void) {
	this->m_state._vert_fmt_def = false;
	return __s_ok;
}

#pragma endregion
#pragma region cls::CPrefx{}

CPrefx::CPrefx (void) : m_type(e_pfx_type::e_undef) {}
CPrefx::CPrefx (const CPrefx& _src) : CPrefx() { *this = _src; }
CPrefx::CPrefx (const e_pfx_type _type, _pc_sz _p_spec) : m_type(_type), m_spec(_p_spec) {}

bool CPrefx::Is_valid (void) const {
	return e_pfx_type::e_undef != this->Type(); 
}

const
CStringA&  CPrefx::Spec (void) const { return this->m_spec; }
CStringA&  CPrefx::Spec (void)       { return this->m_spec; }

e_pfx_type CPrefx::Type (void) const { return this->m_type; }
err_code   CPrefx::Type (const e_pfx_type _type) {
	_type;
	this->m_type = _type; return e_pfx_type::e_undef == _type ? __e_inv_arg : __s_ok;
}

CPrefx& CPrefx::operator = (const CPrefx& _src) { *this << _src.Type() << _src.Spec(); return *this; }
CPrefx& CPrefx::operator <<(const char* _p_spec) { this->Spec() = _p_spec; return *this; }
CPrefx& CPrefx::operator <<(const e_pfx_type _type) { this->Type(_type); return *this; }

CString CPrefx::To_str (void) const {
	static _pc_sz p_fmt_pat = _T("%s");
	CString cs_out; cs_out.Format(p_fmt_pat, (_pc_sz) CString(this->Spec()));
	return  cs_out;
}

#pragma endregion
#pragma region cls::CPrefx_enum{}

CPrefx_enum::CPrefx_enum (void) { this->Init(); }

static CPrefx pfx_inv;

const
CPrefx&  CPrefx_enum::Get (const s_cache& _cached) {
	_cached;
	// for some values of the first symbol/letter there is no sense to know the next symbol;
	switch (_cached.buffer[0]) {
	case '#': return this->m_prefxs.at(size_t(e_pfx_type::e_desc));
	case 'f': return this->m_prefxs.at(size_t(e_pfx_type::e_face));
	case 'g': return this->m_prefxs.at(size_t(e_pfx_type::e_group));
	case 'm': return this->m_prefxs.at(size_t(e_pfx_type::e_mtl));
	case 'u': return this->m_prefxs.at(size_t(e_pfx_type::e_use_mtl));
	case 'v': { // this letter value requires to get the next symbol(s);
		if (_cached.buffer[1] == ' ') return this->m_prefxs.at(size_t(e_pfx_type::e_vert));
		if (_cached.buffer[1] == 'n') return this->m_prefxs.at(size_t(e_pfx_type::e_norm));
		if (_cached.buffer[1] == 'p') return this->m_prefxs.at(size_t(e_pfx_type::e_space));
		if (_cached.buffer[1] == 't') return this->m_prefxs.at(size_t(e_pfx_type::e_tex_uv));
	} break;
	}
	return pfx_inv;
}

err_code CPrefx_enum::Init (void) {

	for (uint32_t i_ = 0; i_ < this->m_prefxs.size() && i_ < _countof(p_prfx); i_++) { // it is supposed p_prfx array has appropriate size;
		CPrefx& prfx = this->m_prefxs.at(i_);
		prfx << static_cast<e_pfx_type>(i_) << p_prfx[i_]; // https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c ;
	}
	return __s_ok; // no error catching yet;
}

#pragma endregion

TPrefxs& ::Get_prefxs (void) {
	static TPrefxs prefxs;
	return  prefxs;
}