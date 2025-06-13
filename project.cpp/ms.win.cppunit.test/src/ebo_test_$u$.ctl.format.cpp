/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2025 at 09:46:37.004, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base format unit test interface implementation file;
*/
#include "ebo_test_$u$.ctl.format.h"

using namespace ebo::boo::test::ctl::base;
using namespace ebo::boo::test::ctl::format;

/////////////////////////////////////////////////////////////////////////////

CBase:: CBase (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBase::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_base.Print(e_print::e_all));
	_out()();

}

void CBase::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before* : %s"), (_pc_sz) this->m_base.Print(e_print::e_all));

	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow);

	_out() += TLog_Acc::e_new_line;
	const TRgbQuad lo_(set_.Dark());
	const TRgbQuad hi_(set_.Light());

	_out() += TStringEx().Format(_T("*gradient* : from %s to %s"), (_pc_sz) lo_.Print(e_print::e_all),  (_pc_sz) hi_.Print(e_print::e_all));

	this->m_base.Bkgnd().Gradient().Set(lo_.ToRgb(), hi_.ToRgb());

	_out() += TStringEx().Format(_T("*after * : %s"), (_pc_sz) this->m_base.Print(e_print::e_all));
	
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CBkgnd:: CBkgnd (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CBkgnd::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_bkgnd.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CFontOpts:: CFontOpts (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFontOpts::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_opts.Print(e_print::e_all));
	_out()();

}

void CFontOpts::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before* : %s"), (_pc_sz) this->m_opts.Print(e_print::e_all));
	_out() += TStringEx().Format(_T("*adding* : %s"), (_pc_sz) TFontOpts::Print(TFontOpts::eExactSize | TFontOpts::eUnderline));

	this->m_opts += TFontOpts::eExactSize;
	this->m_opts += TFontOpts::eUnderline;

	_out() += TStringEx().Format(_T("*after * : %s"), (_pc_sz) this->m_opts.Print(e_print::e_all));
	_out() += TStringEx().Format(_T("*remove* : %s"), (_pc_sz) TFontOpts::Print(TFontOpts::eUnderline));

	this->m_opts -= TFontOpts::eUnderline;
	_out() += TStringEx().Format(_T("*result* : %s"), (_pc_sz) this->m_opts.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CFontSpec:: CFontSpec (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFontSpec::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_spec.Print(e_print::e_all));
	_out()();

}

void CFontSpec::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_spec.Print(e_print::e_all));
	_out()();

}