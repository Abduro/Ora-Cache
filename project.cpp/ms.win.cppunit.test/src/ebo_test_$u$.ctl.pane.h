#ifndef _EBO_TEST_$U$_CTL_PANE_H_INCLUDED
#define _EBO_TEST_$U$_CTL_PANE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Jul-2025 at 13:16:03.655, UTC+4, Batumi, Wednesday;
	This is Ebo Pack user control base pane unit test interface declaration file; 
*/
#include "ebo_test_$u$.ctl.base.h"

namespace ebo { namespace boo { namespace test { namespace ctl { namespace base {

	using TPane = ex_ui::controls::CPane;

	__class (CPane) {
	public:
		 CPane (const bool _b_verb = false);
		~CPane (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool  m_b_verb;
		TPane m_pane;
	};
}}}}}
#endif/*_EBO_TEST_$U$_CTL_PANE_H_INCLUDED*/