#ifndef _EBO_TEST_$D$_CLR_GRAD_H_INCLUDED
#define _EBO_TEST_$D$_CLR_GRAD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:33:21.828, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw color gradient unit test interface declaration file; 
*/
#include "ebo_test_$d$.clr.h"

namespace ebo { namespace boo { namespace test { namespace color { namespace rgb {

	using TGrad = ex_ui::color::rgb::CGradient;

	__class(CGradient) {
	public:
		 CGradient (const bool _b_verb = false);
		~CGradient (void) = default;

	public:
		__ctor (_ctor);
		__method (Is_valid);

	private:
		bool   m_b_verb;
		TGrad  m_grad;
	};

	using TGrad_strip = ex_ui::color::rgb::CGradient_Strip;

	__class(CGrad_strip) {
	public:
		 CGrad_strip (const bool _b_verb = false);
		~CGrad_strip (void) = default;

	public:
		__ctor (_ctor);
		__method (Modify);

	private:
		bool  m_b_verb;
		TGrad_strip m_strip;
	};


}}}}}

#endif/*_EBO_TEST_$D$_CLR_GRAD_H_INCLUDED*/