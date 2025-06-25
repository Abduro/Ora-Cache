/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 06:10:18.030, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib data providers' unit test interface declaration file; 
*/
#include "ebo_test_$9$.msxml.data.h"

using namespace ebo::boo::test::xml;

/////////////////////////////////////////////////////////////////////////////

CFileData:: CFileData (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFileData::Load (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CLocator:: CLocator (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CLocator::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_locator.Print(e_print::e_all));

	_out()();

}

void CLocator::Refresh (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	
	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_locator.Print(e_print::e_all));

	if (__failed(this->m_locator.Refresh(TLocator::e_dll)) || false == this->m_locator.Is_valid()) {
		_out() += TStringEx().Format(_T("file://%s%s"), this->m_locator.Path(), this->m_locator.File());
		_out() += this->m_locator.Error().Print(TError::e_print::e_req);
	}
	else
		_out() += TStringEx().Format(_T("*after* :%s"), (_pc_sz) this->m_locator.Print(e_print::e_all));

	_out()();

}