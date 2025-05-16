/*
	Created by Tech_Dog (ebontrop@gmail.com) om 16-May-2025 at 12:59:06.222, UTC+4, Batumi, Friday;
	This is Ebo Pack 2D space geometry primitive shape line interface implementation file.
*/
#include "2d.shape.line.h"

using namespace geometry::shape::_2D;

/////////////////////////////////////////////////////////////////////////////

CLine:: CLine (const uint8_t _n_thickness) : TBase(), m_thick(_n_thickness) {}

const
TRgbQuad& CLine::Color (void) const { return this->m_color; }
TRgbQuad& CLine::Color (void)       { return this->m_color; }

bool   CLine::Is_valid (void) const { return TBase::Begin() != TBase::End(); }

uint32_t  CLine::Length(void) const {
	uint32_t n_result = 0;

	if (this->Is_valid() == false)
		return n_result;

	TPoint subs = TBase::End() - TBase::Begin();
	// it should be taking into account the most lines in 2D space GUI is horizontal or vertical, thus it should be checked first;
	if (false){}
	else if (subs.X() && 0 == subs.Y()) { // the landscape of the screen is used often, thus the horizontal is the first;
		n_result = (TBase::End().X() > TBase::Begin().X() ? TBase::End().X() - TBase::Begin().X() : TBase::Begin().X() - TBase::End().X());
	}
	else if (subs.Y() && 0 == subs.X()) { // the portrait position the next one, thus the vertical is the second;
		n_result = (TBase::End().Y() > TBase::Begin().Y() ? TBase::End().Y() - TBase::Begin().Y() : TBase::Begin().Y() - TBase::End().Y());
	}
	else if (subs.X() && subs.Y()) {
		const float f_x = (float)::std::pow(abs(subs.X()), 2);
		const float f_y = (float)::std::pow(abs(subs.Y()), 2);

		n_result = static_cast<uint32_t>(::std::sqrt(f_x + f_y));
	}
	return n_result;
}

#if defined(_DEBUG)
CString   CLine::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{line=%s,clr=%s,thick=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{line=%s,clr=%s,thick=%u}");
	static _pc_sz pc_sz_pat_r = _T("{line=%s,clr=%s,thick=%u}");

	CString cs_line  = TBase::Print(e_print::e_req);
	CString cs_clr   = this->Color().Print(e_print::e_req);
	CString cs_thick = TStringEx().Long(this->Thickness());

	CString cs_out;

	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, (_pc_sz) cs_line, (_pc_sz) cs_clr, (_pc_sz) cs_thick);
	}
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_line, (_pc_sz) cs_clr, (_pc_sz) cs_thick);
	}
	if (e_print::e_all == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_line, (_pc_sz) cs_clr, (_pc_sz) cs_thick); }

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

CLine& CLine::operator <<(const TRgbQuad& _clr) { this->Color() = _clr; return *this; }
CLine& CLine::operator <<(const uint8_t& _n_thick) { this->Thickness(_n_thick); return *this; } 