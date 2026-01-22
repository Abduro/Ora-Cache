#ifndef _TEST_CASE_$D$_UNIFORM_H_INCLUDED
#define _TEST_CASE_$D$_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jan-2026 at 14:38:45.084, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL uniform data type wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.render.h"
#include "gl_uniform.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CUniEnum  = ex_ui::draw::open_gl::vars::CUniform_enum;
	using CU_frm_v4 = ex_ui::draw::open_gl::vars::CU_frm_v4;
	using CU_val_v4 = ex_ui::draw::open_gl::vars::CU_val_v4;

	using TUniVars  = ex_ui::draw::open_gl::vars::TU_vars_v4;

	using t_uniform_3f = procs::vars::t_uniform_3f;
	using t_uniform_4f = procs::vars::t_uniform_4f;

	/* the running this tests requires:
		(1) creating the renderer context;
		(2) compiling shaders and linking a program;
		(3) creating a shape, for examole, a triangle;
		(4) starting to draw the shape for executing the shaders code;
		(5) ***running the test case of a uniform variable;***
		(6) ending up the draw operation by destroying all objects related to draw operation;
	*/

	// https://www.allacronyms.com/uniform/abbreviated ;

	class CUni_enum : public TPipe {
	public:
		CUni_enum (const e_object = e_object::e_none); CUni_enum (const CUni_enum&) = delete; CUni_enum (CUni_enum&&) = delete; ~CUni_enum (void) = default;

		static
		uint32_t Count (const e_object, CError&);
		uint32_t Count (void) const; // to-do: getting the active program from the global renderer should be considered; (done)

		TError&  Error (void) const;
#if (0)
		static
		err_code Get (const e_object, TUniVars&, CError&); // enumerates all u-form variables of the program by given identifier;
		err_code Get (void); // without open_gl draw functions the uniform variable has default value;

		static
		err_code OnDraw (const e_object, TUniVars&, CError&); // invokes open_gl draw functions for getting shaders' script executed;
		err_code OnDraw (void);
#endif
		const
		TUniVars& Vars (void) const;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		CUni_enum& operator = (const CUni_enum&) = delete; CUni_enum& operator = (CUni_enum&&) = delete;
		mutable
		CError   m_error;
		TUniVars m_vars;
	};

#if (0)
	class CUni_form {
	public:
		CUni_form (void); CUni_form (const CUni_form&) = delete; CUni_form (CUni_form&&) = delete; ~CUni_form (void) = default;

		TError& Error (void) const;
		static
		CString To_str (const CUniform&);

	private:
		CUni_form& operator = (const CUni_form&) = delete; CUni_form& operator = (CUni_form&&) = delete;
		CError  m_error;
	};
#endif
	
	class CUf_val_v4 : public TPipe {
	public:
		CUf_val_v4 (const e_object = e_object::e_none);
		CUf_val_v4 (const CUf_val_v4&) = delete; CUf_val_v4 (CUf_val_v4&&) = delete; ~CUf_val_v4 (void) = default;

		TError& Error (void) const;
		static
		err_code Get (const e_object, const uint32_t _locate, t_uniform_4f&, CError&); 

	private:
		CUf_val_v4& operator = (const CUf_val_v4&) = delete; CUf_val_v4& operator = (CUf_val_v4&&) = delete;
		CError  m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_UNIFORM_H_INCLUDED*/