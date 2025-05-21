/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 18:04:01.685, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface implementation file.
*/
#include "2d.shape.h"

using namespace geometry::shapes::_2D;

/////////////////////////////////////////////////////////////////////////////

CSide:: CSide (void) : TBase() {}
CSide:: CSide (const CPoint& _begin, const CPoint& _end) : CSide() { (TBase&)*this << _begin >> _end; }
CSide:: CSide (const CMarker& _marker) : CSide() { *this << _marker; }
CSide:: CSide (const CSide& _src) : CSide() { *this = _src; }
CSide:: CSide (CSide&& _victim) : CSide() { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CSide::Desc (void) const { return this->m_desc.GetString(); }
bool    CSide::Desc (_pc_sz _p_desc) {
	_p_desc;
	const bool b_changed = (nullptr != _p_desc && 0 < ::_tcslen(_p_desc) && 0 != this->m_desc.Compare(_p_desc));

	if (b_changed)
		this->m_desc = _p_desc;

	return b_changed;
}

const
CMarker& CSide::Marker (void) const { return this->m_marker; }
CMarker& CSide::Marker (void)       { return this->m_marker; }

#if defined (_DEBUG)
CString   CSide::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{marker=%s;line=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{marker=%s;line=%s}");
	static _pc_sz pc_sz_pat_r = _T("{marker=%s;line=%s}");

	CString cs_line   = TBase::Print(e_print::e_req);
	CString cs_marker = this->Marker().Print(e_print::e_req);

	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_marker, (_pc_sz) cs_line);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_marker, (_pc_sz) cs_line);
	}
	if (e_print::e_req   == e_opt) {
		cs_out.Format(pc_sz_pat_r,(_pc_sz) cs_marker, (_pc_sz) cs_line);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CSide&  CSide::operator = (const CSide& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Marker() << _src.Desc(); return *this; }
CSide&  CSide::operator = (CSide&& _victim) {

	*this = _victim; _victim.Marker().Set(0, nullptr, false); return *this;
}

CSide&  CSide::operator <<(const CMarker& _marker) { this->Marker() = _marker; return *this; }

CSide&  CSide::operator <<(_pc_sz _p_desc) { this->Desc(_p_desc); return *this; }

bool CSide::operator == (const CSide& _rhv) const {
	_rhv;
	return (this->Marker() == _rhv.Marker() && this->Begin() == _rhv.Begin() && this->End() == _rhv.End());
}

bool CSide::operator != (const CSide& _rhv) const {
	_rhv;
	return (this->Marker() != _rhv.Marker() || this->Begin() != _rhv.Begin() || this->End() != _rhv.End());
}

/////////////////////////////////////////////////////////////////////////////

namespace geometry { namespace shape { namespace _2D { namespace _impl {

	bool compare_raw_sides(const t_raw_sides& _lhv,  const t_raw_sides& _rhv) { // returns true in case when one vector contains the same objects as another one;
		_lhv; _rhv;
	
		bool b_is_equal = (false == _lhv.empty() && _lhv.size() == _rhv.size());
		if ( b_is_equal && false) // it is not true statement, because even in case the size is the same, containing objects may be different; just skipping this;
			return b_is_equal;

		if (_lhv.size() != _rhv.size())
			return (b_is_equal = false);
#if (0)
		for (size_t i_ = 0; i_ < _lhv.size() && i_ < _rhv.size(); i_++) { // ToDo: what is about a sort of the objects: different sort order leads to false;
			
			b_is_equal = (_lhv.at(i_) == _rhv.at(i_));
			if (false == b_is_equal)
				return b_is_equal;
		}
#else   // dummy approach is below:
		for (size_t i_ = 0; i_ < _lhv.size(); i_++) {

			b_is_equal = false;

			for (size_t j_ = 0; i_ < _rhv.size(); j_++) {

				b_is_equal = _lhv.at(i_) == _rhv.at(j_);
				if (b_is_equal)
					break;
			}
			if (false == b_is_equal)
				break;
		}
#endif
		return (b_is_equal);
	}

}}}}
using namespace geometry::shape::_2D::_impl;
/////////////////////////////////////////////////////////////////////////////

CSides:: CSides (void) {}
CSides:: CSides (const CSides& _src) : CSides() { *this = _src; }
CSides::~CSides (void) {}

/////////////////////////////////////////////////////////////////////////////

bool    CSides::Append (const CSide& _side) {
	_side;
	bool b_set = false;

	CSide& result = const_cast<CSide&>(this->Find(_side.Marker().Id()));
	if (result.Marker().Is_valid()) {
		b_set = result != _side;
		if (b_set)
			result = _side;
	}
	else {
		this->Get().push_back(_side);
		b_set = true;
	}
	return b_set;
}

const
CSide&  CSides::Find (const uint32_t _marker_id) const {
	_marker_id;
	for (size_t i_ = 0; i_ < this->Get().size(); i_++) {
		if (this->Get().at(i_).Marker().Id() == _marker_id)
			return this->Get().at(i_);
	}
	static CSide sd_inv;
	sd_inv.Marker().Set(_marker_id, _T("#not_found"), false) ; // ToDo: a marker must have set validity property; (done);

	return sd_inv;
}

const
t_raw_sides& CSides::Get (void) const { return this->m_sides; }
t_raw_sides& CSides::Get (void)       { return this->m_sides; }

bool  CSides::Has (const uint32_t _marker_id) const {
	_marker_id;
	bool b_found = false;

	for (size_t i_ = 0; i_ < this->Get().size(); i_++) {
		if (this->Get().at(i_).Marker().Id() == _marker_id)
			return (b_found = true);
	}

	return b_found;
}

#if defined(_DEBUG)
CString  CSides::Print (const e_print e_opt/*= e_print::e_all*/, _pc_sz _pfx/* = _T("")*/, _pc_sz _sfx/* = _T(";")*/) const {
	e_opt; _pfx; _sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{elements=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{elements=%s}");
	static _pc_sz pc_sz_pat_r = _T("elements={%s}");

	CString cs_out;
	CString cs_raw;

	const size_t b_last = (this->Get().size() > 1 ? this->Get().size() - 1 : 0);

	for (size_t i_ = 0; i_ < this->Get().size(); i_++) {
		cs_raw += _pfx;
		cs_raw += this->Get().at(i_).Print(e_print::e_req);
		if (i_ < b_last)
			cs_raw += _sfx;

	}
	if (this->Get().empty()) {
		cs_raw = _T("#empty");
	}

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_raw); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_raw); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_raw); }

	if (cs_out.IsEmpty()) {
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);
	}

	return  cs_out;
}
#endif

bool CSides::Remove (const uint32_t _marker_id) {
	_marker_id;

	bool b_removed = false;
	size_t n_index  = 0;

	for (size_t i_ = 0; i_ < this->Get().size(); i_++ ) {

		if (this->Get().at(i_).Marker().Id() == _marker_id) {
			b_removed = true;
			n_index = i_;
			break;
		}
	}
	if (b_removed)
		this->Get().erase(this->Get().begin() + n_index);

	return b_removed;
}

bool CSides::Set (const t_raw_sides& _sides) {
	_sides;
	const bool b_changed = false == compare_raw_sides(_sides, this->Get()); // ToDo: how to compare to vectors containing side object(s); (done);

	if (b_changed) {
		this->m_sides = _sides;
	}

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSides&  CSides::operator = (const CSides& _src) { *this << _src.Get(); return *this; }
CSides&  CSides::operator <<(const t_raw_sides& _sides) { this->Set(_sides); return *this; }

CSides&  CSides::operator +=(const CSide& _side) { this->Append(_side); return *this; }
CSides&  CSides::operator -=(const CSide& _side) { *this -= _side.Marker().Id(); return *this; }

CSides&  CSides::operator -=(const uint32_t _u_id) { this->Remove(_u_id); return *this; }

/////////////////////////////////////////////////////////////////////////////

CShape:: CShape (const uint32_t _angles) : m_points(_angles) {}
CShape:: CShape (const CShape& _src) : CShape() { *this = _src; }
CShape::~CShape (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CShape::Is_valid (void) const { 
	 return n_min_point_count <= this->Points().Raw().size(); // it is not good idea to think about a line like about a shape;
}

const
CPoints&  CShape::Points (void) const { return this->m_points; }
CPoints&  CShape::Points (void)       { return this->m_points; }

#if defined (_DEBUG)
CString  CShape::Print (const e_print e_opt, const e_prn_details e_details) const {
	e_opt; e_details;
#if (0)
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{sides=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{sides=%s}");
	static _pc_sz pc_sz_pat_r = _T("{sides=%s}");

	CString cs_sides = this->Sides().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_sides);
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_sides); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_sides); }
#else
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{points=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{points=%s}");
	static _pc_sz pc_sz_pat_r = _T("{points=%s}");

	CString cs_sides = this->Points().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_sides);
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_sides); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_sides); }
#endif
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
#if (0)
const
CSides&  CShape::Sides (void) const { return this->m_sides; }
CSides&  CShape::Sides (void)       { return this->m_sides; }
#endif
/////////////////////////////////////////////////////////////////////////////
#if (1)
CShape&  CShape::operator = (const CShape& _shape) { *this << _shape.Points(); return *this; }
CShape&  CShape::operator <<(const CPoints& _pnts) {  this->Points() = _pnts; return *this; }
#else
CShape&  CShape::operator = (const CShape& _shape) { *this << _shape.Sides(); return *this; }
CShape&  CShape::operator <<(const CSides& _sides) {  this->Sides() = _sides; return *this; }
#endif