/*
	Created by Tech_dog (ebontrop@gmsil.com) on 22-Mar-2026 at 14:12:02.641, UTC+4, Batumi, Sunday;
	This is Ebo Pack console event handler interface implementation file;
*/
#include "console.event.h"
#include "shared.preproc.h"

using namespace shared::console;
using namespace shared::console::events;

#pragma region cls::ctrl::CHandler{}

ctrl::CHandler::CHandler (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& ctrl::CHandler::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::input::CRouter{}

input::CRouter::CRouter (void) : m_turned(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  input::CRouter::Error (void) const { return this->m_error; }
bool     input::CRouter::Is_on (void) const { return this->m_turned; }
err_code input::CRouter::Turn  (const bool _b_on_off) {
	_b_on_off;
	this->m_error <<__METHOD__<<__s_ok;

	if (_b_on_off) {
		if (this->Is_on())
			return this->Error();

		this->m_thread = ::std::thread(&input::CRouter::Receive_evt, this);
		this->m_turned = true;
	}
	else {
		if (this->Is_on() == false)
			return this->Error();

		this->m_turned = false;
		this->m_thread.join();
	}

	return this->Error();
}

void input::CRouter::Receive_evt (void) {
	this->m_error <<__METHOD__<<__s_ok; // error object can work in multi threaded environment;
	
	// disables quick edit mode because it interfers with receiving mouse inputs;
	static const ulong u_req_flags = (ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
	static const ulong u_rec_size  =  128;

	modes::CInput input;
	if (__failed( input.Get() )) { this->m_error = input.Error(); this->m_turned = false; return; }
	if (__failed( input << (input.Flags() | u_req_flags))) { this->m_error = input.Error(); this->m_turned = false; return; }

	ulong u_recs = 0;
	ulong u_read = 0;
//	INPUT_RECORD in_recs[u_rec_size] = {0};

	while (this->m_turned) {

		::std::this_thread::sleep_for(::std::chrono::milliseconds(50));

		// https://learn.microsoft.com/en-us/windows/console/getnumberofconsoleinputevents ;
		if (false == !!::GetNumberOfConsoleInputEvents(__in_handle, &u_recs)) {
			this->m_error.Last(); break;
		}
		if (0 == u_recs)
			continue;

		::std::vector<INPUT_RECORD> v_recs(u_recs, {0});

		if (false == ::ReadConsoleInput(__in_handle, v_recs.data(), u_recs, &u_read)) {
			this->m_error.Last(); break;
		}

		try {


		}
		catch (...) { this->m_error <<__e_fail; break; }
	}
	this->m_turned = false;

	return;
}

#pragma endregion

TInputRouter& ::Get_input (void) {
	static TInputRouter input_router;
	return input_router;
}