/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:19:50.563, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL API  procedure loader wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.procs.h"

using namespace test::draw::open_gl;

#pragma region cls::CTstProcExt{}

err_code   CTstProcExt::Load (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Load())) { _out() += (*this)().Error(); return (*this)().Error(); }
	
	_out() += _T("[impt] *result*: OpenGL extensions are loaded;");

	return (*this)().Error();
}

err_code   CTstProcExt::Unload (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Unload())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] *result*: OpenGL extensions are unloaded;");

	return (*this)().Error();
}

const
CProc_Ext& CTstProcExt::operator ()(void) const { return ::Get_ProcExt(); }
CProc_Ext& CTstProcExt::operator ()(void)       { return ::Get_ProcExt(); }

#pragma endregion