/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 09:31:22.974, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' trace console event unit test adapter interface implementation file; 
*/
#include "ebo_test_$w$.con.evt.h"

using namespace ebo::boo::test::con;
using namespace ebo::boo::test::con::events;

#pragma region cls::c_ctrl_router{}

void c_ctrl_router::Turn_off (void) {
	_out()();
}

void c_ctrl_router::Turn_on (void) {
	_out()();
}

#pragma endregion
#pragma region cls::c_input_router{}

void c_input_router::Turn_off (void) {

	_out() += TString().Format(_T("[impt] The router is turned '%s';"), c_rtr_input()().Is_on() ? _T("on") : _T("off"));
	// (1) tries to turn off the router (error is expected);
	c_rtr_input().Turn(false);

	_out()();
}

void c_input_router::Turn_on (void) {

	_out() += TString().Format(_T("[impt] The router is turned '%s';"), c_rtr_input()().Is_on() ? _T("on") : _T("off"));
	c_rtr_input().Turn(true);

	_out()();
}

#pragma endregion