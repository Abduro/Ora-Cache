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
#include "console.cmd.h"
#include "console.out.h"

#include "shared.dbg.h"
#include "shared.preproc.h"
#include "sys.registry.h"

using namespace shared::console;
using namespace shared::dbg;

namespace shared { namespace console  { namespace _impl {

	class CLoader {
	public:
		  CLoader (void) = default; CLoader (const CLoader&) = delete; CLoader (CLoader&&) = delete;
		 ~CLoader (void) = default;
	public:
		HICON Load (const uint16_t _u_res_id, const bool _b_large) {
			_u_res_id; _b_large;
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagew ;
			HICON h_icon = (HICON)::LoadImage(
					static_cast<HINSTANCE>(::GetModuleHandle(nullptr)), MAKEINTRESOURCE(_u_res_id), IMAGE_ICON, this->Size(_b_large).cx, this->Size(_b_large).cy, LR_DEFAULTCOLOR
				);
			if (0 == h_icon) {
				__trace_err_ex_2(CError(__CLASS__,__METHOD__,__LastErrToHresult()));
			}
			return h_icon;
		}

		const t_size& Size (const bool bTreatAsLargeIcon) const
		{
			static const t_size ico_size = {
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CXICON : SM_CXSMICON), 
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CYICON : SM_CYSMICON)
			};
			return ico_size;
		}

	private:
		CLoader& operator = (const CLoader&) = delete;
		CLoader& operator = (CLoader&&) = delete;
	};

}}} using namespace shared::console::_impl;

#pragma region cls::CCmd_Handler{}

CCmd_Handler::CCmd_Handler (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
#if (0)
	if (g_cmd_map.empty() == false)
		g_cmd_map.clear();
	try {
		g_cmd_map.insert(::std::make_pair(e_cmd_ids::e_clear, CCommand(e_cmd_ids::e_clear, _T("Clear"))));
	} catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory = _T("#__e_no_mem: creating command cache failed"); }
#endif
}

TError&  CCmd_Handler::Error (void) const { return this->m_error; }

bool CCmd_Handler::Has_cmd (const uint32_t _u_cmd_id) const {
	_u_cmd_id;
	return (e_cmd_ids)_u_cmd_id != e_cmd_ids::e__undef;
}

err_code CCmd_Handler::On_command (const uint32_t _cmd_id) {
	_cmd_id;
	this->m_error <<__METHOD__<<__s_ok;

	switch (_cmd_id) {
	case e_cmd_ids::e_clear: {
		cmds::CCmd_Clear cmd;
		if (__failed(cmd.Exec()))
			this->m_error = cmd.Error();
	} break;
	default:
		this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: command ID 0x%04x (%u)"), _cmd_id, _cmd_id);
	}

	return this->Error();
}

#pragma endregion
#pragma region cls::CIcon{}

using CIcon = CFrame::CIcon;

CIcon& CIcon::operator <<(const uint16_t _res_id) {
	_res_id;
	::SendMessage(TConAccess(), WM_SETICON, 0, (l_param) CLoader().Load(_res_id, 0));
	::SendMessage(TConAccess(), WM_SETICON, 1, (l_param) CLoader().Load(_res_id, 1));
	return *this;
}

#pragma endregion
#pragma region cls::CCondole{}

CConsole:: CConsole (void) : m_con_wnd(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }
CConsole::~CConsole (void) {}

err_code CConsole::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == !!::AllocConsole()) // on closing the app process the console is destroyed by OS;
		 return this->m_error.Last();
	
	this->m_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;
	this->Frame().OnCreate();

	CLayout layout;
	if (__failed(layout.OnCreate()))
		this->m_error = layout.Error();
	
	return this->Error();
}

err_code CConsole::Close (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) // it is supposed the all opened file descriptors is already closed;
		return this->m_error << __e_not_inited;

	CLayout layout; layout.OnClose();

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
const
CFrame&  CConsole::Frame (void) const { return this->m_frame; }
CFrame&  CConsole::Frame (void)       { return this->m_frame; }

HWND CConsole::Handle (void) const { return this->m_con_wnd; }

bool CConsole::Is_valid (void) const {
	return (0 != this->m_con_wnd && ::IsWindow(this->m_con_wnd));
}

TError& CConsole::Error (void) const { return this->m_error; }

CConsole::operator const HWND (void) const { return this->Handle(); }

#pragma endregion
#pragma region cls::CFrame{}

CFrame::CFrame (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

void CFrame::Caption (_pc_sz _p_cap) {
	_p_cap;
	this->m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowtextw ;
	if (0 == ::SetWindowText(CAccessor(), _p_cap)) { this->m_error.Last(); __trace_err_ex_2(this->Error());}
}

CString  CFrame::Caption_Dflt (const e_print _e_opt/* = e_print::e_all*/) const {
	_e_opt;
#if defined(WIN64)
	static _pc_sz p_pat_a = _T("cls::[%s::%s] %s Trace (64-bits)");
#else
	static _pc_sz p_pat_a = _T("cls::[%s::%s] %s Trace (86-bits)");
#endif

	CString cs_out; cs_out.Format(p_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, _T("\u00a4")); // \u002d ;
	return  cs_out;
}

TError& CFrame::Error (void) const { return this->m_error; }
const
CFrame::CIcon&  CFrame::Icon (void) const { return this->m_icon; }
CFrame::CIcon&  CFrame::Icon (void)       { return this->m_icon; }

err_code CFrame::OnCreate (void) {
	this->m_error <<__METHOD__<<__s_ok;
	// https://devblogs.microsoft.com/oldnewthing/20100604-00/?p=13803 << Raymond Chen ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmenu ;
	HMENU sys_mnu = ::GetSystemMenu(CAccessor(), false); sys_mnu;
#if (1)
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enablemenuitem ;
	if (-1 == ::EnableMenuItem (sys_mnu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED))
		__trace_err_ex_2(this->m_error <<__e_inv_arg = _T("#__e_inv_arg: 'SC_CLOSE' menu item not found"));
#elif (false == true) // doesn't work;
	if (0 == ::RemoveMenu (sys_mnu, MF_BYCOMMAND, SC_CLOSE))
		__trace_err_ex_2(this->m_error(TError::e_get_last));
#else
#endif
	::SetWindowLong(CAccessor(), GWL_STYLE, ::GetWindowLong(CAccessor(), GWL_STYLE) & ~WS_MAXIMIZEBOX);

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawmenubar ;
	if (0 == ::DrawMenuBar(CAccessor()))
		__trace_err_ex_2(this->m_error(TError::e_get_last));

	return this->Error();
}

#pragma endregion
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

TCmdHandler&  ::Get_ConHandler (void) {
	static TCmdHandler handler;
	return handler;
}