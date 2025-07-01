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

void CRegistry::Get_State (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const TThemePalette palette = TThemePalette::e_dark;
	const TThemePart part = TThemePart::e_form;
	const TThemeElement element = TThemeElement::e_back;
	const TThemeState state = TThemeState::e_default;

	TState target;

	CString cs_path = TRouter().Element(palette, part, element);

	_out() += TStringEx().Format(_T("*before*: %s"), (_pc_sz) target.Print(e_print::e_all));
	_out() += TStringEx().Format(_T("Input: \n\t\tpath: %s;\n\t\tstate:%s;"), (_pc_sz) cs_path, (_pc_sz) TPrint::Out(state));

	if (__failed(this->m_storage.Value((_pc_sz) cs_path, state, target)))
		_out() += this->m_storage.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*after *: %s"), (_pc_sz) target.Print(e_print::e_all));

	_out()();
}