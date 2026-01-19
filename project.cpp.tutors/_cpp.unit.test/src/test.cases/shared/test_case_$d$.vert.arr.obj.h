#ifndef _TEST_CASE_$D$_VERT_ARR_OBJ_H_INCLUDED
#define _TEST_CASE_$D$_VERT_ARR_OBJ_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jan-2026 at 20:51:56.282, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL vertex array object wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "gl_vertex_arr.obj.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;
	using namespace ex_ui::draw::open_gl;

	using CArrObject = vertex::CArrObject;

	CArrObject& __vao_accessor (const e_object _target);

	class CVertArrObj : public TPipe {
	public:
		CVertArrObj (const e_object = e_object::e_none); ~CVertArrObj (void) = default;
		CVertArrObj (const CVertArrObj&) = delete; CVertArrObj (CVertArrObj&&) = delete;

		err_code Create (void);  // creates vertex array buffer and its vertex array data;
		err_code Delete (void);  // deletes vertex array buffer and its vertex array data;

		TError&  Error (void) const;
		bool  Is_valid (void) const;

		uint32_t GetId (void) const;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		CVertArrObj& operator = (const CVertArrObj&) = delete; CVertArrObj& operator = (CVertArrObj&&) = delete;
		CError m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_VERT_ARR_OBJ_H_INCLUDED*/