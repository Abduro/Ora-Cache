/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:32:00.806, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw complementary color unit test interface implementation file; 
*/
#include "ebo_test_$d$.clr.compl.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::color::compl;

/////////////////////////////////////////////////////////////////////////////

COne::COne (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void COne::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin*: %s"), (_pc_sz) this->m_compl.Print(e_print::e_all));

	TRgbQuad input(66,66,66,66);

	_out() += TString().Format(_T("*input* : %s"), (_pc_sz) input.Print(e_print::e_all));

	this->m_compl.Set(input.ToRgbA()); // *important*: do not use operator TRgbQuad::operator rgb_color due to it sets alpha value to opaque;

	_out() += TString().Format(_T("*result*: %s"), (_pc_sz) this->m_compl.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CSet::CSet (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CSet::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin*: %s"), (_pc_sz) this->m_set.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CEnum::CEnum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CEnum::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin*: %s"), (_pc_sz) this->m_enum.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CPredefs::CPredefs (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CPredefs::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin*: %s"), (_pc_sz) this->m_predefs.Print(e_print::e_all));

	_out()();
}