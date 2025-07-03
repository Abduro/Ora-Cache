/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2025 at 13:08:10.816, UTC+4, Batumi, Tuesday;
	This is Ebo Pack custom color theme registry interface unit test implementation file; 
*/
#include "ebo_test_$d$.theme.reg.h"

using namespace ebo::boo::test::theme;

/////////////////////////////////////////////////////////////////////////////

CRouter:: CRouter (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRouter:: Get_paths (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const TThemePalette palette = TThemePalette::e_dark;
	_out() += TStringEx().Format(_T("palette: %s = path: %s"), (_pc_sz) TPrint::Out(palette), this->m_router.Palette(palette));

	const TThemePart part = TThemePart::e_form;
	_out() += TStringEx().Format(_T("palette: %s >> part: %s = path: %s"),
		(_pc_sz) TPrint::Out(palette), (_pc_sz) TPrint::Out(part), this->m_router.Part(palette, part)
	);
	const TThemeElement element = TThemeElement::e_back;
	_out() += TStringEx().Format(_T("palette: %s >> part: %s >> element: %s = path: %s"),
		(_pc_sz) TPrint::Out(palette), (_pc_sz) TPrint::Out(part), (_pc_sz) TPrint::Out(element), this->m_router.Element(palette, part, element)
	);

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CRegistry:: CRegistry (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CRegistry::Get_Element (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRouter& router = ex_ui::theme::storage::Get_router();
	CCurrentTheme& theme = router.CurrentTheme();

	TElement target(theme.Element());
	CString cs_path = router.Element(); // gets the element path that is based on currently selected theme;

	_out() += _T("Gets value of one specific element object:");
	if (__failed(this->m_storage.Node((_pc_sz) cs_path, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) target.Print(e_print::e_all));

	TThemeElement border = TThemeElement::e_border;
	theme.Element() = border; // replaces the element value by new one;
	
	_out() += TStringEx().Format(_T("*change* the element to: %s"), (_pc_sz) TPrint::Out(border));

	target.Id(border, true);
	cs_path = router.Element();

	if (__failed(this->m_storage.Node((_pc_sz) cs_path, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) target.Print(e_print::e_all));

	TThemeElement fore = TThemeElement::e_fore;
	theme.Element() = fore; // replaces the element value by new one;

	_out() += TStringEx().Format(_T("*change* the element to: %s"), (_pc_sz) TPrint::Out(fore));

	target.Id(fore, true);
	cs_path = router.Element();

	if (__failed(this->m_storage.Node((_pc_sz) cs_path, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) target.Print(e_print::e_all));

	_out()();
}

void CRegistry::Get_Palette (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRouter& router = ex_ui::theme::storage::Get_router();
	CCurrentTheme& theme = router.CurrentTheme();

	TPallete target(theme.Palette());
	CString cs_path = router.Palette();

	_out() += _T("Gets value of one specific palette object:");
	if (__failed(this->m_storage.Node((_pc_sz) cs_path, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) target.Print(e_print::e_all));

	_out()();
}

void CRegistry::Get_Part (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	TRouter& router = ex_ui::theme::storage::Get_router();
	CCurrentTheme& theme = router.CurrentTheme();

	TPart target(theme.Part());
	CString cs_path = router.Part(); // gets the part path that is based on currently selected theme;

	_out() += _T("Gets value of one specific element object:");
	if (__failed(this->m_storage.Node((_pc_sz) cs_path, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) target.Print(e_print::e_all));

	_out()();
}

void CRegistry::Get_State (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
#if (0)
	const TThemePalette palette = TThemePalette::e_dark;
	const TThemePart part = TThemePart::e_form;
	const TThemeElement element = TThemeElement::e_back;
	const TThemeState state = TThemeState::e_default;
#else
	TRouter& router = ex_ui::theme::storage::Get_router();
	CCurrentTheme& theme = router.CurrentTheme();
#endif
	TState target;

	CString cs_path = TRouter().Element(theme.Palette(), theme.Part(), theme.Element());
	_out() += _T("Gets value of one specific state object:");
	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) target.Print(e_print::e_all));
	_out() += TStringEx().Format(_T("Input: %spath: %s;%sstate:%s;"), _p_new_line, (_pc_sz) cs_path, _p_new_line, (_pc_sz) TPrint::Out(theme.State()));

	if (__failed(this->m_storage.Value((_pc_sz) cs_path, theme.State(), target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) target.Print(e_print::e_all));

	_out() += _T("Gets all available values of the state object:");

	TElement element;
	TRawStates& states = element.States(); // element constructor sets proper identifier and name to each state object;
	// the error is possible due to some states may be not stored in the registry, thus the error is ignored;
	this->m_storage.Value(states);
	if (false) {
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	}
	else {
		for (size_t i_ = 0; i_ < states.size(); i_++) {
			_out() += states.at(i_).Print(e_print::e_no_ns);
		}
	}

	_out()();
}