/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2026 at 09:33:12.922, UTC+4, Batumi, Monday;
	This is OpenGL WinAPI graphics device context wrapper interface implementation file for using in test adapters;
*/
#include "test_case_$d$.ctx.arb.h"

using namespace test::open_gl::context::arb;

#pragma region cls::CTstGraph{}

err_code CTstGraph::Create (const bool _b_verbose/* = true*/) {
	if (_b_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_tst_dev.Create(false)))
		return this->m_tst_dev().Error();

	if (__failed((*this)().Create(this->m_tst_dev()()))) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] result: graphics context is created;");
	}

	return (*this)().Error();
}

err_code CTstGraph::Delete (const bool _b_verbose/* = true*/) {
	if (_b_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Destroy())) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] result: graphics context is destroyed;");
	}

	return (*this)().Error();
}

err_code CTstGraph::MakeCurrent (const bool _yes_or_no) {
	_yes_or_no;
	if (__failed((*this)().MakeCurrent(_yes_or_no))) { _out() += (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] graphics context is made '%s';"), _yes_or_no ? _T("current") : _T("not current"));
	}

	return (*this)().Error();
}

err_code  CTstGraph::Swap (void) {

	if (__failed((*this)().Swap())) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] graphics context is swapped;");
	}

	return (*this)().Error();
}

const
CGraphics&  CTstGraph::operator ()(void) const { return this->m_graph; }
CGraphics&  CTstGraph::operator ()(void)       { return this->m_graph; }

#pragma endregion