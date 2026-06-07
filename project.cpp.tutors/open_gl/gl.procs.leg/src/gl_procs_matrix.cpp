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

#pragma region cls::CMatrix{}

CMatrix::CMatrix (void) : TBase(), m_data{0.0f} { TBase::m_error >>__CLASS__; }

const
f_mat_4x4& CMatrix::Data (void) const { return this->m_data; }
f_mat_4x4& CMatrix::Data (void)       { return this->m_data; }

err_code CMatrix::Get (const e_mat_type _type) {
    return  this->Get (_type, this->m_data);
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;
err_code CMatrix::Get (const e_mat_type _type, f_mat_4x4& _result) {
	_type; _result;
	TBase::m_error << __METHOD__ << __s_ok;

	CParam param;
	if (__failed(param.Get_ptr((uint32_t)_type, _result.data())))
		TBase::m_error = param.Error();

	return TBase::Error();
}

err_code CMatrix::Set (void) {
     return this->Set (this->Data());
}

err_code CMatrix::Set (const f_mat_4x4& _matrix) {
	_matrix;
	return CMatrix::Set(_matrix, TBase::m_error);
}

err_code CMatrix::Set (const f_mat_4x4& _matrix, CError& _error) {
	_matrix; _error;
	/* Possible error codes:
	GL_INVALID_OPERATION : glLoadMatrixf() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	_error << __METHOD__ << __s_ok;

	::glLoadMatrixf(_matrix.data());
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_OPERATION : (_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}
	return _error;
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

f_mat_4x4& CMatrix::To_self (f_mat_4x4& _data) {
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

CString CMatrix::To_str (const f_mat_4x4& _mat_4x4, const bool _b_col_major) {
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

const
f_mat_4x4& CMatrix::operator ()(void) const { return this->Data(); }
f_mat_4x4& CMatrix::operator ()(void)       { return this->Data(); }

err_code   CMatrix::operator <<(const f_mat_4x4& _data) { return this->Set(_data); }

#pragma endregion