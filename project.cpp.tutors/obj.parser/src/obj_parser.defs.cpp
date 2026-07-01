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

s_face::s_face (void) : _vert_ndx{0}, _tex_ndx{0} {}

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

s_model::s_model (void) {}

#pragma endregion