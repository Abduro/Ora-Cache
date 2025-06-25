#ifndef _MSXMLDOCUMENT_H_INCLUDED
#define _MSXMLDOCUMENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Jul-2015 at 3:36:56pm, GMT+7, Phuket, Rawai, Saturday;
	This is Shared Lite Generic XML Data Provider class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack shared MS XML Document interface on 14-Apr-2024 at 16:54:06.0964777, UTC+7, Novosibirsk, Sunday;
*/
#include "msxml.defs.h"
#include "msxml.error.h"

namespace shared { namespace xml { namespace ms {

	using CPrs_Err = CParseError;
	using TPrs_Err = const CPrs_Err;
	using CSvc_Id  = CServiceId ;

	typedef ::ATL::CComPtr<IXMLDOMDocument2>  TDocumentPtr; typedef TDocumentPtr TDocPtr;

	// https://stackoverflow.com/questions/3080224/ways-to-parse-xml-in-c-win32 ;
	// https://libexpat.github.io/doc/api/latest/ ; for the next use;
	// https://gitlab.gnome.org/GNOME/libxml2 ; for the next use;

	class CDocument {
	public:
		 CDocument (void);
		 CDocument (const CDocument&);
		 CDocument (CDocument&&) = delete;
		~CDocument (void);

	public:
		err_code   Create(void) ;
		TPrs_Err&  Error (void) const;
		const bool Is (void) const;     // returns true if XML document interface is created successfully; maybe replaced by calling if (!!Ptr());

#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TDocPtr&   Ptr (void) const;
		TDocPtr&   Ptr (void)      ;
		const
		CSvc_Id&   Svc_Id (void) const;
		CSvc_Id&   Svc_Id (void) ;

	public:
		CDocument& operator = (const CDocument&);
		CDocument& operator = (CDocument&&) = delete;
		CDocument& operator <<(const TDocPtr&);
		CDocument& operator <<(const CSvc_Id&);

	private:
		TDocPtr  m_pDoc ;
		CPrs_Err m_error;
		CSvc_Id  m_svc_id;

	};

}}}

#endif/*_MSXMLDOCUMENT_H_INCLUDED*/