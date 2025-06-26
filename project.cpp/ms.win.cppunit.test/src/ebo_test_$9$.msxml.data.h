#ifndef _EBO_TEST_$9$_MSXML_DATA_H_INCLUDED
#define _EBO_TEST_$9$_MSXML_DATA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 06:03:15.315, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MSXML wrapper lib data providers' unit test interface declaration file; 
*/
#include "ebo_test_$9$.msxml.h"

namespace ebo { namespace boo { namespace test { namespace xml {

	using TLocator = shared::xml::ms::ntfs::CLocator;
	using TFileLoader = shared::xml::ms::ntfs::CProvider;

	__class (CFileData) {
	public:
		 CFileData (const bool _b_verb = false);
		~CFileData (void) = default;

	public:
		__method (Load); // attempts to load an XML file from the current directory where the executable file is located;

	private:
		bool m_b_verb;
		TFileLoader m_loader;
	};

	__class (CLocator) {
	public:
		 CLocator (const bool _b_verb = false);
		~CLocator (void) = default;

	public:
		__ctor (_ctor);
		__method (Refresh);

		const
		TLocator& GetObject (void) const;

	private:
		bool m_b_verb;
		TLocator m_locator;
	};

}}}}

#endif/*_EBO_TEST_$9$_MSXML_DATA_H_INCLUDED*/