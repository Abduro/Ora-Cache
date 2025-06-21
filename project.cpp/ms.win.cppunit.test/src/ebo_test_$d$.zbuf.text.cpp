/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 07:49:47.460, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI text output classes' unit test interface implementation file;
*/
#include "ebo_test_$d$.zbuf.text.h"

using namespace ebo::boo::test::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace draw { namespace text { namespace vertical {

CAlign_H:: CAlign_H (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_H::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign_V:: CAlign_V (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_V::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_v.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out()();
}

void CAlign::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	CFake_Wnd fake_wnd(true);

	if (fake_wnd.Error().Is()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	this->m_align << fake_wnd.Ctx();
	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	}

	_out()();
}

}}}}}}