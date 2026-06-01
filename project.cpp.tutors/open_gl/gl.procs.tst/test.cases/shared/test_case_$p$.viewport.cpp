/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2026 at 10:03:22.486, UTC+4, Batumi, Sunday;
	This is OpenGL viewport related procedures' wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$p$.viewport.h"

using namespace ::test::open_gl::procs;

#pragma region cls::CTstViewport{}

CTstViewport::CTstViewport (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstViewport::Get_Params (void) {
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CParams& params = (*this)().Params();

	if (__failed((*this)().Params().Get())) { _out() += params.Error(); }
	else {
		_out() += TString().Format(_T("[impt] result: %s;"), (_pc_sz) CParams::To_str(params.Value().Offset(), params.Value().Size()));
	}

	return (*this)().Error();
}

err_code   CTstViewport::Is_valid (void) {
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CParams& params = (*this)().Params();

	if (__failed((*this)().Params().Is_valid())) { _out() += (*this)().Params().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result: %s;"), (_pc_sz) CParams::To_str(params.Value().Offset(), params.Value().Size()));
	}

	return (*this)().Error();
}

err_code   CTstViewport::Set_Params (const i_set_4& _values) {
	_values;
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("input params: %s;"), (_pc_sz) CParams::To_str(_values));

	CParams& params = (*this)().Params();

	if (__failed((*this)().Params().Set(_values))) { _out() += (*this)().Params().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result: %s;"), (_pc_sz) CParams::To_str(params.Value().Offset(), params.Value().Size()));
	}

	return (*this)().Error();
}

bool CTstViewport::Verbose (void) const { return this->m_verbose; }
void CTstViewport::Verbose (const bool _yes_or_no) { this->m_verbose = _yes_or_no; }

const
CViewport& CTstViewport::operator ()(void) const { return this->m_viewport; }
CViewport& CTstViewport::operator ()(void)       { return this->m_viewport; }

#pragma endregion