/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 23:45:47.448, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI generic fonts' unit test interface implementation file;
*/
#include "ebo_test_$d$.zbuf.font.h"

using namespace ebo::boo::test::draw;

/////////////////////////////////////////////////////////////////////////////

CFont_Dbg:: CFont_Dbg (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFont_Dbg::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_font.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////
// WTL::CFont is ambiguous symbol, unfortunately;

using CFont = ebo::boo::test::draw::CFont; // does not help :(

ebo::boo::test::draw::CFont:: CFont (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void ebo::boo::test::draw::CFont::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_font.Print(e_print::e_all));
	_out()();
}

void ebo::boo::test::draw::CFont::Create (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_font.Print(e_print::e_all));

	CError err_; err_ << this->m_font.Create(_T("Pirulen Rg"), TFontOpts::eExactSize, -12);
	if (err_.Is()) {
		_out() += err_.Print(CError::e_print::e_req);
	}

	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_font.Print(e_print::e_all));

	_out()();
}