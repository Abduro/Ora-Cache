/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-May-2024 at 08:37:09.3642316, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack system SEH common definition interface implementation file;
*/
#include "sys.seh.common.h"

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

CNode:: CNode (void) : m_code(TErrCodes::no_error), m_alias(_T("$none")), m_desc(_T("#empty")) {}
CNode:: CNode (const CNode& _src) : CNode() { *this = _src; }
CNode:: CNode (const errno_l _code, _pc_sz _p_alias, _pc_sz _p_desc) : CNode() { *this >> _p_alias << _code << _p_desc; }
CNode::~CNode (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz CNode::Alias (void) const { return this->m_alias.GetString(); }
bool   CNode::Alias (_pc_sz _p_alias) {
	_p_alias;
	const bool b_changed = !!this->m_alias.Compare(_p_alias);
	if (b_changed)
		this->m_alias = _p_alias;

	return b_changed;
}

errno_l CNode::Code (void) const { return this->m_code; }
bool    CNode::Code (errno_l _code) {
	_code;
	const bool b_changed = this->Code() != _code; if (b_changed) this->m_code = _code; return b_changed;
}

_pc_sz CNode::Desc (void) const { return this->m_desc.GetString(); }
bool   CNode::Desc (_pc_sz _p_desc) {
	_p_desc;
	const bool b_changed = !!this->m_desc.Compare(_p_desc);
	if (b_changed)
		this->m_desc = _p_desc;

	return b_changed;
}

bool CNode::Is (void) const { return !!this->Code(); }
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString   CNode::Print (const e_print e_opt, _pc_sz _p_class) const {

	static _pc_sz p_sz_pat_a = _T("cls::[%s]>>{%s:code=%d(0x%x);desc='%s';valid=%s}");
	static _pc_sz p_sz_pat_r = _T("{%s=%d(0x%x):%s}");

	CString cs_desc = this->Desc();
	if (cs_desc.IsEmpty())
		cs_desc = _T("#empty");

	CString cs_cls; cs_cls = (!!_p_class ? _p_class : (_pc_sz)__CLASS__);
	CString cs_out;

	if (e_print::e_all == e_opt) cs_out.Format(p_sz_pat_a, (_pc_sz)cs_cls,
	                                                       this->Alias(), this->Code(), this->Code(), (_pc_sz)cs_desc, TString().Bool(this->Is()));
	if (e_print::e_req == e_opt) cs_out.Format(p_sz_pat_r, this->Alias(), this->Code(), this->Code(), (_pc_sz)cs_desc);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CNode& CNode::operator = (const CNode& _src) { *this >> _src.Alias() << _src.Code() << _src.Desc(); return *this; }
CNode& CNode::operator >>(_pc_sz _p_alias) { this->Alias(_p_alias); return *this; }
CNode& CNode::operator <<(errno_l _code) { this->Code(_code); return *this; }
CNode& CNode::operator <<(_pc_sz _p_desc) { this->Desc(_p_desc); return *this; }

CNode::operator errno_l (void) const { return this->Code(); }
CNode::operator _pc_sz  (void) const { return this->Alias(); }

/////////////////////////////////////////////////////////////////////////////

CZyme:: CZyme (void) {}
CZyme:: CZyme (const CZyme& _src) : CZyme() { *this = _src; }
CZyme::~CZyme (void) {}

//////////////////////////////////////////////////////////////////////////////

CZyme&  CZyme::operator = (const CZyme& _src) { _src; return *this; }