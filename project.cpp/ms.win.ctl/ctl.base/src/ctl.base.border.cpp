/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-May-2012 at 9:36:22am, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Project Shared Skinned Control Base class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack project on 25-Nov-2020 at 6:46:50.364 pm, UTC+7, Novosibirsk, Wednesday;
*/
#include "ctl.base.border.h"

using namespace ex_ui::controls::borders;

/////////////////////////////////////////////////////////////////////////////

COne:: COne (int16_t _n_id) : TBase() { *this << _n_id; }
COne:: COne (const COne& _src) : COne() { *this = _src; }
COne:: COne (COne&& _victim) : COne() { *this = _victim;}
COne::~COne (void) {}

/////////////////////////////////////////////////////////////////////////////

int16_t COne::Id (void) const { return this->m_Id; }
bool    COne::Id (const int16_t _n_id) {
	const bool b_changed = (_n_id != this->Id());
	if (b_changed)
		this->m_Id = _n_id;

	return b_changed;
}

const bool COne::IsClear  (void) const {
	return false == TBase::Color().Is() || 0 == TBase::Color().A() || 0 == TBase::Thickness() || false == TBase::Is_valid();
}
const bool COne::IsLimpid (void) const { return this->IsClear(); }
#if (0)
const
CMargin& COne::Margin (void) const { return this->m_margin; }
CMargin& COne::Margin (void)       { return this->m_margin; }
#endif
#if defined(_DEBUG)
CString  COne::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{id=%d;line=%s;is_clear=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{id=%d;line=%s;is_clear=%s}");
	static _pc_sz pc_sz_pat_r = _T("{id=%d;line=%s;is_clear=%s}");

	CString cs_line = TBase::Print(e_print::e_req);
	CString cs_clear = TStringEx().Bool(this->IsClear());

	CString cs_out;

	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__, (_pc_sz) __CLASS__, this->Id(), (_pc_sz) cs_line, (_pc_sz) cs_clear);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, this->Id(), (_pc_sz) cs_line, (_pc_sz) cs_clear); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Id(), (_pc_sz) cs_line, (_pc_sz) cs_clear); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

COne& COne::operator = (const COne& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Id(); return *this;}
COne& COne::operator = (COne&& _victim) { *this = (const COne&)_victim; return *this; }
#if (0)
COne& COne::operator <<(const CMargin& _margin) { this->Margin() = _margin; return *this; }
#else
COne& COne::operator <<(const int16_t _n_id) { this->Id(_n_id); return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

CSet:: CSet (void) {}
CSet:: CSet (const CSet& _src) : CSet() { *this = _src; }
CSet:: CSet (CSet&& _victim) : CSet() { *this= _victim; }
CSet::~CSet (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CSet::Add (const COne& _border) {
	_border;
	TRawBorders::const_iterator it_ = this->Raw().find(_border.Id());
	if (it_ != this->Raw().end())
		return (err_code) TErrCodes::eObject::eExists;

	try {
		this->Raw().insert(::std::make_pair(_border.Id(), _border));
	} catch (const ::std::bad_alloc&) { return __e_no_memory; }

	return __s_ok;
}

bool   CSet::Color (const TRgbQuad& _clr) {
	_clr;
	bool b_changed = false;

	for (TRawBorders::iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_) {
		if (it_->second.Color() != _clr) {
			it_->second.Color()  = _clr;
			b_changed = true;
		}
	}

	return b_changed;
}
const
COne&  CSet::Get (const uint16_t _n_id) const {
	_n_id;
	TRawBorders::const_iterator it_ = this->Raw().find(_n_id);
	if (it_ != this->Raw().end())
		return it_->second;
	static COne brd_inv;
	return brd_inv;
}

COne&  CSet::Get (const uint16_t _n_id) {
	_n_id;
	TRawBorders::iterator it_ = this->Raw().find(_n_id);
	if (it_ != this->Raw().end())
		return it_->second;
	static COne brd_inv;
	return brd_inv;
}

err_code  CSet::Rem (const uint16_t _n_id) {
	_n_id;
	TRawBorders::iterator it_ = this->Raw().find(_n_id);
	if (it_ == this->Raw().end())
		return (err_code) TErrCodes::eData::eNotFound;

	try {
		this->Raw().erase(it_);
	} catch (const ::std::bad_alloc&) { return __e_no_memory; }

	return __s_ok;
}

#if defined(_DEBUG)
CString   CSet::Print (const e_print _e_opt, _pc_sz _pfx, _pc_sz _sfx) const {
	_e_opt; _pfx; _sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::%s>>{%s}");
	static _pc_sz pc_sz_pat_r = _T("%s");

	CString cs_brds;
	if (this->Raw().size()) {
		for (TRawBorders::const_iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_) {
			if (cs_brds.IsEmpty() == false || true) { // always set new line;
				cs_brds += _sfx;
				cs_brds += _pfx;
			}
			cs_brds += it_->second.Print(e_print::e_req);
		}
	}
	else
		cs_brds = _T("#empty");

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz) __SP_NAME__,  (_pc_sz) __CLASS__,
		_sfx, _pfx, (_pc_sz) cs_brds,
		_sfx, _pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz) __CLASS__, (_pc_sz) cs_brds); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_brds); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawBorders& CSet::Raw (void) const { return this->m_borders; }
TRawBorders& CSet::Raw (void)       { return this->m_borders; }

bool   CSet::Thickness (const uint8_t _u_value) {
	_u_value;
	bool b_changed = false;

	for (TRawBorders::iterator it_ = this->Raw().begin(); it_ != this->Raw().end(); ++it_) {
		if (it_->second.Thickness(_u_value))
			b_changed = true;
	}

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CSet&  CSet::operator = (const CSet& _src) { *this << _src.Raw(); return *this;}
CSet&  CSet::operator = (CSet&& _victim) {
	*this = (const CSet&)_victim; ((CSet&)_victim).Raw().clear(); return *this;
}

CSet&  CSet::operator <<(const TRawBorders& _raw) { this->Raw() = _raw; return *this; }
CSet&  CSet::operator <<(const TRgbQuad& _color) { this->Color(_color); return *this; }

CSet&  CSet::operator <<(const uint8_t _n_thickness) {
	this->Thickness(_n_thickness); return *this;
}

CSet&  CSet::operator +=(const CBorder& _border) { this->Add(_border); return *this; }
CSet&  CSet::operator -=(const uint16_t _n_id) { this->Rem(_n_id); return *this; }

const
COne&  CSet::operator [](const uint16_t _n_id) const { return this->Get(_n_id); }
COne&  CSet::operator [](const uint16_t _n_id)       { return this->Get(_n_id); }

/////////////////////////////////////////////////////////////////////////////

CSet_for_rect:: CSet_for_rect (void) : TBase() {
	TBase::Add(COne(e_sides::e_left  ));
	TBase::Add(COne(e_sides::e_top   ));
	TBase::Add(COne(e_sides::e_right ));
	TBase::Add(COne(e_sides::e_bottom));
}
CSet_for_rect::~CSet_for_rect (void) {}

/////////////////////////////////////////////////////////////////////////////

const
CBorder& CSet_for_rect::Get (const e_sides _e_side) const { return TBase::Get(_e_side); }
CBorder& CSet_for_rect::Get (const e_sides _e_side)       { return TBase::Get(_e_side); }

const
CBorder& CSet_for_rect::Bottom (void) const { return this->Get(e_sides::e_bottom); }
CBorder& CSet_for_rect::Bottom (void)       { return this->Get(e_sides::e_bottom); }

const
CBorder& CSet_for_rect::Left (void) const { return this->Get(e_sides::e_left); }
CBorder& CSet_for_rect::Left (void)       { return this->Get(e_sides::e_left); }

const
CBorder& CSet_for_rect::Right (void) const { return this->Get(e_sides::e_right); }
CBorder& CSet_for_rect::Right (void)       { return this->Get(e_sides::e_right); }

const
CBorder& CSet_for_rect::Top (void) const { return this->Get(e_sides::e_top); }
CBorder& CSet_for_rect::Top (void)       { return this->Get(e_sides::e_top); }

bool  CSet_for_rect::Set (const t_rect& _rect) {
	_rect;
	bool b_changed = false;

#define u_use_case 2

	// https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum ;
	static const e_sides e_all[] = { e_sides::e_left, e_sides::e_top, e_sides::e_right, e_sides::e_bottom};

#if u_use_case == 1
	
	// https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp ;
	// https://en.cppreference.com/w/cpp/language/lambda.html ;
	
	::std::for_each (::std::begin(e_all), ::std::end(e_all),
			[this, &_rect, &b_changed](const e_sides _e_side){
				if (this->Get(_e_side).Set(_rect)) b_changed = true;
			}
		);
#elif u_use_case == 2
	using CPoint = geometry::_2D::base::CPoint;
	/*
		(A)— —(D) left->B::A; top->A::D; right->D::C; bottom->C::B;
		 |     |
		 |     |
		(B)— —(C)
	*/
	TRect rect_(_rect);
	const CPoint cnr_A = rect_.Corner(TRect::e_corners::e_A);
	const CPoint cnr_B = rect_.Corner(TRect::e_corners::e_B);
	const CPoint cnr_C = rect_.Corner(TRect::e_corners::e_C);
	const CPoint cnr_D = rect_.Corner(TRect::e_corners::e_D);

	for (int16_t i_ = e_sides::e_left; i_ <= e_sides::e_bottom; i_++) {

		const e_sides e_side = static_cast<e_sides>(i_);
		
		if (false) {} 
		else if (e_sides::e_left   == e_side) { if (this->Left().Set(cnr_B, cnr_A))   b_changed = true; } // B->A ;
		else if (e_sides::e_top    == e_side) { if (this->Top().Set(cnr_A, cnr_D))    b_changed = true; } // A->D ;
		else if (e_sides::e_right  == e_side) { if (this->Right().Set(cnr_D, cnr_C))  b_changed = true; } // D->C ;
		else if (e_sides::e_bottom == e_side) { if (this->Bottom().Set(cnr_C, cnr_B)) b_changed = true; } // C->B ;
		else
			break;
	}	
#else
	if (this->Bottom().Set(_rect)) b_changed = true;
	if (this->Left().Set(_rect))   b_changed = true;
	if (this->Right().Set(_rect))  b_changed = true;
	if (this->Top().Set(_rect))    b_changed = true;
#endif
	return b_changed;
}

CSet_for_rect& CSet_for_rect::operator <<(const t_rect& _rect) { this->Set(_rect); return *this; }
CSet_for_rect& CSet_for_rect::operator <<(const uint8_t _n_thickness) { (TBase&)*this << _n_thickness; return *this; }