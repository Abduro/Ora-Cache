/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Mar-2026 at 17:33:21.820, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' math lib vector of 2 elements uint test interface implementation file for using in test cases' adapters; 
*/
#include "test_case_$m$.vec2.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_tvec_2

float   c_tvec_2::Get_angle (const vec_2& _v_2_0, const vec_2& _v_2_1, const bool _b_cls_out/* = true*/) {
	_v_2_0; _v_2_1; _b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input the 1st vec_2: %s"), (_pc_sz) _v_2_0.To_str());
	_out() += TString().Format(_T("Input the 2nd vec_2: %s"), (_pc_sz) _v_2_1.To_str());

	float  f_angle = 0.0f;

	CTime spent;
	{ CChrono_auto chrono(spent); f_angle = ::Get_angle(_v_2_0, _v_2_1); }

	const float f_degrees = _round(defs::rad_2_deg * f_angle, 2);

	_out() += TString().Format(_T("[impt] the angle = %.2f deg. (%.7f rad.) %s"), f_degrees, f_angle, (_pc_sz) spent());

	return f_angle;
}

float c_tvec_2::Get_dot (const vec_2& _v_2_0, const vec_2& _v_2_1, const bool _b_cls_out/* = true*/) {
	_v_2_0; _v_2_1; _b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input the 1st vec_2: %s"), (_pc_sz) _v_2_0.To_str());
	_out() += TString().Format(_T("Input the 2nd vec_2: %s"), (_pc_sz) _v_2_1.To_str());

	float f_dot = 0.0f;

	CTime spent;
	{ CChrono_auto chrono(spent); f_dot = ::Get_dot(_v_2_0, _v_2_1); }

	f_dot = _round(defs::rad_2_deg * f_dot, 2);
	CString cs_angle = (0.0f == f_dot ? _T("= 90") : 0.0f < f_dot ? _T("< 90") : _T("> 90"));

	_out() += TString().Format(_T("[impt] the dot = %.2f (the angle expected %s deg.) (%s)"), f_dot, (_pc_sz) cs_angle, (_pc_sz) spent());

	return f_dot;
}

#pragma endregion