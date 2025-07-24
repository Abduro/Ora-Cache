/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jul-2025 at 19:28:25.012, UTC+4, Batumi, Thursday;
	This is Ebo Pack custom draw helpers' interface implementation file; 
*/
#include "ebo_test_$d$.draw.case.h"

using namespace ebo::boo::test::cases;

/////////////////////////////////////////////////////////////////////////////

CFake_Wnd:: CFake_Wnd (const bool _b_verb) : m_verb(_b_verb), m_h_dc(nullptr) {
	if (this->m_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	TBase::Create(HWND_MESSAGE);

	if (false == TBase::IsWindow())
		this->m_error.Last();
	else
		this->m_error << __s_ok;
	if (this->Error())
		_out() += this->Error().Print(TError::e_print::e_req);
	else
		this->m_h_dc = TBase::GetDC(); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdc ;
		// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-with-the-mouse :-D
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowdc >> is not necessary yet;
	_out()();
}

CFake_Wnd::~CFake_Wnd (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (nullptr != this->m_h_dc) {
		TBase::ReleaseDC(this->m_h_dc);
		this->m_h_dc = nullptr;
	}

	if (TBase::IsWindow())
		TBase::DestroyWindow();
	_out()();
}

/////////////////////////////////////////////////////////////////////////////
const
HDC&     CFake_Wnd::Ctx   (void) const { return this->m_h_dc; }

TError&  CFake_Wnd::Error (void) const { return this->m_error; }

CFake_Wnd::operator const HDC& (void) const { return this->Ctx(); }