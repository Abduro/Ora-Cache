/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Jan-2026 at 11:14:59.441, UTC+4, Batumi, Monday;
	This is OpenGL vertex array data wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$d$.vert.arr.dat.h"

using namespace test::open_gl::vertex;

#pragma region cls::c_vert_dat{}

c_vert_dat::c_vert_dat (const e_object _target) : m_pipe(_target) {
	if (false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	//	_out()(); this is not a test case method, but simple test class constructor; there is nothing to print out, just put to the log cache;
	}
	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

void c_vert_dat::Create (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CTstGraph graph;
	if (__failed(graph.Create())) { _out()(); return; }

	CVertArrData vert_data((*this)());

	if (__succeeded(vert_data.Create())) vert_data.Delete();

	graph.Delete();

	_out()();
}

void c_vert_dat::Delete (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CTstGraph graph;
	if (__failed(graph.Create())) { _out()(); return; }

	CVertArrData vert_data((*this)());

	_out() += _T("Deleting vertex array that is not crated yet:");
	vert_data.Delete();
	vert_data.Create();

	if (vert_data.Error() == false) {
		_out() += TString().Format(_T("Deleting vertex array (buffer id = %u);"), vert_data.GetId());
		vert_data.Delete();
	}

	graph.Delete();

	_out()();
}

const
TPipe&  c_vert_dat::operator ()(void) const { return this->m_pipe; }
TPipe&  c_vert_dat::operator ()(void)       { return this->m_pipe; }
c_vert_dat& c_vert_dat::operator << (const e_object _target) { this->m_pipe << _target; return *this; }

#pragma endregion