#ifndef _EBO_TEST_$D$_ZBUF_BLEND_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_BLEND_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2025 at 17:45:49.468, UTC+4, Batumi, Tuesday;
	This is Ebo Pack WinAPI GDI in-memory draw blend renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

#pragma region __blend

	using TBlend_Wrap = ex_ui::draw::blend::CBlend_Wrap;

	__class(CBlend_Wrap) {
	public:
		 CBlend_Wrap (const bool _b_verb = false);
		~CBlend_Wrap (void) = default;

	public:
		__method (_ctor);

	private:
		bool m_b_verb;
		TBlend_Wrap  m_bl_wrap;
	};


#pragma endregion

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_BLEND_H_INCLUDED*/