/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2026 at 09:29:52.165, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix stack uint test interface implementation file; 
*/
#include "ebo_test_$m$.stack.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_stk_current{}

c_stk_current::c_stk_current (void) {}

void c_stk_current::Get (void) { c_stk_target().Get(); _out()();  }
void c_stk_current::Set (void) { c_stk_target().Set(e_mat_type::e_undef); _out()(); }

#pragma endregion
#pragma region cls::c_mat_stack{}

c_mat_stack::c_mat_stack (void) {}

void c_mat_stack::Get (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	c_mtx_4x4 mat_4; mat_4().Cell(0,1) = 0.1f;
	c_mtx_stack stack;

	_out() += TString().Format(_T("The metrix *before* pushing to stack:\n%s"), (_pc_sz)c_mtx_4x4::To_str(mat_4(), false));

	if (__failed(stack.Push(mat_4(), c_stk_target()().Get()))) { _out()(); return; }
	if (__failed(stack.Get(e_mat_type::e_modelview, mat_4()))) { _out()(); return; }

	_out() += TString().Format(_T("The metrix *after* pushing to stack:\n%s"), (_pc_sz)c_mtx_4x4::To_str(mat_4(), false));

	_out()();
}

void c_mat_stack::Pop (void) {
	c_mtx_stack().Pop(); _out()();
}

void c_mat_stack::Push (void) {

	c_mtx_stack stack;

	if (__failed(stack.Push(t_mat4x4(), /*e_mat_type::e_undef*/ c_stk_target()().Get()))) {} else stack.Pop(); _out()();
}

#pragma endregion