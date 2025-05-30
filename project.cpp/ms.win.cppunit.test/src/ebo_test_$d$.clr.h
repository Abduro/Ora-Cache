#ifndef _EBO_TEST_$D$_CLR_H_INCLUDED
#define _EBO_TEST_$D$_CLR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Sep-2024 at 13:05:20.849, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared draw color interface declaration file; 
*/
#include "_log.h"

#include "color._defs.h"
#include "color.alpha.h"
#include "color.rgb.h"

#include "color.compl.h"
#include "color.compl.predefs.h"

#include "color.gradient.h"

#include "color.named.h"
#include "color.x11.h"

#pragma comment(lib, "color_v15.lib")        // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

namespace ebo { namespace boo { namespace test { namespace color { namespace rgb {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using TPercent = TPct_Flt;
	using clr_type = ex_ui::color::rgb::clr_type;

	__class(CAlpha) {
	public:
		__ctor(_ctor);
	};

	using TColor = ex_ui::color::rgb::CColor; // the same meaning as TRgbColor typedef has;

	__class(CColor) {
	public:
		 CColor (const bool _b_verb = false);
		~CColor (void) = default;

	public:
		__ctor (_ctor);
		__method (Darken);
		__method (Differ);
		__method (Lighten);

	private:
		bool    m_b_verb;
		TRgbColor m_color;
	};

	using TFloat = ex_ui::color::rgb::CFloat;

	__class(CFloat) {
	public:
		 CFloat (void) = default;
		~CFloat (void) = default;

	public:
		__method(ViceVersa);

	private:
		TFloat m_clr_f;
	};

	__class(CPercent) {
	public:
		 CPercent (const bool _b_verb = false);
		~CPercent (void) = default;

	public:
		__ctor (_ctor);
		__method (Is_equal);

	private:
		bool   m_b_verb;
		TPct_Flt m_percnt;
	};

	__class(CQuad) {
	public:
		 CQuad (const bool _b_verb = false);
		~CQuad (void) = default;

	public:
		__ctor (_ctor);
		__method (EqualTo);

	private:
		bool   m_b_verb;
		TRgbQuad m_quad;	
	};

}}}}}

#endif/*_EBO_TEST_$D$_CLR_H_INCLUDED*/