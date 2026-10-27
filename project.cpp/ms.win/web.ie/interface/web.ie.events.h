#ifndef _WEB_IE_EVENTS_H_INCLUDED
#define _WEB_IE_EVENTS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2026 at 12:03:14.227, UTC+4, Batumi, Thursday;
	This is Ebo Pack IE 11 IWebBrowser2 control events' sink interface declaration file;
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { namespace events { using namespace ::ex_ui::web::IE::defs;
namespace func_defs {

#pragma region TBrowserEvtSnk{}
	extern _ATL_FUNC_INFO BeforeNavigate2_Info;   // void __stdcall BeforeNavigate2  (IDispatch* pDisp, var_ptr pURL, var_ptr pFlags, var_ptr pTargetFrame, var_ptr pPostData, var_ptr pHeaders, var_bool* pvbCancel);
	extern _ATL_FUNC_INFO DocumentComplete_Info;  // void __stdcall DocumentComplete (IDispatch* pDisp, var_ptr pURL);
	extern _ATL_FUNC_INFO NavigateComplete2_Info; // void __stdcall NavigateComplete2(IDispatch* pDisp, var_ptr pURL);
	extern _ATL_FUNC_INFO NavigateError_Info;     // void __stdcall NavigateError(IDispatch* pDisp, var_ptr pURL, var_ptr pFrame, var_ptr pStatusCode, var_bool* pCancel);
	extern _ATL_FUNC_INFO NewWindow2_Info;        // void __stdcall NewWindow2 (IDispatch** ppDisp, var_bool* pCancel);
	extern _ATL_FUNC_INFO NewWindow3_Info;        // void __stdcall NewWindow3 (IDispatch** ppDisp, var_bool* pCancel, dword_t dwFlags, BSTR bstrUrlContext, BSTR bstrUrl);
#pragma endregion
#pragma region THtmlDocEvtSnk{}
	extern _ATL_FUNC_INFO MouseClick_info;        // void __stdcall MouseClick(IHTMLEventObj* pEvtObj);
#pragma endregion
}

	class CBrowserSink;
	class CDoc_2_Sink;
	static const uint32_t uBrowserEvtSinkId = 1;  // the identifier for browser event sink;
	static const uint32_t uHtmlDocEvtSinkId = 2;  // the identifier for HTML document event sink;

	typedef IDispEventSimpleImpl<uBrowserEvtSinkId, CBrowserSink, &DIID_DWebBrowserEvents2 >  TBrowserEvtSnk;
    typedef IDispEventSimpleImpl<uHtmlDocEvtSinkId, CDoc_2_Sink , &DIID_HTMLDocumentEvents2>  THtmlDocEvtSnk;

	class CBase_Props { friend class CBase_Sink;
		enum  e_indices : uint32_t { e_advised, e_attached, e_inactive, e_streamed };
	public:
		CBase_Props (void); CBase_Props (const CBase_Props&) = delete; CBase_Props (CBase_Props&&) = delete; ~CBase_Props (void) = default;

		bool  Advised  (void) const; // returns 'true' in case if this sink is advised to the event source by this class child class object;
		bool  Attached (void) const; // returns 'true' in case if this sink is attached to web browser control host (or container) window;
		bool  InActive (void) const; // returns 'true' in case if this sink is set to 'silent' mode, i.e. in 'inactive' state;
		bool& InActive (void) ;      // gives the direct reference to 'inactive' property value;
		bool  Streamed (void) const; // gets the current mode in which the web browser control opens an URL being navigated to;
		bool& Streamed (void) ;      // sets the current mode of opening an URL to either as a stream or not; this is required for app callback;

	private:
		CBase_Props& operator = (const CBase_Props&) = delete; CBase_Props& operator = (CBase_Props&&) = delete;
		bool  m_flags[e_indices::e_streamed + 1];
	};

	class CBase_Sink {
	protected:
		CBase_Sink (void); CBase_Sink (const CBase_Sink&) = delete; CBase_Sink (CBase_Sink&&) = delete; ~CBase_Sink (void) = default;
	public:
		using CProps = CBase_Props;

		err_code Attach (HWND _h_host_wnd); // attaches this wrapper to an existing CAxWindow hosting the WebBrowser control;

		TError&  Error (void) const;
		const
		CProps&  Props (void) const;
		CProps&  Props (void) ;


		CBase_Sink& operator << (HWND _h_host_wnd); // just invokes this::Attach();
		CBase_Sink& operator << (IWbEvtHandler*);   // sets event handler pointer; not threa-save, because it is called from main thread only;

	protected:
		bool&  Advised (void) { return this->m_props.m_flags[CProps::e_advised]; }
		CError m_error;
		CAxWindow      m_host_wnd;  // it holds the host window handle that is created outside of this class;
		IWbEvtHandler* m_evt_handler_ptr;
		CBase_Props    m_props;
	private:
		CBase_Sink& operator = (const CBase_Sink&) = delete; CBase_Sink& operator = (CBase_Sink&&) = delete;
	};

	// https://learn.microsoft.com/en-us/cpp/atl/reference/idispeventimpl-class ;
	class CBrowserSink : public TBrowserEvtSnk, public CBase_Sink { typedef CBase_Sink TBase;
	public:
		 CBrowserSink (void); CBrowserSink (const CBrowserSink&) = delete; CBrowserSink (CBrowserSink&&) = delete;
		~CBrowserSink (void);

		BEGIN_SINK_MAP(CBrowserSink)
			SINK_ENTRY_INFO(uBrowserEvtSinkId, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2 , BeforeNavigate2 , &func_defs::BeforeNavigate2_Info )
			SINK_ENTRY_INFO(uBrowserEvtSinkId, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, DocumentComplete, &func_defs::DocumentComplete_Info)
			SINK_ENTRY_INFO(uBrowserEvtSinkId, DIID_DWebBrowserEvents2, DISPID_NAVIGATEERROR   , NavigateError   , &func_defs::NavigateError_Info   )
		END_SINK_MAP()

		virtual __declspec(nothrow) err_code BeforeNavigate2 (IDispatch* pDisp, var_ptr pUrl, var_ptr pFlags, var_ptr pTargetFrame, var_ptr pPostData, var_ptr pHeaders, var_bool* pCancel);
		virtual __declspec(nothrow) err_code DocumentComplete(IDispatch* pDisp, var_ptr pUrl);
		virtual __declspec(nothrow) err_code NavigateError   (IDispatch* pDisp, var_ptr pUrl, var_ptr pTargetFrame, var_ptr pStatusCode, var_bool* pCancel);

		err_code Advise (void);
		err_code Unadvise (void);   // proactively cleans up hook;

		bool Is_valid (void) const; // checks smart pointer of browser control for validity;

	private:
		CBrowserSink& operator = (const CBrowserSink&) = delete; CBrowserSink& operator = (CBrowserSink&&) = delete;
		TWebBrwPtr m_pBrowser;
	};

	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa769700(v=vs.85) << HTMLElementEvents interface;
	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa769764(v=vs.85) << HTMLDocumentEvents2 interface;
	class CDoc_2_Sink : public THtmlDocEvtSnk, public CBase_Sink { typedef CBase_Sink TBase;
	public:
		CDoc_2_Sink (void); CDoc_2_Sink (const CDoc_2_Sink&) = delete; CDoc_2_Sink (CDoc_2_Sink&&) = delete; ~CDoc_2_Sink (void);

		BEGIN_SINK_MAP(CDoc_2_Sink)
			SINK_ENTRY_INFO(uHtmlDocEvtSinkId, DIID_HTMLDocumentEvents2, DISPID_HTMLDOCUMENTEVENTS2_ONCLICK, OnClick, &func_defs::MouseClick_info)
		END_SINK_MAP()

		virtual __declspec(nothrow) err_code OnClick (IUnknown* pEvtObj);

		err_code Advise (const TWebBrwPtr& _p_browser);
		err_code Unadvise (void);   // proactively cleans up hook;

		bool Is_valid (void) const; // checks smart pointer of browser control for validity;

	private:
		CDoc_2_Sink& operator = (const CDoc_2_Sink&) = delete; CDoc_2_Sink& operator = (CDoc_2_Sink&&) = delete;
		TDocument2Ptr m_pDoc2;
	};

}}}}
#endif/*_WEB_IE_EVENTS_H_INCLUDED*/