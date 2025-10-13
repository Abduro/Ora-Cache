/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Oct-2025 at 23:56:35.016, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL generic scene wrapper interface implementation file;
*/
#include "gl_scene.h"
#include "program\gl_prog_linker.h"
#include "program\gl_prog_status.h"
#include "shader\gl_compiler.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;

CScene:: CScene (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CScene::~CScene (void) {}

TError&  CScene::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Prog().Shaders().Detach()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Delete()))
		return this->m_error = this->Prog().Shaders().Error();

	return this->Error();
}

TError&  CScene::Error (void) const { return this->m_error; }

err_code CScene::Prepare (void) {
	this->m_error <<__METHOD__<<__s_ok;

	shader::CCompiler cmpl;
	if (false == cmpl.Is_supported()) {
		 __trace_err_2(_T("%s\n"), (_pc_sz) cmpl.Error().Print(TError::e_print::e_req));
		return this->m_error = cmpl.Error();
	}
	else
		__trace_warn_2(_T("%s\n"), _T("Shader compiler is supported;"));

	if (__failed(this->Prog().Create()))
		return this->m_error = this->Prog().Error();

	if (__failed(this->Prog().Shaders().Fragment().Create()))
	    return this->m_error = this->Prog().Shaders().Fragment().Error();

	if (__failed(this->Prog().Shaders().Vertex().Create()))
	    return this->m_error = this->Prog().Shaders().Vertex().Error();

	if (__failed(this->Prog().Shaders().Load()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Compile()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Shaders().Attach()))
		return this->m_error = this->Prog().Shaders().Error();

	if (__failed(this->Prog().Link()))
		return this->m_error = this->Prog().Error();

	this->Prog().Validate();

	return this->Error();
}

const
CProgram& CScene::Prog (void) const { return this->m_prog; }
CProgram& CScene::Prog (void)       { return this->m_prog; }