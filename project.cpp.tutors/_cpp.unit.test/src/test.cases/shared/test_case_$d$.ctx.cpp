/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:19:52.669, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL draw context wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.ctx.h"

using namespace test::open_gl::context;
using namespace test::open_gl::context::ver_1_1;

#pragma region cls::CTstDevice{}

err_code CTstDevice::Create (const bool _b_verbose/* = true*/) {
	if (_b_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create())) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] result: device context is created;");
	}

	return (*this)().Error();
}

err_code CTstDevice::Delete (const bool _b_verbose/* = true*/) {
	if (_b_verbose)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Destroy())) { _out() += (*this)().Error(); }
	else {
		_out() += _T("[impt] result: device context is destroyed;");
	}

	return (*this)().Error();
}

const
CFake_Ctx&  CTstDevice::operator ()(void) const { return this->m_fk_ctx; }
CFake_Ctx&  CTstDevice::operator ()(void)       { return this->m_fk_ctx; }

#pragma endregion
#pragma region cls::CTstFormat{}

err_code   CTstFormat::Find (const SPxBits& _bits) {
	_bits;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input bits: %s;"), (_pc_sz) _bits.To_str());

	uint32_t u_index = 0; u_index;

	CTstDevice fk_ctx;
	if (__failed(fk_ctx.Create(false)))
		return fk_ctx().Error();

	(*this)() << fk_ctx()();

	if (__failed((*this)().Find(_bits, u_index))) { _out() += (*this)().Error(); return (*this)().Error(); }
	_out() += TString().Format(_T("[impt] *result*: found pixel format index is (%d) >> {%s}(%u);"), u_index, (_pc_sz) CPxFormat::To_str((*this)().Get()), (*this)().Get().dwFlags);

	return (*this)().Error();
}

const
CPxFormat& CTstFormat::operator ()(void) const { return this->m_px_fmt; }
CPxFormat& CTstFormat::operator ()(void)       { return this->m_px_fmt; }

#pragma endregion
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
#pragma region cls::CCtxToggle{}
/* unfortunately, the graphics validation is made several times: during making it current and deletion, and in Is_valid() itself;
   perhaps it requires making review, but not this time, and not for caring optimization;
*/
CCtxToggle:: CCtxToggle (void) {}
CCtxToggle::~CCtxToggle (void) {}

const
CFake_Ctx& CCtxToggle::operator ()(void) const { return this->m_fk_ctx; }
CFake_Ctx& CCtxToggle::operator ()(void)       { return this->m_fk_ctx; }

#pragma endregion