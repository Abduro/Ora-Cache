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
#include "msxml.gen.iface.h"
#include "msxml.root.h"

namespace shared { namespace xml { namespace ms {

	using CPrs_Err = CParseError;
	using TPrs_Err = const CPrs_Err;
	using CSvc_Id  = CServiceId ;

	class CDocument {
	public:
		 CDocument (void);
		 CDocument (const CDocument&);
		 CDocument (CDocument&&) = delete;
		~CDocument (void);

	public:
		err_code   Create(const bool _b_norm = false) ; // if input arg is true, XML DOM document object removes all whitespaces;
		err_code   Close (void) ;                       // destroys XML DOM document object;
		TPrs_Err&  Error (void) const;                  // gets a reference to the last error object;

		const bool Is (void) const;                     // returns true if xml document interface is created successfully; maybe replaced by calling if (!!Ptr());

		err_code   Load (_pc_sz _xml_file_path);

#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TDocPtr&   Ptr (void) const;
		TDocPtr&   Ptr (void)      ;
		const
		CNode&     Root  (void) const;          // gets root node reference (ra);
		CNode&     Root  (void)      ;          // gets root node reference (rw);
		const
		CSvc_Id&   Svc_Id (void) const;
		CSvc_Id&   Svc_Id (void) ;

	public:
		CDocument& operator = (const CDocument&);
		CDocument& operator = (CDocument&&) = delete;

		CDocument& operator <<(const TDocPtr&);
		CDocument& operator <<(const CSvc_Id&);

		const
		TDocPtr&   operator ()(void) const;
		TDocPtr&   operator ()(void)      ;

	private:
		TDocPtr    m_pDoc ;
		CPrs_Err   m_error;
		CSvc_Id    m_svc_id;
		CNode      m_root ;
	};

}}}

#endif/*_MSXMLDOCUMENT_H_INCLUDED*/