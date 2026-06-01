/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2026 at 12:12:53.987, UTC+4, Batumi, Thursday;
	This is OpenGL projection matrix wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.project.h"

using namespace test::open_gl::ver_1_1;

#pragma region cls::CTstMatMode{}

CTstMatMode::CTstMatMode (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstMatMode::Get (void) {
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); }
	else  {
		const e_stk_modes n_current = this->m_mode.Current();
		_out() += TString().Format(_T("[impt] current matrix stack mode: '%s';"), CMatMode::To_str(n_current));
	}

	return (*this)().Error();
}

err_code CTstMatMode::Set (const e_stk_modes _e_mode) {
	_e_mode;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Set(_e_mode))) { _out() += (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result matrix stack mode: '%s' is set;"), CMatMode::To_str(_e_mode));
	}

	return (*this)().Error();
}

const
CMatMode& CTstMatMode::operator ()(void) const { return this->m_mode; }
CMatMode& CTstMatMode::operator ()(void)       { return this->m_mode; }

#pragma endregion
#pragma region cls::CTstMatrix{}

CTstMatrix::CTstMatrix (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstMatrix::Get (const e_mat_types _type) {
	_type;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Querying matrix of type '%s':"), CMatrix::To_str(_type));

	if (__failed((*this)().Get(_type))) { _out() += (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result matrix is:\n%s"), (_pc_sz) CMatrix::To_str((*this)().Cached()));
	}

	return (*this)().Error();
}

const
CMatrix& CTstMatrix::operator ()(void) const { return this->m_matrix; }
CMatrix& CTstMatrix::operator ()(void)       { return this->m_matrix; }

#pragma endregion
#pragma region cls::CTstPerspect{}

CTstPerspect::CTstPerspect (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstPerspect::Get (void) {

	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); }
	else {
		const f_seq_4x4& mat_proj = (*this)().Ref();
		_out() += _T("[impt] perspective matrix:");
		_out() += CMatrix::To_str(mat_proj);
	}

	return (*this)().Error();
}

err_code CTstPerspect::Set (const s_pers_args& _args) {
	_args;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Set(_args))) { _out() += (*this)().Error(); }
	else {
		const f_seq_4x4& mat_proj = (*this)().Ref();
		_out() += _T("[impt] perspective matrix:");
		_out() += CMatrix::To_str(mat_proj);
	}

	return (*this)().Error();
}

const
CPerspect& CTstPerspect::operator ()(void) const { return this->m_perspect; }
CPerspect& CTstPerspect::operator ()(void)       { return this->m_perspect; }

#pragma endregion