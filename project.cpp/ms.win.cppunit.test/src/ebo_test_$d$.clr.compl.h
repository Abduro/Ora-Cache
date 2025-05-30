#ifndef _EBO_TEST_$D$_CLR_COMPL_H_INCLUDED
#define _EBO_TEST_$D$_CLR_COMPL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:29:27.467, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw complementary color unit test interface declaration file; 
*/
#include "ebo_test_$d$.clr.h"

namespace ebo { namespace boo { namespace test { namespace color { namespace compl {

	using TOne = ex_ui::color::complementary::COne;

	__class(COne) {
	public:
		 COne (const bool _b_verb = false);
		~COne (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool   m_b_verb;
		TOne   m_compl;
	};

	using TSet = ex_ui::color::complementary::CSet;

	__class(CSet) {
	public:
		 CSet (const bool _b_verb = false);
		~CSet (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool   m_b_verb;
		TSet   m_set;
	};

	using TSet_enum = ex_ui::color::complementary::CSet_Enum;

	__class(CEnum) {
	public:
		 CEnum (const bool _b_verb = false);
		~CEnum (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool    m_b_verb;
		TSet_enum m_enum;
	};

	using TPredefs = ex_ui::color::complementary::CPredefined;

	__class(CPredefs) {
	public:
		 CPredefs (const bool _b_verb = false);
		~CPredefs (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool     m_b_verb ;
		TPredefs m_predefs;
	};

}}}}}

#endif/*_EBO_TEST_$D$_CLR_COMPL_H_INCLUDED*/