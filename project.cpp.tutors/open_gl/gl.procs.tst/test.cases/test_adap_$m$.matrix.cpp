/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 13:02:17.371, UTC+4, Batumi, Friday;
	This is OpenGL version 1.1 matrix wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$m$.matrix.h"

using namespace test::open_gl::ver_1_1;

#pragma region cls::c_matrix{}

void c_matrix::Get (void) {
	_out()();
}

void c_matrix::To_self (void) {
	_out()();
}

#pragma endregion
#pragma region cls::c_opers{}

void c_opers::Multiply (void) {

	// this is the 1D plain array of floats and is displayed as row-major matrix, but in fact this is column-major matrix data;
	const f_mat_4x4 mat_data = {
		0.00f, 0.01f, 0.02f, 0.03f,
		0.04f, 0.05f, 0.06f, 0.07f,
		0.08f, 0.09f, 0.10f, 0.11f,
		0.12f, 0.13f, 0.14f, 0.15f,
	};

	CTstMatrix matrix(true);
	CTstMode   stk_mode(false);
	CTstOpers  opers(true);

	// step #1 sets current matrix stack to projection mode;
	if (__failed(stk_mode.Set(e_stk_mode::e_project))) { _out()(); return; }

	// step #2 multiply the current matrix;
	if (__failed(opers.Multiply(mat_data))) {}
	else if (__failed(matrix.Get(e_mat_type::e_project))) {}

	// step #3 returns back the modelview mode;
	if (__failed(stk_mode.Set(e_stk_mode::e_modelview))){}

	_out()();
}

#pragma endregion