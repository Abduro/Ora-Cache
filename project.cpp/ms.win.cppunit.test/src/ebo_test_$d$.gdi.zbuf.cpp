/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 13:19:23.132, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI in-memory draw renderer lib unit test interface implementation file; 
*/
#include "ebo_test_$d$.gdi.zbuf.h"

using namespace ebo::boo::test::draw;

#pragma region __shade

CRectMesh:: CRectMesh (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRectMesh::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));
	_out()();
}

void CRectMesh::Set (void) {

	_out() += TStringEx().Format(_T("*before set*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));

	this->m_mesh.Set(1, 0);

	_out() += TStringEx().Format(_T("*after set*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));
	_out()();
}

////////////////////////////////////////////////////////////////////////////

CTriMesh:: CTriMesh (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CTriMesh::_ctor (void) {

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));
	_out()();
}

void CTriMesh::Set (void) {

	_out() += TStringEx().Format(_T("*before set*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));

	this->m_mesh.Raw().Vertex1 = 0;
	this->m_mesh.Raw().Vertex2 = 1;
	this->m_mesh.Raw().Vertex3 = 2;

	_out() += TStringEx().Format(_T("*after set*:%s"), (_pc_sz) this->m_mesh.Print(e_print::e_all));
	_out()();
}

////////////////////////////////////////////////////////////////////////////

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

#pragma endregion