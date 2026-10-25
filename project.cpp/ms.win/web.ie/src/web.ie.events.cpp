/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2026 at 12:04:51.014, UTC+4, Batumi, Thursday;
	This is Ebo Pack IE 11 IWebBrowser2 control events' sink interface implementation file;
*/
#include "web.ie.events.h"

using namespace ::ex_ui::web::IE;

namespace ex_ui { namespace web { namespace IE { namespace func_defs {

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

}}}} using namespace func_defs;

#pragma region cls::CSimpleEvtSink{}

CSimpleEvtSink:: CSimpleEvtSink (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("This sink is not initialized yet"); }
CSimpleEvtSink::~CSimpleEvtSink (void) {}

TError& CSimpleEvtSink::Error (void) const { return this->m_error; }

#pragma endregion