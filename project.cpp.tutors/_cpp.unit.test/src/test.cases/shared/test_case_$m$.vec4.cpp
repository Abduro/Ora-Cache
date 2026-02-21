/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Feb-2026 at 17:21:35.731, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL math lib vector of 4 elements uint test interface implementation file for using in test cases' adapters; 
*/
#include "test_case_$m$.vec4.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_tvec_4{}

c_tvec_4::c_tvec_4 (void) {}
c_tvec_4::c_tvec_4 (const float _x, const float _y, const float _z, const float _w) : m_vec_4(_x, _y, _z, _w) {}

float   c_tvec_4::Length (const bool _b_log) const {
	_b_log;
	const float f_length = (*this)().Length();
	if (_b_log) {
		_pc_sz pc_sz_pat = _T("vec4 {%s} == %s");
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out() += TString().Format(pc_sz_pat, (_pc_sz) (*this)().To_str(), TString().Float(f_length, _T("%.7f")));
	}
	return f_length;
}

vec_4&  c_tvec_4::Negate (const bool _b_log/* = true*/) {
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

vec_4&  c_tvec_4::Normalize (const bool _b_fast, const bool _b_log) {
       _b_fast; _b_log;
	if (_b_log) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
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
vec_4&  c_tvec_4::ref (void) const { return this->m_vec_4; }
vec_4&  c_tvec_4::ref (void)       { return this->m_vec_4; }

const
vec_4&  c_tvec_4::operator ()(void) const { return this->ref(); }
vec_4&  c_tvec_4::operator ()(void)       { return this->ref(); }

#pragma endregion