/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 07:49:47.460, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI text output classes' unit test interface implementation file;
*/
#include "ebo_test_$d$.zbuf.text.h"

using namespace ebo::boo::test::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace text { namespace format {

CAlign_H:: CAlign_H (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_H::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	enum e_fake : uint32_t {
	e_el_0 = 0x0,
	e_el_1 = 0x1,
	};

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
	_out()();
}

void CAlign_H::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
	_out() += _T("Setting multiple flags; accepted flag must be one only...");
	const uint32_t n_flags = THorz_Flags::e_center | THorz_Flags::e_left | THorz_Flags::e_right;
	const bool b_changed = this->m_align_h.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_align_h.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign_V:: CAlign_V (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_V::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_v.Print(e_print::e_all));
	_out()();
}

void CAlign_V::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align_v.Print(e_print::e_all));
	_out() += _T("Setting multiple flags; accepted flag must be one only...");
	const uint32_t n_flags = TVert_Flags::e_bottom | TVert_Flags::e_middle | TVert_Flags::e_top;
	const bool b_changed = this->m_align_v.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_align_v.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out()();
}

void CAlign::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out() += _T("Setting multiple flags; not more than *two* flags may be accepted...");
	const uint32_t n_flags = TVert_Flags::e_middle | THorz_Flags::e_center | THorz_Flags::e_right;
	const bool b_changed = this->m_align.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_align.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CCutter:: CCutter (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CCutter::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_cutter.Print(e_print::e_all));
	_out()();
}

void CCutter::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_cutter.Print(e_print::e_all));
	_out() += _T("Setting multiple flags; accepted flag must be one only...");

	const uint32_t n_flags = TCutter::e_value::e_end | TCutter::e_value::e_path | TCutter::e_value::e_word;
	const bool b_changed = this->m_cutter.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_cutter.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CModifier:: CModifier (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CModifier::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_modifier.Print(e_print::e_all));
	_out()();
}

void CModifier::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_modifier.Print(e_print::e_all));

	const uint32_t n_flags = TModifier::e_value::e_do_modify | TModifier::e_value::e_do_prefix | TModifier::e_value::e_tabs_ext;
	const bool b_changed = this->m_modifier.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_modifier.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

COptimizer:: COptimizer (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void COptimizer::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_optimazer.Print(e_print::e_all));
	_out()();
}

void COptimizer::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_optimazer.Print(e_print::e_all));

	const uint32_t n_flags = TOptimizer::e_value::e_rc_calc | TOptimizer::e_value::e_no_clip | TOptimizer::e_value::e_single;
	const bool b_changed = this->m_optimazer.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_optimazer.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CFormat:: CFormat (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFormat::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_format.Print(e_print::e_all));
	_out()();
}

void CFormat::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_format.Print(e_print::e_all));

	_out() += _T("Setting multiple flags; expecting that each of format components is changed...");

	const uint32_t n_flags = THorz_Flags::e_center
	                       | TVert_Flags::e_bottom
	                       | TCutter::e_value::e_path
	                       | TModifier::e_value::e_do_modify
	                       | TOptimizer::e_value::e_rc_calc
	                       | TOptimizer::e_value::e__na;
	
	const bool b_changed = this->m_format.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_format.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

}}}}}

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace text { namespace output {

CAlign_H:: CAlign_H (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_H::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0)
	enum e_fake : uint32_t {
	e_el_0 = 0x0,
	e_el_1 = 0x1,
	};

	static const e_fake e_all[] {e_fake::e_el_0, e_fake::e_el_1};

#define enum_2_str(e_fake) #e_fake

	for (uint32_t i_ = 0; i_ < _countof(e_all); i_++) {
		_out() += _T(enum_2_str(e_all[i_]));
	}
#endif

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
	_out()();
}

void CAlign_H::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
	_out() += _T("Setting multiple flags; accepted flag must be one only...");

	const uint32_t n_flags = THorz_Flags::e_center | THorz_Flags::e_left | THorz_Flags::e_right;
	const bool b_changed = this->m_align_h.Set(n_flags);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_align_h.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign_V:: CAlign_V (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign_V::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_v.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CAlign::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out()();
}

void CAlign::Change (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	_out() += _T("Setting flags to horizontal and vertical alignments of the text...");

	const bool b_changed = this->m_align.Set(THorz_Flags::e_base | TVert_Flags::e_center | TAlign::e_value::e_update_cp);

	CString cs_changed = TStringEx().Bool(b_changed);

	_out() += TStringEx().Format(_T("*after *:%s; changed=%s;"), (_pc_sz) this->m_align.Print(e_print::e_all), (_pc_sz) cs_changed);
	_out()();
}

void CAlign::GetFrom (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CFake_Wnd fake_wnd(true);

	_out() += _T("Creating the fake window for getting device context...");

	if (fake_wnd.Error().Is()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	_out() += _T("Setting the advance graphics mode to device context...");

	CError err_;
	TMode  mode;

	mode << fake_wnd.Ctx();
	err_ << mode.Set(TMode::e_advanced);

	if (err_.Is()) {
		_out() += err_.Print(TError::e_print::e_req);
		_out()(); return;
	}
#if (0)
	// selecting font into the device context does not change default values of the text alignment ;
	_out() += _T("Creating the font for selecting into device context...");

	using TFont = ex_ui::draw::CFont;
	TFont font_;

	err_ << font_.Create(_T("Pirulen Rg"), TFontOpts::eExactSize, -12);
	if (err_.Is()) {
		_out() += err_.Print(CError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Selecting the font into device context...");
	TFnt_Sel fnt_sel(fake_wnd.Ctx(), font_);
#endif
	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	_out() += _T("Retrieving alignment flags...");
	this->m_align << fake_wnd.Ctx();

	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	_out()();
}

void CAlign::SetTo (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	CFake_Wnd fake_wnd(true);

	_out() += _T("Creating the fake window for getting device context...");

	if (fake_wnd.Error().Is()) {
		_out() += fake_wnd.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Setting the advance graphics mode to device context...");

	CError err_;
	TMode  mode;

	mode << fake_wnd.Ctx();
	err_ << mode.Set(TMode::e_advanced);

	if (err_.Is()) {
		_out() += err_.Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Creating the font for selecting into device context...");

	using TFont = ex_ui::draw::CFont;
	TFont font_;

	err_ << font_.Create(_T("Pirulen Rg"), TFontOpts::eExactSize, -12);
	if (err_.Is()) {
		_out() += err_.Print(CError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Selecting the font into device context...");
	TFnt_Sel fnt_sel(fake_wnd.Ctx(), font_);

	this->m_align << fake_wnd.Ctx();
	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	_out() += _T("Setting the flags for vertical alignment...");

	this->m_align.Set(TVert_Flags::e_center);
	this->m_align >> fake_wnd.Ctx();

	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	this->m_align << fake_wnd.Ctx();

	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out()();
}

}}}}}