#ifndef _EBO_TEST_$D$_VERT_ARR_OBJ_H_INCLUDED
#define _EBO_TEST_$D$_VERT_ARR_OBJ_H_INCLUDED
/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 18-Jan-2026 at 22:19:15.921, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex array object wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.vert.arr.obj.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_vert_arr_obj) {
	public:
		 c_vert_arr_obj (const e_object = e_object::e_tria); // the test framework requires default constructor;
		~c_vert_arr_obj (void) = default;

		__method (Create);
		__method (Delete);

		const
		TPipe&  operator ()(void) const;
		TPipe&  operator ()(void) ;
		c_vert_arr_obj& operator << (const e_object) ; // should be called before run of test cases if target object type is changed;

	private:
		TPipe m_pipe; // for draw target type;
	};

}}}}}

#endif/*_EBO_TEST_$D$_VERT_ARR_OBJ_H_INCLUDED*/