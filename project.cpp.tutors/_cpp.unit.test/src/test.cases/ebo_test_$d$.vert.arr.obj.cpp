/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jan-2026 at 22:24:13.050, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex array object wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.vert.arr.obj.h"
#include "test_case_$d$.ctx.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_vert_arr_obj{}

c_vert_arr_obj::c_vert_arr_obj (const e_object _target) : m_pipe(_target) {
	if (false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

void c_vert_arr_obj::Create (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto; // must be created before calling any function from open_gl;
	CVertArrObj v_a_o((*this)());

	if (__succeeded(v_a_o.Create())) v_a_o.Delete();

	_out()();
}

void c_vert_arr_obj::Delete (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	CVertArrObj v_a_o((*this)());

	_out() += _T("Deleting vertex array object that is not crated yet:");
	v_a_o.Delete();
	v_a_o.Create();

	if (v_a_o.Error() == false) {
		_out() += TString().Format(_T("Deleting vertex array oject (id = %u);"), v_a_o.GetId());
		v_a_o.Delete();
	}
	_out()();
}

const
TPipe&  c_vert_arr_obj::operator ()(void) const { return this->m_pipe; }
TPipe&  c_vert_arr_obj::operator ()(void)       { return this->m_pipe; }
c_vert_arr_obj& c_vert_arr_obj::operator << (const e_object _target) { this->m_pipe << _target; return *this; }

#pragma endregion