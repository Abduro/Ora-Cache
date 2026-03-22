/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Sep-2025 at 02:52:56.740.497,UTC+4, Batumi, Saturday;
	This is Ebo Pack console output text blocks interface implementation files;
*/
#include "console.out.h"
#include "shared.dbg.h"
#include "console.h"

using namespace shared::console;

namespace shared { namespace console { namespace _impl {
#pragma region __refs_e
	// https://burgaud.com/bring-colors-to-the-windows-console-with-python/ ;
	// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers?redirectedfrom=MSDN#_win32_character_attributes ;
	// https://stackoverflow.com/questions/8621578/do-windows-console-color-values-have-official-names-constants-associated-with/49929936#49929936 ;
#pragma endregion
#if (0)	
	HANDLE Get_Out (void) {
		static HANDLE h_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
		return h_out;
	}
#endif
	class COutput {
	using CTrace = shared::dbg::CTrace;
	public:
		COutput (void) {} COutput (const COutput&) = delete; COutput (COutput&&) = delete; ~COutput (void) = default;

		static void Print (const CTrace::e_category _e_cat, _pc_sz _p_text) {
			_e_cat; _p_text;
			u_long n_written = 0;
			CString cs_out; cs_out.Format(_T(" %s"), _p_text);

			using c_fg_clrs = CForeClr::e_fg_clrs;

			c_fg_clrs clrs  = c_fg_clrs::e_lightgray;

			if (CTrace::e_category::e_impt == _e_cat) clrs = c_fg_clrs::e_lightblue;
			if (CTrace::e_category::e_info == _e_cat) clrs = c_fg_clrs::e_lightgray;
			if (CTrace::e_category::e_warn == _e_cat) clrs = c_fg_clrs::e_yellow;
			if (CTrace::e_category::e_err  == _e_cat) clrs = c_fg_clrs::e_red;

			// https://learn.microsoft.com/en-us/windows/console/setconsoletextattribute ;
			// https://learn.microsoft.com/en-us/windows/console/writeconsole ;
			void* p_out = __out_handle; // CHandles::Get() is not used;
			if (nullptr == p_out || __e_handle == p_out)
				return;
			::SetConsoleTextAttribute(p_out, clrs);
			::WriteConsole(p_out, cs_out.GetBuffer(), cs_out.GetLength(), &n_written, 0);
		}

	private:
		COutput& operator = (const COutput&) = delete; COutput& operator = (COutput&&) = delete;
	};

}}}

using namespace shared::console::_impl;
using namespace shared::dbg;

void COut::Error (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_err , _text); }
void COut::Impt  (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_impt, _text); }
void COut::Info  (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_info, _text); }
void COut::Warn  (_pc_sz _text) { COutput::Print( shared::dbg::CTrace::e_warn, _text); }