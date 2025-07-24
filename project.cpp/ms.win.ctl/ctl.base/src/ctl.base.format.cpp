/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Aug-2020 at 6:43:22a, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack shared control format base interface implementation file.
*/
#include "ctl.base.format.h"

using namespace ex_ui::controls;
using namespace ex_ui::controls::format;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace controls { namespace format { namespace _impl { void __warning_lnk_4221 (void) {}}}}}

/////////////////////////////////////////////////////////////////////////////

CBkgnd:: CBkgnd (void) : m_clr_solid((rgb_color)::GetSysColor(COLOR_APPWORKSPACE)), m_img_res(0) {}
CBkgnd:: CBkgnd (const CBkgnd& _ref) : CBkgnd() { *this = _ref; }
CBkgnd::~CBkgnd (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CGradient& CBkgnd::Gradient (void) const { return this->m_clr_grad; }
CGradient& CBkgnd::Gradient (void)       { return this->m_clr_grad; }

uint16_t   CBkgnd::ImageRes (void) const { return this->m_img_res ; }
bool       CBkgnd::ImageRes (const uint16_t _res_id) {
	_res_id;
	const bool b_changed  = this->ImageRes() != _res_id;

	if (b_changed)
		this->m_img_res = _res_id;

	return m_img_res ;
}

const
CMargins&  CBkgnd::Margins (void) const { return this->m_margins ; }
CMargins&  CBkgnd::Margins (void)       { return this->m_margins ; }

const
CPadding&  CBkgnd::Padding (void) const { return this->m_padding ; }
CPadding&  CBkgnd::Padding (void)       { return this->m_padding ; }
#if defined(_DEBUG)
CString    CBkgnd::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%sgrad={%s};%s%simg_res=%u;%s%smargins=%s;%s%spadding=%s;%s%sclr_solid=%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%sgrad={%s};%s%simg_res=%u;%s%smargins=%s;%s%spadding=%s;%s%sclr_solid=%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%sgrad={%s};%s%simg_res=%u;%s%smargins=%s;%s%spadding=%s;%s%sclr_solid=%s%s%s}");

	CString cs_grad    = this->Gradient().Print(e_print::e_req);
	CString cs_margins = this->Margins().Print(e_print::e_req);
	CString cs_padding = this->Padding().Print(e_print::e_req);
	CString cs_solid   = this->Solid().Print(e_print::e_req);

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_grad,
		_p_sfx, _p_pfx, this->ImageRes(),
		_p_sfx, _p_pfx, (_pc_sz) cs_margins,
		_p_sfx, _p_pfx, (_pc_sz) cs_padding,
		_p_sfx, _p_pfx, (_pc_sz) cs_solid  , _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_grad,
		_p_sfx, _p_pfx, this->ImageRes(),
		_p_sfx, _p_pfx, (_pc_sz) cs_margins,
		_p_sfx, _p_pfx, (_pc_sz) cs_padding,
		_p_sfx, _p_pfx, (_pc_sz) cs_solid  , _p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_grad,
		_p_sfx, _p_pfx, this->ImageRes(),
		_p_sfx, _p_pfx, (_pc_sz) cs_margins,
		_p_sfx, _p_pfx, (_pc_sz) cs_padding,
		_p_sfx, _p_pfx, (_pc_sz) cs_solid  , _p_sfx, _p_pfx);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
const
TRgbQuad&  CBkgnd::Solid (void) const   { return this->m_clr_solid; }
TRgbQuad&  CBkgnd::Solid (void)         { return this->m_clr_solid; }

/////////////////////////////////////////////////////////////////////////////

CBkgnd&  CBkgnd::operator = (const CBkgnd& _ref) {
	*this << _ref.Gradient() << _ref.ImageRes() << _ref.Solid() << _ref.Margins() << _ref.Padding(); return *this;
}

CBkgnd&  CBkgnd::operator <<(const CGradient& _grad)    { this->Gradient() = _grad;    return *this; }
CBkgnd&  CBkgnd::operator <<(const CMargins&  _margins) { this->Margins()  = _margins; return *this; }
CBkgnd&  CBkgnd::operator >>(const CPadding&  _padding) { this->Padding()  = _padding; return *this; }
CBkgnd&  CBkgnd::operator <<(const uint16_t _res_id)    { this->ImageRes(_res_id);     return *this; }
CBkgnd&  CBkgnd::operator <<(const TRgbQuad& _color)    { this->Solid() = _color;      return *this; }

/////////////////////////////////////////////////////////////////////////////

CFontSpec:: CFontSpec (void) : m_fore(::GetSysColor(COLOR_WINDOWTEXT)), m_name(_T("Verdana")), m_size(10) {}
CFontSpec:: CFontSpec (const CFontSpec& _spec) : CFontSpec() { *this = _spec; }
CFontSpec::~CFontSpec (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CAlign&     CFontSpec::Align  (void) const { return m_align; }
CAlign&     CFontSpec::Align  (void)       { return m_align; }

_pc_sz      CFontSpec::Family (void) const { return m_name.GetString(); }
err_code    CFontSpec::Family (_pc_sz _lp_sz_name) {
	_lp_sz_name;
	err_code n_result = __s_ok;

	CString cs_name(_lp_sz_name); cs_name.Trim();

	if (cs_name.IsEmpty() == true)
		return n_result = __e_inv_arg;

	if (0 == this->m_name.CompareNoCase(cs_name.GetString())) // the input font family name is already set; nothing to do;
		return n_result = __s_false;

	m_name = cs_name;

	return n_result;
}

rgb_color   CFontSpec::Fore   (void) const { return m_fore ; }
rgb_color&  CFontSpec::Fore   (void)       { return m_fore ; }

const
TFontOpts&  CFontSpec::Options(void) const { return m_opts ; }
TFontOpts&  CFontSpec::Options(void)       { return m_opts ; }

#if defined(_DEBUG)
CString     CFontSpec::Print  (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%salign=%s;%s%sfamily=%s;fore=%s;opts=%s;size=%d(pt)%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s;family=%s;fore=%s;opts=%s;size=%d(pt)}");
	static _pc_sz pc_sz_pat_r = _T("{align=%s;family=%s;fore=%s;opts=%s;size=%d(pt)}");

	CString cs_align = this->Align().Print(e_print::e_req);
	CString cs_fore  = TRgbQuad(this->Fore()).Print(e_print::e_req);
	CString cs_opts  = TFontOpts::Print(this->Options().Get());

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz)cs_align,
		_p_sfx, _p_pfx,  this->Family() , (_pc_sz) cs_fore, (_pc_sz) cs_opts, this->Size(),
		_p_sfx, _p_pfx  );
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		(_pc_sz)cs_align, this->Family(), (_pc_sz) cs_fore, (_pc_sz) cs_opts, this->Size());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		(_pc_sz)cs_align, this->Family(), (_pc_sz) cs_fore, (_pc_sz) cs_opts, this->Size());
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return cs_out;
}
#endif

int32_t    CFontSpec::Size   (void) const { return m_size ; }
int32_t&   CFontSpec::Size   (void)       { return m_size ; }

/////////////////////////////////////////////////////////////////////////////

CFontSpec&  CFontSpec::operator = (const CFontSpec& _spec) {
	*this >> _spec.Fore() << _spec.Align() << _spec.Family() << _spec.Options() << _spec.Size(); return *this;
}

CFontSpec&  CFontSpec::operator <<(const CAlign& _align ) { this->Align() = _align; return *this; }
CFontSpec&  CFontSpec::operator >>(const rgb_color _clr_fore) { this->Fore() = _clr_fore; return *this; }
CFontSpec&  CFontSpec::operator <<(const int32_t _dw_size ) { this->Size() = _dw_size; return *this; }
CFontSpec&  CFontSpec::operator <<(const TFontOpts& _opts) { this->Options() = _opts; return *this; }
CFontSpec&  CFontSpec::operator <<(_pc_sz _lp_sz_family) { this->Family(_lp_sz_family); return *this; }

/////////////////////////////////////////////////////////////////////////////

CBase:: CBase (void) {}
CBase:: CBase (const CBase& _src) : CBase() { *this = _src; }
CBase::~CBase (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBkgnd& CBase::Bkgnd (void) const { return m_bkgnd; }
CBkgnd& CBase::Bkgnd (void)       { return m_bkgnd; }
const
CBorders& CBase::Borders (void) const { return m_borders; }
CBorders& CBase::Borders (void)       { return m_borders; }
const
CFontSpec&  CBase::Font  (void) const { return m_spec; }
CFontSpec&  CBase::Font  (void)       { return m_spec; }

#if defined(_DEBUG)
CString     CBase::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%sbkgnd=%s;%s%sborders=%s;%s%sfont=%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%sbkgnd=%s;%s%sborders=%s;%s%sfont=%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("%s%sbkgnd=%s;%s%sborders=%s;%s%sfont=%s%s%s");

	CString cs_bkgnd   = this->Bkgnd().Print(e_print::e_req);
	CString cs_borders = this->Borders().Print(e_print::e_req);
	CString cs_font    = this->Font().Print(e_print::e_req);

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_bkgnd,
		_p_sfx, _p_pfx, (_pc_sz) cs_borders,
		_p_sfx, _p_pfx, (_pc_sz) cs_font,
		_p_sfx, _p_pfx  );
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_bkgnd,
		_p_sfx, _p_pfx, (_pc_sz) cs_borders,
		_p_sfx, _p_pfx, (_pc_sz) cs_font,
		_p_sfx, _p_pfx  );
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_bkgnd,
		_p_sfx, _p_pfx, (_pc_sz) cs_borders,
		_p_sfx, _p_pfx, (_pc_sz) cs_font,
		_p_sfx, _p_pfx  );
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CBase&  CBase::operator = (const CBase&  _ref) { *this << _ref.Bkgnd() << _ref.Font() << _ref.Borders(); return *this; }
CBase&  CBase::operator <<(const CBkgnd& _bkg) { this->Bkgnd() = _bkg ; return *this; }
CBase&  CBase::operator <<(const CBorders& _borders) { this->Borders() = _borders; return *this; }
CBase&  CBase::operator <<(const CFontSpec& _spec) { this->Font() = _spec; return *this; }