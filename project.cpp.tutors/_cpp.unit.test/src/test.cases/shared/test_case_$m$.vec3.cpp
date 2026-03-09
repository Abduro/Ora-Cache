/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 22:36:41.820, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib vector of 3 elements uint test interface implementation file for using in test cases' adapters; 
*/
#include "test_case_$m$.vec3.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_tvec_3{}

c_tvec_3::c_tvec_3 (void) {}
c_tvec_3::c_tvec_3 (const float _x, const float _y, const float _z) : m_vec_3(_x, _y, _z) {}
c_tvec_3::c_tvec_3 (const ::glm::vec3& _vec3) : c_tvec_3() { *this << _vec3; }

vec_3   c_tvec_3::Get_cross (const vec_3& _v_with) {
	_v_with;
	return (*this)().Get_cross(_v_with);
}

float   c_tvec_3::Get_dot (const vec_3& _v_3) const {
	_v_3;
	const float f_dot = (*this)().Get_dot(_v_3);
	return f_dot;
}

float   c_tvec_3::Length (const bool _b_log) const {
	_b_log;
	const float f_length = (*this)().Length();
	if (_b_log) {
		_pc_sz pc_sz_pat = _T("vec3 {%s} == %s");
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out() += TString().Format(pc_sz_pat, (_pc_sz) (*this)().To_str(), TString().Float(f_length, _T("%.7f")));
	}
	return f_length;
}

vec_3&  c_tvec_3::Negate (const bool _b_log/* = true*/) {
	_b_log;
	if (_b_log) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out() += TString().Format(_T("*before*: {%s}"), (_pc_sz) (*this)().To_str());
	}
	(*this)().Negate();
	if (_b_log) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out() += TString().Format(_T("*after* : {%s}"), (_pc_sz) (*this)().To_str());
	}
	return (*this)();
}

vec_3&  c_tvec_3::Normalize (const bool _b_fast, const bool _b_log) {
       _b_fast; _b_log;
	if (_b_log) {
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out() += TString().Format(_T("*before*: {%s}"), (_pc_sz) (*this)().To_str());
	}

	CTime spent;
	{ CChrono_auto chrono(spent); (*this)().Normalize(_b_fast); }
	if (_b_log) {
		_pc_sz pc_sz_pat = _T("*after* : {%s} %s");
		_out() += TString().Format(pc_sz_pat, (_pc_sz) (*this)().To_str(), (_pc_sz) spent());
	}
	return (*this)();
}
const
vec_3&  c_tvec_3::ref (void) const { return this->m_vec_3; }
vec_3&  c_tvec_3::ref (void)       { return this->m_vec_3; }

const
vec_3&  c_tvec_3::operator ()(void) const { return this->ref(); }
vec_3&  c_tvec_3::operator ()(void)       { return this->ref(); }

vec_3&  c_tvec_3::operator <<(const ::glm::vec3& _vec3) {
	(*this)().Set(_vec3.x, _vec3.y, _vec3.z);
	return (*this)();
}
::glm::vec3& c_tvec_3::operator >> (::glm::vec3& _vec3) const {
	_vec3.x = (*this)().x;
	_vec3.y = (*this)().y;
	_vec3.z = (*this)().z;
	return _vec3;
}

#pragma endregion