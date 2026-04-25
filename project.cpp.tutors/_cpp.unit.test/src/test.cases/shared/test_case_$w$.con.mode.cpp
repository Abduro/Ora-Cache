/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 10:04:41.986, UTC+4, Batumi, Monday;
	This is Ebo Pack trace console interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.mode.h"

using namespace test::win_api::console::modes;

#pragma region cls::c_mode_input{}

uint32_t c_mode_input::Get (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); }

	const uint32_t u_flags = (*this)().Flags();

	_out() += TString().Format(_T("[impt] result: %s (%u);"), (*this)().To_str(u_flags), u_flags);

	return u_flags;
}

err_code c_mode_input::Set (const uint32_t _u_flags) {
	_u_flags;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("%s (%u);") , (*this)().To_str(_u_flags), _u_flags);

	if (__failed((*this)().Set(_u_flags))) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: input buffer flags (%u) is set successfully;"), _u_flags); }

	return (*this)().Error();
}

const
t_input& c_mode_input::operator ()(void) const { return this->m_input; }
t_input& c_mode_input::operator ()(void)       { return this->m_input; }

#pragma endregion
#pragma region cls::c_mode_output{}

uint32_t c_mode_output::Get (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Get())) { _out() += (*this)().Error(); }

	const uint32_t u_flags = (*this)().Flags();

	_out() += TString().Format(_T("[impt] result: %s (%u);"), (*this)().To_str(u_flags), u_flags);

	return u_flags;
}

err_code c_mode_output::Set (const uint32_t _u_flags) {
	_u_flags;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("%s (%u);") , (*this)().To_str(_u_flags), _u_flags);

	if (__failed((*this)().Set(_u_flags))) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: output buffer flags (%u) is set successfully;"), _u_flags); }

	return (*this)().Error();
}

const
t_output& c_mode_output::operator ()(void) const { return this->m_output; }
t_output& c_mode_output::operator ()(void)       { return this->m_output; }

#pragma endregion