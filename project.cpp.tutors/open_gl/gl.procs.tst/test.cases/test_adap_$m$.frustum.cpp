/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:19:08.531, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum unit test adapter interface implementation file; 
*/
#include "test_adap_$m$.frustum.h"

using namespace test::open_gl::frustum;

#pragma region cls::c_frustum{}

#if (0)
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
#endif

void c_frustum::Set (void) {

	/*TCtx_Toggle();*/

	using namespace ::open_gl::procs::projection;

//	const t_rect rc_clip = {0, 42, 683, 683};
	const f_planes planes(1.0f, 10.0f);
	const f_rect f_clip(-0.577350378f, 0.577350378f, 0.577350378f, -0.577350378f);

	// step#1: sets the matrix mode to 'projection';
	CTstMode stk_mode(true);
	if (__failed(stk_mode.Set(e_stk_mode::e_project))) { _out()(); return; }

	// step #2 resets the matrix to identity;
	CTstMatrix matrix(true);
	if (__failed(matrix.To_self())) { _out()(); return; }

	// step #3 defines the frustum volume;
	CTstFrustum frustum(true);
	if (__failed(frustum.Set(f_clip, planes))) {/*keeps going*/}
	else {
	// step #4: if setting frustum succeeded queries the changed matrix back;
		matrix.Get(e_mat_type::e_project);
	}
	// step #5: restores 'modelview' mode to draw objects;
	stk_mode.Set(e_stk_mode::e_modelview);
	_out()();
}

#pragma endregion