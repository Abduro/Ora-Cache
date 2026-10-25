#ifndef _WEB_IE_EVENTS_H_INCLUDED
#define _WEB_IE_EVENTS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2026 at 12:03:14.227, UTC+4, Batumi, Thursday;
	This is Ebo Pack IE 11 IWebBrowser2 control events' sink interface declaration file;
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;
namespace func_defs {
	extern _ATL_FUNC_INFO BeforeNavigate2_Info;   // void __stdcall BeforeNavigate2(IDispatch* pDisp, VARIANT* pvtURL, VARIANT* pvtFlags, VARIANT* pvtTargetFrameName, VARIANT* pvtPostData, VARIANT* pvtHeaders, VARIANT_BOOL* pvbCancel)
	extern _ATL_FUNC_INFO DocumentComplete_Info;  // void __stdcall DocumentComplete(IDispatch* pDisp, VARIANT* pvtURL);
	extern _ATL_FUNC_INFO NavigateComplete2_Info; // void __stdcall NavigateComplete2(IDispatch* pDisp, VARIANT* pvtURL);
	extern _ATL_FUNC_INFO NavigateError_Info;     // void __stdcall NavigateError(IDispatch* pDisp, VARIANT* pvtURL, VARIANT* pvtFrame, VARIANT* pvtStatusCode, VARIANT_BOOL* pvbCancel);
	extern _ATL_FUNC_INFO NewWindow2_Info;        // void __stdcall NewWindow2(IDispatch** ppDisp, VARIANT_BOOL* Cancel);
	extern _ATL_FUNC_INFO NewWindow3_Info;        // void __stdcall NewWindow3(IDispatch** ppDisp, VARIANT_BOOL* Cancel, DWORD dwFlags, BSTR bstrUrlContext, BSTR bstrUrl);
}

	// https://learn.microsoft.com/en-us/cpp/atl/reference/idispeventimpl-class ;
	class CSimpleEvtSink {
	public:
		 CSimpleEvtSink (void); CSimpleEvtSink (const CSimpleEvtSink&) = delete; CSimpleEvtSink (CSimpleEvtSink&&) = delete;
		~CSimpleEvtSink (void);

		TError& Error (void) const;

	private:
		CSimpleEvtSink& operator = (const CSimpleEvtSink&) = delete; CSimpleEvtSink& operator = (CSimpleEvtSink&&) = delete;
		CError m_error;
	};
}}}
#endif/*_WEB_IE_EVENTS_H_INCLUDED*/