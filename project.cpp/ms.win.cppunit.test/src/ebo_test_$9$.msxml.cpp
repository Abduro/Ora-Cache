/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 04:03:04.902, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib unit test interface implementation file; 
*/
#include "ebo_test_$9$.msxml.h"

using namespace ebo::boo::test::xml;

/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////

CErr_Pos:: CErr_Pos (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CErr_Pos::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_err_pos.Print(e_print::e_all));
	_out()();

}

void CErr_Pos::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_err_pos.Print(e_print::e_all));

	bool b_changed = false;

	if (this->m_err_pos.Col(33)) b_changed = true;
	if (this->m_err_pos.Offset(66)) b_changed = true;
	if (this->m_err_pos.Row(55)) b_changed = true;

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *: %s; changed=%s;"), (_pc_sz) this->m_err_pos.Print(e_print::e_all), (_pc_sz) cs_changed );

	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CParseError:: CParseError (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CParseError::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_prs_err.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CServiceId:: CServiceId (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CServiceId::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_svc_id.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CSvc_Ids:: CSvc_Ids (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CSvc_Ids::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_svc_ids.Print(e_print::e_all));
	_out()();

}