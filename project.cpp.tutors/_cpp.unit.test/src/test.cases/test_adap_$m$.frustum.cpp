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