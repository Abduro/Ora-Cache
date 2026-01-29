#ifndef _EBO_TEST_$D$_ZBUF_OBJECT_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_OBJECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jul-2025 at 00:23:57.297, UTC+4, Batumi, Sunday;
	This is Ebo Pack WinAPI GDI in-memory bitmap wrappers unit test interface declaration file;
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace bitmap {

	using namespace ebo::boo::test::draw;

	using TDibSection = ex_ui::draw::bitmaps::CDibSection;

	__class(CDibSection) {
	public:
		 CDibSection (const bool _b_verb = false);
		~CDibSection (void) = default;

	public:
		__ctor (_ctor);
		__method (Create);

	private:
		bool      m_b_verb;
		TDibSection  m_dib;
	};

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_OBJECT_H_INCLUDED*/