/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jun-2026 at 13:32:39.674, UTC+4, Batumi, Friday;
	This is OpenGL orthographic projection matrix wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$m$.ortho.h"

using namespace ::test::open_gl::ortho;

#pragma region cls::c_ortho{}

void c_ortho::Set (void) {

	const f_planes planes (-1.0f, 1.0f);
	const t_rect   clip = {0, 0, 640, 480};

	// step#1: sets the matrix mode to 'projection';
	CTstMode stk_mode(true);
	if (__failed(stk_mode.Set(e_stk_mode::e_project))) { _out()(); return; }

	// step #2 resets the matrix to identity;
	CTstMatrix matrix(true);
	if (__failed(matrix.To_self())) { _out()(); return; }

	// step #3: creates the orthographic matrix; << this is the step being tested!
	CTstOrtho ortho;
	if (__failed(ortho.Set(clip, planes))) {/*keeps going*/}
	else {
	// step #4: if setting frustum succeeded queries the changed matrix back;
		matrix.Get(e_mat_type::e_project);
	}
	// step #5: restores 'modelview' mode to draw objects;
	stk_mode.Set(e_stk_mode::e_modelview);
	_out()();
}

#pragma endregion