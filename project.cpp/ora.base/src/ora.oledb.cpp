/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 20:31:50.4961029, UTC+4, Batumi, Sunday;
	This is Ebo Pack Oracle database provider interface implementation file;
*/
#include "ora.oledb.h"

using namespace ora::base::oledb;

/////////////////////////////////////////////////////////////////////////////

CProvider:: CProvider (void) : m_enum(false), m_type(0) {}
CProvider:: CProvider (_pc_sz _prog_id, _pc_sz _p_desc) : CProvider() {
	this->ProgId().Set(_prog_id);
	this->Desc(_p_desc);
	this->ClsId().Set(CClsId::Get(_prog_id));
}
CProvider:: CProvider (const CProvider& _src) : CProvider() { *this = _src; }
CProvider:: CProvider (CProvider&& _victim) : CProvider() { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////
const
CClsId& CProvider::ClsId (void) const { return this->m_cls_id; }
CClsId& CProvider::ClsId (void)       { return this->m_cls_id; }

_pc_sz  CProvider::Desc (void) const { return (_pc_sz) this->m_desc; }
bool    CProvider::Desc (_pc_sz _desc) {
	_desc;
	const bool b_changed = !!this->m_desc.Compare(_desc);
	if (b_changed)
		this->m_desc = _desc;

	return b_changed;
}

bool   CProvider::Is_valid (void) const { return this->ClsId().Is_valid() && this->ProgId().Is_valid();  }

const
CProgId& CProvider::ProgId (void) const { return this->m_prog_id; }
CProgId& CProvider::ProgId (void)       { return this->m_prog_id; }

ushort CProvider::Type (void) const { return this->m_type; }
bool   CProvider::Type (const ushort _value) {
	_value;
	const bool b_changed = (_value != this->Type());
	if (b_changed)
		this->m_type = _value;

	return b_changed;
}

#if defined(DEBUG)
CString CProvider::Print (const e_print e_opt) const {
	e_opt;

	static _pc_sz pc_sz_a = _T("cls::[%s.%s]>>{prog_id=%s;cls_id=%s;desc=%s;valid=%s}");
	static _pc_sz pc_sz_n = _T("cls::[%s]>>{prog_id=%s;cls_id=%s;desc=%s;valid=%s}");
	static _pc_sz pc_sz_r = _T("{prog_id=%s;cls_id=%s;desc=%s}");

	CString cs_prog_id(this->ProgId()); cs_prog_id.Trim(); if (cs_prog_id.IsEmpty()) cs_prog_id = _T("#not_set");
	CString cs_desc(this->Desc()); cs_desc.Trim(); if (cs_desc.IsEmpty()) cs_desc = _T("#no_desc");
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == e_opt) { 
		cs_out.Format(pc_sz_a,
			(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_prog_id, (_pc_sz)this->ClsId().Get(), (_pc_sz)cs_desc, (_pc_sz)cs_valid
		);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_n, (_pc_sz)__CLASS__, (_pc_sz)cs_prog_id, (_pc_sz)this->ClsId().Get(), (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == e_opt) {
		cs_out.Format(pc_sz_r, (_pc_sz)cs_prog_id, (_pc_sz)this->ClsId().Get(), (_pc_sz)cs_desc);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s.%s].%s(#inv_arg=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CProvider& CProvider::operator = (const CProvider& _src) {
	*this << _src.ProgId() << _src.ClsId() << _src.Desc() << _src.Type(); return *this;
}
CProvider& CProvider::operator = (CProvider&& _victim) {
	// this version of the implementation does not care about moving data from one place to another;
	*this = _victim;
	return *this;
}
CProvider& CProvider::operator <<(_pc_sz _desc) { this->Desc(_desc); return *this; }
CProvider& CProvider::operator <<(const CClsId& _cls_id) { this->ClsId() = _cls_id; return *this; }
CProvider& CProvider::operator <<(const CProgId& _prog_id) { this->ProgId() = _prog_id; return *this; }

CProvider& CProvider::operator <<(const ushort _u_type) { this->Type(_u_type); return *this; }

/////////////////////////////////////////////////////////////////////////////

CProvider_enum:: CProvider_enum (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProvider_enum:: CProvider_enum (const CProvider_enum& _src) : CProvider_enum() { *this = _src;  }

/////////////////////////////////////////////////////////////////////////////

COraProvider::COraProvider (void) : TBase() {
	// this is the pre-defined set of properties values for Oracle OLEDB provider;
	TBase::ClsId().Set(TStringEx(_T("{3F63C36E-51A3-11D2-BB7D-00C04FA30080}")).Guid());
	TBase::ProgId().Set(_T("OraOLEDB.Oracle"));
	TBase::Desc(_T("Oracle Provider for OLE DB"));
	TBase::Type(CProv_Types::e_regular);
}

/////////////////////////////////////////////////////////////////////////////

COraProvider& COraProvider::operator = (const COraProvider& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

TError&  CProvider_enum::Error (void) const { return this->m_error; }
const
TProvs&  CProvider_enum::Get (void) const { return this->m_provs; }
err_code CProvider_enum::Set (void) {

	this->m_error << __METHOD__ << __s_ok;

	CEnumerator providers;

	this->m_error = providers.Open();
	if (this->Error())
		return this->Error();

	if (m_provs.empty() == false)
		m_provs.clear();

	while (__is_okay(providers.MoveNext())) {
		if (CProv_Types::e_regular != providers.m_nType) {
			continue;
		}

		CProvider prov_(providers.m_szName, providers.m_szDescription); prov_.Type(providers.m_nType);

		m_provs.push_back(prov_);
	}

	return this->Error();
}

#if defined(_DEBUG)
CString CProvider_enum::Print (_pc_sz _pfx, _pc_sz _sfx) const {
	_pfx; _sfx;

	static _pc_sz p_sz_pat = _T("cls::[%s::%s] {%s%s%s}");

	CString cs_out;
	CString cs_provs;

	for (TProvs::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {

		cs_provs += _pfx;
		cs_provs += it_->Print(CProvider::e_req);
		cs_provs += _sfx;

	}

	if (cs_provs.IsEmpty()) {
		cs_provs += _pfx;
		cs_provs += _T("#empty");
		cs_provs += _sfx;
	}
	cs_out.Format(p_sz_pat, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _sfx, (_pc_sz)cs_provs, _pfx);

	return  cs_out;
}
#endif

bool CProvider_enum::Registered (const _guid& _cls_id) const {
	_cls_id;
	bool b_registered = false;

	for (size_t i_ = 0; i_ < this->m_provs.size(); i_++) {

		const CProvider& prov_ = this->m_provs.at(i_);
		b_registered = _cls_id == prov_.ClsId().Raw();

		if (b_registered)
			break;
	}

	return b_registered;
}

/////////////////////////////////////////////////////////////////////////////

CProvider_enum&  CProvider_enum::operator = (const CProvider_enum& _src) { this->m_error = _src.m_error; return *this; }