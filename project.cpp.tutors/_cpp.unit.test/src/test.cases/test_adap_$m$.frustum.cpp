/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:19:08.531, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum unit test adapter interface implementation file; 
*/
#include "test_adap_$m$.frustum.h"

using namespace test::open_gl::frustum;

#pragma region cls::c_frustum{}

void c_frustum::Get_perspect (void) {

	CTstFrustum().Update();
	_out()();
}

void c_frustum::Set_aspect (void) {

	CTstAspect(true).Set(480, 640);
	_out()();
}

void c_frustum::Set_defaults (void) {

	CTstCfg(true).Set_defaults();
	_out()();
}

#pragma endregion
#pragma region cls::c_project{}

using CTstPerspect = test::open_gl::ver_1_1::CTstPerspect;

void c_project::Get (void) {

	CTstPerspect(true).Get();
	_out()();
}

void c_project::Set (void) {

	using namespace test::open_gl::ver_1_1;

	CTstPerspect(true).Set(g_pers_arg);
	_out()();
}

#pragma endregion
#pragma region cls::c_stk_mode{}

using CTstMatMode = test::open_gl::ver_1_1::CTstMatMode;
using e_stk_modes = test::open_gl::ver_1_1::e_stk_modes;

void c_stk_mode::Get (void) {

	CTstMatMode(true).Get();
	_out()();
}

void c_stk_mode::Set (void) {

	CTstMatMode(true).Set(e_stk_modes::e_project);
	_out()();
}

#pragma endregion