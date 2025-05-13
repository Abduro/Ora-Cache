/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 10:02:47.899, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface implemetation file;
*/
#include "uix.gdi.blend.h"

using namespace ex_ui::draw::blend;

/////////////////////////////////////////////////////////////////////////////

void __warning_lnk_4221 (void) {}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace blend { namespace _impl {
#if defined(_DEBUG)
	class CBlend_Fun_Fmt{
	public:
		 CBlend_Fun_Fmt (const TBlendFun& _b_fun) : m_b_fun(_b_fun) {}
		 CBlend_Fun_Fmt(const CBlend_Fun_Fmt&) = delete; CBlend_Fun_Fmt (CBlend_Fun_Fmt&&) = delete;
		~CBlend_Fun_Fmt (void){}

	public:
		_pc_sz Format (void)  {

			static _pc_sz pc_sz_pat = _T("%d(%s)");

			switch (this->m_b_fun.AlphaFormat) {
			case AC_SRC_ALPHA: this->m_out.Format(pc_sz_pat, this->m_b_fun.AlphaFormat, _T("AC_SRC_ALPHA")); break;
			case  0: this->m_out.Format(pc_sz_pat, this->m_b_fun.BlendOp, _T("#not_set")); break;
			default:
				this->m_out.Format(pc_sz_pat, this->m_b_fun.BlendOp, _T("#undef")); break;
			}
			return (_pc_sz)this->m_out;
		}

		_pc_sz Oper (void)  {

			static _pc_sz pc_sz_pat = _T("%d(%s)");

			switch (this->m_b_fun.BlendOp) {
			case AC_SRC_OVER: this->m_out.Format(pc_sz_pat, this->m_b_fun.BlendOp, _T("AC_SRC_OVER")); break;
			default:
				this->m_out.Format(pc_sz_pat, this->m_b_fun.BlendOp, _T("#undef")); break;
			}
			return (_pc_sz)this->m_out;
		}

	private:
		CBlend_Fun_Fmt& operator = (const CBlend_Fun_Fmt&) = delete;
		CBlend_Fun_Fmt& operator = (CBlend_Fun_Fmt&&) = delete;
	private:
		const TBlendFun& m_b_fun; // the source data for convering to string;
		mutable CString  m_out  ; // cached output string;
	};
#endif
}}}}
using namespace ex_ui::draw::blend::_impl;
/////////////////////////////////////////////////////////////////////////////
CBlend_Wrap:: CBlend_Wrap (void) : m_bl_fun{0} {}

#if defined(_DEBUG)
/*
BLENDFUNCTION {
	BYTE   BlendOp;
    BYTE   BlendFlags; >> not used and must be 0;
    BYTE   SourceConstantAlpha; >> 'SCA' abbreviation;
    BYTE   AlphaFormat; }
*/
CString CBlend_Wrap::Print (const TBlendFun& _bl_fun, const e_print _e_opt) {
	_bl_fun; _e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {src-oper=%s;sca=%s;fmt=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {src-oper=%s;sca=%s;fmt=%s}");
	static _pc_sz pc_sz_pat_r = _T("{src-oper=%s;sca=%s;fmt=%s}");

	CString cs_alpha = TAlpha::Print(_bl_fun.SourceConstantAlpha, e_print::e_req);
	CString cs_out;

	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			CBlend_Fun_Fmt(_bl_fun).Oper(), (_pc_sz) cs_alpha, CBlend_Fun_Fmt(_bl_fun).Format()
		);
	}
	if (e_print::e_no_ns == _e_opt) { 
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			CBlend_Fun_Fmt(_bl_fun).Oper(), (_pc_sz) cs_alpha, CBlend_Fun_Fmt(_bl_fun).Format()
		);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r, CBlend_Fun_Fmt(_bl_fun).Oper(), (_pc_sz) cs_alpha, CBlend_Fun_Fmt(_bl_fun).Format());
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}

CString CBlend_Wrap::Print (const e_print _e_opt) const {
	return CBlend_Wrap::Print(this->m_bl_fun, _e_opt);
}
#endif

const
TBlendFun&  CBlend_Wrap::Ref (void) const { return this->m_bl_fun; }
TBlendFun&  CBlend_Wrap::Ref (void)       { return this->m_bl_fun; }

/////////////////////////////////////////////////////////////////////////////

CBlend_Wrap::operator const TBlendFun& (void) const { return this->Ref(); }
CBlend_Wrap::operator       TBlendFun& (void)       { return this->Ref(); }

/////////////////////////////////////////////////////////////////////////////

CBlender:: CBlender (void) { this->m_error >>__CLASS__ << __METHOD__ << __e_not_inited; }
CBlender::~CBlender (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&    CBlender::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////