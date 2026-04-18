#ifndef _CONSOLE_FONT_H_INCLUDED
#define _CONSOLE_FONT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Oct-2022 at 00:09:08.703, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Windows system console font wrapper interface declaration file;
*/
#include "console.defs.h"
namespace shared { namespace console {

	// https://stackoverflow.com/questions/35382432/how-to-change-the-console-font-size/35383318 ;

	typedef CONSOLE_FONT_INFO   ConFntInfo;    // https://learn.microsoft.com/en-us/windows/console/coord-str ;
	typedef CONSOLE_FONT_INFOEX ConFntInfoEx;  // https://learn.microsoft.com/en-us/windows/console/console-font-infoex ;

	/* https://stackoverflow.com/questions/64785427/c-windows-api-how-to-retrieve-font-scaling-percentage << good question but it has not good answer:
	   Windows UWP is never been native API, so it is other level/intermediate layer of abstraction by involving so named WinRT;
	   the good answer of the question made in above article is https://stackoverflow.com/a/78226131/4325555 ; thanks Ian Boyd for thinking in right direction;
	*/
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-textmetrica ;
	class CFont {
	public:
		 CFont (void); CFont (const CFont&); CFont (CFont&&) = delete;
		~CFont (void) = default;

		const
		ConFntInfoEx& Get (void); // re-call the system function to retrieve the font info in case when font structure is unset;
		err_code      Set (_pc_sz _p_face_name, const int16_t _cy); // TODO: it is assumed that font family is TMPF_TRUETYPE, when new font is set;

		// because a user has a chance of not selecting the desired font size from the dropdown list, but to type directly the size that is not in the list;
		TError&  Error (void) const;
		bool     Is    (void) const;   // checks the condole font structure for validity of data; 
		const
		t_size&  Size  (void) const;   // gets font size of console output in *pixels*;
		const
		ConFntInfoEx& Raw (void) const;
		ConFntInfoEx& Raw (void)      ;

		CFont&  operator = (const CFont&);
		CFont&  operator = (CFont&&) = delete;

		operator bool (void) const;     // calls CFont::Is();
		const
		ConFntInfoEx& operator ()(void) const;
		ConFntInfoEx& operator ()(void) ;

		bool operator != (const CFont&);

		static t_size To_pixels (const COORD&);  // converts logical units of the font size to pixels;

	private:
		CError m_error;
		ConFntInfoEx m_info;
		t_size m_size; // font size is measured in logical units in appropriate with currently set DPI, this class field contains font size in pixels;
	};
#if (0)
	// this is the class for going geometrical metrics of the font size in logical units
	class CFnt_Metrics {
	public:
		CFnt_Metrics (void) ; CFnt_Metrics (const CFnt_Metrics&) = delete; CFnt_Metrics (CFnt_Metrics&&) = delete; ~CFnt_Metrics (void) = default;

	private:
		CFnt_Metrics& operator = (const CFnt_Metrics&) = delete; CFnt_Metrics& operator = (CFnt_Metrics&&) = delete;
	};
#endif
}}
#endif/*_CONSOLE_FONT_H_INCLUDED*/