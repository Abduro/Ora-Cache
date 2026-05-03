#ifndef _CONSOLE_MODE_H_INCLUDED
#define _CONSOLE_MODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 14:03:05.184, UTC+4, Batumi, Saturday;
	This is system console moden wrapper interface declaration file;
*/
#include "console.defs.h"

namespace shared { namespace console { namespace modes { using namespace shared::console;

	// https://learn.microsoft.com/en-us/windows/console/getconsolemode ;
	// https://learn.microsoft.com/en-us/windows/console/setconsolemode ;

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

		bool     EditMode (void);                  // checks input mode of console for enabling/disabling 'quick edit' option;
		err_code EditMode (const bool _yes_or_no); // disables/enables quick edit mode; this mode does not allow to use context menu or to handle pressing right button of mouse;

		err_code Get (void);
		err_code Set (const ulong _u_flags);

		static bool Has (const ulong _u_flags); // returns 'true' in case if given flag set contains at least one flag that is acceptable for input buffer;
		static _pc_sz To_str (const ulong _u_flags);

		err_code operator <<(const ulong _u_flags);
	};

	class COutput : public CBase {
	public:
		COutput (void); ~COutput (void) = default;

		err_code Get (void);
		err_code Set (const ulong _u_flags);

		static bool Has (const ulong _u_flags); // returns 'true' in case if given flag set contains at least one flag that is acceptable for output buffer;
		static _pc_sz To_str (const ulong _u_flags);

		err_code operator <<(const ulong _u_flags);
	};
}}}

#endif/*_CONSOLE_MODE_H_INCLUDED*/