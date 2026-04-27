/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 02:01:31.446, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' view base interface implementation file;
*/
#include "view.base.h"

using namespace ex_ui::draw::open_gl::views;

#pragma region cls::CBase{}

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: base view is not created"); }

err_code CBase::Create (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Device().Is_valid())
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: base view is already created");

	CDevice& dev_ctx = this->Device();
	dev_ctx.Target().Source(TString().Format(_T("context::%s"), CDevice::Class()));

#if (1) // it is not reqiured because fake device format is already found;
	if (__failed(dev_ctx.Create(_h_surface))) { // tries to find a required pixel format and set it to the device context;
		__trace_err_ex_2(this->m_error = dev_ctx.Error()); return this->Error(); // further steps are useless;
	}
#else
	// sets renderer device context format which is received from fake window;
	dev_ctx.Target() << _h_surface;
	dev_ctx.Format() << fk_ctx().Format().Get();
#endif
	// creates OpenGL draw rendering context;
	CGraphics& renderer = this->Renderer();

	renderer.Target().Source(TString().Format(_T("renderer::%s"), CGraphics::Class()));
	renderer.Target() << _h_surface;

	if (__failed(renderer.Create(dev_ctx))) {
		__trace_err_ex_2(this->m_error = renderer.Error()); // return this->Error();
	}

	return this->Error();
}

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	context::CBase* ctx_bases[] = { &this->Renderer(), &this->Device() };

	for (uint32_t i_ = 0; i_ < _countof(ctx_bases); i_++) {
		if (__failed(ctx_bases[i_]->Destroy()))
			this->m_error = ctx_bases[i_]->Error(); // keeps going to the next context; base class outputs error to the trace itself;
	}

	return this->Error();
}

const
CDevice& CBase::Device (void) const { return this->m_device; }
CDevice& CBase::Device (void)       { return this->m_device; }

TError&  CBase::Error (void) const { return this->m_error; }

const
CGraphs& CBase::Renderer (void) const { return this->m_graphs; }
CGraphs& CBase::Renderer (void)       { return this->m_graphs; }    

#pragma endregion