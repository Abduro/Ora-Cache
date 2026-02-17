/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Feb-2026 at 11:56:43.660, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL draw virtual space wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.virt.space.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::CTAxes_Dyn{}

CTAxes_Dyn::CTAxes_Dyn (void) {}

CString CTAxes_Dyn::To_str (const TAxes_Dyn& _axes) {
	_axes;
	static  _pc_sz  ps_sz_pat = _T(
		"Dynamic axes:\n"
		"%sfwd : {%s}\n"
		"%sleft: {%s}\n"
		"%sup  : {%s}"
	);
	static  CString cs_out;
	cs_out.Format ( ps_sz_pat,
		predefs::_p_pfx, (_pc_sz) _axes.Fwd().To_str(), predefs::_p_pfx, (_pc_sz) _axes.Left().To_str(), predefs::_p_pfx, (_pc_sz) _axes.Up().To_str()
	);
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CTAxes_Fix{}

CTAxes_Fix::CTAxes_Fix (void) {}

CString CTAxes_Fix::To_str (const TAxes_Fix& _axes) {
	_axes;
	static  _pc_sz  ps_sz_pat = _T("Fixed axes:\n%sx-axis: {%s}\n%sy-axis: {%s}\n%sz-axis: {%s}");
	static  CString cs_out;
	cs_out.Format ( ps_sz_pat,
		predefs::_p_pfx, (_pc_sz) _axes.X().To_str(), predefs::_p_pfx, (_pc_sz) _axes.Y().To_str(), predefs::_p_pfx, (_pc_sz) _axes.Z().To_str()
	);
	return (_pc_sz) cs_out;
}

#pragma endregion