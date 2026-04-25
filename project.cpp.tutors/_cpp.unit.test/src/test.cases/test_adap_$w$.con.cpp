/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:06:22.537, UTC+4, Batumi, Sunday;
	This is Ebo Pack trace console unit test adapter interface implementation file; 
*/
#include "test_adap_$w$.con.h"

using namespace test::win_api::console;

#pragma region cls::c_wrap{}

void c_locator::Path (void) {

	c_con_loc().Get_path(); _out()();
}

#pragma endregion
#pragma region cls::c_wrap{}

void c_wrap::Create (void) {

	c_con_wrap wrapper;

	wrapper.Create(c_con_loc().Get_path());
	wrapper.Detach();

	_out()();
}

void c_wrap::Path (void) {
	CError error(__CLASS__, __METHOD__, __s_ok);

	c_con_wrap::Get_path(error);

	_out()();
}

#pragma endregion