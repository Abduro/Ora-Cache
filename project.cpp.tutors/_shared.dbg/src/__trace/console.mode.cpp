/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 14:04:40.381, UTC+4, Batumi, Saturday;
	This is system console moden wrapper interface implementation file;
*/
#include "console.mode.h"
#include "shared.preproc.h"

using namespace shared::console::modes;

#pragma region cls::CBase{}

CBase::CBase (void) : m_flags(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

ulong   CBase::Flags (void) const { return this->m_flags; }
ulong&  CBase::Flags (void)       { return this->m_flags; }

TError& CBase::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CInput{}

#pragma region __defs[]
#define in_auto_pos ENABLE_AUTO_POSITION
#define in_echo     ENABLE_ECHO_INPUT
#define in_flags    ENABLE_EXTENDED_FLAGS
#define in_insert   ENABLE_INSERT_MODE
#define in_line     ENABLE_LINE_INPUT
#define in_mouse    ENABLE_MOUSE_INPUT
#define in_procs    ENABLE_PROCESSED_INPUT
#define in_qu_edit  ENABLE_QUICK_EDIT_MODE
#define in_window   ENABLE_WINDOW_INPUT
#define in_virtual  ENABLE_VIRTUAL_TERMINAL_INPUT
#pragma endregion

static ulong u_in_flag_set[10] = { in_auto_pos, in_echo, in_flags, in_insert, in_line, in_mouse, in_procs, in_qu_edit, in_window, in_virtual };

CInput::CInput (void) { CBase::m_error >>__CLASS__; }

err_code CInput::Get (void) {
	CBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/console/getconsolemode ;
	if (false == !!::GetConsoleMode(__in_handle, &CBase::Flags()))
		CBase::m_error.Last();

	return CBase::Error();
}

bool CInput::Has (const ulong _u_flags) {
	_u_flags;
	for (uint32_t i_ = 0; i_ < _countof(u_in_flag_set); i_++)
		if (u_in_flag_set[i_] & _u_flags)
			return true;
	return false;
}

err_code CInput::Set (const ulong _u_flags) {
	_u_flags;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (false == CInput::Has(_u_flags))
		return m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: given set (%u) does not have input buffer flags"), _u_flags);

	// https://learn.microsoft.com/en-us/windows/console/setconsolemode ;
	if (false == ::SetConsoleMode(__in_handle, _u_flags))
		CBase::m_error.Last();

	return CBase::Error();
}

_pc_sz  CInput::To_str (const ulong _u_flags) {
	_u_flags;
	static CString cs_out; cs_out.Empty(); if (0 == _u_flags) { cs_out = _T("$input: no_flags"); return (_pc_sz) cs_out; }

	ulong u_flags = _u_flags; u_flags;

	if (u_flags & in_auto_pos) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("auto_pos");     u_flags &= ~in_auto_pos; }
	if (u_flags & in_echo    ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("echo");         u_flags &= ~in_echo;   }
	if (u_flags & in_flags   ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("ext_flags");    u_flags &= ~in_flags;  }
	if (u_flags & in_insert  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("insert_mode");  u_flags &= ~in_insert; }
	if (u_flags & in_line    ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("by_line");      u_flags &= ~in_line;   }
	if (u_flags & in_mouse   ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("by_mouse");     u_flags &= ~in_mouse;  }
	if (u_flags & in_procs   ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("processed");    u_flags &= ~in_procs;  }
	if (u_flags & in_qu_edit ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("quick_edit");   u_flags &= ~in_qu_edit; }
	if (u_flags & in_window  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("window_input"); u_flags &= ~in_window;  }
	if (u_flags & in_virtual ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("virt_term");    u_flags &= ~in_virtual; }

	if (u_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += TString().Format(_T("#undef: (%u)"), u_flags); }

	cs_out = TString().Format(_T("$input: %s;"), (_pc_sz) cs_out);
	
	return (_pc_sz) cs_out;
}

err_code CInput::operator <<(const ulong _u_flags) { return this->Set(_u_flags); }

#pragma endregion
#pragma region cls::COutput{}

#pragma region __defs[]
#define out_procs  ENABLE_PROCESSED_OUTPUT
#define out_wrap   ENABLE_WRAP_AT_EOL_OUTPUT
#define out_virt   ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define out_no_new DISABLE_NEWLINE_AUTO_RETURN
#define out_w_grid ENABLE_LVB_GRID_WORLDWIDE
#pragma endregion

static ulong u_out_flag_set[5] = { out_procs, out_wrap, out_virt, out_no_new, out_w_grid };

COutput::COutput (void) { CBase::m_error >>__CLASS__; }

err_code COutput::Get (void) {
	CBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/console/getconsolemode ;
	if (false == !!::GetConsoleMode(__out_handle, &CBase::Flags()))
		CBase::m_error.Last();

	return CBase::Error();
}

bool COutput::Has (const ulong _u_flags) {
	_u_flags;
	for (uint32_t i_ = 0; i_ < _countof(u_out_flag_set); i_++)
		if (u_out_flag_set[i_] & _u_flags)
			return true;
	return false;
}

err_code COutput::Set (const ulong _u_flags) {
	_u_flags;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (false == CInput::Has(_u_flags))
		return m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: given set (%u) does not have output buffer flags"), _u_flags);

	// https://learn.microsoft.com/en-us/windows/console/setconsolemode ;
	if (false == ::SetConsoleMode(__out_handle, _u_flags))
		CBase::m_error.Last();

	return CBase::Error();
}

_pc_sz  COutput::To_str (const ulong _u_flags) {
	_u_flags;
	static CString cs_out; cs_out.Empty(); if (0 == _u_flags) { cs_out = _T("$output: no_flags"); return (_pc_sz) cs_out; }

	ulong u_flags = _u_flags; u_flags;

	if (u_flags & out_procs ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("processed"); u_flags &= ~out_procs ; }
	if (u_flags & out_wrap  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("auto-wrap"); u_flags &= ~out_wrap; }
	if (u_flags & out_virt  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("virt_term"); u_flags &= ~out_virt; }
	if (u_flags & out_no_new) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("no_new_ln"); u_flags &= ~out_no_new; }
	if (u_flags & out_w_grid) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("wide_grid"); u_flags &= ~out_w_grid; }


	if (u_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += TString().Format(_T("#undef: (%u)"), u_flags); }

	cs_out = TString().Format(_T("$output: %s;"), (_pc_sz) cs_out);
	
	return (_pc_sz) cs_out;
}

#pragma endregion