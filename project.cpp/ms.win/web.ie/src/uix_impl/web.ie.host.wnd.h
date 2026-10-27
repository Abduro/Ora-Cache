#ifndef _WEB_IE_BROWSER_WRAP_H_INCLUDED
#define _WEB_IE_BROWSER_WRAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is UIX library web browser control host window class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 3:45:02p, UTC+7, Novosibirsk, Monday;
*/
#include "web.ie.browser.h"
#include "web.ie.events.h"

namespace ex_ui { namespace web { namespace IE { namespace core {
	
	using namespace ::ex_ui::web::IE::defs;
	using namespace ::ex_ui::web::IE::events;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/caxwindow2t ;
	// https://learn.microsoft.com/en-us/cpp/atl/reference/caxwindow-class ;

	class CBrowserHost;
	static const uint32_t nWebBrowserCtrlId = 1;

	typedef IDispEventImpl<nWebBrowserCtrlId, CBrowserHost, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 0> THtmlSink;

	typedef CWindowImpl<CBrowserHost, CAxWindow> TBrowserHost;  // this is ATL::CWindowImpl<> template's specialization type definition;
	typedef CComPtr<IOleInPlaceActiveObject>     TActiveObject;
	typedef CComPtr<IServiceProvider>            TSvcProvider;  // https://learn.microsoft.com/en-us/windows/win32/api/servprov/nn-servprov-iserviceprovider ;

	class CBrowserHost : public TBrowserHost {
		friend class CWebBrowser;
		enum { eAsyncRedirect = WM_USER + 1 };
	public:
		 CBrowserHost (void) = delete; CBrowserHost (const CBrowserHost&) = delete; CBrowserHost (CBrowserHost&&) = delete;
		 CBrowserHost (IWbEvtHandler&);
		~CBrowserHost (void) = default;

		DECLARE_WND_SUPERCLASS(_T("ex_ui::web::IE::Window"), ::ATL::CAxWindow::GetWndClassName());

		BEGIN_MSG_MAP(CBrowserHost)
			MESSAGE_HANDLER(WM_CLOSE      , OnClose   )
			MESSAGE_HANDLER(WM_CREATE     , OnCreate  )
			MESSAGE_HANDLER(WM_ERASEBKGND , OnErase   )
			MESSAGE_HANDLER(eAsyncRedirect, OnRedirect)
			MESSAGE_HANDLER(WM_SIZE       , OnSize    )
#if (0)
			if (TBrowserHost::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, 0))
				return true;
#endif
		END_MSG_MAP()

		err_code CreateObject (const HWND hParent, const rect_t& rcArea, TSvcProvider&, const bool bVisible); // creates an instance of IWebBrowser2 ActiveX control;
		err_code SetBackColor (const COLORREF _clr);
#if 0 /*(_WIN32_IE >= _WIN32_IE_IE60SP2)*/
		err_code EnableFeature (const dword_t dwFeature, const bool bEnabled, const dword_t dwScope = SET_FEATURE_ON_PROCESS);
		err_code IsFeatureEnabled (const dword_t dwFeature, const dword_t dwScope = GET_FEATURE_FROM_PROCESS);
#endif
		TError&  Error (void) const;
		err_code Refresh (void);
		const
		TWebEvtSinks& Sinks (void) const;
		TWebEvtSinks& Sinks (void) ;

	private:
		LRESULT OnClose    (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnCreate   (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnErase    (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnRedirect (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);
		LRESULT OnSize     (UINT uMsg, WPARAM wParam, LPARAM lParam, bool_t& bHandled);

		CBrowserHost& operator = (const CBrowserHost&) = delete; CBrowserHost& operator = (CBrowserHost&&) = delete;

		bool           m_bInited     ;
		IWbEvtHandler& m_evt_handler ;
		TActiveObject  m_act_object  ;
		_variant_t     m_async_data  ;
		bool           m_bDoNotNotify;
		bool           m_bStreamObject;
		CError  m_error;
		TWebEvtSinks   m_evt_sinks;
	};
}}}}

#endif/*_WEB_IE_BROWSER_WRAP_H_INCLUDED*/