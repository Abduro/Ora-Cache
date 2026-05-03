/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 09:32:44.315, UTC+4, Batumi, Sunday;
	This is Ebo Pack console content wrapper interface implementation file;
*/
#include "console.content.h"

using namespace shared::console;
using namespace shared::console::content;

#pragma region cls::CCtxMenu{}

CCtxMenu::CCtxMenu (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCtxMenu::Enable (const bool _b_state) {
	_b_state;
	this->m_error << __METHOD__<<__s_ok;

	modes::CInput input;
	if (__failed(input.Get()))
	{__trace_err_ex_2(this->m_error = input.Error()); return this->Error(); }

	CString p_before_in  = modes::CInput::To_str(input.Flags()); p_before_in;
	CString p_before_out = modes::COutput::To_str(input.Flags()); p_before_out; // looks like useless, because input mode does not contain output mode flags;

	if (__failed(input.EditMode(false)))
	{__trace_err_ex_2(this->m_error = input.Error()); return this->Error(); }

	CString p_after_in = modes::CInput::To_str(input.Flags()); p_after_in;
	CString p_after_out = modes::COutput::To_str(input.Flags()); p_after_out;

	return this->Error();
}

TError& CCtxMenu::Error (void) const { return this->m_error; }

#pragma endregion