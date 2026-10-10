/*
	Created by Tech_dog (ebontrop@gmail.com) 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library web browser control wrapper class(es) implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:22:40p, UTC+7, Phuket, Rawai, Monday;
	Adopted to v15a on 2-Oct-2018 at 8:33:03p, UTC+7, Novosibirsk, Tuesday;
*/
#include "web.ie.browser.h"
#include "web.ie.accessor.h"
#include "web.ie.window.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::core;

static CWebBrowser* p_browser = 0;

#pragma region cls::CWebBrowser{}

CWebBrowser:: CWebBrowser(IWbEvtHandler& evt_ref) : m_command(m_window), m_content(m_window), m_script(m_window) {
	evt_ref;
	m_error >> __CLASS__ << __METHOD__;
	try { m_window = ::std::make_shared<CBrowserWnd>(evt_ref); } catch (::std::bad_alloc&){ ATLASSERT(0); this->m_error <<__e_no_memory; }
	p_browser = this;
}

CWebBrowser::~CWebBrowser (void)
{
	this->Destroy();
#if (0)
	if (m_window) {
		try { delete m_window; m_window = 0; } catch(...) { ATLASSERT(0); this->m_error <<__e_no_memory; }
	}
#endif
}
const
CCommand& CWebBrowser::Command (void) const { return this->m_command; }
CCommand& CWebBrowser::Command (void)       { return this->m_command; }
const
CContent& CWebBrowser::Content (void) const { return this->m_content; }
CContent& CWebBrowser::Content (void)       { return this->m_content; }

err_code  CWebBrowser::Create (const HWND hParent, const rect_t& rcArea, const bool bVisible) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->State() == false)
		return this->m_error = this->Error();

	::ATL::CComPtr<IServiceProvider> pProvider;
	this->m_error << this->m_window->CreateObject(hParent, rcArea, pProvider, bVisible);
	return this->Error();
}

err_code  CWebBrowser::Create (const HWND hParent, const rect_t& rcArea, CComPtr<IServiceProvider>& pProvider) {
	this->m_error << __METHOD__ << __s_ok;
	
	if (this->State() == false)
		return this->m_error = this->Error();

	this->m_error <<m_window->CreateObject(hParent, rcArea, pProvider, true);
	return this->Error();
}

err_code  CWebBrowser::Destroy (void) {
	this->m_error << __METHOD__ << __s_ok;
	if (this->m_window)
		if (this->m_window->IsWindow()) this->m_window->SendMessage(WM_CLOSE);

	return this->Error();
}
const
TWebBrwPtr& CWebBrowser::Ctrl (void) const { return this->m_browser; }
TWebBrwPtr& CWebBrowser::Ctrl (void)       { return this->m_browser; }

TErrorRef CWebBrowser::Error (void) const { return m_error; }
const
CScript&  CWebBrowser::Script (void) const { return this->m_script; }
CScript&  CWebBrowser::Script (void)       { return this->m_script; }
const
CState&   CWebBrowser::State (void) const { return this->m_state; }
CState&   CWebBrowser::State (void)       { return this->m_state; }

static ::ATL::CAxWindow inv_wnd;
const
CAxWindow& CWebBrowser::Window (void) const { return this->m_window == nullptr ? inv_wnd : *this->m_window; }
CAxWindow& CWebBrowser::Window (void)       { return this->m_window == nullptr ? inv_wnd : *this->m_window; }

#pragma endregion

TIEBrowser* ::Get_IE_ptr (void) { return p_browser; }

#if (0)

namespace ex_ui { namespace web { namespace details
{
	::ATL::CAxWindow& CWebBrowser_InvalidWindowObjectRef(void)
	{
		static ::ATL::CAxWindow wnd;
		return wnd;
	}
}}}

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

HRESULT       CWebBrowser::Redirect(LPCWSTR pTarget, const bool bAsync) {
	m_error << __METHOD__ << S_OK;

	if (!this->IsValid())
		return (m_error = OLE_E_BLANK);
	if (!bAsync)
		return (m_error = E_NOTIMPL);

	m_error.Clear();
	m_browser->m_async_data = _variant_t(pTarget);
	m_browser->PostMessage(CWebControl::eAsyncRedirect, 0, 0);

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

void          CWebBrowser::SetInitialized(void) {
	if (m_browser)
		m_browser->m_bInited = true;
}

/////////////////////////////////////////////////////////////////////////////

CWebBrowser::operator CAxWindow&(void)
{
	return this->GetAxWindowRef();
}
#endif