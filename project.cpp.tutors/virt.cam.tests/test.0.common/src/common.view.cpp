/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2026 at 12:40:24.629, UTC+4, Batumi, Monday;
	This is virtual camera common GUI base view interface implementation file;
*/
#include "common.view.h"

using namespace ::test::gui::views;

#pragma region cls::CBase{}

CBase::CBase (void) : m_browser(*this) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CBase::Create (const HWND hParent, const rect_t& rect) {
	hParent; rect;
	this->m_error <<__METHOD__<<__s_ok;
	if (0 == hParent || false == !!::IsWindow(hParent))
		return this->m_error <<__e_hwnd = _T("__e_hwnd: the parent window handle is invalid");

	this->m_error << this->m_browser.Create(hParent, rect, true);
	if (this->Error())
		this->m_error = this->m_browser.Error();

	return this->Error();
}

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_error << this->m_browser.Destroy();
	if (this->Error())
		this->m_error = this->m_browser.Error();
	return this->Error();
}

TError& CBase::Error (void) const { return this->m_error; }

err_code CBase::Open (_pc_sz _p_url) {
	_p_url;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->m_browser.State().Is_valid() == false)
		return this->m_error = this->m_browser.State().Error();

	CLocator locator(_p_url);
	if (locator.Error())
		return this->m_error = locator.Error();

//	this->m_browser.Open(locator.URL());
	if (false) {}
	else if (__failed(this->m_browser.Open(locator.URL()))) this->m_error = this->m_browser.Error();
	else if (__failed(this->m_browser.Refresh())) this->m_error = this->m_browser.Error();
	else {}
	return this->Error();
}

err_code CBase::WbEvt_BeforeNavigate  (_pc_sz _p_url) {_p_url; return __e_not_impl; }
err_code CBase::WbEvt_DocumentComplete(_pc_sz _p_url, const bool _b_use_stream) { _p_url; _b_use_stream;  return __e_not_impl; }
err_code CBase::WbEvt_OnMouseMessage  (const MSG&) { return __e_not_impl; }

#pragma endregion