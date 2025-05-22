/*
	Created by Tech_Dog (ebontrop@gmail.com) om 17-May-2025 at 02:14:30.319, UTC+4, Batumi, Saturday;
	This is Ebo Pack 2D space geometry primitive shape rectangle interface declaration file.
*/
#include "2d.shape.rect.h"

using namespace geometry::_2D::shapes;

/////////////////////////////////////////////////////////////////////////////

namespace geometry { namespace _2D { namespace shapes { namespace _impl {


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
			cs_out += p_pt.Print(e_print::e_req);
			cs_out += _sfx;
		}
		return  cs_out;
	}

}}}}

using namespace geometry::_2D::shapes::_impl;

/////////////////////////////////////////////////////////////////////////////

COblong:: COblong (void) : TBase(COblong::u_vertices) {}
COblong:: COblong (const COblong& _src) : COblong() { *this = _src; }
COblong:: COblong (COblong&& _victim) : COblong() { *this = _victim; }
COblong::~COblong (void) {}

/////////////////////////////////////////////////////////////////////////////

CPoint COblong::Center (void) const {

	const CPoint& pt_l_t = this->Vertex(e_vertex::e_left_top);
	const CPoint& pt_r_l = this->Vertex(e_vertex::e_right_low);

	return CPoint(
		pt_r_l.X() > pt_l_t.X() ? pt_r_l.X() - pt_l_t.X() : pt_l_t.X() - pt_r_l.X(),
		pt_r_l.Y() > pt_l_t.Y() ? pt_r_l.Y() - pt_l_t.Y() : pt_l_t.Y() - pt_r_l.Y()
	);
}
const
TRgbQuad& COblong::Color (void) const { return this->m_color; }
TRgbQuad& COblong::Color (void)       { return this->m_color; }


CPoint COblong::Corner (const e_corners _e_corner) const {

	const CPoint& pt_l_t = this->Vertex(e_vertex::e_left_top);
	const CPoint& pt_r_l = this->Vertex(e_vertex::e_right_low);

	switch (_e_corner) {
	case e_corners::e_A: return CPoint(pt_l_t);
	case e_corners::e_B: return CPoint(pt_r_l.X(), pt_l_t.Y());
	case e_corners::e_C: return CPoint(pt_r_l);
	case e_corners::e_D: return CPoint(pt_l_t.X(), pt_r_l.Y());
	}
	static CPoint pt_inv;
	return pt_inv;
}

bool   COblong::Is_valid (void) const {
	return COblong:: u_vertices == TBase::Points().Count() && this->Vertex(e_vertex::e_left_top) != this->Vertex(e_vertex::e_right_low);
}

#if defined (_DEBUG)
CString      COblong::Print  (const e_print e_opt, _pc_sz _pfx, _pc_sz _sfx) const {
	e_opt; _pfx; _sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s;valid=%s;clr=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s;valid=%s;clr=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s;valid=%s;clr=%s}");

	CString cs_clr = this->Color().Print(e_print::e_req);
	CString cs_pts = TStringEx().Format(_T("l:%d|t:%d|r:%d|b:%d"),
		this->Vertex(e_vertex::e_left_top).X() , this->Vertex(e_vertex::e_left_top).Y(),
		this->Vertex(e_vertex::e_right_low).X(), this->Vertex(e_vertex::e_right_low).Y());

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_pts, (_pc_sz) cs_valid, (_pc_sz) cs_clr);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_pts, (_pc_sz) cs_valid, (_pc_sz) cs_clr);
	}
	if (e_print::e_req   == e_opt) {
		cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_pts, (_pc_sz) cs_valid, (_pc_sz) cs_clr);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

CSize COblong::Size (void) const {

//	const int32_t n_height = (((const COblong&)*this)[e_index::e_A].X() > ((const COblong&)*this)[e_index::e_D].X());

	const CPoint& pt_l_t = this->Vertex(e_vertex::e_left_top);
	const CPoint& pt_r_l = this->Vertex(e_vertex::e_right_low);

	const int32_t n_height = pt_r_l.Y() > pt_l_t.Y() ? pt_r_l.Y() - pt_l_t.Y() : pt_l_t.Y() - pt_r_l.Y();
	const int32_t n_width  = pt_r_l.X() > pt_l_t.X() ? pt_r_l.X() - pt_l_t.X() : pt_l_t.X() - pt_r_l.X();

//	const int32_t n_height = (
//		this->Corners().A().X() > this->Corners().D().X() ? this->Corners().A().X() - this->Corners().D().X() : this->Corners().D().X() > this->Corners().A().X()
//	) / 2;

	return CSize(n_width, n_height);
}

const
CPoint&  COblong::Vertex (const e_vertex _vertex) const {
	if (e_vertex::e_left_top  == _vertex) return TBase::Points().Get(0);
	if (e_vertex::e_right_low == _vertex) return TBase::Points().Get(1);

	return _get_invalid_point();
}
CPoint&  COblong::Vertex (const e_vertex _vertex) {
	if (e_vertex::e_left_top  == _vertex) return TBase::Points().Get(0);
	if (e_vertex::e_right_low == _vertex) return TBase::Points().Get(1);

	return _get_invalid_point();
}

/////////////////////////////////////////////////////////////////////////////

COblong& COblong::operator = (const COblong& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
COblong& COblong::operator = (COblong&& _victim) {
	*this = (const COblong&)_victim; ((COblong&)_victim).Points().Count(0);
	return *this;
}

COblong& COblong::operator <<(const CPoint& _left_up)   { this->Vertex(e_vertex::e_left_top) = _left_up; return *this; }
COblong& COblong::operator >>(const CPoint& _right_low) { this->Vertex(e_vertex::e_right_low) = _right_low; return *this; }