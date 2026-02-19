/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 22:36:41.820, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib vector of 3 elements uint test interface implementation file for using in test cases' adapters; 
*/
#include "test_case_$m$.vec3.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_tvec_3x3{}

c_tvec_3x3::c_tvec_3x3 (void) {}
c_tvec_3x3::c_tvec_3x3 (const float _x, const float _y, const float _z) : m_vec_3(_x, _y, _z) {}

const
vec_3&  c_tvec_3x3::ref (void) const { return this->m_vec_3; }
vec_3&  c_tvec_3x3::ref (void)       { return this->m_vec_3; }

const
vec_3&  c_tvec_3x3::operator ()(void) const { return this->ref(); }
vec_3&  c_tvec_3x3::operator ()(void)       { return this->ref(); }

#pragma endregion