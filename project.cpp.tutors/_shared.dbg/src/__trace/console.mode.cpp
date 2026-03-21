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

CInput::CInput (void) { CBase::m_error >>__CLASS__; }

_pc_sz  CInput::To_str (const ulong _u_flags) {
	_u_flags;
	static CString cs_out; cs_out.Empty(); if (0 == _u_flags) { cs_out = _T("$input: no_flags"); return (_pc_sz) cs_out; }

	ulong u_flags = _u_flags; u_flags;
#pragma region __defs[]
#define in_echo_in  ENABLE_ECHO_INPUT
#define in_insert   ENABLE_INSERT_MODE
#define in_line_in  ENABLE_LINE_INPUT
#define in_mouse_in ENABLE_MOUSE_INPUT
#define in_procs_in ENABLE_PROCESSED_INPUT
#define in_qu_edit  ENABLE_QUICK_EDIT_MODE
#define in_wnd_in   ENABLE_WINDOW_INPUT
#define in_virtual  ENABLE_VIRTUAL_TERMINAL_INPUT
#pragma endregion
	if (u_flags & in_echo_in ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("echo_input");   u_flags &= ~in_echo_in; }
	if (u_flags & in_insert  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("insert_mode");  u_flags &= ~in_insert;  }
	if (u_flags & in_line_in ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("line_input");   u_flags &= ~in_line_in; }
	if (u_flags & in_mouse_in) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("mouse_input");  u_flags &= ~in_mouse_in;}
	if (u_flags & in_procs_in) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("processed");    u_flags &= ~in_procs_in;}
	if (u_flags & in_qu_edit ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("quick_edit");   u_flags &= ~in_qu_edit; }
	if (u_flags & in_wnd_in  ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("window_input"); u_flags &= ~in_wnd_in;  }
	if (u_flags & in_virtual ) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("virt_term");    u_flags &= ~in_virtual; }

	if (u_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += TString().Format(_T("#undef: (%u)"), u_flags); }

	cs_out = TString().Format(_T("$input: %s;"), (_pc_sz) cs_out);
	
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::COutput{}

COutput::COutput (void) { CBase::m_error >>__CLASS__; }

_pc_sz  COutput::To_str (const ulong _u_flags) {
	_u_flags;
	static CString cs_out; cs_out.Empty(); if (0 == _u_flags) { cs_out = _T("$output: no_flags"); return (_pc_sz) cs_out; }

	ulong u_flags = _u_flags; u_flags;
#pragma region __defs[]
#define out_procs  ENABLE_PROCESSED_OUTPUT
#define out_wrap   ENABLE_WRAP_AT_EOL_OUTPUT
#define out_virt   ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define out_no_new DISABLE_NEWLINE_AUTO_RETURN
#define out_w_grid ENABLE_LVB_GRID_WORLDWIDE
#pragma endregion
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
#pragma region cls::CMode{}

const
CInput& CMode::In (void) const { return this->m_input; }
CInput& CMode::In (void)       { return this->m_input; }
const
COutput& CMode::Out (void) const { return this->m_output; }
COutput& CMode::Out (void)       { return this->m_output; }

#pragma endregion