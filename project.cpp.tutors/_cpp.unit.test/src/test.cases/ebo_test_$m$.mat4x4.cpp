/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 12:28:21.697, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix4x4 unit test adapter interface implementation file; 
*/
#include "ebo_test_$m$.mat4x4.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {

	// https://en.wikipedia.org/wiki/Prep >> preparatory; 
	class CPrep_4x4 {
	public:
		 CPrep_4x4 (void) = default; CPrep_4x4 (const CPrep_4x4&) = delete; CPrep_4x4 (CPrep_4x4&&) = delete;
		~CPrep_4x4 (void) = default;

		static
		void Do_it (const float _f_angle, const axes_t::e_axes _e_axis) {
			_f_angle; _e_axis;
			c_rot_4x4 mat_4x4; mat_4x4().Prepare(_f_angle, _e_axis);

			_out() += TString().Format(pc_sz_fmt_args, _f_angle, axes_t::To_str(_e_axis));
			_out() += TString().Format(_T("[impt] c_mat4x4 is prepared:"));
			c_mtx_4x4::To_str(mat_4x4(), false);

			::glm::mat4x4 mat_glm(1.0f); // creates the identity matrix;
			::glm::vec3 v_axis = CPrep_4x4::Get_axis(_e_axis);

			mat_glm = glm::rotate(mat_glm, glm::radians(_f_angle), v_axis); // rotates the matrix around given axis;

			t_mat4x4 mat_cpy = c_adapter() << mat_glm;

			_out() += TString().Format(_T("[impt] mat_glm_4x4 *after* rotation:"));
			c_mtx_4x4::To_str(mat_cpy, false);

			const float f_cmp_thresh = 0.0000003f;

			static _pc_sz pc_sz_pat_success = _T("[impt] result: glm::mat4x4 and c_mat4x4 are equal (compare threshold = %.7f);");
			static _pc_sz pc_sz_pat_failure = _T("[error] result: glm::mat4x4 and c_mat4x4 are *not* equal (compare threshold = %.7f);");

			if (c_comparator::Do_it(mat_cpy, mat_4x4()(), f_cmp_thresh))
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
		CPrep_4x4& operator = (const CPrep_4x4&) = delete; CPrep_4x4& operator = (CPrep_4x4&&) = delete;
	};
	class CRot_4x4 {
	public:
		 CRot_4x4 (void) = default; CRot_4x4 (const CRot_4x4&) = delete; CRot_4x4 (CRot_4x4&&) = delete;
		~CRot_4x4 (void) = default;
	};
}}}}}
using namespace ebo::boo::test::open_gl::_impl;

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
#if (0)
void c_t_rotate_4x4::Around_X (void) {
	// generates random-value-matrix;
	c_rot_4x4 this_rot; this_rot()() = c_mtx_4x4::Generate(-1.0f, +1.0f);
	c_rot_4x4 this_cpy; this_cpy()() = this_rot()(); // makes a copy of original matrix before its rotation;

	_out() += _T("[warn] c_rot_4x4 *before* rotation:");
	c_mtx_4x4::To_str(this_rot(), false);

	this_rot.Around_X(+90.0f); // rotate function outputs result matrix itself;
#if (0)
	c_rot_4x4 mat_rot_90; mat_rot_90()() = this_rot()(); // copies the matrix data after rotation to 90 degree angle;

	_out() += _T("[warn] c_rot_4x4 rotate the matrix back:");
	this_rot.Around_X(-90.0f);

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
#endif

void c_t_rotate_4x4::Prepare (void) {

	float f_angle = 90.0f;
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_x_axis);
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_y_axis);
	_impl::CPrep_4x4::Do_it(f_angle, axes_t::e_z_axis);

	_out()();
}

#pragma endregion