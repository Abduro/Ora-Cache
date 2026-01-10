/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jan-2026 at 12:48:36.508, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' draw context builder interface declaration file;
*/
#include "ebo_test_$d$.builder.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::draw;

using CDevCtx = CBuilder::CDevCtx;
using CGraphCtx = CBuilder::CGraphCtx;
using CProg = CBuilder::CProg;
using CShaders = CBuilder::CShaders;

#pragma region cls::CBuilder{}

CBuilder::CBuilder (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
const
CDevCtx& CBuilder::Device (void) const { return this->m_device; }
CDevCtx& CBuilder::Device (void)       { return this->m_device; }
const
CGraphCtx& CBuilder::Graph (void) const { return this->m_graph; }
CGraphCtx& CBuilder::Graph (void)       { return this->m_graph; }

TError&  CBuilder::Error (void) const { return this->m_error; }
const
CProg&   CBuilder::Prog (void) const { return this->m_prog; }
CProg&   CBuilder::Prog (void)       { return this->m_prog; }
const
CShaders& CBuilder::Shaders (void) const { return this->m_shaders; }
CShaders& CBuilder::Shaders (void)       { return this->m_shaders; }

err_code CBuilder::Release (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Graph().Delete())) return this->m_error = this->Graph().Error();
	if (__failed(this->Device().Delete())) return this->m_error = this->Device().Error();

	return this->Error();
}

#pragma endregion
#pragma region cls::CDevCtx{}

CDevCtx::CDevCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CDevCtx::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += this->Window().To_str();

	if (this->Window().Error()) {
		return this->m_error = this->Window().Error();
	}

	TRenderer& renderer = ::Get_renderer();

	CDevice& dev_ref = renderer.Scene().Ctx().Device();
	dev_ref.Target().Source(TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__));

	if (__failed(dev_ref.Create(this->Window()))) {
		this->m_error = dev_ref.Error();
	}

	return this->Error();
}

err_code CDevCtx::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();

	/* at the end of the test case the device context must be deleted;
	   otherwise on process exit and calling objects' destructors a lot of errors is thrown;
	   debug trace is connected to test output, a possible error is output using debug;
	*/
	if (renderer.Scene().Ctx().Device().Is_valid())
		renderer.Scene().Ctx().Device().Destroy();

	return this->Error();
}

TError&  CDevCtx::Error (void) const { return this->m_error; }

const
CFakeWnd& CDevCtx::Window (void) const { return this->m_fk_wnd; }
CFakeWnd& CDevCtx::Window (void)       { return this->m_fk_wnd; }

#pragma endregion
#pragma region cls::CGraphCtx{}

CGraphCtx::CGraphCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CGraphCtx::Create (const HWND _h_target) {
	_h_target;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_cls = TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__);
	_out() += TString().Format(_T("cls::[%s].%s():"), (_pc_sz) cs_cls, (_pc_sz)__METHOD__);
				
	TRenderer& renderer = Get_renderer();
	renderer.Scene().Ctx().Graphics().Target() << _h_target;
	renderer.Scene().Ctx().Graphics().Target().Source((_pc_sz)cs_cls);

	const uint32_t u_major = renderer.Scene().Ctx().Graphics().Version().Major();
	const uint32_t u_minor = renderer.Scene().Ctx().Graphics().Version().Minor();

	if (__failed(renderer.Scene().Ctx().Graphics().Create(u_major, u_minor))) {
		this->m_error = renderer.Scene().Ctx().Graphics().Error();
	}

	return this->Error();
}

err_code CGraphCtx::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
				
	/* at the end of the test case the graphics object must be destroyed;
	   otherwise on process exit and calling objects' destructors a lot of errors is thrown;
	   debug trace is connected to test output, a possible error is output using debug;
	*/
	if (renderer.Scene().Ctx().Graphics().Is_valid())
		renderer.Scene().Ctx().Graphics().Destroy();

	return this->Error();
}

TError&  CGraphCtx::Error (void) const { return this->m_error; }

#pragma endregion
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