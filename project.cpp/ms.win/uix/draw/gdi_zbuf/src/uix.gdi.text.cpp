/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 01:50:36.151, UTC+4, Batumi;
	This is Ebo Pack GDI genetric output text block interface implementation file;
*/
#include "uix.gdi.text.h"
#include "uix.gdi.zbuf.h"

using namespace ex_ui::draw::text;
using CZBuffer = ex_ui::draw::memory::CZBuffer;

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif

#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace text { namespace _impl {
#if defined(_DEBUG)
	class CFmt_Base {
	protected:
		 CFmt_Base (const uint32_t _n_value) : m_value(_n_value){}
		 CFmt_Base (void) : m_value(0) {} CFmt_Base (const CFmt_Base&) = delete; CFmt_Base (CFmt_Base&&) = delete;
		~CFmt_Base (void) {}
	private:
		CFmt_Base& operator = (const CFmt_Base&) = delete;
		CFmt_Base& operator = (CFmt_Base&&) = delete;
	protected:
		uint32_t m_value;
	};
#endif
}}}}

/////////////////////////////////////////////////////////////////////////////

CProp_Trim:: CProp_Trim (const uint32_t _n_value, _pc_sz _p_name) : TBase(_n_value, _p_name) {}
CProp_Trim::~CProp_Trim (void) {}

bool  CProp_Trim::operator = (const uint32_t _n_value) { return TBase::Set(_n_value); }
CProp_Trim& CProp_Trim::operator = (const CProp_Trim& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CProp_Err:: CProp_Err (const uint32_t _n_value, _pc_sz _p_name) : TBase(_n_value, _p_name) {}
CProp_Err:: CProp_Err (const CProp_Err& _src) : TBase() { (TBase&)*this = (const TBase&)_src; }
CProp_Err::~CProp_Err (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CProperty& CProp_Err::Base (void) const { return (TBase&)*this; }
CProperty& CProp_Err::Base (void)       { return (TBase&)*this; }

TError&    CProp_Err::Error(void) const { return this->m_error; }

bool  CProp_Err::operator = (const uint32_t _n_value) { return TBase::Set(_n_value); }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace text { namespace format {
namespace _impl {
#if defined(_DEBUG)
	using CFmt_Base = ex_ui::draw::text::_impl::CFmt_Base;

	class CAlign_H_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CAlign_Horz::e_value;
	public:
		 CAlign_H_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CAlign_H_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if (false) {}
			else if ( e_value::e_center & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_center"); }
			else if ( e_value::e_left   & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_left"  ); } // condition failed;
			else if ( e_value::e_right  & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_right" ); }
			else {
				cs_out = _T("e_left"); // because this is default value and it equals to '0';
			}
			return  cs_out;
		}
	};

	class CAlign_V_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CAlign_Vert::e_value;
	public:
		 CAlign_V_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CAlign_V_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if (false) {}
			else if ( e_value::e_bottom & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_bottom"); }
			else if ( e_value::e_middle & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_middle"); }
			else if ( e_value::e_top    & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_top"); } // condition failed;
			else {
				cs_out = _T("e_top");  // because this is default value and it equals to '0';
			}
			return  cs_out;
		}
	};

	class CCutter_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CCutter::e_value;
	public:
		 CCutter_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CCutter_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if (false) {}
			else if ( e_value::e_end  & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_end" ); }
			else if ( e_value::e_path & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_path"); }
			else if ( e_value::e_word & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_word"); }
			else {
				cs_out = _T("#not_set");
			}
			return  cs_out;
		}
	};

	class CModifier_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CModifier::e_value;
	public:
		 CModifier_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CModifier_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if ( e_value::e_do_modify & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_do_modify"); }
			if ( e_value::e_do_prefix & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_do_prefix"); }
			if ( e_value::e_no_prefix & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_no_prefix"); }
			if ( e_value::e_tabs_ext  & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_tabs_ext" ); }
			if (cs_out.IsEmpty()) {
				cs_out = _T("#not_set");
			}
			return  cs_out;
		}
	};

	class COptimizer_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = COptimizer::e_value;
	public:
		 COptimizer_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~COptimizer_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if ( e_value::e_rc_calc & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_rc_calc"); }
			if ( e_value::e_no_clip & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_no_clip"); }
			if ( e_value::e_single  & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_single"); }
			if (cs_out.IsEmpty()) {
				cs_out = _T("#not_set");
			}
			return  cs_out;
		}
	};

#endif
}
using namespace _impl;

CAlign_Horz:: CAlign_Horz (const uint32_t _n_value) : TBase(_n_value, _T("#h_align")) {}
CAlign_Horz::~CAlign_Horz (void) {}

#if defined(_DEBUG)
CString   CAlign_Horz::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("horz=%s");

	CString cs_val = CAlign_H_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CAlign_Horz::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;
	if (false){}
	else if (false == b_changed && (e_value::e_center & _u_flags)) { b_changed = (TBase&)*this = e_value::e_center ; }
	else if (false == b_changed && (e_value::e_right  & _u_flags)) { b_changed = (TBase&)*this = e_value::e_right; }
	else
		b_changed = (TBase&)*this = e_value::e_left;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CAlign_Vert:: CAlign_Vert (const uint32_t _n_value) : TBase(_n_value, _T("#v_align")) {}
CAlign_Vert::~CAlign_Vert (void) {}

#if defined(_DEBUG)
CString   CAlign_Vert::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("vert=%s");

	CString cs_val = CAlign_V_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CAlign_Vert::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;
	if (false){}
	else if (false == b_changed && (e_value::e_bottom & _u_flags)) { b_changed = (TBase&)*this = e_value::e_bottom; }
	else if (false == b_changed && (e_value::e_middle & _u_flags)) { b_changed = (TBase&)*this = e_value::e_middle; }
	else
		b_changed = (TBase&)*this = e_value::e_top;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (void) : TBase(0, _T("#align")) {}
CAlign::~CAlign (void) {}

/////////////////////////////////////////////////////////////////////////////

const
CAlign_Horz& CAlign::Horz (void) const { return this->m_horz; }
CAlign_Horz& CAlign::Horz (void)       { return this->m_horz; }

#if defined(_DEBUG)
CString   CAlign::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s;%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s;%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s;%s}");

	CString cs_horz = /*CAlign_H_Fmt(TBase::Value()).ToString()*/this->Horz().Print(e_print::e_req);
	CString cs_vert = /*CAlign_V_Fmt(TBase::Value()).ToString()*/this->Vert().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_horz, (_pc_sz) cs_vert); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_horz, (_pc_sz) cs_vert); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_horz, (_pc_sz) cs_vert); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool  CAlign::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;
	if (this->Horz().Set(_u_flags)) b_changed = true;
	if (this->Vert().Set(_u_flags)) b_changed = true;

	return b_changed;
}

const
CAlign_Vert& CAlign::Vert (void) const { return this->m_vert; }
CAlign_Vert& CAlign::Vert (void)       { return this->m_vert; }

/////////////////////////////////////////////////////////////////////////////

CCutter:: CCutter (void) : TBase (e_value::e__na, _T("#cutter")) {}

#if defined(_DEBUG)
CString   CCutter::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{val=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{val=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_val = CCutter_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CCutter::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;
	if (false){}
	else if (false == b_changed && (e_value::e_end  & _u_flags)) { b_changed = (TBase&)*this = e_value::e_end ; }
	else if (false == b_changed && (e_value::e_path & _u_flags)) { b_changed = (TBase&)*this = e_value::e_path; }
	else if (false == b_changed && (e_value::e_word & _u_flags)) { b_changed = (TBase&)*this = e_value::e_word; }
	else
		b_changed = (TBase&)*this = e_value::e__na;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CModifier:: CModifier (void) : TBase (e_value::e__na, _T("#modifier")) {}

#if defined(_DEBUG)
CString   CModifier::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{flags=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{flags=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_val = CModifier_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CModifier::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;

	const uint32_t n_before = TBase::Value(); 

	if (e_value::e_do_modify & _u_flags) { (TBase&)*this += e_value::e_do_modify; }
	if (e_value::e_do_prefix & _u_flags) { (TBase&)*this += e_value::e_do_prefix; }
	if (e_value::e_no_prefix & _u_flags) { (TBase&)*this += e_value::e_no_prefix; }
	if (e_value::e_tabs_ext  & _u_flags) { (TBase&)*this += e_value::e_tabs_ext ; }
	
	return b_changed = n_before != TBase::Value();
}

/////////////////////////////////////////////////////////////////////////////

COptimizer:: COptimizer (void) : TBase (e_value::e__na, _T("#optimizer")) {}

#if defined(_DEBUG)
CString   COptimizer::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{flags=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{flags=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s}");

	CString cs_val = COptimizer_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool COptimizer::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;

	const uint32_t n_before = TBase::Value(); 

	if (e_value::e_rc_calc & _u_flags) { (TBase&)*this += e_value::e_rc_calc; }
	if (e_value::e_no_clip & _u_flags) { (TBase&)*this += e_value::e_no_clip; }
	if (e_value::e_single  & _u_flags) { (TBase&)*this += e_value::e_single; }
	
	return b_changed = n_before != TBase::Value();
}

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (void) : TBase (0, _T("#format")) {}

const
CAlign&  CFormat::Align (void) const { return this->m_align; }
CAlign&  CFormat::Align (void)       { return this->m_align; }
const
CCutter& CFormat::Cut (void) const{ return this->m_cutter; }
CCutter& CFormat::Cut (void)      { return this->m_cutter; }
const
CAlterer& CFormat::Modify (void) const { return this->m_modify; }
CAlterer& CFormat::Modify (void)       { return this->m_modify; }
const
COptima& CFormat::Optimize (void) const { return this->m_optima; }
COptima& CFormat::Optimize (void)       { return this->m_optima; }

#if defined(_DEBUG)
CString   CFormat::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt;_p_pfx;_p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%salign=%s%s%scut=%s%s%salt=%s%s%sopt=%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s%salign=%s%s%scut=%s%s%salt=%s%s%sopt=%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%salign=%s%s%scut=%s%s%salt=%s%s%sopt=%s%s%s}");

	CString cs_align  = this->Align().Print(e_print::e_req);
	CString cs_cutter = this->Cut().Print(e_print::e_req);
	CString cs_modify = this->Modify().Print(e_print::e_req);
	CString cs_optima = this->Optimize().Print(e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_align ,
		_p_sfx, _p_pfx, (_pc_sz) cs_cutter,
		_p_sfx, _p_pfx, (_pc_sz) cs_modify,
		_p_sfx, _p_pfx, (_pc_sz) cs_optima, _p_sfx, _p_pfx);
	}
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
		_p_sfx, _p_pfx, (_pc_sz) cs_align ,
		_p_sfx, _p_pfx, (_pc_sz) cs_cutter,
		_p_sfx, _p_pfx, (_pc_sz) cs_modify,
		_p_sfx, _p_pfx, (_pc_sz) cs_optima, _p_sfx, _p_pfx);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r,
		_p_sfx, _p_pfx, (_pc_sz) cs_align ,
		_p_sfx, _p_pfx, (_pc_sz) cs_cutter,
		_p_sfx, _p_pfx, (_pc_sz) cs_modify,
		_p_sfx, _p_pfx, (_pc_sz) cs_optima, _p_sfx, _p_pfx);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CFormat::Set (const uint32_t _flags) {
	_flags;
	bool b_changed = false;
	if (0 == _flags)
		return b_changed;

	if (this->Align().Set(_flags)) b_changed = true;
	if (this->Cut().Set(_flags)) b_changed = true;
	if (this->Modify().Set(_flags)) b_changed = true;
	if (this->Optimize().Set(_flags)) b_changed = true;

	return b_changed;
}

CFormat& CFormat::operator << (const CAlign& _align) { this->Align() = _align; return *this; }
CFormat& CFormat::operator << (const CAlterer& _alter) { this->Modify() = _alter; return *this; }
CFormat& CFormat::operator << (const CCutter& _cutter) { this->Cut() = _cutter; return *this; }
CFormat& CFormat::operator << (const COptima& _optima) { this->Optimize() = _optima; return *this; }

CFormat& CFormat::operator += (const uint32_t _flags) {

	if (0 != _flags) {
		this->Align() += _flags;
		this->Cut() += _flags;
		this->Modify() += _flags;
		this->Optimize() += _flags;
	}
	return *this;
}

CFormat& CFormat::operator -= (const uint32_t _flags) {

	if (0 != _flags) {
		this->Align() -= _flags;
		this->Cut() -= _flags;
		this->Modify() -= _flags;
		this->Optimize() -= _flags;
	}
	return *this;
}

}}}}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace text { namespace output {
namespace _impl {

#if defined(_DEBUG)
	using CFmt_Base = ex_ui::draw::text::_impl::CFmt_Base;

	class CAlign_H_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CAlign_Horz::e_value;
	public:
		 CAlign_H_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CAlign_H_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if (false) {}
			else if ( e_value::e_base   & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_base"); }
			else if ( e_value::e_center & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_center"); }
			else if ( e_value::e_left   & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_left"); } // condition failed;
			else if ( e_value::e_right  & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_right"); }
			else {
				cs_out = _T("e_left"); // because this is default value and it equals to '0';
			}
			return  cs_out;
		}
	};

	class CAlign_V_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CAlign_Vert::e_value;
	public:
		 CAlign_V_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CAlign_V_Fmt (void) {}

	public:
		CString  ToString (void) const {
		CString  cs_out;
			if (false) {}
			else if ( e_value::e_base   & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_base"); }
			else if ( e_value::e_bottom & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_bottom"); }
			else if ( e_value::e_center & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_center"); }
			else if ( e_value::e_top    & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_top"); } // condition failed;
			else {
				cs_out = _T("e_top");  // because this is default value and it equals to '0';
			}
			return  cs_out;
		}
	};

	class CAlign_A_Fmt : private CFmt_Base { typedef CFmt_Base TBase;
	using e_value = CAlign::e_value;
	public:
		 CAlign_A_Fmt (const uint32_t _n_value) : TBase(_n_value){}
		~CAlign_A_Fmt (void) {}

	public:
		CString ToString (void) const {
		CString cs_out;
			if (false) {}
			else if ( e_value::e_no_update & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_no_update"); }
			else if ( e_value::e_update_cp & TBase::m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_update_cp"); }
			else {
				cs_out = _T("e_no_update"); // because this is default value and it equals to '0';
			}
			return  cs_out;
		}
	};

#endif

}
using namespace _impl;

CAlign_Horz:: CAlign_Horz (const uint32_t _n_value) : TBase(_n_value, _T("#h_align")) {}
CAlign_Horz::~CAlign_Horz (void) {}

#if defined(_DEBUG)
CString   CAlign_Horz::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("horz=%s");

	CString cs_val = CAlign_H_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CAlign_Horz::Set (const uint32_t _u_flags) {
	_u_flags;
	bool b_changed = false;
	if (false){}
	else if (false == b_changed && (e_value::e_base   & _u_flags)) { b_changed = (TBase&)*this = e_value::e_base   ; }
	else if (false == b_changed && (e_value::e_center & _u_flags)) { b_changed = (TBase&)*this = e_value::e_center ; }
	else if (false == b_changed && (e_value::e_right  & _u_flags)) { b_changed = (TBase&)*this = e_value::e_right  ; }
	else
		b_changed = (TBase&)*this = e_value::e_left;  //  if a flag is set again, the resetting to default value is not necessary;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CAlign_Vert:: CAlign_Vert (const uint32_t _n_value) : TBase(_n_value, _T("#v_align")) {}
CAlign_Vert::~CAlign_Vert (void) {}

#if defined(_DEBUG)
CString   CAlign_Vert::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("vert=%s");

	CString cs_val = CAlign_V_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CAlign_Vert::Set (const uint32_t _u_flags) {
	_u_flags;
	if (0 == _u_flags)
		return false;

	bool b_changed = false;
	if (false){}
	else if (false == b_changed && (e_value::e_base   & _u_flags)) { b_changed = (TBase&)*this = e_value::e_base   ; }
	else if (false == b_changed && (e_value::e_bottom & _u_flags)) { b_changed = (TBase&)*this = e_value::e_bottom ; }
	else if (false == b_changed && (e_value::e_center & _u_flags)) { b_changed = (TBase&)*this = e_value::e_center ; }
	else
		b_changed = (TBase&)*this = e_value::e_top;  //  if a flag is set again, the resetting to default value is not necessary;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (void) : TBase(e_value::e_no_update, _T("#align")) { TBase::m_error >> __CLASS__ << __METHOD__  << __e_not_inited; }
CAlign::~CAlign (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CAlign::GetFrom (const HDC& _h_dc) {
	_h_dc;
	err_code n_result = __s_ok;

	if (nullptr == _h_dc || false == CZBuffer::Is_DC(_h_dc))
		return n_result = TBase::m_error << __METHOD__ << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gettextalign ;
	const uint32_t n_flags = ::GetTextAlign(_h_dc);
	if (GDI_ERROR == n_flags)
		return n_result = (TBase::m_error << __METHOD__).Last();

	this->Set(n_flags);  // the result of changing flags is not important this time;
	TBase::m_error << __METHOD__ << n_result;

	return n_result;
}

err_code CAlign::SetTo (const HDC& _h_dc) {
	_h_dc;

	err_code n_result = __s_ok;

	if (nullptr == _h_dc || false == CZBuffer::Is_DC(_h_dc))
		return n_result = TBase::m_error << __METHOD__ << __e_inv_arg;

	const uint32_t n_flags = this->Get();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-settextalign ;
	if (GDI_ERROR == ::SetTextAlign(_h_dc, n_flags))
		n_result = (TBase::m_error << __METHOD__).Last();

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

uint32_t CAlign::Get (void) const {
	return this->Horz().Value() | this->Vert().Value() | TBase::Value();
}

bool     CAlign::Set (const uint32_t _flags) {
	_flags;
	bool b_changed = false;

	if (this->Horz().Set(_flags)) { b_changed = true; }
	if (this->Vert().Set(_flags)) { b_changed = true; }

	if ((e_value::e_update_cp & _flags) && ((TBase&)*this = e_value::e_update_cp)) { b_changed = true; }
	else
		b_changed = b_changed; // no assigning value to 'b_changed' variable, because it may be already assigned by above calls;

	if (!!this->Get())
		TBase::m_error << __METHOD__ << __s_ok;

	return b_changed;
}

const
CAlign_Horz& CAlign::Horz (void) const { return this->m_horz; }
CAlign_Horz& CAlign::Horz (void)       { return this->m_horz; }

const
CAlign_Vert& CAlign::Vert (void) const { return this->m_vert; }
CAlign_Vert& CAlign::Vert (void)       { return this->m_vert; }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString  CAlign::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("{align=%s}");

	CString cs_val = TStringEx().Format(_T("%s;%s;%s"),
			(_pc_sz) CAlign_A_Fmt(TBase::Value()).ToString(),
			(_pc_sz) this->Horz().Print(e_print::e_req),
			(_pc_sz) this->Vert().Print(e_print::e_req)
	);
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

err_code CAlign::operator <<(const HDC& _h_dc) { return this->GetFrom(_h_dc); }
err_code CAlign::operator >>(const HDC& _h_dc) { return this->SetTo(_h_dc); }

}}}}

/////////////////////////////////////////////////////////////////////////////

CTextOut:: CTextOut (void) : m_h_dc(nullptr), m_draw_rect{0}, m_clr_fore(__clr_none), m_anchor{0} {}
CTextOut::~CTextOut (void) {}

/////////////////////////////////////////////////////////////////////////////
const
ex_ui::draw::text::output::CAlign& CTextOut::Align (void) const { return this->m_align; }
ex_ui::draw::text::output::CAlign& CTextOut::Align (void)       { return this->m_align; }

const
t_point&   CTextOut::Anchor(void) const { return this->m_anchor; }
t_point&   CTextOut::Anchor(void)       { return this->m_anchor; }

const
HDC&  CTextOut::Ctx (void) const { return this->m_h_dc; }
HDC&  CTextOut::Ctx (void)       { return this->m_h_dc; }
const
rgb_color& CTextOut::Fore  (void) const { return this->m_clr_fore; }
rgb_color& CTextOut::Fore  (void)       { return this->m_clr_fore; }
const
t_rect&    CTextOut::Out_to(void) const { return this->m_draw_rect; }
t_rect&    CTextOut::Out_to(void)       { return this->m_draw_rect; }

err_code   CTextOut::Recalc_anchor (void) {

	err_code n_result = __s_ok;

	if (::IsRectEmpty(&this->Out_to()))
		return n_result = __e_rect;
	// ToDo: using 2D::rect may be is better, but not for this time;
	this->Anchor().x = this->Out_to().left + __W(this->Out_to())/2;
	this->Anchor().y = this->Out_to().top  + __H(this->Out_to())/2;

	if (nullptr != this->Ctx()) {
		t_size size = {0};
		// the required font must be selected into device; otherwize the default font will be applied for the string size calculation;
		if (::GetTextExtentPoint32(this->Ctx(), (_pc_sz) this->Text(), this->Text().GetLength(), &size)) {

		}
		else 
			n_result = __LastErrToHresult();
	}

	return n_result;
}

const
CString&   CTextOut::Text  (void) const { return this->m_text; }
CString&   CTextOut::Text  (void)       { return this->m_text; }

/////////////////////////////////////////////////////////////////////////////

CTextOut&  CTextOut::operator <<(_pc_sz _p_text) { this->Text() = _p_text; return *this; }
CTextOut&  CTextOut::operator <<(const HDC& _h_dc) { this->Ctx() = _h_dc; return *this; }
CTextOut&  CTextOut::operator <<(const rgb_color& _clr_fore) { this->Fore() = _clr_fore; return *this; }
CTextOut&  CTextOut::operator <<(const t_rect& _out) {
	this->Out_to() = _out;
	this->Recalc_anchor(); return *this;
}