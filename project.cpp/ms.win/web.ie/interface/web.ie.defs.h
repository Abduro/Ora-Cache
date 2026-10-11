#ifndef _WEB_IE_DEFS_H_INCLUDED
#define _WEB_IE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is Ebo Pack shared UIX Web Browser library common interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 2:48:42p, UTC+7, Novosibirsk, Monday;
*/
#include <atlbase.h>
#include <atlexcept.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atlsafe.h>
#include <comdef.h>
#include <comutil.h>
#include <dispex.h>
#include <map>
#include <vector>
#include <Exdisp.h>
#include <Exdispid.h>

#include "shared.dbg.h"
#include "shared.types.h"
#include "sys.error.h"
#include "sys.mem.heap.h"

namespace ex_ui { namespace web { namespace IE {
namespace core {
	class CBrowserWnd;
}	
namespace defs {

	using namespace ::shared::types;
	using namespace ::ATL;

	using CError = ::shared::sys_core::CError;
	using TError = const CError;

	using var_bool = VARIANT_BOOL;
	
	#define var_true  VARIANT_TRUE
	#define var_false VARIANT_FALSE

	using   ICmdTarget = IOleCommandTarget;

	typedef CComPtr<ICmdTarget>     TCmdTargetPtr;
	typedef CComPtr<IDispatch>      TDispatchPtr;    using TDispPtr = TDispatchPtr;
	typedef CComPtr<IHTMLDocument>  TDocument0Ptr;   using TDoc0Ptr = TDocument0Ptr;
	typedef CComPtr<IHTMLDocument2> TDocument2Ptr;   using TDoc2Ptr = TDocument2Ptr;
	typedef CComPtr<IHTMLDocument3> TDocument3Ptr;   using TDoc3Ptr = TDocument3Ptr;
	typedef CComPtr<IHTMLElement>   TElementPtr;     using TElemPtr = TElementPtr;

	using   ex_ui::web::IE::core::CBrowserWnd;
	typedef ::std::shared_ptr<CBrowserWnd> TBrwWndPtr; // https://learn.microsoft.com/en-us/cpp/standard-library/unique-ptr-class ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa752127(v=vs.85) ;
	typedef CComQIPtr<IWebBrowser2> TWebBrwPtr;

	interface IWbEvtHandler
	{
		virtual err_code WbEvt_BeforeNavigate  (_pc_sz _p_url) = 0;
		virtual err_code WbEvt_DocumentComplete(_pc_sz _p_url, const bool _b_use_stream) = 0;
		virtual err_code WbEvt_OnMouseMessage  (const MSG&) { return __e_not_impl; }
	};

	interface IHtmlElEvtClbk
	{
		virtual err_code ElEvt_OnGeneric ( _pc_sz _p_element, _pc_sz _p_event ) { _p_element; _p_event; return __s_ok; }
	};
}}}}

#endif/*_WEB_IE_DEFS_H_INCLUDED*/