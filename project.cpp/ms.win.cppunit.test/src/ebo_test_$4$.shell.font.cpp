/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:12:25.658, UTC+4, Batumi, Friday;
	This is Ebo pack system shell installed fonts' list wrapper library unit test implementation file; 
*/
#include "ebo_test_$4$.shell.font.h"

using namespace ebo::boo::test::shell;

/////////////////////////////////////////////////////////////////////////////

CFonts:: CFonts (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CFonts::_ctor (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_fonts.Print(e_print::e_all));
	_out()();

}

void CFonts::Has (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_fonts.GetInstalled();
	if (this->m_fonts.Error()) {
		_out() += this->m_fonts.Error().Print(TError::e_print::e_req);
	}
	else {

		CString cs_name(_T("Pirulen Rg"));

		_out() += TStringEx().Format(_T("Trying to find font: %s..."), (_pc_sz) cs_name);

		if (this->m_fonts.Has((_pc_sz)cs_name))
			_out() += _T("*result* : installed");
		else
			_out() += _T("*result* : not installed");
	}
	_out()();
}

void CFonts::GetInstalled (void) {

	_out() += TLog_Acc::e_new_line;
	_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_fonts.GetInstalled(); // no check for error this time;

	_out() += TStringEx().Format(_T("%s"), (_pc_sz) this->m_fonts.Print(e_print::e_all));
	_out()();
}