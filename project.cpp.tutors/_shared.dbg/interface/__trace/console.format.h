#ifndef _CONSOLE_FORMAT_H_INCLUDED
#define _CONSOLE_FORMAT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 11:28:21.366, UTC+4, Batumi, Saturday;
	This is system console format interface declaration file;
*/
#include "console.defs.h"
#include "console.buffer.h"

namespace shared { namespace console {

	typedef uint32_t colorref;
	// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes ;
	class CForeClr {
	public:
		 CForeClr (void) = default; CForeClr (const CForeClr&) = delete; CForeClr (CForeClr&&) = delete;
		~CForeClr (void) = default;
		typedef enum e_fg_clrs : uint16_t
		{
			e_black        = 0x00, // 0000 ;
			e_blue         = 0x01, // 0001 ; FOREGROUND_BLUE ;
			e_green        = 0x02, // 0010 ; FOREGROUND_GREEN ;
			e_cyan         = 0x03, // 0011 ; FOREGROUND_GREEN | FOREGROUND_BLUE ;
			e_red          = 0x04, // 0100 ; FOREGROUND_RED ;
			e_magenta      = 0x05, // 0101 ; FOREGROUND_RED | FOREGROUND_BLUE ;
			e_brown        = 0x06, // 0110 ; FOREGROUND_RED | FOREGROUND_GREEN ;
			e_lightgray    = 0x07, // 0111 ; FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ;
			e_gray         = 0x08, // 1000 ; FOREGROUND_INTENSITY ;
			e_lightblue    = 0x09, // 1001 ; FOREGROUND_INTENSITY | FOREGROUND_BLUE ;
			e_lightgreen   = 0x0a, // 1010 ; FOREGROUND_INTENSITY | FOREGROUND_GREEN ;
			e_lightcyan    = 0x0b, // 1011 ; FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE ;
			e_lightred     = 0x0c, // 1100 ; FOREGROUND_INTENSITY | FOREGROUND_RED ;
			e_lightmagenta = 0x0d, // 1101 ; FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE ;
			e_yellow       = 0x0e, // 1110 ; FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN ;
			e_white        = 0x0f, // 1111 ; FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ;
		} e_fg_clrs;
	private:
		CForeClr& operator = (const CForeClr&) = delete; CForeClr& operator = (CForeClr&&) = delete;
	};

	class CBkgnd { // https://stackoverflow.com/questions/6460932/change-entire-console-background-color-win32-c ;
	public:
		typedef enum e_bkg_clrs : uint16_t
		{
			e_black        = 0x00, // 0000 0000 ; BACKGROUND_BLACK ;
			e_navyblue     = 0x10, // 0001 0000 ; BACKGROUND_BLUE ;
			e_green        = 0x20, // 0010 0000 ; BACKGROUND_GREEN ;
			e_teal         = 0x30, // 0011 0000 ; BACKGROUND_GREEN | BACKGROUND_BLUE ;
			e_maroon       = 0x40, // 0100 0000 ; BACKGROUND_RED ;
			e_purple       = 0x50, // 0101 0000 ; BACKGROUND_RED | BACKGROUND_BLUE ;
			e_olive        = 0x60, // 0110 0000 ; BACKGROUND_RED | BACKGROUND_GREEN ;
			e_silver       = 0x70, // 0111 0000 ; BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE ;
			e_gray         = 0x80, // 1000 0000 ; BACKGROUND_INTENSITY ;
			e_blue         = 0x90, // 1001 0000 ; BACKGROUND_INTENSITY | BACKGROUND_BLUE ;
			e_lime         = 0xa0, // 1010 0000 ; BACKGROUND_INTENSITY | BACKGROUND_GREEN ;
			e_cyan         = 0xb0, // 1011 0000 ; BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE ;
			e_red          = 0xc0, // 1100 0000 ; BACKGROUND_INTENSITY | BACKGROUND_RED ;
			e_magenta      = 0xd0, // 1101 0000 ; BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE ;
			e_yellow       = 0xe0, // 1110 0000 ; BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN ;
			e_white        = 0xf0, // 1111 0000 ; BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE ;
		} e_bkg_clrs;
	public:
		 CBkgnd (void); CBkgnd (const CBkgnd&) = delete; CBkgnd (CBkgnd&&) = delete;
		~CBkgnd (void);
		
		TError& Error (void) const;

		// https://stackoverflow.com/a/46656810/4325555 ; good example of how to set rgb color to background of the console output;

		colorref   Color (void) const;       // gets background color that is currently set to console output;
		err_code   Color (const colorref);   // sets background color to console output;

		e_bkg_clrs Index (void) const;       // gets the color index that is currently set in the table of colors;
		err_code   Index (const e_bkg_clrs); // sets the color index for changing background color of the console outpue;
		
	private:
		CBkgnd& operator = (const CBkgnd&) = delete; CBkgnd& operator = (CBkgnd&&) = delete;
		mutable
		CError   m_error;
		colorref m_clr_ref;
		uint16_t m_clr_ndx;
	};

	class CFormat {
	public:
		 CFormat (void); CFormat (const CFormat&) = delete; CFormat (CFormat&&) = delete;
		~CFormat (void);

		TError&  Error (void) const;

	private:
		CFormat& operator = (const CFormat&) = delete; CFormat& operator = (CFormat&&) = delete;
		mutable
		CError  m_error;
	};
}}

#endif/*_CONSOLE_FORMAT_H_INCLUDED*/