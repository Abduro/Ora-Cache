#ifndef _TEST_CASE_$W$_CMD_LN_H_INCLUDED
#define _TEST_CASE_$W$_CMD_LN_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Jul-2026 at 13:24:29.364, UTC+4, Batumi, Thursday;
	This is Ebo Pack generic command line wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$w$.defs.h"
#include "shared.cmd.ln.h"

namespace test { namespace win_api { namespace input {

	using CCmdLine = ::shared::input::CCmdLine;

	class CTstCmdLn {
	public:
		CTstCmdLn (const bool _b_verbose = true); CTstCmdLn (const CTstCmdLn&) = delete; CTstCmdLn (CTstCmdLn&&) = delete; ~CTstCmdLn (void) = default;

		err_code Parse (void); // parses command line received by calling ::GetCommandLine();

		const
		CCmdLine& operator ()(void) const;
		CCmdLine& operator ()(void) ;

		CTstCmdLn& operator <<(const bool _b_verbose);

	private:
		CTstCmdLn& operator = (const CTstCmdLn&) = delete; CTstCmdLn& operator = (CTstCmdLn&&) = delete;
		bool m_verbose;
		CCmdLine m_cmd_ln;
	};

}}}

#endif/*_TEST_CASE_$W$_CMD_LN_H_INCLUDED*/