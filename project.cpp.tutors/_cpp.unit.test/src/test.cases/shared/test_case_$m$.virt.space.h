#ifndef _TEST_CASE_$M$_VIRT_SPACE_H_INCLUDED
#define _TEST_CASE_$M$_VIRT_SPACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Feb-2026 at 11:53:13.379, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL draw virtual space wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_case_$m$.matrix.h"
#include "virt_space.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math { using namespace ex_ui::draw::open_gl::space;

	using TAxes_Fix = axes::CFixed;
	using TAxes_Dyn = axes::CDynamic;

	class CTAxes_Dyn {
	public:
		CTAxes_Dyn (void); ~CTAxes_Dyn (void) = default; CTAxes_Dyn (const CTAxes_Dyn&) = delete; CTAxes_Dyn (CTAxes_Dyn&&) = delete;

		static CString To_str (const TAxes_Dyn&);

	private:
		CTAxes_Dyn& operator = (const CTAxes_Dyn&) = delete; CTAxes_Dyn& operator = (CTAxes_Dyn&&) = delete;
	};

	class CTAxes_Fix {
	public:
		CTAxes_Fix (void); ~CTAxes_Fix (void) = default; CTAxes_Fix (const CTAxes_Fix&) = delete; CTAxes_Fix (CTAxes_Fix&&) = delete;

		static CString To_str (const TAxes_Fix&);

	private:
		CTAxes_Fix& operator = (const CTAxes_Fix&) = delete; CTAxes_Fix& operator = (CTAxes_Fix&&) = delete;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VIRT_SPACE_H_INCLUDED*/