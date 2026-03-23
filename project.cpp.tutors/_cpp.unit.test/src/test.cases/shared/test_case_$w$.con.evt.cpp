/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 08:09:11.484, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' trace console input event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.con.evt.h"

using namespace ebo::boo::test::con::events;

#pragma region cls::c_rtr_ctrl{}

const
t_rtr_ctrl& c_rtr_ctrl::operator ()(void) const { return this->m_rtr_ctrl; }
t_rtr_ctrl& c_rtr_ctrl::operator ()(void)       { return this->m_rtr_ctrl; }

#pragma endregion
#pragma region cls::c_rtr_input{}

err_code c_rtr_input::Turn (const bool _b_on_off) {
	_b_on_off;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Turn(_b_on_off))) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: input buffer event router is turned '%s';"), _b_on_off ? _T("on") : _T("off")); }

	return (*this)().Error();
}

const
t_rtr_input& c_rtr_input::operator ()(void) const { return /*this->m_rtr_input*/ ::Get_input(); }
t_rtr_input& c_rtr_input::operator ()(void)       { return /*this->m_rtr_input*/ ::Get_input(); }

#pragma endregion