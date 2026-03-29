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

CPers:: CPers (void) : m_timer(*this) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CPers::~CPers (void) { this->m_timer.Destroy(); }

TError&  CPers::Error (void) const { return this->m_error; }
err_code CPers::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using namespace ex_ui::popup::layout;

	TRegKeyEx the_key;
	t_rect rc_ = { // this is not working on multi-monitor system, because it doesn't allow negative values;
		(long)the_key.Value().GetDword(_T("left")),
		(long)the_key.Value().GetDword(_T("top")),
		(long)the_key.Value().GetDword(_T("right")),
		(long)the_key.Value().GetDword(_T("bottom")),
	};

	if (::IsRectEmpty(&rc_)) { // the position of the console window is not saved yet;
		t_size_u size = CPrimary().Default();
		rc_ = CPrimary().Centered(size);
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
	::SetWindowPos(CAccessor()(), 0, rc_.left, rc_.top, rc_.right - rc_.left, rc_.bottom - rc_.top, 0);

	m_timer.Create(30);

	return this->Error();
}

err_code CPers::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowrect ;
	t_rect rc_ = {0};

	if (false == !!::GetWindowRect(CAccessor()(), &rc_))
		return this->m_error.Last();

	TRegKeyEx the_key;
	the_key.Value().Set(::Get_reg_router().Trace().Root(), _T("left"), ::abs(rc_.left));
	the_key.Value().Set(::Get_reg_router().Trace().Root(), _T("top"), ::abs(rc_.top));
	the_key.Value().Set(::Get_reg_router().Trace().Root(), _T("right"), ::abs(rc_.right));
	the_key.Value().Set(::Get_reg_router().Trace().Root(), _T("bottom"), ::abs(rc_.bottom));

	return this->Error();
}

void CPers::IWaitable_OnComplete (void) {
	this->Save();
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
#if (1)
	using  CIcons = shared::gui::CFrame::CIcons;
	return CIcons::Set(IDR_TRACE_CON_0_ICO, CAccessor()(), this->m_error);
#else
	return CIcons::Set(IDR_TRACE_CON_0_ICO, this->m_error);
#endif
}

TError&  CLoader::Error (void) const { return this->m_error; }

#pragma endregion