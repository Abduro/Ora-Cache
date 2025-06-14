/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jun-2025 at 09:33:15.034, UTC+4, Batumi, Saturday;
	This is Ebo pack system shell base wrapper library unit test implementation file; 
*/
#include "ebo_test_$4$.shell.h"

using namespace ebo::boo::test::shell;

/////////////////////////////////////////////////////////////////////////////

CFonts:: CFonts (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFonts::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_fonts.Print(e_print::e_all));
	_out()();

}

void CFonts::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_fonts.GetInstalled();

	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_fonts.Print(e_print::e_all));
	_out()();

}