/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 13:19:23.132, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI in-memory draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.gdi.zbuf.h"

using namespace ebo::boo::test::draw;

#pragma region __blend
CVertex:: CVertex (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CVertex::_ctor (void) {

	this->m_vertex.Point(10, 20);
	this->m_vertex.Clr(TRgbQuad(0x61, 0x61, 0x61, _Opaque));

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_vertex.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CRectGrad:: CRectGrad (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRectGrad::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_grad.Print(e_print::e_all));
	_out()();
}

void CRectGrad::Set (void) {

	this->m_grad.LeftTop().Point(0, 0);
	this->m_grad.RightBottom().Point(32, 32);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_grad.Print(e_print::e_all));
	_out()();
}

////////////////////////////////////////////////////////////////////////////

CTriaGrad:: CTriaGrad (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CTriaGrad::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_grad.Print(e_print::e_all));
	_out()();
}

void CTriaGrad::Set (void) {

	this->m_grad.Get_A().Point(0, 0);
	this->m_grad.Get_B().Point(32, 32);
	this->m_grad.Get_C().Point(0, 32);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_grad.Print(e_print::e_all));
	_out()();
}

#pragma endregion