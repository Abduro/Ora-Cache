/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2026 at 10:15:29.516, UTC+4, Batumi, Sunday;
	This is OpenGL viewport related  procedures wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$p$.viewport.h"

using namespace ::test::open_gl::procs::ver_1_1;

#pragma region cls::c_viewport{}

void c_viewport::Get_Params (void) {

	TCtxToggle toggle;

	CTstViewport(true).Get_Params();
	_out()();
}

void c_viewport::Is_valid (void) {

	TCtxToggle toggle;
	CTstViewport viewport(false); CViewport& v_port = viewport(); CParams& params = v_port.Params();

	static
	_pc_sz p_tc_pat = _T("test case #%u: params = %s;");
	uint32_t number = 0;

	params.Value()() = {  0,  0,  0,  0}; _out() += TString().Format(p_tc_pat, number++, (_pc_sz) CParams::To_str(params.Value())); viewport.Is_valid();
	params.Value()() = {  0,  0,  0, 90}; _out() += TString().Format(p_tc_pat, number++, (_pc_sz) CParams::To_str(params.Value())); viewport.Is_valid();
	params.Value()() = {  0,  0, 90, 90}; _out() += TString().Format(p_tc_pat, number++, (_pc_sz) CParams::To_str(params.Value())); viewport.Is_valid();
	params.Value()() = { 90,  0, 90, 90}; _out() += TString().Format(p_tc_pat, number++, (_pc_sz) CParams::To_str(params.Value())); viewport.Is_valid();
	params.Value()() = {  0,-90, 90, 90}; _out() += TString().Format(p_tc_pat, number++, (_pc_sz) CParams::To_str(params.Value())); viewport.Is_valid();

	_out()();
}

void c_viewport::Set_Params (void) {

	TCtxToggle toggle;
	CTstViewport viewport(true);

	viewport.Set_Params({0, 0, 640, 480}); viewport.Verbose(false);
	_out() += _T("Query to viewport to confirm the result:"); viewport.Get_Params();

	_out()();
}

#pragma endregion