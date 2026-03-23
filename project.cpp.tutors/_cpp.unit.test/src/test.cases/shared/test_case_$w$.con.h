#ifndef _TEST_CASE_$W$_CON_H_INCLUDED
#define _TEST_CASE_$W$_CON_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 20:59:27.699, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' trace console interface declaration file for using in test cases adapters;
*/
#include "test_case_$w$.con.evt.h"
#include "test_case_$w$.con.mode.h"
#include "console.h"

namespace ebo { namespace boo { namespace test { namespace con {

	/* query: can console window be created from test case of MSTest Framework (to Google AI);
	   In the MSTest Framework, a standard console window is *not* automatically created or displayed when a test case is executed.
	   Instead, MSTest redirects all standard output to the test results for later viewing;
	   Possible solutions:
	   (1) open a physical console window (advanced) by using AllocConsole();
	       This forces the operating system to attach a console window to the current test process; (possibly good approach);
	   (2) use the MSTest console runner:
	       VSTest.Console.exe command-line options are here https://learn.microsoft.com/en-us/visualstudio/test/vstest-console-options?view=visualstudio ;
	   (3) debug via a console app wrapper, it seems to be the best solution;
	*/

	using t_wrap = shared::console::CWrap;

	class c_con_wrap {
	public:
		 c_con_wrap (void) = default; c_con_wrap (const c_con_wrap&) = delete; c_con_wrap (c_con_wrap&&) = delete;
		~c_con_wrap (void) = default;

		err_code Create (void); // creates console process with visible window and attaches to the process;
		err_code Detach (void); // detaches from the console; the console process must be ended automatically by OS;

		const
		t_wrap& operator ()(void) const;
		t_wrap& operator ()(void) ;

	private:
		c_con_wrap& operator = (const c_con_wrap&) = delete; c_con_wrap& operator = (c_con_wrap&&) = delete;
		t_wrap m_wrap; // it is required for keeping console attached between calling this class methods;
	};

}}}}

#endif/*_TEST_CASE_$W$_CON_H_INCLUDED*/