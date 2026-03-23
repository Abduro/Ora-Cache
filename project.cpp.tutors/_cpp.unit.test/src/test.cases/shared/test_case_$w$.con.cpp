/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:01:03.022, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' trace console interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.h"

using namespace ebo::boo::test::con;

#pragma region cls::c_con_wrap{}

err_code c_con_wrap::Create (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create(true, true))) { _out() += (*this)().Error(); }
	else _out() += _T("[impt] result: console process is created;");

	return (*this)().Error();
}

err_code c_con_wrap::Detach (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Detach())) { _out() += (*this)().Error(); }
	else _out() += _T("[impt] result: console process is dettached;");

	return (*this)().Error();
}

const
t_wrap& c_con_wrap::operator ()(void) const { return this->m_wrap; }
t_wrap& c_con_wrap::operator ()(void)       { return this->m_wrap; }

#pragma endregion