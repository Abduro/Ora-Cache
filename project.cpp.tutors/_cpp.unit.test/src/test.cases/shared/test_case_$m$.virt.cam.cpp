/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Feb-2026 at 22:00:45.042, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL draw virtual camera wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.virt.cam.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::CTPosition{}

CTPosition::CTPosition (void) {}

_pc_sz  CTPosition::To_str (const CCamPos& _pos) {
	_pos;
	static  _pc_sz ps_sz_pat = _T("pos >> {%s}");
	static  CString cs_out; cs_out.Format(ps_sz_pat, (_pc_sz) _pos.Get().To_str());
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CTRotation{}

CTRotation::CTRotation (void) {}

_pc_sz  CTRotation::To_str (const CCamRot& _rot) {
	_rot;
	static  _pc_sz  pc_sz_pat = _T("[impt] rotation:\n%sangle: %s\n%smatrix:\n%s%squat: %s\n");
	static  CString cs_out;
	cs_out.Format ( pc_sz_pat,
		 predefs::_p_pfx , TString().Float(0.0f, _T("%10.7f")), predefs::_p_pfx, c_mtx_4x4().To_str(_rot.Get(), false),
		 predefs::_p_pfx , (_pc_sz) _rot.Quat().To_str());
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CTTarget{}

CTTarget::CTTarget (void) {}

_pc_sz  CTTarget::To_str (const CCamTarget& _tgt) {
	_tgt;
	static  _pc_sz  pc_sz_pat = _T("[impt] target:\n%sdistance: %s\n%scoords: {%s}");
	static  CString cs_out;
	cs_out.Format ( pc_sz_pat, predefs::_p_pfx, TString().Float(_tgt.Distance(), _T("%.7f")), predefs::_p_pfx, (_pc_sz) _tgt.Get().To_str());
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CTVirtCam{}

CTVirtCam::CTVirtCam (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CTVirtCam::Create (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->m_error <<__METHOD__<<__s_ok;

	TVirtCam& v_cam = ::Get_virt_cam();
	if (v_cam.Error()) { _out() += (this->m_error = v_cam.Error()); }
	_out() += CTRotation::To_str(v_cam.Rotate());
	_out() += CTPosition::To_str(v_cam.Pos());
	_out() += CTTarget::To_str(v_cam.Target());

	return this->Error();
}

TError& CTVirtCam::Error (void) const { return this->m_error; }

#pragma endregion