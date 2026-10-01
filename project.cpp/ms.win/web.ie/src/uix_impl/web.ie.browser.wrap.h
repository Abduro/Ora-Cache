#ifndef _UIXFRAMEWND_H_EDB40837_A7D7_43e9_883E_EA3E3C8717A2_INCLUDED
#define _UIXFRAMEWND_H_EDB40837_A7D7_43e9_883E_EA3E3C8717A2_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser control host window class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 3:45:02p, UTC+7, Novosibirsk, Monday;
*/
#include "shared.web.browser.h"

namespace ex_ui { namespace web { namespace core
{
	class CWebBrowserWrap;
	static const UINT nWebBrowserCtrlId = 1;
	typedef ::ATL::IDispEventImpl<nWebBrowserCtrlId, CWebBrowserWrap, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, -1, -1> THtmlSink;

	class CWebBrowserWrap:
		public  ::ATL::CWindowImpl<CWebBrowserWrap, ::ATL::CAxWindow>,
		public  THtmlSink
	{
		typedef ::ATL::CWindowImpl<CWebBrowserWrap, ::ATL::CAxWindow>  TWindow;
		typedef ::ATL::CComPtr<IOleInPlaceActiveObject>                TActiveObject;
		friend class CWebBrowser;
	private:
		enum {
			eAsyncRedirect = WM_USER + 1
		};
	private:
		bool                       m_bInited     ;
		IWebBrowserEventHandler&   m_evt_handler ;
		TActiveObject              m_act_object  ;
		_variant_t                 m_async_data  ;
		bool                       m_bDoNotNotify;
		bool                       m_bStreamObject;
	public:
		 CWebBrowserWrap(IWebBrowserEventHandler&);
		~CWebBrowserWrap(void);
	public:
		static _ATL_FUNC_INFO BeforeNavigate2_Info;
		static _ATL_FUNC_INFO DocumentComplete_Info;
		static _ATL_FUNC_INFO NavigateError_Info;
	public:
#if (1)
		DECLARE_WND_SUPERCLASS(_T("ex_ui::web::Window"), ::ATL::CAxWindow::GetWndClassName());
//		DECLARE_WND_CLASS_EX(_T("ex_ui::web::Window"), CS_SAVEBITS, 0);
#else
		static ATL::CWndClassInfo& GetWndClassInfo() {
			static ATL::CWndClassInfo wc = {
				{
					sizeof(WNDCLASSEX), 0, StartWindowProc, 0, 0, NULL, NULL, NULL, (HBRUSH)(RGB(0,0,0) + 1), NULL, _T("ex_ui::Window"), NULL
				},
				::ATL::CAxWindow::GetWndClassName(), NULL, NULL, TRUE, 0, _T("")
			};
			return wc;
		}
#endif
		BEGIN_MSG_MAP(CWebBrowserWrap)
			MESSAGE_HANDLER(WM_CLOSE      , OnClose   )
			MESSAGE_HANDLER(WM_CREATE     , OnCreate  )
			MESSAGE_HANDLER(WM_ERASEBKGND , OnErase   )
			MESSAGE_HANDLER(eAsyncRedirect, OnRedirect)
		END_MSG_MAP()
	public:
		BEGIN_SINK_MAP(CWebBrowserWrap)
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2 , BeforeNavigate2 , &BeforeNavigate2_Info )
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, DocumentComplete, &DocumentComplete_Info)
			SINK_ENTRY_INFO(nWebBrowserCtrlId, DIID_DWebBrowserEvents2, DISPID_NAVIGATEERROR   , NavigateError   , &NavigateError_Info   )
		END_SINK_MAP()
	private:
		LRESULT OnClose   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnCreate  (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnErase   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnRedirect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	private:
		STDMETHOD(BeforeNavigate2)( LPDISPATCH pDisp, LPVARIANT pUrl, LPVARIANT pFlags, 
		                            LPVARIANT  pTargetFrameName,
		                            LPVARIANT  pPostData,
		                            LPVARIANT  pHeaders,
		                            VARIANT_BOOL* pCancel);
		STDMETHOD(DocumentComplete)(LPDISPATCH pDisp, LPVARIANT pUrl);
		STDMETHOD(NavigateError)  ( LPDISPATCH pDisp, LPVARIANT pUrl, LPVARIANT pTargetFrameName,
		                            LPVARIANT  pStatusCode,
		                            VARIANT_BOOL* pCancel);
	public:
		HRESULT  CreateObject(const HWND hParent, const RECT& rcArea, ::ATL::CComPtr<IServiceProvider>&, const bool bVisible);
		HRESULT  SetBackColor(const COLORREF _clr);
#if 0 /*(_WIN32_IE >= _WIN32_IE_IE60SP2)*/
		HRESULT  EnableFeature(const DWORD dwFeature, const bool bEnabled, const DWORD dwScope = SET_FEATURE_ON_PROCESS);
		HRESULT  IsFeatureEnabled(const DWORD dwFeature, const DWORD dwScope = GET_FEATURE_FROM_PROCESS);
#endif
	};
}}}

#endif/*_UIXFRAMEWND_H_EDB40837_A7D7_43e9_883E_EA3E3C8717A2_INCLUDED*/