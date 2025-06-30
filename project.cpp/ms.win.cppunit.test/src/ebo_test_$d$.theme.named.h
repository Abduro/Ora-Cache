#ifndef _EBO_TEST_$D$_THEME_NAMED_H_INCLUDED
#define _EBO_TEST_$D$_THEME_NAMED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:35:01.886, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme named interface unit test declaration file; 
*/
#include "ebo_test_$d$.theme.defs.h"

namespace ebo { namespace boo { namespace test { namespace themes {

	using TNamed = ex_ui::theme::CNamed;

	__class (CNamed) {
	public:
		 CNamed (const bool _b_verb = false);
		~CNamed (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TNamed  m_named;
	};

	using TNamed_Enum = ex_ui::theme::CNamed_Enum;

	__class (CNamed_Enum) {
	public:
		 CNamed_Enum (const bool _b_verb = false);
		~CNamed_Enum (void) = default;

	public:
		__ctor (_ctor);
		__method (Load);

	private:
		bool   m_b_verb;
		TNamed_Enum  m_named_enum;
	};

	using TState = ex_ui::theme::CState;

	__class (CState) {
	public:
		 CState (const bool _b_verb = false);
		~CState (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);

	private:
		bool    m_b_verb;
		TState  m_state ;
	};
}}}}

#endif/*_EBO_TEST_$D$_THEME_NAMED_H_INCLUDED*/