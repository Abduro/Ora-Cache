#ifndef _CON_CMD_LINE_INCLUDED
#define _CON_CMD_LINE_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Apr-2012 at 07:46:04pm, GMT+3, Rostov-on-Don, Sunday;
	This is Pulsepay project server application generic command line interface declaration file. [oDesk.com]
	-----------------------------------------------------------------------------[oDesk.com]
	Adopted to Platinum Clocking project on 19-Mar-2014 at 8:17:25am, GMT+4, Taganrog, Wednesday;
	Adopted to BotRevolt project on 21-Aug-2014 at 6:06:46am, GMT+4, Taganrog, Thursday;
	-----------------------------------------------------------------------------[Upwork.com]
	Adopted to FG (thefileguardian.com) project on 11-Jun-2016 at 1:28:28p, GMT+7, Phuket, Rawai, Saturday;
	Adopted to sound-bin-trans project on 5-Apr-2019 at 11:52:11a, UTC+7, Phuket, Rawai, Friday;
*/
#include <atlbase.h>
#include <shellapi.h>   // for CommandLineToArgvW(); https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-commandlinetoargvw;
#include <processenv.h> // for ::GetCommandLine(); https://learn.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getcommandlinea ;

#include <map>
#include <vector>

#include "sys.error.h"
#include "sys.err.codes.h"

#include "shared.string.h"
#include "shared.types.h"

namespace ebo { namespace boo { namespace test {

	using namespace shared::types;

	typedef ::std::map<CString, CString> TCmdLineArgs;  // a key is an argument name, value is argument value;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx;

	class CCommandLine {
	public:
		 CCommandLine (void);                     // gets all available command line arguments;
		 CCommandLine (const CCommandLine&);      // just make copying;
		 CCommandLine (CCommandLine&&) = delete;  // not required yet;
		~CCommandLine (void);                     // just clean the collection of arguments if any;

	public:
		err_code      Append(_pc_sz _p_sz_name, _pc_sz _p_sz_value);         // appends new command line argument to the collection;
		err_code      Append(_pc_sz _p_sz_name, long _l_value);
		CString       Arg   (_pc_sz _p_sz_name) const;                       // gets an argument value as string, if not found empty value is returned;
		_long         Arg   (_pc_sz _p_sz_name, const _long _def_val) const; // gets an argument value as long, if not found the default value is returned;
		TCmdLineArgs  Args  (void) const;                                    // returns a copy of command line argument collection
		void          Clear (void)      ;
		uint16_t      Count (void) const;
		bool          Has   (_pc_sz pszArgName) const;                       // checks the existance an argument with the name specified;
		CString       Path  (void) const;                                    // returns executable absolute path, that is the first arg in the command line;

		TError&  Error (void) const;
#if defined (_DEBUG)
		CString  Print (void) const;
#endif

	public:
		CString       ToString (_pc_sz _p_sz_sep = NULL) const;

	public:
		CCommandLine& operator = (const CCommandLine&);
		CCommandLine& operator = (CCommandLine&&) = delete;

	public:
		operator        _pc_sz (void) const;         // returns command line object as a string;
		bool operator==(_pc_sz pszArgName) const;    // finds an argument by name provided;

	private:
		mutable
		CError  m_error;
		CString   m_module_path;
		TCmdLineArgs m_args;
	};

	class CArgument {
	public:
		 CArgument (void);
		 CArgument (const CArgument&);
		 CArgument (const _word _w_res_name, const _word _w_res_verb, const dword _dw_type);
		 CArgument (_pc_sz _l_sz_name, _pc_sz _p_sz_verb, const dword _dw_type);
		~CArgument (void);

	public:
		bool      Is   (void) const;
		_pc_sz    Name (void) const;
		err_code  Name (const _word _w_res_id);
		err_code  Name (_pc_sz _p_sz_name );
		dword     Type (void) const;
		bool      Type (const dword);
		_pc_sz    Verb (void) const;
		err_code  Verb (const _word _w_res_id);
		err_code  Verb (_pc_sz _p_sz_desc );

	public:
		CArgument& operator = (const CArgument&);

	public:
		bool operator == (const CArgument&) const;
		bool operator == (_pc_sz _lp_sz_name) const;

	protected:
		DWORD     m_type;
		CString   m_name;
		CString   m_verb;
	};
}}}

typedef ebo::boo::test::CArgument     TArgument;
typedef ::std::vector<TArgument>      TArguments;
typedef ebo::boo::test::CCommandLine  TCmdLine;

#endif/*_CON_CMD_LINE_INCLUDED*/