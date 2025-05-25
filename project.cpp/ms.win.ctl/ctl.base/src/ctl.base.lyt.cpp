/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 23:27:38.528, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control base layout interface implementation file;
*/
#include "ctl.base.lyt.h"

using namespace ex_ui::controls::layout;

/////////////////////////////////////////////////////////////////////////////

CMargin:: CMargin (const uint16_t _n_id, const int16_t _n_value) : m_id(_n_id), m_value(_n_value) {}

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

CMargin&  CMargin::operator <<(const uint16_t _n_id) { this->Id(_n_id); return *this; }
CMargin&  CMargin::operator >>(const  int16_t _n_value) { this->Value(_n_value); return *this; }