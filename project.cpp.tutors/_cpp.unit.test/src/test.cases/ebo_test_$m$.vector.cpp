/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:53:10.131, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface implementation file ; 
*/
#include "ebo_test_$m$.vector.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_vec3{}

c_vec3::c_vec3(void) {}

void c_vec3::Length (void) {
	c_tvec_3().Length(true); c_tvec_3(1.0f, 1.0f, 1.0f).Length(true);  _out()();
}

void c_vec3::Negate (void) {
	c_tvec_3 v_3(1.0f, 1.0f, 1.0f);
	v_3.Negate(true);
	v_3.Negate(true);
	_out()();
}

void c_vec3::Normalize (void) {
	_out() += _T("Using fast inverse:"); c_tvec_3(1.0f, 1.0f, 1.0f).Normalize(true);
	_out() += _T("Using regular inverse:"); c_tvec_3(1.0f, 1.0f, 1.0f).Normalize(false);
	_out()();
}

#pragma endregion
#pragma region cls::c_vec4{}

c_vec4::c_vec4(void) {}

void c_vec4::Length (void) {
	c_tvec_4().Length(true); c_tvec_4(1.0f, 1.0f, 1.0f, 1.0f).Length(true);  _out()();
}

void c_vec4::Normalize (void) {
	{c_tvec_4 v_4(2.0f, 2.0f, 2.0f, 2.0f); v_4.Length(true); _out() += _T("Using fast inverse:"); v_4.Normalize(true); }
	{c_tvec_4 v_4(3.0f, 3.0f, 3.0f, 3.0f); v_4.Length(true); _out() += _T("Using regular inverse:"); v_4.Normalize(false); }
	_out()();
}

#pragma endregion