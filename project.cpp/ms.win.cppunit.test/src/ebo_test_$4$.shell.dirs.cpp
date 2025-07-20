/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:21:58.828, UTC+4, Batumi, Friday;
	This is Ebo pack system shell generic folder wrapper library unit test implementation file; 
*/
#include "ebo_test_$4$.shell.dirs.h"
#if (0)
#include "uix.theme.named.h"
#include "uix.theme.reg.h"
#else
#include "ebo_test_$d$.theme.case.h"
#endif
using namespace ebo::boo::test::shell;
#if (0)
using namespace ex_ui::theme;
using namespace ex_ui::theme::storage;
#else
using namespace ebo::boo::test::cases;
#endif

/////////////////////////////////////////////////////////////////////////////

CFolder:: CFolder (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_emp_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFolder::_ctor (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("%s"), (_pc_sz) this->m_folder.Print(e_print::e_all));
	_out()();

}

void CFolder::EnumItems (void) {

	_out() += TLog_Acc::e_emp_line;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("*before*: %s"), (_pc_sz) this->m_folder.Print(e_print::e_all));

	CBase case_bs;

	_out() += _T("Reading the test cases root folder path:");

	if (__failed(case_bs.Root().Set())) {
		_out() += case_bs.Root().Error().Print(TError::e_print::e_req);
		_out()(); return;
	}
	CString cs_root = case_bs.Root().Get();

	_out() += cs_root;

	_out() += _T("Setting the test cases root folder path:");

	if (__failed(this->m_folder.Path(cs_root))) {
		_out() += this->m_folder.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}
	_out() += _T("The path is set successfully;");
	_out() += _T("Enumerating the test cases image files...");

	if (__failed(this->m_folder.EnumItems(_T("png")))) {
		_out() += this->m_folder.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += TString().Format(_T("*after *: %s"), (_pc_sz) this->m_folder.Print(e_print::e_all));

	_out()();

}