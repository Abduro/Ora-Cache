#ifndef _EBO_TEST_$D$_ZBUF_CACHE_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jul-2025 at 10:48:07.749, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI in-memory image cache unit test interface declaration file;
*/
#include "ebo_test_$d$.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	using TCacheItem = ex_ui::draw::images::CItem;

	__class(CCacheItem) {
	public:
		 CCacheItem (const bool _b_verb = false);
		~CCacheItem (void) = default;

	public:
		__ctor (_ctor);
		__method (Create);

	private:
		bool      m_b_verb;
		TCacheItem  m_item;
	};

}}}}

#endif/*_EBO_TEST_$D$_ZBUF_CACHE_H_INCLUDED*/