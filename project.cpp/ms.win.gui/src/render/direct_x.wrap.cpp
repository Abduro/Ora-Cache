/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2025 at 02:50:32.714, UTC+4, Batumi, Tuesday;
	This is Ebo Pack DirectX draw render connect wrapper interface implementation file;
*/
#include "direct_x.wrap.h"

using namespace ebo::boo::gui::render;

/////////////////////////////////////////////////////////////////////////////

CRender_Wrap:: CRender_Wrap (void) {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
}

CRender_Wrap::~CRender_Wrap (void) {
}

/////////////////////////////////////////////////////////////////////////////

TError&   CRender_Wrap::Error (void) const { return this->m_error; }
err_code  CRender_Wrap::Init  (const HWND _h_target) {
	_h_target;
	// (1) sets a target window handle to cfg of the device;
	this->m_error << __METHOD__ << this->m_device.Cfg().Default(_h_target);
	if (this->Error())
		return this->Error();
	// (2) creates the device object with swap chain, that is essential;
	this->m_device.Cfg().Type((TDrvType)CDrv_Type::e_type::e_ref);
	this->m_error << this->m_device.Create(CDrv_Type::e_type::e_ref, true);

	// the error may occur for example on MS Windows of home edition;
	if (this->m_device.Error()) {
	// (2.a) tries to create other device of different adapter type;
	this->m_device.Cfg().Type((TDrvType)CDrv_Type::e_type::e_hard);
	this->m_error << this->m_device.Create(CDrv_Type::e_type::e_hard, true);

	if (this->m_device.Error())
		return this->m_device.Error();
	}
	// (3) creates a texture as a draw surface by swap & chain object, not by the device itself!
	CTexture tex_2d;

	CSwapChain& swp_chain = this->m_device.SwapChain();
	this->m_error << swp_chain.GetZBuffer(tex_2d);
	if (this->Error())
		return swp_chain.Error();

	// (4) sets target object cache;
	this->m_target << this->m_device << tex_2d;

	// (5) creates a render target view;
	this->m_error << this->m_target.Create();
	if (this->m_target.Error())
		return this->m_target.Error();

	return this->Error();
}

err_code  CRender_Wrap::Term (void) {
	this->m_error << __METHOD__ << __s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-clearstate ;
	if (this->m_device.Ctx().Is_valid())
		this->m_device.Ctx().Ptr()->ClearState();


	return this->Error();
}

CTarget& CRender_Wrap::Target (void) { return this->m_target; }

/////////////////////////////////////////////////////////////////////////////

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CRender_Wrap::IEvtFrame_OnSize   (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored: {
	} break;
	}

	return   n_result;
}

err_code CRender_Wrap::IEvtFrame_OnSizing (const eEdges, LPRECT) {

	err_code n_result = __s_false;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////
TRender&  _render(void) {

	static TRender render;
	return render;
}