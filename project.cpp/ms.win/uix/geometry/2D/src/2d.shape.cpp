/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Oct-2024 at 18:04:01.685, UTC+4, Batumi, Monday;
	This is Ebo Pack 2D space geometry base shape interface implementation file.
*/
#include "2d.shape.h"

using namespace geometry::shape::_2D;

/////////////////////////////////////////////////////////////////////////////

CSide:: CSide (void) {}
CSide:: CSide (const CPoint& _begin, const CPoint& _end) : CSide() { *this << _begin >> _end; }
CSide:: CSide (const CMarker& _marker) : CSide() { *this << _marker; }
CSide:: CSide (const CSide& _src) : CSide() { *this = _src; }
CSide:: CSide (CSide&& _victim) : CSide() { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////
const
CPoint& CSide::Begin(void) const { return this->Point(e_points::e_begin); }
CPoint& CSide::Begin(void)       { return this->Point(e_points::e_begin); }

_pc_sz  CSide::Desc (void) const { return this->m_desc.GetString(); }
bool    CSide::Desc (_pc_sz _p_desc) {
	_p_desc;
	const bool b_changed = (nullptr != _p_desc && 0 < ::_tcslen(_p_desc) && 0 != this->m_desc.Compare(_p_desc));

	if (b_changed)
		this->m_desc = _p_desc;

	return b_changed;
}

const
CPoint& CSide::End (void)  const { return this->Point(e_points::e_end); }
CPoint& CSide::End (void)        { return this->Point(e_points::e_end); }

const
CMarker& CSide::Marker (void) const { return this->m_marker; }
CMarker& CSide::Marker (void)       { return this->m_marker; }

CPoint  CSide::Middle (void) const {

	const int32_t n_x = (this->Begin().X() > this->End().X() ? this->Begin().X() - this->End().X() : this->End().X() - this->Begin().X()  ) / 2;
	const int32_t n_y = (this->Begin().Y() > this->End().Y() ? this->Begin().Y() - this->End().Y() : this->End().Y() - this->Begin().Y()  ) / 2;

	return CPoint(n_x, n_y);
}

const
CPoint& CSide::Point (const e_points _index) const { return this->m_points[_index]; }
CPoint& CSide::Point (const e_points _index)       { return this->m_points[_index]; }

#if defined (_DEBUG)
CString   CSide::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{marker=%s;begin=%s;end=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{marker=%s;begin=%s;end=%s}");
	static _pc_sz pc_sz_pat_r = _T("{marker=%s;begin=%s;end=%s}");

	CString cs_mkt = this->Marker().Print(CMarker::e_no_ns);
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_mkt, (_pc_sz) this->Begin().Print(CPoint::e_req), (_pc_sz) this->End().Print(CPoint::e_req));
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_mkt, (_pc_sz) this->Begin().Print(CPoint::e_req), (_pc_sz) this->End().Print(CPoint::e_req)); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz) cs_mkt, (_pc_sz) this->Begin().Print(CPoint::e_req), (_pc_sz) this->End().Print(CPoint::e_req)); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CSide&  CSide::operator = (const CSide& _src) { *this << _src.Marker() << _src.Begin() << _src.Desc() >> _src.End(); return *this; }
CSide&  CSide::operator = (CSide&& _victim) {

	*this = _victim; _victim.Marker().Set(0, nullptr, false); return *this;
}

CSide&  CSide::operator <<(const CMarker& _marker) { this->Marker() = _marker; return *this; }

CSide&  CSide::operator <<(const CPoint& _begin) { this->Begin() = _begin; return *this; }
CSide&  CSide::operator >>(const CPoint& _end) { this->End() = _end; return *this; }

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
		cs_raw += this->Get().at(i_).Print(TSide::e_req);
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

CShape:: CShape (void) {}
CShape:: CShape (const CShape& _src) : CShape() { *this = _src; }
CShape::~CShape (void) {}

/////////////////////////////////////////////////////////////////////////////
#if defined (_DEBUG)
CString  CShape::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{sides=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{sides=%s}");
	static _pc_sz pc_sz_pat_r = _T("{sides=%s}");

	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) this->Sides().Print(CSides::e_req));
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) this->Sides().Print(CSides::e_req)); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) this->Sides().Print(CSides::e_req)); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
CSides&  CShape::Sides (void) const { return this->m_sides; }
CSides&  CShape::Sides (void)       { return this->m_sides; }

/////////////////////////////////////////////////////////////////////////////

CShape&  CShape::operator = (const CShape& _shape) { *this << _shape.Sides(); return *this; }
CShape&  CShape::operator <<(const CSides& _sides) {  this->Sides() = _sides; return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace geometry { namespace shape { namespace _2D { namespace _impl {


	CPoint_2&  _get_invalid_point (void) {
	
		static CPoint_2 pt_inv;
		{
			(CPoint&)pt_inv >> 0 << 0; pt_inv.Marker() << (uint32_t)0 << _T("#invalid") << false; 
		}
		return pt_inv;
	}

	CString   _print_out_point_x_set(const CPoint_2* const _p_set, const uint32_t _n_size, _pc_sz _pfx, _pc_sz _sfx) {
		_p_set; _n_size;
		CString cs_out;

		for (uint32_t i_ = 0; i_ < _n_size; i_++) {
		
			const CPoint_2& p_pt = _p_set[i_];
			
			cs_out += _pfx;
			cs_out += p_pt.Print(CPoint_2::e_req);
			cs_out += _sfx;
		}


		return  cs_out;
	}

}}}}

using namespace geometry::shape::_2D::_impl;
using CCorners = CRectangle::CCorners;
/////////////////////////////////////////////////////////////////////////////

CCorners:: CCorners (void) {
	m_points[e_index::e_A].Marker() << e_index::e_A << _T("A") << true; // otherwise the validity attribute is false by default;
	m_points[e_index::e_B].Marker() << e_index::e_B << _T("B") << true;
	m_points[e_index::e_C].Marker() << e_index::e_C << _T("C") << true;
	m_points[e_index::e_D].Marker() << e_index::e_D << _T("D") << true;
}
CCorners:: CCorners (const CCorners& _src) : CCorners() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

const CPoint_2& CCorners::A(void) const { return this->m_points[e_corners::e_A]; } CPoint_2& CCorners::A(void) { return this->m_points[e_corners::e_A]; }
const CPoint_2& CCorners::B(void) const { return this->m_points[e_corners::e_A]; } CPoint_2& CCorners::B(void) { return this->m_points[e_corners::e_A]; }
const CPoint_2& CCorners::C(void) const { return this->m_points[e_corners::e_A]; } CPoint_2& CCorners::C(void) { return this->m_points[e_corners::e_A]; }
const CPoint_2& CCorners::D(void) const { return this->m_points[e_corners::e_A]; } CPoint_2& CCorners::D(void) { return this->m_points[e_corners::e_A]; }

const
CPoint_2& CCorners::Corner(const e_corners _n_corner) const {
	
	if (_n_corner < CRectangle::u_corners)
		return this->m_points[_n_corner];
	else
		return _get_invalid_point();
}

CPoint_2& CCorners::Corner(const e_corners _n_corner) {

	if (_n_corner < CRectangle::u_corners)
		return this->m_points[_n_corner];
	else
		return _get_invalid_point();
}

/////////////////////////////////////////////////////////////////////////////

CCorners& CCorners::operator = (const CCorners& _src) {

	this->A() = _src.A(); this->B() = _src.B(); this->C() = _src.C(); this->D() = _src.D(); return *this;
}

const
CPoint_2&   CCorners::operator [] (const e_corners _n_ndx) const { return this->Corner(_n_ndx); }
CPoint_2&   CCorners::operator [] (const e_corners _n_ndx)       { return this->Corner(_n_ndx); }

/////////////////////////////////////////////////////////////////////////////

CRectangle:: CRectangle (void) {}
CRectangle:: CRectangle (const CRectangle& _src) : CRectangle() { *this = _src; }
CRectangle::~CRectangle (void) {}

/////////////////////////////////////////////////////////////////////////////

CPoint       CRectangle::Center (void) const {

	return CPoint(
		CSide(this->Corners().A(), this->Corners().B()).Middle().X(),
		CSide(this->Corners().A(), this->Corners().D()).Middle().Y()
	);
}
const
CCorners&    CRectangle::Corners (void) const { return this->m_corners; }
CCorners&    CRectangle::Corners (void)       { return this->m_corners; }

const bool   CRectangle::Is_valid (void) const {

	bool b_valid = true;

	if ( b_valid ) b_valid = this->Corners().A().Marker().Is_valid();
	if ( b_valid ) b_valid = this->Corners().B().Marker().Is_valid();
	if ( b_valid ) b_valid = this->Corners().C().Marker().Is_valid();
	if ( b_valid ) b_valid = this->Corners().D().Marker().Is_valid();

	return b_valid;
}

#if defined (_DEBUG)
CString      CRectangle::Print  (const e_print e_opt, _pc_sz _pfx, _pc_sz _sfx) const {
	e_opt; _pfx; _sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{corners=%s%s%svalid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{corners=%s%s%svalid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{corners=%s%s%svalid=%s}");

	CString cs_pts = _print_out_point_x_set(this->m_corners.m_points, CRectangle::u_corners, _pfx, _sfx); CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _sfx, (_pc_sz) cs_pts, _pfx, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, _sfx, (_pc_sz) cs_pts, _pfx, (_pc_sz) cs_valid); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, _sfx, (_pc_sz) cs_pts, _pfx, (_pc_sz) cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

CSize CRectangle::Size (void) const {

//	const int32_t n_height = (((const CRectangle&)*this)[e_index::e_A].X() > ((const CRectangle&)*this)[e_index::e_D].X());

	const int32_t n_height = CSide(this->Corners().A(), this->Corners().D()).Middle().Y();
	const int32_t n_width  = CSide(this->Corners().A(), this->Corners().B()).Middle().X();

//	const int32_t n_height = (
//		this->Corners().A().X() > this->Corners().D().X() ? this->Corners().A().X() - this->Corners().D().X() : this->Corners().D().X() > this->Corners().A().X()
//		) / 2;

	return CSize(n_width, n_height);
}


/////////////////////////////////////////////////////////////////////////////

CRectangle& CRectangle::operator = (const CRectangle& _src) { *this << _src.Corners();	return *this; }
CRectangle& CRectangle::operator <<(const CCorners& _corners) { this->Corners() = _corners; return *this; }

const
CPoint_2&   CRectangle::operator [] (const e_index _n_ndx) const { return this->Corners().Corner(_n_ndx); }
CPoint_2&   CRectangle::operator [] (const e_index _n_ndx)       { return this->Corners().Corner(_n_ndx); }