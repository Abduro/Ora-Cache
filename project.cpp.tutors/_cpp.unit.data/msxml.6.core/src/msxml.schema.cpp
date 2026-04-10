/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2026 at 03:30:16.347, UTC+4, Batumi, Friday;
	This is Ebo Pack data provider XML schema cache wrapper interface implementation file;
*/
#include "msxml.schema.h"
#include "msxml.doc.h"    // it is required for parsing syntax of the xsd document because there's possible incorrect xml structure;

using namespace shared::xml::ms;

#pragma region cls::CSchema{}

CSchema::CSchema (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }

err_code CSchema::Create (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->m_pSchema)
		return this->m_error << (err_code) TErrCodes::eObject::eExists = _T("Schema cache object is already created;");

	const CSchema_Ids schema_ids;

	for (uint32_t i_ = 0; i_ < schema_ids.Raw().size(); i_++) {

		const CServiceId& svc_id = schema_ids.Raw().at(i_);

		this->m_error << this->m_pSchema.CoCreateInstance(svc_id.ClsId());
		if ( !m_error ) {

			this->Svc_Id() = svc_id;
			break;
		}
	}

	return this->Error();
}

err_code CSchema::Destroy (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == (*this)())
		return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Schema cache object is not created;");

	(*this)() = nullptr;
	this->m_error << __e_not_inited;

	return __s_ok; // destroying operation is completed successfully;
}

TError&  CSchema::Error (void) const { return this->m_error; }
const bool  CSchema::Is  (void) const { return this->Ptr() != nullptr; }

err_code CSchema::Load (_pc_sz _xsd_file_path) {
	_xsd_file_path;
	this->m_error << __METHOD__ <<__s_ok;

	if (nullptr == _xsd_file_path || 0 == ::_tcslen(_xsd_file_path))
		return this->m_error << __e_inv_arg = _T("XSD file path is invalid");

	if (false == this->Is())
		return this->m_error << __e_not_inited = _T("Interface object is not created");

	// just for checking the syntax of xsd document, because XSD is still be an XML document;
	CDocument doc;
	if (__failed(doc.Create()))
		return this->m_error = doc.Error();
	if (__failed(doc.Load(_xsd_file_path)))
		return this->m_error = doc.Error();

	_bstr_t p_ns(_T(""));

	::ATL::CComVariant var_path(_xsd_file_path);

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms766451(v=vs.85) ;
	this->m_error << this->Ptr()->add(p_ns, /*_variant_t(_xsd_file_path)*/var_path);

	return this->Error();
}
const
TSchemaPtr&  CSchema::Ptr (void) const { return this->m_pSchema; }
TSchemaPtr&  CSchema::Ptr (void)       { return this->m_pSchema; }
const
CSvc_Id&     CSchema::Svc_Id (void) const { return this->m_svc_id; }
CSvc_Id&     CSchema::Svc_Id (void)       { return this->m_svc_id; }
const
TSchemaPtr&  CSchema::operator ()(void) const { return this->Ptr(); }
TSchemaPtr&  CSchema::operator ()(void)       { return this->Ptr(); }

#pragma endregion