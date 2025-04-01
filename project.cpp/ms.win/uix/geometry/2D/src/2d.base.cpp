/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 22:07:50.118, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry fundamental objects' interface implementation file.
*/
#include "2d.base.h"

using namespace geometry::base::_2D;

/////////////////////////////////////////////////////////////////////////////

CMarker:: CMarker (void) : m_id (0), m_tag(_T("#undef")), m_valid(false) {} // possibly it is not good way for initialization of this object, but is okay for now;
CMarker:: CMarker (const uint32_t _u_id, _pc_sz _p_tag, const bool _b_valid) : CMarker() { *this << _u_id << _p_tag << _b_valid; }
CMarker:: CMarker (const CMarker& _src) : CMarker() { *this = _src; }
CMarker::~CMarker (void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CMarker::Id (void) const { return this->m_id; }
bool      CMarker::Id (const uint32_t _value) { const bool b_changed = (this->Id() != _value); if (b_changed) this->m_id = _value; return b_changed; }

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
		cs_out.Format(_T("cls::[%s].%s(#inv_arg==%d);"), (_pc_sz) __CLASS__, (_pc_sz) __METHOD__, e_opt);

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

CPoints:: CPoints (void) {}
CPoints:: CPoints (const CPoints& _src) : CPoints() { *this = _src; }
CPoints:: CPoints (CPoints&& _victim) : CPoints() { *this = _victim; }
CPoints::~CPoints (void) {}

/////////////////////////////////////////////////////////////////////////////
const
t_raw_pts& CPoints::Raw (void) const { return this->m_points; }
t_raw_pts& CPoints::Raw (void)       { return this->m_points; }

#if defined(_DEBUG)

CString CPoints::Print (void) const {

	static _pc_sz pc_sz_pat_e = _T("cls::[%s]>>elements={%s}");

	CString cs_out;
	CString cs_pts;

	const size_t b_last = (this->Raw().size() > 1 ? this->Raw().size() - 1 : 0);

	for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {

		cs_pts += this->Raw().at(i_).Print(TPoint::e_req);
		if (i_ < b_last)
			cs_pts += _T(";");

	}
	if (this->Raw().empty()) {
		cs_pts = _T("#empty");
		
	}
	cs_out.Format(pc_sz_pat_e, (_pc_sz)__CLASS__, (_pc_sz)cs_pts);
	return  cs_out;
}

#endif
/////////////////////////////////////////////////////////////////////////////

CPoints&  CPoints::operator = (const CPoints& _src) { this->Raw() = _src.Raw(); return *this; }
CPoints&  CPoints::operator = (CPoints&& _victim) {
	*this = _victim; _victim.Raw().clear(); return *this; // no swap is used yet;
}

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

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->X(), this->Y(), (_pc_sz) this->Marker().Print(CMarker::e_req)); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, this->X(), this->Y(), (_pc_sz) this->Marker().Print(CMarker::e_req)); }
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, this->X(), this->Y(), (_pc_sz) this->Marker().Print(CMarker::e_req)); }

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

namespace geometry { namespace base { namespace _2D { namespace _impl {

#if defined(_DEBUG)
	using e_print = TSize::e_print;

	class CPattern {
	public:
		 CPattern (void) {} CPattern (const CPattern&) = delete; CPattern (CPattern&&) = delete;
		~CPattern (void) {}

	public:
		static _pc_sz Get (const uint16_t _e_opt) {

			static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{height=%d;width=%d;zero=%s}");
			static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{height=%d;width=%d;zero=%s}");
			static _pc_sz pc_sz_pat_r = _T("{height=%d;width=%d}");

			if (e_print::e_all == _e_opt) return pc_sz_pat_a;
			if (e_print::e_no_ns == _e_opt) return pc_sz_pat_n;
			if (e_print::e_req == _e_opt) return pc_sz_pat_r;

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
using namespace geometry::base::_2D::_impl;

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

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->H(), this->W(), TStringEx().Bool(this->Is_zero())); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __CLASS__, this->H(), this->W(), TStringEx().Bool(this->Is_zero())); }
	if (e_print::e_req == e_opt) { cs_out.Format(pat::Get(e_opt), this->H(), this->W()); }

	if (cs_out.IsEmpty())
		cs_out.Format(pat::Get(0xf), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

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

bool CSize_U::Is_zero (void) const { return (!this->H() && !this->W()); }

#if defined(_DEBUG)
CString   CSize_U::Print (const e_print e_opt) const {
	e_opt;

	using pat = CPattern;

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->H(), this->W(), TStringEx().Bool(this->Is_zero())); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pat::Get(e_opt), (_pc_sz) __CLASS__, this->H(), this->W(), TStringEx().Bool(this->Is_zero())); }
	if (e_print::e_req == e_opt) { cs_out.Format(pat::Get(e_opt), this->H(), this->W()); }

	if (cs_out.IsEmpty())
		cs_out.Format(pat::Get(0xf), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

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