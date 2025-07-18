/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 13:19:23.132, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI in-memory draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.zbuf.h"

using namespace ebo::boo::test::draw;

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

/////////////////////////////////////////////////////////////////////////////

CMode:: CMode (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CMode::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_mode.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CMode::Get (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CFake_Wnd fake_wnd(true);

	if (fake_wnd.Error().Is()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	this->m_mode << fake_wnd.Ctx();
	this->m_mode.Get();

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_mode.Print(e_print::e_all));
	_out()();
}

void CMode::Set (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_mode.Print(e_print::e_all));

	CFake_Wnd fake_wnd(true);

	if (fake_wnd.Error().Is()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	this->m_mode << fake_wnd.Ctx();
	this->m_mode.Get();

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_mode.Print(e_print::e_all));

	CError err_; err_ << this->m_mode.Set(TMode::e_advanced);
	if (err_.Is()) {
		_out() += err_.Print(TError::e_print::e_req);
	}

	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_mode.Print(e_print::e_all));

	_out()();
}