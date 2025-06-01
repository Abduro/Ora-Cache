/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-May-2012 at 9:36:22am, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Project Shared Skinned Control Base class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack project on 25-Nov-2020 at 6:46:50.364 pm, UTC+7, Novosibirsk, Wednesday;
*/
#include "ctl.base.border.h"

using namespace ex_ui::controls::borders;

/////////////////////////////////////////////////////////////////////////////

COne:: COne (uint16_t _n_id) : TBase() { this->Margin().Id(_n_id); }
COne:: COne (const COne& _src) : COne() { *this = _src; }
COne:: COne (COne&& _victim) : COne() { *this = _victim;}
COne::~COne (void) {}

/////////////////////////////////////////////////////////////////////////////

const bool COne::IsClear  (void) const {
	return false == TBase::Color().Is() || 0 == TBase::Color().A() || 0 == TBase::Thickness() || false == TBase::Is_valid();
}
const bool COne::IsLimpid (void) const { return this->IsClear(); }

const
CMargin& COne::Margin (void) const { return this->m_margin; }
CMargin& COne::Margin (void)       { return this->m_margin; }

#if defined(_DEBUG)
CString  COne::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{line=%s;is_clear=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{line=%s;is_clear=%s}");
	static _pc_sz pc_sz_pat_r = _T("{line=%s;is_clear=%s}");

	CString cs_line = TBase::Print(e_print::e_req);
	CString cs_clear = TStringEx().Bool(this->IsClear());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, (_pc_sz) cs_line, (_pc_sz) cs_clear); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_line, (_pc_sz) cs_clear); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_line, (_pc_sz) cs_clear); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

COne& COne::operator = (const COne& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Margin();  return *this;}
COne& COne::operator = (COne&& _victim) { *this = (const COne&)_victim; return *this; }

COne& COne::operator <<(const CMargin& _margin) { this->Margin() = _margin; return *this; }

/////////////////////////////////////////////////////////////////////////////

CSet:: CSet (void) {}
CSet:: CSet (const CSet& _src) : CSet() { *this = _src; }
CSet:: CSet (CSet&& _victim) : CSet() { *this= _victim; }
CSet::~CSet (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CSet::Add (const COne& _border) {
	_border;
	TRawBorders::const_iterator it_ = this->Raw().find(_border.Margin().Id());
	if (it_ != this->Raw().end())
		return (err_code) TErrCodes::eObject::eExists;

	try {
		this->Raw().insert(::std::make_pair(_border.Margin().Id(), _border));
	} catch (const ::std::bad_alloc&) { return __e_no_memory; }

	return __s_ok;
}

const
COne&  CSet::Get (const uint16_t _n_id) const {
	_n_id;
	TRawBorders::const_iterator it_ = this->Raw().find(_n_id);
	if (it_ != this->Raw().end())
		return it_->second;
	static COne brd_inv;
	return brd_inv;
}

COne&  CSet::Get (const uint16_t _n_id) {
	_n_id;
	TRawBorders::iterator it_ = this->Raw().find(_n_id);
	if (it_ != this->Raw().end())
		return it_->second;
	static COne brd_inv;
	return brd_inv;
}

err_code  CSet::Rem (const uint16_t _n_id) {
	_n_id;
	TRawBorders::iterator it_ = this->Raw().find(_n_id);
	if (it_ == this->Raw().end())
		return (err_code) TErrCodes::eData::eNotFound;

	try {
		this->Raw().erase(it_);
	} catch (const ::std::bad_alloc&) { return __e_no_memory; }

	return __s_ok;
}

#if defined(_DEBUG)
CString   CSet::Print (const e_print _e_opt, _pc_sz _pfx, _pc_sz _sfx) const {
	_e_opt; _pfx; _sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::%s>>{%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_brds;
	if (this->Raw().size()) {
		for (TRawBorders::const_iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_) {
			if (cs_brds.IsEmpty() == false) {
				cs_brds += _sfx;
				cs_brds += _pfx;
			}
			cs_brds += it_->second.Print(e_print::e_req);
		}
	}
	else
		cs_brds = _T("#empty");

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__,  (_pc_sz) __CLASS__,
		_sfx, _pfx, (_pc_sz) cs_brds,
		_sfx, _pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_brds); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_brds); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawBorders& CSet::Raw (void) const { return this->m_borders; }
TRawBorders& CSet::Raw (void)       { return this->m_borders; }

/////////////////////////////////////////////////////////////////////////////

CSet&  CSet::operator = (const CSet& _src) { *this << _src.Raw(); return *this;}
CSet&  CSet::operator = (CSet&& _victim) {
	*this = (const CSet&)_victim; ((CSet&)_victim).Raw().clear(); return *this;
}

CSet&  CSet::operator <<(const TRawBorders& _raw) { this->Raw() = _raw; return *this; }

CSet&  CSet::operator +=(const CBorder& _border) { this->Add(_border); return *this; }
CSet&  CSet::operator -=(const uint16_t _n_id) { this->Rem(_n_id); return *this; }

const
COne&     CSet::operator [](const uint16_t _n_id) const { return this->Get(_n_id); }
COne&     CSet::operator [](const uint16_t _n_id)       { return this->Get(_n_id); }

/////////////////////////////////////////////////////////////////////////////

CSet_for_rect:: CSet_for_rect (void) : TBase() {

}
CSet_for_rect::~CSet_for_rect (void) {}