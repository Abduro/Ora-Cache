/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2025 at 11:59:19.796, UTC+4, Batumi, Sunday;
	This is Ebo Pack user control base wrapper lib unit test interface implementation file;
*/
#include "ebo_test_$u$.ctl.base.h"

using namespace ebo::boo::test::ctl::base;

/////////////////////////////////////////////////////////////////////////////

CMargin:: CMargin (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CMargin::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("_ctor: %s"), (_pc_sz) this->m_margin.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CBorder:: CBorder (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBorder::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("_ctor: %s"), (_pc_sz) this->m_border.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CBorders:: CBorders (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBorders::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("_ctor: %s"), (_pc_sz) this->m_bdrset.Print(e_print::e_all));
	_out()();

}

void CBorders::Modify (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("before add: %s"), (_pc_sz) this->m_bdrset.Print(e_print::e_all));

	this->m_bdrset.Add(TBorder(1));

	_out() += TStringEx().Format(_T("after add: %s"), (_pc_sz) this->m_bdrset.Print(e_print::e_all));

	_out()();
}