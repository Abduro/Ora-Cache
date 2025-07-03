#ifndef _EBO_TEST_$D$_THEME_REG_H_INCLUDED
#define _EBO_TEST_$D$_THEME_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2025 at 12:58:49.352, UTC+4, Batumi, Tuesday;
	This is Ebo Pack custom color theme registry interface unit test declaration file; 
*/
#include "ebo_test_$d$.theme.defs.h"

namespace ebo { namespace boo { namespace test { namespace theme {

	using TRegistry  = ex_ui::theme::storage::CRegistry;
	using TRouter    = ex_ui::theme::storage::CReg_router;

	using TRawStates = ex_ui::theme::TRawStates;

	__class (CRouter) {
	public:
		 CRouter (const bool _b_verb = false);
		~CRouter (void) = default;

	public:
		__method (Get_paths);

	private:
		bool      m_b_verb;
		TRouter   m_router;
	};

	__class (CRegistry) {
	public:
		 CRegistry (const bool _b_verb = false);
		~CRegistry (void) = default;

	public:
		__method (Get_Element);
		__method (Get_Palette);
		__method (Get_Part);
		__method (Get_State);

	private:
		bool      m_b_verb;
		TRegistry m_storage;
	};

}}}}

#endif/*_EBO_TEST_$D$_THEME_REG_H_INCLUDED*/