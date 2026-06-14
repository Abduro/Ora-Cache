/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 02:01:31.446, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' view base interface implementation file;
*/
#include "view.base.h"
#include "gl_procs_depth.h"

using namespace ::open_gl::views;
using CDepth = ::open_gl::procs::ver_1_1::CDepth;
using CComp  = CDepth::CComparator;
using ::open_gl::procs::ver_1_1::e_criteria;


#pragma region cls::CBase{}

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: base view is not created"); }

err_code CBase::Create (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Device().Is_valid())
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: base view is already created");

	if (__failed(this->Grid().Create())) return this->m_error = this->Grid().Error();

	CDevice& dev_ctx = this->Device();
	dev_ctx.Surface().Source(TString().Format(_T("context::%s"), CDevice::Class()));

#if (1) // it is not reqiured because fake device format is already found;
	if (__failed(dev_ctx.Create(_h_surface))) { // tries to find a required pixel format and set it to the device context;
		__trace_err_ex_2(this->m_error = dev_ctx.Error()); return this->Error(); // further steps are useless;
	}
#else
	// sets renderer device context format which is received from fake window;
	dev_ctx.Surface() << _h_surface;
	dev_ctx.Format() << fk_ctx().Format().Get();
#endif
#if (1)
	// creates OpenGL draw rendering context;
	CGraphs& graphs = this->Graphs();

	graphs.Surface().Source(TString().Format(_T("renderer::%s"), CGraphs::Class()));
	graphs.Surface() << _h_surface;

	if (__failed(graphs.Create(dev_ctx))) {
		__trace_err_ex_2(this->m_error = graphs.Error());
	}
#endif
	if (__failed(this->Grid().Create())) return this->m_error = this->Grid().Error();

	return this->Error();
}

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	::open_gl::context::CBase* ctx_bases[] = {&this->Graphs(), &this->Device() };

	for (uint32_t i_ = 0; i_ < _countof(ctx_bases); i_++) {
		if (__failed(ctx_bases[i_]->Destroy()))
			this->m_error = ctx_bases[i_]->Error(); // keeps going to the next context; base class outputs error to the trace itself;
	}

	if (__failed(this->Grid().Destroy())) return this->m_error = this->Grid().Error();

	return this->Error();
}

const
CDevice& CBase::Device (void) const { return this->m_device; }
CDevice& CBase::Device (void)       { return this->m_device; }

TError&  CBase::Error (void) const { return this->m_error; }

const
CGraphs& CBase::Graphs (void) const { return this->m_graphs; }
CGraphs& CBase::Graphs (void)       { return this->m_graphs; }    

const
CGrid& CBase::Grid (void) const { return this->m_grid; }
CGrid& CBase::Grid (void)       { return this->m_grid; }     

err_code CBase::Init (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == ::Get_version().Is_base()) {
		static _pc_sz p_err_ver_unsupp = _T("#__e_vers: OpenGL ver %s is not supported");
		__trace_err_ex_2(
			this->m_error <<(err_code)TErrCodes::eExecute::eState = TString().Format(p_err_ver_unsupp, (_pc_sz) ::Get_version().Data().To_str() )
		);
		return this->Error();
	}
	// (1) sets a background color of this view;
	CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) {
		__trace_err_ex_2(bkgnd.Error());
	}

	// (2) this is needed for creating a perspective view of the grid;
	CDepth depth;
	if (__failed((depth.Comp() << true).Error())) {__trace_err_ex_2(this->m_error = depth.Comp().Error()); }
	if (__failed((depth.Comp() << e_criteria::e_lt_eq).Error())) {__trace_err_ex_2(this->m_error = depth.Comp().Error()); }
	return this->Error();
}

#pragma endregion