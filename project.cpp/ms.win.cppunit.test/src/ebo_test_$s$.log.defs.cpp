/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Jun-2025 at 12:40:36.810, UTC+4, Batumi, Friday;
	This is Ebo Pack generic events' logger lib unit test interface declaration file; 
*/
#include "ebo_test_$s$.log.defs.h"

using namespace ebo::boo::test::log;

/////////////////////////////////////////////////////////////////////////////
#if (0)
CErr_Desc:: CErr_Desc (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CErr_Desc::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_err_desc.Print(e_print::e_all));
	_out()();

}

void CErr_Desc::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_err_desc.Print(e_print::e_all));

	bool b_changed = false;

	if (this->m_err_desc.Code(13)) b_changed = true;
	if (this->m_err_desc.Reason(_T("#test_case"))) b_changed = true;
	if (this->m_err_desc.Text(_T("#bad_format"))) b_changed = true;

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *: %s; changed=%s;"), (_pc_sz) this->m_err_desc.Print(e_print::e_all), (_pc_sz) cs_changed );

	_out()();

}
#endif