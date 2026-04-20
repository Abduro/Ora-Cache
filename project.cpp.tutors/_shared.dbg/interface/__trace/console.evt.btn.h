#ifndef _CONSOLE_EVT_BTN_H_INCLUDED
#define _CONSOLE_EVT_BTN_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Apr-2026 at 18:30:21.547, (UTC+4), Batumi, Monday;
	This is Ebo Pack console mouse buttons' interface declaration file;
*/
#include "console.defs.h"

namespace shared { namespace console { namespace events {
namespace input { 
	using namespace shared::console;

	// https://learn.microsoft.com/en-us/windows/console/mouse-event-record-str ;
	class CButton {
	public:
		enum e_state : uint32_t { e_none = 0x0, e_pressed, e_released };
		CButton (const uint32_t _v_code = 0, _pc_sz _p_name = 0); CButton (const CButton&); CButton (CButton&&); ~CButton (void) = default;

		uint32_t Code (void) const;     // gets virtual code of the button;
		bool     Code (const uint32_t); // sets virtual code of the button; returns 'true' in case of code change;

		bool  Is_pressed (void) const;
		bool  Is_released (void) const;
		bool  Is_valid (void) const;    // checks virual code first and the name (optional);

		_pc_sz   Name (void) const;     // gets the name of the button;
		bool     Name (_pc_sz);         // sets the name of the button; returns 'true' in case of name change; no trim or check for null;

		e_state  State (void) const;    // gets the last state of this button;
		bool     State (const e_state); // sets the last state of this button; returns 'true' in case of state change;

		CButton& operator = (const CButton&); CButton& operator = (CButton&&);
		CButton& operator <<(const uint32_t _u_virt_code);
		CButton& operator <<(const CString& _cs_name);
		CButton& operator <<(_pc_sz _p_name);
		CButton& operator <<(const e_state);

	private:	
		uint32_t m_code;  // virtual code of the mouse button;
		CString  m_name;  // the name of the button;
		e_state  m_state; // the last state of the button;
	};
	// https://www.highrez.co.uk/downloads/XMouseButtonControl.htm ;
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ;
	static uint32_t v_btn_codes[] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2}; // 5 elements;
	static const uint32_t v_btn_count = _countof(v_btn_codes);
	static _pc_sz p_btn_names[] = {_T("Left"), _T("Right"), _T("Scroll"), _T("Back"), _T("Next")};  // 5 elements;

	typedef ::std::vector<CButton> ctrl_btns_t;

	class CBtn_enum {
	public:
		CBtn_enum (void); CBtn_enum (const CBtn_enum&) = delete; CBtn_enum (CBtn_enum&&) = delete; ~CBtn_enum (void) = default;

		const
		CButton& Get (const dword _v_code) const;
		CButton& Get (const dword _v_code) ;
		const ctrl_btns_t& Set (const dword _btn_state); // sets mouse button state by using MOUSE_EVENT_RECORD.dwButtonState;

		const
		CButton& operator ()(const uint32_t _u_code) const;
		CButton& operator ()(const uint32_t _u_code);

	private:
		CBtn_enum& operator = (const CBtn_enum&) = delete; CBtn_enum& operator = (CBtn_enum&&) = delete;
	};
}}}}

#endif/*_CONSOLE_EVT_BTN_H_INCLUDED*/