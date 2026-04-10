#ifndef __MSXML_SCHEMA_H_INCLUDED
#define __MSXML_SCHEMA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2026 at 03:28:30.378, UTC+4, Batumi, Friday;
	This is Ebo Pack data provider XML schema cache wrapper interface declaration file;
*/
#include "msxml.defs.h"

namespace shared { namespace xml { namespace ms {

	using CSvc_Id = CServiceId;
	// https://learn.microsoft.com/en-us/previous-versions/office/infopath-external/dn929912(v=office.15) ;
	class CSchema {
	public:
		 CSchema (void); CSchema (const CSchema&) = delete; CSchema (CSchema&&) = delete;
		~CSchema (void) = default;

		err_code Create (void);
		err_code Destroy (void);

		TError&  Error (void) const;
		const bool Is (void) const;

		err_code   Load (_pc_sz _xsd_file_path);
		const
		TSchemaPtr&   Ptr (void) const;
		TSchemaPtr&   Ptr (void) ;

		const
		CSvc_Id&   Svc_Id (void) const;
		CSvc_Id&   Svc_Id (void) ;

		const
		TSchemaPtr&   operator ()(void) const;
		TSchemaPtr&   operator ()(void)      ;

	private:
		CSchema& operator = (const CSchema&) = delete; CSchema& operator = (CSchema&&) = delete;
		TSchemaPtr m_pSchema;
		CError     m_error;
		CSvc_Id    m_svc_id;
	};

}}}

#endif/*__MSXML_SCHEMA_H_INCLUDED*/