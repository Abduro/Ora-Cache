/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 09:32:44.315, UTC+4, Batumi, Sunday;
	This is Ebo Pack console content wrapper interface implementation file;
*/
#include "console.content.h"
#include "shared.preproc.h"

using namespace shared::console::content;

#pragma region cls::CCtxMenu{}

CCtxMenu::CCtxMenu (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCtxMenu::Enable (const bool _b_state) {
	_b_state;
	this->m_error << __METHOD__<<__s_ok;

	void* p_input = /*_con.Get_in()*/__in_handle;
	unsigned long u_mode = 0;

	// https://learn.microsoft.com/en-us/windows/console/getconsolemode ;
	if (false == !!::GetConsoleMode(p_input, &u_mode))
		return this->m_error.Last();

	CString p_before_in  = modes::CInput::To_str(u_mode); p_before_in;
	CString p_before_out = modes::COutput::To_str(u_mode); p_before_out;

	static const uint32_t u_req = (ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	if (_b_state) u_mode &= ~(u_req);
	else u_mode |= u_req;

	// https://learn.microsoft.com/en-us/windows/console/setconsolemode ;
	if (false == !!::SetConsoleMode(p_input, u_mode))
		this->m_error.Last();

	CString p_after_in = modes::CInput::To_str(u_mode); p_after_in;
	CString p_after_out = modes::COutput::To_str(u_mode); p_after_out;

	return this->Error();
}

TError& CCtxMenu::Error (void) const { return this->m_error; }

#pragma endregion