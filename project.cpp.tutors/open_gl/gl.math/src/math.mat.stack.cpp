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

namespace ex_ui  { namespace draw { namespace open_gl { namespace math {
namespace matrix {

	e_mat_type _mode_2_type (const e_mat_mode _mode) {
		switch (_mode) {
		case e_mat_mode::e_color    : return e_mat_type::e_color    ;
		case e_mat_mode::e_modelview: return e_mat_type::e_modelview;
		case e_mat_mode::e_project  : return e_mat_type::e_project  ;
		case e_mat_mode::e_texture  : return e_mat_type::e_texture  ;
		default: return e_mat_type::e_undef;
		}
	}
	e_mat_mode _type_2_mode (const e_mat_type _type) {
		switch (_type) {
		case e_mat_type::e_color    : return e_mat_mode::e_color    ;
		case e_mat_type::e_modelview: return e_mat_mode::e_modelview;
		case e_mat_type::e_project  : return e_mat_mode::e_project  ;
		case e_mat_type::e_texture  : return e_mat_mode::e_texture  ;
		default: return e_mat_mode::e_undef;
		}
	}

}}}}}

#pragma region cls::CTarget{}

CTarget:: CTarget (void) : m_mode(e_mat_mode::e_undef) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CTarget::~CTarget (void) {}

TError& CTarget::Error (void) const { return this->m_error; }

e_mat_mode CTarget::Get (void) const {
	if (e_mat_mode::e_undef != this->m_mode)
		return this->m_mode;
	this->m_error <<__METHOD__<<__s_ok;

	this->m_mode = ::__get_mat_mode_procs().Get();

	if (::__get_mat_mode_procs().Error()) {
		this->m_error = ::__get_mat_mode_procs().Error(); __trace_err_ex_3(this->Error());
	}

	return this->m_mode;
}

err_code CTarget::Set (const e_mat_mode _e_mode) {
	_e_mode;
	this->m_error <<__METHOD__<<__s_ok;

	if (e_mat_mode::e_undef == _e_mode)
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: Invalid matrix type = '%s'"), TMatModeProcs::To_str(_e_mode));

	if (this->m_mode == _e_mode)
		return this->Error();  // does nothing and returns __s_ok;

	if (__failed(::__get_mat_mode_procs().Set(_e_mode))) {
		this->m_error = ::__get_mat_mode_procs().Error(); __trace_err_ex_3(this->Error());
	} else this->m_mode = _e_mode;

	return this->Error();
}

err_code CTarget::Set (const e_mat_type _e_type) {
	return this->Set(_type_2_mode(_e_type));
}

const
CTarget&  CTarget::operator >>(e_mat_mode& _e_type) const { _e_type = this->Get(); return *this; }
CTarget&  CTarget::operator <<(const e_mat_mode _e_type) { this->Set(_e_type); return *this; }

e_mat_mode CTarget::operator ()(void) const { return this->Get(); }

#pragma endregion
#pragma region cls::CStack{}

CStack:: CStack (const bool _b_auto) : m_auto(_b_auto), m_pushed(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; if (this->m_auto) this->Push(); }
CStack::~CStack (void) { if (this->m_auto) this->Pop(); }

const
CTarget& CStack::Current (void) const { return this->m_target; }
CTarget& CStack::Current (void)       { return this->m_target; }

TError&  CStack::Error (void) const { return this->m_error; }
bool     CStack::Is_pushed (void) const { return this->m_pushed; }

err_code CStack::Get  (const e_mat_type _e_type, c_mat4x4& _mat_out) {
	_e_type; _mat_out;
/*
	if (__failed(this->Current().Set(_e_type))) {
		return this->m_error = this->Current().Error();
	}
*/
	if (__failed(::__get_stack_procs().Get(_e_type, _mat_out.Data()))) {
		this->m_error = ::__get_stack_procs().Error();
	}

	return this->Error();
}

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

err_code CStack::Push (const c_mat4x4& _mat, const e_mat_mode _mode) {
	_mat; _mode;
	return this->Push(_mat, _mode_2_type(_mode));
}

err_code CStack::Push (const c_mat4x4& _mat, const e_mat_type _type) {
	_mat; _type;
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_pushed())
		return this->m_error <<__e_not_expect = _T("The stack is already pushed");

	if (__failed(::__get_mat_mode_procs().Set(_type_2_mode(_type))))
		return this->m_error = ::__get_mat_mode_procs().Error();

	if (__failed(::__get_matrix_procs().Load(_mat()))) {
		this->m_error = ::__get_matrix_procs().Error(); __trace_err_ex_3(this->Error());
	} else { this->m_pushed = true; }

	return this->Error();
}

#pragma endregion