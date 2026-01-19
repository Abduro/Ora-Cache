#ifndef _TEST_CASE_$D$_VERT_ARR_DAT_H_INCLUDED
#define _TEST_CASE_$D$_VERT_ARR_DAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Jan-2026 at 11:43:15.709, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL vertex array data wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "gl_vertex_arr.dat.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;
	using namespace ex_ui::draw::open_gl;

	using CVertArray = ex_ui::draw::open_gl::CVertArray;

	CVertArray& __vert_arr_accessor (const e_object _target);

	class CVertArrData : public TPipe {
	public:
		CVertArrData (const e_object = e_object::e_none); ~CVertArrData (void) = default;
		CVertArrData (const CVertArrData&) = delete; CVertArrData (CVertArrData&&) = delete;

		err_code Create (void); // creates vertex array buffer (aka vbo);
		err_code Delete (void); // deletes vertex array buffer (aka vbo);

		TError&  Error (void) const;
		bool  Is_valid (void) const; // checks data consistency of the vertex array data;

		uint32_t GetId (void) const; // vertex array does not have the identifier itself, but its data buffer has;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		CVertArrData& operator = (const CVertArrData&) = delete; CVertArrData& operator = (CVertArrData&&) = delete;
		CError m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_VERT_ARR_DAT_H_INCLUDED*/