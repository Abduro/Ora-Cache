/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 09:21:38.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry lib unit test common definition implementation  file; 
*/
#include "ebo_test_$g$.2d.h"

using namespace ebo::boo::test::_2D;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { void __warning_lnk_4221 (void) {}}}}

/////////////////////////////////////////////////////////////////////////////

CMarker:: CMarker (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CMarker::_ctor (void) {
	_out() += TLog_Acc::e_new_line;
	_out() += TMarker().Print(e_print::e_all);
	_out()();
}

void CMarker::Operators (void) {

	TMarker mark_0(6, _T("The 1st one"), true);
	TMarker mark_1(7, _T("The 2nd one"), true);

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(
		_T("Marker %s equals to %s one >> %s"),
		(_pc_sz) mark_0.Print(e_print::e_req), (_pc_sz) mark_1.Print(e_print::e_req), TStringEx().Bool(mark_0 == mark_1)
	);
	_out()();
}

CRotate:: CRotate (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRotate::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("#ctor : %s"), (_pc_sz) this->m_rotate.Print(e_print::e_all));
	_out()();
}

void CRotate::Angle (void) {
	if (this->m_b_verb || true) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("*before* set : %d"), this->m_rotate.Angle());

	this->m_rotate.Angle(-372);
	
	_out() += TStringEx().Format(_T("*after * set : %d"), this->m_rotate.Angle());
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CRotate::ApplyTo (void) {
	_out() += TStringEx().Format(_T("*center* : %s"), (_pc_sz) this->m_rotate.Center().Print(e_print::e_all));

	TLine line; line.Begin().Set(10, 10); line.End().Set(10, 20);

	_out() += TStringEx().Format(_T("*target* before : %s"), (_pc_sz) line.Print(e_print::e_all));

	this->m_rotate.Angle(90);
	this->m_rotate.ApplyTo(line);

	_out() += TStringEx().Format(_T("angle=%d; direct=%s;"), this->m_rotate.Angle(), (_pc_sz) this->m_rotate.DirectAsText());
	_out() += TStringEx().Format(_T("*target* after : %s"), (_pc_sz) line.Print(e_print::e_all));

	TRect rect; rect.Vertex(TRect::e_left_top).Set(10, 20); rect.Vertex(TRect::e_right_low).Set(40, 10);

	_out() += TStringEx().Format(_T("*target* before : %s"), (_pc_sz) rect.Print(e_print::e_all));

	this->m_rotate.ApplyTo(rect);

	_out() += TStringEx().Format(_T("*target* after : %s"), (_pc_sz) rect.Print(e_print::e_all));

	TShape shape(3); shape.Points().Get(0).Set(0, 0); shape.Points().Get(1).Set(20, 30); shape.Points().Get(2).Set(40, 0); // this is the triangle;

	_out() += TStringEx().Format(_T("*target* before : %s"), (_pc_sz) shape.Print(e_print::e_all));

	this->m_rotate.ApplyTo(shape);

	_out() += TStringEx().Format(_T("*target* after : %s"), (_pc_sz) shape.Print(e_print::e_all));

	_out()();
}

void CRotate::DoIt (void) {
	_out() += TStringEx().Format(_T("*center* : %s"), (_pc_sz) this->m_rotate.Center().Print(e_print::e_all));

	TPoint point(10, 20);
	_out() += TStringEx().Format(_T("*target* : %s"), (_pc_sz) point.Print(e_print::e_all));

	int16_t angles[] = {-90, 90, -180, 180, -270, 270};
	for (uint16_t i_ = 0; i_ < _countof(angles); i_++) {

		TPoint rotor = point;

		this->m_rotate.Angle(angles[i_]);
		this->m_rotate.ApplyTo(rotor);
		_out() += TStringEx().Format(_T("angle=%d; direct=%s; *result* : %s"),
			this->m_rotate.Angle(), (_pc_sz) this->m_rotate.DirectAsText(), (_pc_sz) rotor.Print(e_print::e_all)
		);
	}

	this->m_rotate.Center() = TPoint(10,10);
	_out() += TStringEx().Format(_T("*center changed* : %s"), (_pc_sz) this->m_rotate.Center().Print(e_print::e_all));
	for (uint16_t i_ = 0; i_ < _countof(angles); i_++) {

		TPoint rotor = point;

		this->m_rotate.Angle(angles[i_]);
		this->m_rotate.ApplyTo(rotor);
		_out() += TStringEx().Format(_T("angle=%d; direct=%s; *result* : %s"),
			this->m_rotate.Angle(), (_pc_sz) this->m_rotate.DirectAsText(), (_pc_sz) rotor.Print(e_print::e_all)
		);
	}

	_out()();
}