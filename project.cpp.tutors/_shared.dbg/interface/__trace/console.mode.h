#ifndef _CONSOLE_MODE_H_INCLUDED
#define _CONSOLE_MODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 14:03:05.184, UTC+4, Batumi, Saturday;
	This is system console moden wrapper interface declaration file;
*/
#include "console.defs.h"

namespace shared { namespace console { namespace modes { using namespace shared::console;

	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		TError& Error (void) const;

		ulong   Flags (void) const;
		ulong&  Flags (void) ;

	protected:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		CError m_error;
		ulong  m_flags;
	};

	class CInput : public CBase {
	public:
		CInput (void); ~CInput (void) = default;

		err_code Get (void);
		err_code Set (void);

		static
		_pc_sz To_str (const ulong _u_flags);
	};

	class COutput : public CBase {
	public:
		COutput (void); ~COutput (void) = default;

		err_code Get (void);
		err_code Set (void);

		static
		_pc_sz To_str (const ulong _u_flags);
	};

	// https://learn.microsoft.com/en-us/windows/console/getconsolemode ;
	// https://learn.microsoft.com/en-us/windows/console/setconsolemode ;

	class CMode {
	public:
		 CMode (void) = default; CMode (const CMode&) = delete; CMode (CMode&&) = delete;
		~CMode (void) = default;

		const
		CInput& In (void) const;
		CInput& In (void) ;
		const
		COutput& Out (void) const;
		COutput& Out (void) ;

	private:
		CMode& operator = (const CMode&) = delete; CMode& operator = (CMode&&) = delete;
		CInput  m_input;
		COutput m_output;
	};
}}}

#endif/*_CONSOLE_MODE_H_INCLUDED*/