/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 16:37:01.437, UTC+4, Batumi, Tuesday;
	Ebo Pack OpenGL tutorials' data providers' uint test adapter interface implementation file;
*/
#include "test_adap_$dat$.msxml.h"

using namespace ebo::boo::test::data;

#pragma region cls::c_xml_locator

void c_xml_locator::Get_providers (void) {

	CTstLocator().Get_path(CTstLocator::e_prov_list); _out()();
}

void c_xml_locator::Get_spec (void) {

	CTstLocator().Get_path(CTstLocator::e_spec); _out()();
}

#pragma endregion