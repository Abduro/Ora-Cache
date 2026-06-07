/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2026 at 12:12:53.987, UTC+4, Batumi, Thursday;
	This is OpenGL projection matrix wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.matrix.h"

using namespace test::open_gl::ver_1_1;

#pragma region cls::CTstMatrix{}

CTstMatrix::CTstMatrix (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstMatrix::Get (const e_mat_type _type) {
	_type;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Querying matrix of type '%s':"), (_pc_sz) CEnum::To_str(_type));

	if (__failed((*this)().Get(_type))) { _out() += (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result matrix is:\n%s"), (_pc_sz) CMatrix::To_str((*this)().Data()));
	}

	return (*this)().Error();
}

err_code CTstMatrix::To_self (void) {
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().To_self())) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] an identity matrix is set;");
	}

	return (*this)().Error();
}

const
CMatrix& CTstMatrix::operator ()(void) const { return this->m_matrix; }
CMatrix& CTstMatrix::operator ()(void)       { return this->m_matrix; }

#pragma endregion