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

s_model::s_model (void) { this->_objects.push_back(s_draw_obj()); }

#pragma endregion

s_model& ::Get_model (void) {
	static s_model model;
	return   model;
}

namespace shared { namespace parsers { namespace obj {

CString To_str (const s_face& _face) {
	_face;
	static _pc_sz p_pair_pat = _T("%u/%u");
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

CString To_str (const normal_t& _norm) {
	_norm;
	static _pc_sz p_fmt_val = _T("%3.1f");

	CString cs_out(_T("vn: "));
	CString cs_val;
	
	cs_out += _T(" "); cs_val = TString().Float(_norm._x, t_fmt_spec::e_decimal, p_fmt_val); if (_T('-') == cs_val.Left(1)) {} else cs_out += _T(" "); cs_out += cs_val;
	cs_out += _T(" "); cs_val = TString().Float(_norm._y, t_fmt_spec::e_decimal, p_fmt_val); if (_T('-') == cs_val.Left(1)) {} else cs_out += _T(" "); cs_out += cs_val;
	cs_out += _T(" "); cs_val = TString().Float(_norm._z, t_fmt_spec::e_decimal, p_fmt_val); if (_T('-') == cs_val.Left(1)) {} else cs_out += _T(" "); cs_out += cs_val;
	
	return  cs_out;
}

}}}