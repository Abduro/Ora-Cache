#ifndef _EBO_TEST_$D$_THEME_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_THEME_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:11:59.496, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme unit test include headers' and common declarations' file; 
*/
#include "_log.h"

#include "uix.theme.h"
#include "uix.theme.named.h"
#include "uix.theme.reg.h"

namespace ebo { namespace boo { namespace test { namespace theme {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using TPercent = TPct_Flt;
	using clr_type = ex_ui::color::rgb::clr_type;

	using TPrint = ex_ui::theme::colors::TPrint;
	using CHex   = ex_ui::color::rgb::CHex;

	using TMarker = TColorMarker;

	using TElement = ex_ui::theme::CElement; 
	using TNamed   = ex_ui::theme::CNamed;
	using TNamed_Enum = ex_ui::theme::CNamed_Enum;
	using TPalette    = ex_ui::theme::CPalette;
	using TPart  = ex_ui::theme::CPart;
	using TState = ex_ui::theme::CState;

	using CCurrentTheme = ex_ui::theme::CCurrent;

	static _pc_sz _p_pfx = _T("\t\t");
	static _pc_sz _p_sfx = _T("\n");
	static _pc_sz _p_new_line = _T("\n\t\t");

}}}}

#pragma comment(lib, "theme_v15.lib")        // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$D$_THEME_DEFS_H_INCLUDED*/