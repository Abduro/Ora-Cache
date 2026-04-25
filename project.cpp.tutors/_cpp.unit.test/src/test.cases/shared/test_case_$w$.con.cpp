/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:01:03.022, UTC+4, Batumi, Sunday;
	This is Ebo Pack trace console interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.h"

using namespace test::win_api;
using namespace test::win_api::console;

#pragma region cls::c_con_loc{}

_pc_sz c_con_loc::Get_path (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	t_locate locate_;

	static CString cs_path; cs_path = locate_.Get_path(); // to-do: returning the pointer to the static string object must be reviewed;

	if (locate_.Error()) _out() += locate_.Error();
	else _out() += TString().Format(_T("[impt] result: '%s';"), (_pc_sz) cs_path);

	return (_pc_sz) cs_path;
}

#pragma endregion
#pragma region cls::c_con_wrap{}

err_code c_con_wrap::Create (_pc_sz _p_path) {
	_p_path;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create(_p_path, true, true))) { _out() += (*this)().Error(); }
	else _out() += _T("[impt] result: console process is created;");

	return (*this)().Error();
}

err_code c_con_wrap::Detach (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Detach())) { _out() += (*this)().Error(); }
	else _out() += _T("[impt] result: console process is dettached;");

	return (*this)().Error();
}

_pc_sz c_con_wrap::Get_path (CError& _err) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	static CString cs_path = t_module::Get_path(_err);
	if (_err) _out() += _err;
	else _out() += TString().Format(_T("[impt] result: '%s';"), (_pc_sz) cs_path);

	return (_pc_sz) cs_path;
}

const
t_wrap& c_con_wrap::operator ()(void) const { return this->m_wrap; }
t_wrap& c_con_wrap::operator ()(void)       { return this->m_wrap; }

#pragma endregion