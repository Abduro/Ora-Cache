/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jun-2025 at 00:14:25.583, UTC+4, Batumi, Wednesday;
	This is Ebo Pack MS XML v6 wrapper include header(s) definition file;
*/
#include "msxml.defs.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace xml { namespace ms { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

/////////////////////////////////////////////////////////////////////////////

CServiceId:: CServiceId (void) : m_cls_id{0}, m_prog_id(_T("#not_set")) {}
CServiceId:: CServiceId (const CServiceId& _src) : CServiceId() { *this = _src; }
CServiceId:: CServiceId (CServiceId&& _victim) : CServiceId() { *this = _victim; }
CServiceId:: CServiceId (const GUID& _cls_id, _pc_sz _p_prog_id) : CServiceId() { *this << _cls_id << _p_prog_id; }
CServiceId::~CServiceId (void) {}

/////////////////////////////////////////////////////////////////////////////
const
GUID&  CServiceId::ClsId (void) const { return this->m_cls_id; }
GUID&  CServiceId::ClsId (void)       { return this->m_cls_id; }

#if defined(_DEBUG)
CString CServiceId::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("csl::[%s::%s] >> {cls_id=%s;prog_id=%s}");
	static _pc_sz pc_sz_pat_n = _T("csl::[%s] >> {cls_id=%s;prog_id=%s}");
	static _pc_sz pc_sz_pat_r = _T("cls_id=%s;prog_id=%s");

	CString cs_cls_id = TStringEx().Guid(this->ClsId());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_cls_id, this->ProgId()); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_cls_id, this->ProgId()); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_cls_id, this->ProgId()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

_pc_sz CServiceId::ProgId (void) const { return this->m_prog_id.GetString(); }
void   CServiceId::ProgId (_pc_sz _prog_id) {
	this->m_prog_id = _prog_id;
}

/////////////////////////////////////////////////////////////////////////////

CServiceId& CServiceId::operator = (const CServiceId& _src) { *this << _src.ClsId() << _src.ProgId(); return *this; }
CServiceId& CServiceId::operator = (CServiceId&& _victim) { *this = (const CServiceId&)_victim; return *this; }

CServiceId& CServiceId::operator <<(const GUID& _cls_id) { this->ClsId() = _cls_id; return *this; }
CServiceId& CServiceId::operator <<(_pc_sz _p_prog_id) { this->ProgId(_p_prog_id); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSvc_Ids:: CSvc_Ids (void) {
#if defined(_DEBUG)
	bool b_break = false;

	b_break = !b_break;

	if (b_break) {
		b_break = !b_break;
	}
#endif
	try {
#if defined(CLSID_DOMDocument60) || (true != false)
		this->m_ids.push_back(CServiceId(CLSID_DOMDocument60, _T("MSXML2.DOMDocument.6.0")));
#endif
#if defined(CLSID_DOMDocument50)
		this->m_ids.push_back(CServiceId(CLSID_DOMDocument50, _T("MSXML2.DOMDocument.5.0")));
#endif
#if defined(CLSID_DOMDocument40)
		this->m_ids.push_back(CServiceId(CLSID_DOMDocument40, _T("MSXML2.DOMDocument.4.0")));
#endif
#if defined(CLSID_DOMDocument30) || (true != false)
		this->m_ids.push_back(CServiceId(CLSID_DOMDocument30, _T("MSXML2.DOMDocument.3.0")));
#endif
#if defined(CLSID_DOMDocument26) || (true != false)
		this->m_ids.push_back(CServiceId(CLSID_DOMDocument26, _T("MSXML2.DOMDocument.2.6")));
#endif
	} catch (const ::std::bad_alloc&) {}

}
CSvc_Ids::~CSvc_Ids (void) {}

/////////////////////////////////////////////////////////////////////////////

const TRawSvcIds& CSvc_Ids::Raw (void) const { return this->m_ids; }

#if defined(_DEBUG)
CString  CSvc_Ids::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_ids;

	for (uint32_t i_ = 0; i_ < this->Raw().size(); i_++) {
		const CServiceId& svc_id = this->Raw().at(i_);
		cs_ids += _p_sfx;
		cs_ids += _p_pfx;
		cs_ids += svc_id.Print(e_print::e_req);
	}
	if (cs_ids.IsEmpty()) {
		cs_ids.Format(_T("%s%s#empty"), _p_sfx, _p_pfx);
	}
	cs_ids += _p_sfx;
	cs_ids += _p_pfx;
		
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_ids); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_ids); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_ids); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif