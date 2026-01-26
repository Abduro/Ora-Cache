/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 12:58:26.506, UTC+4, Batumi, Ssturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.buffer.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CVertBuffer{}

CVertBuffer::CVertBuffer (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

TError& CVertBuffer::Error (void) const { return this->m_error; }

uint32_t CVertBuffer::Size (void) const {
	this->m_error <<__METHOD__<<__s_ok; return CVertBuffer::Size((*this)().Target(), this->m_error);
}
uint32_t CVertBuffer::Size (const e_bind_targets _target, CError& _err) {
	_target; _err;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto(false); { _out()(false); ctx_auto.Create(); _out()(true); }

	const uint32_t u_size = CBuffer::Get_size(_target, _err);
	if (false == _err) {
		_out() += TString().Format(_T("[impt] The vertex buffer size is: %u (bytes);"), u_size);
	}
	_out()(false); // no output from context destructor;

	return u_size;
}

const
CBuffer& CVertBuffer::operator ()(void) const { return this->m_buffer; }
CBuffer& CVertBuffer::operator ()(void)       { return this->m_buffer; }

#pragma endregion