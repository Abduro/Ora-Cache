#ifndef _EBO_TEST_$D$_IMG_STREAM_H_INCLUDED
#define _EBO_TEST_$D$_IMG_STREAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jul-2025 at 21:55:38.702, UTC+4, Batumi, Tuesday;
	This is Ebo Pack image stream wrapper unit test interface declaration file; 
*/
#include "ebo_test_$d$.img.defs.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using TStream = ex_ui::draw::images::CStream;

	__class (CStream) {
	public:
		 CStream (const bool _b_verb = false);
		~CStream (void) = default;

	public:
		__ctor (_ctor);
		__method (Load_image);

	private:
		bool    m_b_verb;
		TStream m_stream;
	};

}}}}

#endif/*_EBO_TEST_$D$_IMG_STREAM_H_INCLUDED*/