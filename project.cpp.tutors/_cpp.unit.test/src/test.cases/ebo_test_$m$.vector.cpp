/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:53:10.131, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface implementation file ; 
*/
#include "ebo_test_$m$.vector.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace _impl {

	class c_dot_v2 {
	public:
		 c_dot_v2 (void) = default; c_dot_v2 (const c_dot_v2&) = delete; c_dot_v2 (c_dot_v2&&) = delete;
		~c_dot_v2 (void) = default;

		static
		float Get (const vec_2& _v2_0, const vec_2& _v2_1, const bool _b_cls_out = true) {
			_v2_0; _v2_1; _b_cls_out;
			if (_b_cls_out)
			_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
			_out() += TString().Format(_T("Input the 1st vec_2: %s"), (_pc_sz) _v2_0.To_str());
			_out() += TString().Format(_T("Input the 2nd vec_2: %s"), (_pc_sz) _v2_1.To_str());

			::glm::vec2 v2_0_(_v2_0.x, _v2_0.y);
			::glm::vec2 v2_1_(_v2_1.x, _v2_1.y);

			float f_dot = 0.0f;

			CTime spent;
		//	{ CChrono_auto chrono(spent); f_dot = ::glm::clamp(::glm::dot(v2_0_, v2_1_), -1.0f, 1.0f); }
			{ CChrono_auto chrono(spent); f_dot = ::glm::dot(v2_0_, v2_1_); }
			if (_b_cls_out)
			_out() += TString().Format(_T("[impt] ::glm::dot = %.2f (%s)"), f_dot, (_pc_sz) spent());

			return f_dot;
		}

	private:
		c_dot_v2& operator = (const c_dot_v2&) = delete; c_dot_v2& operator = (c_dot_v2&&) = delete;
	};

}}}}
using namespace ebo::boo::test::_impl;

#pragma region cls::c_vec2{}

void c_vec2::Get_angle (void) {

	vec_2 v2_0(0.0f, 1.0f);
	vec_2 v2_1(1.0f, 0.0f);

	const float f_angle_0 = c_tvec_2().Get_angle(v2_0, v2_1, true);
	const float f_angle_1 = ::glm::acos(c_dot_v2::Get(v2_0, v2_1, false));
	/* query: how to get angle between to vec2 opengl c++:
	float angle = glm::atan2(b.y, b.x) - glm::atan2(a.y, a.x);
    
    // normalizes the result to the [-PI, PI] range;
    if (angle >  glm::pi<float>()) angle -= 2.0f * glm::pi<float>();
    if (angle <=-glm::pi<float>()) angle += 2.0f * glm::pi<float>();
	*/
	_out() += TString().Format(_T("[impt] ::glm::angle = %.2f;"), defs::rad_2_deg * f_angle_1);

	_out()();
}

void c_vec2::Get_dot (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	vec_2 v_2_0(0.0f, 1.0f);
	vec_2 v_2_1(1.0f, 0.0f);

	_out() += _T("[imprt] Expected angle == 90 deg.:"); c_tvec_2().Get_dot(v_2_0, v_2_1, false);
	_out() += _T("[imprt] Expected angle < 90 deg.:");  c_tvec_2().Get_dot(v_2_1, v_2_1, false);  // gets the dot product on the same vector;
	_out() += _T("[imprt] Expected angle > 90 deg.:");  c_tvec_2().Get_dot(v_2_0, vec_2(1.0f, -1.0f), false);

	const float f_dot_glm = c_dot_v2::Get(vec_2(1.0f, 0.0f), vec_2(1.0f, 0.0f), true);

	_out()();
}

#pragma endregion
#pragma region cls::c_vec3{}

void c_vec3::Cross (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_tvec_3 v_3_0(0.0f, 1.0f, 0.0f); _out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_3_0().To_str());
	c_tvec_3 v_3_1(1.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_1: {%s};"), (_pc_sz) v_3_1().To_str());

	vec_3 v_3 = v_3_0().Get_cross(v_3_1());
	_out() += TString().Format(_T("[impt] result: %s;"), (_pc_sz) v_3.To_str());
	_out()();
}

void c_vec3::Dot (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_tvec_3 v_3_0(0.0f, 1.0f, 0.0f); _out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_3_0().To_str());
	c_tvec_3 v_3_1(1.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_1: {%s};"), (_pc_sz) v_3_1().To_str());

	float f_dot = v_3_0.Get_dot(v_3_1());
	bool  b_dot = defs::f_epsilon > f_dot;

	_pc_sz pc_sz_pat = _T("%s dot product: %.7f; vectors are: %s'orthogonal';");
	_out() += TString().Format(pc_sz_pat, b_dot ? _T("[impt]") : _T("[warn]"), f_dot, b_dot ? _T("") : _T("not"));

	v_3_1().Set(0.0f, 1.0f, 0.1f);
	f_dot = v_3_0.Get_dot(v_3_1());
	b_dot = defs::f_epsilon > f_dot;
	
	_out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_3_1().To_str());
	_out() += TString().Format(pc_sz_pat, b_dot ? _T("[impt]") : _T("[warn]"), f_dot, b_dot ? _T("") : _T("not"));
	_out()();
}

void c_vec3::Length (void) {
	c_tvec_3().Length(true); c_tvec_3(1.0f, 1.0f, 1.0f).Length(true);  _out()();
}

void c_vec3::Negate (void) {
	c_tvec_3 v_3_0(1.0f, 1.0f, 1.0f);
	c_tvec_3 v_3_1(1.0f, 1.0f, 1.0f);
	v_3_0.Negate(true);
	v_3_0.Negate(true);
	_out() += v_3_1() == v_3_0() ? _T("[impt] result: test case is passed;") : _T("[error] test case is not passed;");
	_out()();
}

void c_vec3::Normalize (void) {
#if (0)
	_out() += _T("Using bits level inverse:"); c_tvec_3(1.0f, 1.0f, 1.0f).Normalize(true);
	_out() += _T("Using std::sqrtf inverse:"); c_tvec_3(1.0f, 1.0f, 1.0f).Normalize(false);
	_out() += _T("Trying to normalize 0-length vector:");

	c_tvec_3 v_0; v_0.Normalize(false);
	if (c_tvec_3()() == v_0()) // no change is expected;
		_out() += TString().Format(_T("[error] The vector of length = %.7f cannot be normalized;"), v_0().Length());
#else
	c_tvec_3 v3_val (1.0f, 1.0f, 1.0f);
	c_tvec_3 v3_norm; v3_norm() = v3_val(); v3_norm.Normalize(false);
	
	::glm::vec3 v3_glm(0.0f); v3_val >> v3_glm;
	CTime spent;
	{ CChrono_auto chrono(spent); v3_glm = ::glm::normalize(v3_glm); }
	
	c_tvec_3 v3_result(v3_glm);
	_out() += _T("[warn]::glm::vec3.normalize():");
	_out() += TString().Format(_T("*after* : {%s} %s"), (_pc_sz) v3_result().To_str(), (_pc_sz) spent());

	if (v3_result() == v3_norm())
	     _out() += _T("[impt] result: glm::vec3 and math::vec_3 are equal after normalize();");
	else _out() += _T("[error] result: glm::vec3 and math::vec_3 are *not* equal after normalize();");

#endif
	_out()();
}

#pragma endregion
#pragma region cls::c_vec4{}

void c_vec4::Cross (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_tvec_4 v_4_0(0.0f, 1.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_4_0().To_str());
	c_tvec_4 v_4_1(1.0f, 0.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_1: {%s};"), (_pc_sz) v_4_1().To_str());

	vec_4 v_4 = v_4_0().Get_cross(v_4_1());
	_out() += TString().Format(_T("[impt] result: %s;"), (_pc_sz) v_4.To_str());
	_out()();
}

void c_vec4::Dot (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_tvec_4 v_4_0(0.0f, 1.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_4_0().To_str());
	c_tvec_4 v_4_1(1.0f, 0.0f, 0.0f, 0.0f); _out() += TString().Format(_T("v_1: {%s};"), (_pc_sz) v_4_1().To_str());

	float f_dot = v_4_0.Get_dot(v_4_1());
	bool  b_dot = defs::f_epsilon > f_dot;

	_pc_sz pc_sz_pat = _T("%s dot product: %.7f; vectors are: %s'orthogonal';");
	_out() += TString().Format(pc_sz_pat, b_dot ? _T("[impt]") : _T("[warn]"), f_dot, b_dot ? _T("") : _T("not"));

	v_4_1().Set(0.0f, 1.0f, 0.1f, 0.0f);
	f_dot = v_4_0.Get_dot(v_4_1());
	b_dot = defs::f_epsilon > f_dot;

	_out() += TString().Format(_T("v_0: {%s};"), (_pc_sz) v_4_1().To_str());
	_out() += TString().Format(pc_sz_pat, b_dot ? _T("[impt]") : _T("[warn]"), f_dot, b_dot ? _T("") : _T("not"));
	_out()();
}

void c_vec4::Length (void) {
	c_tvec_4().Length(true); c_tvec_4(1.0f, 1.0f, 1.0f, 1.0f).Length(true);  _out()();
}

void c_vec4::Negate (void) {
	c_tvec_4 v_4_0(1.0f, 1.0f, 1.0f, 1.0f);
	c_tvec_4 v_4_1(1.0f, 1.0f, 1.0f, 1.0f);
	v_4_0.Negate(true);
	v_4_0.Negate(true);
	_out() += v_4_1() == v_4_0() ? _T("[impt] result: test case is passed;") : _T("[error] test case is not passed;");
	_out()();
}

void c_vec4::Normalize (void) {
	{c_tvec_4 v_4(2.0f, 2.0f, 2.0f, 2.0f); v_4.Length(true); _out() += _T("Using bits level inverse:"); v_4.Normalize(true); }
	{c_tvec_4 v_4(3.0f, 3.0f, 3.0f, 3.0f); v_4.Length(true); _out() += _T("Using std::sqrtf inverse:"); v_4.Normalize(false); }
	_out() += _T("Trying to normalize 0-length vector:");

	c_tvec_4 v_0; v_0.Normalize(false);
	if (c_tvec_4()() == v_0()) // no change is expected;
		_out() += TString().Format(_T("[error] The vector of length = %.7f cannot be normalized;"), v_0().Length());

	_out()();
}

#pragma endregion