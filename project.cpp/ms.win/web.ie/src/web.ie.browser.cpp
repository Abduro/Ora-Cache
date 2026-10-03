/*
	Created by Tech_dog (ebontrop@gmail.com) 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library web browser control wrapper class(es) implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:22:40p, UTC+7, Phuket, Rawai, Monday;
	Adopted to v15a on 2-Oct-2018 at 8:33:03p, UTC+7, Novosibirsk, Tuesday;
*/
#if (0)
#include "shared.web.browser.h"
#include "shared.web.brw.wrap.h"
#include "shared.web.obj.access.h"

using namespace ex_ui::web;
using namespace ex_ui::web::core;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace web { namespace details
{
	::ATL::CAxWindow& CWebBrowser_InvalidWindowObjectRef(void)
	{
		static ::ATL::CAxWindow wnd;
		return wnd;
	}
}}}

/////////////////////////////////////////////////////////////////////////////

CWebBrowser:: CWebBrowser(IWebBrowserEventHandler& evt_ref) : m_browser(NULL)
{
	m_error >> __CLASS__ << __METHOD__;
	try { m_browser = new CWebBrowserWrap(evt_ref); } catch (::std::bad_alloc&){ ATLASSERT(0); }
}

CWebBrowser::~CWebBrowser(void)
{
	this->Destroy();
	if (m_browser)
	{
		try { delete m_browser; m_browser = NULL; } catch(...) { ATLASSERT(0); }
	}
}

/////////////////////////////////////////////////////////////////////////////

CStringW      CWebBrowser::Charset(void) const {
	m_error << __METHOD__ << S_OK;
	CStringW cs_charset;
	
	if (!this->IsValid())
		return cs_charset;

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error || NULL == doc_obj)
		return cs_charset;

	_bstr_t bstrCharset;
	m_error = doc_obj->get_charset(bstrCharset.GetAddress());

	if (!m_error)
		cs_charset = (LPCWSTR)bstrCharset;

	return cs_charset;
}

HRESULT       CWebBrowser::Charset(LPCWSTR pszCharset, const bool bRefresh) {
	m_error << __METHOD__ << S_OK;
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error || doc_obj == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}
	m_error = doc_obj->put_charset(_bstr_t(pszCharset));
	if (!m_error && bRefresh)
		this->Refresh();
	return m_error;
}

HRESULT       CWebBrowser::Content(CStringW& _result) const {
	m_error << __METHOD__ << S_OK;
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument3> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error || doc_obj == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}
	::ATL::CComPtr<IHTMLElement> root_;
	m_error = doc_obj->get_documentElement(&root_);
	if (m_error || root_ == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}
	_bstr_t content_;

	m_error = root_->get_outerHTML(content_.GetAddress());
	if (!m_error)
		_result = (LPCWSTR)content_;

	return m_error;
}

HRESULT       CWebBrowser::Create(const HWND hParent, const RECT& rcArea, const bool bVisible) {
	m_error << __METHOD__ << S_OK;

	if (!m_browser)
		return (m_error = OLE_E_BLANK);
	::ATL::CComPtr<IServiceProvider> pProvider;
	m_error = m_browser->CreateObject(hParent, rcArea, pProvider, bVisible);
	return m_error;
}

HRESULT       CWebBrowser::Create(const HWND hParent, const RECT& rcArea, ::ATL::CComPtr<IServiceProvider>& pProvider) {
	m_error << __METHOD__ << S_OK;
	if (!m_browser)
		return (m_error = OLE_E_BLANK);
	m_error = m_browser->CreateObject(hParent, rcArea, pProvider, true);
	return m_error;
}

HRESULT       CWebBrowser::Destroy(void) {
	m_error << __METHOD__ << S_OK;
	if (m_browser)
		if (m_browser->IsWindow()) m_browser->SendMessage(WM_CLOSE);
	m_error.Reset();
	return  S_OK;
}

TErrorRef     CWebBrowser::Error(void)const { return m_error; }

HRESULT       CWebBrowser::ExecuteScript(LPCWSTR lpszScript) {
	m_error << __METHOD__ << S_OK;

	if (!lpszScript || ::_tcslen(lpszScript) < 1)
		return (m_error = E_INVALIDARG);

	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);

	if (m_error || doc_obj == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}
	::ATL::CComPtr<IHTMLWindow2> window;
	m_error = doc_obj->get_parentWindow(&window);
	if (m_error)
		return m_error;
	_variant_t var_;
	try
	{
		m_error = window->execScript(_bstr_t(lpszScript), _bstr_t(_T("JavaScript")), &var_);
	}
	catch(_com_error& err_ref)
	{
		m_error = err_ref.Error();
		m_error = (LPCWSTR)err_ref.Description();
	}
	return m_error;
}

const
CAxWindow&    CWebBrowser::GetAxWindowRef(void) const
{
	if (!m_browser)
		return details::CWebBrowser_InvalidWindowObjectRef();
	else
		return *m_browser;
}

CAxWindow&    CWebBrowser::GetAxWindowRef(void)
{
	if (!m_browser)
		return details::CWebBrowser_InvalidWindowObjectRef();
	else
		return *m_browser;
}

HRESULT       CWebBrowser::GetScriptObject(::ATL::CComPtr<IDispatch>& pObject) const {
	m_error << __METHOD__ << S_OK;
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error || doc_obj == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}

	m_error = doc_obj->get_Script(&pObject);
	return m_error;
}

bool          CWebBrowser::IsBusy(void)const
{
	if (!this->IsValid())
		return false;
	if (!m_web_obj)
		return false;
	VARIANT_BOOL val_ = VARIANT_FALSE;
	m_error = m_web_obj->get_Busy(&val_);
	if (m_error)
		return false;
	else
		return (VARIANT_TRUE == val_);
}

bool          CWebBrowser::IsValid(void)const {
	if (NULL == m_browser/* || NULL == m_web_obj*/) // we cannot control COM object here, because it may be NULL;
		return false;
	return !!m_browser->IsWindow();
}

#if defined(_use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_)

HRESULT       CWebBrowser::Open(::ATL::CComPtr<IStream>& p_stream) {
	m_error << __METHOD__ << S_OK;

	if (!p_stream)
		return (m_error = E_INVALIDARG);
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error || doc_obj == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}

	::ATL::CComQIPtr<IPersistStreamInit> p_pers;
	m_error = doc_obj.QueryInterface(&p_pers);
	if (m_error)
		return m_error;
	if (!p_pers)
		return (m_error = E_NOINTERFACE);

	m_error = p_pers->InitNew();
	if (m_error)
		return m_error;

	m_browser->m_bStreamObject = true;

	m_error = p_pers->Load(p_stream);
	return m_error;
}

#else

HRESULT       CWebBrowser::Open(::ATL::CComPtr<IMoniker>& p_moniker)
{
	TRACE_FUNC();
	if (!p_moniker)
		return (m_error = E_INVALIDARG);
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error)
	{
		TRACE_ERR__a2(_T("Cannot access document object: code=0x%x, desc=%s"),
			m_error.GetHresult(),
			m_error.GetDescription());
		return m_error;
	}

	CComQIPtr<IPersistMoniker> p_doc_moniker(doc_obj);
	if (!p_doc_moniker)
	{
		m_error = E_NOINTERFACE;
		TRACE_ERR__a2(_T("Cannot access persistent object: code=0x%x, desc=%s"),
			m_error.GetHresult(),
			m_error.GetDescription());
		return m_error;
	}
	m_error = p_doc_moniker->Load(TRUE, p_moniker, NULL, STGM_READ);
	if (m_error)
	{
		TRACE_ERR__a2(_T("Cannot load the data from moniker: code=0x%x, desc=%s"),
			m_error.GetHresult(),
			m_error.GetDescription());
	}
	return m_error;
}

HRESULT          CWebBrowser::Open(const CRawData& raw_data)
{
	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);
	if (!raw_data.IsValid())
		return (m_error = raw_data.Error());
	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_obj);
	if (m_error)
		return m_error;

	VARIANT* pData = NULL;
	SAFEARRAY* psa = ::SafeArrayCreateVector(VT_VARIANT, 0, 1);
	if (!psa)
		return (m_error = E_OUTOFMEMORY);
	m_error = ::SafeArrayAccessData(psa,(LPVOID*)&pData);
	if (!m_error)
	{
		::ATL::CStringW cs_data(raw_data.ToString());
		pData->vt   = VT_BSTR;
		pData->bstrVal = cs_data.AllocSysString();
		m_error = ::SafeArrayUnaccessData(psa);
		m_error = doc_obj->write(psa);
	}
	if (psa)
		::SafeArrayDestroy(psa);
	return m_error;
}

#endif

HRESULT       CWebBrowser::Open(LPCWSTR pURL) {
	m_error << __METHOD__ << S_OK;

	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	if (NULL == pURL || ::_tcslen(pURL) < 10)
		return (m_error = E_INVALIDARG);

	::ATL::CComPtr<IUnknown> pControl;
	m_error = m_browser->QueryControl(&pControl);
	if (!m_error)
	{
		m_web_obj = pControl;
		if (m_web_obj)
		{
			m_browser->m_bStreamObject = false;

			::ATL::CComVariant vUrl(pURL);
			m_error = m_web_obj->Navigate2(&vUrl, 0, 0, 0, 0);
		}
		else m_error = E_NOTIMPL;
	}
	return m_error;
}

HRESULT       CWebBrowser::Print(void) {
	m_error << __METHOD__ << S_OK;

	HRESULT hr_ = m_error;
	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	hr_ = acc.DocumentObject(doc_obj);
	if (FAILED(hr_) || NULL == doc_obj) // very important for check document creation; hr_ can be S_FALSE;
		return (m_error = (hr_ = __DwordToHresult(ERROR_INVALID_STATE)));

	::ATL::CComPtr<IOleCommandTarget> pCmdTarget;
	hr_ = doc_obj->QueryInterface(&pCmdTarget);
	if (FAILED(hr_) || pCmdTarget == NULL) {
		m_error = hr_;
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}

	if (pCmdTarget) {
		hr_ = pCmdTarget->Exec(
			NULL, OLECMDID_PRINT, OLECMDEXECOPT_PROMPTUSER, NULL, NULL
		);
	}

	return m_error;
}

HRESULT       CWebBrowser::PrintPreview(void) {
	m_error << __METHOD__ << S_OK;

	HRESULT hr_ = m_error;
	::ATL::CComPtr<IHTMLDocument2> doc_obj;

	CWebBrowserObjectAccessor acc(*m_browser);
	hr_ = acc.DocumentObject(doc_obj);
	if (FAILED(hr_))
		return (m_error = hr_);

	::ATL::CComPtr<IOleCommandTarget> pCmdTarget;
	hr_ = doc_obj->QueryInterface(&pCmdTarget);

	if (FAILED(hr_) || pCmdTarget == NULL) {
		m_error = hr_;
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}

	if (pCmdTarget) {
		hr_ = pCmdTarget->Exec(
			NULL, OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_PROMPTUSER, NULL, NULL
		);
	}

	return m_error;
}

HRESULT       CWebBrowser::Redirect(LPCWSTR pTarget, const bool bAsync) {
	m_error << __METHOD__ << S_OK;

	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);
	if (!bAsync)
		return (m_error = E_NOTIMPL);

	m_error.Clear();
	m_browser->m_async_data = _variant_t(pTarget);
	m_browser->PostMessage(CWebBrowserWrap::eAsyncRedirect, 0, 0);

	return m_error;
}

HRESULT       CWebBrowser::Refresh(void) {
	m_error << __METHOD__ << S_OK;

	if (this->IsValid() == false)
		return (m_error = OLE_E_BLANK);

	_variant_t v_level((long)REFRESH_IFEXPIRED);

	if (m_web_obj)
		m_error = m_web_obj->Refresh();(v_level);
	return m_error;
}

HRESULT       CWebBrowser::SetBackColor  (const COLORREF _clr) {
	_clr;
	m_error << __METHOD__ << S_OK;
	if (NULL == m_browser || NULL == m_web_obj)
		return (m_error << OLE_E_BLANK);

//	m_error = m_browser->SetBackColor(_clr);
	HWND h_browser = NULL;
	LONG_PTR l_ptr = NULL;
	m_error = m_web_obj->get_HWND(&l_ptr);

	h_browser = reinterpret_cast<HWND>(l_ptr);

	return m_error;
}

void          CWebBrowser::SetInitialized(void) {
	if (m_browser)
		m_browser->m_bInited = true;
}

bool          CWebBrowser::Silent(void)const
{
	if (!m_web_obj)
		return false;
	VARIANT_BOOL v_result = VARIANT_FALSE;
	m_web_obj->get_Silent( &v_result );
	return (VARIANT_TRUE == v_result );
}

HRESULT       CWebBrowser::Silent(const bool b_set)
{
	if (!m_web_obj)
		return OLE_E_BLANK;
	const bool bChanged = (this->Silent() != b_set);
	if (!bChanged)
		return S_FALSE;
	HRESULT hr_ = m_web_obj->put_Silent(b_set ? VARIANT_TRUE : VARIANT_FALSE);
	return  hr_;
}

CStringW      CWebBrowser::Title(void) const {
	m_error << __METHOD__ << S_OK;

	::ATL::CStringW cs_title;
	if (!this->IsValid())
		return cs_title;

	::ATL::CComPtr<IHTMLDocument2> doc_ref;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_ref);
	if (m_error || doc_ref == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return cs_title;
	}

	_bstr_t bs_title;
	m_error = doc_ref->get_title(bs_title.GetAddress());
	if (m_error)
		return cs_title;
	cs_title = bs_title.GetBSTR();
	return cs_title;
}

HRESULT       CWebBrowser::Title(LPCWSTR pTitle) {
	m_error << __METHOD__ << S_OK;

	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);

	::ATL::CComPtr<IHTMLDocument2> doc_ref;

	CWebBrowserObjectAccessor acc(*m_browser);
	m_error = acc.DocumentObject(doc_ref);

	if (m_error || doc_ref == NULL) {
		if (m_error.Is() == false)
			m_error = E_NOINTERFACE;
		return m_error;
	}
	_bstr_t bs_title(pTitle);
	m_error = doc_ref->put_title(bs_title);
	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CWebBrowser::operator CAxWindow&(void)
{
	return this->GetAxWindowRef();
}
#endif