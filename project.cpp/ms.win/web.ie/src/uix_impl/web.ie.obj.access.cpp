/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser object accessor class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:05:09p, UTC+7, Phuket, Rawai, Monday;
*/
#include "shared.web.obj.access.h"
#include "shared.web.browser.h"

using namespace ex_ui::web::core;

/////////////////////////////////////////////////////////////////////////////

CWebBrowserObjectAccessor:: CWebBrowserObjectAccessor(::ATL::CAxWindow& browser_ref) : m_browser(browser_ref)
{
}

CWebBrowserObjectAccessor::~CWebBrowserObjectAccessor(void)
{
}

/////////////////////////////////////////////////////////////////////////////

HRESULT    CWebBrowserObjectAccessor::GenericDocument(::ATL::CComPtr<IDispatch>& doc_ref)
{
	if (!m_browser.IsWindow())
		return OLE_E_BLANK;
	::ATL::CComPtr<IUnknown> pControl;
	HRESULT hr_ = m_browser.QueryControl(&pControl);
	if (S_OK != hr_)
		return  hr_;
	::ATL::CComQIPtr<IWebBrowser2> pBrowser;
	hr_ = pControl.QueryInterface(&pBrowser);
	if (FAILED(hr_))
		return hr_;

	if (!pBrowser)
		return (hr_ = E_NOINTERFACE);
	hr_ = pBrowser->get_Document(&doc_ref);
	return hr_;
}

HRESULT    CWebBrowserObjectAccessor::DocumentObject (::ATL::CComPtr<IHTMLDocument2>& doc_ref)
{
	::ATL::CComPtr<IDispatch> pGenericDocument;
	HRESULT hr_ = this->GenericDocument(pGenericDocument);
	if (S_OK != hr_)
		return  hr_;
	::ATL::CComQIPtr<IHTMLDocument2> pHtmlDocument;
	hr_ = pGenericDocument.QueryInterface(&pHtmlDocument);
	if (FAILED(hr_))
		return hr_;
	if (!pHtmlDocument)
		return (hr_ = E_NOINTERFACE);
	doc_ref = pHtmlDocument;
	hr_ = (doc_ref ? S_OK : E_NOINTERFACE);
	return hr_;
}

HRESULT    CWebBrowserObjectAccessor::DocumentObject (::ATL::CComPtr<IHTMLDocument3>& doc_ref)
{
	::ATL::CComPtr<IDispatch> pGenericDocument;
	HRESULT hr_ = this->GenericDocument(pGenericDocument);
	if (S_OK != hr_)
		return  hr_;
	::ATL::CComQIPtr<IHTMLDocument3> pHtmlDocument;
	hr_ = pGenericDocument.QueryInterface(&pHtmlDocument);
	if (FAILED(hr_))
		return hr_;
	if (!pHtmlDocument)
		return (hr_ = E_NOINTERFACE);
	doc_ref = pHtmlDocument;
	hr_ = (doc_ref ? S_OK : E_NOINTERFACE);
	return hr_;
}

HRESULT    CWebBrowserObjectAccessor::ElementObject  (::ATL::CComPtr<IHTMLElement>&   elm_ref, LPCTSTR pId)
{
	if (!pId || ::_tcslen(pId) < 1)
		return E_INVALIDARG;
	::ATL::CComPtr<IHTMLDocument3> pHtmlDocument;
	HRESULT hr_ = this->DocumentObject(pHtmlDocument);
	if (S_OK != hr_)
		return  hr_;
	hr_ = pHtmlDocument->getElementById(_bstr_t(pId), &elm_ref);
	if (S_OK == hr_ && !elm_ref)
		hr_ = TYPE_E_ELEMENTNOTFOUND;
	return  hr_;
}