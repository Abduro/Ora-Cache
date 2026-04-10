/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 16:37:01.437, UTC+4, Batumi, Tuesday;
	Ebo Pack OpenGL tutorials' data providers' uint test adapter interface implementation file;
*/
#include "test_adap_$dat$.msxml.h"

using namespace ebo::boo::test::data;

using e_docs = CTstLocator::e_docs;
using e_schemas = CTstLocator::e_schemas;

namespace ebo { namespace boo { namespace test { namespace _impl {

	class CValidator {
	public:
		CValidator (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
		CValidator (const CValidator&) = delete; CValidator (CValidator&&) = delete; ~CValidator (void) = default;

		err_code Do_it (const uint32_t _u_doc_type) { // the input argument value can be either an element of e_docs or e_schemas;
			_u_doc_type;
			this->m_error <<__METHOD__<<__s_ok;

			CTstXmlDoc xml_doc;
			CTstSchema xsd_schema;

			if (__failed(xml_doc.Load((_pc_sz) CTstLocator().Get_path(this->_uint_to_xml(_u_doc_type))))) { return this->m_error = xml_doc().Error(); }
			if (__failed(xsd_schema.Load((_pc_sz) CTstLocator().Get_path(this->_uint_to_xsd(_u_doc_type))))) { return this->m_error = xsd_schema().Error(); }

			_out() += _T("Validating xml document...");
			if (__failed(xml_doc().Validate(xsd_schema()))) { _out() += xml_doc().Error(); }
			else _out() += _T("[impt] result: xml document is validated;");

			return this->Error();
		}

		TError& Error (void) const { return this->m_error; }

	private:
		CValidator& operator = (const CValidator&) = delete; CValidator& operator = (CValidator&&) = delete;
		CError  m_error;

		e_docs _uint_to_xml (const uint32_t _u_value) {
			_u_value;
			return (uint32_t) e_docs::e_prov_list == _u_value ? e_docs::e_prov_list :
			       (uint32_t) e_docs::e_prov_logo == _u_value ? e_docs::e_prov_logo : e_docs::e_curr_spec;
		}
		e_schemas _uint_to_xsd (const uint32_t _u_value) {
			_u_value;
			return (uint32_t) e_schemas::e_prov_list == _u_value ? e_schemas::e_prov_list :
			       (uint32_t) e_schemas::e_prov_logo == _u_value ? e_schemas::e_prov_logo : e_schemas::e_curr_spec;
		}
	};

}}}} using namespace ebo::boo::test::_impl;

#pragma region cls::c_xml_doc

void c_xml_doc::Load (void) {

	CTstXmlDoc().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_prov_list));
	CTstXmlDoc().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_prov_logo));
	CTstXmlDoc().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_curr_spec)); _out()();
}

void c_xml_doc::Validate (void) {

	CValidator().Do_it((uint32_t) e_docs::e_prov_list);
	CValidator().Do_it((uint32_t) e_docs::e_prov_logo);
	CValidator().Do_it((uint32_t) e_docs::e_curr_spec);

	_out()();
}

#pragma endregion
#pragma region cls::c_xml_locator

void c_xml_locator::Get_logo(void) {

	CTstLocator().Get_path(CTstLocator::e_docs::e_prov_logo); _out()();
}

void c_xml_locator::Get_providers (void) {

	CTstLocator().Get_path(CTstLocator::e_docs::e_prov_list); _out()();
}

void c_xml_locator::Get_spec (void) {

	CTstLocator().Get_path(CTstLocator::e_docs::e_curr_spec); _out()();
}

#pragma endregion
#pragma region cls::c_xsd_locator

void c_xsd_locator::Get_logo(void) {

	CTstLocator().Get_path(CTstLocator::e_schemas::e_prov_logo); _out()();
}

void c_xsd_locator::Get_providers (void) {

	CTstLocator().Get_path(CTstLocator::e_schemas::e_prov_list); _out()();
}

void c_xsd_locator::Get_spec (void) {

	CTstLocator().Get_path(CTstLocator::e_schemas::e_curr_spec); _out()();
}

#pragma endregion
#pragma region cls::c_xsd_schema{}

void c_xsd_schema::Load (void) {

	CTstSchema().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_schemas::e_prov_list));
	CTstSchema().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_schemas::e_prov_logo));
	CTstSchema().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_schemas::e_curr_spec));
	_out()();
}

#pragma endregion