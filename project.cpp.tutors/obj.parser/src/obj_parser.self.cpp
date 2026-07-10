/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jul-2026 at 19:15:48.811, UTC+4, Batumi, Wednesday;
	This is 3D module object file parser interface implementation file;
*/
#include "obj_parser.self.h"

using namespace shared::parsers::obj;

namespace shared { namespace parsers { namespace _impl {

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/scanf-s-scanf-s-l-wscanf-s-wscanf-s-l ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sscanf-s-sscanf-s-l-swscanf-s-swscanf-s-l ; << this one is used;

	class CHelper {
	public:
		CHelper (void) {} CHelper (const CHelper&) = delete; CHelper (CHelper&&) = delete; ~CHelper (void) = default;

		void Get_norm (const CPrefx& _pfx, const s_cache& _cached, s_vec_3& _norm) {
			_pfx; _cached; _norm;
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), "%f %f %f", &_norm._x, &_norm._y, &_norm._z); // the format is "v x y";
			if (vars == 3){}
		}

		void Get_vert (const CPrefx& _pfx, const s_cache& _cached, s_vec_3& _vert) {
			_pfx; _cached; _vert;
			const int vars = ::sscanf_s(_cached.buffer + _pfx.Spec().GetLength(), "%f %f %f", &_vert._x, &_vert._y, &_vert._z); // the format is "v x y (z)";
			if (vars == 3){}
		}

	private:
		CHelper& operator = (const CHelper&) = delete; CHelper& operator = (CHelper&&) = delete;
	};

	CHelper& Get_helper (void) {
		static CHelper helper;
		return helper;
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
		switch (prefx.Type()) {
		case e_pfx_type::e_norm: { s_vec_3 vert; ::Get_helper().Get_norm(prefx, _cached, vert); } break;
		case e_pfx_type::e_vert: { s_vec_3 vert; ::Get_helper().Get_vert(prefx, _cached, vert); } break;
		}
		__trace_info_$(_T("%s\n"), (_pc_sz) prefx.To_str());
	}

	return this->Error();
}

TError&  CParser::Error (void) const { return this->m_error; }

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
	case '#': return this->m_prefxs.at(size_t(e_pfx_type::e_comm));
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