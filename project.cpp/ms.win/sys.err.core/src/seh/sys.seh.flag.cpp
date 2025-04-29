/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-May-2024 at 15:37:40.6041017, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack system SEH EXCEPTION_RECORD flag enumeration interface implementation file;
*/
#include "sys.seh.flag.h"

using namespace shared::sys_core::seh;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace seh { namespace _impl {

	struct _raw_flags : public _raw_data {
		bool _is_sys;
	};

	_raw_flags raw_flags[] = {
		{TExcValues::e_no_way  , _T("#NOWAY")  , _T("Noncontinuable exception.")        , false },
		{TExcValues::e_unwind  , _T("#UNWIND") , _T("Unwind is in progress.")           , true  },
		{TExcValues::e_go_exit , _T("#UNW_EXT"), _T("Exit unwind is in progress.")      , true  },
		{TExcValues::e_no_stack, _T("#INV_STK"), _T("Stack out of limits or unaligned."), true  },
		{TExcValues::e_nested  , _T("#NST_CAL"), _T("Nested exception handler call.")   , true  },
		{TExcValues::e_target  , _T("#UNW_TAG"), _T("Target unwind in progress.")       , true  },
		{TExcValues::e_collide , _T("#UNW_CLD"), _T("Collided exception handler call.") , true  },
	};

}}}}
using namespace shared::sys_core::seh::_impl;
/////////////////////////////////////////////////////////////////////////////

CFlag:: CFlag (void) : TBase(), m_is_sys(true) {}
CFlag:: CFlag (const CFlag& _ref) : CFlag() { *this = _ref; }
CFlag:: CFlag (const errno_l _code, _pc_sz _alias, _pc_sz _desc, bool _is_sys) : TBase(_code, _alias, _desc), m_is_sys(_is_sys) {}
CFlag::~CFlag (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CFlag::Is (void) const { return (TBase::Is() && !TBase::m_alias.IsEmpty()); }

bool CFlag::Is_sys (void) const { return this->m_is_sys && !!TBase::Code(); }
bool CFlag::Is_sys (bool _is_set) { const bool b_changed = _is_set != this->Is_sys(); this->m_is_sys = _is_set; return b_changed; }

#if defined(_DEBUG)
CString     CFlag::Print (const e_print e_opt) const {

	static _pc_sz pc_sz_pat = _T("%s;_is_sys=%s;");
	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz)TBase::Print (e_opt, (_pc_sz)__CLASS__), TString().Bool(this->Is_sys()));
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CFlag&  CFlag::operator = (const CFlag& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Is_sys(); return *this; }
CFlag&  CFlag::operator <<(const bool _is_sys) { this->Is_sys(_is_sys); return *this; }

/////////////////////////////////////////////////////////////////////////////

const bool CFlag::Has (const uint32_t _raw, const CFlag::_values _to_check_for) {
	return !!(_raw & _to_check_for);
}

/////////////////////////////////////////////////////////////////////////////

CFlag_Fake:: CFlag_Fake (void) : TBase() { this->Set(); }
CFlag_Fake::~CFlag_Fake (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CFlag_Fake::Has (errno_l _value) const { return (this->Get().end() != this->Get().find(_value)); }
const
CFlag& CFlag_Fake::Find (errno_l _value) const {
	_value;
	TSafe_Flag();
	TFlags::const_iterator it_found = this->Get().find(_value);

	if (this->Get().end() == it_found) {
		static CFlag fake_;

		fake_ >> _T("#FAKE") << TString().Format(_T("Fake exception flag<%d>"), _value) << _value;

		return fake_;
	}
	else
		return it_found->second;
}
const
TFlags&  CFlag_Fake::Get (void) const { return this->m_flags; }
err_code CFlag_Fake::Set (void) {

	err_code n_result = TErrCodes::no_error;

	if (this->m_flags.empty() == false)
		this->m_flags.clear();

	for (uint16_t i_ = 0; i_ < _countof(raw_flags); i_++)
		this->m_flags.insert(
			::std::make_pair(raw_flags[i_]._code,  CFlag(raw_flags[i_]._code, raw_flags[i_]._p_alias, raw_flags[i_]._p_desc, raw_flags[i_]._is_sys)
			));

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CFlag_Fake::Print (_pc_sz _pfx, _pc_sz _sfx) const {
	_pfx;_sfx;

	static _pc_sz p_sz_pat = _T("cls::[%s]%s%s");

	CString cs_out;
	CString cs_codes;

	for (TFlags::const_iterator it_ = this->Get().begin(); it_ != this->Get().end(); ++it_) {

		cs_codes += _pfx;
		cs_codes += it_->second.Print(e_print::e_req);
		cs_codes += _sfx;

	}

	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, _sfx, (_pc_sz)cs_codes);

	return  cs_out;
} 
#endif

/////////////////////////////////////////////////////////////////////////////

CFlag_Fake& CFlag_Fake::Ref (void) {

	static CFlag_Fake the_fake;
	return the_fake;
}

/////////////////////////////////////////////////////////////////////////////

CFlag_Unw:: CFlag_Unw (void) : TBase() {}
CFlag_Unw:: CFlag_Unw (const CFlag_Unw& _src) : CFlag_Unw() { *this = _src; }
CFlag_Unw:: CFlag_Unw (const errno_l _code, _pc_sz _p_alias, _pc_sz _p_desc) : TBase(_code, _p_alias, _p_desc) {}
CFlag_Unw::~CFlag_Unw (void) {}

/////////////////////////////////////////////////////////////////////////////

CFlag_Unw&  CFlag_Unw::operator = (const CFlag_Unw& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CFlag_Unw_Collection:: CFlag_Unw_Collection (void) : TBase() {}
CFlag_Unw_Collection:: CFlag_Unw_Collection (const CFlag_Unw_Collection& _src) : CFlag_Unw_Collection() { *this = _src; }
CFlag_Unw_Collection::~CFlag_Unw_Collection (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TRawFlags& CFlag_Unw_Collection::Get (void) const { return this->m_flags; }
err_code   CFlag_Unw_Collection::Set (const TPointers* const _ptrs) {
	_ptrs;
	err_code n_result = TErrCodes::no_error;

	if (!CAccepted()(_ptrs))
		return n_result = E_POINTER;

	return n_result = this->Set(_ptrs->ExceptionRecord);
}

err_code   CFlag_Unw_Collection::Set (const TRecord* const _p_rec) {
	_p_rec;
	err_code n_result = TErrCodes::no_error;

	if (!CAccepted()(_p_rec))
		return n_result = E_POINTER;

	uint32_t dw_flags = _p_rec->ExceptionFlags;

	if (!dw_flags) {
		return n_result;
	}

	return n_result = this->Set(dw_flags);
}

err_code   CFlag_Unw_Collection::Set (const uint32_t _raw_flags) {
	_raw_flags;
	err_code n_result = TErrCodes::no_error;

	if (this->m_flags.empty() == false)
		this->m_flags.clear();

	uint32_t dw_flags =_raw_flags;

	if (!dw_flags) {
		return n_result;
	}

	if (TExcValues::e_collide  & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_collide )); dw_flags &=~ TExcValues::e_collide ; }
	if (TExcValues::e_go_exit  & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_go_exit )); dw_flags &=~ TExcValues::e_go_exit ; }
	if (TExcValues::e_nested   & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_nested  )); dw_flags &=~ TExcValues::e_nested  ; }
	if (TExcValues::e_no_stack & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_no_stack)); dw_flags &=~ TExcValues::e_no_stack; }
	if (TExcValues::e_no_way   & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_no_way  )); dw_flags &=~ TExcValues::e_no_way  ; }
	if (TExcValues::e_target   & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_target  )); dw_flags &=~ TExcValues::e_target  ; }
	if (TExcValues::e_unwind   & dw_flags) { m_flags.push_back(CFlag_Fake::Ref().Find(TExcValues::e_unwind  )); dw_flags &=~ TExcValues::e_unwind  ; }

	if (!!dw_flags) {
		CFlag e_unk(dw_flags, _T("#UNK"), TString().Format(_T("Flag is unknown<0x%x>."), dw_flags), false);
		m_flags.push_back(e_unk);
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

void CFlag_Unw_Collection::Set (const TRawFlags& _raw) {
	_raw;
	this->m_flags = _raw;
}

/////////////////////////////////////////////////////////////////////////////

CFlag_Unw_Collection& CFlag_Unw_Collection::operator = (const CFlag_Unw_Collection& _src) { *this << _src.Get(); return *this; }

CFlag_Unw_Collection& CFlag_Unw_Collection::operator <<(const TPointers* const _p_exc_ptrs) { this->Set(_p_exc_ptrs); return *this; }
CFlag_Unw_Collection& CFlag_Unw_Collection::operator <<(const TRecord* const _p_exc_rec) { this->Set(_p_exc_rec); return *this; }

CFlag_Unw_Collection& CFlag_Unw_Collection::operator <<(const uint32_t _raw_value) { this->Set(_raw_value); return *this; }

const TRawFlags& CFlag_Unw_Collection::operator >> (const TRecord* const _p_exc_rec) {
	_p_exc_rec;
	this->Set(_p_exc_rec);
	return this->Get();
}

#if defined (_DEBUG)
CString  CFlag_Unw_Collection::Print (const TRawFlags& _flags, _pc_sz _sep) {
	_flags; _sep;

	static _pc_sz pc_sz_pat= _T("%s%s");

	CString cs_out;
	
	for (uint8_t i_ = 0; i_ < _flags.size(); i_++) {
		const CFlag& flag_ = _flags.at(i_);

		cs_out += flag_.Print();
		if (_flags.size() > 1)
			if (i_ < _flags.size() - 1)
				cs_out += _sep;
	}

	if (cs_out.IsEmpty())
		cs_out = _T("no flags");

	return cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CFlag_Unw_Collection& CFlag_Unw_Collection::operator <<(const TRawFlags& _raw) { this->Set(_raw); return *this; }