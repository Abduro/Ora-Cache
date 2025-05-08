/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-May-2025 at 09:44:27.366, UTC+4, Batumi, Thursday;
	This is Ebo Pack 2D space geometry shape classes' unit test interface implementation file; 
*/
#include "ebo_test_$g$.2d.shape.h"

using namespace ebo::boo::test;
using namespace ebo::boo::test::outline::_2D;

#pragma region __sides

CSide:: CSide (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CSide::_ctor (void) {

	TSide a_side;
	// It is prefereble to use appropriate constructor, otherwise validity flag of the marker remains false by default;
	a_side.Marker() << (uint32_t) 1 << _T("left") << true; // error C2666: requires specific data type definition for marker identifier :( ;

	a_side.Begin() = TPoint(0,0);
	a_side.End() = TPoint(1,1);

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("Default: %s"), (_pc_sz) TSide().Print(e_print::e_all));
	_out() += TStringEx().Format(_T("Inited : %s"), (_pc_sz) a_side.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CSides:: CSides (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CSides::_ctor (void) {

	TSides sides;
	TSide  side ;

	side.Marker() << (uint32_t)1 << _T("The 1st marker") << true; sides.Append(side);
	side.Marker() << (uint32_t)2 << _T("The 2nd marker") << true; sides.Append(side);

	_out() += TLog_Acc::e_new_line;
	_out() += sides.Print(e_print::e_all, _T("\n\t"), _T(""));
	_out()();
}

#pragma endregion

#pragma region __shapes

CRect:: CRect (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRect::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TString().Format(_T("Default: %s"), (_pc_sz)TRect().Print(e_print::e_req));
	_out()();

}

#pragma endregion