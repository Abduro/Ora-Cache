#ifndef _SYS_SHELL_FONT_H_INCLUDED
#define _SYS_SHELL_FONT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jun-2025 at 22:34:50.687, UTC+4, Batumi, Friday;
	This is Ebo Pack system font collection generic wrapper interface declaration file;
*/
#include "sys.shell.inc.h"

namespace shared { namespace sys_core { namespace shell {

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-enumfontfamiliesexa ;
	// https://learn.microsoft.com/en-us/previous-versions/dd162618(v=vs.85) ;
	// this stuff is not required yet;
#if (0)
	class CFontStub {
	public:
		 CFontStub (void); CFontStub (const CFontStub&); CFontStub(CFontStub&&);
		~CFontStub (void);

	public:
		const
		LOGFONT&   Raw (void) const;
		LOGFONT&   Raw (void) ;

	public:
		CFontStub&  operator = (const CFontStub&);
		CFontStub&  operator = (CFontStub&&);
		CFontStub&  operator <<(const LOGFONT&);

		operator const LOGFONT& (void) const;
		operator       LOGFONT& (void) ;

	private:
		LOGFONT  m_log;
	};

	typedef ::std::vector<CFontStub> TFntInstalled;
#endif
	typedef ::std::vector<CString> TFntList;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-addfontresourcea   ; for installing the required font dynamically;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-addfontresourceexa ; for the private access;
	// this class enumerates all installed fonts in the operating system;
	class CFonts {
	public:
		 CFonts (void); CFonts (const CFonts&) = delete; CFonts (CFonts&&) = delete;
		~CFonts (void);

	public:
		TError&  Error (void) const;
		err_code GetInstalled (void);
#if (0)
		const
		TFntInstalled&  Raw (void) const;
#else
		bool     Has  (_pc_sz _p_name) const; // returns 'true' in case of installed font set contains the font of the input name;
		const
		TFntList List (void) const;
#endif
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	public:
		CFonts&  operator = (const CFonts&) = delete;
		CFonts&  operator = (CFonts&&) = delete;

	private:
#if (0)
		TFntInstalled m_installed;
#else
		TFntList m_installed;
#endif
		CError   m_error;
	};

}}}

#endif/*_SYS_SHELL_FONT_H_INCLUDED*/