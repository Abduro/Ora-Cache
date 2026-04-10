/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 16:37:01.437, UTC+4, Batumi, Tuesday;
	Ebo Pack OpenGL tutorials' data providers' uint test adapter interface implementation file;
*/
#include "test_adap_$dat$.msxml.h"

using namespace ebo::boo::test::data;

#pragma region cls::c_xml_doc

void c_xml_doc::Load (void) {

	CTstXmlDoc().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_prov_list));
	CTstXmlDoc().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_curr_spec)); _out()();
}

void c_xml_doc::Validate (void) {

	CTstXmlDoc xml_doc;
	CTstSchema xsd_schema;

	if (__failed(xml_doc.Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_docs::e_curr_spec)))) { _out()(); return; }
	if (__failed(xsd_schema.Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_schemas::e_curr_spec)))) { _out()(); return; }

	if (__failed(xml_doc().Validate(xsd_schema()))) { _out() += xml_doc().Error(); }
	else _out() += _T("[impt] result: xml document is validated;");

	_out()();
}

#pragma endregion
#pragma region cls::c_xml_locator

void c_xml_locator::Get_providers (void) {

	CTstLocator().Get_path(CTstLocator::e_docs::e_prov_list); _out()();
}

void c_xml_locator::Get_spec (void) {

	CTstLocator().Get_path(CTstLocator::e_docs::e_curr_spec); _out()();
}

#pragma endregion
#pragma region cls::c_xsd_locator

void c_xsd_locator::Get_providers (void) {

	CTstLocator().Get_path(CTstLocator::e_schemas::e_prov_list); _out()();
}

void c_xsd_locator::Get_spec (void) {

	CTstLocator().Get_path(CTstLocator::e_schemas::e_curr_spec); _out()();
}

#pragma endregion
#pragma region cls::c_xsd_schema{}

void c_xsd_schema::Load (void) {

	CTstSchema().Load((_pc_sz) CTstLocator().Get_path(CTstLocator::e_schemas::e_curr_spec));
	_out()();
}

#pragma endregion