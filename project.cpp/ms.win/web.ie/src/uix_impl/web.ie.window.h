#ifndef _WEB_IE_BROWSER_WRAP_H_INCLUDED
#define _WEB_IE_BROWSER_WRAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser control host window class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 3:45:02p, UTC+7, Novosibirsk, Monday;
*/
#include "web.ie.browser.h"

namespace ex_ui { namespace web { namespace IE { namespace core { using namespace ::ex_ui::web::IE::defs;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/caxwindow2t ;
	// https://learn.microsoft.com/en-us/cpp/atl/reference/caxwindow-class ;

	class CBrowserWnd;
	static const uint32_t nWebBrowserCtrlId = 1;

	typedef IDispEventImpl<nWebBrowserCtrlId, CBrowserWnd, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, -1, -1> THtmlSink;

	typedef CWindowImpl<CBrowserWnd, CAxWindow> TBrwWindow;
	typedef CComPtr<IOleInPlaceActiveObject>    TActiveObject;
	typedef CComPtr<IServiceProvider>           TSvcProvider;

	class CBrowserWnd : public TBrwWindow, THtmlSink {
		friend class CWebBrowser;
		enum { eAsyncRedirect = WM_USER + 1 };
	public:
		 CBrowserWnd (void) = delete; CBrowserWnd (const CBrowserWnd&) = delete; CBrowserWnd (CBrowserWnd&&) = delete;
		 CBrowserWnd (IWbEvtHandler&);
		~CBrowserWnd (void) = default;

		static _ATL_FUNC_INFO BeforeNavigate2_Info;
		static _ATL_FUNC_INFO DocumentComplete_Info;
		static _ATL_FUNC_INFO NavigateError_Info;

		DECLARE_WND_SUPERCLASS(_T("ex_ui::web::IE::Window"), ::ATL::CAxWindow::GetWndClassName());

		BEGIN_MSG_MAP(CBrowserWnd)
			MESSAGE_HANDLER(WM_CLOSE      , OnClose   )
			MESSAGE_HANDLER(WM_CREATE     , OnCreate  )
			MESSAGE_HANDLER(WM_ERASEBKGND , OnErase   )
			MESSAGE_HANDLER(eAsyncRedirect, OnRedirect)
		END_MSG_MAP()

		BEGIN_SINK_MAP(CBrowserWnd)
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2 , BeforeNavigate2 , &BeforeNavigate2_Info )
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, DocumentComplete, &DocumentComplete_Info)
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_NAVIGATEERROR   , NavigateError   , &NavigateError_Info   )
		END_SINK_MAP()

		err_code CreateObject (const HWND hParent, const rect_t& rcArea, TSvcProvider&, const bool bVisible); // creates an instance of IWebBrowser2 ActiveX control;
		err_code SetBackColor (const COLORREF _clr);
#if 0 /*(_WIN32_IE >= _WIN32_IE_IE60SP2)*/
		err_code EnableFeature (const dword_t dwFeature, const bool bEnabled, const dword_t dwScope = SET_FEATURE_ON_PROCESS);
		err_code IsFeatureEnabled (const dword_t dwFeature, const dword_t dwScope = GET_FEATURE_FROM_PROCESS);
#endif
		TError& Error (void) const;

	private:
		LRESULT OnClose    (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnCreate   (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnErase    (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnRedirect (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
	
		STDMETHOD(BeforeNavigate2)( LPDISPATCH pDisp, LPVARIANT pUrl, LPVARIANT pFlags, 
		                            LPVARIANT  pTargetFrameName,
		                            LPVARIANT  pPostData,
		                            LPVARIANT  pHeaders,
		                            VARIANT_BOOL* pCancel);
		STDMETHOD(DocumentComplete)(LPDISPATCH pDisp, LPVARIANT pUrl);
		STDMETHOD(NavigateError)  ( LPDISPATCH pDisp, LPVARIANT pUrl, LPVARIANT pTargetFrameName,
		                            LPVARIANT  pStatusCode,
		                            VARIANT_BOOL* pCancel);

		CBrowserWnd& operator = (const CBrowserWnd&) = delete; CBrowserWnd& operator = (CBrowserWnd&&) = delete;

		bool           m_bInited     ;
		IWbEvtHandler& m_evt_handler ;
		TActiveObject  m_act_object  ;
		_variant_t     m_async_data  ;
		bool           m_bDoNotNotify;
		bool           m_bStreamObject;
		CError m_error;
	};
}}}}

#endif/*_WEB_IE_BROWSER_WRAP_H_INCLUDED*/