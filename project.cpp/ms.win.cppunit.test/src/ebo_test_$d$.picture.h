#ifndef _EBO_TEST_$D$_PICTURE_H_INCLUDED
#define _EBO_TEST_$D$_PICTURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:41:01.085, UTC+4, Batumi, Thursday;
	This is Ebo Pack component object picture wrapper unit test declaration file; 
*/
#include "ebo_test_$d$.img.defs.h"
#include "ebo_test_$d$.img.stream.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using TPicture = ex_ui::draw::images::CPicture;

	__class (CPicture) {
	public:
		 CPicture (const bool _b_verb = false);
		~CPicture (void) = default;

	public:
		__ctor (_ctor);
		__method (Load_file);

	private:
		bool  m_b_verb;
		TPicture m_picture;
	};

}}}}

#endif/*_EBO_TEST_$D$_PICTURE_H_INCLUDED*/