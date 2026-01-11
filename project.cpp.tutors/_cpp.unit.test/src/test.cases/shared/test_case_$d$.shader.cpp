/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:51:44.122, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shaders' wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.shader.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region CShaders{}

CShaders::CShaders (const e_object _target) : TBase(_target) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code  CShaders::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer = ::Get_renderer();
	CProgram& prog = renderer.Scene().Progs().Get(TBase::Target());

	if (__failed(prog.Shaders().Create()))
		this->m_error = prog.Shaders().Error();

	return this->Error();
}

const
$Fragment& CShaders::Fragment (void) const { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Fragment(); }
$Fragment& CShaders::Fragment (void)       { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Fragment(); }

TError& CShaders::Error (void) const { return this->m_error; }
const
$Vertex& CShaders::Vertex (void) const { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Vertex(); }
$Vertex& CShaders::Vertex (void)       { return ::Get_renderer().Scene().Progs().Get(TBase::Target()).Shaders().Vertex(); }

#pragma endregion