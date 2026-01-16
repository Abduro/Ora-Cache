#ifndef _TEST_CASE_$D$_UNIFORM_H_INCLUDED
#define _TEST_CASE_$D$_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jan-2026 at 14:38:45.084, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL uniform data type wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.render.h"
#include "test_case_$d$.shape.2d.h"
#include "gl_uniform.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CUniEnum  = ex_ui::draw::open_gl::vars::CUniform_enum;
	using CUniform  = ex_ui::draw::open_gl::vars::CUniform;
	using CUniValue = ex_ui::draw::open_gl::vars::CUniform::CValue;

	using TUniVars  = ex_ui::draw::open_gl::vars::TUniVars;

	// https://www.allacronyms.com/uniform/abbreviated ;

	class CUni_enum {
	public:
		CUni_enum (void); CUni_enum (const CUni_enum&) = delete; CUni_enum (CUni_enum&&) = delete; ~CUni_enum (void) = default;

		static
		uint32_t Count (const uint32_t _prog_id, CError&);
		uint32_t Count (const uint32_t _prog_id); // to-do: getting the active program from the global renderer should be considered;
		TError&  Error (void) const;
		static
		err_code Get (const uint32_t _prog_id, TUniVars&, CError&); // enumerates all u-fofm variables of the program by given identifier;
		err_code Get (const uint32_t _prog_id); // without open_gl draw functions the uniform variable has default value;

		static
		err_code OnDraw (TUniVars&, CError&); // invokes open_gl draw functions for getting shaders' script executed;
		err_code OnDraw (void);

		const
		TUniVars& Vars (void) const;

	private:
		CUni_enum& operator = (const CUni_enum&) = delete; CUni_enum& operator = (CUni_enum&&) = delete;
		CError   m_error;
		TUniVars m_vars;
		C3angle  m_shape;
	};

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

	class CUni_value {
	public:
		CUni_value (void); CUni_value (const CUni_value&) = delete; CUni_value (CUni_value&&) = delete; ~CUni_value (void) = default;

		TError& Error (void) const;

	private:
		CUni_value& operator = (const CUni_value&) = delete; CUni_value& operator = (CUni_value&&) = delete;
		CError  m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_UNIFORM_H_INCLUDED*/