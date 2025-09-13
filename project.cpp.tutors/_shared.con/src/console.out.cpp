/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Sep-2025 at 02:52:56.740.497,UTC+4, Batumi, Saturday;
	This is Ebo Pack console output text blocks interface implementation files;
*/
#include "console.out.h"
#include "shared.dbg.h"

using namespace shared::console;

namespace shared { namespace console { namespace _impl {
	// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers?redirectedfrom=MSDN#_win32_character_attributes ;
	// https://stackoverflow.com/questions/8621578/do-windows-console-color-values-have-official-names-constants-associated-with/49929936#49929936 ;
	class c_fg_clrs { c_fg_clrs (void) = default; ~c_fg_clrs (void) = default;
	public:
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
	};

	class c_bkg_clrs {
	public:
		typedef enum e_bkg_clrs 
		{
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
	};
	
	HANDLE Get_Out (void) {
		static HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
		return h_out;
	}

	class COutput {
	using CTrace = shared::dbg::CTrace;
	public:
		COutput (void) {} COutput (const COutput&) = delete; COutput (COutput&&) = delete; ~COutput (void) = default;

		static void Print (const CTrace::e_category _e_cat, _pc_sz _p_text) {
			_e_cat; _p_text;
			uint32_t n_written = 0;
			CString cs_out; cs_out.Format(_T(" %s"), _p_text);

			c_fg_clrs::e_fg_clrs clrs = c_fg_clrs::e_lightgray;

			if (CTrace::e_category::e_info == _e_cat) clrs = c_fg_clrs::e_lightgray;
			if (CTrace::e_category::e_warn == _e_cat) clrs = c_fg_clrs::e_yellow;
			if (CTrace::e_category::e_err  == _e_cat) clrs = c_fg_clrs::e_red;

			::SetConsoleTextAttribute(Get_Out(), clrs);
			::WriteConsole(Get_Out(), cs_out.GetBuffer(), cs_out.GetLength(), (LPDWORD)&n_written, 0);
		}

	private:
		COutput& operator = (const COutput&) = delete; COutput& operator = (COutput&&) = delete;
	};

}}}

using namespace shared::console::_impl;
using namespace shared::dbg;

void COut::Error (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_err , _text); }
void COut::Info  (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_info, _text); }
void COut::Warn  (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_warn, _text); }