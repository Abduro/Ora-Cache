/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Sep-2024 at 14:51:36.891, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared draw color interface implementation file; 
*/
#include "ebo_test_$d$.clr.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::color::rgb;

/////////////////////////////////////////////////////////////////////////////

void CAlpha::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TAlpha::Print(TPercent((int32_t)45)); // almost semi-transparent;
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CColor::CColor (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CColor::_ctor (void) {

	TRgbColor clr_b(_r_g_b_a(50, 50, 50, 50));

	_out() += TLog_Acc::e_new_line;
	_out() += clr_b.Print(e_print::e_all);
	_out()();
}

void CColor::Darken (void) {

	TRgbColor clr_d(_r_g_b_a(50, 50, 50, 50));

	_out() +=  TLog_Acc::e_new_line;
	_out() += _T("Making darken down to 10%...");
	_out() += TString().Format(_T("Before: %s"), (_pc_sz) clr_d.Print(e_print::e_all)); clr_d.Darken(10);
	_out() += TString().Format(_T("After : %s"), (_pc_sz) clr_d.Print(e_print::e_all));
	_out()();
}

void CColor::Differ (void) {

	const rgb_color clr_base = _r_g_b_a(50, 50, 50, 50);

	TRgbColor clr_b(clr_base);
	TRgbQuad  clr_q(clr_base);

	_out() +=  TLog_Acc::e_new_line;
	_out() += _T("Differ method can be changed or even is not required:");
	_out() += _T("(1) set color to input one;");
	_out() += _T("(2) make darken or lighten;");
	_out() += _T("(3) the distinction is made;");
	_out() +=  TString().Format(_T("Target: %s"), (_pc_sz)clr_b.Print(e_print::e_req));
	_out() +=  TString().Format(_T("Differ: %s"), (_pc_sz)clr_q.Print(e_print::e_req));
#if (1)
	uint8_t u_pct = 15 ;     // start percent value;

	for (uint8_t i_ = 0; i_ < 10; i_++) {

		uint8_t u_step = u_pct * (i_ + 1);

		clr_b.Differ(clr_q.ToRgbA(), u_step); // just increases to the next +10%; no restoring the object is made before;

		_out() += TString().Format(_T("Making differ +15%%[total=%u%%] >> %s"), u_step, (_pc_sz)clr_b.Print(e_print::e_req));
	}
	// ToDo: Differ method does not proceed in cases when input procent value greater than 100;
#else
	_out() += _T("Making differ +10%...."); clr_b.Differ(clr_q.ToRgbA(), +10);
	_out() +=  TString().Format(_T("After +10%: %s"), (_pc_sz)clr_b.Print(TRgbQuad::e_no_pfx));

	_out() += _T("Making differ -20%...."); clr_b.Differ(clr_q.ToRgbA(), -20);
	_out() +=  TString().Format(_T("After -20%: %s"), (_pc_sz)clr_b.Print(TRgbQuad::e_no_pfx));

	_out() += _T("Restore the color object..."); clr_b << clr_base << (rgb_value)50; // or simple: clr_b.Set(clr_base);
	_out() += TString().Format(_T("Target: %s"), (_pc_sz)clr_b.Print(TRgbQuad::e_no_pfx));

	_out() += _T("Making differ +90%...."); clr_b.Differ(clr_q.ToRgbA(), +90);
	_out() +=  TString().Format(_T("After +90%: %s"), (_pc_sz)clr_b.Print(TRgbQuad::e_no_pfx));
#endif
	_out()();
}

void CColor::Lighten (void) {

	TRgbColor clr_l(_r_g_b_a(50, 50, 50, 50));

	_out() +=  TLog_Acc::e_new_line;
	_out() += _T("Making lighten up to 10%...");
	_out() += TString().Format(_T("Before: %s"), (_pc_sz) clr_l.Print(e_print::e_all)); clr_l.Lighten(10);
	_out() += TString().Format(_T("After : %s"), (_pc_sz) clr_l.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CFloat::ViceVersa (void) {

	TRgbQuad  clr_in(61, 61, 61, 61);

	this->m_clr_f.Set((const clr_type)clr_in.ToRgbA());

	_out() += TStringEx().Format(_T("*input*: %s"), (_pc_sz) clr_in.Print(e_print::e_all));
	_out() += TStringEx().Format(_T("*to_float*: %s"), (_pc_sz) this->m_clr_f.Print(e_print::e_all));

	TRgbQuad  clr_out(this->m_clr_f.ToRgbA());

	_out() += TStringEx().Format(_T("*to_back* : %s"), (_pc_sz) clr_out.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CPercent::CPercent (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CPercent::_ctor(void) {

	_out() += TLog_Acc::e_new_line;
#if (1)
	_out() += TString().Format(_T("Sets negative value: -13.7; result >> %s"), (_pc_sz)TPct_Flt(-13.7f).Print());
	_out() += TString().Format(_T("Sets positive value: +13  ; result >> %s"), (_pc_sz)TPct_Flt(+13).Print());

	_out() += TString().Format(_T("Gets vaue (+13.5) as an integer; result >> %s"), (_pc_sz)TPct_Flt(13.5f).Print(TPct_Flt::e_as_int));
#else
				
	_out() += TString().Format(_T("Sets negative value: -13; result >> %s"), (_pc_sz)TPercent(-13).Print());
	_out() += TString().Format(_T("Sets positive value: +13; result >> %s"), (_pc_sz)TPercent(+13).Print());
#endif
	_out()();
}

void CPercent::Is_equal (void) {

	TPct_Flt pct_0(127.3f); // to compare as flout and int eather;
	TPct_Flt pct_1(127.5f); // to compare as flout and int eather;
	TPct_Flt pct_2(pct_1 ); // to compare as int only;
			
	// ToDo: comparing two float percent objects as integers must be made clear, without taking separate account into integer part trunctation or extraction;

	_out() += TLog_Acc::e_new_line;	
	_out() += TString().Format(
		_T("Compare as float: %s & %s >> is_equal=%s;"), (_pc_sz) pct_0.Print(), (_pc_sz) pct_1.Print(), TString().Bool(pct_0.Is_equal((float)pct_1)));

	_out() += TString().Format(
		_T("Compare as int32: %s & %s >> is_equal=%s;"), (_pc_sz) pct_0.Print(), (_pc_sz) pct_1.Print(), TString().Bool(pct_0.Is_equal((int)pct_1.GetAsInt(true),0)));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CQuad::CQuad (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CQuad::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TRgbQuad(6, 6, 6, 6).Print(e_print::e_all);
	_out()();
}

void CQuad::EqualTo (void) {

	TRgbQuad quad_0(13, 13, 13);
	TRgbQuad quad_1(14, 14, 14); TRgbQuad quad_2(quad_1);

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Quad #0: %s"), (_pc_sz)quad_0.Print(e_print::e_req));
	_out() += TString().Format(_T("Quad #1: %s"), (_pc_sz)quad_1.Print(e_print::e_req));
	_out() += TString().Format(_T("Quad #2: %s"), (_pc_sz)quad_2.Print(e_print::e_req));
	_out() += TString().Format(_T("Quad #0 equals to #1 one: %s;"), TString().Bool(quad_0 == quad_1));
	_out() += TString().Format(_T("Quad #1 equals to #2 one: %s;"), TString().Bool(quad_1 == quad_2));
	_out()();
}