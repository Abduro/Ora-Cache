/*
	Created by Tech_Dog (ebontrop@gmail.com) om 16-May-2025 at 12:59:06.222, UTC+4, Batumi, Friday;
	This is Ebo Pack 2D space geometry base primitive line interface implementation file.
*/
#include "2d.base.line.h"

using namespace geometry::_2D::base;

/////////////////////////////////////////////////////////////////////////////

CLine:: CLine (const uint8_t _n_thickness) : m_thick(_n_thickness) {
	this->Color().Is() = false;
}

/////////////////////////////////////////////////////////////////////////////
const
CPoint& CLine::Begin(void) const { return this->Point(e_points::e_begin); }
CPoint& CLine::Begin(void)       { return this->Point(e_points::e_begin); }
const
TRgbQuad& CLine::Color (void) const { return this->m_color; }
TRgbQuad& CLine::Color (void)       { return this->m_color; }
const
CPoint& CLine::End (void)  const { return this->Point(e_points::e_end); }
CPoint& CLine::End (void)        { return this->Point(e_points::e_end); }

bool   CLine::Is_horz  (void) const { return this->Begin().X() == this->End().X(); }
bool   CLine::Is_valid (void) const { return this->Begin()     != this->End(); }
bool   CLine::Is_vert  (void) const { return this->Begin().Y() == this->End().Y(); }

uint32_t CLine::Length (void) const {
	uint32_t n_result = 0;

	if (this->Is_valid() == false)
		return n_result;

	TPoint subs = this->End() - this->Begin();
	// it should be taking into account the most lines in 2D space GUI is horizontal or vertical, thus it should be checked first;
	if (false){}
	else if (subs.X() && 0 == subs.Y()) { // the landscape of the screen is used often, thus the horizontal is the first;
		n_result = (this->End().X() > this->Begin().X() ? this->End().X() - this->Begin().X() : this->Begin().X() - this->End().X());
	}
	else if (subs.Y() && 0 == subs.X()) { // the portrait position the next one, thus the vertical is the second;
		n_result = (this->End().Y() > this->Begin().Y() ? this->End().Y() - this->Begin().Y() : this->Begin().Y() - this->End().Y());
	}
	else if (subs.X() && subs.Y()) {
		const float f_x = (float)::std::pow(abs(subs.X()), 2);
		const float f_y = (float)::std::pow(abs(subs.Y()), 2);

		n_result = static_cast<uint32_t>(::std::sqrt(f_x + f_y));
	}
	return n_result;
}

CPoint   CLine::Middle (void) const {

	const int32_t n_x = (this->Begin().X() > this->End().X() ? this->Begin().X() - this->End().X() : this->End().X() - this->Begin().X()  ) / 2;
	const int32_t n_y = (this->Begin().Y() > this->End().Y() ? this->Begin().Y() - this->End().Y() : this->End().Y() - this->Begin().Y()  ) / 2;

	return CPoint(n_x, n_y);
}

const
CPoint&   CLine::Point (const e_points _index) const { return this->m_points[_index]; }
CPoint&   CLine::Point (const e_points _index)       { return this->m_points[_index]; }

#if defined(_DEBUG)
CString   CLine::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{begin=%s;end=%s;len=%spx;thick=%spx;clr=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{begin=%s;end=%s;len=%spx;thick=%spx;clr=%s}");
	static _pc_sz pc_sz_pat_r = _T("{begin=%s;end=%s;len=%spx;thick=%spx;clr=%s}");

	CString cs_begin = this->Begin().Print(e_print::e_req);
	CString cs_end   = this->End().Print(e_print::e_req);
	CString cs_clr   = this->Color().Print(e_print::e_req);
	CString cs_thick = TStringEx().Long(this->Thickness());
	CString cs_len   = TStringEx().Long(this->Length());

	CString cs_out;

	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__,
		(_pc_sz) cs_begin, (_pc_sz) cs_end, (_pc_sz) cs_len, (_pc_sz) cs_thick, (_pc_sz) cs_clr);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__,
		(_pc_sz) cs_begin, (_pc_sz) cs_end, (_pc_sz) cs_len, (_pc_sz) cs_thick, (_pc_sz) cs_clr);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz) cs_begin, (_pc_sz) cs_end, (_pc_sz) cs_len, (_pc_sz) cs_thick, (_pc_sz) cs_clr);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

uint8_t  CLine::Thickness (void) const { return this->m_thick; }
bool     CLine::Thickness (const uint8_t _n_value) {
	const bool b_changed = this->Thickness() != _n_value;

	if (b_changed)
		this->m_thick = _n_value;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CLine&  CLine::operator <<(const TRgbQuad& _clr) { this->Color() = _clr; return *this; }
CLine&  CLine::operator <<(const uint8_t& _n_thick) { this->Thickness(_n_thick); return *this; }

CLine&  CLine::operator <<(const CPoint& _begin) { this->Begin() = _begin; return *this; }
CLine&  CLine::operator >>(const CPoint& _end) { this->End() = _end; return *this; }

CLine&  CLine::operator = (const CLine& _src) {
	*this << _src.Begin() >> _src.End() << _src.Thickness() << _src.Color(); return *this;
}