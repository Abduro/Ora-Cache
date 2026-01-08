#ifndef _OUT_H_INCLUDED
#define _OUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Sep-2020 at 6:54:34p, UTC+7, Novosibirsk, Thursday;
	This is FakeGPS driver version 2 desktop client console interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Wanderer Path Finder project on 6-Jan-2021 at 11:42:05.633 am, UTC+7, Novosibirsk, Tuesday;
	Adopted to Yandex Wanderer project on 11-Dec-2022 at 07:38:02.6575746, UTC+7, Novosibirsk, Sunday;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.defs.h"

namespace shared { namespace console {

	typedef CONSOLE_SCREEN_BUFFER_INFO    TScrBufInfo;    // https://learn.microsoft.com/en-us/windows/console/console-screen-buffer-info-str ;
	typedef CONSOLE_SCREEN_BUFFER_INFOEX  TScrBufInfoEx;  // https://learn.microsoft.com/en-us/windows/console/console-screen-buffer-infoex ;

	typedef uint32_t colorref;
	// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes ;
	class CColor {
	private: CColor (const CColor&) = delete; CColor (CColor&&) = delete;
	public:  CColor (void); ~CColor (void);
		typedef enum class e_back_ndx : uint16_t { // background color indices;
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
		} e_back_ndx;
		typedef enum class e_fore_ndx : uint16_t { // foreground color indices;
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
		} e_fore_ndx;
	private:
		CColor& operator = (const CColor&) = delete; CColor& operator = (CColor&&) = delete;
	};

	class CFormat {
	private: CFormat (const CFormat&) = delete; CFormat (CFormat&&) = delete;
	public : CFormat (void); ~CFormat (void) ;
		class CBkgnd { // https://stackoverflow.com/questions/6460932/change-entire-console-background-color-win32-c ;
		using e_back_ndx = CColor::e_back_ndx;
		private: CBkgnd (const CBkgnd&) = delete; CBkgnd (CBkgnd&&) = delete;
		public : CBkgnd (void); ~CBkgnd (void);
		
			TError& Error (void) const;
			// https://stackoverflow.com/a/46656810/4325555 ; good example of how to set rgb color to background of the console output;
			colorref Color (void) const;      // gets background color that is currently set to console output;
			err_code Color (const colorref);  // sets background color to console output;

			e_back_ndx Index (void) const;       // gets the color index that is currently set in the table of colors;
			err_code   Index (const e_back_ndx); // sets the color index for changing background color of the console outpue;
		
		private: CBkgnd& operator = (const CBkgnd&) = delete; CBkgnd& operator = (CBkgnd&&) = delete;
			mutable
			CError   m_error;
			colorref m_clr_ref;
			uint16_t m_clr_ndx;
		};

		TError&  Error (void) const;

	private:
		CFormat& operator = (const CFormat&) = delete; CFormat& operator = (CFormat&&) = delete;
		mutable
		CError  m_error;
	};

	// https://learn.microsoft.com/en-us/windows/console/creation-of-a-console ;
	// https://learn.microsoft.com/en-us/windows/console/allocconsole ;
	// the excerpt from the above article: this function is primarily used by a graphical user interface (GUI) application to create a console window...;
  
	class CConsole {
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void);

		 err_code Close (void); // closes all IO handles; ::FreeConsole() is not used because there is no call to ::AttachConsole() was made before;
		 err_code Open  (const HWND _h_parent, const t_rect&, const bool _b_visible); // creates *new* console, inserts it as a chiled window to the parent one;

		 TError&  Error  (void) const;	
		 HWND     Handle (void) const; // returns console window handle;
		 bool  Is_valid  (void) const; // checks validity of the console window handle;

		 const HANDLE&   Get_err (void) const; // gets std::error handle;
		 const HANDLE&   Get_in  (void) const; // gets std::input handle;
		 const HANDLE&   Get_out (void) const; // gets std::output handle;
		 
		 operator const HWND (void) const;

	private:
		 CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
		 mutable
		 CError    m_error;
		 HWND      m_con_wnd;
		 HANDLE    m_handles[3]; // 0: is for std_input_handle; 1: is for std_output_handle; 2: is for std_err_handle;
	};

	class CLayout {
	public:
		class COutput { // it is the alias for ScreenBuffer;
		public:
			class CHScroll {
			public:
				CHScroll (void); CHScroll (const CHScroll&) = delete; CHScroll (CHScroll&&) = delete; ~CHScroll (void) = default;
				TError&  Error (void) const ;
				// https://stackoverflow.com/questions/50264637/add-horizontal-scroll-bar-to-console ;
				bool     Get (void) const; // checks a horizontal scroll bar existance within screen buffer of the console;
				err_code Set (const bool _b_set); // adds/removes a horizontal scroll bar to/from screen buffer of the console;

			private:
				CHScroll& operator = (const CHScroll&&) = delete; CHScroll& operator = (CHScroll&&) = delete;
				CError m_error;
			};
		public:
			COutput (void); COutput (const COutput&) = delete; COutput (COutput&&) = delete; ~COutput (void) = default;
			TError&  Error  (void) const;

			const
			CHScroll&  HScroll (void) const;
			CHScroll&  HScroll (void) ;

		private:
			COutput& operator = (const COutput&) = delete; COutput& operator = (COutput&&) = delete;
			CError   m_error;
			CHScroll m_h_scroll;
		};
	public:
		CLayout (void); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete; ~CLayout (void) = default;

		TError&  Error  (void) const;
		const
		COutput& Output (void) const;
		COutput& Output (void) ;

	private:
		CLayout& operator = (const CLayout&) = delete; CLayout& operator = (CLayout&&) = delete;

		CError   m_error;
		COutput  m_output;
	};

}}

typedef shared::console::CConsole out_;

/////////////////////////////////////////////////////////////////////////////

static out_ _out;

#endif/*_OUT_H_INCLUDED*/