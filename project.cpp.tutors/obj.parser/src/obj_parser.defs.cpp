/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jun-2026 at 10:41:30.418, UTC+4, Batumi, Tuesday;
	This is 3D module object parser common interface implementation file;
*/
#include "obj_parser.defs.h"

using namespace ::shared::parsers::obj;

#pragma region str::s_color{}

s_color::s_color (const uint16_t _u_r, const uint16_t _u_g, const uint16_t _u_b) : _r(_u_r), _g(_u_g), _b(_u_b) {}

#pragma endregion
#pragma region str::s_draw_obj{}

s_draw_obj::s_draw_obj (void) {}

void s_draw_obj::Reset (void) {
	this->_vertices.clear(); this->_normals.clear(); this->_uv_coord.clear(); this->_faces.clear(); this->_desc.Empty();; this->_name.Empty();
}

#pragma endregion
#pragma region str::s_face{}

s_face::s_face (void) {}

#pragma endregion
#pragma region str::s_mat_info{}

s_mat_info::s_mat_info (void) {}

#pragma endregion
#pragma region str::s_tex_info{}

s_tex_info::s_tex_info (void) : _id(0){}

#pragma endregion
#pragma region str::s_vec_2{}

s_vec_2::s_vec_2 (const float _f_x, const float _f_y) : _x(_f_x), _y(_f_y) {}
#if (0)
CString s_vec_2::To_str (void) const {
	static _pc_sz p_pat = _T("x=%.7f;y=%.7f");
	CString cs_out; cs_out.Format(p_pat, this->_x, this->_y);
	return  cs_out;
}
#endif
#pragma endregion
#pragma region str::s_vec_3{}

s_vec_3::s_vec_3 (const float _f_x, const float _f_y, const float _f_z) : s_vec_2(_f_x, _f_y), _z(_f_z) {}
#if (0)
CString s_vec_3::To_str (void) const {
	static _pc_sz p_pat = _T("%s;z=%.7f");
	CString cs_out; cs_out.Format(p_pat, (_pc_sz) s_vec_2::To_str(), this->_z);
	return  cs_out;
}
#endif
#pragma endregion
#pragma region str::s_model{}

s_model::s_model (void) { this->_objects.push_back(s_draw_obj()); } // adds an empty draw object by default;

void s_model::Reset (void) {
	for (uint32_t i_ = 0; i_ < this->_objects.size(); i_++) {
		this->_objects.at(i_).Reset();
	}
}

#pragma endregion

namespace shared { namespace parsers { namespace _impl {

	struct s_indent {
		uint32_t _digits = 0;
		_pc_sz Get (void) {
			return this->Get(this->_digits);
		}
		
		_pc_sz Get (const uint32_t _places) const {
			switch (_places) {
			case 1:  return _T(" ");
			case 2:  return _T("  ");
			case 3:  return _T("   ");
			default: return _T("");
			}
		}

		uint32_t Set (const float _f_val) {
			const int n_val = int(abs(_f_val));
			if (false){}
			else if (n_val > 99 && this->_digits < 3) this->_digits = 3;
			else if (n_val >  9 && this->_digits < 2) this->_digits = 2;
			else this->_digits = 1;
			return this->_digits;
		}
		s_indent& operator <<(const float _f_val) { this->Set(_f_val); return *this; }
		operator uint32_t (void) const { return this->_digits; }
	};

	static s_indent  g_indent;

	void _elem_to_str (const  float  _f_val, _pc_sz _p_format, CString& _out) {
		static CString cs_val;
		cs_val = TString().Float(_f_val, t_fmt_spec::e_decimal, _p_format);
		if (_T('-') == cs_val.Left(1)) {
		_out += g_indent.Get(g_indent._digits - 1); } else
		_out += g_indent.Get(g_indent._digits - 0);
		_out += cs_val;
	}

	void _quad_to_str (const s_vec_4& _quad, _pc_sz _p_format, CString& _out) {
		_quad; _p_format; _out;
		g_indent << _quad._x << _quad._y << _quad._z << _quad._w;

		_elem_to_str(_quad._x, _p_format, _out); _out += _T(" ");
		_elem_to_str(_quad._y, _p_format, _out); _out += _T(" ");
		_elem_to_str(_quad._z, _p_format, _out); _out += _T(" ");
		_elem_to_str(_quad._w, _p_format, _out);
	}

	void _vert_to_str (const s_vec_3& _vert, _pc_sz _p_format, CString& _out) {
		_vert; _p_format; _out;
		g_indent << _vert._x << _vert._y << _vert._z;

		_elem_to_str(_vert._x, _p_format, _out); _out += _T(" ");
		_elem_to_str(_vert._y, _p_format, _out); _out += _T(" ");
		_elem_to_str(_vert._z, _p_format, _out);

	}

}}} using namespace ::shared::parsers::_impl;

#pragma region cls::CPrint{}

CString CPrint::Face (const s_face& _face) {
	_face;
	static _pc_sz p_pair_pat = _T("% 2u/% 2u");
	CString cs_out (_T("face: "));
	CString cs_pair;
	for (uint32_t i_ = 0; i_ < _face._indices.size(); i_++) {

		cs_pair.Format(p_pair_pat, _face._indices.at(i_).first, _face._indices.at(i_).second);
		cs_out += cs_pair;
		if (i_ < _face._indices.size() - 1)
			cs_out += _T(" ");
	}

	return  cs_out;
}

CString CPrint::Norm (const normal_t& _norm) {
	_norm;
	static _pc_sz p_fmt_val = _T("%3.1f");

	CString cs_out(_T("vn: ")); _vert_to_str(_norm, p_fmt_val, cs_out);
	return  cs_out;
}

CString CPrint::Quad (const quad_t& _quad) {
	_quad;
	static _pc_sz p_fmt_val = _T("%10.6f");

	CString cs_out(_T("v: ")); _quad_to_str(_quad, p_fmt_val, cs_out);
	return  cs_out;
}

CString CPrint::Vert (const vertex_t& _vert) {
	_vert;
	static _pc_sz p_fmt_val = _T("%9.7f");

	CString cs_out(_T("v: ")); _vert_to_str(_vert, p_fmt_val, cs_out);
	return  cs_out;
}

void CPrint::Reset (void) {
	g_indent._digits = 0;
}

#pragma endregion

s_model& ::Get_model (void) {
	static s_model model;
	return   model;
}

namespace shared { namespace parsers { namespace obj {
}}}