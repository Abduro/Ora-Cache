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
#include <dispex.h>
#include <map>
#include <vector>
#include <Exdisp.h>
#include <Exdispid.h>

#include "shared.dbg.h"
#include "shared.types.h"
#include "sys.error.h"

namespace ex_ui { namespace web { namespace IE { namespace defs {

	using namespace ::shared::types;

	using CError = ::shared::sys_core::CError;
	using TError = const CError;

	interface IWebBrowserEventHandler
	{
		virtual err_code BrowserEvent_BeforeNavigate  (_pc_sz lpszUrl) PURE;
		virtual err_code BrowserEvent_DocumentComplete(_pc_sz lpszUrl, const bool bStreamObject) PURE;
		virtual err_code BrowserEvent_OnMouseMessage  (const MSG&) { return __e_not_impl; }
	};

	interface IHtmlElementEventCallback
	{
		virtual err_code HtmlEvent_OnGeneric( _pc_sz lpszElement, _pc_sz lpszEvent ) { lpszElement; lpszEvent; return __s_ok; }
	};

}}}}

#endif/*_WEB_IE_DEFS_H_INCLUDED*/