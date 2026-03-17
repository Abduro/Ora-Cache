/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 10:54:23.202, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 4x4 rotation interface implementation file;
*/
#include "math.rot.4x4.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region cls::c_rotate_4x4{}

c_rotate_4x4::c_rotate_4x4 (const bool _b_identity/* = true*/) : c_mat4x4(_b_identity) {}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad); const float cos_1 = 1.0f - cos_;

	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 1), (*this)()(0, 2)}, // col_#_1: x, y, z; w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 1), (*this)()(1, 2)}, // col_#_2: x, y, z; w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 1), (*this)()(2, 2)}, // col_#_3: x, y, z; w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 1), (*this)()(3, 2)}; // col_#_4: x, y, z; w:f excluded;

	c_rotate_3x3 rot(_f_angle, _x, _y, _z);

	// multiplies view matrix by rotation matrix;
	/* cols:     1st                              2nd                              3rd                              4th
	rows: x 1st  0 = r0 * 0' + r4 * 1' + r8 * 2'  4 = r0 * 4' + r4 * 5' + r8 * 6'  8 = r0 * 8' + r4 * 9' + r8 * a'  c = r0 * c' + r4 * d' + r8 * e'
	      y 2nd  1 = r1 * 0' + r5 * 1' + r9 * 2'  5 = r1 * 4' + r5 * 5' + r9 * 6'  9 = r1 * 8' + r5 * 9' + r9 * a'  d = r1 * c' + r5 * d' + r9 * e'
	      z 3rd  2 = r2 * 0' + r6 * 1' + ra * 2'  6 = r2 * 4' + r6 * 5' + ra * 6'  a = r2 * 8' + r6 * 9' + ra * a'  e = r2 * c' + r6 * d' + ra * e'
	      w : excluded;
	*/
	// col_#_1
	(*this)()(0, 0) = rot()(0, 0) * col_0._x + rot()(1, 0) * col_0._y + rot()(2, 0) * col_0._z;  // 0 = 1st row of rotate matrix [0|4|8] * 1st col of the view matrix [0|1|2];
	(*this)()(0, 1) = rot()(0, 1) * col_0._x + rot()(1, 1) * col_0._y + rot()(2, 1) * col_0._z;  // 1 = 2nd row of rotate matrix [1|5|9] * 1st col of the view matrix [0|1|2];
	(*this)()(0, 2) = rot()(0, 2) * col_0._x + rot()(1, 2) * col_0._y + rot()(2, 2) * col_0._z;  // 2 = 3rd row of rotate matrix [2|6|a] * 1st col of the view matrix [0|1|2];
	// col_#_2
	(*this)()(1, 0) = rot()(0, 0) * col_1._x + rot()(1, 0) * col_1._y + rot()(2, 0) * col_1._z;  // 4 = 1st row of rotate matrix [0|4|8] * 2nd col of the view matrix [4|5|6];
	(*this)()(1, 1) = rot()(0, 1) * col_1._x + rot()(1, 1) * col_1._y + rot()(2, 1) * col_1._z;  // 5 = 2nd row of rotate matrix [1|5|9] * 2nd col of the view matrix [4|5|6];
	(*this)()(1, 2) = rot()(0, 2) * col_1._x + rot()(1, 2) * col_1._y + rot()(2, 2) * col_1._z;  // 6 = 3rd row of rotate matrix [2|6|a] * 2nd col of the view matrix [4|5|6];
	// col_#_3
	(*this)()(2, 0) = rot()(0, 0) * col_2._x + rot()(1, 0) * col_2._y + rot()(2, 0) * col_2._z;  // 8 = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [8|9|a];
	(*this)()(2, 1) = rot()(0, 1) * col_2._x + rot()(1, 1) * col_2._y + rot()(2, 1) * col_2._z;  // 9 = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [8|9|a];
	(*this)()(2, 2) = rot()(0, 2) * col_2._x + rot()(1, 2) * col_2._y + rot()(2, 2) * col_2._z;  // a = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [8|9|a];
	// col_#_4
	(*this)()(3, 0) = rot()(0, 0) * col_3._x + rot()(1, 0) * col_3._y + rot()(2, 0) * col_3._z;  // c = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [c|d|e];
	(*this)()(3, 1) = rot()(0, 1) * col_3._x + rot()(1, 1) * col_3._y + rot()(2, 1) * col_3._z;  // d = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [c|d|e];
	(*this)()(3, 2) = rot()(0, 2) * col_3._x + rot()(1, 2) * col_3._y + rot()(2, 2) * col_3._z;  // e = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [c|d|e];

	return (*this)();
}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const vec_3& _coords) { return this->Do(_f_angle, _coords.x, _coords.y, _coords.z); }

vec_4&    c_rotate_4x4::Do (const float _f_angle, vec_4& _to_rot, const axes_t::e_axes _e_axis, const bool _b_use_eps/* = false*/) {
	_f_angle; _to_rot; _e_axis; _b_use_eps;
	/* (1) prepares this matrix for rotation around given axis; */
	this->Prepare(_f_angle, _e_axis);
	// (2) calculates the target vector values: x,y and z, w element does not participate actually;
	(*this)().Mltply(_to_rot);
	if (_b_use_eps) { _to_rot.Round(); /*uses default threashold: defs::f_epsilon;*/ }
	return _to_rot;
}

vec_3 c_rotate_4x4::Get_angle (void) const {
	return c_rotate_3x3(c_mat3x3(
		{(*this)()(0, 0),(*this)()(0, 1),(*this)()(0, 2)},
		{(*this)()(1, 0),(*this)()(1, 1),(*this)()(1, 2)},
		{(*this)()(2, 0),(*this)()(2, 1),(*this)()(2, 2)})
	).Get_angle();
}

vec_4& c_rotate_4x4::Around_X (const float _f_angle, vec_4& _to_rot, const bool _b_use_eps) { return this->Do(_f_angle, _to_rot, axes_t::e_x_axis, _b_use_eps); }
vec_4& c_rotate_4x4::Around_Y (const float _f_angle, vec_4& _to_rot, const bool _b_use_eps) { return this->Do(_f_angle, _to_rot, axes_t::e_y_axis, _b_use_eps); }
vec_4& c_rotate_4x4::Around_Z (const float _f_angle, vec_4& _to_rot, const bool _b_use_eps) { return this->Do(_f_angle, _to_rot, axes_t::e_z_axis, _b_use_eps); }

c_mat4x4& c_rotate_4x4::Prepare (const float _f_angle, const axes_t::e_axes _e_axis) {
	_f_angle; _e_axis;
	/* creates the rotation matrix: it is done by creating rotation sub-matrix 3x3;
	*/
	c_rotate_3x3 mat_3x3; mat_3x3.Prepare(_f_angle, _e_axis);
	(*this)().Identity();

	if (false) {}
	else if (axes_t::e_x_axis == _e_axis) {
	/*      mat_2x2           mat_3x3        this mat_4x4
	cols:   #0      #1        #0  #1  #2     #0  #1  #2  #3
	rows:#0 cos(a) -sin(a)     1   0   0     m3  m3  m3   0
	     #1 sin(a)  cos(a) >>  0  m2  m2  >> m3  m3  m3   0
	     #2                    0  m2  m2     m3  m3  m3   0
	     #3                                   0   0   0   1
		 *notes*:
	       (1) matrix_2x2 is applied to bottom-right corner of the matrix_3x3;
	       (2) matrix 3x3 is applied to top-left corner of this matrix;
	*/
	(*this)() << mat_3x3;
	}
	else if (axes_t::e_y_axis == _e_axis) {
	/*      mat_2x2           mat_3x3        this mat_4x4
	cols:   #0      #1        #0  #1  #2     #0  #1  #2  #3
	rows:#0 cos(a) -sin(a)    m2   0  m2     m3  m3  m3   0
	     #1 sin(a)  cos(a) >>  0   1   0  >> m3  m3  m3   0
	     #2                   m2   0  m2     m3  m3  m3   0
	     #3                                   0   0   0   1
	     *notes*:
	       (1) matrix_2x2 is torn at all corners;
	       (2) the matrix_2x2 is inverted along the main diagonal;
	*/
	(*this)() << mat_3x3;
	}
	else if (axes_t::e_z_axis == _e_axis) {
	/*      mat_2x2           mat_3x3        this mat_4x4
	cols:   #0      #1        #0  #1  #2     #0  #1  #2  #3
	rows:#0 cos(a) -sin(a) >> m2  m2   0     m3  m3  m3   0
	     #1 sin(a)  cos(a)    m2  m2   0  >> m3  m3  m3   0
	     #2                    0   0   1     m3  m3  m3   0
         #3                                   0   0   0   1
	     *notes*:
	       (1) matrix_2x2 is applied to top-left corner;
	*/
	(*this)() << mat_3x3;
	}
	else {
		__trace_err_ex_2(CError(__CLASS__, __METHOD__, __e_inv_arg) = TString().Format(_T("#__e_inv_arg: %04u"), (uint32_t)_e_axis));
	}

	return (*this)();
}

const
c_mat4x4& c_rotate_4x4::operator ()(void) const { return (c_rotate_4x4&)*this; }
c_mat4x4& c_rotate_4x4::operator ()(void)       { return (c_rotate_4x4&)*this; }

#pragma endregion