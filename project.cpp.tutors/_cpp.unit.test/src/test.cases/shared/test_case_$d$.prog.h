#ifndef _TEST_CASE_$D$_PROG_H_INCLUDED
#define _TEST_CASE_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:36:34.036, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL shader program wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "gl_program.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CProgram  = ex_ui::draw::open_gl::CProgram;

	class CProg : public CPipeline { typedef CPipeline TBase; // the pipline helps to identify the target draw object;
	public:
		CProg (const e_object = e_object::e_grid); // creates grid program by default for testing matrices throug shaders;
		CProg (const CProg&) = delete; CProg (CProg&&) = delete; ~CProg (void) = default;

		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;

	private:
		CProg& operator = (const CProg&) = delete; CProg& operator = (CProg&&) = delete;
		CError   m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_PROG_H_INCLUDED*/