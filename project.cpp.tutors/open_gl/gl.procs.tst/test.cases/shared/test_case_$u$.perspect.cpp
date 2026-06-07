/*
	Created by Tech_dog (ebontrop@gmai.com) on 05-Jun-2026 at 12:50:19.639, UTC+4, Batumi, Friday;
	This is OpenGL v_1_1 GLU related procedures' wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$u$.perspect.h"

using namespace ::test::open_gl::utils::ver_1_1;

#pragma region cls::CTstPerspect{}

CTstPerspect::CTstPerspect (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstPerspect::Get (void) {

	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); }
	else {
		const f_mat_4x4& mat_proj = (*this)().Ref();
		_out() += TString().Format(_T("[impt] perspective matrix:%s%s"), (_pc_sz)::_prn_params.m_sfx, (_pc_sz) CMatrix::To_str(mat_proj));
	}

	return (*this)().Error();
}

err_code CTstPerspect::Set (const s_pers_args& _args) {
	_args;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Set(_args))) { _out() += (*this)().Error(); }
	else {
		const f_mat_4x4& mat_proj = (*this)().Ref();
		_out() += _T("[impt] perspective matrix:");
		_out() += CMatrix::To_str(mat_proj);
	}

	return (*this)().Error();
}

const
CPerspect& CTstPerspect::operator ()(void) const { return this->m_perspect; }
CPerspect& CTstPerspect::operator ()(void)       { return this->m_perspect; }

#pragma endregion