/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 07:49:47.460, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI text output classes' unit test interface implementation file;
*/
#include "ebo_test_$d$.zbuf.text.h"

using namespace ebo::boo::test::draw;

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace draw { namespace text { namespace vertical {

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

	_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_align_h.Print(e_print::e_all));
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

void CAlign::Get (void) {

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

	_out() += _T("Setting the target device context to alignment object...");

	this->m_align << fake_wnd.Ctx();

	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	_out() += _T("Retrieving alignment flags...");
	_out() += TStringEx().Format(_T("*before*:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	this->m_align.Get();

	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));

	_out()();
}

void CAlign::Set (void) {

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
	if (this->m_align.Error().Is()) {
		_out() += this->m_align.Error().Print(TError::e_print::e_req);
		_out()(); return;
	}

	this->m_align.Get();

	_out() += TStringEx().Format(_T("*after *:%s"), (_pc_sz) this->m_align.Print(e_print::e_all));
	_out()();
}

}}}}}}