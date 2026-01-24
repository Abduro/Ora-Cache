#ifndef _EBO_TEST_$D$_VERT_ARR_DAT_H_INCLUDED
#define _EBO_TEST_$D$_VERT_ARR_DAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Jan-2026 at 11:12:22.502, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL vertex array data wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.vert.arr.dat.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_vert_dat) {
	public:
		 c_vert_dat (const e_object = e_object::e_tria); // the test framework requires default constructor;
		~c_vert_dat (void) = default;

		__method (Create);
		__method (Delete);

		const
		TPipe&  operator ()(void) const;
		TPipe&  operator ()(void) ;
		c_vert_dat& operator << (const e_object) ; // should be called before run of test cases if target object type is changed;

	private:
		TPipe m_pipe; // for draw target type;
	};

}}}}}

#endif/*_EBO_TEST_$D$_VERT_ARR_DAT_H_INCLUDED*/