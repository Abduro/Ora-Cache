/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 13:58:23.617, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' MSXML wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$dat$.msxml.h"

using namespace ebo::boo::test::data;

#pragma region cls::CTstLocator{}

using e_docs = CTstLocator::e_docs;
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

CString CTstLocator::Get_path (const e_docs _e_doc, const bool _b_cls_out) {
	_e_doc; _b_cls_out;
	if (_b_cls_out)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	CString cs_key; cs_key.Format(_T("%s\\Data\\Xml"), ::Get_reg_router().Root().Path());

	if (__failed((*this)().Open((_pc_sz) cs_key))) {
		_out() += (*this)().Error();
		return CString();
	}
	CString cs_name; // default;
	if (e_docs::e_prov_list == _e_doc) cs_name = _T("Providers");
	if (e_docs::e_curr_spec == _e_doc) cs_name = _T("Spec");

	if (cs_name.IsEmpty()) {
		_out() += _T("[error] The xml document type value name cannot be empty"); return CString();
	}

	CString cs_path;
	cs_path = (*this)().Value().GetString((_pc_sz) cs_name);

	if (cs_path.IsEmpty()) { _out() += (*this)().Error(); }
	else _out() += TString().Format(_T("[impt] result >> doc_type: '%s';\n\t\tpath: %s"), (_pc_sz) __e_doc_to_str(_e_doc), (_pc_sz) cs_path);

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