/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 06:38:02.148, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib XML document unit test interface implementation file; 
*/
#include "ebo_test_$9$.msxml.doc.h"

using namespace ebo::boo::test::xml;

/////////////////////////////////////////////////////////////////////////////

CDocument:: CDocument (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CDocument::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_x_doc.Print(e_print::e_all));
	_out()();

}

void CDocument::Create (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const err_code n_result = this->m_x_doc.Create();
	if (__failed(n_result)) {
	_out() += ((TError&)this->m_x_doc.Error()).Print(CError::e_print::e_all);
	}
	else
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_x_doc.Print(e_print::e_all));
	_out()();

}