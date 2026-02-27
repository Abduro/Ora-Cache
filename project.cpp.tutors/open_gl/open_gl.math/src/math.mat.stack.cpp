/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 22:39:59.517, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL matrix stack wrapper interface implementation file;
*/
#include "math.mat.stack.h"
#include "gl_procs_math.h"
#include "matrix\gl_procs_mtx.stack.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;
using namespace ex_ui::draw::open_gl::math::matrix;

#pragma region cls::CTarget{}

CTarget:: CTarget (void) : m_type(e_mat_type::e_undef) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CTarget::~CTarget (void) {}

TError& CTarget::Error (void) const { return this->m_error; }

e_mat_type CTarget::Get (void) const {
	if (e_mat_type::e_undef != this->m_type)
		return this->m_type;
	this->m_error <<__METHOD__<<__s_ok;

	this->m_type = ::__get_mat_mode_procs().Get();

	if (::__get_mat_mode_procs().Error()) {
		this->m_error = ::__get_mat_mode_procs().Error(); __trace_err_ex_3(this->Error());
	}

	return this->m_type;
}

err_code CTarget::Set (const e_mat_type _e_type) {
	_e_type;
	this->m_error <<__METHOD__<<__s_ok;

	if (e_mat_type::e_undef == _e_type)
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: Invalid matrix type = '%s'"), TMatModeProcs::To_str(_e_type));

	if (this->m_type == _e_type)
		return this->Error();  // does nothing and returns __s_ok;

	if (__failed(::__get_mat_mode_procs().Set(_e_type))) {
		this->m_error = ::__get_mat_mode_procs().Error(); __trace_err_ex_3(this->Error());
	} else this->m_type = _e_type;

	return this->Error();
}

const
CTarget&  CTarget::operator >>(e_mat_type& _e_type) const { _e_type = this->Get(); return *this; }
CTarget&  CTarget::operator <<(const e_mat_type _e_type) { this->Set(_e_type); return *this; }

e_mat_type CTarget::operator ()(void) const { return this->Get(); }

#pragma endregion
#pragma region cls::CStack{}

CStack:: CStack (const bool _b_auto) : m_auto(_b_auto), m_pushed(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; if (this->m_auto) this->Push(); }
CStack::~CStack (void) { if (this->m_auto) this->Pop(); }

const
CTarget& CStack::Current (void) const { return this->m_target; }
CTarget& CStack::Current (void)       { return this->m_target; }

TError&  CStack::Error (void) const { return this->m_error; }
bool     CStack::Is_pushed (void) const { return this->m_pushed; }

err_code CStack::Pop (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_pushed())
		return this->Error(); // just keeping the silence;

	if (__failed(::__get_stack_procs().Pop())) {
		this->m_error = __get_stack_procs().Error(); __trace_err_ex_3(this->Error());
	}
	else
		this->m_pushed = false;

	return this->Error();
}

err_code CStack::Push (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (true == this->Is_pushed())
		return this->m_error << __e_not_expect = _T("The matrix is already pushed");

	if (__failed(::__get_stack_procs().Push())) {
		this->m_error = __get_stack_procs().Error(); __trace_err_ex_3(this->Error());
	}
	else
		this->m_pushed = true;

	return this->Error();
}

err_code CStack::Push (const c_mat4x4& _mat, const e_mat_type _type) {
	_mat; _type;
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_pushed())
		return this->m_error <<__e_not_expect = _T("The stack is already pushed");

	using e_mat_mode = ex_ui::draw::open_gl::procs::matrix::e_mat_mode;

	if (__failed(::__get_mat_mode_procs().Set(_type)))
		return this->m_error = ::__get_mat_mode_procs().Error();

	if (__failed(::__get_matrix_procs().Load(_mat()))) {
		this->m_error = ::__get_matrix_procs().Error(); __trace_err_ex_3(this->Error());
	} else { this->m_pushed = true; }

	return this->Error();
}

#pragma endregion