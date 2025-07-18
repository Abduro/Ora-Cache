/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 16:48:36.208, UTC+4, Batumi, Friday;
	This is Ebo pack system shell processor list  wrapper library unit test implementation file; 
*/
#include "ebo_test_$4$.shell.proc.h"

using namespace ebo::boo::test::shell;

/////////////////////////////////////////////////////////////////////////////

CProcess:: CProcess (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CProcess::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_process.Print(e_print::e_all));
	_out()();

}


/////////////////////////////////////////////////////////////////////////////

CProcess_List:: CProcess_List (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CProcess_List::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_proc_list.Print(e_print::e_all));
	_out()();

}

void CProcess_List::Get_It (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);


	this->m_proc_list.Get_It();
	if (this->m_proc_list.Error().Is()) {
		_out() += this->m_proc_list.Error().Print(CError::e_print::e_all);
	}
	else {
		
	}
	const TProc_map& proc_list = this->m_proc_list.Raw();
	const size_t n_count = proc_list.size();
	
	_out() += TStringEx().Format(_T("Processes: %u"), n_count);
#if (0)
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_proc_list.Print(e_print::e_all));
#endif
	_out()();

}