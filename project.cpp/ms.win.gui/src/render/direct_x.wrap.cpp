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
	this->m_error << __METHOD__ << this->m_device.Cfg().Default(_h_target);

	if (this->Error())
		return this->Error();
	this->m_device.Cfg().Type((TDrvType)CDrv_Type::e_type::e_ref);
	this->m_error << this->m_device.Create(CDrv_Type::e_type::e_ref, true);

	return this->Error();
}

err_code  CRender_Wrap::Term (void) {
	this->m_error << __METHOD__ << __s_ok;
	return this->Error();
}

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