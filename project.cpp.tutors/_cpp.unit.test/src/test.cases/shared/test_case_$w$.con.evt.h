#ifndef _TEST_CASE_$W$_CON_EVT_H_INCLUDED
#define _TEST_CASE_$W$_CON_EVT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 08:07:22.495, UTC+4, Batumi, Monday;
	This is Ebo Pack trace console input event wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$w$.defs.h"
#include "console.event.h"

namespace test { namespace win_api { namespace console { namespace events {
	/* query: abbreviation for router; (Google AI)
	   common abbreviations for a router include: RTR (frequently used in technical documentation) or simply RT;
	*/
	using t_rtr_ctrl  = shared::console::events::ctrl::CRouter;
	using t_rtr_input = shared::console::events::input::CRouter;

	class c_rtr_ctrl {
	public:
		 c_rtr_ctrl (void) = default; c_rtr_ctrl (const c_rtr_ctrl&) = delete; c_rtr_ctrl (c_rtr_ctrl&&) = delete;
		~c_rtr_ctrl (void) = default;

		const
		t_rtr_ctrl& operator ()(void) const;
		t_rtr_ctrl& operator ()(void) ;

	private:
		c_rtr_ctrl& operator = (const c_rtr_ctrl&) = delete; c_rtr_ctrl& operator = (c_rtr_ctrl&&) = delete;
		t_rtr_ctrl  m_rtr_ctrl;
	};

	class c_rtr_input {
	public:
		 c_rtr_input (void) = default; c_rtr_input (const c_rtr_input&) = delete; c_rtr_input (c_rtr_input&&) = delete;
		~c_rtr_input (void) = default;

		err_code Turn (const bool _b_on_off); // starts or stops the input buffer event receiving;

		const
		t_rtr_input& operator ()(void) const;
		t_rtr_input& operator ()(void) ;

	private:
		c_rtr_input& operator = (const c_rtr_input&) = delete; c_rtr_input& operator = (c_rtr_input&&) = delete;
//		t_rtr_input  m_rtr_input; there is a singleton of this router because only one console can be associated with the process;
	};

}}}}

#endif/*_TEST_CASE_$W$_CON_EVT_H_INCLUDED*/