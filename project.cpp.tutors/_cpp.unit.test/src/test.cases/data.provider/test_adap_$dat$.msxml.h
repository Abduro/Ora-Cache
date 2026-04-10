#ifndef _TEST_ADAP_$DAT$_MSXML_H_INCLUDED
#define _TEST_ADAP_$DAT$_MSXML_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 16:32:11.445, UTC+4, Batumi, Tuesday;
	Ebo Pack OpenGL tutorials' data providers' uint test adapter interface declaration file;
*/
#include "test_case_$dat$.msxml.h"

namespace ebo { namespace boo { namespace test { namespace data {

	__class (c_xml_doc) {
	public:
		 c_xml_doc (void) = default; c_xml_doc (const c_xml_doc&) = delete; c_xml_doc (c_xml_doc&&) = delete;
		~c_xml_doc (void) = default;

		__method (Load);
		__method (Validate);

	private:
		c_xml_doc& operator = (const c_xml_doc&) = delete; c_xml_doc& operator = (c_xml_doc&&) = delete;
	};

	__class (c_xml_locator) {
	public:
		 c_xml_locator (void) = default; c_xml_locator (const c_xml_locator&) = delete; c_xml_locator (c_xml_locator&&) = delete;
		~c_xml_locator (void) = default;

		__method (Get_logo);
		__method (Get_providers);
		__method (Get_spec);

	private:
		c_xml_locator& operator = (const c_xml_locator&) = delete; c_xml_locator& operator = (c_xml_locator&&) = delete;
	};

	__class (c_xsd_locator) {
	public:
		 c_xsd_locator (void) = default; c_xsd_locator (const c_xsd_locator&) = delete; c_xsd_locator (c_xsd_locator&&) = delete;
		~c_xsd_locator (void) = default;

		__method (Get_logo);
		__method (Get_providers);
		__method (Get_spec);

	private:
		c_xsd_locator& operator = (const c_xsd_locator&) = delete; c_xsd_locator& operator = (c_xsd_locator&&) = delete;
	};

	__class (c_xsd_schema) {
	public:
		 c_xsd_schema (void) = default; c_xsd_schema (const c_xsd_schema&) = delete; c_xsd_schema (c_xsd_schema&&) = delete;
		~c_xsd_schema (void) = default;

		__method (Load);

	private:
		c_xsd_schema& operator = (const c_xsd_schema&) = delete; c_xsd_schema& operator = (c_xsd_schema&&) = delete;
	};

}}}}

#endif/*_TEST_ADAP_$DAT$_MSXML_H_INCLUDED*/