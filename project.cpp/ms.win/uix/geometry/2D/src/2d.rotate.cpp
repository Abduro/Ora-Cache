/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-May-2025 at 11:06:21.659, UTC+4, Batumi, Thursday;
	This is Ebo Pack 2D space geometry figure rotation interface implementation file.
*/
#include "2d.rotate.h"

using namespace geometry::_2D;

/////////////////////////////////////////////////////////////////////////////

using eRotDirect = CRotate::e_direct;

CRotate:: CRotate (void) : m_angle(0), m_direct(e_direct::e_cw) { this->m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CRotate::~CRotate (void) {}

/////////////////////////////////////////////////////////////////////////////

int16_t   CRotate::Angle (void) const { return this->m_angle; }  
bool      CRotate::Angle (const int16_t _degree) {
	_degree;
	const int16_t n_degree = _degree % 360;
	const bool b_changed = this->Angle() != n_degree;

	if (b_changed) {
		this->m_angle = n_degree;
		this->m_direct = n_degree < 0 ? e_direct::e_cw : e_direct::e_ccw;
	}

	return b_changed;
}

err_code  CRotate::ApplyTo (CLine& _line) const {
	_line;
	err_code n_result = __s_ok;

	if (false == _line.Is_valid()) {
		return this->m_error << __METHOD__ << (n_result = __e_inv_arg) = _T("Input line is not valid;");
	}

	this->ApplyTo(_line.Begin());
	this->ApplyTo(_line.End());

	return n_result;
}

err_code  CRotate::ApplyTo (CRect& _rect) const {
	_rect;
	err_code n_result = __s_ok;

	if (false == _rect.Is_valid()) {
		return this->m_error << __METHOD__ << (n_result = __e_inv_arg) = _T("Input rect/oblong is not valid;");
	}

	this->ApplyTo(_rect.Vertex(CRect::e_left_top));
	this->ApplyTo(_rect.Vertex(CRect::e_right_low));

	return n_result;
}

err_code  CRotate::ApplyTo (CShape& _shape) const {
	_shape;
	err_code n_result = __s_ok;

	if (false == _shape.Is_valid()) {
		return this->m_error << __METHOD__ << (n_result = __e_inv_arg) = _T("Input shape is not valid;");
	}

	for (uint32_t i_ = 0; i_ < _shape.Points().Count(); i_++) {
		this->ApplyTo(_shape.Points().Get(i_));
	}
	return n_result;
}

err_code  CRotate::ApplyTo (CPoint& _vertex) const {
	_vertex;
	err_code n_result = __s_ok;

	if (this->Angle() == 0)
		return n_result;

	CPoint cast = _vertex - this->Center();
	if (false) {}
	else if (- 90 == this->Angle()) { _vertex << +cast.Y() >> -cast.X(); return n_result; } //  cw;
	else if (+ 90 == this->Angle()) { _vertex << -cast.Y() >> +cast.X(); return n_result; } // ccw;
	else if (-180 == this->Angle()) { _vertex << -cast.X() >> -cast.Y(); return n_result; } // just the inversion of the coordinate values;
	else if (+180 == this->Angle()) { _vertex << -cast.X() >> -cast.Y(); return n_result; } // the same as above;
	else if (-270 == this->Angle()) { _vertex << -cast.Y() >> +cast.X(); return n_result; } // the same as to rotate to +90;
	else if (+270 == this->Angle()) { _vertex << +cast.Y() >> -cast.X(); return n_result; } // the same as to rotate to -90;

	const float rads = this->Angle() * M_PI/180;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/rotation ; the formula at the end of the article;
	/* x' = (x * cos(angle)) - (y * sin(angle)) 
	   y' = (x * sin(angle)) + (y * cos(angle)) 
	*/
#if (0)
	if (e_direct::e_ccw == this->Direct()) {
	_vertex.Set(
		static_cast<int32_t>((float(cast.X()) * ::std::cos((float)this->Angle())) - (float(cast.Y()) * ::std::sin((float)this->Angle()))),
		static_cast<int32_t>((float(cast.X()) * ::std::sin((float)this->Angle())) + (float(cast.Y()) * ::std::cos((float)this->Angle())))
	); } else {
	_vertex.Set(
		static_cast<int32_t>((float(cast.X()) * ::std::cos((float)this->Angle())) + (float(cast.Y()) * ::std::sin((float)this->Angle()))),
		static_cast<int32_t>((float(cast.X()) * ::std::sin((float)this->Angle())) - (float(cast.Y()) * ::std::cos((float)this->Angle())))
	); }
#else
	const float x_0 = float(cast.X()) * ::std::cos(rads);
	const float x_1 = float(cast.Y()) * ::std::sin(rads);
	const float y_0 = float(cast.X()) * ::std::sin(rads);
	const float y_1 = float(cast.Y()) * ::std::cos(rads);
//	if (e_direct::e_ccw == this->Direct()) {
	_vertex.Set(
		static_cast<int32_t>((float(cast.X()) * ::std::cos(rads)) - (float(cast.Y()) * ::std::sin(rads))),
		static_cast<int32_t>((float(cast.X()) * ::std::sin(rads)) + (float(cast.Y()) * ::std::cos(rads)))
	);// } else {
//	_vertex.Set(
//		static_cast<int32_t>((float(cast.X()) * ::std::cos(rads)) + (float(cast.Y()) * ::std::sin(rads))),
//		static_cast<int32_t>((float(cast.X()) * ::std::sin(rads)) - (float(cast.Y()) * ::std::cos(rads)))
//	);// }
#endif
	return n_result;
}

const
CPoint&    CRotate::Center (void) const { return this->m_center; }
CPoint&    CRotate::Center (void)       { return this->m_center; }

eRotDirect CRotate::Direct (void) const { return this->m_direct; }
#if (0)
bool CRotate::Direct (const e_direct _value) {
	const bool b_changed = (this->Direct() != _value);
	if (b_changed) {
		this->m_direct = _value;
	}
	return b_changed;
}
#endif
TError&    CRotate::Error (void) const { return this->m_error; }
#if defined (_DEBUG)
CString    CRotate::DirectAsText (void) const {

	CString cs_direct;
	if (false) {}
	else if (e_direct::e_cw  == this->Direct()) { cs_direct = _T("clockwise"); }
	else if (e_direct::e_ccw == this->Direct()) { cs_direct = _T("counter-cw"); }
	else { cs_direct = _T("#undef"); }
	return cs_direct;
}

CString    CRotate::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{center=%s;angle=%s;direct=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{center=%s;angle=%s;direct=%s}");
	static _pc_sz pc_sz_pat_r = _T("{center=%s;angle=%s;direct=%s}");

	CString cs_center = this->Center().Print(e_print::e_req);
	CString cs_angle  = TStringEx().Long(this->Angle());
	CString cs_direct = this->DirectAsText();
	
	CString cs_out;

	if (e_print::e_all   == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz) cs_center, (_pc_sz) cs_angle, (_pc_sz) cs_direct);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz) cs_center, (_pc_sz) cs_angle, (_pc_sz) cs_direct);
	}
	if (e_print::e_req   == e_opt) {
		cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_center, (_pc_sz) cs_angle, (_pc_sz) cs_direct);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////
#if (0)
CRotate&   CRotate::operator <<(const e_direct  _value) { this->Direct(_value); return *this; }
#endif
CRotate&   CRotate::operator <<(const CPoint&  _center) { this->Center() = _center; return *this; }
CRotate&   CRotate::operator <<(const int16_t   _angle) { this->Angle(_angle); return *this; }

CRotate&   CRotate::operator >>(CLine&  _line)  { this->ApplyTo(_line);  return *this; }
CRotate&   CRotate::operator >>(CPoint& _point) { this->ApplyTo(_point); return *this; }
CRotate&   CRotate::operator >>(CRect&  _rect)  { this->ApplyTo(_rect);  return *this; }
CRotate&   CRotate::operator >>(CShape& _shape) { this->ApplyTo(_shape); return *this; }