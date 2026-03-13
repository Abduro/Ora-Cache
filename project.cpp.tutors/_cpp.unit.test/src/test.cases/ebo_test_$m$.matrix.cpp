/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {}}}}}

#pragma region cls::c_mat_3x3{}

#pragma endregion
#pragma region cls::c_mat_4x4{}

void c_mat_4x4::Identity (void) {

	c_mtx_4x4 mat_this; mat_this.Identity();
	c_mtx_4x4 mat_glm(glm::mat4x4(1.f));

	_out() += _T("[warn] glm::mat4x4 identity:");
	c_mtx_4x4::To_str(mat_glm(), false);

	if (mat_this() == mat_glm())
	     _out() += _T("[impt] result: matrices are equal;");
	else _out() += _T("[error] result: matrices are not equal;");
	_out()();
}

void c_mat_4x4::Translate (void) {
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml ;
	c_mtx_4x4 mat_this; mat_this.Translate(c_tvec_3(0.0f, 0.1f, 0.0f)());
	c_mtx_4x4 mat_glm = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));

	_out() += _T("[warn] glm::mat4x4 translated:");
	c_mtx_4x4::To_str(mat_glm(), false);

	if (mat_this() == mat_glm())
	     _out() += _T("[impt] result: matrices are equal;");
	else _out() += _T("[error] result: matrices are not equal;");
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
c_rot_3x3::c_rot_3x3 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_rot_3x3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->To_str();
}

const
t_rot3x3& c_rot_3x3::ref (void) const { return this->m_rot3x3; }
t_rot3x3& c_rot_3x3::ref (void)       { return this->m_rot3x3; }

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

void c_t_rotate_3x3::Prepare (void) {

	c_rot_3x3().Prepare(+90.0f);
	c_rot_3x3().Prepare(-90.0f);
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

	c_ada_4x4(this_cpy()()) >> mat_glm;

	mat_glm = glm::rotate(mat_glm, glm::radians(+90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_out() += _T("[warn] glm::mat4x4 after rotation:");

	c_ada_4x4(this_cpy()()) << mat_glm;  // copies data from glm::mat4x4 to data copy matrix in order to compare the result of rotation of both matrices;
	c_mtx_4x4::To_str(this_cpy()(), false);

	if (this_rot()() == this_cpy()())
	     _out() += _T("[impt] result: glm::mat4x4 and c_mat4x4 are equal after rotation;");
	else _out() += _T("[error] result: glm::mat4x4 and c_mat4x4 are *not* equal after rotation;");

	_out()();
}

#pragma endregion
#pragma region cls::c_stk_current{}

c_stk_current::c_stk_current (void) {}

void c_stk_current::Get (void) { c_stk_target().Get(); _out()();  }
void c_stk_current::Set (void) { c_stk_target().Set(e_mat_type::e_undef); _out()(); }

#pragma endregion
#pragma region cls::c_mat_stack{}

c_mat_stack::c_mat_stack (void) {}

void c_mat_stack::Get (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_mtx_4x4 mat_4; mat_4().Cell(0,1) = 0.1f;
	c_mtx_stack stack;

	_out() += TString().Format(_T("The metrix *before* pushing to stack:\n%s"), (_pc_sz)c_mtx_4x4::To_str(mat_4(), false));

	if (__failed(stack.Push(mat_4(), c_stk_target()().Get()))) { _out()(); return; }
	if (__failed(stack.Get(e_mat_type::e_modelview, mat_4()))) { _out()(); return; }

	_out() += TString().Format(_T("The metrix *after* pushing to stack:\n%s"), (_pc_sz)c_mtx_4x4::To_str(mat_4(), false));

	_out()();
}

void c_mat_stack::Pop (void) {
	c_mtx_stack().Pop(); _out()();
}

void c_mat_stack::Push (void) {

	c_mtx_stack stack;

	if (__failed(stack.Push(t_mat4x4(), /*e_mat_type::e_undef*/ c_stk_target()().Get()))) {} else stack.Pop(); _out()();
}

#pragma endregion