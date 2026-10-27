/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2026 at 12:04:51.014, UTC+4, Batumi, Thursday;
	This is Ebo Pack IE 11 IWebBrowser2 control events' sink interface implementation file;
*/
#include "web.ie.events.h"

using namespace ::ex_ui::web::IE::events;

namespace ex_ui { namespace web { namespace IE { namespace events { namespace func_defs {

	_ATL_FUNC_INFO BeforeNavigate2_Info = {
		CC_STDCALL, VT_EMPTY, 7,    // { calling convention, return type(void), number of params };
		{	                        // input param's types;
			VT_DISPATCH,
			VT_BYREF | VT_VARIANT,  // URL;
			VT_BYREF | VT_VARIANT,  // Flags;
			VT_BYREF | VT_VARIANT,  // TargetFrameName;
			VT_BYREF | VT_VARIANT,  // PostData;
			VT_BYREF | VT_VARIANT,  // Headers;
			VT_BYREF | VT_BOOL      // Cancel;
		}
	};

	_ATL_FUNC_INFO DocumentComplete_Info   = {
		CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF | VT_VARIANT} // {calling convention, return type, number of params, params' types: IDispatch, URL}
	};

	_ATL_FUNC_INFO NavigateComplete2_Info = {
		CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF | VT_VARIANT} // {calling convention, return type, number of params, params' types: IDispatch, URL}
	};

	_ATL_FUNC_INFO NavigateError_Info = {
		CC_STDCALL, VT_EMPTY, 5,
		{
			VT_DISPATCH,
			VT_BYREF | VT_VARIANT,  // URL;
			VT_BYREF | VT_VARIANT,  // Frame (Target Frame Name);
			VT_BYREF | VT_VARIANT,  // StatusCode (e.g. HTTP status codes like 404, or WinInet error codes);
			VT_BYREF | VT_BOOL      // Cancel;
		}
	};

	_ATL_FUNC_INFO NewWindow2_Info = {
		CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH | VT_BYREF, VT_BOOL | VT_BYREF } // {input params: IDispath, Cancel};
	};

	_ATL_FUNC_INFO NewWindow3_Info = {
		CC_STDCALL, VT_EMPTY, 5, 
		{ 
			VT_DISPATCH | VT_BYREF, // ppDisp;
			VT_BOOL | VT_BYREF,     // Cancel;
			VT_UI4 ,                // dwFlags (unsigned long / DWORD);
			VT_BSTR,                // bstrUrlContext;
			VT_BSTR                 // bstrUrl;
		}
	};

	_ATL_FUNC_INFO MouseClick_info = { CC_STDCALL, VT_EMPTY, 1, { VT_UNKNOWN } };
}}}}} using namespace func_defs;

#pragma region cls::CBase_Props{}

CBase_Props::CBase_Props (void) : m_flags{false}{}

bool   CBase_Props::Advised  (void) const { return this->m_flags[e_indices::e_advised]; }
bool   CBase_Props::Attached (void) const { return this->m_flags[e_indices::e_attached]; }
bool   CBase_Props::InActive (void) const { return this->m_flags[e_indices::e_inactive]; }
bool&  CBase_Props::InActive (void)       { return this->m_flags[e_indices::e_inactive]; }     
bool   CBase_Props::Streamed (void) const { return this->m_flags[e_indices::e_streamed]; }
bool&  CBase_Props::Streamed (void)       { return this->m_flags[e_indices::e_streamed]; }     

#pragma endregion
#pragma region cls::CBase_Sink{}

using CProps = CBase_Props;

CBase_Sink::CBase_Sink (void) : m_evt_handler_ptr(0) {
	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("This sink is not initialized yet");
}

err_code CBase_Sink::Attach (HWND _h_host_wnd) {
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _h_host_wnd || false == !!::IsWindow(_h_host_wnd))
		return this->m_error <<__e_hwnd = _T("__e_wnd: Host window handle being attached is invalid");

	this->m_host_wnd = _h_host_wnd;

	return this->Error();
}

TError&  CBase_Sink::Error (void) const { return this->m_error; }
const
CProps&  CBase_Sink::Props (void) const { return this->m_props; }
CProps&  CBase_Sink::Props (void)       { return this->m_props; }

CBase_Sink& CBase_Sink::operator << (HWND _h_host_wnd) { this->Attach(_h_host_wnd); return *this; }
CBase_Sink& CBase_Sink::operator << (IWbEvtHandler* _p_handler) { this->m_evt_handler_ptr = _p_handler; return *this; }

#pragma endregion
#pragma region cls::CBrowserSink{}

CBrowserSink:: CBrowserSink (void) : TBase() { TBase::m_error >>__CLASS__; }
CBrowserSink::~CBrowserSink (void) { this->Unadvise(); }

#pragma region event_sink_impl
// https://learn.microsoft.com/en-us/previous-versions/aa768326(v=vs.85) ;
// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768280(v=vs.85) ;
err_code CBrowserSink::BeforeNavigate2 (IDispatch* pDisp, var_ptr pUrl, var_ptr pFlags, var_ptr pTargetFrame, var_ptr pPostData, var_ptr pHeaders, var_bool* pCancel) {
	pDisp; pUrl; pFlags; pTargetFrame; pPostData; pHeaders; pCancel;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (TBase::m_evt_handler_ptr == nullptr) // callback pointer is not set, there is nothing to do;
		return TBase::Error();

	if (TBase::Props().InActive()) // the 'silent' mode is turned on;
		return TBase::Error();

	TBase::m_error << TBase::m_evt_handler_ptr->WbEvt_BeforeNavigate((_pc_sz) CString((*pUrl).bstrVal));

	if (pCancel && TBase::Error() != __s_ok) // perhaps, it requires a review of such condition, but it will be made later during an integration with test cases;
		*pCancel = var_true;

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/previous-versions/aa768329(v=vs.85) ;
err_code CBrowserSink::DocumentComplete (IDispatch* pDisp, var_ptr pUrl) {
	pDisp; pUrl;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (TBase::m_evt_handler_ptr == nullptr) // callback pointer is not set, there is nothing to do;
		return TBase::Error();

	CComPtr<IUnknown> pControl;
	TBase::m_error << this->m_host_wnd.QueryControl(&pControl);
	if (TBase::Error())
		return TBase::Error();

	bool bTopFrame = false; // this is a flag for indicating the document is loaded to top frame, otherwise a document can be loaded by sub-frame;
	CComPtr<IUnknown> pFrame;
	if (__succeeded(TBase::m_error << pDisp->QueryInterface( IID_IUnknown, (void**)&pFrame)))
		bTopFrame = (pControl == pFrame);

#if (0) // this is alternative way in order to define the top frame has loaded the document or not;
	CComQIPtr<IWebBrowser2> pWebBrowser;
	this->m_error << pControl.QueryInterface(&pWebBrowser);
	if (this->Error())
		return this->Error();
	 CComPtr<IDispatch> p_the_app;
	 this->m_error << pWebBrowser->get_Application(&p_the_app);
	 if (this->Error())
		return this->Error();
	 bTopFrame = p_the_app.IsEqualObject(pDisp);
	 if (bTopFrame) { // this code block is not required, because the web browser control was not updatable due to incorrect main message loop of app;
		 rect_t rect = {0};
		 if (TBrowserHost::GetClientRect(&rect)) {
			 TBrowserHost::SetWindowPos(0, &rect, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_FRAMECHANGED);
			 TBrowserHost::Invalidate(true);
			 TBrowserHost::UpdateWindow();
		 }
	 }
#endif
	if (bTopFrame)
		TBase::m_evt_handler_ptr->WbEvt_DocumentComplete((_pc_sz) CString((*pUrl).bstrVal), this->Props().Streamed());

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/previous-versions//bb268221(v=vs.85) ;
// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768286(v=vs.85) ;
err_code CBrowserSink::NavigateError (IDispatch* pDisp, var_ptr pUrl, var_ptr pTargetFrame, var_ptr pStatusCode, var_bool* pCancel) {
	pDisp; pUrl; pTargetFrame; pStatusCode; pCancel;
	TBase::m_error <<__METHOD__<<__s_ok;
	// to-do: TBase::m_error must contain navigation error details or callback interface needs to have additional callback function especially for this use case;
	return TBase::Error();
}

#pragma endregion

static _pc_sz p_host_wnd_not_attached = _T("__e_state: Host window is not attached");
static _pc_sz p_sink_is_advised = _T("__e_state: This sink is already advised");

err_code CBrowserSink::Advise (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (TBase::Props().Attached() == false)
		return TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_host_wnd_not_attached;

	if (TBase::Props().Advised() == true) // no auto-unadvising is implemented yet;
		return TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_sink_is_advised;

	CComPtr<IUnknown> pControl;
	TBase::m_error << this->m_host_wnd.QueryControl(&pControl);
	if (TBase::Error())
		return TBase::Error();

	TBase::m_error << pControl->QueryInterface(IID_IWebBrowser2, (void**)&this->m_pBrowser);
	if (TBase::Error())
		return TBase::Error();

	TBase::m_error << TBrowserEvtSnk::DispEventAdvise(this->m_pBrowser, &DIID_DWebBrowserEvents2);
	TBase::Advised() = TBase::Error() == false;

	return TBase::Error();
}

bool CBrowserSink::Is_valid (void) const { return this->m_pBrowser != nullptr; }

err_code CBrowserSink::Unadvise (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (TBase::Props().Advised() == false) // nothing to do;
		return TBase::Error();

	if (this->Is_valid() == false) // actually it is not possible, but in any way, it should be checked;
		return TBase::m_error <<__e_pointer = _T("__e_pointer: WebBrowser control is not inited");

	TBase::m_error << TBrowserEvtSnk::DispEventUnadvise(this->m_pBrowser, &DIID_DWebBrowserEvents2);
	TBase::Advised() = TBase::Error() == true; // the error has occurred while trying to unsubscribe from events;

	if (TBase::Props().Advised() == false)
		this->m_pBrowser = nullptr;

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CDoc_2_Sink{}

CDoc_2_Sink:: CDoc_2_Sink (void) { TBase::m_error >>__CLASS__; }
CDoc_2_Sink::~CDoc_2_Sink (void) { this->Unadvise(); }

err_code CDoc_2_Sink::Advise (const TWebBrwPtr& _p_browser) {
	_p_browser;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_browser)
		TBase::m_error <<__e_pointer = _T("__e_pointer: Input web browser control pointer is invalid");

	if (TBase::Props().Advised() == true) // no auto-unadvising is implemented yet;
		return TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_sink_is_advised;

	CComPtr<IDispatch> pDocDisp;
	TBase::m_error << _p_browser->get_Document(&pDocDisp);
	if (TBase::Error())
		return TBase::Error();

	TBase::m_error << pDocDisp->QueryInterface(IID_IHTMLDocument2, (void**)&this->m_pDoc2);
	if (TBase::Error())
		return TBase::Error();

	TBase::m_error << THtmlDocEvtSnk::DispEventAdvise(this->m_pDoc2, &DIID_HTMLDocumentEvents2);
	TBase::Advised() = TBase::Error() == false;

	return TBase::Error();
}

err_code CDoc_2_Sink::Unadvise (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (TBase::Props().Advised() == false) // nothing to do;
		return TBase::Error();

	if (this->Is_valid() == false)
		return TBase::m_error <<__e_pointer = _T("__e_pointer: HTML Document2 object is not inited");

	TBase::m_error << THtmlDocEvtSnk::DispEventUnadvise(this->m_pDoc2, &DIID_HTMLDocumentEvents2);
	TBase::Advised() = TBase::Error() == true; // the error has occurred while trying to unsubscribe from events;

	if (TBase::Props().Advised() == false)
		this->m_pDoc2 = nullptr;

	return TBase::Error();
}

bool CDoc_2_Sink::Is_valid (void) const { return this->m_pDoc2 != nullptr; }

err_code CDoc_2_Sink::OnClick (IUnknown* pEvtObj) {
	pEvtObj;
	TBase::m_error <<__METHOD__<<__s_ok;
	// IHTMLEventObj is expected as input argument;

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CSinks{}

using CBrwSink = CBrowserSink;
using CDocSink = CDoc_2_Sink;

CSinks:: CSinks (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CSinks::~CSinks (void) {}

TError&  CSinks::Error (void) const { return this->m_error; }

const
CBrwSink& CSinks::GetBrwSink (void) const { return this->m_brw_sink; }
CBrwSink& CSinks::GetBrwSink (void)       { return this->m_brw_sink; }
const
CDocSink& CSinks::GetDocSink (void) const { return this->m_doc_sink; }
CDocSink& CSinks::GetDocSink (void)       { return this->m_doc_sink; }

err_code  CSinks::Unadvise (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_error << this->GetDocSink().Unadvise();
	
	if (this->Error()) {
		return this->m_error = this->GetDocSink().Error();
	}

	this->m_error << this->GetBrwSink().Unadvise();
	if (this->Error())
		this->m_error = this->GetBrwSink().Error();

	return this->Error();
}

CSinks&   CSinks::operator << (HWND _h_host_wnd) { this->GetBrwSink() << _h_host_wnd; this->GetDocSink() << _h_host_wnd; return *this; }
CSinks&   CSinks::operator << (IWbEvtHandler* _p_handler) { this->GetBrwSink() << _p_handler; this->GetDocSink() << _p_handler; return *this; }

#pragma endregion