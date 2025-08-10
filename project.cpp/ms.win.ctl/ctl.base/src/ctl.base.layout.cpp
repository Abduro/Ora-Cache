/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 23:27:38.528, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control base layout interface implementation file;
*/
#include "ctl.base.layout.h"

using namespace ex_ui::controls::layout;

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace controls { namespace layout {

CImage:: CImage (void) : m_size{0}, m_anchor{0} {}
CImage:: CImage (const CImage& _src) : CImage() { *this = _src; }

const
t_point&   CImage::Anchor  (void) const { return this->m_anchor; }
t_point&   CImage::Anchor  (void)       { return this->m_anchor; }
bool       CImage::Anchor  (const int32_t _n_x, const int32_t _n_y) {
	_n_x; _n_y;
	const bool b_changed = this->Anchor().x != _n_x || this->Anchor().y != _n_y;

	if (b_changed) {
		this->Anchor().x = _n_x; this->Anchor().y = _n_y;
	}

	return b_changed;
}

const bool CImage::Is_valid(void) const { return (m_size.cx > 0 && m_size.cy > 0); }
const bool CImage::IsSquare(void) const { return (this->Is_valid() && m_size.cx == m_size.cy); }
const
CMargins&  CImage::Margins (void) const { return m_margins; }
CMargins&  CImage::Margins (void)       { return m_margins; }
#if defined(_DEBUG)
CString    CImage::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {anchor=%s;margins=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {anchor=%s;margins=%s;size=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("anchor=%s;margins=%s;size=%s;valid=%s");

	CString cs_anchor = TString().Format (_T("[w:%s|h:%d]"), this->Anchor().x, this->Anchor().y);
	CString cs_margins = this->Margins().Print(e_print::e_req);
	CString cs_size = TString().Format(_T("[cx:%d|cy:%d]"), this->Size().cx, this->Size().cy);
	CString cs_valid = TString().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a , (_pc_sz)__SP_NAME__,  (_pc_sz)__CLASS__,
		(_pc_sz) cs_anchor, (_pc_sz) cs_margins, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n , (_pc_sz)__CLASS__,
		(_pc_sz) cs_anchor, (_pc_sz) cs_margins, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r ,
		(_pc_sz) cs_anchor, (_pc_sz) cs_margins, (_pc_sz) cs_size, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
const
t_size&    CImage::Size  (void) const { return m_size; }
t_size&    CImage::Size  (void)       { return m_size; }

err_code   CImage::Size  (const HIMAGELIST _list) {
	_list;
	err_code n_result = __s_ok;

	if (nullptr == _list)
	return (n_result = __e_inv_arg);
	// https://learn.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-imagelist_geticonsize;
	const bool b_result = !!::ImageList_GetIconSize(_list, reinterpret_cast<PINT>(&m_size.cx), reinterpret_cast<PINT>(&m_size.cy));
	if (false == b_result)
		n_result = __e_fail;

	return n_result;
}

t_size     CImage::Total (void) const {
	return {
		this->Size().cx + this->Margins().Left() + this->Margins().Right(),
		this->Size().cy + this->Margins().Top () + this->Margins().Bottom()
	};
}

CImage&    CImage::operator = (const CImage& _src) { *this << _src.Margins() << _src.Size(); return *this; }
CImage&    CImage::operator <<(const CMargins& _margins) { this->Margins() = _margins; return *this; }
CImage&    CImage::operator <<(const t_point& _anchor) { this->Anchor() = _anchor; return *this; }
CImage&    CImage::operator <<(const t_size&  _size) { this->Size() = _size; return *this; }

}}}
/////////////////////////////////////////////////////////////////////////////

CGap:: CGap (const int16_t _n_id, const int16_t _n_value) : m_id(_n_id), m_value(_n_value) {}
CGap:: CGap (const CGap& _src) : CGap() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

int16_t  CGap::Id (void) const { return this->m_id; }
bool     CGap::Id (const int16_t _n_id) {
	_n_id;
	const bool b_changed = this->Id() != _n_id;

	if (b_changed)
		this->m_id = _n_id;

	return b_changed;
}

#if defined(_DEBUG)
CString  CGap::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{id=%d;value=%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{id=%d;value=%d}");
	static _pc_sz pc_sz_pat_r = _T("{id=%d;value=%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Id(), this->Value());
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Id(), this->Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Id(), this->Value()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

int16_t  CGap::Value (void) const { return this->m_value; }
bool     CGap::Value (const int16_t _n_value) {
	const bool b_changed = this->Value() != _n_value;
	if (b_changed)
		this->m_value = _n_value;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CGap&  CGap::operator = (const CGap& _src) { *this << _src.Id() >> _src.Value(); return *this; }
CGap&  CGap::operator <<(const int16_t _n_id) { this->Id(_n_id); return *this; }
CGap&  CGap::operator >>(const int16_t _n_value) { this->Value(_n_value); return *this; }

CGap::operator int16_t (void) const { return this->Value(); }

/////////////////////////////////////////////////////////////////////////////

CGapSet:: CGapSet (void) {} CGapSet:: CGapSet (const CGapSet& _src) : CGapSet () { *this = _src; }
CGapSet::~CGapSet (void) {} CGapSet:: CGapSet (CGapSet&& _victim) : CGapSet () { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////

bool  CGapSet::Is_zero (void) const {

	for (TRawGaps::const_iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_)
		if (!!it_->second.Value())
			return false;
	return true;
}

const
TRawGaps& CGapSet::Raw (void) const { return this->m_raw; }
TRawGaps& CGapSet::Raw (void)       { return this->m_raw; }

err_code  CGapSet::Set (const TRawGaps& _raw) {
	_raw;
	err_code n_result = __s_ok;
	try {
		if (this->Raw().empty() == false)
			this->Raw().clear();
		this->Raw() = _raw;
	} catch (const ::std::bad_alloc&) { n_result = __e_no_memory; }

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CGapSet& CGapSet::operator = (const CGapSet& _src) { *this << _src.Raw(); return *this; }
CGapSet& CGapSet::operator = (CGapSet&& _victim) { *this = (const CGapSet&)_victim; _victim.Raw().clear(); return *this; }
CGapSet& CGapSet::operator <<(const TRawGaps& _raw) { this->Set(_raw); return *this; }

/////////////////////////////////////////////////////////////////////////////
#if (0)
CMargin:: CMargin (const int16_t _n_id, const int16_t _n_value) : TBase(_n_id, _n_value) {}
CMargin:: CMargin (const CMargin& _src) : CMargin() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString   CMargin::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{id=%d;value=%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{id=%d;value=%d}");
	static _pc_sz pc_sz_pat_r = _T("{id=%d;value=%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TBase::Id(), TBase::Value());
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, TBase::Id(), TBase::Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, TBase::Id(), TBase::Value()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CMargin&  CMargin::operator = (const CMargin& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CMargin&  CMargin::operator <<(const int16_t _n_id) { TBase::Id(_n_id); return *this; }
CMargin&  CMargin::operator >>(const int16_t _n_value) { TBase::Value(_n_value); return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////
#if (0)
CMargins:: CMargins (void) : TBase() {} CMargins:: CMargins (const CMargins& _src) : CMargins () { *this = _src; }
CMargins::~CMargins (void) {}           CMargins:: CMargins (CMargins&& _victim) : CMargins () { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////

CMargins& CMargins::operator = (const CMargins& _src) { (TBase&)*this << _src.Raw(); return *this; }
CMargins& CMargins::operator = (CMargins&& _victim) { *this = (const CMargins&)_victim; _victim.Raw().clear(); return *this; }
CMargins& CMargins::operator <<(const TRawMargins& _raw) { this->Set(_raw); return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

CGaps_of_rect::CSides:: CSides (void) : m_selected(_part::e_top) {}
CGaps_of_rect::CSides:: CSides (const _part _selected) : CSides() { *this << _selected; }
CGaps_of_rect::CSides:: CSides (const CSides& _ref) : CSides() { *this = _ref; }
CGaps_of_rect::CSides::~CSides (void) {}

/////////////////////////////////////////////////////////////////////////////

bool  CGaps_of_rect::CSides::IsHorz (void) const { return this->Selected() == _part::e_bottom || this->Selected() == _part::e_top; }
bool  CGaps_of_rect::CSides::IsVert (void) const { return this->Selected() == _part::e_left || this->Selected() == _part::e_right; }

CGaps_of_rect::CSides::_part  CGaps_of_rect::CSides::Selected (void) const { return m_selected; }
CGaps_of_rect::CSides::_part& CGaps_of_rect::CSides::Selected (void)       { return m_selected; }

/////////////////////////////////////////////////////////////////////////////

CGaps_of_rect::CSides&  CGaps_of_rect::CSides::operator = (const CSides& _ref) { *this << _ref.Selected(); return *this; }
CGaps_of_rect::CSides&  CGaps_of_rect::CSides::operator <<(const _part _selected) { this->Selected() = _selected; return *this; }

/////////////////////////////////////////////////////////////////////////////

size_t   CGaps_of_rect::CSides::EnumToIndex(const CSides::_part _value) {
	_value;
	size_t ndx_ = static_cast<size_t>(_value);
	return ndx_;
}

CString  CGaps_of_rect::CSides::EnumToName (const CSides::_part _value) {
	_value;
	CString cs_name(_T("#Undef"));

	switch(_value) {
	case CSides::e_bottom: { cs_name = _T("Bottom"); } break;
	case CSides::e_left  : { cs_name = _T("Left");   } break;
	case CSides::e_right : { cs_name = _T("Right");  } break;
	case CSides::e_top   : { cs_name = _T("Top");    } break;
	}
	return cs_name;
}

CGaps_of_rect::CSides::_e CGaps_of_rect::CSides::IndexToEnum(const size_t _ndx) {
	_ndx;
	if (_ndx <= CSides::e_bottom)
		return static_cast<CSides::_e>(_ndx);
	else
		return CSides::e_top;
}

/////////////////////////////////////////////////////////////////////////////

CGaps_of_rect:: CGaps_of_rect (void) : TBase() {

	try {
		TBase::m_raw.insert(::std::make_pair(e_sides::e_left  , CMargin(e_sides::e_left  , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_top   , CMargin(e_sides::e_top   , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_right , CMargin(e_sides::e_right , 0)));
		TBase::m_raw.insert(::std::make_pair(e_sides::e_bottom, CMargin(e_sides::e_bottom, 0)));
	} catch (const ::std::bad_alloc&) { __e_no_memory; }

}

CGaps_of_rect:: CGaps_of_rect (const int16_t _left, const int16_t _top, const int16_t _right, const int16_t _bottom) : CGaps_of_rect() {
	this->Set(_left, _top, _right, _bottom);
}

CGaps_of_rect:: CGaps_of_rect (const CGaps_of_rect& _src)/* : CGaps_of_rect()*/ { *this = _src; }
CGaps_of_rect::~CGaps_of_rect (void) {}

/////////////////////////////////////////////////////////////////////////////

bool CGaps_of_rect::ApplyTo (t_rect& _rect) const {
	_rect;
	bool b_changed = false;

	if (TBase::Is_zero())
		return b_changed;

	if (!!this->Get(e_sides::e_left  ).Value()) { _rect.left   += this->Get(e_sides::e_left  ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_top   ).Value()) { _rect.top    += this->Get(e_sides::e_top   ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_right ).Value()) { _rect.right  += this->Get(e_sides::e_right ).Value(); b_changed = true; }
	if (!!this->Get(e_sides::e_bottom).Value()) { _rect.bottom += this->Get(e_sides::e_bottom).Value(); b_changed = true; }

	return b_changed;
}

const
CGap& CGaps_of_rect::Get(const e_sides _side) const {

	TRawGaps::const_iterator found = TBase::Raw().find(_side);
	if (found == TBase::Raw().end()) {
		static CGap inv_margin(0,0);
		return inv_margin;
	}
	else
		return found->second;
}
CGap& CGaps_of_rect::Get(const e_sides _side)  {

	TRawGaps::iterator found = TBase::Raw().find(_side);
	if (found == TBase::Raw().end()) {
		static CGap inv_margin(0,0);
		return inv_margin;
	}
	else
		return found->second;
}

#if defined(_DEBUG)
CString  CGaps_of_rect::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{left:%d;top:%d;right:%d;bottom:%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{left:%d;top:%d;right:%d;bottom:%d}");
	static _pc_sz pc_sz_pat_r = _T("{left:%d;top:%d;right:%d;bottom:%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		this->Get(e_sides::e_left).Value(), this->Get(e_sides::e_top).Value(), this->Get(e_sides::e_right).Value(), this->Get(e_sides::e_bottom).Value());
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CGaps_of_rect::Set (const int16_t _all) {
	return this->Set(_all, _all, _all, _all);
}

bool CGaps_of_rect::Set (const int16_t _left, const int16_t _top, const int16_t _right, const int16_t _bottom) {
	_left; _top; _right; _bottom;

	bool b_changed = false;

	if (this->Get(e_sides::e_left  ).Value(_left  )) { b_changed = true; }
	if (this->Get(e_sides::e_top   ).Value(_top   )) { b_changed = true; }
	if (this->Get(e_sides::e_right ).Value(_right )) { b_changed = true; }
	if (this->Get(e_sides::e_bottom).Value(_bottom)) { b_changed = true; }

	return b_changed;
}

int16_t CGaps_of_rect::Bottom (void) const { return this->Get(e_sides::e_bottom).Value(); }
bool    CGaps_of_rect::Bottom (const int16_t _value) { return this->Get(e_sides::e_bottom).Value(_value); }

int16_t CGaps_of_rect::Left (void) const { return this->Get(e_sides::e_left).Value(); }
bool    CGaps_of_rect::Left (const int16_t _value) { return this->Get(e_sides::e_left).Value(_value); }

int16_t CGaps_of_rect::Right (void) const { return this->Get(e_sides::e_right).Value(); }
bool    CGaps_of_rect::Right (const int16_t _value) { return this->Get(e_sides::e_right).Value(_value); }

int16_t CGaps_of_rect::Top (void) const { return this->Get(e_sides::e_top).Value(); }
bool    CGaps_of_rect::Top (const int16_t _value) { return this->Get(e_sides::e_top).Value(_value); }

/////////////////////////////////////////////////////////////////////////////

CGaps_of_rect&  CGaps_of_rect::operator = (const CGaps_of_rect& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace controls { namespace layout {

using CMargins = CMargins_of_rect;

}}}