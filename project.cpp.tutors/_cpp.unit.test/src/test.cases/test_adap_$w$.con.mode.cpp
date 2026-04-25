/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 09:30:40.660, UTC+4, Batumi, Monday;
	This is Ebo Pack trace console mode unit test adapter interface implementation file; 
*/
#include "test_adap_$w$.con.mode.h"

using namespace test::win_api::console;
using namespace test::win_api::console::modes;

#pragma region cls::c_input{}

void c_input::Get (void) {

	const uint32_t u_flags = c_mode_input().Get(); u_flags;

	_out()();
}

void c_input::Set (void) {
	// (1) trying to set flags of 0 value; (error is expected);
	c_mode_input().Set(0);
	// (2) possibly the flag set is expected to be succeeded;
	c_mode_input().Set(10);
	_out()();
}

#pragma endregion
#pragma region cls::c_output{}

void c_output::Get (void) {

	const uint32_t u_flags = c_mode_output().Get(); u_flags;

	_out()();
}

void c_output::Set (void) {
	// (1) trying to set flags of 0 value; (error is expected);
	c_mode_output().Set(0);
	// (2) possibly the flag set is expected to be succeeded;
	c_mode_output().Set(10);
	_out()();
}

#pragma endregion