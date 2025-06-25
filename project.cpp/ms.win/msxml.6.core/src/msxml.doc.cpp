/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2024 at 16:54:06.0964777, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared MS XML Document interface implementation file;
*/
#include "msxml.doc.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

CDocument:: CDocument (void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDocument:: CDocument (const CDocument& _doc) : CDocument() { *this = _doc; }
CDocument::~CDocument (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code    CDocument::Create (void) {
	m_error() << __METHOD__ << S_OK;

	if (this->m_pDoc)
		return (m_error() << (err_code) TErrCodes::eObject::eExists);

	const CSvc_Ids svc_ids;

	for (uint32_t i_ = 0; i_ < svc_ids.Raw().size(); i_++) {

		const CServiceId& svc_id = svc_ids.Raw().at(i_);

		this->m_error() << this->m_pDoc.CoCreateInstance(svc_id.ClsId());
		if ( !m_error ) {

			this->Svc_Id() = svc_id;
			break;
		}
	}
	if (!this->Error()) {
		err_code n_result = this->m_pDoc->get_parseError(&this->m_error.Ptr());
		if (__failed(n_result)) { // ToDo: rewriting the error of parsing the xml document requires making review of such approach;
			this->m_error() << n_result;
		}
	}

	return this->Error();
}

TPrs_Err&   CDocument::Error (void) const { return this->m_error; }
const bool  CDocument::Is  (void) const { return this->Ptr() != nullptr; }

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
CSvc_Id&    CDocument::Svc_Id (void) const { return this->m_svc_id; }
CSvc_Id&    CDocument::Svc_Id (void)       { return this->m_svc_id; }

/////////////////////////////////////////////////////////////////////////////

CDocument&  CDocument::operator = (const CDocument& _doc) { *this << _doc.Ptr() << _doc.Svc_Id(); return *this; }
CDocument&  CDocument::operator <<(const TDocPtr& _p_doc) {  this->Ptr() = _p_doc; return *this; }

CDocument&  CDocument::operator <<(const CSvc_Id& _svc_id) { this->Svc_Id() = _svc_id; return *this; }

/////////////////////////////////////////////////////////////////////////////