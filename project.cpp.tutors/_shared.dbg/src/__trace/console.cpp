/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Sep-2020 at 6:58:28p, UTC+7, Novosibirsk, Thursday;
	This is FakeGPS driver version 2 desktop client console interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to Wanderer Path Finder project on 6-Jan-2021 at 11:46:09.018 am, UTC+7, Novosibirsk, Tuesday;
	Adopted to Yandex Wanderer project on 12-Dec-2022 at 11:21:30.7989254, UTC+7, Novosibirsk, Monday;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.h"
#include "console.buffer.h"
#include "console.out.h"

#include "shared.preproc.h"

using namespace shared::console;

namespace shared { namespace console  { namespace _impl {

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif

#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

}}} using namespace shared::console::_impl;

#pragma region cls::CCondole{}

/* taking into account that the only one console can be created/associated with a process, the process info structure can be static;
*/
static
PROCESS_INFORMATION s_proc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information ;

CWrap:: CWrap (void) : m_hwnd(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CWrap::~CWrap (void) {
	if (this->Is_attached())
		this->Detach();
	if (s_proc.hProcess) { ::CloseHandle( s_proc.hProcess ); }
	if (s_proc.hThread ) { ::CloseHandle( s_proc.hThread ); } s_proc = {0};
}

err_code CWrap::Create (const bool _b_visible, const bool _b_attach) {
	_b_visible; _b_attach;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr != ::GetConsoleWindow()) // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;
		return this->m_error << (err_code)TErrCodes::eObject::eExists = _T("The console is already associated with this process");

	STARTUPINFO s_info = {0};  // https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfow ;
	s_info.cb = sizeof(s_info);
	s_info.dwFlags = STARTF_USESHOWWINDOW;
	s_info.wShowWindow = _b_visible ? SW_SHOW : SW_HIDE;

	// https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes ;
	if (false == !!::CreateProcess(0, CString("cmd.exe").GetBuffer(), 0, 0, 0, 0, 0, 0, &s_info, &s_proc))
		return this->m_error.Last();

	// https://learn.microsoft.com/en-us/windows/console/attachconsole ;
	if (false == !!::AttachConsole(s_proc.dwProcessId))
		return this->m_error.Last();

	this->m_hwnd = ::GetConsoleWindow();
	if (nullptr == this->m_hwnd)
		return this->m_error <<__e_hwnd = _T("There is no associated console with this process");

	CScreenBuffer().Clear();

	if (false == _b_attach) { // if not specified to keep the console attached, tries to disattach it;

		if (false == !!::FreeConsole()) // https://learn.microsoft.com/en-us/windows/console/freeconsole;
			this->m_error.Last();
		else
			this->m_hwnd = 0;
	}
	return this->Error();
}

err_code CWrap::Detach (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_attached())
		return this->Error();

	if (false == !!::FreeConsole()) // https://learn.microsoft.com/en-us/windows/console/freeconsole;
		this->m_error.Last();
	else
		this->m_hwnd = 0;

	return this->Error();
}

TError&  CWrap::Error (void) const { return this->m_error; }

bool CWrap::Is_attached (void) const { return 0 != ::GetConsoleWindow(); }

#pragma endregion;
#pragma region cls::CCondole{}

CConsole:: CConsole (void) : m_con_wnd(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }
CConsole::~CConsole (void) {}

err_code   CConsole::Close (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) // it is supposed the all opened file descriptors is already closed;
		return this->m_error << __e_not_inited;

#if (0)
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ; throws the system error 'Access denied';
	if (0 == ::DestroyWindow(this->m_con_wnd))
		return this->m_error.Last();
#endif
	this->m_con_wnd = 0;

	return this->Error();
}

err_code CConsole::Open  (const HWND _h_parent, const t_rect& _rect_wnd_pos, const bool _b_visible) {
	_h_parent; _rect_wnd_pos; _b_visible;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (0 == _h_parent || false == !!::IsWindow(_h_parent))
		return this->m_error << __e_hwnd = _T("Parent window handle is invalid");

	if (::IsRectEmpty(&_rect_wnd_pos))
		return this->m_error << __e_rect = _T("The input rectangle is empty");

	if (false == !!::AllocConsole()) // on closing the app process the console is destroyed by OS;
		return this->m_error.Last();
	else
		this->m_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;

	CLayout().As_child(this->m_con_wnd, _rect_wnd_pos, _b_visible);
#if (0)
	
#endif
	// https://learn.microsoft.com/en-us/windows/console/console-functions ;
	// https://learn.microsoft.com/en-us/windows/console/writeconsole ;
#if (0)
	COut::Error(_T("this is the error;\n"));
	COut::Info (_T("this is the info;\n"));
	COut::Warn (_T("this is the warn;\n"));
#else
	// https://cplusplus.com/forum/windows/58206/ ; how to make things better: redirect ::std::ios to this console;
#endif
	return this->Error();
}

HWND CConsole::Handle (void) const { return this->m_con_wnd; }

bool CConsole::Is_valid (void) const {
	return (0 != this->m_con_wnd && ::IsWindow(this->m_con_wnd));
}

TError& CConsole::Error (void) const { return this->m_error; }

CConsole::operator const HWND (void) const { return this->Handle(); }

#pragma endregion