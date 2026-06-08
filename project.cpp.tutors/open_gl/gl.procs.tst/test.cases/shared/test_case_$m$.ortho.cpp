/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jun-2026 at 13:22:37.551, UTC+4, Batumi, Monday;
	This is OpenGL orthographic projection matrix wrapper interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.ortho.h"

using namespace ::test::open_gl::ortho;

#pragma region cls::CTstOrtho{}

CTstOrtho::CTstOrtho (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code CTstOrtho::Set (const t_rect& _clip, const f_planes& _planes) {
	_clip; _planes;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input args: clip rect = %s; planes = {%s};"), To_str(_clip), _planes.To_str());

	if (__failed((*this)().Set(_clip, _planes))) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] result: success;");
	}

	return (*this)().Error();
}

const
COrtho& CTstOrtho::operator ()(void) const { return this->m_ortho; }
COrtho& CTstOrtho::operator ()(void)       { return this->m_ortho; }

CTstOrtho& CTstOrtho::operator <<(const bool _b_verbose) { this->m_verbose = _b_verbose; return *this; }

#pragma endregion