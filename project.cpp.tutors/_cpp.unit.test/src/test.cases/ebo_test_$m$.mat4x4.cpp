/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 12:28:21.697, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix4x4 unit test adapter interface implementation file; 
*/
#include "ebo_test_$m$.mat4x4.h"
#include "test_case_$m$.mat3x3.h" // it is required for printing glm::mat4x4 after casting to glm::mat3x3;
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace _impl {

	// https://en.wikipedia.org/wiki/Prep >> preparatory; 
	class CPrep_4x4 {
	public:
		 CPrep_4x4 (void) = default; CPrep_4x4 (const CPrep_4x4&) = delete; CPrep_4x4 (CPrep_4x4&&) = delete;
		~CPrep_4x4 (void) = default;

		static
		void Do_it (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			c_rot_4x4 mat_4x4; mat_4x4.Prepare(s_rot_cri_t(_f_angle, _e_axis, true)); /*mat_4x4().Prepare(_f_angle, _e_axis);*/
#if (0) //	mat_4x4.Prepare() outputs all of this information;
			_out() += TString().Format(pc_sz_fmt_args, _f_angle, axes_t::To_str(_e_axis));
			_out() += TString().Format(_T("[impt] c_mat4x4 is prepared:"));
			c_mtx_4x4::To_str(mat_4x4(), false);
#endif
			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = c_axes::Get_axis(_e_axis);

			mat_glm = ::glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			t_mat4x4 mat_cpy = c_adapter() << mat_glm;

			_out() += TString().Format(_T("[impt] mat_glm_4x4 *after* rotation:"));
			c_mtx_4x4::To_str(mat_cpy, false);

			const float f_cmp_thresh = 0.0000003f;

			c_compare()(mat_cpy, mat_4x4()(), f_cmp_thresh);
		}

	private:
		CPrep_4x4& operator = (const CPrep_4x4&) = delete; CPrep_4x4& operator = (CPrep_4x4&&) = delete;
	};

	class CRot_4x4 {
	public:
		 CRot_4x4 (void) = default; CRot_4x4 (const CRot_4x4&) = delete; CRot_4x4 (CRot_4x4&&) = delete;
		~CRot_4x4 (void) = default;

		static
		void   Compare (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			vec_4 v_to_rot_0(1.0f, 1.0f, 1.0f, 1.0f); // is used by creating glm::vec4; 'w' element is set to 1.0f, because it is position;
			vec_4 v_to_rot_1(1.0f, 1.0f, 1.0f, 1.0f); // is used by creating math::vec_4; 'w' element is set to 1.0f, because it is position;

			CRot_4x4::Do_it(_f_angle, _e_axis, v_to_rot_0);     // uses GLM lib;
	//		c_rot_4x4()().Around_X(_f_angle, v_to_rot_1, true); // uses these tutorials' math lib; no direct call;
			c_rot_4x4().Do((s_rot_cri_v4() << _f_angle << _e_axis), v_to_rot_1); // uses math lib;

			const float f_cmp_thresh = 0.0000003f;

			c_compare()(v_to_rot_0, v_to_rot_1, f_cmp_thresh);
		}
		static
		vec_4& Do_it (const float _f_angle, const axes_t::e_axes _e_axis, vec_4& _to_rot) { // rotates input vector by using GLM lib;
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
	//		_out() += TString().Format(_T("[impt] mat_glm_3x3 *after* rotation:")); c_mtx_3x3::To_str(mat_cpy_3x3, false);

			_out() += TString().Format(_T("Input glm::vec4 *before*: %s;"), (_pc_sz) _to_rot.To_str());
			_to_rot.Set(v_res_glm.x, v_res_glm.y, v_res_glm.z, 1.0f);
			_out() += TString().Format(_T("Input glm::vec4 *after* : %s;"), (_pc_sz) _to_rot.To_str());

			return _to_rot;
		}

	private:
		CRot_4x4& operator = (const CRot_4x4&) = delete; CRot_4x4& operator = (CRot_4x4&&) = delete;
	};

	class CSeq_4x4 {
	public:
		 CSeq_4x4 (void) = default; CSeq_4x4 (const CSeq_4x4&) = delete; CSeq_4x4 (CSeq_4x4&&) = delete;
		~CSeq_4x4 (void) = default;

		static
		t_mat4x4  Do_it (const float _f_angle) {
			_f_angle;
			_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

			::glm::mat4x4 mat_glm_x(1.0f); mat_glm_x = ::glm::rotate(mat_glm_x, glm::radians(_f_angle), c_axes::Get_axis(axes_t::e_x_axis));
			::glm::mat4x4 mat_glm_y(1.0f); mat_glm_y = ::glm::rotate(mat_glm_y, glm::radians(_f_angle), c_axes::Get_axis(axes_t::e_y_axis));
			::glm::mat4x4 mat_glm_z(1.0f); mat_glm_z = ::glm::rotate(mat_glm_z, glm::radians(_f_angle), c_axes::Get_axis(axes_t::e_z_axis));

			::glm::mat4x4 mat_glm_res = mat_glm_z * mat_glm_y * mat_glm_x;

			static
			t_mat4x4 mat_res; mat_res = c_adapter() << mat_glm_res;

			_out() += _T("[impt] the result glm::mat4x4 is :");
			c_mtx_4x4::To_str(mat_res, false);

			return mat_res;
		}

	private:
		CSeq_4x4& operator = (const CSeq_4x4&) = delete; CSeq_4x4& operator = (CSeq_4x4&&) = delete;
	};
}}}}
using namespace ebo::boo::test::_impl;

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
#pragma region cls::c_rot_4x4{}

void c_t_rotate_4x4::Around_X (void) {
	float f_angle = -90.0f;
	CRot_4x4::Compare(f_angle, axes_t::e_x_axis);
	_out()();
}

void c_t_rotate_4x4::Around_Y (void) {
	float f_angle = 180.0f;
	CRot_4x4::Compare(f_angle, axes_t::e_y_axis);
	_out()();
}

void c_t_rotate_4x4::Around_Z (void) {
	float f_angle = -45.0f;
	CRot_4x4::Compare(f_angle, axes_t::e_z_axis);
	_out()();
}

void c_t_rotate_4x4::Prepare (void) {

	float f_angle = 90.0f;
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_x_axis);
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_y_axis);
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_z_axis);

	_out()();
}

void c_t_rotate_4x4::Sequence (void) {
	float f_angle = -90.0f;

	t_mat4x4 mat_res_0 = c_rot_4x4().Sequence(f_angle,  true);
	t_mat4x4 mat_res_1 = CSeq_4x4().Do_it(f_angle);

	const float f_cmp_thresh = 0.0000003f;

	c_compare()(mat_res_0, mat_res_1, f_cmp_thresh);

	_out()();
}

#pragma endregion