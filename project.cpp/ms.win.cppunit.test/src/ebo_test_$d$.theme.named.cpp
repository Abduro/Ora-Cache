/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:36:15.405, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme named interface unit test implementation file; 
*/
#include "ebo_test_$d$.theme.named.h"

using namespace ebo::boo::test::theme;

/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CNamed::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named.Print(e_print::e_all));
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CNamed_Enum::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named_enum.Print(e_print::e_all));
	_out()();

}

void CNamed_Enum::Load (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (1)
	_out() += TStringEx().Format(_T("Loading palette %s :"), (_pc_sz) TPrint::Out(TThemePalette::e_dark));

	if (__failed(this->m_named_enum.Load(TThemePalette::e_dark)))
		_out() += this->m_named_enum.Error().Print(TError::e_print::e_req) ;
	else {
		const TPalette& palette = this->m_named_enum.PaletteOf(TThemePalette::e_dark);
		_out() += palette.Print(e_print::e_all);
	}

	_out() += TStringEx().Format(_T("Loading palette %s :"), (_pc_sz) TPrint::Out(TThemePalette::e_light));

	if (__failed(this->m_named_enum.Load(TThemePalette::e_light)))
		_out() += this->m_named_enum.Error().Print(TError::e_print::e_req) ;
	else {
		const TPalette& palette = this->m_named_enum.PaletteOf(TThemePalette::e_light);
		_out() += palette.Print(e_print::e_all);
	}
#else
	if (__failed(this->m_named_enum.Load()))
		_out() += this->m_named_enum.Error().Print(TError::e_print::e_req) ;
	else
		_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_named_enum.Print(e_print::e_all));
#endif
	_out()();

}

/////////////////////////////////////////////////////////////////////////////

CState:: CState (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CState::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_state.Print(e_print::e_all));
	_out()();

}

void CState::Set (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) this->m_state.Print(e_print::e_all));

	const TThemeState e_state = TThemeState::e_default;
	const rgb_color color_ = _r_g_b(0x0, 0xff, 0x0);

	CString cs_name  = TStringEx().Format(_T("#test_case: %s"), (_pc_sz) TPrint::Out(e_state));
	CString cs_color = TStringEx().Format(_T("%s(%s)"), (_pc_sz) CHex::Print(color_), _T("green"));

	_out() += TStringEx().Format(
		_T("Input:"
		"%smarker/ID: %u;"
		"%sname: %s;"
		"%scolor: %s;"), _p_new_line, e_state, _p_new_line,(_pc_sz) cs_name, _p_new_line, (_pc_sz) cs_color
	);

	this->m_state.Id(e_state, false);
	this->m_state.Name((_pc_sz)cs_name);
	this->m_state.Color(color_);
	this->m_state.Is_valid(true);

	_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) this->m_state.Print(e_print::e_all));

	_out()();

}