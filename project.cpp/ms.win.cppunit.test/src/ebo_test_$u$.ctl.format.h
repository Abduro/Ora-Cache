#ifndef _EBO_TEST_$U$_CTL_FORMAT_H_INCLUDED
#define _EBO_TEST_$U$_CTL_FORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jun-2025 at 09:43:19.035, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base format unit test interface declaration file; 
*/
#include "ebo_test_$u$.ctl.base.h"

namespace ebo { namespace boo { namespace test { namespace ctl {
namespace format {
	using TBkgnd = ex_ui::controls::format::CBkgnd;

	__class (CBkgnd) {
	public:
		 CBkgnd (const bool _b_verb = false);
		~CBkgnd (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TBkgnd  m_bkgnd ;
	};

	__class (CFontOpts) {
	public:
		 CFontOpts (const bool _b_verb = false);
		~CFontOpts (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);

	private:
		bool     m_b_verb;
		TFontOpts  m_opts;
	};

	using TFontSpec  = ex_ui::controls::format::CFontSpec;

	__class (CFontSpec) {
	public:
		 CFontSpec (const bool _b_verb = false);
		~CFontSpec (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);

	private:
		bool     m_b_verb;
		TFontSpec  m_spec;
	};
}
}}}}

#endif/*_EBO_TEST_$U$_CTL_FORMAT_H_INCLUDED*/