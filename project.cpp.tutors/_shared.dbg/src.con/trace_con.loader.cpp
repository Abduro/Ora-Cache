/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Mar-2026 at 16:08:36.312, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL trace console loader interface implementation file.
*/
#include "trace_con.loader.h"
#include "trace_con.res.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "sys.registry.h"
#include "win.gui.wnd.h"

using namespace shared::console;

namespace shared { namespace console { namespace _impl {

	class CAccessor {
	public:
		 CAccessor (void) = default;  CAccessor (const CAccessor&) = delete; CAccessor (CAccessor&&) = delete;
		~CAccessor (void) = default;

		HWND operator ()(void) const {

			const HWND h_wnd = ::GetConsoleWindow();
			if (0 == h_wnd) {
				CError error(__CLASS__, __METHOD__, (err_code)TErrCodes::eExecute::eState);
				error = _T("There is *no* association with console process");
				__trace_err_ex_3(error);
			}
			return h_wnd;
		}

	private:
		CAccessor& operator = (const CAccessor&) = delete; CAccessor& operator = (CAccessor&&) = delete;
	};

	// https://stackoverflow.com/questions/2986853/is-there-a-way-to-change-the-console-icon-at-runtime ;
	typedef int32_t (_stdcall *pfn_SetIcon)(HICON);

	class CIcons {
	public:
		 CIcons (void) = default; CIcons (const CIcons&) = delete; CIcons (CIcons&&) = delete;
		~CIcons (void) = default;

		static
		err_code Set (const uint16_t _u_res_id, CError& _err) {
			_u_res_id; _err;
			using CIcon = ex_ui::resource::CIcon;

			HMODULE h_kernel = ::GetModuleHandle(_T("kernel32.dll"));
			pfn_SetIcon p_fun = (pfn_SetIcon)::GetProcAddress(h_kernel, "SetConsoleIcon");
			if (0 == p_fun) {
				::FreeLibrary(h_kernel);
				return _err << (err_code) TErrCodes::eExecute::eAddress = _T("Requested function is not found");
			}
			p_fun(ex_ui::resource::CIcon().Load(_u_res_id, 0));
			p_fun(ex_ui::resource::CIcon().Load(_u_res_id, 1));

			::FreeLibrary(h_kernel);
			return _err;
		}

	private:
		CIcons& operator = (const CIcons&) = delete; CIcons& operator = (CIcons&&) = delete;
	};


}}} using namespace shared::console::_impl;
#pragma region cls::CPers{}

CPers:: CPers (void) : TBase(), m_timer(*this) { TBase::m_error >>__CLASS__; }
CPers::~CPers (void) { this->m_timer.Destroy(); }

err_code CPers::Load (void) {
	TBase::Load();
	const t_rect rc_pos = TBase::Get();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
	::SetWindowPos(CAccessor()(), 0, rc_pos.left, rc_pos.top, rc_pos.right - rc_pos.left, rc_pos.bottom - rc_pos.top, 0);

	static const uint32_t n_interval = 6666; // the interval is just for test purposes;

	m_timer.Create(n_interval); // the interval is just for test purposes;

	return TBase::Error();
}

void CPers::IWaitable_OnComplete (void) {
	TBase::Save();
}

#pragma endregion
#pragma region cls::CLoader{}

CLoader::CLoader (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CLoader::Do_it (void) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	/* it is assumed the console window is created as the result of:
	(1) trace console project main() is called;
	(2) or AllocConsole() is called;
	in any way this process must be "associated" with console process;
	*/
	CString cs_cap; cs_cap.LoadString(IDS_TRACE_CON_CAP);

	::SetWindowText(CAccessor()(), (_pc_sz) cs_cap);
#if (1)
	using  CIcons = shared::gui::CFrame::CIcons;
	return CIcons::Set(IDR_TRACE_CON_0_ICO, CAccessor()(), this->m_error);
#else
	return CIcons::Set(IDR_TRACE_CON_0_ICO, this->m_error);
#endif
}

TError&  CLoader::Error (void) const { return this->m_error; }

#pragma endregion