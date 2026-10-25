/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser control host window class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:17:50p, UTC+7, Phuket, Rawai, Monday;
*/
#include "web.ie.host.wnd.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::core;

using CEvents = CBrowserHost::CEvents;

namespace ex_ui { namespace web { namespace IE { namespace core
{
namespace _impl {
	HHOOK&  GetKeyboardHook_Ref (void)
	{
		static HHOOK m_msg_filter = 0;
		return m_msg_filter;
	}

	HHOOK&  GetMouseHook_Ref (void)
	{
		static HHOOK m_msg_filter = 0;
		return m_msg_filter;
	}

	static LRESULT __stdcall KeyboardHandler_Func (INT nCode, WPARAM wParam, LPARAM lParam); // https://learn.microsoft.com/en-us/windows/win32/winmsg/lowlevelkeyboardproc ;
	static LRESULT __stdcall MouseEvtHandler_Func (INT nCode, WPARAM wParam, LPARAM lParam); // https://learn.microsoft.com/en-us/windows/win32/winmsg/mouseproc ;

	class CKbrdHandler_Cache { typedef ::std::map<HWND, CComPtr<IOleInPlaceActiveObject> >  TCache;
	public:
		 CKbrdHandler_Cache (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CKbrdHandler_Cache (const CKbrdHandler_Cache&) = delete;
		 CKbrdHandler_Cache (CKbrdHandler_Cache&&) = delete;
		~CKbrdHandler_Cache (void) {
			if (!m_cache.empty()) m_cache.clear();
		}

		TError&  Error (void) const { return this->m_error; }

		err_code Handle (PMSG pMsg) {
			pMsg;
			this->m_error <<__METHOD__<<__s_false; // not handled;

			if (nullptr == pMsg || m_cache.empty())
				return this->Error();

			for (TCache::iterator it_ = m_cache.begin(); it_ != m_cache.end(); ++it_)
			{
				const HWND hWnd = it_->first;
				if (!::IsChild(hWnd, pMsg->hwnd) && hWnd != pMsg->hwnd)
					continue;
				::ATL::CComPtr<IOleInPlaceActiveObject>& obj_ref = it_->second;
				if (!obj_ref)
					continue;
				this->m_error << obj_ref->TranslateAccelerator(pMsg);
				if (this->m_error !=__s_ok)
					continue;
				::memset((void*)pMsg, 0, sizeof(MSG));
				this->m_error <<__s_ok; // marks the input message is handled;
				break;
			}
			return this->Error();
		}
		err_code Register (const HWND hWnd, const ::ATL::CComPtr<IOleInPlaceActiveObject> act_obj_ref) {
			this->m_error <<__METHOD__<<__s_ok;
			try {
				m_cache[hWnd] = act_obj_ref;
			}
			catch (::std::bad_alloc&) { return this->m_error <<__e_no_memory; }

			if (0 < m_cache.size() && nullptr == GetKeyboardHook_Ref())
			{	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexW ;
				HHOOK& hook_ref = GetKeyboardHook_Ref();
				hook_ref = ::SetWindowsHookEx(
					WH_KEYBOARD_LL, KeyboardHandler_Func, ::ATL::_AtlBaseModule.GetModuleInstance(), ::GetCurrentThreadId()
				);
				if (nullptr == hook_ref)
					this->m_error.Last();
			}
			return this->Error();
		}
		err_code Unregister (const HWND hWnd) {
			this->m_error <<__METHOD__<<__s_ok;

			TCache::iterator it_ = m_cache.find(hWnd);
			if (m_cache.end() == it_)
				return this->Error();
			it_->second = nullptr; // it is required, otherwise, the access violation error may occur;
			m_cache.erase(it_);
			if (m_cache.empty() && nullptr != GetKeyboardHook_Ref())
			{	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-unhookwindowshookex ;
				if (false == !!::UnhookWindowsHookEx(GetKeyboardHook_Ref()))
					this->m_error.Last();
				GetKeyboardHook_Ref() = 0;
			}
			return this->Error();
		}
	private:
		CKbrdHandler_Cache& operator = (CKbrdHandler_Cache&&) = delete;
		CKbrdHandler_Cache& operator = (const CKbrdHandler_Cache&) = delete;

		TCache m_cache;
		CError m_error;
	};

	using ex_ui::web::IE::IWbEvtHandler;
	class CMouseHandler_Cache { typedef ::std::map<HWND, IWbEvtHandler*> TCache;
	public:
		 CMouseHandler_Cache (void){ this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
		 CMouseHandler_Cache (const CMouseHandler_Cache&) = delete;
		 CMouseHandler_Cache (CMouseHandler_Cache&&) = delete;
		~CMouseHandler_Cache (void){
			if (!m_cache.empty()) m_cache.clear();
		}

		TError&  Error (void) const { return this->m_error; }

		err_code Handle (PMOUSEHOOKSTRUCT pMouseData, const dword_t dwMessage) {
			pMouseData; dwMessage;
			this->m_error <<__METHOD__<<__s_false; // the input mouse data is not handled;

			if (!pMouseData || m_cache.empty())
				return this->Error();

			for (TCache::iterator it_ = m_cache.begin(); it_ != m_cache.end(); ++it_)
			{
				const HWND hWnd = it_->first;
				if (!::IsChild(hWnd, pMouseData->hwnd) && hWnd != pMouseData->hwnd)
					continue;
				IWbEvtHandler* const handler_ = it_->second;
				if (!handler_)
					break;
				MSG msg  = {0};
				msg.hwnd = pMouseData->hwnd;
				msg.message = dwMessage;
				msg.pt   = pMouseData->pt;
				this->m_error << handler_->WbEvt_OnMouseMessage(msg);
				if (this->m_error == __s_ok)
					break; // marks the input message is handled;
			}
			return this->Error();
		}
		err_code Register (const HWND hWnd, IWbEvtHandler* const pHandler) {
			hWnd; pHandler;
			this->m_error <<__METHOD__<<__s_ok;

			try {
				m_cache[hWnd] = pHandler;
			}
			catch(::std::bad_alloc&){ return this->m_error <<__e_no_memory; }

			HHOOK&  hook_ref = GetMouseHook_Ref();
			if (0 < m_cache.size() && nullptr == hook_ref)
			{	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa ;
				hook_ref = ::SetWindowsHookEx(
								WH_MOUSE, MouseEvtHandler_Func, ::ATL::_AtlBaseModule.GetModuleInstance(), ::GetCurrentThreadId()
							);
				if (nullptr == hook_ref)
					this->m_error.Last();
			}
			return  this->Error();
		}
		err_code Unregister (const HWND hWnd) {
			hWnd;
			this->m_error <<__METHOD__<<__s_ok;

			TCache::iterator it_ = m_cache.find(hWnd);
			if (m_cache.end() == it_)
				return this->Error();

			m_cache.erase(it_);
			HHOOK&  hook_ref = GetMouseHook_Ref();
			if (m_cache.empty() && nullptr != hook_ref)
			{
				if (false == !!::UnhookWindowsHookEx(hook_ref))
					this->m_error.Last();
				hook_ref = nullptr; // ignores possible unsubscription error;
			}
			return this->Error();
		}

	private:
		CMouseHandler_Cache& operator = (const CMouseHandler_Cache&) = delete;
		CMouseHandler_Cache& operator = (CMouseHandler_Cache&&) = delete;
		TCache m_cache;
		CError m_error;
	};

	CKbrdHandler_Cache& KbrdHandler_GetCacheObject (void)
	{
		static CKbrdHandler_Cache cache;
		return cache;
	}

	CMouseHandler_Cache& MouseHandler_GetCacheObject (void)
	{
		static CMouseHandler_Cache cache;
		return cache;
	}

	// https://learn.microsoft.com/en-us/windows/win32/winmsg/keyboardproc << this procedure does not allow to handle keyboard event, just only virtual code of the key;
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/lowlevelkeyboardproc ;
	static LRESULT __stdcall KeyboardHandler_Func (INT nCode, WPARAM wParam, LPARAM lParam) {
		nCode; wParam; lParam;
		const HHOOK hHook = GetKeyboardHook_Ref();
		if (HC_ACTION != nCode)
			return ::CallNextHookEx(hHook, nCode, wParam, lParam);
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-kbdllhookstruct ;
		KBDLLHOOKSTRUCT* p_struct = {0};
		p_struct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
		if (p_struct) {
			// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes << WPARAM holds one of these codes;
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-msg ;
			MSG msg = {0};
			msg.message = static_cast<UINT>(wParam);
			msg.wParam  = wParam;
			msg.lParam  = p_struct->flags;

			KbrdHandler_GetCacheObject().Handle(&msg);
		}
		return ::CallNextHookEx(hHook, nCode, wParam, lParam);
	}
	static LRESULT __stdcall MouseEvtHandler_Func (INT nCode, WPARAM wParam, LPARAM lParam)
	{
		const HHOOK hHook = GetMouseHook_Ref();
		if (HC_ACTION != nCode)
			return ::CallNextHookEx(hHook, nCode, wParam, lParam);

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-mousehookstruct ;
		PMOUSEHOOKSTRUCT pMsg =  reinterpret_cast<PMOUSEHOOKSTRUCT>(lParam);
		if ( pMsg && (WM_MOUSEMOVE != wParam)) // there is no interest of mouse movement over HTML document content;
		{
			MouseHandler_GetCacheObject().Handle(pMsg, (DWORD)wParam);
		}
		return ::CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	class CWebBrowser_Helper {
	public:
		 CWebBrowser_Helper (const HWND _h_browser_wnd) : m_browser(_h_browser_wnd) {}
		 CWebBrowser_Helper (const CWebBrowser_Helper&) = delete; CWebBrowser_Helper (CWebBrowser_Helper&&) = delete;
		~CWebBrowser_Helper (void) {}

		err_code FindServer (HWND& _h_srv_wnd) {
			// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumchildwindows ;
			const bool_t b_result = ::EnumChildWindows(m_browser, CWebBrowser_Helper::EnumChildren, (LPARAM)&_h_srv_wnd); b_result;
			return __s_ok;
		}
		// https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633493(v=vs.85) ;
		static bool_t __stdcall EnumChildren (HWND hwndChild, LPARAM lParam) {
			hwndChild; lParam;
			static _pc_sz lp_sz_cls[] = { _T("Shell Embedding"), _T("Shell DocObject View"), _T("Internet Explorer_Server")};

			if (lParam) {
				HWND* p_wnd = reinterpret_cast<HWND*>(lParam);
				if ( p_wnd )
					*p_wnd = hwndChild;
			}

			bool_t  b_result = false;
			wchar_t w_buffer[32] = {0};
			// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassnamew ;
			const INT n_result = ::GetClassNameW(hwndChild, w_buffer, _countof(w_buffer));
			if (0 != n_result) {
				b_result = true;
			}
			return b_result;
		}
	private:
		CWindow m_browser;
	};

	class CGuid_Wrap {
	public:
		 CGuid_Wrap (void) : m_p_guid(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; this->Set(); }
		 CGuid_Wrap (const CGuid_Wrap&) = delete; CGuid_Wrap (CGuid_Wrap&&) = delete;
		~CGuid_Wrap (void) {
			this->Clear();
		}

		err_code Clear (void) {
			this->m_error <<__METHOD__<<__s_ok;
			if (this->m_p_guid) {
				// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cotaskmemfree ;
				::CoTaskMemFree(this->m_p_guid); // returns no error;
				this->m_p_guid = 0;
			}
			return this->Error();
		}
		TError&  Error (void) const { return this->m_error; }
		bool  Is_valid (void) const { return this->Get() != 0; }

		wchar_t* Get (void) const { return this->m_p_guid; }
		err_code Set (void) {
			this->m_error <<__METHOD__<< ::StringFromCLSID(CLSID_WebBrowser, &this->m_p_guid);
			return this->Error();
		}

		CGuid_Wrap& operator = (const CGuid_Wrap&) = delete; CGuid_Wrap& operator = (CGuid_Wrap&&) = delete;

		wchar_t* const operator ()(void) const { return this->Get(); }
		operator wchar_t* const (void) const { return this->Get(); }

	private:
		wchar_t* m_p_guid;
		CError   m_error ;
	};
#if defined(__use_untrusted_clients)
#include <Objsafe.h>
	err_code RegisterSafeCtrl (CComPtr<IUnknown>& pCtrl) {
		if (!pCtrl)
			return __e_inv_arg;
		
		CComQIPtr<IObjectSafety> pSafe = pCtrl;
		if (!pSafe)
			return __e_not_impl;

		dword_t dwSupportedOptions = 0;
		dword_t dwEnabledOptions   = 0;
		err_code h_result = pSafe->GetInterfaceSafetyOptions(__uuidof(IDispatch), &dwSupportedOptions, &dwEnabledOptions);
		if (__failed(h_result))
			return  h_result;

		bool bSetSafeOptions = false;
		if ((INTERFACESAFE_FOR_UNTRUSTED_CALLER & dwSupportedOptions) && !(INTERFACESAFE_FOR_UNTRUSTED_CALLER & dwEnabledOptions))
		{
			dwEnabledOptions |= INTERFACESAFE_FOR_UNTRUSTED_CALLER;
			bSetSafeOptions   = true;
		}
		if ((INTERFACESAFE_FOR_UNTRUSTED_DATA & dwSupportedOptions) && !(INTERFACESAFE_FOR_UNTRUSTED_DATA & dwEnabledOptions))
		{
			dwEnabledOptions |= INTERFACESAFE_FOR_UNTRUSTED_DATA;
			bSetSafeOptions   = true;
		}
		if(bSetSafeOptions)
		{
			h_result = pSafe->SetInterfaceSafetyOptions(__uuidof(IDispatch), dwEnabledOptions, dwEnabledOptions);
		}
		return  h_result;
	}
#endif

	err_code GetBrowserObject (CAxWindow& _host, CComPtr<IWebBrowser2>& _browser_obj)
	{
		CComPtr<IUnknown> pControl;

		err_code h_result = _host.QueryControl(&pControl);
		if (__succeeded(h_result)) {
			h_result = pControl->QueryInterface(IID_IWebBrowser2, (void**)&_browser_obj);
		}
		return h_result;
	}
}
}}}} using namespace _impl;

#pragma region cls::CBrowserHost{}

CBrowserHost::CBrowserHost (IWbEvtHandler& evt_ref) :  m_evt_handler(evt_ref), m_bInited(false), m_bDoNotNotify(false), m_bStreamObject(false), m_events(*this) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
}

err_code CBrowserHost::CreateObject(const HWND hParent, const rect_t& rcArea, TSvcProvider& pProvider, const bool bVisible) {
	hParent; rcArea; pProvider; bVisible;
	this->m_error <<__METHOD__<<__s_ok;

	if (!::IsWindow(hParent))
		return this->m_error <<__e_hwnd;

	if (TBrowserHost::IsWindow())
		return this->m_error << (err_code)TErrCodes::eObject::eExists = TString().Format(_T("The object of class '%s' does exist"), (_pc_sz)__CLASS__);

	rect_t rc_ = rcArea;
	CGuid_Wrap brw_guid;
	if (brw_guid.Is_valid() == false)
		return this->m_error = brw_guid.Error();

	const dword_t dStyle = (bVisible ? WS_VISIBLE : 0)|WS_CHILD;
	const HWND hBrowser = TBrowserHost::Create(hParent, rc_, brw_guid, dStyle);
	if (nullptr == hBrowser) {
		this->m_error.Last(); return this->Error();
	}

	this->m_error << TBrowserHost::CreateControl(brw_guid);
	if (this->m_error)
		return this->m_error;

	CComPtr<IUnknown> pControl;
	this->m_error << TBrowserHost::QueryControl(&pControl);
	if (this->m_error)
		return this->m_error;

#if defined(__use_untrusted_clients)
	this->m_error << RegisterSafeCtrl(pControl);
#endif
	if (pProvider)
	{
		CComPtr<IUnknown> pHost;
		this->m_error << TBrowserHost::QueryHost(&pHost);
		if (pHost)
		{
			CComQIPtr<IObjectWithSite> pObject;
			this->m_error << pHost.QueryInterface(&pObject);
			if (pObject)
				pObject->SetSite(pProvider);
		}
	}
	
	CComQIPtr<IWebBrowser2> pWebBrowser;
	this->m_error << pControl.QueryInterface(&pWebBrowser);
	if (pWebBrowser)
		pWebBrowser->QueryInterface(IID_IOleInPlaceActiveObject, (void**)&this->m_act_object);
#if (1)
	this->m_error << this->m_events.Advise();
#endif
	if (m_act_object)
	KbrdHandler_GetCacheObject().Register(TBrowserHost::m_hWnd, m_act_object);
	MouseHandler_GetCacheObject().Register(TBrowserHost::m_hWnd, &m_evt_handler);

	if (this->Error())
		return this->Error();

	CComPtr<IOleInPlaceObject> spInPlace;
	this->m_error << TBrowserHost::QueryControl(IID_PPV_ARGS(&spInPlace));
	if (this->Error() == false) {
		this->m_error << spInPlace->SetObjectRects(&rc_, &rc_);
	}

	CComQIPtr<IAxWinAmbientDispatch> spAmb;
	this->m_error << TBrowserHost::QueryHost(&spAmb);

	if (this->m_error == __s_ok)
	{
		spAmb->put_AllowContextMenu(var_false);
		spAmb->put_DocHostFlags( DOCHOSTUIFLAG_DIALOG
		                       | DOCHOSTUIFLAG_NO3DBORDER 
		                       | DOCHOSTUIFLAG_THEME
		                       | DOCHOSTUIFLAG_DISABLE_HELP_MENU
		                       | DOCHOSTUIFLAG_SCROLL_NO
		                       | DOCHOSTUIFLAG_DPI_AWARE);
	}
	return this->Error();
}

TError& CBrowserHost::Error (void) const { return this->m_error; }
#if (0)
CEvents& CBrowserHost::Events (void) { return this->m_events; }
#endif
err_code CBrowserHost::Refresh (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == !!TBrowserHost::IsWindow())
		return this->m_error <<__e_not_inited;

	rect_t rect = {0};
	TBrowserHost::GetClientRect(&rect);
	rect.right += 1; TBrowserHost::MoveWindow(&rect);
	rect.right -= 1; TBrowserHost::MoveWindow(&rect);

	return this->Error();
}

#pragma endregion
#pragma region event handlers

LRESULT CBrowserHost::OnClose (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	uMsg; wParam; lParam; bHandled;
	this->m_events.Unadvise();
#if (0)
	CComPtr<IUnknown> spUnk;
	err_code n_result = TBrowserHost::QueryControl(&spUnk);
	if (__succeeded(n_result)) {
		n_result = THtmlSink::DispEventUnadvise(spUnk);
	}
#endif
	KbrdHandler_GetCacheObject().Unregister(TBrowserHost::m_hWnd);
	MouseHandler_GetCacheObject().Unregister(TBrowserHost::m_hWnd); this->m_act_object = nullptr;
	return 0;
}

LRESULT CBrowserHost::OnCreate (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	uMsg; wParam; lParam; bHandled;
#if (0)
	static _pc_sz lp_sz_cls[] = { _T("Shell Embedding"), _T("Shell DocObject View"), _T("Internet Explorer_Server")};
	const HWND h_emb = ::FindWindowExW(*this, 0, lp_sz_cls[0], 0);
	if (nullptr != h_emb) {
		const HWND h_shell = ::FindWindowExW(h_emb, 0, lp_sz_cls[1], 0);
		if (nullptr != h_shell) {
		}
	}
#endif
	return 0;
}

LRESULT CBrowserHost::OnErase (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	uMsg; wParam; lParam; bHandled;
	return 1;
}

LRESULT CBrowserHost::OnRedirect (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	uMsg; wParam; lParam; bHandled;
	if (VT_BSTR != m_async_data.vt || nullptr == m_async_data.bstrVal)
		return 0;

	CComPtr<IUnknown> spUnk;
	err_code n_result = TBrowserHost::QueryControl(&spUnk);
	if (__succeeded(n_result))
	{
		CComQIPtr<IWebBrowser2> spWeb;
		n_result = spUnk.QueryInterface(&spWeb);

		if (__succeeded(n_result) && spWeb)
		{
		//	this->Events().Advise();
			m_bDoNotNotify = true;
			n_result = spWeb->Navigate2(&m_async_data, 0, 0, 0, 0);
			m_bDoNotNotify = false;
		}
	}
	return 0;
}

LRESULT CBrowserHost::OnSize (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled) {
	uMsg; wParam; lParam; bHandled;
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-size ;
	const SIZE size = { LOWORD(lParam), HIWORD(lParam) };
	
	CComPtr<IOleInPlaceObject> spInPlace;

	err_code n_result = TBrowserHost::QueryControl(IID_PPV_ARGS(&spInPlace));
	if (__succeeded(n_result) && nullptr != spInPlace) {

		rect_t rect = {0, 0, size.cx, size.cy};
		n_result = spInPlace->SetObjectRects(&rect, &rect);
	}

	return 0;
}

#pragma endregion
#pragma region sink callbacks

// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768280(v=vs.85) ;
STDMETHODIMP CBrowserHost::BeforeNavigate2 (LPDISPATCH, LPVARIANT pUrl, LPVARIANT, LPVARIANT, LPVARIANT, LPVARIANT, VARIANT_BOOL* pCancel)
{
	pUrl; pCancel;
	this->m_error <<__METHOD__<<__s_ok;

	if (m_bInited && nullptr != pUrl && VT_BSTR == (*pUrl).vt)
	{
		CString csUrl((*pUrl).bstrVal);
		if (!m_bDoNotNotify)
		{
			this->m_error << m_evt_handler.WbEvt_BeforeNavigate(csUrl.GetString());
			if (pCancel) {
				*pCancel = (this->Error() ? var_true : var_false);
			}
		}
		else
		{
			if (pCancel)
				*pCancel = var_false;
		}
	}
	return this->Error();
}

// https://learn.microsoft.com/en-us/previous-versions/aa768329(v=vs.85) ;
STDMETHODIMP CBrowserHost::DocumentComplete( LPDISPATCH pDisp, LPVARIANT pUrl) {
	pDisp; pUrl;
	this->m_error <<__METHOD__<<__s_ok;

	CString csUrl((*pUrl).bstrVal);
	bool bTopFrame = false;

	CComPtr<IUnknown> pControl;
	this->m_error << TBrowserHost::QueryControl(&pControl);
	if (this->Error())
		return this->Error();

#if (1)
	CComPtr<IUnknown> pFrame;
	if (__succeeded(this->m_error << pDisp->QueryInterface( IID_IUnknown, (void**)&pFrame)))
		bTopFrame = (pControl == pFrame);
#else
	CComQIPtr<IWebBrowser2> pWebBrowser;
	this->m_error << pControl.QueryInterface(&pWebBrowser);
	if (this->Error())
		return this->Error();
	 CComPtr<IDispatch> p_the_app;
	 this->m_error << pWebBrowser->get_Application(&p_the_app);
	 if (this->Error())
		return this->Error();
	 bTopFrame = p_the_app.IsEqualObject(pDisp);
	 if (bTopFrame) {
		 rect_t rect = {0};
		 if (TBrowserHost::GetClientRect(&rect)) {
			 TBrowserHost::SetWindowPos(0, &rect, SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_FRAMECHANGED);
			 TBrowserHost::Invalidate(true);
			 TBrowserHost::UpdateWindow();
		 }
	 }
#endif
	if (bTopFrame)
		m_evt_handler.WbEvt_DocumentComplete(csUrl.GetString(), m_bStreamObject);

	return this->Error();
}

// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa768286(v=vs.85) ;
STDMETHODIMP CBrowserHost::NavigateError (LPDISPATCH, LPVARIANT, LPVARIANT, LPVARIANT, VARIANT_BOOL* ) {
	return __s_ok;
}

#pragma endregion
#pragma region properties

err_code CBrowserHost::SetBackColor (const COLORREF _clr) {
	_clr;
	this->m_error <<__METHOD__<<__s_ok;

	CWebBrowser_Helper helper(*this);
	HWND hwnd_server = nullptr;

	this->m_error << helper.FindServer(hwnd_server);
	if (nullptr != hwnd_server && ::IsWindow(hwnd_server)) {
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setclasslongptrw ;
		HBRUSH brush = ::CreateSolidBrush(_clr);
		if (0 == ::SetClassLongPtr(hwnd_server, GCLP_HBRBACKGROUND, (LONG_PTR)brush)) // brush being set must be *destroyed* on window closing;
			this->m_error.Last();
		else {
			::InvalidateRect(hwnd_server, 0, true);
			::UpdateWindow(hwnd_server);
		}
	}
	return this->Error();
}
#if	0/*(_WIN32_IE >= _WIN32_IE_IE60SP2)*/

// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/ms537168(v=vs.85) ;
// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/ms537169(v=vs.85) ;
err_code CBrowserHost::EnableFeature (const dword_t dwFeature, const bool bEnabled, const dword_t dwScope) {
	this->m_error <<__METHOD__<<__s_ok;

	CComPtr<IWebBrowser2> browser;
	this->m_error << GetBrowserObject(*this, browser);
	if (this->m_error == false) {
		this->m_error << ::CoInternetSetFeatureEnabled((INTERNETFEATURELIST) dwFeature, dwScope, bEnabled);
	}
	return this->Error();
}

// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/ms537164(v=vs.85) ;
err_code CBrowserHost::IsFeatureEnabled (const dword_t dwFeature, const dword_t dwScope) {
	this->m_error <<__METHOD__<<__s_ok;

	CComPtr<IWebBrowser2> browser;
	this->m_error << GetBrowserObject(*this, browser);
	if (this->m_error == false) {
		this->m_error << ::CoInternetIsFeatureEnabled((INTERNETFEATURELIST) dwFeature, dwScope); //__s_ok: enabled, __s_false: disabled, otherwise, the error code;
	}
	return this->Error();
}

#endif
#pragma endregion
#pragma region cls::CEvemts{}

CEvents:: CEvents (CBrowserHost& _host) : m_host(_host) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CEvents::~CEvents (void) {}

TError& CEvents::Error (void) const { return this->m_error; }

err_code CEvents::Advise (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CComPtr<IUnknown> pControl;
	this->m_error << this->m_host.QueryControl(&pControl);
	if (this->Error())
		return this->Error();

	CComQIPtr<IWebBrowser2> pWebBrowser;
	this->m_error << pControl.QueryInterface(&pWebBrowser);
	if (this->Error())
		return this->Error();

	this->m_error << this->m_host.DispEventAdvise(pWebBrowser, &DIID_DWebBrowserEvents2);

	return this->Error();
}

err_code CEvents::Unadvise (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CComPtr<IUnknown> pControl;
	this->m_error << this->m_host.QueryControl(&pControl);
	if (this->Error())
		return this->Error();

	CComQIPtr<IWebBrowser2> pWebBrowser;
	this->m_error << pControl.QueryInterface(&pWebBrowser);
	if (this->Error())
		return this->Error();

	this->m_error << this->m_host.DispEventUnadvise(pWebBrowser);

	return this->Error();
}

#pragma endregion