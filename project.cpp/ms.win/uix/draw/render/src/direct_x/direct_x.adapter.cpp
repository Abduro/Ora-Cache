/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 14:07:02.321, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project hardware video/adapter interface implementation file;
*/
#include "direct_x.adapter.h"
#include "direct_x.factory.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CProps:: CProps (void) : m_12_vers(false), m_hi_perf(false), m_lo_power(false) {}
CProps:: CProps (const CProps& _src) : CProps() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

bool  CProps::Dx_12   (void) const { return this->m_12_vers; }
bool  CProps::Dx_12   (const bool _b_value) {
	const bool b_changed = (this->Dx_12() != _b_value); if (b_changed) this->m_12_vers = _b_value; return b_changed;
}

bool  CProps::Hi_Perf (void) const { return this->m_hi_perf; }
bool  CProps::Hi_Perf (const bool _b_value) {
	const bool b_changed = (this->Hi_Perf() != _b_value); if (b_changed) this->m_hi_perf = _b_value; return b_changed;
}

bool  CProps::Lo_Power(void) const { return this->m_lo_power; }
bool  CProps::Lo_Power(const bool _b_value) {
	const bool b_changed = (this->Lo_Power() != _b_value); if (b_changed) this->m_lo_power = _b_value; return b_changed;
}

#if defined(_DEBUG)
CString  CProps::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{dx_12=%s;hi_perf=%s;lo_power=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{dx_12=%s;hi_perf=%s;lo_power=%s}");
	static _pc_sz pc_sz_pat_r = _T("{dx_12=%s;hi_perf=%s;lo_power=%s}");

	CString cs_dx_12 = TStringEx().Bool(this->Dx_12());
	CString cs_hi_perf = TStringEx().Bool(this->Hi_Perf());
	CString cs_lo_power = TStringEx().Bool(this->Lo_Power());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			(_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			(_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CProps&  CProps::operator = (const CProps& _src) {
	this->Dx_12(_src.Dx_12()); this->Hi_Perf(_src.Hi_Perf()); this->Lo_Power(_src.Lo_Power());
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
}}}}

using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

}}}}

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

}}}}