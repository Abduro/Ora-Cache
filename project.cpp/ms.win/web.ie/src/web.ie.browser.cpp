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

CWebBrowser:: CWebBrowser(IWbEvtHandler& evt_ref) : m_command(m_host), m_content(m_host), m_script(m_host), m_state(this) {
	evt_ref;
	m_error >> __CLASS__ << __METHOD__;
	try { m_host = ::std::make_shared<CBrowserWnd>(evt_ref); } catch (::std::bad_alloc&){ ATLASSERT(0); this->m_error <<__e_no_memory; }
	p_browser = this;
}

CWebBrowser::~CWebBrowser (void)
{
	this->Destroy();
#if (0)
	if (m_host) {
		try { delete m_host; m_host = 0; } catch(...) { ATLASSERT(0); this->m_error <<__e_no_memory; }
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

	if (this->Host() == nullptr)
		return this->m_error << __e_not_inited;

	::ATL::CComPtr<IServiceProvider> pProvider;
	this->m_error << this->m_host->CreateObject(hParent, rcArea, pProvider, bVisible);
	if (this->m_error)
		this->m_error = this->m_host->Error();
	else if (nullptr == this->m_browser) { // checks for browser control object validity;
		CComPtr<IUnknown> pControl;
		this->m_error << this->m_host->QueryControl(&pControl);
		if (this->Error() == false) {
			this->m_browser = pControl;
		}
	}
	return this->Error();
}

err_code  CWebBrowser::Create (const HWND hParent, const rect_t& rcArea, CComPtr<IServiceProvider>& pProvider) {
	this->m_error << __METHOD__ << __s_ok;
	
	if (this->Host() == nullptr)
		return this->m_error << __e_not_inited;

	this->m_error << m_host->CreateObject(hParent, rcArea, pProvider, true); // creates a web browser control instance too;
	if (this->m_error)
		this->m_error = this->m_host->Error();
	else if (nullptr == this->m_browser) { // checks for browser control object validity;
		CComPtr<IUnknown> pControl;
		this->m_error << this->m_host->QueryControl(&pControl);
		if (this->Error() == false) {
			this->m_browser = pControl;
		}
	}
	return this->Error();
}

err_code  CWebBrowser::Destroy (void) {
	this->m_error << __METHOD__ << __s_ok;
	if (this->m_host)
		if (this->m_host->IsWindow()) this->m_host->SendMessage(WM_CLOSE);
	if (this->Ctrl())
		this->Ctrl().Release();

	return this->Error();
}
const
TWebBrwPtr& CWebBrowser::Ctrl (void) const { return this->m_browser; }
TWebBrwPtr& CWebBrowser::Ctrl (void)       { return this->m_browser; }

TErrorRef   CWebBrowser::Error (void) const { return m_error; }
const
TBrwWndPtr& CWebBrowser::Host (void) const { return this->m_host; }
TBrwWndPtr& CWebBrowser::Host (void)       { return this->m_host; }     

#if defined(_use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_)
err_code  CWebBrowser::Open (CComPtr<IStream>& p_stream) {
	p_stream;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == p_stream)
		return m_error <<__e_inv_arg = _T("__e_inv_arg: input stream pointer is invalid");

	if (false == this->State())
		return this->m_error = this->State().Error();

	TDocument2Ptr pDocument;

	CAccessor acc(*m_host);
	this->m_error << acc.Document2(pDocument);
	if (this->Error())
		return this->Error();

	CComQIPtr<IPersistStreamInit> p_pers;
	this->m_error << pDocument.QueryInterface(&p_pers);

	if (false){}
	else if (this->Error()){}
	else if (nullptr == p_pers) { this->m_error <<__e_no_iface; }
	else if (this->m_error << p_pers->InitNew()){}
	else {
		this->m_host->m_bStreamObject = true;
		this->m_error << p_pers->Load(p_stream);
	}
	return this->Error();
}
#else
err_code  CWebBrowser::Open (CComPtr<IMoniker>& _p_moniker) {
	_p_moniker;
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_moniker)
		return this->m_error <<__e_inv_arg = _T("__e_inv_arg: input moniker pointer is invalid");

	if (false == this->State())
		return this->m_error = this->State().Error();

	TDocument2Ptr pDocument;

	CAccessor acc(*m_host);
	this->m_error << acc.Document2(pDocument);
	if (this->Error())
		return this->Error();

	CComQIPtr<IPersistMoniker> p_moniker(pDocument);

	if (false){}
	else if (nullptr == p_moniker) { this->m_error <<__e_no_iface = _T("Moniker persistent interface is not implemented"); }
	else if (this->m_error << p_moniker->Load(true, _p_moniker, 0, STGM_READ)) { this->m_error = _T("Cannot load the data from moniker"); }
	else {}
	return this->Error();
}

err_code  CWebBrowser::Open (const TRawData& raw_data) {
	raw_data;
	this->m_error << __METHOD__ << __s_ok;

	if (false == raw_data.IsValid())
		return this->m_error = raw_data.Error();

	if (false == this->State())
		return this->m_error = this->State().Error();
	
	TDocument2Ptr pDocument;

	CAccessor acc(*m_host);
	this->m_error << acc.Document2(pDocument);
	if (this->Error())
		return this->Error();
	// https://learn.microsoft.com/en-us/windows/win32/api/oleauto/nf-oleauto-safearraycreatevector ;
	SAFEARRAY* psa = ::SafeArrayCreateVector(VT_VARIANT, 0, 1);
	if (nullptr == psa)
		return this->m_error <<__e_no_memory;

	VARIANT* pData = 0;
	this->m_error << ::SafeArrayAccessData(psa, (void**)&pData);
	if (false == this->Error()) {
		CString cs_data;
		this->m_error << raw_data.ToStringUtf16(cs_data); // it is supposed the project settings use unicode string;
		if (false == this->Error()) {
			pData->vt = VT_BSTR;
			pData->bstrVal = cs_data.AllocSysString();
			m_error << ::SafeArrayUnaccessData(psa); // getting possible error code is useless in such context;
			m_error << pDocument->write(psa);
		}
	}
	this->m_error << ::SafeArrayDestroy(psa); // https://learn.microsoft.com/en-us/windows/win32/api/oleauto/nf-oleauto-safearraydestroy ;
	return this->Error();
}
#endif
#include <atlutil.h>

err_code  CWebBrowser::Open (_pc_sz pURL) {
	pURL;
	this->m_error << __METHOD__ <<__s_ok;

	CString cs_url(pURL); cs_url.Trim();

	if (cs_url.IsEmpty() || false == CUrl().CrackUrl((_pc_sz)cs_url)) // https://learn.microsoft.com/en-us/cpp/atl/reference/curl-class ;
		return this->m_error <<__e_inv_arg = _T("__e_inv_arg: Input URL string is not valid");

	if (false == this->State())
		return this->m_error = this->State().Error();

	this->Host()->m_bStreamObject = false; 
	CComVariant vUrl((_pc_sz)cs_url);

	this->m_error << this->Ctrl()->Navigate2(&vUrl, 0, 0, 0, 0);
	return this->Error();
}

err_code  CWebBrowser::Redirect (_pc_sz pTarget, const bool bAsync) {
	pTarget; bAsync;
	this->m_error << __METHOD__ <<__s_ok;

	if (false == this->State())
		return this->m_error = this->State().Error();

	if (false == bAsync)
		return this->m_error <<__e_not_impl;

	this->Host()->m_async_data = _variant_t(pTarget);
	this->Host()->PostMessage(CBrowserWnd::eAsyncRedirect, 0, 0);

	return this->Error();
}

err_code  CWebBrowser::Refresh (void) {
	m_error <<__METHOD__<<__s_ok;

	if (false == this->State())
		return this->m_error = this->State().Error();

	// https://learn.microsoft.com/en-us/previous-versions//aa768258(v=vs.85) << does not use refresh operation levels;
	// https://learn.microsoft.com/en-us/previous-versions//aa768260(v=vs.85) << this is the refresh2 that uses levels (see below);
	// https://learn.microsoft.com/en-us/previous-versions//aa768363(v=vs.85) << this is an enumeration of levels of refresh operation;

	_variant_t v_level((long)REFRESH_COMPLETELY); v_level;

	this->m_error << this->Ctrl()->Refresh();
//	if (this->Error() == false)  {
		this->Host()->Refresh();
//	}
	return this->Error();
}

const
CScript&  CWebBrowser::Script (void) const { return this->m_script; }
CScript&  CWebBrowser::Script (void)       { return this->m_script; }
const
CState&   CWebBrowser::State (void) const { return this->m_state; }
CState&   CWebBrowser::State (void)       { return this->m_state; }

static ::ATL::CAxWindow inv_wnd;
const
CAxWindow& CWebBrowser::Window (void) const { return this->m_host == nullptr ? inv_wnd : *this->m_host; }
CAxWindow& CWebBrowser::Window (void)       { return this->m_host == nullptr ? inv_wnd : *this->m_host; }

#pragma endregion

TIEBrowser* ::Get_IE_ptr (void) { return p_browser; }