/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser object accessor class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:05:09p, UTC+7, Phuket, Rawai, Monday;
*/
#include "web.ie.accessor.h"

using namespace ::ex_ui::web::IE::core;

namespace ex_ui { namespace web { namespace IE { namespace core { namespace _impl {

	class CDoc_iface_loader {
	public:
		 CDoc_iface_loader (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
		 CDoc_iface_loader (const CDoc_iface_loader&) = delete; CDoc_iface_loader (CDoc_iface_loader&&) = delete;
		~CDoc_iface_loader (void) = default;

		TError& Error (void) const { return this->m_error; }

	private:
		CDoc_iface_loader& operator = (const CDoc_iface_loader&) = delete; CDoc_iface_loader& operator = (CDoc_iface_loader&&) = delete;
		CError m_error;
	};

}}}}} using namespace ::ex_ui::web::IE::core::_impl;

#pragma region cls::CAccessor{}

CAccessor::CAccessor (CAxWindow& browser_ref) : m_browser(browser_ref) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CAccessor::Error (void) const { return this->m_error; }

err_code CAccessor::CmdTarget (TCmdTargetPtr& target_ref) {
	target_ref;
	TDocument2Ptr pDocument;
	if (__failed(this->Document2(pDocument))) return this->Error();

	this->m_error <<__METHOD__ << pDocument->QueryInterface(&target_ref);

	if (false) {}
	else if (this->Error()) {}
	else if (nullptr == target_ref) this->m_error <<__e_no_iface;
	else {}
	return this->Error();
}

err_code CAccessor::Document0 (TDispatchPtr& doc_ref) {
	doc_ref;
	this->m_error <<__METHOD__<<__s_ok;

	if (!m_browser.IsWindow())
		return this->m_error << __e_hwnd;
	
	do {
		CComPtr<IUnknown> pControl;
		this->m_error << m_browser.QueryControl(&pControl); if (this->m_error) break;

		CComQIPtr<IWebBrowser2> pBrowser;
		this->m_error << pControl.QueryInterface(&pBrowser); if (this->m_error) break;

		if (!pBrowser) { this->m_error <<__e_not_impl; break; }
		// https://learn.microsoft.com/en-us/previous-versions//aa752116(v=vs.85)?redirectedfrom=MSDN ;
		this->m_error << pBrowser->get_Document(&doc_ref);
	} while (true == false);

	return this->Error();
}

err_code CAccessor::Document2 (TDocument2Ptr& doc_ref) {
	doc_ref;
	TDispatchPtr pDocument;
	const err_code n_result = this->Document0(pDocument);
	if (n_result != __s_ok)
		return n_result;

	this->m_error <<__METHOD__<<__s_ok;

	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa752574(v=vs.85) ;
	TDocument2Ptr pHtmlDocument;
	this->m_error << pDocument.QueryInterface(&pHtmlDocument);
 
	if (false){}
	else if (this->Error()) {}
	else if (false == pHtmlDocument) { this->m_error <<__e_no_iface; }
	else {
		doc_ref = pHtmlDocument;
	}
	return this->Error();
}

err_code CAccessor::Document3 (TDocument3Ptr& doc_ref) {
	doc_ref;
	TDispatchPtr pDocument;
	const err_code n_result = this->Document0(pDocument);
	if (n_result != __s_ok)
		return n_result;

	this->m_error <<__METHOD__<<__s_ok;

	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa752541(v=vs.85) ;
	TDocument3Ptr pHtmlDocument;
	this->m_error << pDocument.QueryInterface(&pHtmlDocument);

	if (false){}
	else if (this->Error()) {}
	else if (false == pHtmlDocument) { this->m_error <<__e_no_iface; }
	else {
		doc_ref = pHtmlDocument;
	}
	return this->Error();
}

err_code CAccessor::Element (TElementPtr& elm_ref, _pc_sz _p_el_id) {
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_el(_p_el_id); cs_el.Trim();

	if (cs_el.IsEmpty())
		return this->m_error <<__e_inv_arg;

	TDocument3Ptr pHtmlDocument;
	
	if (__failed(this->Document3(pHtmlDocument)))
		return this->Error();

	this->m_error << pHtmlDocument->getElementById(_bstr_t(_p_el_id), &elm_ref);
	if (false){}
	else if (this->Error()) {}
	else if (false == elm_ref) { this->m_error <<__e_not_found; }

	return this->Error();
}

#pragma endregion