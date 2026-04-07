#ifndef _TEST_CASE_$DAT$_MSXML_H_INCLUDED
#define _TEST_CASE_$DAT$_MSXML_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 13:53:31.133, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' MSXML wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$dat$.defs.h"

namespace ebo { namespace boo { namespace test { namespace data {
	// gets XML file path from the registry;
	class CTstLocator {
	public:
		enum e_docs : uint32_t { // predefined xml document types;
		     e_prov_list, // contains the path to the file of data providers' list;
		     e_spec,      // contains the path to the file of currency specification;
		};
		 CTstLocator (void) = default; CTstLocator (const CTstLocator&) = delete; CTstLocator (CTstLocator&&) = delete;
		~CTstLocator (void) = default;

		CString  Get_path (const e_docs);  // gets the path of given document type; if empty path is returned the error occurs;
		const
		TRegKeyEx& operator ()(void) const;
		TRegKeyEx& operator ()(void) ;

	private:
		CTstLocator& operator = (const CTstLocator&) = delete; CTstLocator& operator = (CTstLocator&&) = delete;
		TRegKeyEx  m_key;
	};

}}}}

#endif/*_TEST_CASE_$DAT$_MSXML_H_INCLUDED*/