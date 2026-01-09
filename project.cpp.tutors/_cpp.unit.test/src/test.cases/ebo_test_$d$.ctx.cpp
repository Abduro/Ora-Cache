/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 01:26:39.207, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL drawing context of regular device and of renderer uint test interface implementation file;
*/
#include "ebo_test_$d$.ctx.h"
#include "shared.preproc.h"

#include <crtdbg.h>

using namespace ebo::boo::test::open_gl::draw;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw { namespace _impl {

	class CBuilder {
	public:
		CBuilder (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		CBuilder (const CBuilder&) = delete; CBuilder (CBuilder&&) = delete; ~CBuilder (void) = default;

		class CDevCtx {
		public:
			CDevCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
			CDevCtx (const CDevCtx&) = delete; CDevCtx (CDevCtx&&) = delete; ~CDevCtx (void) = default;

			err_code Create (void) {
				this->m_error <<__METHOD__<<__s_ok;

				_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
				_out() += this->Window().To_str();

				if (this->Window().Error()) {
					return this->m_error = this->Window().Error();
				}

				TRenderer& renderer = ::Get_renderer();

				CDevice& dev_ref = renderer.Scene().Ctx().Device();
				dev_ref.Target().Source(TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__));

				if (__failed(dev_ref.Create(this->Window().m_hWnd))) {
					_out() += this->Window().Error().Print(TError::e_print::e_req);
				}

				return this->Error();
			}

			err_code Delete (void) {
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

			TError&  Error  (void) const { return this->m_error; }
			const
			CFakeWnd& Window (void) const { return this->m_fk_wnd; }
			CFakeWnd& Window (void)       { return this->m_fk_wnd; }

		private:
			CDevCtx& operator = (const CDevCtx&) = delete; CDevCtx& operator = (CDevCtx&&) = delete;
			CError   m_error ;
			CFakeWnd m_fk_wnd;
		};
		const
		CDevCtx& Device (void) const { return this->m_device; }
		CDevCtx& Device (void)       { return this->m_device; }

		TError&  Error  (void) const { return this->m_error; }

		class CGraphCtx {
		public:
			CGraphCtx (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
			CGraphCtx (const CGraphCtx&) = delete; CGraphCtx (CGraphCtx&&) = delete; ~CGraphCtx (void) = default;

			err_code Create (const HWND _h_target) { // for the test case the fake window handle is used;
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
				//	_out() += this->Error().Print(TError::e_print::e_req); not necessary because the context base class does it;
				}

				return this->Error();
			}

			err_code Delete (void) {
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

			TError&  Error (void) const { return this->m_error; }

		private:
			CGraphCtx& operator = (const CGraphCtx&) = delete; CGraphCtx& operator = (CGraphCtx&&) = delete;
			CError m_error;
		};
		const
		CGraphCtx& Graph (void) const { return this->m_graph; }
		CGraphCtx& Graph (void)       { return this->m_graph; }

	private:
		CBuilder& operator = (const CBuilder&) = delete; CBuilder& operator = (CBuilder&&) = delete;
		CError    m_error;
		CDevCtx   m_device;
		CGraphCtx m_graph;
	};

}}}}}}


#pragma region cls::c_ctx{}

c_ctx::c_ctx (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

c_ctx::~c_ctx (void) {
//	__debugbreak(); it very looks like running *each* test case method creates its own *new* copy of this class;
//	_out()();       thus other event handlers' macros should be used those are executed *before* and *after* running the test case;
}

void c_ctx::OnClean (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::OnInit (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::_ctor (void) {
	if (false == this->m_b_verb)
		return;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::Device (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	
	_impl::CBuilder builder;

	builder.Device().Create(); // the error and result are output by builder itself;
	builder.Device().Delete();

	_out()();
}

void c_ctx::Graphics (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_impl::CBuilder builder;

	const bool b_error = false; // if is set to 'true' the error part of this test case throws the error;
	if (b_error) {
		builder.Graph().Create(nullptr);
		builder.Graph().Delete();
	}
	else if (__failed(builder.Device().Create())) { /*nothing to test;*/ }
	else if (__failed(builder.Graph().Create(builder.Device().Window().m_hWnd)))  { /*nothing to test;*/ }
	else {
		builder.Graph().Delete();
		builder.Device().Delete();
	}
	_out()();
}

#pragma endregion