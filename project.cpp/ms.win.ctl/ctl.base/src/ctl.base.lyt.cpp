/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 23:27:38.528, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control base layout interface implementation file;
*/
#include "ctl.base.lyt.h"

using namespace ex_ui::controls::layout;

/////////////////////////////////////////////////////////////////////////////

CMargin:: CMargin (const uint16_t _n_id, const int16_t _n_value) : m_id(_n_id), m_value(_n_value) {}
CMargin:: CMargin (const CMargin& _src) : CMargin() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

uint16_t  CMargin::Id (void) const { return this->m_id; }
bool      CMargin::Id (const uint16_t _n_id) {
	_n_id;
	const bool b_changed = this->Id() != _n_id;

	if (b_changed)
		this->m_id = _n_id;

	return b_changed;
}

#if defined(_DEBUG)
CString   CMargin::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{id=%u;value=%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{id=%u;value=%d}");
	static _pc_sz pc_sz_pat_r = _T("{id=%u;value=%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Id(), this->Value());
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Id(), this->Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Id(), this->Value()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

int16_t   CMargin::Value (void) const { return this->m_value; }
bool      CMargin::Value (const int16_t _n_value) {
	const bool b_changed = this->Value() != _n_value;
	if (b_changed)
		this->m_value = _n_value;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CMargin&  CMargin::operator = (const CMargin& _src) { *this << _src.Id() >> _src.Value(); return *this; }

CMargin&  CMargin::operator <<(const uint16_t _n_id) { this->Id(_n_id); return *this; }
CMargin&  CMargin::operator >>(const  int16_t _n_value) { this->Value(_n_value); return *this; }

/////////////////////////////////////////////////////////////////////////////

CMargins:: CMargins (void) {}
CMargins::~CMargins (void) {}

/////////////////////////////////////////////////////////////////////////////

bool  CMargins::Is_zero (void) const {

	for (TRawMargins::const_iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_)
		if (!!it_->second.Value())
				return false;
	return true;
}

const
TRawMargins& CMargins::Raw (void) const { return this->m_raw; }
TRawMargins& CMargins::Raw (void)       { return this->m_raw; }

/////////////////////////////////////////////////////////////////////////////

CMargins_of_rect:: CMargins_of_rect (void) : TBase() {

	try {
		TBase::m_raw.insert(::std::make_pair(e_sides::e_left  , CMargin(e_sides::e_left  , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_top   , CMargin(e_sides::e_top   , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_right , CMargin(e_sides::e_right , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_bottom, CMargin(e_sides::e_bottom, 0)));
	} catch (const ::std::bad_alloc&) { __e_no_memory; }

}
CMargins_of_rect::~CMargins_of_rect (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CMargins_of_rect::ApplyTo (t_rect& _rect) const {
	_rect;
	bool b_changed = false;

	if (TBase::Is_zero())
		return b_changed;

	if (!!this->Get(e_sides::e_left  ).Value()) { _rect.left   += this->Get(e_sides::e_left  ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_top   ).Value()) { _rect.top    += this->Get(e_sides::e_top   ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_right ).Value()) { _rect.right  -= this->Get(e_sides::e_right ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_bottom).Value()) { _rect.bottom -= this->Get(e_sides::e_bottom).Value(); b_changed = true; }

	return b_changed;
}

const
CMargin& CMargins_of_rect::Get(const e_sides _side) const {

	TRawMargins::const_iterator found = TBase::Raw().find(_side);
	if (found == TBase::Raw().end()) {
		static CMargin inv_margin(0,0);
		return inv_margin;
	}
	else
		return found->second;
}
CMargin& CMargins_of_rect::Get(const e_sides _side)  {

	TRawMargins::iterator found = TBase::Raw().find(_side);
	if (found == TBase::Raw().end()) {
		static CMargin inv_margin(0,0);
		return inv_margin;
	}
	else
		return found->second;
}

#if defined(_DEBUG)
CString   CMargins_of_rect::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{left:%d;top:%d;right:%d;bottom:%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{left:%d;top:%d;right:%d;bottom:%d}");
	static _pc_sz pc_sz_pat_r = _T("{left:%d;top:%d;right:%d;bottom:%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif