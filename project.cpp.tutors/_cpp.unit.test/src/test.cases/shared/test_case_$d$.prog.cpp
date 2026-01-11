/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:39:16.076, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shader program wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.prog.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CProg{}

CProg::CProg (const e_object _target) : TBase(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CProg::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();

	CProgram& prog = renderer.Scene().Progs().Get(TBase::Target());
	if (__failed(prog.Create()))
		this->m_error = prog.Error();
	else this->Delete();

	return this->Error();
}

err_code CProg::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TBase::Target());

	if (__failed(prog.Delete()))
		this->m_error = prog.Error();

	return this->Error();
}

TError&  CProg::Error (void) const { return this->m_error; }

#pragma endregion