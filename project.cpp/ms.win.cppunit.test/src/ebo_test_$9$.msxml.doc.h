#ifndef _EBO_TEST_$9$_MSXML_DOC_H_INCLUDED
#define _EBO_TEST_$9$_MSXML_DOC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 06:36:00.171, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib XML document unit test interface declaration file; 
*/
#include "ebo_test_$9$.msxml.h"

namespace ebo { namespace boo { namespace test { namespace xml {

	using TXDoc = shared::xml::ms::CDocument;

	__class (CDocument) {
	public:
		 CDocument (const bool _b_verb = false);
		~CDocument (void) = default;

	public:
		__ctor (_ctor);
		__method (Create);

	private:
		bool    m_b_verb;
		TXDoc   m_x_doc ;
	};

}}}}

#endif/*_EBO_TEST_$9$_MSXML_DOC_H_INCLUDED*/