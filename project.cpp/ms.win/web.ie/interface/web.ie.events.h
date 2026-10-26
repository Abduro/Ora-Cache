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
	extern _ATL_FUNC_INFO MouseClick_info;        // void __stdcall MouseClick(IDispatch* pDisp, IHTMLEventObj* pEvtObj);
#pragma endregion
}

	class CBrowserSink;
	static const uint32_t uBrowserEvtSinkId = 1;  // the identifier for browser event sink;
	static const uint32_t uHtmlDocEvtSinkId = 2;  // the identifier for HTML document event sink;

	typedef IDispEventSimpleImpl<uBrowserEvtSinkId, CBrowserSink, &DIID_DWebBrowserEvents2 >  TBrowserEvtSnk;
    typedef IDispEventSimpleImpl<uHtmlDocEvtSinkId, CBrowserSink, &DIID_HTMLDocumentEvents2>  THtmlDocEvtSnk;

	class CBase_Sink {
	protected:
		CBase_Sink (void); CBase_Sink (const CBase_Sink&) = delete; CBase_Sink (CBase_Sink&&) = delete; ~CBase_Sink (void) = default;
	public:
		err_code Attach (HWND _h_host_wnd); // attaches this wrapper to an existing CAxWindow hosting the WebBrowser control;

		TError&  Error (void) const;
		bool  Is_advised (void) const;      // returns 'true' in case if this sink is advised to the event source by this class child class object;
		bool  Is_attached (void) const;     // returns 'true' in case if this sink is attached to web browser control host (or container) window;

	protected:
		CBase_Sink& operator = (const CBase_Sink&) = delete; CBase_Sink& operator = (CBase_Sink&&) = delete;
		CError m_error;
		bool   m_advised;
		CAxWindow  m_host_wnd;  // it holds the host window handle that is created outside of this class;
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
		TDocument2Ptr m_pDoc2;
	};

#if (0)
class CHtmlEventWrapper
    ~CHtmlEventWrapper()
    {
        UnadviseAll();
    }

    // Proactively clean up hooks
    void UnadviseAll()
    {
        UnadviseDocument();

        if (m_bBrowserAdvised && m_spWebBrowser)
        {
            DispEventUnadvise(m_spWebBrowser, &DIID_DWebBrowserEvents2);
            m_bBrowserAdvised = false;
        }
        m_spWebBrowser.Release();
    }

    // Explicitly navigate to a file or resource safely
    HRESULT Navigate(const CComBSTR& bstrUrl)
    {
        // Unadvise document immediately BEFORE navigating to avoid crash or memory state corruption
        UnadviseDocument();

        if (!m_spWebBrowser) return E_POINTER;

        CComVariant vEmpty;
        return m_spWebBrowser->Navigate2(&CComVariant(bstrUrl), &vEmpty, &vEmpty, &vEmpty, &vEmpty);
    }

private:
    // Safely detaches from the current document instance
    void UnadviseDocument()
    {
        if (m_bDocAdvised && m_spDocument)
        {
            DispEventUnadvise(m_spDocument, &DIID_HTMLDocumentEvents2);
            m_bDocAdvised = false;
        }
        m_spDocument.Release();
    }

    // Automatically wires up the fresh document instance
    void AdviseDocument()
    {
        UnadviseDocument(); // Clear any stale state first

        if (!m_spWebBrowser) return;

        CComPtr<IDispatch> spDocDisp;
        m_spWebBrowser->get_Document(&spDocDisp);
        if (spDocDisp)
        {
            spDocDisp->QueryInterface(IID_IHTMLDocument2, (void**)&m_spDocument);
            if (m_spDocument)
            {
                HRESULT hr = DispEventAdvise(m_spDocument, &DIID_HTMLDocumentEvents2);
                if (SUCCEEDED(hr))
                {
                    m_bDocAdvised = true;
                }
            }
        }
    }

public:
    // ATL Sink Map using Simple Event entries to explicitly state target interfaces
    BEGIN_SINK_MAP(CHtmlEventWrapper)
        // Browser Events
        SINK_ENTRY_INFO(IDC_BROWSER_SINK_ID, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete, &OnClickInfo /* Reuse or create matching generic info block */)
        // Document Events (e.g., intercepting a click inside the HTML body)
        SINK_ENTRY_INFO(IDC_DOCUMENT_SINK_ID, DIID_HTMLDocumentEvents2, DISPID_HTMLDOCUMENTEVENTS2_ONCLICK, OnHtmlClick, &OnClickInfo)
    END_SINK_MAP()

    // --- DWebBrowserEvents2 Handler ---
    void __stdcall OnDocumentComplete(IDispatch* pDisp, VARIANT* URL)
    {
        // Guard: Verify this event came from the top-level main frame browser instance
        CComPtr<IUnknown> spUnkBrowser;
        CComPtr<IUnknown> spUnkDisp;
        if (m_spWebBrowser && SUCCEEDED(m_spWebBrowser->QueryInterface(IID_IUnknown, (void**)&spUnkBrowser)))
        {
            pDisp->QueryInterface(IID_IUnknown, (void**)&spUnkDisp);
            if (spUnkBrowser == spUnkDisp)
            {
                // Top level load finished! Safe to link up our document event sink map
                AdviseDocument();
            }
        }
    }

    // --- HTMLDocumentEvents2 Handler ---
    void __stdcall OnHtmlClick(IHTMLEventObj* pEvtObj)
    {
        // Handle your click business here!
        ATLTRACE(_T("HTML Document body clicked.\n"));
    }

private:
    CAxWindow               m_wndAx;
    CComPtr<IWebBrowser2>    m_spWebBrowser;
    CComPtr<IHTMLDocument2>  m_spDocument;
    bool                     m_bBrowserAdvised;
    bool                     m_bDocAdvised;
};

#endif

}}}}
#endif/*_WEB_IE_EVENTS_H_INCLUDED*/