/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-May-2025 at 18:25:29.097, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry common definition file.
*/
#include "2d.defs.h"

using namespace geometry::_2D;

/////////////////////////////////////////////////////////////////////////////

namespace geometry { namespace _2D { namespace _impl { void __warning_lnk_4221 (void) {} }}}

/////////////////////////////////////////////////////////////////////////////

CMarker:: CMarker (void) : m_id (0), m_tag(_T("#undef")), m_valid(false) {} // possibly it is not good way for initialization of this object, but is okay for now;
CMarker:: CMarker (const uint32_t _u_id, _pc_sz _p_tag, const bool _b_valid) : CMarker() { *this << _u_id << _p_tag << _b_valid; }
CMarker:: CMarker (const CMarker& _src) : CMarker() { *this = _src; }
CMarker::~CMarker (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CMarker::Id (void) const { return this->m_id; }
bool      CMarker::Id (const uint32_t _value) { const bool b_changed = (this->Id() != _value); if (b_changed) this->m_id = _value; return b_changed; }

uint32_t& CMarker::Id_ref (void) { return this->m_id; }

bool   CMarker::Is_valid (void) const { return this->m_valid; }
bool   CMarker::Is_valid (const bool _b_valid) {
	_b_valid;
	const bool b_changed = (this->Is_valid() != _b_valid);

	if (b_changed)
		this->m_valid = _b_valid;

	return b_changed;
}

#if defined(_DEBUG)
CString CMarker::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{id=%u;tag=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{id=%u;tag=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{id=%u;tag=%s;valid=%s}");

	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Id(), this->Tag(), TStringEx().Bool(this->Is_valid())); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Id(), this->Tag(), TStringEx().Bool(this->Is_valid())); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, this->Id(), this->Tag(), TStringEx().Bool(this->Is_valid())); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

bool    CMarker::Set (const uint32_t _u_id, _pc_sz _p_tag, const bool _b_valid) {
	_u_id; _p_tag; _b_valid;
	bool b_changed = false;

	if (this->Id(_u_id)) b_changed = true;
	if (this->Tag(_p_tag)) b_changed = true;
	if (this->Is_valid(_b_valid)) b_changed = true;

	return b_changed;
}

_pc_sz  CMarker::Tag (void) const { return (_pc_sz) this->m_tag; }
bool    CMarker::Tag (_pc_sz _p_tag) {
	_p_tag;
	bool b_changed =!(nullptr == _p_tag && nullptr == this->Tag()); // there is no sense to replace nullptr by nullptr;
	if (!b_changed)
		return b_changed;

	if (nullptr != _p_tag)
		b_changed = !!this->m_tag.Compare(_p_tag);

	if (b_changed) {
		this->m_tag = _p_tag;
		this->m_tag.Trim();
		b_changed = !!m_tag.GetLength();
	}

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CMarker&  CMarker::operator = (const CMarker& _src) { *this << _src.Id() << _src.Tag() << _src.Is_valid(); return *this; }
CMarker&  CMarker::operator <<(const uint32_t _u_id) { this->Id(_u_id); return *this; }
CMarker&  CMarker::operator <<(_pc_sz _p_tag) { this->Tag(_p_tag); return *this; }
CMarker&  CMarker::operator <<(const bool _b_valid) { this->Is_valid(_b_valid); return *this; }

CMarker::operator _pc_sz (void) const { return this->Tag(); }
CMarker::operator uint32_t (void) const { return this->Id(); }

bool CMarker::operator == (const CMarker& _rhv) const { return (this->Id() == _rhv.Id() && !this->m_tag.Compare(_rhv.Tag()) && this->Is_valid() == _rhv.Is_valid()); }
bool CMarker::operator != (const CMarker& _rhv) const { return false == (*this == _rhv); }