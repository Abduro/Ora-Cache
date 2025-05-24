/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 22:07:50.118, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry fundamental objects' interface implementation file.
*/
#include "2d.base.h"

using namespace geometry::_2D;
using namespace geometry::_2D::base;

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CPoint:: CPoint (int32_t _x, int32_t _y) : m_point{_x, _y} {}
CPoint:: CPoint (const CPoint& _src) : CPoint() { *this = _src; }
CPoint:: CPoint (CPoint&& _victim) : CPoint() { *this = _victim; }
CPoint::~CPoint (void) {}

/////////////////////////////////////////////////////////////////////////////
void CPoint::Clear (void) { this->Set(0,0); }
bool CPoint::Is_zero (void) const { return (!this->X() && !this->Y()); }

const
t_point&  CPoint::Raw (void) const { return this->m_point; }
t_point&  CPoint::Raw (void)       { return this->m_point; }

bool CPoint::Set (const int32_t _x, const int32_t _y) {
	_x; _y;
	bool b_changed = false;

	if (this->X(_x)) b_changed = true;
	if (this->Y(_y)) b_changed = true;

	return (b_changed);
}

int32_t CPoint::X (void) const { return this->Raw().x; }
bool    CPoint::X (const int32_t _x) { const bool b_changed = this->X() != _x; if (b_changed) this->m_point.x = _x; return b_changed; }

int32_t CPoint::Y (void) const { return this->Raw().y; }
bool    CPoint::Y (const int32_t _y) { const bool b_changed = this->Y() != _y; if (b_changed) this->m_point.y = _y; return b_changed; }

#if defined(_DEBUG)
CString CPoint::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{x=%d;y=%d;zero=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{x=%d;y=%d}");
	static _pc_sz pc_sz_pat_r = _T("{x=%d;y=%d}");

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->X(), this->Y(), TStringEx().Bool(this->Is_zero())); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, this->X(), this->Y()); }
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, this->X(), this->Y()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CPoint& CPoint::operator = (const CPoint& _src) { *this << _src.X() >> _src.Y(); return *this; }

CPoint& CPoint::operator = (CPoint&& _victim) {

	*this = _victim; _victim.Set(0,0); return *this;
}

CPoint& CPoint::operator <<(const int32_t _x) { this->X(_x); return *this; }
CPoint& CPoint::operator >>(const int32_t _y) { this->Y(_y); return *this; }

CPoint& CPoint::operator <<(const t_point& _pt) { *this >> _pt.y << _pt.x; return *this; }

CPoint::operator const t_point& (void) const { return this->Raw(); }
CPoint::operator       t_point& (void)       { return this->Raw(); }

bool CPoint::operator == (const CPoint& _rsv) const { return (this->X() == _rsv.X() && this->Y() == _rsv.Y()); }
bool CPoint::operator != (const CPoint& _rsv) const { return (this->X() != _rsv.X() || this->Y() != _rsv.Y()); }

CPoint& CPoint::operator += (const CPoint& _rhs) { this->X(this->X() + _rhs.X()); this->Y(this->Y() + _rhs.Y()); return *this; }
CPoint& CPoint::operator -= (const CPoint& _rhs) { this->X(this->X() - _rhs.X()); this->Y(this->Y() - _rhs.Y()); return *this; }

/////////////////////////////////////////////////////////////////////////////

TPoint  operator + (const TPoint& _lsv, const TPoint& _rsv) { return TPoint(_lsv.X() + _rsv.X(), _lsv.Y() + _rsv.Y()); }
TPoint  operator - (const TPoint& _lsv, const TPoint& _rsv) { return TPoint(_lsv.X() - _rsv.X(), _lsv.Y() - _rsv.Y()); }

/////////////////////////////////////////////////////////////////////////////

CPoints:: CPoints (const uint32_t _n_count) { *this << _n_count; }
CPoints:: CPoints (const CPoints& _src) : CPoints() { *this = _src; }
CPoints:: CPoints (CPoints&& _victim) : CPoints() { *this = _victim; }
CPoints::~CPoints (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CPoints::Count (void) const { return static_cast<uint32_t>(this->Raw().size()); }    
err_code  CPoints::Count (const uint32_t _n_count) {
	_n_count;
	err_code n_result = __s_ok;

	try {
		if (false) {}
		else if (0 == _n_count) {
			this->Raw().clear();
			this->Raw().shrink_to_fit();
		}
		else if (_n_count != this->Count()) { // removes element(s) or adds element(s);
			this->Raw().resize(_n_count);
			this->Raw().shrink_to_fit();
		}
		else
			n_result = __s_false;
	}
	catch (const ::std::bad_alloc&) { n_result = __e_no_memory; }

	return n_result;
}

const
CPoint&  CPoints::Get (const uint32_t _ndx) const { if (_ndx >= this->Count()) { static CPoint pt_fake; return pt_fake; } else return this->Raw().at(_ndx); }
CPoint&  CPoints::Get (const uint32_t _ndx)       { if (_ndx >= this->Count()) { static CPoint pt_fake; return pt_fake; } else return this->Raw().at(_ndx); }     

#if defined(_DEBUG)

CString CPoints::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>points:[%s]");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>points:[%s]");
	static _pc_sz pc_sz_pat_r = _T("[%s]");

	CString cs_out;
	CString cs_pts;

	const size_t b_last = (this->Raw().size() > 1 ? this->Raw().size() - 1 : 0);

	for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {

		cs_pts += this->Raw().at(i_).Print(e_print::e_req);
		if (i_ < b_last)
			cs_pts += _T(";");
	}
	if (this->Raw().empty()) {
		cs_pts = _T("#empty");
	}
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, (_pc_sz) cs_pts); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_pts); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_pts); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

#endif

const
t_raw_pts& CPoints::Raw (void) const { return this->m_points; }
t_raw_pts& CPoints::Raw (void)       { return this->m_points; }

err_code  CPoints::Rem (const uint32_t _ndx) {
	_ndx;
	err_code n_result = __s_ok;
	if (_ndx >= this->Count())
		return n_result = __e_inv_arg;

	try {
		// https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index ;
		this->Raw().erase(this->Raw().begin() + _ndx);
		this->Raw().shrink_to_fit();
	}
	catch(...){ n_result = __e_no_memory; }

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CPoints&  CPoints::operator = (const CPoints& _src) { this->Raw() = _src.Raw(); return *this; }
CPoints&  CPoints::operator = (CPoints&& _victim) {
	*this = _victim; _victim.Raw().clear(); return *this; // no swap is used yet;
}

CPoints&  CPoints::operator <<(const t_raw_pts& _pts) { this->Raw() = _pts; return *this; }
CPoints&  CPoints::operator <<(const uint32_t _n_count) { this->Count(_n_count); return *this; }

bool CPoints::operator == (const CPoints& _rhv) const {
	_rhv;
	bool b_result = (0 == this->Raw().size() && 0 == _rhv.Raw().size());
	if ( b_result )
		return b_result;

	b_result = this->Raw().size() != _rhv.Raw().size(); // if vectors' sizes are not the same: it is obviosly vectors having different content;
	if (b_result)
		return (b_result = false);

	for (size_t i_ = 0; i_ < this->Raw().size() && i_ < _rhv.Raw().size(); i_++) {

		if (this->Raw().at(i_) != _rhv.Raw().at(i_))
			return (b_result = false);
	}

	return (b_result = true);
}

bool CPoints::operator != (const CPoints& _rhv) const {
	return false == (*this == _rhv);
}

/////////////////////////////////////////////////////////////////////////////

CPoint_2:: CPoint_2 (const int32_t _x, const int32_t _y) : TBase(_x, _y) {}
CPoint_2:: CPoint_2 (const CPoint_2& _src) : CPoint_2() { *this = _src; }
CPoint_2:: CPoint_2 (CPoint_2&& _victim) : CPoint_2() { *this = _victim; }
CPoint_2::~CPoint_2 (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CMarker&   CPoint_2::Marker (void) const { return this->m_marker; }
CMarker&   CPoint_2::Marker (void)       { return this->m_marker; }

#if defined(_DEBUG)
CString    CPoint_2::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{x=%d;y=%d;marker=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{x=%d;y=%d;marker=%s}");
	static _pc_sz pc_sz_pat_r = _T("{x=%d;y=%d;marker=%s}");

	CString cs_marker = this->Marker().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->X(), this->Y(), (_pc_sz) cs_marker); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, this->X(), this->Y(), (_pc_sz) cs_marker); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, this->X(), this->Y(), (_pc_sz) cs_marker); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s].%s(#inv_arg==%d);"), (_pc_sz) __CLASS__, (_pc_sz) __METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CPoint_2& CPoint_2::operator = (const CPoint_2& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Marker(); return *this; }
CPoint_2& CPoint_2::operator = (CPoint_2&& _victim) { *this = _victim; return *this; }
CPoint_2& CPoint_2::operator <<(const CMarker& _marker) { this->Marker() = _marker; return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace geometry { namespace _2D { namespace base { namespace _impl {

#if defined(_DEBUG)

	class CPattern {
	public:
		 CPattern (void) {} CPattern (const CPattern&) = delete; CPattern (CPattern&&) = delete;
		~CPattern (void) {}

	public:
		static _pc_sz Get (const ::e_print _e_opt) {

			static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{height=%d;width=%d;zero=%s}");
			static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{height=%d;width=%d;zero=%s}");
			static _pc_sz pc_sz_pat_r = _T("{h|w=%d|%d(px)}");

			if (e_print::e_all   == _e_opt) return pc_sz_pat_a;
			if (e_print::e_no_ns == _e_opt) return pc_sz_pat_n;
			if (e_print::e_req   == _e_opt) return pc_sz_pat_r;

			static
			_pc_sz  pc_sz_not_sup = _T("cls::[%s::%s].%s(#inv_arg==%d);");
			return  pc_sz_not_sup;
		}

	private:
		CPattern& operator = (CPattern&) = delete;
		CPattern& operator = (CPattern&&) = delete;

	};
#endif
}}}}
using namespace geometry::_2D::base::_impl;

/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (int32_t _width, int32_t _height) : m_size{_width, _height} {}
CSize:: CSize (const CSize& _src) : CSize() { *this = _src; }
CSize:: CSize (CSize&& _victim) : CSize() { *this = _victim; }
CSize::~CSize (void) {}

/////////////////////////////////////////////////////////////////////////////

int32_t CSize::H (void) const { return this->m_size.cy; }
bool    CSize::H (const int32_t _height) { const bool b_changed = (this->H() != _height); if (b_changed) this->m_size.cy = _height; return b_changed; }

int32_t CSize::Height (void) const { return this->H(); }
bool    CSize::Height (const int32_t _value) { return this->H(_value); }

bool CSize::Is_point (void) const { return this->Is_zero(); }
bool CSize::Is_zero (void) const { return (!this->H() && !this->W()); }

#if defined(DEBUG)
CString CSize::Print (const e_print e_opt) const {
	e_opt;
#if (0)
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{height=%d;width=%d;zero=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{height=%d;width=%d;zero=%s}");
	static _pc_sz pc_sz_pat_r = _T("{height=%d;width=%d}");
#endif
	using pat = CPattern;

	CString cs_valid = TStringEx().Bool(this->Is_zero());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->H(), this->W(), (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __CLASS__, this->H(), this->W(), (_pc_sz)cs_valid); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pat::Get(e_opt), this->H(), this->W()); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
t_size& CSize::Raw (void) const { return this->m_size; }
t_size& CSize::Raw (void)       { return this->m_size; }

bool    CSize::Set (const int32_t _width, const int32_t _height) {
	_width; _height;

	bool b_changed = false;

	if (this->H(_height)) b_changed = true;
	if (this->W(_width)) b_changed = true;

	return b_changed;
}

int32_t CSize::W (void) const { return this->m_size.cx; }
bool    CSize::W (const int32_t _width) { const bool b_changed = (this->W() != _width); if (b_changed) this->m_size.cx = _width; return b_changed; }

int32_t CSize::Width (void) const { return this->W(); }
bool    CSize::Width (const int32_t _value) { return this->W(_value); }

/////////////////////////////////////////////////////////////////////////////

CSize&  CSize::operator = (const CSize& _src) { *this >> _src.H() << _src.W(); return *this; }

CSize&  CSize::operator = (CSize&& _victim) {

	*this = _victim; _victim.Set(0, 0);
	return *this;
}

CSize&  CSize::operator <<(const int32_t _width) { this->W(_width); return *this; }
CSize&  CSize::operator >>(const int32_t _height) { this->H(_height); return *this; }

CSize&  CSize::operator <<(const t_size& _size) { *this >> _size.cy << _size.cx; return *this; }

CSize::operator const t_size& (void) const { return this->Raw(); }
CSize::operator       t_size& (void)       { return this->Raw(); }

bool CSize::operator == (const CSize& _rsv) const { return (this->H() == _rsv.H() && this->W() == _rsv.W()); }
bool CSize::operator != (const CSize& _rsv) const { return (this->H() != _rsv.H() || this->W() != _rsv.W()); }

/////////////////////////////////////////////////////////////////////////////

CSize_U:: CSize_U (void) : m_size{0,0} {}
CSize_U:: CSize_U (const uint32_t _width, const uint32_t _height) : CSize_U() { *this >> _height << _width; }
CSize_U:: CSize_U (const CSize_U& _src) : CSize_U() { *this = _src; }
CSize_U:: CSize_U (CSize_U&& _victim) : CSize_U() { *this = _victim; }
CSize_U::~CSize_U (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CSize_U::H (void) const { return this->m_size.cy; }
bool      CSize_U::H (const uint32_t _value) { const bool b_changed = (this->H() != _value); this->m_size.cy = _value; return b_changed; }

uint32_t  CSize_U::Height (void) const { return this->H(); }
bool      CSize_U::Height (const uint32_t _value) { return this->H(_value); }

bool CSize_U::Is_zero (void) const {
	return (0 == this->H() || 0 == this->W());  // this is acceptable for a size of a shape; but not valid for a line, because it has a length;
}

#if defined(_DEBUG)
CString   CSize_U::Print (const e_print e_opt) const {
	e_opt;

	using pat = CPattern;

	CString cs_valid = TStringEx().Bool(this->Is_zero());
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pat::Get(e_opt), (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->H(), this->W(), (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pat::Get(e_opt), (_pc_sz) __CLASS__, this->H(), this->W(), (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == e_opt) { cs_out.Format(pat::Get(e_opt), this->H(), this->W()); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
size_u& CSize_U::Raw (void) const { return this->m_size; }
size_u& CSize_U::Raw (void)       { return this->m_size; }

bool    CSize_U::Set (const uint32_t _width, const uint32_t _height) {
	_width; _height;

	bool b_changed = false;

	if (this->H(_height)) b_changed = true;
	if (this->W(_width)) b_changed = true;

	return b_changed;
}

bool     CSize_U::Set (const t_rect& _rect) {
	return this->Set(__W(_rect), __H(_rect));
}

uint32_t CSize_U::W (void) const { return this->m_size.cx; }
bool     CSize_U::W (const uint32_t _value) { const bool b_changed = (this->W() != _value); if (b_changed) this->m_size.cx = _value; return b_changed; }

uint32_t CSize_U::Width (void) const { return this->W(); }
bool     CSize_U::Width (const uint32_t _value) { return this->W(_value); }

/////////////////////////////////////////////////////////////////////////////

CSize_U& CSize_U::operator = (const CSize_U& _src) { *this >> _src.H() << _src.W(); return *this; }
CSize_U& CSize_U::operator = (CSize_U&& _victim) {

	*this = _victim; _victim.Set(0,0); return *this;
}

CSize_U& CSize_U::operator <<(const uint32_t _width) { this->W(_width); return *this; }
CSize_U& CSize_U::operator >>(const uint32_t _height) { this->H(_height); return *this; }

CSize_U& CSize_U::operator <<(const t_rect& _rect) { this->Set(_rect); return *this; }

CSize_U::operator const size_u& (void) const { return this->Raw(); }
CSize_U::operator       size_u& (void)       { return this->Raw(); }

bool CSize_U::operator == (const CSize_U& _rsv) const { return (this->H() == _rsv.H() && this->W() == _rsv.W()); }
bool CSize_U::operator != (const CSize_U& _rsv) const { return (this->H() != _rsv.H() || this->W() != _rsv.W()); }

CSize_U& CSize_U::operator += (const CSize_U& _rsv) { this->Set(this->W() + _rsv.W(), this->H() + _rsv.H()); return *this; }
CSize_U& CSize_U::operator -= (const CSize_U& _rsv) { this->Set(this->W() - _rsv.W(), this->H() - _rsv.H()); return *this; }

/////////////////////////////////////////////////////////////////////////////

TSize   operator + (const TSize&  _lsv, const TSize&  _rsv) { return TSize (_lsv.W() + _rsv.W(), _lsv.H() + _rsv.H()); }
TSize   operator - (const TSize&  _lsv, const TSize&  _rsv) { return TSize (_lsv.W() - _rsv.W(), _lsv.H() - _rsv.H()); }

TSizeU  operator + (const TSizeU& _lsv, const TSizeU& _rsv) { return TSizeU(_lsv.W() + _rsv.W(), _lsv.H() + _rsv.H()); }
TSizeU  operator - (const TSizeU& _lsv, const TSizeU& _rsv) { return TSizeU(_lsv.W() - _rsv.W(), _lsv.H() - _rsv.H()); }

/////////////////////////////////////////////////////////////////////////////
#if (1)
CPosition:: CPosition (const TPoint& _anchor, const TSizeU& _size) { *this << _anchor << _size; }
CPosition:: CPosition (const CPosition& _src) : CPosition() { *this = _src; }
CPosition:: CPosition (CPosition&& _victim) : CPosition() { *this = _victim; }
#endif
/////////////////////////////////////////////////////////////////////////////
const
CPoint&     CPosition::Anchor (void) const { return this->m_anchor; }
CPoint&     CPosition::Anchor (void)       { return this->m_anchor; }
#if defined (_DEBUG)
CString     CPosition::Print  (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{anchor=%s;size=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{anchor=%s;size=%s}");
	static _pc_sz pc_sz_pat_r = _T("{anchor=%s;size=%s}");

	CString cs_anchor = this->Anchor().Print(e_print::e_req);
	CString cs_size_u = this->Size().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_anchor, (_pc_sz) cs_size_u);
	}
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,(_pc_sz) cs_anchor, (_pc_sz) cs_size_u); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_anchor, (_pc_sz) cs_size_u); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif
const
CSize_U&    CPosition::Size (void) const { return this->m_size; }
CSize_U&    CPosition::Size (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CPosition&  CPosition::operator = (const CPosition& _src) { *this << _src.Anchor() << _src.Size(); return *this; }

CPosition&  CPosition::operator = (CPosition&& _victim) { *this = (const CPosition&)_victim; return *this; }

CPosition&  CPosition::operator <<(const CPoint& _anchor) { this->Anchor() = _anchor; return *this; }
CPosition&  CPosition::operator <<(const t_point&  _pt) { this->Anchor() << _pt; return *this; }
CPosition&  CPosition::operator <<(const t_rect& _rect) {
	this->Anchor() << _rect.left >> _rect.top;
	this->Size() << _rect;
	return *this;
}
CPosition&  CPosition::operator <<(const CSize_U& _size_u) { this->Size() = _size_u; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPosition::operator const t_rect (void) const {
	return t_rect{
		this->Anchor().X(), this->Anchor().Y(), this->Anchor().X() + (int32_t)this->Size().W(), this->Anchor().Y() + (int32_t)this->Size().H()
	};
}