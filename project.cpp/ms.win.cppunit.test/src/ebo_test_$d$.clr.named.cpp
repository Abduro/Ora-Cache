/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:22:12.428, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw named color unit test interface implementation file; 
*/
#include "ebo_test_$d$.clr.named.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::color::named;

/////////////////////////////////////////////////////////////////////////////

CNamed::CNamed (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CNamed::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TNamedColor(TRgbColor(0), _T("#fake_named")).Print(::e_print::e_all);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CNamed_X11::CNamed_X11 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CNamed_X11::_ctor (void) {

	const TNamedClrRaw& named_raw = TX11_Named::Ref().Raw();

	_out() += TLog_Acc::e_new_line;

	for (TNamedClrRaw::const_iterator it_ = named_raw.begin(); it_ != named_raw.end(); ++it_) {
		const TNamedColor& named_clr = it_->second;
		_out() += named_clr.Print(::e_print::e_req);
	}

	_out().Cached()();
}