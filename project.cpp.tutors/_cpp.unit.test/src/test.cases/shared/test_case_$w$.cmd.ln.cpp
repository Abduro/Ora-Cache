/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Jul-2026 at 13:28:51.457, UTC+4, Batumi, Thursday;
	This is Ebo Pack generic command line wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.cmd.ln.h"

using namespace ::test::win_api::input;

#pragma region cls::CTstCmdLn{}

CTstCmdLn::CTstCmdLn (const bool _b_verbose) : m_verbose(_b_verbose) { _out().Clear(); }

err_code   CTstCmdLn::Parse (void) {
	if (this->m_verbose)
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Parse())) { _out() += (*this)().Error(); }
	else {
		_out() += TString().Format(_T("[impt] result: %s"), (_pc_sz) (*this)().Print());
	}

	return (*this)().Error();
}

const
CCmdLine&  CTstCmdLn::operator ()(void) const { return this->m_cmd_ln; }
CCmdLine&  CTstCmdLn::operator ()(void)       { return this->m_cmd_ln; }

CTstCmdLn& CTstCmdLn::operator <<(const bool _b_verbose) { this->m_verbose = _b_verbose; return *this; }

#pragma endregion