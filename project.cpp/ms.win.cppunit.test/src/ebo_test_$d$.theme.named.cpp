/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:36:15.405, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme named interface unit test implementation file; 
*/
#include "ebo_test_$d$.theme.named.h"

using namespace ebo::boo::test::themes;

/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CNamed::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CNamed_Enum::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named_enum.Print(e_print::e_all));
	_out()();

}

void CNamed_Enum::Load (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_named_enum.Load();

	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named_enum.Print(e_print::e_all));
	_out()();

}