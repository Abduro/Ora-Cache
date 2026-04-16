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

#include "shared.dbg.h"
#include "shared.preproc.h"
#include "sys.registry.h"

using namespace shared::console;
using namespace shared::dbg;

namespace shared { namespace console  { namespace _impl {/*not used yeat*/}}} using namespace shared::console::_impl;

#pragma region cls::CLocator{}

CLocator::CLocator (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("the locator is not used yet"); }

TError& CLocator::Error (void) const { return this->m_error; }

_pc_sz  CLocator::Get_path (void) {
	this->m_error <<__METHOD__<<__s_ok;

	static CString cs_path;
	if (cs_path.IsEmpty() == false) cs_path.Empty();
	// (1) getting the path of debug messages output trace console from the registry is absent for this time;
	// (2) tries to get the part of the current prosses executable;
	//     it is assumed the call is made from test case, otherwise, the trace console does not make this call itself;

	CString cs_lib = CModule::Get_path(this->m_error);
	if (cs_lib.IsEmpty())
		return this->Error();

	const int n_found = cs_lib.ReverseFind(_T('\\'));
	if (-1 < n_found)
		cs_lib = cs_lib.Left(n_found);

	cs_path = TString().Format(_T("%s\\trace_console.exe"), (_pc_sz) cs_lib); // the hard coded file name is used yet;

	return (_pc_sz) cs_path;
}

#pragma endregion
#pragma region cls::CWrap{}

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

err_code CWrap::Create (_pc_sz _p_path, const bool _b_visible, const bool _b_attach) {
	_p_path; _b_visible; _b_attach;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr != ::GetConsoleWindow()) // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;
		return this->m_error << (err_code)TErrCodes::eObject::eExists = _T("The console is already associated with this process");

	if (0 == _p_path || 0 == ::_tcslen(_p_path))
		return this->m_error << __e_inv_arg = _T("input path of executable file is invalid");

	STARTUPINFO s_info = {0};  // https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfow ;
	s_info.cb = sizeof(s_info);
	s_info.dwFlags = STARTF_USESHOWWINDOW;
	s_info.wShowWindow = _b_visible ? SW_SHOW : SW_HIDE;

	CString cs_path(_p_path);

	// https://learn.microsoft.com/en-us/windows/win32/procthread/creating-processes ;
	if (false == !!::CreateProcess(0, cs_path.GetBuffer(), 0, 0, 0, 0, 0, 0, &s_info, &s_proc))
		return this->m_error.Last();

	// https://learn.microsoft.com/en-us/windows/console/attachconsole ;
	if (false == !!::AttachConsole(s_proc.dwProcessId))
	/**important*: running the console under 'cmd.exe' control leads to the following error:
	   cls::[CError]>>{code=0x0005;result=0x80070005;desc='Access is denied.';context=CWrap::Create()} ;
	   elevating the process of VS does not affect the security level of testhost.exe;
	*/ return this->m_error.Last();
	/* it very looks like the console wrapper executable must be running by this::Create() function;
	*/

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
		return this->m_error << (err_code)TErrCodes::eExecute::eState = _T("The console is not attached");

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

err_code CConsole::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == !!::AllocConsole()) // on closing the app process the console is destroyed by OS;
		this->m_error.Last();
	else
		this->m_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;

	CLayout layout;
	if (__failed(layout.OnCreate()))
		this->m_error = layout.Error();

	return this->Error();
}

err_code CConsole::Close (void) {

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

err_code CConsole::Create (const s_create_data& _data) {
	_data;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;
#if (0) // the creating a console window is not dependent on main/app window handle;
	if (0 == _data.m_parent || false == !!::IsWindow(_data.m_parent)) {
		this->m_error << __e_hwnd = _T("Parent window handle is invalid");
		__trace_err_ex_2(this->Error()); return this->Error();
	}
	if (::IsRectEmpty(&_data.m_rect))
		return this->m_error << __e_rect = _T("The input rectangle is empty");
#endif
	if (false == !!::AllocConsole()) // on closing the app process the console is destroyed by OS;
		return this->m_error.Last();
	else
		this->m_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;

	CLayout().As_child(_data);

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