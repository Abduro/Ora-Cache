/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 15:26:41.620, UTC+4, Batumi, Wednesday;
	This is OpenGL version 1.1 buffers' swap wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$u$.vsync.h"

using namespace ::test::open_gl::utils::ver_1_1;

#pragma region cls::CTstVSync{}

CTstVSync::CTstVSync (const bool _verbose) : m_verbose(_verbose) { _out().Clear(); }

err_code CTstVSync::Get (int32_t& _intervals) {
	_intervals = 0;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_intervals = (*this)().Get();

	if ((*this)().Error()) _out() += (*this)().Error();
	else
		_out() += TString().Format(_T("[impt] result: frame count is %d;"), _intervals);

	return (*this)().Error();
}

err_code CTstVSync::Set (const uint32_t _intervals) {
	_intervals;
	if (this->m_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("input frame count: %u"), _intervals);

	if (__failed((*this)().Set(_intervals))) _out() += (*this)().Error();
	else
		_out() += TString().Format(_T("[impt] result: frame count is set to %u;"), _intervals);

	return (*this)().Error();
}

const
CVSync&  CTstVSync::operator ()(void) const { return this->m_vsync; }
CVSync&  CTstVSync::operator ()(void)       { return this->m_vsync; }

CTstVSync& CTstVSync::operator <<(const bool _verbose) { this->m_verbose = _verbose; return *this; }

#pragma endregion