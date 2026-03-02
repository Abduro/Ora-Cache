/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:19:52.669, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL draw context wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.ctx.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CDevCtx{}

CDevCtx::CDevCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CDevCtx::Create (const bool _b_verbose/* = true*/) {
	_b_verbose;
	this->m_error <<__METHOD__<<__s_ok;
	
	const bool b_locked = _out().Cached().Locked(); // to-do: must be re-viewed, some sort triggering the lock state would be useful;
	_out()(_b_verbose);

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += this->Window().To_str();

	if (this->Window().Error()) {
		_out()(!b_locked); return this->m_error = this->Window().Error();
	}

	if (this->Is_valid()) {
		_out() += _T("the device context is already created;"); _out()(!b_locked); return this->Error();
	}

	TRenderer& renderer = ::Get_renderer();

	CDevice& dev_ref = renderer.Scene().Ctx().Device();
	dev_ref.Target().Source(TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__));

	if (__failed(dev_ref.Create(this->Window()))) {
		this->m_error = dev_ref.Error();
		_out()(this->Error());
	}
	_out()(!b_locked); return this->Error();
}

err_code CDevCtx::Delete (const bool _b_verbose/* = true*/) {
	_b_verbose;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_locked = _out().Cached().Locked();
	_out()(_b_verbose);

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();

	/* at the end of the test case the device context must be deleted;
	   otherwise on process exit and calling objects' destructors a lot of errors is thrown;
	   debug trace is connected to test output, a possible error is output using debug;
	*/
	if (renderer.Scene().Ctx().Device().Is_valid())
		renderer.Scene().Ctx().Device().Destroy();

	_out()(!b_locked); return this->Error();
}

TError&  CDevCtx::Error (void) const { return this->m_error; }
bool  CDevCtx::Is_valid (void) const { return (*this)().Is_valid(); }

const
CFakeWnd& CDevCtx::Window (void) const { return this->m_fk_wnd; }
CFakeWnd& CDevCtx::Window (void)       { return this->m_fk_wnd; }

const
CDevice&  CDevCtx::operator ()(void) const { return ::Get_renderer().Scene().Ctx().Device(); }
CDevice&  CDevCtx::operator ()(void)       { return ::Get_renderer().Scene().Ctx().Device(); }

#pragma endregion
#pragma region cls::CGraphCtx{}

CGraphCtx::CGraphCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CGraphCtx::Create (const HWND _h_target, const bool _b_verbose/* = true*/) {
	_h_target; _b_verbose;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_locked = _out().Cached().Locked();
	_out()(_b_verbose);

	CString cs_cls = TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__);
	_out() += TString().Format(_T("[warn] cls::[%s].%s():"), (_pc_sz) cs_cls, (_pc_sz)__METHOD__);

	if (this->Is_valid()) {
		_out() += _T("the graphics context is already created;"); _out()(!b_locked); return this->Error();
	}
				
	TRenderer& renderer = Get_renderer();
	renderer.Scene().Ctx().Graphics().Target().Source((_pc_sz)cs_cls);
	renderer.Scene().Ctx().Graphics().Target() << _h_target;
	
	const uint32_t u_major = renderer.Scene().Ctx().Graphics().Version().Major();
	const uint32_t u_minor = renderer.Scene().Ctx().Graphics().Version().Minor();

	if (__failed(renderer.Scene().Ctx().Graphics().Create(u_major, u_minor))) {
		this->m_error = renderer.Scene().Ctx().Graphics().Error();  _out()(this->Error());
	}

	_out()(!b_locked); return this->Error();
}

err_code CGraphCtx::Delete (const bool _b_verbose/* = true*/) {
	_b_verbose;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_locked = _out().Cached().Locked();
	_out()(_b_verbose);

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();
				
	/* at the end of the test case the graphics object must be destroyed;
	   otherwise on process' exit and calling objects' destructors a lot of errors is thrown;
	   debug trace is connected to test output, a possible error is output using debug;
	*/
	if (renderer.Scene().Ctx().Graphics().Is_valid())
		renderer.Scene().Ctx().Graphics().Destroy(); // to-do: possible error of this procedure may be of interest;

	_out()(!b_locked); return this->Error();
}

TError&  CGraphCtx::Error (void) const { return this->m_error; }

bool  CGraphCtx::Is_valid (void) const { return (*this)().Is_valid(); }

err_code CGraphCtx::Swap (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRenderer& renderer = ::Get_renderer();

	if (false == !!::SwapBuffers(renderer.Scene().Ctx().Graphics().Target().Get())) {
		this->m_error.Last();
		_out()(this->Error());
	}
	return this->Error();
}

const
CGraphics& CGraphCtx::operator ()(void) const { return ::Get_renderer().Scene().Ctx().Graphics(); }
CGraphics& CGraphCtx::operator ()(void)       { return ::Get_renderer().Scene().Ctx().Graphics(); }

#pragma endregion
#pragma region cls::CCtx_auto{}

CCtx_auto:: CCtx_auto (const bool _b_auto) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok; if (_b_auto) this->Create();
}
CCtx_auto::~CCtx_auto (void) { this->Delete(); }

err_code CCtx_auto::Create (const bool _b_verbose/* = true*/) {
	_b_verbose;
	this->m_error <<__METHOD__<<__s_ok;

	if (false) {}
	else if (__failed(this->Device().Create(_b_verbose))) this->m_error = this->Device().Error();
	else if (__failed(this->Graph().Create(this->Device().Window(), _b_verbose))) this->m_error = this->Graph().Error();

	return this->Error();
}
err_code CCtx_auto::Delete (const bool _b_verbose/* = true*/) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Graph().Delete(_b_verbose))) this->m_error = this->Graph().Error();
	if (__failed(this->Device().Delete(_b_verbose))) this->m_error = this->Device().Error();
	
	return this->Error();
}

const
CDevCtx& CCtx_auto::Device (void) const { return this->m_device; }
CDevCtx& CCtx_auto::Device (void)       { return this->m_device; }
const
CGraphCtx& CCtx_auto::Graph (void) const { return this->m_graphs; }
CGraphCtx& CCtx_auto::Graph (void)       { return this->m_graphs; }

TError&  CCtx_auto::Error (void) const { return this->m_error; }

bool CCtx_auto::Is_created (void) const {
	return this->Device().Is_valid() || this->Graph().Is_valid();
}

#pragma endregion

TDevCtx& ::__get_dev_ctx (const bool _b_silent) {
	_b_silent;
	static TDevCtx dev_ctx; return dev_ctx;
}

 TGraph& ::__get_graph (void) {
	 static TGraph graph(false); return graph;
 }