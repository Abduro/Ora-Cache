/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jul-2025 at 07:41:12.248, UTC+4, Batumi, Sunday;
	This is Ebo Pack WinAPI GDI in-memory bitmap wrappers unit test interface implementation file;
*/
#include "ebo_test_$d$.zbuf.bitmap.h"

using namespace ebo::boo::test::bitmap;

CDibSection:: CDibSection (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CDibSection::_ctor (void) {
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*result*: %s"), (_pc_sz) this->m_dib.Print(e_print::e_all));
	_out()();
}

void CDibSection::Create (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*befor*: %s"), (_pc_sz) this->m_dib.Print(e_print::e_all));

	const HDC h_screen = ::GetDC(nullptr); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdc ;
	const t_size size{16,16};

	CString cs_hdc = TStringEx().__address_of(h_screen, _T("0x%08x"));
	CString cs_size = TStringEx().Format(_T("w|h:%d|%d (px)"), size.cx, size.cy);

	_out() += TStringEx().Format(_T("Input params:%sh_scr=%s%ssize=%s"), _p_new, (_pc_sz) cs_hdc, _p_new, (_pc_sz) cs_size);

	if (__failed(this->m_dib.Create(h_screen, size)))
		_out() += this->m_dib.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after* : %s"), (_pc_sz) this->m_dib.Print(e_print::e_all));

	if (h_screen) {
		::ReleaseDC(HWND_DESKTOP, h_screen);
	}
	_out()();
}