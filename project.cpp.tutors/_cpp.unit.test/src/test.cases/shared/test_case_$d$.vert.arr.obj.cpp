/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jan-2026 at 20:54:55.560, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex array object wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.vert.arr.obj.h"

using namespace ebo::boo::test::open_gl::draw;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	CArrObject& __vao_accessor (const e_object _target) {
		TRenderer& renderer = ::Get_renderer();
		return renderer.Scene().ArrObjects().Get(_target);
	}

}}}}}

#pragma region cls::CVertArrObj{}

CVertArrObj::CVertArrObj (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

err_code CVertArrObj::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CArrObject& vao = __vao_accessor(TPipe::Target());

	if (__failed(vao.Create())) {
		this->m_error = vao.Error();
	}
//	       _out() += this->Error().Print(TError::e_print::e_req); }
//	else { _out() += TString().Format(_T("Vertex array object is created: id = %u;"), vao.GetId()); }
	return this->Error();
}

err_code CVertArrObj::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CArrObject& vao = __vao_accessor(TPipe::Target());

	const uint32_t u_id = vao.GetId();
	if (false) {}
	else if (0 == u_id) {
//		_out() += _T("Vertex array object is not created yet;");
	}
	else if (__failed(vao.Delete())) {
		this->m_error = vao.Error();
	}
//	       _out() += this->Error().Print(TError::e_print::e_req); }
//	else { _out() += TString().Format(_T("Vertex array object (id = %u) is deleted;"), u_id); }
	return this->Error();
}

TError& CVertArrObj::Error (void) const { return this->m_error; }

uint32_t CVertArrObj::GetId (void) const {
	const uint32_t u_id = __vao_accessor(TPipe::Target()).GetId();

	_out() += TString().Format(_T("Vertex array object id = %u;"), u_id);
	return u_id;
}

bool  CVertArrObj::Is_valid (void) const {
	const bool b_valid = __vao_accessor(TPipe::Target()).Is_valid();

	_out() += TString().Format(_T("Vertex array object is valid: '%s';"), TString().Bool(b_valid));
	return b_valid;
}

const
TPipe&  CVertArrObj::operator ()(void) const { return (TPipe&)*this; }
TPipe&  CVertArrObj::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion