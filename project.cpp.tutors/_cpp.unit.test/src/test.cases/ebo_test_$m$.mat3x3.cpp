/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 11:57:58.721, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix3x3 unit test adapter interface implementation file; 
*/
#include "ebo_test_$m$.mat3x3.h"
#include "test_case_$m$.mat4x4.h" // it is required for printing glm::mat4x4 before casting to glm::mat3x3;

#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {

	// https://en.wikipedia.org/wiki/Prep >> preparatory; 
	class CPrep_3x3 {
	public:
		 CPrep_3x3 (void) = default; CPrep_3x3 (const CPrep_3x3&) = delete; CPrep_3x3 (CPrep_3x3&&) = delete;
		~CPrep_3x3 (void) = default;

		static
		void Do_it (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			c_rot_3x3 mat_3x3; mat_3x3.Prepare(s_rot_cri_t(_f_angle, _e_axis, true));

			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = c_axes::Get_axis(_e_axis);

			mat_glm = glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			::glm::mat3x3 mat_glm_3x3 = mat_glm;
			t_mat3x3 mat_cpy = c_adapter() << mat_glm_3x3;

			_out() += TString().Format(_T("[impt] mat_glm_3x3 *after* rotation:"));
			c_mtx_3x3::To_str(mat_cpy, false);

			const float f_cmp_thresh = 0.0000003f;

			c_compare()(mat_cpy, mat_3x3()(), f_cmp_thresh);
		}

	private:
		CPrep_3x3& operator = (const CPrep_3x3&) = delete; CPrep_3x3& operator = (CPrep_3x3&&) = delete;
	};

	class CRot_3x3 {
	public:
		 CRot_3x3 (void) = default; CRot_3x3 (const CRot_3x3&) = delete; CRot_3x3 (CRot_3x3&&) = delete;
		~CRot_3x3 (void) = default;

		static
		void   Compare (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			vec_3 v_to_rot_0(1.0f, 1.0f, 1.0f); // is used by creating glm::vec3;
			vec_3 v_to_rot_1(1.0f, 1.0f, 1.0f); // is used by creating math::vec_3;

			CRot_3x3::Do_it(_f_angle, _e_axis, v_to_rot_0);                      // uses GLM lib;
			c_rot_3x3().Do((s_rot_cri_v3() << _f_angle << _e_axis), v_to_rot_1); // uses math lib;

			const float f_cmp_thresh = 0.0000003f;

			c_compare()(v_to_rot_0, v_to_rot_1, f_cmp_thresh);
		}

		static
		vec_3& Do_it (const float _f_angle, const axes_t::e_axes _e_axis, vec_3& _to_rot) { // rotates input vector by using GLM lib;
			_f_angle; _e_axis; _to_rot;
			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = c_axes::Get_axis(_e_axis);
			::glm::vec3 v_res_glm(_to_rot.x, _to_rot.y, _to_rot.z); // this is the vector being rotated, i.e. the transformed or result vector;

			mat_glm = glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			::glm::mat3x3 mat_glm_3x3 = mat_glm; // casts to matrix_3x3;
			v_res_glm = mat_glm_3x3 * v_res_glm; // applies the rotation matrix to the vector being rotated;

			s_rot_cri_t::To_str(_f_angle, _e_axis, true);

			t_mat3x3 mat_cpy_3x3 = c_adapter() << mat_glm_3x3;
			t_mat4x4 mat_cpy_4x4 = c_adapter() << mat_glm;

			_out() += TString().Format(_T("[impt] mat_glm_4x4 *after* rotation:")); c_mtx_4x4::To_str(mat_cpy_4x4, false);
			_out() += TString().Format(_T("[impt] mat_glm_3x3 *after* rotation:")); c_mtx_3x3::To_str(mat_cpy_3x3, false);

			_out() += TString().Format(_T("Input glm::vec3 *before*: %s;"), (_pc_sz) _to_rot.To_str());
			_to_rot.Set(v_res_glm.x, v_res_glm.y, v_res_glm.z);
			_out() += TString().Format(_T("Input glm::vec3 *after* : %s;"), (_pc_sz) _to_rot.To_str());

			return _to_rot;
		}

	private:
		CRot_3x3& operator = (const CRot_3x3&) = delete; CRot_3x3& operator = (CRot_3x3&&) = delete;
	};

}}}}}
using namespace ebo::boo::test::open_gl::_impl;

#pragma region cls::c_t_rotate_3x3{}

void c_t_rotate_3x3::Around_X (void) {
	float f_angle = -90.0f;
	CRot_3x3::Compare(f_angle, axes_t::e_x_axis);
	_out()();
}

void c_t_rotate_3x3::Around_Y (void) {
	float f_angle = -90.0f;
	CRot_3x3::Compare(f_angle, axes_t::e_y_axis);
	_out()();
}

void c_t_rotate_3x3::Around_Z (void) {
	float f_angle = -90.0f;
	CRot_3x3::Compare(f_angle, axes_t::e_z_axis);
	_out()();
}

void c_t_rotate_3x3::Pivot (void) {

	vec_2 v_2_rot(1.0f, 0.0f);
	vec_2 v_point(1.0f, 1.0f); // pivot point is set through ctor of s_rot_cri_v2({1.0f, 1.0f}, true);

	c_rot_3x3().Do((s_rot_cri_v2({1.0f, 1.0f}, true) << 90.0f << axes_t::e_z_axis), v_2_rot);

	_out()();
}

void c_t_rotate_3x3::Point (void) {

	vec_2 v_2_rot(1.0f, 0.0f);

	c_rot_3x3().Do((s_rot_cri_v2() << 90.0f << axes_t::e_z_axis), v_2_rot); // pivot point is set to axes'origin (0,0) and does not affect the rotation;

	_out()();
}

void c_t_rotate_3x3::Prepare (void) {

//	c_rot_3x3().Prepare(f_angle); f_angle = -90.0f;
//	c_rot_3x3().Prepare(f_angle); f_angle =  90.0f;

	float f_angle = 90.0f;
	_impl::CPrep_3x3::Do_it(f_angle, axes_t::e_x_axis);
	_impl::CPrep_3x3::Do_it(f_angle, axes_t::e_y_axis);
	_impl::CPrep_3x3::Do_it(f_angle, axes_t::e_z_axis);

	_out()();
}

#pragma endregion