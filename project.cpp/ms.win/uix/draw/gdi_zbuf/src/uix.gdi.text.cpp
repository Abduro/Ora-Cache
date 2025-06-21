/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 01:50:36.151, UTC+4, Batumi;
	This is Ebo Pack GDI genetric output text block interface implementation file;
*/
#include "uix.gdi.text.h"

using namespace ex_ui::draw::text;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace text { namespace output { namespace horizontal { 


}}}}}
/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace text { namespace output { namespace vertical { 

namespace _impl {

#if defined(_DEBUG)
	
	class CAlign_H_Fmt {
	using e_value = CAlign_Horz::e_value;
	public:
		 CAlign_H_Fmt (const uint32_t _n_value) : m_value(_n_value){}
		 CAlign_H_Fmt (void) = delete; CAlign_H_Fmt (const CAlign_H_Fmt&) = delete; CAlign_H_Fmt (CAlign_H_Fmt&&) = delete;
		~CAlign_H_Fmt (void) {}

	public:
		CString  ToString (void) const {
		
			CString cs_out;

			if (false) {}
			else if ( e_value::e_center & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_center"); }
			else if ( e_value::e_left   & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_left"); }
			else if ( e_value::e_right  & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_right"); }
			else {
				cs_out = _T("#not_set");
			}

			return  cs_out;
		}

	private:
		CAlign_H_Fmt& operator = (const CAlign_H_Fmt&) = delete;
		CAlign_H_Fmt& operator = (CAlign_H_Fmt&&) = delete;
	private:
		uint32_t m_value;
	};

	class CAlign_V_Fmt {
	using e_value = CAlign_Vert::e_value;
	public:
		 CAlign_V_Fmt (const uint32_t _n_value) : m_value(_n_value){}
		 CAlign_V_Fmt (void) = delete; CAlign_V_Fmt (const CAlign_V_Fmt&) = delete; CAlign_V_Fmt (CAlign_V_Fmt&&) = delete;
		~CAlign_V_Fmt (void) {}

	public:
		CString  ToString (void) const {
		
			CString cs_out;

			if (false) {}
			else if ( e_value::e_bottom & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_bottom"); }
			else if ( e_value::e_center & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_center"); }
			else if ( e_value::e_top    & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_top"); }
			else {
				cs_out = _T("#not_set");
			}

			return  cs_out;
		}

	private:
		CAlign_V_Fmt& operator = (const CAlign_V_Fmt&) = delete;
		CAlign_V_Fmt& operator = (CAlign_V_Fmt&&) = delete;
	private:
		uint32_t m_value;
	};

	class CAlign_Fmt {
	using e_value = CAlign::e_value;
	public:
		 CAlign_Fmt (const uint32_t _n_value) : m_value(_n_value){}
		 CAlign_Fmt (void) = delete; CAlign_Fmt (const CAlign_Fmt&) = delete; CAlign_Fmt (CAlign_Fmt&&) = delete;
		~CAlign_Fmt (void) {}

	public:
		CString  ToString (void) const {
		
			CString cs_out;

			if (false) {}
			else if ( e_value::e_no_update & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_no_update"); }
			else if ( e_value::e_update_cp & this->m_value ) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("e_update_cp"); }
			else {
				cs_out = _T("#not_set");
			}

			return  cs_out;
		}

	private:
		CAlign_Fmt& operator = (const CAlign_Fmt&) = delete;
		CAlign_Fmt& operator = (CAlign_Fmt&&) = delete;
	private:
		uint32_t m_value;
	};

#endif

}
using namespace _impl;

CAlign_Horz:: CAlign_Horz (const uint32_t _n_value) : TBase(_n_value) {}
CAlign_Horz::~CAlign_Horz (void) {}

#if defined(_DEBUG)
CString   CAlign_Horz::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("{align=%s}");

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

/////////////////////////////////////////////////////////////////////////////

CAlign_Vert:: CAlign_Vert (const uint32_t _n_value) : TBase(_n_value) {}
CAlign_Vert::~CAlign_Vert (void) {}

#if defined(_DEBUG)
CString   CAlign_Vert::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("{align=%s}");

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

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (const uint32_t _n_value) : TBase(_n_value) {}
CAlign::~CAlign (void) {}

#if defined(_DEBUG)
CString   CAlign::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{align=%s}");
	static _pc_sz pc_sz_pat_r = _T("{align=%s}");

	CString cs_val = CAlign_Fmt(TBase::Value()).ToString();
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_val); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_val); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

}}}}}