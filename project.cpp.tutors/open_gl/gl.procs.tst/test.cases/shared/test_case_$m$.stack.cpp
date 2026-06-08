/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2026 at 18:40:47.430, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL math lib matrix stack wrapper uint test interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.stack.h"

using namespace test::open_gl::ver_1_1;

#pragma region cls::CTstStack{}

CTstMode::CTstMode (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstMode::Get (void) {
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result: current matrix stack mode is '%s';"), CEnum::To_str((*this)()));
	}
	return (*this)().Error();
}

err_code CTstMode::Set  (const e_stk_mode _mode) {
	_mode;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input mode: '%s';"), CEnum::To_str(_mode));

	if (__failed((*this)().Set(_mode))) { _out() += (*this)().Error(); }
	else if (this->m_verbose) _out() += TString().Format(_T("[impt] he mode is set to '%s';"), CEnum::To_str(_mode));
	
	return (*this)().Error();
}

const
CStack& CTstStack::operator ()(void) const { return this->m_stack; }
CStack& CTstStack::operator ()(void)       { return this->m_stack; }

#pragma endregion
#pragma region cls::CTstStack{}

CTstStack::CTstStack (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstStack::Push (const CMatrix& _matrix, const e_mat_type _type) {
	_matrix; _type;
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);


	return (*this)().Error();
}

err_code CTstStack::Pop  (void) {
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	return (*this)().Error();
}

const
CMode& CTstMode::operator ()(void) const { return this->m_mode; }
CMode& CTstMode::operator ()(void)       { return this->m_mode; }

#pragma endregion
#if (0)
using namespace test::open_gl::math;

#pragma region cls::c_stk_target{}

c_stk_target:: c_stk_target (void) : TBase() { TBase::m_error >>__CLASS__; this->m_graph.Create(); }
c_stk_target::~c_stk_target (void) { this->m_graph.Delete(); }

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

c_mtx_stack:: c_mtx_stack (void) : TBase() { TBase::m_error >>__CLASS__; this->m_graph.Create(); }
c_mtx_stack::~c_mtx_stack (void) { this->m_graph.Delete(); }

err_code c_mtx_stack::Get (const e_mat_type _e_type, t_mat4x4& _mat) {
	_e_type; _mat;
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get(_e_type, _mat))) {
		_out() += TBase::m_error = (*this)().Error();
	}

	return TBase::Error();
}

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
#endif