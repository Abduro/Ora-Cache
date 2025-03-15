/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-May-2024 at 05:33:45.5461699, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack system structured exception handling (SEH) unit test case implementation declaration file;
*/
#include "test_$1$_std_except.h"

using namespace ebo::boo::test;

/////////////////////////////////////////////////////////////////////////////

TTestCases:: CCases (void) {}
TTestCases::~CCases (void) {}

/////////////////////////////////////////////////////////////////////////////

void TTestCases::_0 (void) const {
	try
	{
		_out().Cache() += TString().Format(_T("%s::%s"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
//		_out_t << _T( "In __try, about to force exception\n" );
		int x = 5;
		int y = 0;
		int *p = &y;
		*p = x / *p;
	}
	catch (...)
	{
//		_out_t << _T("In __finally\n" );
	}
}

void TTestCases::_1 (void) const {
	try
	{
		_out().Cache() += TString().Format(_T("%s::%s"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		static _pc_sz p_sz_pat = _T("%1;%2");
		CString cs_out;
		cs_out.Format(p_sz_pat, 1, 2);
	}
	catch (...)
	{
	}
}

/////////////////////////////////////////////////////////////////////////////

CThrow:: CThrow (void) { m_error >> __CLASS__ << __METHOD__; }
CThrow::~CThrow (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CThrow::Do (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	CTranslator trans;

	try {
		CThrow::Case_0();
	}
	catch (const CException& _ex) {
		_ex;
		this->m_error << TErrCodes::eExecute::eInternal = (_pc_sz) _ex.ToString();
	}

	return this->Error();
}

TError&      CThrow::Error (void) const { return this->m_error; }

const
TTestCases&  CThrow::Cases (void) const { return this->m_cases; }
TTestCases&  CThrow::Cases (void)       { return this->m_cases; }

/////////////////////////////////////////////////////////////////////////////

void CThrow::Case_0 (void) {
	__try
	{
		_out_t << _T( "In __try, about to force exception\n" );
		int x = 5;
		int y = 0;
		int *p = &y;
		*p = x / *p;
	}
	__finally
	{
		_out_t << _T("In __finally\n" );
	}
}