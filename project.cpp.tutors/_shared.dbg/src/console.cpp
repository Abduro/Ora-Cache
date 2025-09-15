/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Sep-2020 at 6:58:28p, UTC+7, Novosibirsk, Thursday;
	This is FakeGPS driver version 2 desktop client console interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to Wanderer Path Finder project on 6-Jan-2021 at 11:46:09.018 am, UTC+7, Novosibirsk, Tuesday;
	Adopted to Yandex Wanderer project on 12-Dec-2022 at 11:21:30.7989254, UTC+7, Novosibirsk, Monday;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include <io.h>       // for _open_osfhandle ;
#include <fcntl.h>    // for constant decl, like to _O_TEXT ;

#include "shared.preproc.h"
#include "console.h"
#include "console.out.h"

using namespace shared::console;

namespace shared { namespace console  { namespace _impl {

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif

#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

	class CScreenBuffer {
		CScreenBuffer (const CScreenBuffer&) = delete; CScreenBuffer (CScreenBuffer&&) = delete;
	public:
		CScreenBuffer (void) : m_info{0} { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		TError&  Error(void) const { return this->m_error; }

		const
		TScrBufInfo& Get (void) const {
			this->m_error >>__METHOD__<<__s_ok;
			
			// https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo ;
			if (0 == ::GetConsoleScreenBufferInfo (__out_handle, &this->m_info))
				this->m_error.Last();

			return this->m_info;
		}

		err_code Set (void) {

			COORD n_size =  m_info.dwSize;
			n_size.X *= 2;
			
			::SetConsoleScreenBufferSize(__out_handle, n_size);
			return this->Error();
		}

		operator const TScrBufInfo& (void) const { return this->m_info; }
		operator       TScrBufInfo& (void)       { return this->m_info; }

		TScrBufInfo    operator ()  (void) { this->Get(); return this->m_info; }

	private:
		CScreenBuffer& operator = (const CScreenBuffer&) = delete; CScreenBuffer& operator = (CScreenBuffer&&) = delete;
		mutable CError m_error;
		mutable TScrBufInfo m_info;
	};

}}}

using namespace shared::console::_impl;

/////////////////////////////////////////////////////////////////////////////

CConsole:: CConsole (void) : m_con_wnd(0), m_streams{0} { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CConsole::~CConsole (void) {
	this->Close(); // if it was called before the returned error code is ignored;
}

err_code   CConsole::Close (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) // it is supposed the all opened file descriptors is already closed;
		return this->m_error << __e_not_inited;

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/get-osfhandl ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fclose-fcloseall ;

	for (uint32_t i_ = 0; i_ < _countof(this->m_streams); i_++) {
		if (nullptr == this->m_streams[i_])
			continue;
		if (0 != ::fclose(this->m_streams[i_])) {
			CString cs_stream;

			if (0 == i_) cs_stream = _T("std_input_stream");
			if (1 == i_) cs_stream = _T("std_output_stream");
			if (2 == i_) cs_stream = _T("std_err_stream");

			this->m_error << __e_fail = TString().Format(_T("Close '%s' is failed"), (_pc_sz) cs_stream); // it saves the last error only;
		}
		else
			this->m_streams[i_] = nullptr;
	}

	// ::setvbuf() is used for setting the stream operation(s); it is not required to manage these buffers due to they are opened with _IONBF option;
#if (0)
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ; throws the system error 'Access denied';
	if (0 == ::DestroyWindow(this->m_con_wnd))
		return this->m_error.Last();
#endif
	this->m_con_wnd = 0;

	return this->Error();
}

err_code   CConsole::Open  (const HWND _h_parent, const t_rect& _rect_wnd_pos, const bool _b_visible) {
	_h_parent; _rect_wnd_pos; _b_visible;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (0 == _h_parent || false == !!::IsWindow(_h_parent))
		return this->m_error << __e_hwnd = _T("Parent window handle is invalid");

	if (::IsRectEmpty(&_rect_wnd_pos))
		return this->m_error << __e_rect = _T("The input rectangle is empty");

	if (false == !!::AllocConsole())
		return this->m_error.Last();
	else
		this->m_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;

	// (0) hides the console window first;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow ;
	::ShowWindow(this->m_con_wnd, SW_HIDE); // it looks like this function does not return the error code, but what is expected if input handle is invalid?

	// (1) customizes the console for being a child window of the parent one, i.e. the main/app window;
	// (1.a) removes caption and borders of the window frame;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowlongptrw ;
	LONG_PTR lp_style = ::GetWindowLongPtr(this->m_con_wnd, GWL_STYLE);
	lp_style &= ~(WS_CAPTION|WS_THICKFRAME|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX);
//	lp_style |=   WS_CHILD; // it is not necessary because the console window can never be as a child window; (conhost.exe);
	lp_style |=   WS_HSCROLL;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw ;
	::SetWindowLongPtr(this->m_con_wnd, GWL_STYLE, lp_style);

	// (1.b) applies new style to the console window; the flag 'SWP_FRAMECHANGED' is the most important;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
	::SetWindowPos(
		this->m_con_wnd, 0, _rect_wnd_pos.left, _rect_wnd_pos.top, __W(_rect_wnd_pos), __H(_rect_wnd_pos), SWP_FRAMECHANGED|SWP_NOACTIVATE|SWP_NOZORDER
	);

	// (2) sets output/read handle
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/open-osfhandle ;
	{
		const intptr_t cin_ = reinterpret_cast<intptr_t>(::GetStdHandle(STD_INPUT_HANDLE));
		const INT input_ = ::_open_osfhandle(cin_, _O_TEXT );
		FILE* p_file_in = ::_fdopen(input_, "r");

		::setvbuf( p_file_in, 0, _IONBF, 0 ); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/setvbuf ;
	}
	// (3) sets input/write handle
	{
		const intptr_t out_ = reinterpret_cast<intptr_t>(::GetStdHandle(STD_OUTPUT_HANDLE));
		const INT output_ = ::_open_osfhandle(out_, _O_TEXT );
		FILE* p_file_out = ::_fdopen(output_, "w");

		::setvbuf( p_file_out, 0, _IONBF, 0 );
	}
	// (4) sets error handle
	{
		const intptr_t err_ = reinterpret_cast<intptr_t>(::GetStdHandle(STD_ERROR_HANDLE));
		const INT error_ = ::_open_osfhandle(err_, _O_TEXT );
		FILE* p_file_err = ::_fdopen(error_, "w");

		::setvbuf( p_file_err, 0, _IONBF, 0 );
	}

	// (5) shows the console window at final step of the creating procedure;
	::ShowWindow(this->m_con_wnd, SW_SHOW);

	// https://learn.microsoft.com/en-us/windows/console/console-functions ;
	// https://learn.microsoft.com/en-us/windows/console/writeconsole ;
#if (0)
	COut::Error(_T("this is the error;\n"));
	COut::Info (_T("this is the info;\n"));
	COut::Warn (_T("this is the warn;\n"));
#else
	// https://cplusplus.com/forum/windows/58206/ ; how to make thisngs better: redirect ::std::ios to this console;
#endif
	return this->Error();
}

HWND   CConsole::Handle (void) const { return this->m_con_wnd; }

bool   CConsole::Is_valid (void) const {
	return (0 != this->m_con_wnd && ::IsWindow(this->m_con_wnd));
}

TError&    CConsole::Error (void) const { return this->m_error; }

CConsole::operator const HWND (void) const { return this->Handle(); }

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

TError&   CLayout::Error (void) const { return this->m_error; }
const
CLayout::COutput& CLayout::Output (void) const { return this->m_output; }
CLayout::COutput& CLayout::Output (void)       { return this->m_output; }

/////////////////////////////////////////////////////////////////////////////

CLayout::COutput:: COutput (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

TError&   CLayout::COutput::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

CLayout::COutput::CHScroll:: CHScroll (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

TError&  CLayout::COutput::CHScroll::Error (void) const { return this->m_error; }

bool CLayout::COutput::CHScroll::Get (void) const {

	CScreenBuffer buff;
	if (__failed( buff.Set()))
		return false;

	LONG_PTR lp_style = ::GetWindowLongPtr(::GetConsoleWindow(), GWL_STYLE);
	return   lp_style & WS_HSCROLL;
}

err_code CLayout::COutput::CHScroll::Set (const bool _b_set) {
	_b_set;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_has = this->Get();
	if (_b_set == true && b_has == true)
		return this->Error();

	if (_b_set == false && b_has == false)
		return this->Error();

	// https://learn.microsoft.com/en-us/windows/console/getconsolescreenbufferinfo ;
	CONSOLE_SCREEN_BUFFER_INFO con_info = {0};

	if (false == !!::GetConsoleScreenBufferInfo(__out_handle, &con_info))
		return this->m_error.Last();

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
	t_rect rc_client = {0};
	if (0 == ::GetClientRect(::GetConsoleWindow(), &rc_client))
		return this->m_error.Last();

	const int n_req = __W(rc_client) / con_info.dwSize.X;

	if (_b_set) {
		con_info.dwSize.X = static_cast<int16_t>(con_info.dwSize.X * 2);
	}
	else {
		con_info.dwSize.X = static_cast<int16_t>(con_info.dwSize.X / 2);
	}

	// https://learn.microsoft.com/en-us/windows/console/setconsolescreenbuffersize ;
	if (0 == ::SetConsoleScreenBufferSize(__out_handle, con_info.dwSize))
		this->m_error.Last();

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

const
CLayout::COutput::CHScroll&  CLayout::COutput::HScroll (void) const { return this->m_h_scroll; }
CLayout::COutput::CHScroll&  CLayout::COutput::HScroll (void)       { return this->m_h_scroll; }