/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-May-2025 at 00:59:34.953, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX generic view interface implementation file;
*/
#include "direct_x.view.h"

using namespace ex_ui::draw::direct_x::views;
using namespace ex_ui::draw::direct_x::views::_11;

/////////////////////////////////////////////////////////////////////////////

CViewPort:: CViewPort (void) : m_port{0} {}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  CViewPort::Print (const TViewPort&, const e_print) {
	CString cs_out;
	return  cs_out;
}
CString  CViewPort::Print (const e_print _e_opt) {
	return CViewPort::Print(this->Raw(), _e_opt);
}
#endif
const
TViewPort& CViewPort::Raw (void) const { return this->m_port; }
TViewPort& CViewPort::Raw (void)       { return this->m_port; }

err_code   CViewPort::SetSize(HWND const _target) {
	_target;
	err_code n_result = __s_ok;

	if (!::IsWindow(_target))
		return n_result = __e_hwnd;

	this->m_port.TopLeftX = 0.0f;
	this->m_port.TopLeftY = 0.0f;

	this->m_port.MinDepth = 0.0f;
	this->m_port.MaxDepth = 1.0f;

	RECT rc_client = {0};
	::GetClientRect(_target, &rc_client);
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_viewport ;
	// *important*: no negative values neither for left nor top; the same is for a width and for a height;
	if (::IsRectEmpty(&rc_client)) {
		n_result = __e_rect;
		// sets just default values, mainly for debug purposes, but in any case, this is not good approach;
		this->m_port.Height = float(256);
		this->m_port.Width  = float(256);
	}
	else {
		this->m_port.Height = float(rc_client.bottom - rc_client.top);
		this->m_port.Width  = float(rc_client.right - rc_client.left);
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CView:: CView (void) { this->m_error >>__CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError& CView::Error (void) const { return this->m_error; }
bool    CView::Is_valid (void) const { return nullptr != this->View(); }

err_code  CView::Get (TResPtr& _p_res) const {
	_p_res;
	this->m_error << __METHOD__ << __s_ok;
	if (_p_res)
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11view-getresource ;
	this->View()->GetResource(&_p_res);
	if (nullptr == _p_res)
		this->m_error << __e_no_iface = _T("The resource interface is not inherited;");

	return this->Error();
}

err_code  CView::Set (const CDevice& _device) {
	_device;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _device.Is_valid())
		return this->m_error << __e_invalid_arg;

	if (this->m_device.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_device.Ptr(_device.Ptr());

	return this->Error();
}
#if (0)
err_code  CView::Set (const CSwapChain& _chain) {
	_chain;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _chain.Is_valid())
		return this->m_error << __e_invalid_arg;

	if (this->m_swap.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_swap.Ptr(_chain.Ptr());

	return this->Error();
}
#else
err_code  CView::Set (const CTexture& _tex) {
	_tex;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _tex.Is_valid())
		return this->m_error << __e_invalid_arg;

	if (this->m_texture.Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	this->m_texture.Ptr(_tex.Ptr());

	return this->Error();
}
#endif

const
TViewPtr& CView::View (void) const { return this->m_p_view; }
err_code  CView::View (const TViewPtr& _p_res) {
	_p_res;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_res)
		return this->m_error << __e_pointer;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	this->m_p_view = _p_res;

	return this->Error();
}