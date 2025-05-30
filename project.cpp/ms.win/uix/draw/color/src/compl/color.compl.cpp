/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Nov-2019 at 6:37:16a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared drawing library complementary colors pairs implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color library on 10-Oct-2021 at 2:01:31.3813618 pm, UTC+7, Novosibirsk, Sunday
*/
#include "color.compl.h"

using namespace ex_ui::color::complementary;

/////////////////////////////////////////////////////////////////////////////

COne:: COne (void) : m_algo(_algo::e_simplistic), m_clr(0) {}
COne:: COne (const COne& _ref) : COne() { *this = _ref; }
COne:: COne (const rgb_color _clr_src, const _algo e_algo) : COne() { *this << e_algo << _clr_src; }
COne::~COne (void) {}

/////////////////////////////////////////////////////////////////////////////

using TAlgo = COne::_algo;

TAlgo  COne::Algo (void) const { return this->m_algo; }
bool   COne::Algo (const _algo e_algo) {
	e_algo;
	bool b_changed = (this->Algo() != e_algo);

	if ( b_changed )
		this->m_algo = e_algo;

	return b_changed;
}

rgb_color COne::Get (void) const { return this->m_clr; }

#if defined(_DEBUG)
CString   COne::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {clr=%s;algo=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {clr=%s;algo=%s}");
	static _pc_sz pc_sz_pat_r = _T("clr=%s;algo=%s");

	CString cs_clr = CQuad(this->Get()).Print(e_print::e_req);
	CString cs_algo = _T("e_simplistic");  // this one is only available;

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, (_pc_sz) cs_clr, (_pc_sz) cs_algo); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_clr, (_pc_sz) cs_algo); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_clr, (_pc_sz) cs_algo); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

err_code  COne::Set (const rgb_color _from, const _algo e_how_to_make_it) {
	_from; e_how_to_make_it;
	err_code n_result = __s_ok;

	if (__clr_none == _from)
		return (n_result = __e_inv_arg);

	this->Algo(e_how_to_make_it);

	switch (e_how_to_make_it) {
	case _algo::e_simplistic: {
			// https://stackoverflow.com/questions/3054873/programmatically-find-complement-of-colors ;
			_long r_ = 0xff & (_from >>  0);  r_ = 0xff - r_;
			_long g_ = 0xff & (_from >>  8);  g_ = 0xff - g_;
			_long b_ = 0xff & (_from >> 16);  b_ = 0xff - b_;
			_long a_ = 0xff & (_from >> 24);  // alpha value must not be affected, because it is treated as not pre-multiplied;

			this->m_clr = _r_g_b_a(r_,g_,b_,a_);

		} break;
	default:
		n_result = (err_code)TErrCodes::eData::eUnsupport;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

COne&  COne::operator = (const COne& _ref) { this->m_clr = _ref.Get(); *this << _ref.Algo(); return *this; }
COne&  COne::operator <<(const _algo e_algo)  { this->Algo(e_algo); return *this; }
COne&  COne::operator <<(const rgb_color _clr) { this->Set(_clr, this->Algo()); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSet:: CSet (void) { m_clr[0] = m_clr[1] = m_clr[2] = __clr_none; this->Name() = _T("#unset"); }
CSet:: CSet (const CSet& _src) : CSet() { *this = _src; }
CSet:: CSet (const rgb_color _dark, const rgb_color _mid, const rgb_color _lt, _pc_sz _lp_sz_nm, _pc_sz _lp_sz_ds) {
	m_clr[0] = _dark; m_clr[1] = _mid; m_clr[2] = _lt; m_name = _lp_sz_nm; m_desc = _lp_sz_ds;
}
CSet:: CSet (CSet&& _victim) : CSet() { *this = _victim; }
CSet::~CSet (void) {}

/////////////////////////////////////////////////////////////////////////////

const
rgb_color& CSet::Dark  (void) const { return m_clr[0]; }
rgb_color& CSet::Dark  (void)       { return m_clr[0]; }

const
rgb_color& CSet::Light (void) const { return m_clr[2]; }
rgb_color& CSet::Light (void)       { return m_clr[2]; }

const
rgb_color& CSet::Medium(void) const { return m_clr[1]; }
rgb_color& CSet::Medium(void)       { return m_clr[1]; }

const
rgb_color& CSet::C0 (void) const { return m_clr[0]; }
rgb_color& CSet::C0 (void)       { return m_clr[0]; }

const
rgb_color& CSet::C2 (void) const { return m_clr[2]; }
rgb_color& CSet::C2 (void)       { return m_clr[2]; }

const
rgb_color& CSet::C1 (void) const { return m_clr[1]; }
rgb_color& CSet::C1 (void)       { return m_clr[1]; }

/////////////////////////////////////////////////////////////////////////////

const bool   CSet::Is (void) const { return (m_clr[0] != __clr_none || m_clr[1] != __clr_none || m_clr[2] != __clr_none); }

/////////////////////////////////////////////////////////////////////////////
const
CString&  CSet::Desc  (void) const { return m_desc;   }
CString&  CSet::Desc  (void)       { return m_desc;   }
const
CString&  CSet::Name  (void) const { return m_name;   }
CString&  CSet::Name  (void)       { return m_name;   }

#if defined(_DEBUG)
CString   CSet::Print(const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {dark:%s;medium:%s;light:%s;name=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {dark:%s;medium:%s;light:%s;name=%s}");
	static _pc_sz pc_sz_pat_r = _T("dark:%s;medium:%s;light:%s;name=%s");

	CString cs_drk = CQuad(this->Dark()).Print(e_print::e_req);
	CString cs_mdm = CQuad(this->Medium()).Print(e_print::e_req);
	CString cs_lgt = CQuad(this->Light()).Print(e_print::e_req);

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_drk, (_pc_sz) cs_mdm, (_pc_sz) cs_lgt, (_pc_sz) this->Name());
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_drk, (_pc_sz) cs_mdm, (_pc_sz) cs_lgt, (_pc_sz) this->Name());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz) cs_drk, (_pc_sz) cs_mdm, (_pc_sz) cs_lgt, (_pc_sz) this->Name());
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CSet& CSet::operator = (const CSet& _src) {
	this->C0() = _src.C0(); this->C1() = _src.C1(); this->C2() = _src.C2(); this->Name() = _src.Name(); this->Desc() = _src.Desc();
	return *this;
}
CSet& CSet::operator = (CSet&& _victim) {
	*this = (const CSet&)_victim; return *this;
}

/////////////////////////////////////////////////////////////////////////////

CSet_Enum:: CSet_Enum(void) {}
CSet_Enum::~CSet_Enum(void) {}

/////////////////////////////////////////////////////////////////////////////

const CSet& CSet_Enum::Get (const uint32_t _ndx) const {
	_ndx;
	if (_ndx >= this->Raw().size()) {
		static CSet inv_set;
		return inv_set;
	}
	return this->m_sets.at(_ndx);
}
const
TRawSets& CSet_Enum::Raw (void) const { return m_sets; }

#if defined(_DEBUG)
CString   CSet_Enum::Print(const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("%s%s%s%s%s");

	CString cs_sets;

	if (this->Raw().empty()) {
		cs_sets = _T("#empty");
	}
	else {
		for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {
			const CSet& set = this->Raw().at(i_);
			if (cs_sets.IsEmpty() == false) {
				cs_sets += _p_sfx;
				cs_sets += _p_pfx;
			}
			cs_sets += set.Print(e_print::e_req);
		}
	}

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_sets, _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_sets, _p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_sets, _p_sfx, _p_pfx);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

const CSet& CSet_Enum:: operator[] (const uint32_t _ndx) const { return this->Get(_ndx); }