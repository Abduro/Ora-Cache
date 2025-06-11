/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2025 at 09:36:43.277, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base layout unit test interface implementation file;
*/
#include "ebo_test_$u$.ctl.layout.h"

using namespace ebo::boo::test::ctl::base;
using namespace ebo::boo::test::ctl::layout;

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

/////////////////////////////////////////////////////////////////////////////

CGap:: CGap (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CGap::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_gap.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CGaps_of_rect:: CGaps_of_rect (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CGaps_of_rect::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_gaps.Print(e_print::e_all));
	_out()();

}

void CGaps_of_rect::ApplyMargins (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_gaps.Set(-10, -20, +10, +20);
	_out() += TStringEx().Format(_T("*margins* : %s"), (_pc_sz) this->m_gaps.Print(e_print::e_all));

	TRect rect_;
	t_rect rect_input{40, 80, 40, 80}; rect_ << rect_input; // ToDo: static Print(const t_rect&) would be useful;

	_out() += TStringEx().Format(_T("*before* : %s"), (_pc_sz) rect_.Print(e_print::e_all));

	t_rect rect_margins = rect_.Get(); this->m_gaps.ApplyTo(rect_margins); rect_ << rect_margins;
	_out() += TStringEx().Format(_T("*after*  : %s"), (_pc_sz) rect_.Print(e_print::e_all));

	_out()();
}

void CGaps_of_rect::ApplyPadding (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_gaps.Set(+10, +20, -10, -20);
	_out() += TStringEx().Format(_T("*padding* : %s"), (_pc_sz) this->m_gaps.Print(e_print::e_all));

	TRect rect_;
	t_rect rect_input{40, 80, 40, 80}; rect_ << rect_input;

	_out() += TStringEx().Format(_T("*before* : %s"), (_pc_sz) rect_.Print(e_print::e_all));

	t_rect rect_padding = rect_.Get(); this->m_gaps.ApplyTo(rect_padding); rect_ << rect_padding;
	_out() += TStringEx().Format(_T("*after*  : %s"), (_pc_sz) rect_.Print(e_print::e_all));

	_out()();
}