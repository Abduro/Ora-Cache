/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {

	// https://en.wikipedia.org/wiki/Prep >> preparatory; 
	class CPrep {
	public:
		 CPrep (void) = default; CPrep (const CPrep&) = delete; CPrep (CPrep&&) = delete;
		~CPrep (void) = default;

		static
		void Do_it (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			c_rot_3x3 mat_3x3; mat_3x3.Prepare(s_rot_cri_t(_f_angle, _e_axis, true));

			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = CPrep::Get_axis(_e_axis);

			mat_glm = glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			::glm::mat3x3 mat_glm_3x3 = mat_glm;
			t_mat3x3 mat_cpy = c_adapter() << mat_glm_3x3;

			_out() += TString().Format(_T("[impt] mat_glm_3x3 *after* rotation:"));
			c_mtx_3x3::To_str(mat_cpy, false);

			const float f_cmp_thresh = 0.0000003f;

			static _pc_sz pc_sz_pat_success = _T("[impt] result: glm::mat3x3 and c_mat3x3 are equal (compare threshold = %.7f);");
			static _pc_sz pc_sz_pat_failure = _T("[error] result: glm::mat3x3 and c_mat3x3 are *not* equal (compare threshold = %.7f);");

			if (c_comparator::Do_it(mat_cpy, mat_3x3()(), f_cmp_thresh))
				 _out() += TString().Format(pc_sz_pat_success, f_cmp_thresh);
			else _out() += TString().Format(pc_sz_pat_failure, f_cmp_thresh);
		}

		static ::glm::vec3 Get_axis (const axes_t::e_axes _e_axis) {
			_e_axis;
			switch (_e_axis) {
			case axes_t::e_x_axis: return ::glm::vec3(1.0f, 0.0f, 0.0f);
			case axes_t::e_y_axis: return ::glm::vec3(0.0f, 1.0f, 0.0f);
			case axes_t::e_z_axis: return ::glm::vec3(0.0f, 0.0f, 1.0f);
			default: return ::glm::vec3(0.0f, 0.0f, 0.0f);
			}
		}

	private:
		CPrep& operator = (const CPrep&) = delete; CPrep& operator = (CPrep&&) = delete;
	};

	static _pc_sz pc_sz_mat_equal = _T("[impt] result: matrices are equal;");
	static _pc_sz pc_sz_mat_diff  = _T("[error] result: matrices are *not* equal;");

	static _pc_sz pc_sz_vec_equal = _T("[impt] result: vectors are equal (compare threshold = %.7f);");
	static _pc_sz pc_sz_vec_diff  = _T("[error] result: vectors are *not* equal (compare threshold = %.7f);");

	class CRotator {
	public:
		 CRotator (void) = default; CRotator (const CRotator&) = delete; CRotator (CRotator&&) = delete;
		~CRotator (void) = default;

		static
		vec_3& Do_it (const float _f_angle, const axes_t::e_axes _e_axis, vec_3& _to_rot) { // rotates input vector by using GLM lib;
			_f_angle; _e_axis;
			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = CPrep::Get_axis(_e_axis);
			::glm::vec3 v_res_glm(_to_rot.x, _to_rot.y, _to_rot.z);

			mat_glm = glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			::glm::mat3x3 mat_glm_3x3 = mat_glm; // casts to matrix_3x3;
			v_res_glm = mat_glm_3x3 * v_res_glm; // applies the rotation matrix to the vector being rotated;

			s_rot_cri_t::To_str(_f_angle, _e_axis, true);

			t_mat3x3 mat_cpy_3x3 = c_adapter() << mat_glm_3x3;
			t_mat4x4 mat_cpy_4x4 = c_adapter() << mat_glm;

			_out() += TString().Format(_T("[impt] mat_glm_4x4 *after* rotation:")); c_mtx_4x4::To_str(mat_cpy_4x4, false);
			_out() += TString().Format(_T("[impt] mat_glm_3x3 *after* rotation:")); c_mtx_3x3::To_str(mat_cpy_3x3, false);

			_out() += TString().Format(_T("Input glm::vec_3 *before* : %s;"), (_pc_sz) _to_rot.To_str());
			_to_rot.Set(v_res_glm.x, v_res_glm.y, v_res_glm.z);
			_out() += TString().Format(_T("Input glm::vec_3 *after*  : %s;"), (_pc_sz) _to_rot.To_str());

			return _to_rot;
		}

	private:
		CRotator& operator = (const CRotator&) = delete; CRotator& operator = (CRotator&&) = delete;
	};

}}}}}
using namespace ebo::boo::test::open_gl::_impl;

#pragma region cls::c_mat_3x3{}

#pragma endregion
#pragma region cls::c_mat_4x4{}

void c_mat_4x4::Identity (void) {

	c_mtx_4x4 mat_this; mat_this.Identity();
	c_mtx_4x4 mat_glm(glm::mat4x4(1.f));

	_out() += _T("[warn] glm::mat4x4 identity:");
	c_mtx_4x4::To_str(mat_glm(), false);

	if (mat_this() == mat_glm())
	     _out() += pc_sz_mat_equal;
	else _out() += pc_sz_mat_diff;
	_out()();
}

void c_mat_4x4::Translate (void) {
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml ;
	c_mtx_4x4 mat_this; mat_this.Translate(c_tvec_3(0.0f, 0.1f, 0.0f)());
	c_mtx_4x4 mat_glm = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));

	_out() += _T("[warn] glm::mat4x4 translated:");
	c_mtx_4x4::To_str(mat_glm(), false);

	if (mat_this() == mat_glm())
	     _out() += pc_sz_mat_equal;
	else _out() += pc_sz_mat_diff;
	_out()();
}

void c_mat_4x4::Transpose (void) {

	c_mtx_4x4 mat_this; mat_this().Cols().Set(0, t_seq_4{0.0f, 1.0f, 2.0f, 3.0f});
	c_mtx_4x4 mat_copy; mat_copy() = mat_this(); // makes the transpose matrix copy;

	_out() += _T("[warn] The matrix *before* transpose:");
	c_mtx_4x4::To_str(mat_this(), false);

	mat_this().Transpose();
	c_mtx_4x4 mat_trans; mat_trans() = mat_this(); // makes a copy of the matrix transponed;

	_out() += _T("[warn] The matrix *after* transpose:");
	c_mtx_4x4::To_str(mat_this(), false);

	mat_this().Transpose(); // rolls back the transpose, i.e. restores the matrix to initial state;

	_out() += _T("[warn] The matrix *roll-back* transpose:");
	c_mtx_4x4::To_str(mat_this(), false);

	if (mat_this() == mat_copy())
	     _out() += _T("[impt] result: the matrix is restored;");
	else _out() += _T("[error] result: the matrix is not restored;");

	// glm::transpose() function flips the matrix along its main diagonal, effectively swapping rows and columns ;
	// https://stackoverflow.com/questions/40760841/how-are-glmvec3-and-glmmat4-initialised ;
	glm::mat4x4 mat_glm(0.0f); mat_glm[0] = glm::vec4(0.0f, 1.0f, 2.0f, 3.0f);

	_out() += _T("[warn] The glm::matrix *before* transpose:");
	c_mtx_4x4::To_str(c_mtx_4x4(mat_glm)(), false);

	glm::mat4x4 mat_glm_trans = ::glm::transpose(mat_glm);
	_out() += _T("[warn] The glm::matrix *after* transpose:");
	c_mtx_4x4::To_str(c_mtx_4x4(mat_glm_trans)(), false);

	if (mat_trans() == c_mtx_4x4(mat_glm_trans)())
	     _out() += _T("[impt] result: the transposed matrices 'glm::mat' and 'math::c_mat4x4' are equal;");
	else _out() += _T("[error] result: the transposed matrices 'glm::mat' and 'math::c_mat4x4' are *not* equal;");

	_out()();
}

#pragma endregion
#pragma region cls::c_rot_3x3{}
#if (0)

void      c_rot_3x3::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);

	c_tvec_3 x_axis(1.0f, 0.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("x"), (_pc_sz) x_axis().To_str());

		this->ref().Do(f_angels[i_], x_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		_out() +=  c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_y (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);
	c_tvec_3 y_axis(0.0f, 1.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("y"), (_pc_sz) y_axis().To_str());

		this->ref().Do(f_angels[i_], y_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_z (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);
	c_tvec_3 z_axis(0.0f, 0.0f, 1.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("z"), (_pc_sz) z_axis().To_str());

		this->ref().Do(f_angels[i_], z_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

CString   c_rot_3x3::To_str (void) const {
	CString cs_out = c_mtx_3x3().To_str(this->ref(), this->m_b_verb); if (this->m_b_verb) _out()();
	return  cs_out;
}
#endif
#pragma endregion
#pragma region cls::c_t_rotate_2x2{}

void c_t_rotate_2x2::Matrix (void) {

	t_mat2x2 m_2_rot({0.5f, 0.5f, 0.5f, 0.5f});
	c_rot_2x2 m_mat_rot;

	c_rot_2x2().Rotate(90.0f, m_2_rot);
	
	_out()();
}

void c_t_rotate_2x2::Pivot (void) {
	/*steps:
	(1) create the target vector with the target point on X-axis (x=1.0f;y=0.0f);
	(2) create the pivot point vector in axes origin (x=0.0f;y=0.0f);
	(3) prepare the rotate matrix;
	(4) rotate the target with taking into account the pivot point; 
	*/
	// the 1st test case with pivot point at orign of the axes;
	// expected result: no change for position of rotated vector;
	// (1),(2):
	vec_2  v_2_rot({1.0f, 0.0f}); // on X-axis;
	vec_2  v_pivot({0.0f, 0.0f}); // at the origin;

	// (3),(4):
	const float f_angle = 90.0f;
	c_rot_2x2 m_rot_2x2; m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	// the 2nd test case with pivot point located at *not* the axes origin; 
	// expected result: rotated vector will be moved in accordance with pivot point;
	v_2_rot.Set(1.0f, 0.0f);
	v_pivot.Set(0.0f, 1.0f);

	m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	// the 3rd test case with pivot point located at *not* the axes origin; 
	v_2_rot.Set(1.0f, 0.0f);
	v_pivot.Set(1.0f, 1.0f);

	m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	_out()();
}

void c_t_rotate_2x2::Prepare (void) {

	c_rot_2x2().Prepare(+90.0f);
	c_rot_2x2().Prepare(-90.0f);
	_out()();
}

void c_t_rotate_2x2::Vector (void) {
	/*steps:
	(1) creating the vector with the target point on X-axis (x=1.0f;y=0.0f);
	(2) preparing the rotate matrix for 90 degree angle;
	(3) to get the expected result: x~=0.0f;y=1.0f; for better accuracy of the result values it seems using the comparison with epsilon is required;
	*/
	vec_2  v_2_rot({1.0f, 0.0f});
	c_rot_2x2 m_mat_rot;

	c_rot_2x2().Rotate(+90.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f); // restores the initial values;
	c_rot_2x2().Rotate(-90.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f); // expected result is: x=0.0f;y=-1.0f;
#if (0)
	c_rot_2x2().Rotate(+60.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f);
	/* how to get the sin() and cos() specific value;
	   the angle equals to asinf(val) and acosf(val), where val is required value of the sinf() or cosf(); it gives different angles;
	*/
	const float f_angle_cos = ::acosf(0.5f) * ::defs::rad_2_deg; f_angle_cos;
	const float f_angle_sin = ::asinf(0.5f) * ::defs::rad_2_deg; f_angle_sin;
#endif
	v_2_rot.Set(1.0f, 1.0f); CError error(__CLASS__, __METHOD__, __s_ok);        // sets values for getting the angle that is required for these values;
	const float f_req = v_2_rot.Get_angle(true, error); v_2_rot.Set(1.0f, 0.0f); // restores origin values;

	if (error) {_out() += error; _out()(); return; }
	c_rot_2x2().Rotate(f_req, v_2_rot, true);

	if (::defs::f_epsilon > ::abs(v_2_rot.x - v_2_rot.y)) // checks for valid result: x & y must have the same value for the angle 45;
	_out() += TString().Format(_T("The result is confirmed: x (%.7f) ~= y (%.7f)"), v_2_rot.x, v_2_rot.y); 
	else // equality of x and y coordinates by value (not sign) is available for the following angles only: 45, 135, 225, 315 counter clockwise;
	_out() += TString().Format(_T("[error] The result is not confirmed: x(%.7f) != y(%.7f);"), v_2_rot.x, v_2_rot.y);
	_out()();
}

#pragma endregion
#pragma region cls::c_t_rotate_3x3{}

void c_t_rotate_3x3::Pivot (void) {

	vec_2 v_2_rot(1.0f, 0.0f);
	vec_2 v_point(1.0f, 1.0f); // pivot point is set through ctor of s_rot_cri_v2({1.0f, 1.0f}, true);

	c_rot_3x3().Rotate((s_rot_cri_v2({1.0f, 1.0f}, true) << 90.0f << axes_t::e_z_axis), v_2_rot);

	_out()();
}

void c_t_rotate_3x3::Point (void) {

	vec_2 v_2_rot(1.0f, 0.0f);

	c_rot_3x3().Rotate((s_rot_cri_v2() << 90.0f << axes_t::e_z_axis), v_2_rot); // pivot point is set to axes'origin (0,0) and does not affect the rotation;

	_out()();
}

void c_t_rotate_3x3::Prepare (void) {

//	c_rot_3x3().Prepare(f_angle); f_angle = -90.0f;
//	c_rot_3x3().Prepare(f_angle); f_angle =  90.0f;

	float f_angle = 90.0f;
	_impl::CPrep::Do_it(f_angle, axes_t::e_x_axis);
	_impl::CPrep::Do_it(f_angle, axes_t::e_y_axis);
	_impl::CPrep::Do_it(f_angle, axes_t::e_z_axis);

	_out()();
}

void c_t_rotate_3x3::Vector (void) {

	float f_angle = 90.0f;

	vec_3 v_to_rot_0(1.0f, 1.0f, 1.0f);
	vec_3 v_to_rot_1(1.0f, 1.0f, 1.0f);

	_impl::CRotator::Do_it(f_angle, axes_t::e_x_axis, v_to_rot_0);                   // uses GLM lib;
	c_rot_3x3().Rotate((s_rot_cri_v3() << f_angle << axes_t::e_x_axis), v_to_rot_1); // uses math lib;

	const float f_cmp_thresh = 0.0000003f;

	if (c_comparator::Do_it(v_to_rot_0, v_to_rot_1 , f_cmp_thresh))
		 _out() += TString().Format(pc_sz_vec_equal, f_cmp_thresh);
	else _out() += TString().Format(pc_sz_vec_diff , f_cmp_thresh);

	_out()();
}

#pragma endregion
#pragma region cls::c_rot_4x4{}
#if (0)
void c_rot_4x4::Rotate_free (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->Set();

	c_tvec_3 axis(0.5f, 0.5f, 0.5f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; axis = %s");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], (_pc_sz) axis().To_str() );

		this->ref().Do(f_angels[i_], axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_x(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_y (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_y(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_z (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_z(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Set (void) {

	c_tvec_4
	col_0(0.0f, 0.1f, 0.2f, 1.0f),
	col_1(0.4f, 0.5f, 0.6f, 1.0f),
	col_2(0.7f, 0.8f, 0.9f, 1.0f),
	col_3(0.5f, 0.5f, 0.5f, 1.0f);

	_out() += TString().Format(_T("col_#_0: %s"), (_pc_sz) col_0().To_str());
	_out() += TString().Format(_T("col_#_1: %s"), (_pc_sz) col_1().To_str());
	_out() += TString().Format(_T("col_#_2: %s"), (_pc_sz) col_2().To_str());
	_out() += TString().Format(_T("col_#_3: %s"), (_pc_sz) col_3().To_str());

	this->ref().Cols().Set(col_0.ref(), col_1.ref(), col_2.ref(), col_3.ref());

	_out() += _T("the matrix *after* setting data:");
	c_mtx_4x4().To_str(this->ref(), true);

	_out()();
}

CString   c_rot_4x4::To_str (void) const {
	CString cs_out = c_mtx_4x4().To_str(this->ref(), true); _out()();
	return  cs_out;
}
#endif

void c_t_rotate_4x4::On_X (void) {
	// generates random-value-matrix;
	c_rot_4x4 this_rot; this_rot()() = c_mtx_4x4::Generate(-1.0f, +1.0f);
	c_rot_4x4 this_cpy; this_cpy()() = this_rot()(); // makes a copy of original matrix before its rotation;

	_out() += _T("[warn] c_rot_4x4 *before* rotation:");
	c_mtx_4x4::To_str(this_rot(), false);

	this_rot.On_X(+90.0f); // rotate function outputs result matrix itself;
#if (0)
	c_rot_4x4 mat_rot_90; mat_rot_90()() = this_rot()(); // copies the matrix data after rotation to 90 degree angle;

	_out() += _T("[warn] c_rot_4x4 rotate the matrix back:");
	this_rot.On_X(-90.0f);

	if (this_rot()() == this_cpy()())
	     _out() += _T("[impt] result: the matrix data is set to initial values;");
	else _out() += _T("[error] result: the matrix data is not set to initial values;");
#endif
//	::glm::mat2x2 mat_glm_2(0.0f); mat_glm_2 =::glm::rotate(mat_glm_2, glm::radians(+90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	::glm::mat4x4 mat_glm(0.0f);

	c_adapter() << this_cpy()() >> mat_glm;

	mat_glm = glm::rotate(mat_glm, glm::radians(+90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_out() += _T("[warn] glm::mat4x4 after rotation:");

	c_adapter() << this_cpy()() << mat_glm;  // copies data from glm::mat4x4 to data copy matrix in order to compare the result of rotation of both matrices;
	c_mtx_4x4::To_str(this_cpy()(), false);

	if (this_rot()() == this_cpy()())
	     _out() += _T("[impt] result: glm::mat4x4 and c_mat4x4 are equal after rotation;");
	else _out() += _T("[error] result: glm::mat4x4 and c_mat4x4 are *not* equal after rotation;");

	_out()();
}

#pragma endregion