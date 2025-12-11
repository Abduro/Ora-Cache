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

using CDevice = context::CDevice;
using CArrObjs = CScene::CArrObjs;

#pragma region CScene::CContext
CScene::CContext::CContext (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CScene::CContext::Clear (void) {
	this->m_error <<__METHOD__<<__s_ok;

	context::CBase*  ctx_bases[] = { &this->Draw(), &this->Device() };

	for (uint32_t i_ = 0; i_ < _countof(ctx_bases); i_++) {
		if (__failed(ctx_bases[i_]->Destroy()))
			this->m_error = ctx_bases[i_]->Error(); // keeps going to the next context; base class outputs error to the trace itself;
	}

	return this->Error();
}

const
CScene::CDevCtx& CScene::CContext::Device (void) const { return this->m_dev_ctx; }
CScene::CDevCtx& CScene::CContext::Device (void)       { return this->m_dev_ctx; }
const
CScene::CDrwCtx& CScene::CContext::Draw (void) const { return this->m_drw_ctx; }
CScene::CDrwCtx& CScene::CContext::Draw (void)       { return this->m_drw_ctx; }

TError& CScene::CContext::Error (void) const { return this->m_error; }
#pragma endregion
/////////////////////////////////////////////////////////////////////////////

CScene:: CScene (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CScene::~CScene (void) {}

const
CArrObjs& CScene::ArrObjs (void) const { return this->m_arr_objs; }
CArrObjs& CScene::ArrObjs (void)       { return this->m_arr_objs; }     

const
CScene::CContext& CScene::Ctx (void) const { return this->m_ctx; }
CScene::CContext& CScene::Ctx (void)       { return this->m_ctx; }

TError&  CScene::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Progs().Delete()))
		return this->m_error = this->Progs().Error();

	return this->Error();
}

TError&  CScene::Error (void) const { return this->m_error; }

err_code CScene::Prepare (void) {
	this->m_error <<__METHOD__<<__s_ok;
#if (0) // it should be called as soon as possible, just right after creating fake window device context;
	shader::CCompiler cmpl;
	if (false == cmpl.Is_supported()) {
		 __trace_err_2(_T("%s\n"), (_pc_sz) cmpl.Error().Print(TError::e_print::e_req));
		return this->m_error = cmpl.Error();
	}
	else
		__trace_warn_2(_T("%s\n"), _T("Shader compiler is supported;"));
#endif
#pragma region _1st_step
	// the step #1: creating shaders, program, shaders' attachment and linking the program;
	if (__failed(this->Progs().Create()))
		return this->m_error = this->Progs().Error();
	
	if (__failed(this->Progs().Load()))
		return this->m_error = this->Progs().Error();

	if (__failed(this->Progs().Build()))
		return this->m_error = this->Progs().Error();
#pragma endregion
#pragma region __2nd_step
	// the step #2: configuring vertex attributes and creating vertex attribute objects;
	if (__failed(this->Progs().Attrs().Init())) { this->m_error = this->Progs().Attrs().Error(); } // does nothing with the error;
	if (__failed(this->ArrObjs().Create())) { this->m_error = this->Progs().Attrs().Error(); }     // does nothing with the error;
#pragma endregion

#if (0) // needs to be moved to the programs enumerator class;
	if (__failed(prog.Buffer().Create()))
		return this->m_error = prog.Buffer().Error();

	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;
#if (1)
	if (__failed(prog.Buffer().BindTo(e_bind_targets::e_array)))
		return this->m_error = prog.Buffer().Error();
#else
	if (__failed(prog.Buffer().Bind()))
		return this->m_error = prog.Buffer().Error();
#endif
#endif
	if (false == this->Error())
		__trace_impt_2(_T("The draw scene is prepared;\n"));

	return this->Error();
}

const
CScene::CProgs& CScene::Progs (void) const { return this->m_progs; }
CScene::CProgs& CScene::Progs (void)       { return this->m_progs; }