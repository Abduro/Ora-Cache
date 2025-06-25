#ifndef _MSXML_DEFS_H_INCLUDED
#define _MSXML_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 00:07:23.072, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MS XML v6 wrapper include header(s) declaration file;
*/
#include <atlbase.h>
#include <algorithm>    // for sorting the std::vector of string;

// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms753804(v=vs.85)
#include <msxml2.h>    // CLSID_DOMDocument30, CLSID_DOMDocument26 ;
#include <msxml6.h>    // CLSID_DOMDocument60 ;

#pragma comment(lib, "msxml2.lib")
#pragma comment(lib, "msxml6.lib")

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"
#include "sys.error.h"

#include "sys.mem.heap.h"
#include "com.def.base.h"

// https://en.wikipedia.org/wiki/MSXML ;
// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms764622(v=vs.85) ; guids of MSXML versions;

/* XML formats, examples:
	https://learn.microsoft.com/en-us/windows/deployment/usmt/xml-file-requirements ;
	https://learn.microsoft.com/en-us/windows/deployment/usmt/usmt-custom-xml-examples ;
*/

namespace shared { namespace xml { namespace ms {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms757837(v=vs.85) ; enumeration of program Ids that can be used;

	// CLSID_DOMDocument26 looks like to be removed from support due to:
	// https://support.microsoft.com/en-us/topic/ms07-042-vulnerability-in-microsoft-xml-core-services-could-allow-remote-code-execution-5846db72-8861-c39b-bf8b-169a1b378447 ;

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms766426(v=vs.85) ; MSXML2.DOMDocument.3.0, it looks like to be always installed;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms754671(v=vs.85) ; Msxml2.DOMDocument.4.0, requires its installation;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms759214(v=vs.85) ; Msxml2.DOMDocument.5.0, requires its installation;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms764622(v=vs.85) ; Msxml2.DOMDocument.6.0, requires its installation;

	class CServiceId { // this class field set may be extended if necessary;
	public:
		 CServiceId (void); CServiceId (const CServiceId&); CServiceId (CServiceId&&); CServiceId (const GUID& _cls_id, _pc_sz _p_prog_id);
		~CServiceId (void);

	public:
		const
		GUID&  ClsId (void) const;
		GUID&  ClsId (void) ;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		_pc_sz ProgId (void) const;
		void   ProgId (_pc_sz) ;

	public:
		CServiceId& operator = (const CServiceId&);
		CServiceId& operator = (CServiceId&&);       // no move/swap operation is applied, just copying data;

		CServiceId& operator <<(const GUID& _cld_id);
		CServiceId& operator <<(_pc_sz _p_prog_id);

	private:
		GUID    m_cls_id ;
		CString m_prog_id; // just for debug output messages for this time;
	};

	typedef ::std::vector<CServiceId> TRawSvcIds;

	class CSvc_Ids {
	public:
		 CSvc_Ids (void); CSvc_Ids (const CSvc_Ids&) = delete; CSvc_Ids (CSvc_Ids&&) = delete;
		~CSvc_Ids (void);

	public:
		const TRawSvcIds& Raw (void) const;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif

	private:
		CSvc_Ids& operator = (const CSvc_Ids&) = delete;
		CSvc_Ids& operator = (CSvc_Ids&&) = delete;

	private:
		TRawSvcIds m_ids;
	};

}}}

#endif/*_MSXML_DEFS_H_INCLUDED*/