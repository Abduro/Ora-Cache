/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2024 at 16:54:06.0964777, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared MS XML Document interface implementation file;
*/
#include "msxml.doc.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CDocument:: CDocument (void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDocument:: CDocument (const CDocument& _doc) : CDocument() { *this = _doc; }
CDocument::~CDocument (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code    CDocument::Create(const bool _b_norm) {
	_b_norm;
	this->m_error() << __METHOD__ << __s_ok;

	if (this->m_pDoc)
		return this->m_error() << (err_code) TErrCodes::eObject::eExists = _T("Document object is already created;");

	const CSvc_Ids svc_ids;

	for (uint32_t i_ = 0; i_ < svc_ids.Raw().size(); i_++) {

		const CServiceId& svc_id = svc_ids.Raw().at(i_);

		this->m_error() << this->m_pDoc.CoCreateInstance(svc_id.ClsId());
		if ( !m_error ) {

			this->Svc_Id() = svc_id;
			break;
		}
	}

	if (this->Is() == false) // the interface instance is not created;
		return this->Error();

	this->m_error() << (err_code) (*this)()->put_preserveWhiteSpace(
		(_b_norm ? __vt_false : __vt_true)
	);

	return this->Error();
}

err_code    CDocument::Close (void) {

	this->m_error() << __METHOD__ << __s_ok;

	if (nullptr == (*this)())
		return this->m_error() << (err_code) TErrCodes::eExecute::eState = _T("Document object is not created;");

	(*this)() = nullptr;
	this->m_error() << __e_not_inited;

	return __s_ok;
}

TPrs_Err&   CDocument::Error (void) const { return this->m_error; }
const bool  CDocument::Is  (void) const { return this->Ptr() != nullptr; }

err_code    CDocument::Load(_pc_sz _xml_file_path) {
	_xml_file_path;
	this->m_error() << __METHOD__ <<__s_ok;

	if (nullptr == _xml_file_path || 0 == ::_tcslen(_xml_file_path))
		return this->m_error() << __e_inv_arg;

	if (false == this->Is())
		return this->m_error() << __e_not_inited;

	_variant_t v_result_3((short)0, VT_I2);
	
	this->m_error() << this->Ptr()->load(_variant_t(_xml_file_path), &v_result_3.iVal); // *load*, *NOT* loadXML!
	if (this->m_error())
		return this->Error();       // no error parsing yet, just return the error of loading;

	if (v_result_3.iVal == false) { // indicates the error occurred during the xml document parsing;

		err_code n_result = (*this)()->get_parseError(&this->m_error.Ptr());
		if (__failed(n_result)) {
			return this->m_error() << n_result;
		} else { this->m_error.Refresh(); }
	}
	// it looks like parsing data error should not be inherited from generic error object due to the simple thing:
	// (a) parsing XML data error has no common with
	// (b) handling the COM interface errors;
	// the one of the possible solutions - to separate these error types between each other;
	if (this->Error().Is())         // calling this property Is() that is overloaded would look like more reliable but it is not;
		return this->Error();       // it is expected the error object contains information of what goes wrong during the parsing XML data;

	CRoot root_nd;
	err_code n_result = (*this)()->get_documentElement(&root_nd());

	if (__failed(n_result))
		return this->m_error() << n_result;

	n_result = root_nd.Name(this->Root().Name_Ref());
	if (__failed(n_result))
		return this->m_error() << n_result;

	n_result = root_nd.Atts(this->Root().Attributes());
	if (__failed(n_result))
		return this->m_error() << n_result;

	CNode_Enum* p_kids = const_cast<CNode_Enum*>(this->Root().Children());
	if (nullptr != p_kids) {
		n_result = root_nd.Kids(*p_kids);
		if (__failed(n_result))
			this->m_error() << n_result;
	}
	return this->Error();
}

#if defined(_DEBUG)
CString     CDocument::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s;created=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s;created=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s;created=%s}");

	CString cs_created = TStringEx().Bool(this->Is());
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) this->Svc_Id().Print(e_print::e_req), (_pc_sz) cs_created);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) this->Svc_Id().Print(e_print::e_req), (_pc_sz) cs_created);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r,
		(_pc_sz) this->Svc_Id().Print(e_print::e_req), (_pc_sz) cs_created);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TDocPtr&    CDocument::Ptr (void) const { return this->m_pDoc; }
TDocPtr&    CDocument::Ptr (void)       { return this->m_pDoc; }

const
CNode&      CDocument::Root  (void) const { return this->m_root; }
CNode&      CDocument::Root  (void)       { return this->m_root; }

const
CSvc_Id&    CDocument::Svc_Id (void) const { return this->m_svc_id; }
CSvc_Id&    CDocument::Svc_Id (void)       { return this->m_svc_id; }

/////////////////////////////////////////////////////////////////////////////

CDocument&  CDocument::operator = (const CDocument& _doc) { *this << _doc.Ptr() << _doc.Svc_Id(); return *this; }
CDocument&  CDocument::operator <<(const TDocPtr& _p_doc) {  this->Ptr() = _p_doc; return *this; }

CDocument&  CDocument::operator <<(const CSvc_Id& _svc_id) { this->Svc_Id() = _svc_id; return *this; }

/////////////////////////////////////////////////////////////////////////////
const
TDocPtr&    CDocument::operator ()(void) const { return this->Ptr(); }
TDocPtr&    CDocument::operator ()(void)       { return this->Ptr(); }