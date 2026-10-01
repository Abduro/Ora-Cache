/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser control host window class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:17:50p, UTC+7, Phuket, Rawai, Monday;
*/
#include "shared.web.brw.wrap.h"

using namespace ex_ui::web;
using namespace ex_ui::web::core;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace web { namespace core
{
	_ATL_FUNC_INFO CWebBrowserWrap::BeforeNavigate2_Info = {
			CC_STDCALL, VT_EMPTY, 7, { VT_DISPATCH, VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_BOOL}
	};

	_ATL_FUNC_INFO CWebBrowserWrap::NavigateError_Info   = {
			CC_STDCALL, VT_EMPTY, 5, { VT_DISPATCH, VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_VARIANT ,
								VT_BYREF | VT_BOOL}
	};

	_ATL_FUNC_INFO CWebBrowserWrap::DocumentComplete_Info   = {
			CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF | VT_VARIANT}
	};
}}}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace web { namespace core
{
namespace details {

	HHOOK&  UIX_Frame_GetKeyboardHook_Ref(void)
	{
		static HHOOK m_msg_filter = NULL;
		return m_msg_filter;
	}

	HHOOK&  UIX_Frame_GetMouseHook_Ref(void)
	{
		static HHOOK m_msg_filter = NULL;
		return m_msg_filter;
	}

	static LRESULT CALLBACK UIX_Frame_KeyboardHandler_Func(INT nCode, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK UIX_Frame_MouseEvtHandler_Func(INT nCode, WPARAM wParam, LPARAM lParam);

	class UIX_Frame_KeyboardHandler_Cache
	{
		typedef ::std::map<HWND, ::ATL::CComPtr<IOleInPlaceActiveObject> >  TCache;
	private:
		TCache     m_cache;
	public:
		 UIX_Frame_KeyboardHandler_Cache(void){}
		~UIX_Frame_KeyboardHandler_Cache(void)
		{
			if (!m_cache.empty()) m_cache.clear();
		}
	public:
		HRESULT    Handle(PMSG pMsg)
		{
			if (!pMsg || m_cache.empty())
				return S_FALSE;
			for (TCache::iterator it_ = m_cache.begin(); it_ != m_cache.end(); ++it_)
			{
				const HWND hWnd = it_->first;
				if (!::IsChild(hWnd, pMsg->hwnd) && hWnd != pMsg->hwnd)
					continue;
				::ATL::CComPtr<IOleInPlaceActiveObject>& obj_ref = it_->second;
				if (!obj_ref)
					continue;
				const HRESULT hr_ = obj_ref->TranslateAccelerator(pMsg);
				if (S_OK != hr_)
					continue;
				::memset((void*)pMsg, 0, sizeof(MSG));
				return S_OK;
			}
			return S_FALSE;
		}
		HRESULT    Register(const HWND hWnd, const ::ATL::CComPtr<IOleInPlaceActiveObject>& act_obj_ref)
		{
			try
			{
				m_cache[hWnd] = act_obj_ref;
			}
			catch(::std::bad_alloc&){ return E_OUTOFMEMORY; }
			HRESULT hr_ = S_OK;
			if (0 < m_cache.size() && NULL == UIX_Frame_GetKeyboardHook_Ref())
			{
				HHOOK& hook_ref = UIX_Frame_GetKeyboardHook_Ref();
				hook_ref = ::SetWindowsHookEx(
					WH_GETMESSAGE, UIX_Frame_KeyboardHandler_Func, ::ATL::_AtlBaseModule.GetModuleInstance(), ::GetCurrentThreadId()
				);
				if (NULL == hook_ref)
					hr_ = HRESULT_FROM_WIN32(::GetLastError());
			}
			return  hr_;
		}
		HRESULT    Unregister(const HWND hWnd)
		{
			TCache::iterator it_ = m_cache.find(hWnd);
			if (m_cache.end() == it_)
				return S_OK;
			m_cache.erase(it_);
			if (m_cache.empty() && NULL != UIX_Frame_GetKeyboardHook_Ref())
			{
				::UnhookWindowsHookEx(UIX_Frame_GetKeyboardHook_Ref());
				UIX_Frame_GetKeyboardHook_Ref() = NULL;
			}
			return S_OK;
		}
	private:
		UIX_Frame_KeyboardHandler_Cache(const UIX_Frame_KeyboardHandler_Cache&);
		UIX_Frame_KeyboardHandler_Cache& operator= (const UIX_Frame_KeyboardHandler_Cache&);
	};

	using ex_ui::web::IWebBrowserEventHandler;
	class UIX_Frame_MouseEvtHandler_Cache
	{
		typedef ::std::map<HWND, IWebBrowserEventHandler*> TCache;
	private:
		TCache     m_cache;
	public:
		 UIX_Frame_MouseEvtHandler_Cache(void){}
		~UIX_Frame_MouseEvtHandler_Cache(void){if (!m_cache.empty())m_cache.clear();}
	public:
		HRESULT    Handle(PMOUSEHOOKSTRUCT pMouseData, const DWORD dwMessage)
		{
			if (!pMouseData || m_cache.empty())
				return S_FALSE;
			for (TCache::iterator it_ = m_cache.begin(); it_ != m_cache.end(); ++it_)
			{
				const HWND hWnd = it_->first;
				if (!::IsChild(hWnd, pMouseData->hwnd) && hWnd != pMouseData->hwnd)
					continue;
				IWebBrowserEventHandler* const handler_ = it_->second;
				if (!handler_)
					break;
				MSG msg  = {0};
				msg.hwnd = pMouseData->hwnd;
				msg.message = dwMessage;
				msg.pt   = pMouseData->pt;
				const HRESULT hr_ = handler_->BrowserEvent_OnMouseMessage(msg);
				if (S_OK == hr_)
					break;
			}
			return S_FALSE;
		}
		HRESULT    Register(const HWND hWnd, IWebBrowserEventHandler* const pHandler)
		{
			try
			{
				m_cache[hWnd] = pHandler;
			}
			catch(::std::bad_alloc&){ return E_OUTOFMEMORY; }
			HRESULT hr_ = S_OK;
			HHOOK&  hook_ref = UIX_Frame_GetMouseHook_Ref();
			if (0 < m_cache.size() && NULL == hook_ref)
			{
				hook_ref = ::SetWindowsHookEx(
								WH_MOUSE, UIX_Frame_MouseEvtHandler_Func, ::ATL::_AtlBaseModule.GetModuleInstance(), ::GetCurrentThreadId()
							);
				if (NULL == hook_ref)
					hr_ = HRESULT_FROM_WIN32(::GetLastError());
			}
			return  hr_;
		}
		HRESULT    Unregister(const HWND hWnd)
		{
			TCache::iterator it_ = m_cache.find(hWnd);
			if (m_cache.end() == it_)
				return S_OK;
			m_cache.erase(it_);
			HHOOK&  hook_ref = UIX_Frame_GetMouseHook_Ref();
			if (m_cache.empty() && NULL != hook_ref)
			{
				::UnhookWindowsHookEx(hook_ref);
				hook_ref = NULL;
			}
			return S_OK;
		}
	};

	UIX_Frame_KeyboardHandler_Cache& UIX_Frame_KeyboardHandler_GetCacheObject(void)
	{
		static UIX_Frame_KeyboardHandler_Cache cache;
		return cache;
	}

	UIX_Frame_MouseEvtHandler_Cache& UIX_Frame_MouseEvtHandler_GetCacheObject(void)
	{
		static UIX_Frame_MouseEvtHandler_Cache cache;
		return cache;
	}

	static LRESULT CALLBACK UIX_Frame_KeyboardHandler_Func(INT nCode, WPARAM wParam, LPARAM lParam)
	{
		const HHOOK hHook = UIX_Frame_GetKeyboardHook_Ref();
		if (HC_ACTION != nCode)
			return ::CallNextHookEx(hHook, nCode, wParam, lParam);
		MSG* pMsg = (MSG*)lParam;
		if ( pMsg && WM_KEYDOWN == pMsg->message
#if !defined(_DEBUG)
			&& VK_F5 != pMsg->wParam
#endif
		)
		{
			UIX_Frame_KeyboardHandler_GetCacheObject().Handle(pMsg);
		}
		return ::CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	static LRESULT CALLBACK UIX_Frame_MouseEvtHandler_Func(INT nCode, WPARAM wParam, LPARAM lParam)
	{
		const HHOOK hHook = UIX_Frame_GetMouseHook_Ref();
		if (HC_ACTION != nCode)
			return ::CallNextHookEx(hHook, nCode, wParam, lParam);
		PMOUSEHOOKSTRUCT pMsg =  (PMOUSEHOOKSTRUCT)lParam;
		if ( pMsg && (WM_LBUTTONDOWN == wParam || WM_LBUTTONUP == wParam))
		{
			UIX_Frame_MouseEvtHandler_GetCacheObject().Handle(pMsg, (DWORD)wParam);
		}
		return ::CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	class CWebBrowser_Helper {
	private:
		CWindow   m_browser;

	public:
		 CWebBrowser_Helper (const HWND _h_browser_wnd) : m_browser(_h_browser_wnd) {}
		~CWebBrowser_Helper (void) {}

	public:
		HRESULT FindServer  (HWND& _h_srv_wnd) { HRESULT hr_ = S_OK;
			// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumchildwindows
			const BOOL b_result = ::EnumChildWindows(m_browser, CWebBrowser_Helper::EnumChildren, (LPARAM)&_h_srv_wnd); b_result;

			return hr_;
		}

	public:
		// https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms633493(v=vs.85)
		static BOOL CALLBACK EnumChildren(HWND hwndChild, LPARAM lParam) {
			hwndChild; lParam;
			static LPCWSTR lp_sz_cls[] = { _T("Shell Embedding"), _T("Shell DocObject View"), _T("Internet Explorer_Server")};

			if (lParam) {
				HWND* p_wnd = reinterpret_cast<HWND*>(lParam);
				if ( p_wnd )
					*p_wnd = hwndChild;
			}

			BOOL b_result = FALSE;
			WCHAR w_buffer[32] = {0};
			// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassnamew
			const INT n_result = ::GetClassNameW(hwndChild, w_buffer, _countof(w_buffer));
			if (0 != n_result) {
				b_result = TRUE;
			}

			return b_result;
		}
	};
}}}}
using namespace ex_ui::web::core::details;
/////////////////////////////////////////////////////////////////////////////

CWebBrowserWrap:: CWebBrowserWrap(IWebBrowserEventHandler& evt_ref) : 
	m_evt_handler(evt_ref), m_bInited(false), m_bDoNotNotify(false), m_bStreamObject(false)
{
}

CWebBrowserWrap::~CWebBrowserWrap(void)
{
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CWebBrowserWrap::OnClose   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	uMsg; wParam; lParam; bHandled;
	::ATL::CComPtr<IUnknown> spUnk;
	HRESULT hr_ = TWindow::QueryControl(&spUnk);
	if (S_OK == hr_)
	{
		hr_ = THtmlSink::DispEventUnadvise(spUnk);
	}
	details::UIX_Frame_KeyboardHandler_GetCacheObject().Unregister(TWindow::m_hWnd); ATLASSERT(S_OK == hr_);
	details::UIX_Frame_MouseEvtHandler_GetCacheObject().Unregister(TWindow::m_hWnd); ATLASSERT(S_OK == hr_);
	return 0;
}

LRESULT CWebBrowserWrap::OnCreate  (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	uMsg; wParam; lParam; bHandled;
#if (0)
	static LPCWSTR lp_sz_cls[] = { _T("Shell Embedding"), _T("Shell DocObject View"), _T("Internet Explorer_Server")};
	const HWND h_emb = ::FindWindowExW(*this, NULL, lp_sz_cls[0], NULL);
	if (NULL != h_emb) {
		const HWND h_shell = ::FindWindowExW(h_emb, NULL, lp_sz_cls[1], NULL);
		if (NULL != h_shell) {
		}
	}
#endif
	return 0;
}

LRESULT CWebBrowserWrap::OnErase   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	uMsg; wParam; lParam; bHandled;
	return 1;
}

LRESULT CWebBrowserWrap::OnRedirect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	uMsg; wParam; lParam; bHandled;
	if (VT_BSTR == m_async_data.vt && NULL != m_async_data.bstrVal)
	{
		::ATL::CComPtr<IUnknown> spUnk;
		HRESULT hr_ = TWindow::QueryControl(&spUnk);
		if (S_OK == hr_)
		{
			::ATL::CComQIPtr<IWebBrowser2> spWeb;
			hr_ = spUnk.QueryInterface(&spWeb);
			if (SUCCEEDED(hr_) && spWeb)
			{
				m_bDoNotNotify = true;
				hr_ = spWeb->Navigate2(&m_async_data, 0, 0, 0, 0);
				m_bDoNotNotify = false;
			}
		}
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CWebBrowserWrap::BeforeNavigate2(
	LPDISPATCH    pDisp ,
	LPVARIANT     pUrl  ,
	LPVARIANT     pFlags,
	LPVARIANT     pTargetFrameName,
	LPVARIANT     pPostData,
	LPVARIANT     pHeaders ,
	VARIANT_BOOL* pCancel
)
{
	pDisp; pUrl; pFlags; pTargetFrameName; pPostData; pHeaders; pCancel;
	if (m_bInited && NULL != pUrl && VT_BSTR == (*pUrl).vt)
	{
		::ATL::CStringW csUrl((*pUrl).bstrVal);
		if (!m_bDoNotNotify)
		{
			HRESULT hr_ = m_evt_handler.BrowserEvent_BeforeNavigate(csUrl.GetString());
			if (NULL != pCancel)
			{
				*pCancel = (S_OK != hr_ ? VARIANT_TRUE : VARIANT_FALSE);
			}
		}
		else
		{
			if (NULL != pCancel)
				*pCancel = VARIANT_FALSE;
		}
	}
	return S_OK;
}

STDMETHODIMP CWebBrowserWrap::DocumentComplete( LPDISPATCH pDisp, LPVARIANT pUrl)
{
	pDisp; pUrl;
	::ATL::CStringW csUrl((*pUrl).bstrVal);
	bool bTopFrame = false;
	::ATL::CComPtr<IUnknown> pControl;
	if (S_OK == TWindow::QueryControl(&pControl))
	{
		::ATL::CComPtr<IUnknown> pFrame;
		if (SUCCEEDED(pDisp->QueryInterface( IID_IUnknown,  (void**)&pFrame)))
			bTopFrame = (pControl == pFrame);
	}
	if (bTopFrame)
		m_evt_handler.BrowserEvent_DocumentComplete(csUrl.GetString(), m_bStreamObject);
	return S_OK;
}

STDMETHODIMP CWebBrowserWrap::NavigateError  (
	LPDISPATCH    pDisp,
	LPVARIANT     pUrl ,
	LPVARIANT     pTargetFrameName,
	LPVARIANT     pStatusCode,
	VARIANT_BOOL* pCancel
)
{
	pDisp; pUrl; pTargetFrameName; pStatusCode; pCancel;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace hidden
{
namespace details {
	HRESULT UIX_Frame_GetBrowserObject(::ATL::CAxWindow& _host, ::ATL::CComPtr<IWebBrowser2>& _browser_obj)
	{
		::ATL::CComPtr<IUnknown> pControl;

		HRESULT hr_ = _host.QueryControl(&pControl);
		if (S_OK == hr_)
		{
			hr_ = pControl->QueryInterface(IID_IWebBrowser2, (void**)&_browser_obj);
		}
		return hr_;
	}
#if defined(_6D037463_C465_4c0a_BBBA_85F18AD433E0_)
#include <Objsafe.h>
	HRESULT UIX_Frame_RegisterSafeCtrl(::ATL::CComPtr<IUnknown>& pCtrl)
	{
		if (!pCtrl)
			return E_INVALIDARG;
		::ATL::CComQIPtr<IObjectSafety> pSafe = pCtrl;
		if (!pSafe)
			return E_NOINTERFACE;
		DWORD dwSupportedOptions = 0;
		DWORD dwEnabledOptions   = 0;
		HRESULT hr_ = pSafe->GetInterfaceSafetyOptions(__uuidof(IDispatch), &dwSupportedOptions, &dwEnabledOptions);
		if (S_OK != hr_)
			return  hr_;
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
			hr_ = pSafe->SetInterfaceSafetyOptions(__uuidof(IDispatch), dwEnabledOptions, dwEnabledOptions);
		}
		return  hr_;
	}
#endif
}}}

/////////////////////////////////////////////////////////////////////////////

HRESULT  CWebBrowserWrap::CreateObject(const HWND hParent, const RECT& rcArea, ::ATL::CComPtr<IServiceProvider>& pProvider, const bool bVisible)
{
	if (!::IsWindow(hParent))
		return OLE_E_INVALIDHWND;
	if (TWindow::IsWindow())
		return HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS);
	RECT rc_ = rcArea;
	LPOLESTR pCLSID  = NULL;
	HRESULT hr_ = ::StringFromCLSID(CLSID_WebBrowser, &pCLSID);
	if (S_OK != hr_)
		return  hr_;
	const DWORD dStyle = (bVisible ? WS_VISIBLE : NULL)|WS_CHILD/*|WS_CLIPSIBLINGS|WS_CLIPCHILDREN*/;
	const HWND hBrowser = TWindow::Create(hParent, rc_, pCLSID, dStyle);
	if (NULL!= hBrowser)
	{
		hr_ = TWindow::CreateControl(pCLSID);
		if (S_OK == hr_)
		{
			::ATL::CComPtr<IUnknown> pControl;
			hr_ = TWindow::QueryControl(&pControl);
			if (S_OK == hr_)
			{
#if defined(_6D037463_C465_4c0a_BBBA_85F18AD433E0_)
				hr_ = details::UIX_Frame_RegisterSafeCtrl(pControl);
#endif
				if (pProvider)
				{
					::ATL::CComPtr<IUnknown> pHost;
					hr_ = TWindow::QueryHost(&pHost);
					if (pHost)
					{
						::ATL::CComQIPtr<IObjectWithSite> pObject;
						hr_ = pHost.QueryInterface(&pObject);
						if (pObject)
							pObject->SetSite(pProvider);
					}
				}
				hr_ = this->DispEventAdvise(pControl);
				::ATL::CComQIPtr<IWebBrowser2> pWebBrowser;
				hr_ = pControl.QueryInterface(&pWebBrowser);
				if (pWebBrowser)
					pWebBrowser->QueryInterface(IID_IOleInPlaceActiveObject, (void**)&m_act_object);
				if (m_act_object)
					details::UIX_Frame_KeyboardHandler_GetCacheObject().Register(TWindow::m_hWnd, m_act_object);
				if (true)
					details::UIX_Frame_MouseEvtHandler_GetCacheObject().Register(TWindow::m_hWnd, &m_evt_handler);
			}
		}
		if (S_OK == hr_)
		{
			::ATL::CComQIPtr<IAxWinAmbientDispatch> spAmb;
			hr_ = TWindow::QueryHost(&spAmb);
			if (S_OK == hr_)
			{
				spAmb->put_AllowContextMenu(VARIANT_FALSE);
				spAmb->put_DocHostFlags( DOCHOSTUIFLAG_DIALOG | DOCHOSTUIFLAG_NO3DBORDER 
				                       | DOCHOSTUIFLAG_THEME
				                       | DOCHOSTUIFLAG_DISABLE_HELP_MENU
				                       | DOCHOSTUIFLAG_SCROLL_NO
				                       | DOCHOSTUIFLAG_DPI_AWARE);
			}
		}
	}
	::CoTaskMemFree(pCLSID);
	pCLSID = NULL;
	return hr_;
}

HRESULT  CWebBrowserWrap::SetBackColor(const COLORREF _clr) { HRESULT hr_ = S_OK;
	_clr;
	CWebBrowser_Helper helper(*this);
	HWND hwnd_server = NULL;
	hr_ = helper.FindServer(hwnd_server);
	if (NULL != hwnd_server && ::IsWindow(hwnd_server)) {
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setclasslongptrw
		HBRUSH brush = ::CreateSolidBrush(_clr);
		::SetClassLongPtrW(hwnd_server, GCLP_HBRBACKGROUND, (LONG_PTR)brush); // TODO: brush needs to be destroyed later?

	}
	return hr_;
}

#if 0/*(_WIN32_IE >= _WIN32_IE_IE60SP2)*/

HRESULT  CWebBrowserWrap::EnableFeature(const DWORD dwFeature, const bool bEnabled, const DWORD dwScope)
{
	::ATL::CComPtr<IWebBrowser2> browser;
	HRESULT hr_ = details::UIX_Frame_GetBrowserObject(*this, browser);
	if (S_OK == hr_)
	{
		hr_ = ::CoInternetSetFeatureEnabled((INTERNETFEATURELIST)dwFeature, dwScope, bEnabled);
	}
	return hr_;
}

HRESULT  CWebBrowserWrap::IsFeatureEnabled(const DWORD dwFeature, const DWORD dwScope)
{
	::ATL::CComPtr<IWebBrowser2> browser;
	HRESULT hr_ = details::UIX_Frame_GetBrowserObject(*this, browser);
	if (S_OK == hr_)
	{
		hr_ = ::CoInternetIsFeatureEnabled((INTERNETFEATURELIST)dwFeature, dwScope);
	}
	return hr_;
}

#endif