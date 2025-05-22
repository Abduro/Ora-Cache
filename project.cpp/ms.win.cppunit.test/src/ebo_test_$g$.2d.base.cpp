/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-May-2025 at 09:43:51.849, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry base classes' unit test interface implementation file; 
*/
#include "ebo_test_$g$.2d.base.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::_2D::base;

/////////////////////////////////////////////////////////////////////////////

CLine:: CLine (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CLine::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Default: %s"), (_pc_sz) this->m_line.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

#pragma region __points

CPoint:: CPoint (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPoint::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TPoint().Print(e_print::e_all);
	_out()();
}

void CPoint::Operators (void) {

	TPoint pt_0(0,0),pt_1(1,1);

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Points: %s & %s are equal to each other >> %s"),
		(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), TStringEx().Bool(pt_0 == pt_1));

	pt_0 << 2 >> -2;
	pt_1 << 3 >> -3;

	TPoint pt_result = (pt_0 + pt_1);

	_out() += TString().Format(_T("%s + %s = %s"),
		(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), (_pc_sz) pt_result.Print(e_print::e_req));

	pt_0 << 4 >> -4;
	pt_1 << 6 >> -6;

	pt_result = (pt_0 - pt_1);

	_out() += TString().Format(_T("%s - %s = %s"),
		(_pc_sz)pt_0.Print(e_print::e_req), (_pc_sz)pt_1.Print(e_print::e_req), (_pc_sz) pt_result.Print(e_print::e_req));

	_out()();
}
 ////////////////////////////////////////////////////////////////////////////

CPoints:: CPoints (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPoints::_ctor (void) {

	TPoints pts_;

	pts_.Raw().push_back(TPoint(0,0));
	pts_.Raw().push_back(TPoint(1,1));
	pts_.Raw().push_back(TPoint(2,2));
	pts_.Raw().push_back(TPoint(3,3));

	_out() += TLog_Acc::e_new_line;
	_out() += pts_.Print();
	_out()();
}

////////////////////////////////////////////////////////////////////////////

CPoint_2:: CPoint_2 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPoint_2::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Default: %s"), (_pc_sz)TPoint_2().Print(e_print::e_all));
	_out()();
}

#pragma endregion

#pragma region __sizes

CSize:: CSize (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CSize::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TSize().Print(e_print::e_all);
	_out()();
}

void CSize::Operators (void) {

	TSize sz_0(0,0),sz_1(1,1);

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Sizes: %s & %s are equal to each other >> %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), TStringEx().Bool(sz_0 == sz_1));


	sz_0 << 2 >> -2;
	sz_1 << 3 >> -3;

	TSize sz_result = (sz_0 + sz_1);

	_out() += TString().Format(_T("%s + %s = %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

	sz_0 << 4 >> -4;
	sz_0 << 6 >> -6;

	sz_result = (sz_0 - sz_1);

	_out() += TString().Format(_T("%s - %s = %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CSizeU:: CSizeU (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CSizeU::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TSizeU().Print(e_print::e_all);
	_out()();

}

void CSizeU::Operators (void) {

	TSizeU sz_0(0,0),sz_1(1,1);

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Sizes: %s & %s are equal to each other >> %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), TStringEx().Bool(sz_0 == sz_1));

	sz_0 << 2 >> 2;
	sz_1 << 3 >> 3;

	TSizeU sz_result = (sz_0 + sz_1);

	_out() += TString().Format(_T("%s + %s = %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

	sz_0 << 4 >> 4;
	sz_0 << 6 >> 6;

	sz_result = (sz_0 - sz_1);

	_out() += TString().Format(_T("%s - %s = %s"),
		(_pc_sz)sz_0.Print(e_print::e_req), (_pc_sz)sz_1.Print(e_print::e_req), (_pc_sz) sz_result.Print(e_print::e_req));

	_out()();
}

#pragma endregion

#pragma region __position

CAnchor:: CAnchor (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAnchor::_ctor(void) {

	TAnchor anchor; anchor.Marker().Set(1, _T("pos::anchor"), true);

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) anchor.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CPosition:: CPosition (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CPosition::_ctor(void) {

	TPosition pos;
	pos.Anchor().Marker().Set(1, _T("pos::anchor"), true);
	pos.Size().Set(20, 10);

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) pos.Print(e_print::e_all));
	_out()();
}

#pragma endregion