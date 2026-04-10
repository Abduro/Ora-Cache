/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 13:58:23.617, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' MSXML wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$dat$.msxml.h"

using namespace ebo::boo::test::data;

using e_docs = CTstLocator::e_docs;
using e_schemas = CTstLocator::e_schemas;

namespace ebo { namespace boo { namespace test { namespace _impl {
CString __e_doc_to_str (const e_docs _e_doc) {
	_e_doc;
	CString cs_out;
	switch (_e_doc) {
	case e_docs::e_prov_list: cs_out = _T("e_prov_list"); break;
	case e_docs::e_curr_spec: cs_out = _T("e_curr_spec"); break;
	default: cs_out = _T("#__e_undef");
	}
	return  cs_out;
}

CString __e_schemas_to_str (const e_schemas _e_schema) {
	_e_schema;
	CString cs_out;
	switch (_e_schema) {
	case e_schemas::e_prov_list: cs_out = _T("e_prov_list"); break;
	case e_schemas::e_curr_spec: cs_out = _T("e_curr_spec"); break;
	default: cs_out = _T("#__e_undef");
	}
	return  cs_out;
}

	class CLoad_Helper {
	public:
		CLoad_Helper (void) {} CLoad_Helper (const CLoad_Helper&) = delete; CLoad_Helper (CLoad_Helper&&) = delete; ~CLoad_Helper (void) = default;

		CString Get_key (const uint32_t _e_key) {
			_e_key;

			CString cs_pat;
			
			if (false) {}
			else if ((uint32_t)e_docs::e_prov_list == _e_key || (uint32_t)e_docs::e_curr_spec == _e_key) cs_pat = _T("%s\\Data\\Xml");
			else if ((uint32_t)e_schemas::e_prov_list == _e_key || (uint32_t)e_schemas::e_curr_spec == _e_key) cs_pat = _T("%s\\Data\\Xsd");

			CString cs_out;cs_out.Format((_pc_sz) cs_pat, ::Get_reg_router().Root().Path());
			return  cs_out;
		}

		CString Get_name (const uint32_t _e_key) {
			_e_key;
			CString cs_out;
			if (false) {}
			else if ((uint32_t)e_docs::e_prov_list == _e_key || (uint32_t)e_docs::e_curr_spec == _e_key) cs_out = _T("Providers");
			else if ((uint32_t)e_schemas::e_prov_list == _e_key || (uint32_t)e_schemas::e_curr_spec == _e_key) cs_out = _T("Spec");

			return  cs_out;
		}

	private:
		CLoad_Helper& operator = (const CLoad_Helper&) = delete; CLoad_Helper& operator = (CLoad_Helper&&) = delete;
	};


}}}} using namespace ebo::boo::test::_impl;

#pragma region cls::CTstLocator{}

CString CTstLocator::Get_path (const e_docs _e_doc, const bool _b_cls_out) {
	_e_doc; _b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Open((_pc_sz) CLoad_Helper().Get_key((uint32_t)_e_doc)))) {
		_out() += (*this)().Error();
		return CString();
	}
#if (0)
	CString cs_name = CLoad_Helper().Get_name((uint32_t)_e_doc);

	if (cs_name.IsEmpty()) {
		_out() += _T("[error] The xml document type value name cannot be empty"); return CString();
	}
#endif
	CString cs_path;
	cs_path = (*this)().Value().GetString((_pc_sz) CLoad_Helper().Get_name((uint32_t)_e_doc));

	if (cs_path.IsEmpty()) { _out() += (*this)().Error(); }
	else _out() += TString().Format(_T("[impt] result >> doc_type: '%s';\n\t\tpath: %s"), (_pc_sz) __e_doc_to_str(_e_doc), (_pc_sz) cs_path);

	return  cs_path;
}

CString CTstLocator::Get_path (const e_schemas _e_schema, const bool _b_cls_out/* = true*/) {
	_e_schema; _b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Open((_pc_sz) CLoad_Helper().Get_key((uint32_t)_e_schema)))) {
		_out() += (*this)().Error();
		return CString();
	}

	CString cs_path;
	cs_path = (*this)().Value().GetString((_pc_sz) CLoad_Helper().Get_name((uint32_t)_e_schema));

	if (cs_path.IsEmpty()) { _out() += (*this)().Error(); }
	else _out() += TString().Format(_T("[impt] result >> xsd_type: '%s';\n\t\tpath: %s"), (_pc_sz) __e_schemas_to_str(_e_schema), (_pc_sz) cs_path);

	return  cs_path;
}

const
TRegKeyEx& CTstLocator::operator ()(void) const { return this->m_key; }
TRegKeyEx& CTstLocator::operator ()(void)       { return this->m_key; }

#pragma endregion
#pragma region cls::CTstXmlDoc{}

err_code CTstXmlDoc::Load (_pc_sz _p_path) {
	_p_path;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] the document com-object is created;");

	if (__failed((*this)().Load(_p_path))) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += TString().Format(_T("[impt] result: XML file %s is loaded;"), _p_path);

	return (*this)().Error();
}

const
CDocument& CTstXmlDoc::operator ()(void) const { return this->m_doc; }
CDocument& CTstXmlDoc::operator ()(void)       { return this->m_doc; }

#pragma endregion
#pragma region cls::CTstSchema{}

err_code CTstSchema::Load (_pc_sz _p_path) {
	_p_path;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] the schema cache com-object is created;");

	if (__failed((*this)().Load(_p_path))) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += TString().Format(_T("[impt] result: XSD file %s is loaded;"), _p_path);

	return (*this)().Error();
}

const
CSchema& CTstSchema::operator ()(void) const { return this->m_schema; }
CSchema& CTstSchema::operator ()(void)       { return this->m_schema; }

#pragma endregion