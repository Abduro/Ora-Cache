/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Jul-2026 at 13:44:04.340, UTC+4, Batumi, Thursday;
	This is Ebo Pack generic input wrappers' unit test adapter interface implementation file; 
*/
#include "test_adap_$w$.input.h"

using namespace ::test::win_api::input;


#pragma region cls::c_cmd_cln{}

void c_cmd_cln::Parse (void) {

	CTstCmdLn cmd_ln;
	cmd_ln.Parse();
	_out()();
}

#pragma endregion