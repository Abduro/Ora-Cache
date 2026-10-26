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

#pragma region cls::CBase_Sink{}

CBase_Sink::CBase_Sink (void) : m_advised(false) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("This sink is not initialized yet"); }

err_code CBase_Sink::Attach (HWND _h_host_wnd) {
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _h_host_wnd || false == !!::IsWindow(_h_host_wnd))
		return this->m_error <<__e_hwnd = _T("__e_wnd: Host window handle being attached is invalid");

	this->m_host_wnd = _h_host_wnd;

	return this->Error();
}

TError& CBase_Sink::Error (void) const { return this->m_error; }
bool  CBase_Sink::Is_advised (void) const { return this->m_advised; }
bool  CBase_Sink::Is_attached (void) const { return this->m_host_wnd.IsWindow(); }

#pragma endregion
#pragma region cls::CBrowserSink{}

CBrowserSink:: CBrowserSink (void) : TBase() { TBase::m_error >>__CLASS__; }
CBrowserSink::~CBrowserSink (void) {}

#pragma region event_sink_impl
err_code CBrowserSink::BeforeNavigate2 (IDispatch* pDisp, var_ptr pUrl, var_ptr pFlags, var_ptr pTargetFrame, var_ptr pPostData, var_ptr pHeaders, var_bool* pCancel) {
	pDisp; pUrl; pFlags; pTargetFrame; pPostData; pHeaders; pCancel;
	TBase::m_error <<__METHOD__<<__s_ok;

	return TBase::Error();
}

err_code CBrowserSink::DocumentComplete (IDispatch* pDisp, var_ptr pUrl) {
	pDisp; pUrl;
	TBase::m_error <<__METHOD__<<__s_ok;
	return TBase::Error();
}

err_code CBrowserSink::NavigateError   (IDispatch* pDisp, var_ptr pUrl, var_ptr pTargetFrame, var_ptr pStatusCode, var_bool* pCancel) {
	pDisp; pUrl; pTargetFrame; pStatusCode; pCancel;
	TBase::m_error <<__METHOD__<<__s_ok;
	return TBase::Error();
}

#pragma endregion

static _pc_sz p_host_wnd_not_attached = _T("__e_state: Host window is not attached");
static _pc_sz p_sink_is_advised = _T("__e_state: This sink is already advised");

err_code CBrowserSink::Advise (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (TBase::Is_attached() == false)
		return TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_host_wnd_not_attached;

	if (TBase::Is_advised() == true) // no auto-unadvising is implemented yet;
		return TBase::m_error << (err_code)TErrCodes::eExecute::eState = p_sink_is_advised;

	TBase::m_error << this->m_host_wnd.QueryControl(IID_IWebBrowser2, (void**)&this->m_pBrowser);
	if (TBase::Error())
		return TBase::Error();

	TBase::m_error << TBrowserEvtSnk::DispEventAdvise(this->m_pBrowser, &DIID_DWebBrowserEvents2);
	TBase::m_advised = TBase::Error() == false;

	return TBase::Error();
}

bool CBrowserSink::Is_valid (void) const { return this->m_pBrowser != nullptr; }

err_code CBrowserSink::Unadvise (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (TBase::Is_advised() == false) // nothing to do;
		return TBase::Error();

	if (this->Is_valid() == false) // actually it is not possible, but in any way, it should be checked;
		return TBase::m_error <<__e_pointer = _T("__e_pointer: WebBrowser control is not inited");

	TBase::m_error << TBrowserEvtSnk::DispEventUnadvise(this->m_pBrowser, &DIID_DWebBrowserEvents2);
	TBase::m_advised = TBase::Error() == true; // the error has occurred while trying to unsunscribe from events;

	return TBase::Error();
}

#pragma endregion