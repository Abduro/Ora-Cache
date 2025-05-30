/*
	Created by Tech_doc (ebontrop@gmail.com) on 12-Oct-2021 at 1:28:01.4586375 am, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack color project gradient interface implementation file;
*/
#include "color.gradient.h"

using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

CGradient:: CGradient (void) : m_b_vert(false) { this->c0().Is() = this->c1().Is() = false; }
CGradient:: CGradient (const CColor& _from, const CColor& _to) : CGradient() { *this << _from >> _to; }
CGradient:: CGradient (const rgb_color _from, const rgb_color _to) : CGradient() { this->Set(_from, _to);  }
CGradient:: CGradient (const CGradient& _src) : CGradient() { *this = _src; }
CGradient:: CGradient (CGradient&& _victim) : CGradient() { *this = _victim; }
CGradient::~CGradient (void) {}

/////////////////////////////////////////////////////////////////////////////

const bool  CGradient::Is(void) const {

	bool b_valid = true;
	if ( b_valid ) b_valid = m_clr_0.Is() && m_clr_1.Is(); // (1) both colors are valid;
	if ( b_valid ) b_valid = m_clr_0.A()  && m_clr_1.A();  // (2) both colors are not transparent;
	if ( b_valid ) b_valid = m_clr_0 != m_clr_1;           // (3) the start and the end of gradient colors are deferent;

	return b_valid;
}
const bool  CGradient::IsVert(void) const { return m_b_vert; }
      bool& CGradient::IsVert(void)       { return m_b_vert; }
const
CColor&     CGradient::c0 (void) const { return m_clr_0; }
CColor&     CGradient::c0 (void)       { return m_clr_0; }
const
CColor&     CGradient::c1 (void) const { return m_clr_1; }
CColor&     CGradient::c1 (void)       { return m_clr_1; }

const
CColor&     CGradient::From (void) const { return m_clr_0; }
CColor&     CGradient::From (void)       { return m_clr_0; }

#if defined(_DEBUG)
CString     CGradient::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {start=[%s];stop=[%s];vert=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {start=[%s];stop=[%s];vert=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("start=[%s];stop=[%s];vert=%s;valid=%s");

	CString cs_valid = TStringEx().Bool(this->Is());
	CString cs_vert  = TStringEx().Bool(this->IsVert());

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		(_pc_sz)this->From().Print(e_print::e_req), (_pc_sz)this->To().Print(e_print::e_req), (_pc_sz) cs_vert, (_pc_sz) cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n,(_pc_sz)__CLASS__,
		(_pc_sz)this->From().Print(e_print::e_req), (_pc_sz)this->To().Print(e_print::e_req), (_pc_sz) cs_vert, (_pc_sz) cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz)this->From().Print(e_print::e_req), (_pc_sz)this->To().Print(e_print::e_req), (_pc_sz) cs_vert, (_pc_sz) cs_valid);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
CColor&     CGradient::To (void) const { return m_clr_1; }
CColor&     CGradient::To (void)       { return m_clr_1; }
err_code    CGradient::Set (const CSet& _set) {
	_set;
	err_code n_result = __s_ok;

	if (__clr_none == _set.Dark() ||
	    __clr_none == _set.Light())
		return (n_result = __e_inv_arg);

	this->From() = CColor(_set.Dark());
	this->To() = CColor(_set.Light());

	return n_result;
}

err_code    CGradient::Set (const CColor& _from, const CColor& _to) {
	_from; _to;
	err_code n_result = __s_ok;

	if (_from.Is() == false || _to.Is() == false)
		return (n_result = __e_inv_arg);

	this->From() = _from;
	this->To() = _to;

	return  n_result;
}

err_code    CGradient::Set (const rgb_color _from, const rgb_color _to) {
	_from; _to;
	return this->Set(CColor(_from), CColor(_to));
}

/////////////////////////////////////////////////////////////////////////////

CGradient&  CGradient::operator = (const CGradient& _src) { *this << _src.From() >> _src.To() << _src.IsVert();  return *this;}

CGradient&  CGradient::operator = (CGradient&& _victim) { *this = (const CGradient&)_victim; return *this; }

CGradient&  CGradient::operator <<(const bool _b_vert) { this->IsVert() = _b_vert; return *this; }
CGradient&  CGradient::operator <<(const CSet& _set) { this->Set(_set); return *this; }
CGradient&  CGradient::operator <<(const CColor& _clr_from) { this->From() = _clr_from; return *this; }
CGradient&  CGradient::operator >>(const CColor& _clr_upto) { this->To() = _clr_upto; return *this; }

/////////////////////////////////////////////////////////////////////////////

CGradient_Strip:: CGradient_Strip (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CGradient_Strip:: CGradient_Strip (const CGradient_Strip& _src) : CGradient_Strip() { *this = _src; }
CGradient_Strip::~CGradient_Strip (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CGradient_Strip::Add   (const CGradient& _item) {
	_item;
	this->m_error << __METHOD__ << __s_ok;

	try {
		this->m_strip.push_back(_item);
	}
	catch (const ::std::bad_alloc&) {
		this->m_error << __e_no_memory;
	}

	return this->Error();
}

err_code CGradient_Strip::Clear (void) {

	this->m_error << __METHOD__ << __s_ok;

	if (this->Count() == 0)
		return (m_error << __s_false);

	this->m_strip.clear();

	return this->Error();
}

uint32_t CGradient_Strip::Count (void) const { return static_cast<uint32_t>(this->Raw().size()); }
TError&  CGradient_Strip::Error (void) const { return this->m_error; }

const bool CGradient_Strip::Is  (void) const {

	bool is_valid = false;

	for (uint32_t i_ = 0; i_ < this->m_strip.size(); i_++)
		if (this->m_strip[i_].Is() == false)
			return is_valid;

	return (is_valid = true);
}

const bool CGradient_Strip::IsVert(void) const {

	bool is_vert = false;

	if (this->Count() == 0)
		return is_vert;

	for (size_t i_ = 0; i_ < this->m_strip.size(); i_++)
		if (this->m_strip[i_].IsVert() == false)
			return is_vert;

	return (is_vert = true);
}

void CGradient_Strip::IsVert(const bool _is_vert) {
	_is_vert;
	for (size_t i_ = 0; i_ < this->m_strip.size(); i_++)
		this->m_strip[i_].IsVert() = _is_vert;
}

#if defined(_DEBUG)
CString    CGradient_Strip::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("%s%s%s%s%s");

	CString cs_tiles;
	if (this->Raw().empty()) {
		cs_tiles = _T("#empty");
	}
	else {
		for (size_t i_ = 0; i_ < this->Raw().size(); i_++) {
			const CGradient& grad= this->Raw().at(i_);
			if (cs_tiles.IsEmpty() == false) {
				cs_tiles += _p_sfx;
				cs_tiles += _p_pfx;
			}
			cs_tiles += grad.Print(e_print::e_req);
		}
	}

	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_tiles, _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_tiles, _p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_tiles, _p_sfx, _p_pfx);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
TRawGrads& CGradient_Strip::Raw (void) const { return this->m_strip; }

err_code   CGradient_Strip::Remove(const uint32_t _ndx) {
	_ndx;
	m_error << __METHOD__ << __s_ok;

	if (_ndx >= this->Count())
		return (m_error << DISP_E_BADINDEX);

	this->m_strip.erase(this->m_strip.begin() + _ndx);

	return this->Error();
}

const
CGradient& CGradient_Strip::Tile (const uint32_t _ndx) const {
	_ndx;
	this->m_error << __METHOD__ << __s_ok;

	if (_ndx >= this->Count()) {
		static CGradient inv_; this->m_error << DISP_E_BADINDEX;
		return inv_;
	}
	else
		return this->m_strip[_ndx];
}

CGradient& CGradient_Strip::Tile (const uint32_t _ndx) {
	_ndx;
	m_error << __METHOD__ << __s_ok;

	if (_ndx >= this->Count()) {
		static CGradient inv_; m_error << DISP_E_BADINDEX;
		return inv_;
	}
	else
		return this->m_strip[_ndx];
}

/////////////////////////////////////////////////////////////////////////////

CGradient_Strip& CGradient_Strip::operator = (const CGradient_Strip& _src) { *this << _src.Raw(); return *this; }

CGradient_Strip& CGradient_Strip::operator <<(const TRawGrads& _raw) {
	_raw;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Count())
		if (__failed(this->Clear()))
			return *this;
	// https://en.cppreference.com/w/cpp/iterator/back_inserter ;
	try {
		::std::copy(_raw.begin(), _raw.end(), ::std::back_inserter(this->m_strip));
	}
	catch (const ::std::bad_alloc&) {
		this->m_error << __e_no_memory;
	}
	return *this;
}

CGradient_Strip& CGradient_Strip::operator+= (const CGradient& _grad) { this->Add(_grad); return *this; }
CGradient_Strip& CGradient_Strip::operator-= (const uint32_t _ndx) { this->Remove(_ndx); return *this; }