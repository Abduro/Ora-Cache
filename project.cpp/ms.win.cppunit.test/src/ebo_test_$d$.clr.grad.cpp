/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:34:58.130, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw color gradient unit test interface implementation file; 
*/
#include "ebo_test_$d$.clr.grad.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::color::rgb;

/////////////////////////////////////////////////////////////////////////////

CGradient::CGradient (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CGradient::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin* : %s"), (_pc_sz) this->m_grad.Print(e_print::e_all));

	this->m_grad.From().Is() = false;

	_out() += TString().Format(_T("*changed*: %s"), (_pc_sz) this->m_grad.Print(e_print::e_all));

	_out()();
}

void CGradient::Is_valid (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin* : %s >> %s;"), (_pc_sz) this->m_grad.Print(e_print::e_all), _T("both colors are not valid"));

	this->m_grad.c0().Is() = this->m_grad.c1().Is() = true;

	_out() += TString().Format(_T("*changed* : %s >> %s;"), (_pc_sz) this->m_grad.Print(e_print::e_all), _T("both colors are transparent"));

	this->m_grad.c0().A(_Opaque);
	this->m_grad.c1().A(_Opaque);

	_out() += TString().Format(_T("*changed* : %s >> %s;"), (_pc_sz) this->m_grad.Print(e_print::e_all), _T("both colors are the same"));

	this->m_grad.c0().R(0xff);

	_out() += TString().Format(_T("*changed* : %s >> %s;"), (_pc_sz) this->m_grad.Print(e_print::e_all), _T("*good* colors"));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CGrad_strip::CGrad_strip (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CGrad_strip::_ctor(void) {

	this->m_b_verb = true;

	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin* : %s"), (_pc_sz) this->m_strip.Print(e_print::e_all));
	_out()();
}

void CGrad_strip::Modify (void) {

	this->m_b_verb = true;

	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("*origin* : %s"), (_pc_sz) this->m_strip.Print(e_print::e_all));

	TGrad tile_0(_r_g_b_a(0x00, 0x01, 0x02, 0x03), _r_g_b_a(0x04, 0x05, 0x06, 0x07));
	TGrad tile_1(_r_g_b_a(0x04, 0x05, 0x06, 0x07), _r_g_b_a(0x00, 0x01, 0x02, 0x03));

	_out() += TString().Format(_T("*added* : %s"), (_pc_sz) tile_0.Print(e_print::e_all)); this->m_strip.Add(tile_0);
	_out() += TString().Format(_T("*added* : %s"), (_pc_sz) tile_1.Print(e_print::e_all)); this->m_strip.Add(tile_1);

	_out() += TString().Format(_T("*result* : %s"), (_pc_sz) this->m_strip.Print(e_print::e_all));

	_out()();
}