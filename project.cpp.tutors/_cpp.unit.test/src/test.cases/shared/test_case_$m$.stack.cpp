/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2026 at 18:40:47.430, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL math lib matrix stack wrapper uint test interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.stack.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_stk_target{}

c_stk_target:: c_stk_target (void) : TBase() { TBase::m_error >>__CLASS__; ::__get_dev_ctx().Create(false); }
c_stk_target::~c_stk_target (void) { ::__get_dev_ctx().Delete(false); }

err_code  c_stk_target::Get (void) const {
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	(*this)().Get();
	if ((*this)().Error()) {
		_out() += TBase::m_error = (*this)().Error();
	} else { _out() += TString().Format(_T("[impt] result: '%s';"), TMatModeProcs::To_str((*this)().Get())); }

	return TBase::Error();
}

err_code c_stk_target::Set (const e_mat_type _e_type) {
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Set(_e_type))) {
		_out() += TBase::m_error = (*this)().Error();
	} else { _out() += _T("[impt] result: success;"); }

	return TBase::Error();
}

const
t_stk_target& c_stk_target::operator ()(void) const { return this->m_target; }
t_stk_target& c_stk_target::operator ()(void)       { return this->m_target; }

#pragma endregion
#pragma region cls::c_mtx_stack{}

c_mtx_stack:: c_mtx_stack (void) : TBase() { TBase::m_error >>__CLASS__; ::__get_dev_ctx().Create(false); }
c_mtx_stack::~c_mtx_stack (void) { ::__get_dev_ctx().Delete(false); }

err_code c_mtx_stack::Push (const c_mat4x4& _mat, const e_mat_mode _e_mode) {
	_mat; _e_mode;
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Push(_mat(), _e_mode))) {
		_out() += TBase::m_error = (*this)().Error();
	} else { _out() += _T("[impt] result: success;"); }

	return TBase::Error();
}

err_code c_mtx_stack::Push (const c_mat4x4& _mat, const e_mat_type _e_type) {
	_mat; _e_type;
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Push(_mat(), _e_type))) {
		_out() += TBase::m_error = (*this)().Error();
	} else { _out() += _T("[impt] result: success;"); }

	return TBase::Error();
}

err_code c_mtx_stack::Pop (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Pop())) {
		_out() += TBase::m_error = (*this)().Error();
	} else { _out() += _T("[impt] result: success;"); }

	return TBase::Error();
}

const
t_mat_stack& c_mtx_stack::operator ()(void) const { return this->m_stack; }
t_mat_stack& c_mtx_stack::operator ()(void)       { return this->m_stack; }

#pragma endregion