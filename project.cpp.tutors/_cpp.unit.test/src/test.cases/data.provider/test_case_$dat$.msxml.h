#ifndef _TEST_CASE_$DAT$_MSXML_H_INCLUDED
#define _TEST_CASE_$DAT$_MSXML_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 13:53:31.133, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' MSXML wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$dat$.defs.h"
#include "msxml.doc.h"
#include "msxml.schema.h"

namespace ebo { namespace boo { namespace test { namespace data {
	// gets XML file path from the registry;
	class CTstLocator {
	public:
		enum class e_docs : uint32_t { // predefined xml document types;
			e_prov_list, // contains the path to the file of data providers' list;
			e_prov_logo, // data provider logo image encoded by base64bin;
			e_curr_spec, // contains the path to the file of currency specification;
		};
		enum class e_schemas : uint32_t {
			e_prov_list = (uint32_t) e_docs::e_curr_spec + 1,
			e_prov_logo,
			e_curr_spec,
		};
		 CTstLocator (void) = default; CTstLocator (const CTstLocator&) = delete; CTstLocator (CTstLocator&&) = delete;
		~CTstLocator (void) = default;

		CString  Get_path (const e_docs, const bool _b_cls_out = true); // gets the path of given document type; if empty path is returned the error occurs;
		CString  Get_path (const e_schemas, const bool _b_cls_out = true); // gets the path to XSD schema file by given value of enumeration;

		const
		TRegKeyEx& operator ()(void) const;
		TRegKeyEx& operator ()(void) ;

	private:
		CTstLocator& operator = (const CTstLocator&) = delete; CTstLocator& operator = (CTstLocator&&) = delete;
		TRegKeyEx  m_key;
	};

	using CDocument = shared::xml::ms::CDocument;

	class CTstXmlDoc {
	public:
		 CTstXmlDoc (void) = default; CTstXmlDoc (const CTstXmlDoc&) = delete; CTstXmlDoc (CTstXmlDoc&&) = delete;
		~CTstXmlDoc (void) = default;

		err_code  Load (_pc_sz _p_xml_path); // loads xml file and builds xml document (DOM);

		const
		CDocument& operator ()(void) const;
		CDocument& operator ()(void) ;

	private:
		CTstXmlDoc&  operator = (const CTstXmlDoc&) = delete; CTstXmlDoc& operator = (CTstXmlDoc&&) = delete;
		CDocument m_doc;
	};

	using CSchema = shared::xml::ms::CSchema;

	class CTstSchema {
	public:
		 CTstSchema (void) = default; CTstSchema (const CTstSchema&) = delete; CTstSchema (CTstSchema&&) = delete;
		~CTstSchema (void) = default;

		err_code  Load (_pc_sz _p_xsd_path); // loads xsd file and creates schema cache;

		const
		CSchema& operator ()(void) const;
		CSchema& operator ()(void) ;

	private:
		CTstSchema&  operator = (const CTstSchema&) = delete; CTstSchema& operator = (CTstSchema&&) = delete;
		CSchema m_schema;
	};

}}}}

#endif/*_TEST_CASE_$DAT$_MSXML_H_INCLUDED*/