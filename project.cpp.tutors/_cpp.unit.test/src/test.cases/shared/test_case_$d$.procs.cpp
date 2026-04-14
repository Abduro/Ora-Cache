/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:19:50.563, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL API  procedure loader wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.procs.h"

using namespace test::draw::open_gl;

#pragma region cls::CTstProcExt{}

bool  CTstProcExt::Is_remote (void) const {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const bool b_remote = (*this)().Is_remote();
	if ((*this)().Error()) _out() += (*this)().Error();

	if (b_remote)
	     _out() += _T("[warn] *result*: OpenGL resides on remote desktop;");
	else _out() += _T("[impt] *result*: OpenGL resides on local machine;");

	return b_remote;
}

err_code   CTstProcExt::Load (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Load())) { _out() += (*this)().Error(); return (*this)().Error(); }
	
	_out() += _T("[impt] *result*: OpenGL extensions are loaded:");
	const
	ext_items_t& v_exts = (*this)().Get();
	for (uint32_t i_ = 0; i_ < v_exts.size(); i_++) {
		_out() += v_exts.at(i_).Name();
	}

	return (*this)().Error();
}
const
TProcExtEnum& CTstProcExt::operator ()(void) const { return ::Get_ProcExt(); }
TProcExtEnum& CTstProcExt::operator ()(void)       { return ::Get_ProcExt(); }

#pragma endregion