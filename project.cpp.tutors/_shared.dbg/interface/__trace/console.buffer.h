#ifndef _CONSOLE_BUFFER_H_INCLUDED
#define _CONSOLE_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 12:08:51.597, UTC+4, Batumi, Saturday;
	This is system console screen buffer wrapper interface declaration file;
*/
#include "console.defs.h"

namespace shared { namespace console {

	typedef CONSOLE_SCREEN_BUFFER_INFO    TScrBufInfo;    // https://learn.microsoft.com/en-us/windows/console/console-screen-buffer-info-str ;
	typedef CONSOLE_SCREEN_BUFFER_INFOEX  TScrBufInfoEx;  // https://learn.microsoft.com/en-us/windows/console/console-screen-buffer-infoex ;

	class CScreenBuffer {
	public:
		 CScreenBuffer (void);
		~CScreenBuffer (void);
		 CScreenBuffer (const CScreenBuffer&) = delete; CScreenBuffer (CScreenBuffer&&) = delete;

		err_code Clear (const t_char _symbol = _T(' ')); // clears console screen buffer by filling the given symbol;

		TError& Error (void) const;

		err_code Get (void);  // gets console screen buffer info;
		err_code Set (void);  // sets console screen buffer info;

		operator const TScrBufInfo& (void) const;
		operator       TScrBufInfo& (void)      ;

		TScrBufInfo&   operator ()  (void);

	private:
		CScreenBuffer& operator = (const CScreenBuffer&) = delete; CScreenBuffer& operator = (CScreenBuffer&&) = delete;
		CError m_error;
		TScrBufInfo m_info;
	};

	class CScreenBufferEx {
	public:
		 CScreenBufferEx (void);
		~CScreenBufferEx (void) = default;
		 CScreenBufferEx (const CScreenBufferEx&) = delete; CScreenBufferEx (CScreenBufferEx&&) = delete;

		TError&  Error (void) const;

		err_code Get (void);  // gets console screen buffer info;
		err_code Set (void);  // sets console screen buffer info;

		const
		TScrBufInfoEx& Ref (void) const;
		TScrBufInfoEx& Ref (void)      ;

		operator const TScrBufInfoEx& (void) const;
		operator       TScrBufInfoEx& (void)      ;

		TScrBufInfoEx& operator ()(void);

	private:
		CScreenBufferEx& operator = (const CScreenBufferEx&) = delete; CScreenBufferEx& operator = (CScreenBufferEx&&) = delete;
		CError m_error;
		TScrBufInfoEx m_info_ex;
	};
	// https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events ;
}}

#endif/*_CONSOLE_BUFFER_H_INCLUDED*/