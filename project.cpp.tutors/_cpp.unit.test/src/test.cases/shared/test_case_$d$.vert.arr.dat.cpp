/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Jan-2026 at 11:55:34.133, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL vertex array data wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.vert.arr.dat.h"

using namespace ebo::boo::test::open_gl::draw;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	CVertArray& __vert_arr_accessor (const e_object _target) {
		TRenderer& renderer = ::Get_renderer();
		return renderer.Scene().ArrObjects().Get(_target).VertArray();
	}

}}}}}

#pragma region cls::CVertArrData{}

CVertArrData::CVertArrData (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

err_code CVertArrData::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CVertArray& vert_arr = renderer.Scene().ArrObjects().Get(TPipe::Target()).VertArray();

	if (__failed(vert_arr.Create())) {
		this->m_error = vert_arr.Error();
	}
//	       _out() += this->Error().Print(TError::e_print::e_req); }
//	else { _out() += _T("Vertex array buffer is created;"); }

	return this->Error();
}

err_code CVertArrData::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
	CVertArray& vert_arr = renderer.Scene().ArrObjects().Get(TPipe::Target()).VertArray();

	if (__failed(vert_arr.Delete())) {
		this->m_error = vert_arr.Error();
	}
//	       _out() += this->Error().Print(TError::e_print::e_req); }
//	else { _out() += _T("Vertex array buffer is deleted;"); }

	return this->Error();
}

TError& CVertArrData::Error (void) const { return this->m_error; }

bool  CVertArrData::Is_valid (void) const {
	const bool b_valid = __vert_arr_accessor(TPipe::Target()).Is_valid();
	_out() += TString().Format(_T("Vertex array is valid: '%s';"), TString().Bool(b_valid));
	return b_valid;
}

uint32_t CVertArrData::GetId (void) const {
	return __vert_arr_accessor(TPipe::Target()).Buffer().GetId();
}

const
TPipe&  CVertArrData::operator ()(void) const { return (TPipe&)*this; }
TPipe&  CVertArrData::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion