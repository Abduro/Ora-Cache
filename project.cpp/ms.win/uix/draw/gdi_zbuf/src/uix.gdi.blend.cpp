/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 10:02:47.899, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI blend function wrapper interface implemetation file;
*/
#include "uix.gdi.blend.h"
#include "uix.gdi.zbuf.h"

using namespace ex_ui::draw::blend;
using namespace ex_ui::draw::memory;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace blend { namespace _impl {
#if defined(_DEBUG)

	class CInput_Fmt {
	public:
		 CInput_Fmt (const CInput& _input) : m_input(_input){} CInput_Fmt (const CInput_Fmt&) = delete; CInput_Fmt (CInput_Fmt&&) = delete;
		~CInput_Fmt (void) {}

	public:
		_pc_sz ToString (_pc_sz _sp_name, _pc_sz __cls_name, const e_print _e_opt) {
			
			static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {ctx=%s;pos=%s;valid=%s}");
			static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {ctx=%s;pos=%s;valid=%s}");
			static _pc_sz pc_sz_pat_r = _T("{ctx=%s;pos=%s;valid=%s}");

	//		CString cs_ctx = TStringEx().Format(_T("%p"), this->m_input.Ctx());
			CString cs_ctx = TStringEx().__address_of(this->m_input.Ctx());
			CString cs_pos = this->m_input.Position().Print(e_print::e_req);
			CString cs_valid = TStringEx().Bool(this->m_input.Is_valid());

			if (e_print::e_all   == _e_opt) {
				this->m_out.Format(pc_sz_pat_a, _sp_name, __cls_name, (_pc_sz)cs_ctx, (_pc_sz)cs_pos, (_pc_sz)cs_valid);
			}
			if (e_print::e_no_ns == _e_opt) {
				this->m_out.Format(pc_sz_pat_n, __cls_name, (_pc_sz)cs_ctx, (_pc_sz)cs_pos, (_pc_sz)cs_valid);
			}
			if (e_print::e_req   == _e_opt) {
				this->m_out.Format(pc_sz_pat_r, (_pc_sz)cs_ctx, (_pc_sz)cs_pos, (_pc_sz)cs_valid);
			}

			if (this->m_out.IsEmpty())
				this->m_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
			
			return this->m_out.GetString();
		}

	private:
		CInput_Fmt& operator = (const CInput_Fmt&) = delete;
		CInput_Fmt& operator = (CInput_Fmt&&) = delete;
	private:
		const
		CInput& m_input;
		CString m_out;
	};

#endif
}}}}
using namespace ex_ui::draw::blend::_impl;
/////////////////////////////////////////////////////////////////////////////

CInput:: CInput (void) : m_h_dc(nullptr) { this->m_error >>__CLASS__ << __METHOD__ << __e_not_inited; }

const HDC  CInput::Ctx (void) const { return this->m_h_dc; }
const bool CInput::Ctx (const HDC _h_dc) {
	_h_dc;
	bool b_result = CZBuffer::Is_DC(_h_dc);
	if ( b_result == false)
		return b_result;

	this->m_h_dc = _h_dc;

	return b_result;
}

TError&  CInput::Error (void) const { return this->m_error; }
const bool CInput::Is_valid (void) const {
	this->m_error << __METHOD__ << __s_ok;
	if (false == CZBuffer::Is_DC(this->Ctx()))
		return false == (this->m_error << (err_code) TErrCodes::eObject::eHandle = _T("Invalid device context")).Is();

	if (this->Position().Size().Is_zero())
		return false == (this->m_error << (err_code) TErrCodes::eData::eInvalid = _T("Invalid size")).Is();

	return false == this->Error().Is(); // CError::Is() returns 'true' in case the error occurs and is registered;
}

const
CPos&  CInput::Position (void) const { return this->m_pos; } const CPos& CInput::Pos (void) const { return this->m_pos; }
CPos&  CInput::Position (void)       { return this->m_pos; }       CPos& CInput::Pos (void)       { return this->m_pos; }

CInput&  CInput::operator <<(const HDC _h_dc) { this->Ctx(_h_dc); return *this; }
CInput&  CInput::operator <<(const t_rect& _rect) { this->Pos() << _rect; return *this; }

/////////////////////////////////////////////////////////////////////////////

CIn_Out:: CIn_Out (void) : CInput() {
//	CInput::Position().Anchor().Marker().Set(1, _T("#dest_dev_ctx"), true);
}

CIn_Src:: CIn_Src (void) : CInput() {
//	CInput::Position().Anchor().Marker().Set(1, _T("#source_dev_ctx"), true);
}

#if defined(_DEBUG)
CString  CIn_Out::Print(const e_print _e_opt) const {
	return CInput_Fmt(*this).ToString((_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _e_opt);
}
CString  CIn_Src::Print(const e_print _e_opt) const {
	return CInput_Fmt(*this).ToString((_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _e_opt);
}
#endif

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

CBlend_Wrap:: CBlend_Wrap (void) : m_bl_fun{0}, m_bPerPixelAlpha(false) { this->Ref().BlendOp = AC_SRC_OVER; }

bool    CBlend_Wrap::PerPixelAlpha (void) const {
     return this->m_bPerPixelAlpha;
}

bool    CBlend_Wrap::PerPixelAlpha (const bool _b_use, const rgb_value _n_alpha) {
	_b_use; _n_alpha;
	const bool b_changed = (this->PerPixelAlpha() != _b_use || this->Ref().SourceConstantAlpha != _n_alpha);

	if (b_changed) {
		this->Ref().SourceConstantAlpha = _b_use ? 0xff : _n_alpha;
		this->Ref().AlphaFormat = _b_use ? AC_SRC_ALPHA : 0;

		this->m_bPerPixelAlpha  = _b_use;
	}

	return b_changed;
}

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
const
CBlend_Wrap& CBlender::Func (void) const { return this->m_bl_fun; }
CBlend_Wrap& CBlender::Func (void)       { return this->m_bl_fun; }

err_code   CBlender::Draw  (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_ready() == false)
		return this->Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-alphablend ;
	const bool b_result = ::AlphaBlend(
		this->Out ().Ctx(), this->Out().Pos().Anchor().X(), this->Out().Pos().Anchor().Y(), this->Out().Pos().Size().W(), this->Out().Pos().Size().H(),
		this->Src ().Ctx(), this->Src().Pos().Anchor().X(), this->Src().Pos().Anchor().Y(), this->Src().Pos().Size().W(), this->Src().Pos().Size().H(),
		this->Func().Ref()
	);

	if (false == b_result)
		this->m_error.Last();

	return this->Error();
}

TError&    CBlender::Error (void) const { return this->m_error; }

bool  CBlender::Is_ready (void) const {
	this->m_error << __METHOD__ << __s_ok;

	// (1) checks the destination data first;
	if (this->Out().Is_valid() == false)
		return false == (this->m_error = this->Out().Error()).Is();

	// (2) checks the source data wrapper;
	if (this->Src().Is_valid() == false)
		return false == (this->m_error = this->Src().Error()).Is();

	// (3) checks the destination and source device contexts;
	if (this->Out().Ctx() == this->Src().Ctx())
		return false == (
				this->m_error << (err_code) TErrCodes::eExecute::eParameter = _T("The source and dest device contexts cannot be the same;")
			).Is();

	return false == this->Error().Is();
}

const
CIn_Out&   CBlender::Out (void) const { return this->m_in_out; }
CIn_Out&   CBlender::Out (void)       { return this->m_in_out; }     
const
CIn_Src&   CBlender::Src (void) const { return this->m_in_src; }
CIn_Src&   CBlender::Src (void)       { return this->m_in_src; }     

/////////////////////////////////////////////////////////////////////////////