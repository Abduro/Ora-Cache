#ifndef _TEST_CASE_$W$_CON_MODE_H_INCLUDED
#define _TEST_CASE_$W$_CON_MODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 09:57:20.277, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' trace console mode interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$w$.defs.h"
#include "console.mode.h"

namespace ebo { namespace boo { namespace test { namespace con {
namespace modes {

	using t_input = shared::console::modes::CInput;
	using t_output = shared::console::modes::COutput;

	class c_mode_input {
	public:
		 c_mode_input (void) = default; c_mode_input (const c_mode_input&) = delete; c_mode_input (c_mode_input&&) = delete;
		~c_mode_input (void) = default;

		uint32_t Get  (void);
		err_code Set  (const uint32_t);

		const
		t_input& operator ()(void) const;
		t_input& operator ()(void) ;

	private:
		c_mode_input& operator = (const c_mode_input&) = delete; c_mode_input& operator = (c_mode_input&&) = delete;
		t_input m_input;
	};

	class c_mode_output {
	public:
		 c_mode_output (void) = default; c_mode_output (const c_mode_output&) = delete; c_mode_output (c_mode_output&&) = delete;
		~c_mode_output (void) = default;

		uint32_t Get  (void);
		err_code Set  (const uint32_t);

		const
		t_output& operator ()(void) const;
		t_output& operator ()(void) ;

	private:
		c_mode_output& operator = (const c_mode_output&) = delete; c_mode_output& operator = (c_mode_output&&) = delete;
		t_output m_output;
	};

}}}}}

#endif/*_TEST_CASE_$W$_CON_MODE_H_INCLUDED*/