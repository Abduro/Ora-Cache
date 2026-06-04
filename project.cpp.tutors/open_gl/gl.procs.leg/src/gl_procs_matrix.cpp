/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 16:19:21.618, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 matrix related function set wrapper interface implementation file;
*/
#include "gl_procs_matrix.h"

using namespace ::open_gl::procs;
using namespace ::open_gl::procs::ver_1_1;
using namespace ::open_gl::procs::matrix::ver_1_1;

namespace open_gl { namespace procs {
}}

#pragma region cls::CType{}

e_mat_type CType::Uint_to_enum (const uint32_t _value, CError& _error) {
	_value; _error;
	e_mat_type e_type = e_mat_type::e_modelview; // this is the default value as stated in documentation;
	_error <<__s_ok;

	switch (_value) {
	case e_mat_type::e_modelview: case e_mat_type::e_project: case e_mat_type::e_texture: e_type = static_cast<e_mat_type>(_value); break;
	default:
		_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: '_value' 0x%x ('%s') is not valid type"), _value, CType::To_str(_value));
	}
	return e_type;
}

_pc_sz  CType::To_str (const uint32_t _type) {
	_type;
	static CString cs_out;
	switch (_type) {
	case e_mat_type::e_modelview: cs_out = _T("e_modelview"); break;
	case e_mat_type::e_project  : cs_out = _T("e_project"); break;
	case e_mat_type::e_texture  : cs_out = _T("e_texture"); break;
	default:
		cs_out = _T("#undef");
	}

	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CMatrix{}

CMatrix::CMatrix (void) : TBase(), m_cached{0.0f} { TBase::m_error >>__CLASS__; }

const
f_seq_4x4& CMatrix::Cached (void) const { return this->m_cached; }

err_code CMatrix::Get (const e_mat_type _type) {
	return this->Get(_type, this->m_cached);
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;
err_code CMatrix::Get (const e_mat_type _e_type, f_seq_4x4& _result) {
	_e_type; _result;

	TBase::m_error <<__METHOD__<<__s_ok;
	CMatrix::To_self(_result);

	::glGetFloatv(_e_type, _result.data());
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : TBase::m_error <<__e_inv_arg = TString().Format(p_err_inv_enum, _e_type); break;
	case GL_INVALID_OPERATION : { TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glloadidentity ;
err_code CMatrix::To_self (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	::glLoadIdentity();
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : { TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

f_seq_4x4& CMatrix::To_self (f_seq_4x4& _data) {
	_data;
	/*cols:  #0  #1  #2  #3
	rows: #0 1.0 0.0 0.0 0.0
	      #1 0.0 1.0 0.0 0.0
	      #2 0.0 0.0 1.0 0.0
	      #3 0.0 0.0 0.0 1.0
	*/
	// https://stackoverflow.com/questions/57756557/initializing-a-stdarray-with-all-elements-having-the-same-value ;
	::std::fill(_data.begin(), _data.end(), 0.0f);
	_data.at(0x0) = 1.0f;
	_data.at(0x5) = 1.0f;
	_data.at(0xa) = 1.0f;
	_data.at(0xf) = 1.0f;

	return _data;
}

CString CMatrix::To_str (const f_seq_4x4& _mat_4x4, const bool _b_col_major) {
	_b_col_major;
	static const uint32_t u_cols = 4, u_rows = 4;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");

	CString cs_out;
	CString cs_value;

	for (uint32_t row_ = 0; row_ < u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < u_cols; col_++) {
#if (0) // -0.00f is not recognizable as a digit that is less than 0.0f and the format being applied is not correct;
			if (_mat_4x4.at(row_ + col_ * u_cols) < 0.0f) {} // the '-' sign will be added by sprintf();
			else cs_row += _T(" ");

			cs_row += TString().Float(_mat_4x4.at(row_ + col_ * u_cols), t_fmt_spec::e_decimal, pc_sz_fmt_0);
#else
			cs_value = TString().Float(_mat_4x4.at(row_ + col_ * u_cols), t_fmt_spec::e_decimal, pc_sz_fmt_0);
			if (_T('-') == cs_value.Left(1)) {}
			else cs_row += _T(" ");
#endif
			cs_row += cs_value;

			if (col_ < u_cols - 1)
				cs_row += _T(" ");
		}
		cs_out += TString().Format(_T("%s%s%s"), ::_prn_params._pfx(), (_pc_sz) cs_row, ::_prn_params._sfx());
	}
	cs_out = TString().Format(_T("%s[%s%s%s]"), ::_prn_params._pfx_hf(), ::_prn_params._sfx(), (_pc_sz) cs_out, ::_prn_params._pfx_hf());

	return cs_out;
}

#pragma endregion