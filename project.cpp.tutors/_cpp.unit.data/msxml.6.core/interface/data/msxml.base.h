#ifndef _MSXML_BASE_H_INCLUDED
#define _MSXML_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2024 at 19:51:14.8089054, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack MSXML data base provider interface declaration file;
*/
#include "msxml.defs.h"
#include "msxml.doc.h"

namespace shared { namespace xml { namespace ms {

	using CXmlDoc = shared::xml::ms::CDocument;

	class CProv_Base {
	public:
		 CProv_Base (void);
		 CProv_Base (const CProv_Base&);
		 CProv_Base (CProv_Base&&) = delete;
		~CProv_Base (void);

	public:
		const
		CXmlDoc&   Doc (void) const;     // gets a reference to XML document object (ro);
		CXmlDoc&   Doc (void)      ;     // gets a reference to XML document object (rw);
		TErrorRef  Error (void) const;

	public:
		CProv_Base&  operator = (const CProv_Base&);
		CProv_Base&  operator = (CProv_Base&&) = delete;

		CProv_Base&  operator <<(const CXmlDoc&);

	protected:
		mutable
		CError  m_error;
		CXmlDoc m_x_doc;
	};
}}}

#endif/*_MSXML_PROVIDER_H_INCLUDED*/