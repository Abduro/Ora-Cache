/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-May-2025 at 11:46:26.845, UTC+4, Batumi, Tuesday;
	This is Ebo Pack user control base pane interface implementation file;
*/
#include "ctl.base.pane.h"

using namespace ex_ui::controls;

namespace ex_ui { namespace controls { namespace pane {
/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (void) : CFmtBase(), m_img_ndx(-1) {}
CFormat:: CFormat (const CFormat& _src) : CFormat () { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

int32_t   CFormat::Image_Ndx (void) const { return this->m_img_ndx; }
bool      CFormat::Image_Ndx (const int32_t _n_ndx) {
	_n_ndx;
	const bool b_changed = this->Image_Ndx() != _n_ndx; if (b_changed) this->m_img_ndx = _n_ndx; return b_changed;
}
#if defined(_DEBUG)
CString   CFormat::Print(const e_print _e_opt/* = e_print::e_all*/, _pc_sz _p_pfx/* = _T("\t\t")*/, _pc_sz _p_sfx/* = _T("\n")*/) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {img_ndx=%s;%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {img_ndx=%s;%s}");
	static _pc_sz pc_sz_pat_r = _T("img_ndx=%s;%s");

	CString cs_base = CFmtBase::Print(e_print::e_req, _p_pfx, _p_sfx);
	CString cs_ndx  = 0 > this->Image_Ndx() ? _T("#not_set") : TStringEx().Long(this->Image_Ndx());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return cs_out;
}
#endif

CFormat&  CFormat::operator = (const CFormat& _src) { (*this)() = _src(); *this << _src.Image_Ndx(); return *this; }
CFormat&  CFormat::operator <<(const int32_t _img_ndx) { this->Image_Ndx(_img_ndx); return *this; }
const
CFmtBase& CFormat::operator ()(void) const { return (const CFmtBase&)*this; }
CFmtBase& CFormat::operator ()(void)       { return (      CFmtBase&)*this; }

CFormat::operator const int32_t (void) const { return this->Image_Ndx(); }

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (void) : m_rect{0} {}
CLayout:: CLayout (const CLayout& _src) : CLayout() { *this = _src; }

const
CAlign&   CLayout::Align  (void) const { return m_align; }
CAlign&   CLayout::Align  (void)       { return m_align; }

const
ex_ui::controls::layout::CImage&   CLayout::Image  (void) const { return m_image; }
ex_ui::controls::layout::CImage&   CLayout::Image  (void)       { return m_image; }

#if defined(_DEBUG)
CString   CLayout::Print(const e_print _e_opt/*= e_print::e_all*/) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {align=%s;pos=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {align=%s;pos=%s}");
	static _pc_sz pc_sz_pat_r = _T("align=%s;pos=%s");

	CString cs_align = this->Align().Print(e_print::e_req);
#if (0)
	CString cs_pos = this->Position().Print(e_print::e_req);
#else
	CString cs_pos = _T("#undef");
#endif
	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_align, (_pc_sz) cs_pos); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_align, (_pc_sz) cs_pos); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_align, (_pc_sz) cs_pos); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
t_rect&   CLayout::Rect (void) const { return m_rect ; }
t_rect&   CLayout::Rect (void)       { return m_rect ; }

bool CLayout::Update (void) { return false; }
bool CLayout::Update (const t_rect& _rect_of_place) { _rect_of_place; return false; }

CLayout&  CLayout::operator = (const CLayout& _src) { *this << _src.Align() << _src.Image() << _src.Rect(); return *this; }

CLayout&  CLayout::operator <<(const CAlign& _align) { this->Align() = _align; return *this; }
CLayout&  CLayout::operator <<(const ex_ui::controls::layout::CImage& _image) { this->Image() = _image; return *this; }
CLayout&  CLayout::operator <<(const t_rect& _rect) { this->Rect() = _rect; return *this; }

}}}

using CFormat = CPane::CFormat;
using CLayout = CPane::CLayout;
/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (CPane& _pane) : CFmtBase(), m_pane(_pane), m_img_ndx(-1) {}
CFormat:: CFormat (const CFormat& _src) : CFormat (const_cast<CPane&>(_src.Pane())) { *this = _src; }

int32_t   CFormat::Image_Ndx (void) const { return this->m_img_ndx; }
bool      CFormat::Image_Ndx (const int32_t _n_ndx) {
	const bool b_changed = this->Image_Ndx() != _n_ndx; if (b_changed) this->m_img_ndx = _n_ndx; return b_changed;
}

const
CPane&    CFormat::Pane (void) const { return this->m_pane; }
CPane&    CFormat::Pane (void)       { return this->m_pane; }
#if defined(_DEBUG)
CString   CFormat::Print(const e_print _e_opt/* = e_print::e_all*/, _pc_sz _p_pfx/* = _T("\t\t")*/, _pc_sz _p_sfx/* = _T("\n")*/) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {img_ndx=%s;%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {img_ndx=%s;%s}");
	static _pc_sz pc_sz_pat_r = _T("img_ndx=%s;%s");

	CString cs_base = CFmtBase::Print(e_print::e_req, _p_pfx, _p_sfx);
	CString cs_ndx  = 0 > this->Image_Ndx() ? _T("#not_set") : TStringEx().Long(this->Image_Ndx());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_ndx, (_pc_sz) cs_base); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return cs_out;
}
#endif
CFormat&  CFormat::operator = (const CFormat& _src) { (CFmtBase&)*this = (const CFmtBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CPane& _pane) : m_pane(_pane), m_rect{0} {}
CLayout:: CLayout (const CLayout& _src) : CLayout(const_cast<CPane&>(_src.Pane())) { *this = _src; }

const
CAlign&   CLayout::Align  (void) const { return m_align; }
CAlign&   CLayout::Align  (void)       { return m_align; }
const
ex_ui::controls::layout::CImage&   CLayout::Image  (void) const { return m_image; }
ex_ui::controls::layout::CImage&   CLayout::Image  (void)       { return m_image; }
const
CPane&    CLayout::Pane (void) const { return this->m_pane; }
CPane&    CLayout::Pane (void)       { return this->m_pane; }
#if (0)
const
CPosition& CLayout::Pos (void) const { return this->Position(); }
CPosition& CLayout::Pos (void)       { return this->Position(); }

const
CPosition& CLayout::Position (void) const { return this->m_position; }
CPosition& CLayout::Position (void)       { return this->m_position; }
#endif
#if defined(_DEBUG)
CString   CLayout::Print(const e_print _e_opt/*= e_print::e_all*/) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {align=%s;pos=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {align=%s;pos=%s}");
	static _pc_sz pc_sz_pat_r = _T("align=%s;pos=%s");

	CString cs_align = this->Align().Print(e_print::e_req);
#if (0)
	CString cs_pos = this->Position().Print(e_print::e_req);
#else
	CString cs_pos = _T("#undef");
#endif
	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_align, (_pc_sz) cs_pos); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_align, (_pc_sz) cs_pos); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_align, (_pc_sz) cs_pos); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
t_rect&   CLayout::Rect (void) const { return m_rect ; }
t_rect&   CLayout::Rect (void)       { return m_rect ; }

bool CLayout::Update (void) {
//	return this->m_pane.Format().Borders().Set(this->Position());
	return false;
}

bool CLayout::Update (const t_rect& _rect_of_place) {
	_rect_of_place;
//	this->Position() << _rect_of_place;
	return this->Update();
}

CLayout&  CLayout::operator = (const CLayout& _src) { *this << _src.Align()/* << _src.Position()*/; return *this; }

CLayout&  CLayout::operator <<(const CAlign& _align) { this->Align() = _align; return *this; }
#if (0)
CLayout&  CLayout::operator <<(const CPosition& _pos) { this->Pos() = _pos; return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) : m_format(*this), m_layout(*this)  {} CPane:: CPane (CPane&& _victim) : CPane() { *this = _victim; }
CPane:: CPane (const CPane& _src) : CPane() { *this = _src; }
CPane::~CPane (void) {}

/////////////////////////////////////////////////////////////////////////////
#if (0)
const
CBorders& CPane::Borders (void) const { return this->m_borders; }
CBorders& CPane::Borders (void)       { return this->m_borders; }
#endif
const
CFormat&  CPane::Format  (void) const { return this->m_format ; }
CFormat&  CPane::Format  (void)       { return this->m_format ; }
const
CLayout&  CPane::Layout  (void) const { return this->m_layout ; }
CLayout&  CPane::Layout  (void)       { return this->m_layout ; }

err_code  CPane::Draw (const HDC _hdc, const t_rect& _drw_area) const {
	_hdc; _drw_area;
	err_code n_result = __s_ok;

	const t_rect drw_area = {0}; // this->Layout().Position();

	CZBuffer z_buffer(_hdc, drw_area);

	if (z_buffer.Is_valid() == false)
		return (n_result = z_buffer.Error());

	// (1) draws the background first;
	const TRgbQuad& bkg_ = this->Format().Bkgnd().Solid();
	if (bkg_.Is() && bkg_.A() != 0) { // alpha value must be checked too;
		n_result = z_buffer.Draw(drw_area, bkg_);
	}

	using e_sides = ex_ui::controls::layout::CGaps_of_rect::e_sides;
	using CBorder = ex_ui::controls::borders::CBorder;

	for (int16_t i_ = 0; i_ <= e_sides::e_bottom; i_++) { // border set for rectangular area is expected, but nevertheless;

		const CBorder& border = this->Format().Borders().Get(static_cast<e_sides>(i_));

		if (border.IsClear())
			continue;

		n_result = z_buffer.Draw(border);
		if (__failed(n_result))
			break;
	}

	return  n_result;
}

#if defined(_DEBUG)
CString   CPane::Print(const e_print _e_opt/* = e_print::e_all*/, _pc_sz _p_pfx/* = _T("\t\t")*/, _pc_sz _p_sfx/* = _T("\n")*/) const {
	_e_opt; _p_pfx; _p_sfx;
#if (0)
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%sborders:%s;%s%sformat:%s%s%s;%s%slayout:%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {borders=%s;format=%s;layout=%s}");
	static _pc_sz pc_sz_pat_r = _T("borders=%s;format=%s;layout=%s");

	CString cs_borders = this->Borders().Print(e_print::e_req, _p_pfx, _p_sfx);
#else
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%sformat:%s;%s%slayout:%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {format:%s;layout:%s}");
	static _pc_sz pc_sz_pat_r = _T("format:%s;layout:%s");
#endif
	CString cs_format  = this->Format().Print(e_print::e_no_ns, _p_pfx, _p_sfx);
	CString cs_layout  = this->Layout().Print(e_print::e_req);

	CString cs_out;
	if (e_print::e_all == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_format , // moves the format info section to the new line with the indent;
		_p_sfx, _p_pfx, (_pc_sz) cs_layout);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_format, (_pc_sz) cs_layout); }
	if (e_print::e_req == _e_opt) { cs_out.Format (pc_sz_pat_r, (_pc_sz) cs_format, (_pc_sz) cs_layout); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CPane&  CPane::operator = (const CPane& _src) { *this << /*_src.Borders() <<*/ _src.Format() << _src.Layout(); return *this; }
CPane&  CPane::operator = (CPane&& _victim) { *this = (const CPane&)_victim; return *this; }
#if (0)
CPane&  CPane::operator <<(const CBorders& _borders) { this->Borders() = _borders; return *this; }
#endif
CPane&  CPane::operator <<(const CFormat& _format) { this->Format() = _format; return *this; }
CPane&  CPane::operator <<(const CLayout& _layout) { this->Layout() = _layout; return *this; }