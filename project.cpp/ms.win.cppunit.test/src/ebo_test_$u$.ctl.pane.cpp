/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Jul-2025 at 13:21:01.682, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base pane unit test interface implementation file;
*/
#include "ebo_test_$u$.ctl.pane.h"

using namespace ebo::boo::test::ctl::base;

/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPane::_ctor (void) {

//	_out() += TLog_Acc::e_emp_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
//	_out() += TString().Format(_T("_ctor: %s"), (_pc_sz) /*this->m_pane*/TPane().Print(e_print::e_all));
	_out() += TPane().Print(e_print::e_all);
	_out()();

}