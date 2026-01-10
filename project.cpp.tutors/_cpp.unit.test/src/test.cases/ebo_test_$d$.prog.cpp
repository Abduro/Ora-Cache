/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 09-Jan-2026 at 22:02:46.843, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' program wrapper unit test interface implementation file.
*/
#include "ebo_test_$d$.prog.h"
#include "gl_procs_shader.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_prog{}

c_prog::c_prog (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_prog::Grid (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CBuilder builder;

	if (__failed(builder.Device().Create())) return;
	if (__failed(builder.Graph().Create(builder.Device().Window()))) return;

	builder.Prog().Target(e_object::e_grid); // by default, it is already set as the target of the grid, but for better readability;

	builder.Prog().Create();
	builder.Prog().Delete();

	builder.Release();

	_out()();
}

#pragma endregion
#pragma region cls::c_shaders{}

c_shaders::c_shaders (const e_object _target, const bool _b_verb) : m_target(_target), m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_shaders::Create_all (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out()();
}

void c_shaders::Get_frag (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CBuilder builder;

	if (__failed(builder.Device().Create())) { _out()(); return; }

	$Fragment& $_frag = builder.Shaders().Fragment();

	if (false){}
	else if (__failed($_frag.Create())) {/*nothig for test*/}
	else if (__failed($_frag.Src().Set())) {/*nothig for test*/}

	builder.Device().Delete();

	_out()();
}

void c_shaders::Get_vert (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

#pragma endregion