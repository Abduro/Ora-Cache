#ifndef _CONSOLE_EVT_KEY_H_INCLUDED
#define _CONSOLE_EVT_KEY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Apr-2026 at 17:53:36.128, (UTC+4), Batumi, Monday;
	This is Ebo Pack console control key interface declaration file;
*/
#include "console.defs.h"

namespace shared { namespace console { namespace events {
namespace input { 
	using namespace shared::console;
	/* this key base class could contain 'generic' state of particular key true/false: pressed/released for control key and turned on/off for lock keys;
	   but for this version of the implementation, the control and lock key classes do this separately;
	*/
	class CKey_Base {
	protected:
		CKey_Base (void); CKey_Base (const CKey_Base&); CKey_Base (CKey_Base&&); ~CKey_Base (void) = default;

	public:
		uint16_t  Code (void) const;      // gets key virtual code;
		bool      Code (const uint16_t);  // sets key virtual code; returns 'true' in case of code change;
		_pc_sz Name (void) const;         // gets the key name;
		bool   Name (_pc_sz);             // sets the key name; returns 'true' in case of name change;

		bool   Is_changed (void) const;   // indicates the key state is changed;
		bool&  Is_changed (void) ;        // sets the key change flag value;
	
		CKey_Base& operator <<(const bool  _b_changed);
		CKey_Base& operator <<(const uint16_t _u_code);
		CKey_Base& operator <<(const _pc_sz   _p_name);
		CKey_Base& operator <<(const CString _cs_name);

		CKey_Base& operator = (const CKey_Base&); CKey_Base& operator = (CKey_Base&&);
	protected:
		uint16_t m_code;
		CString  m_name;
		bool     m_changed;
	};

	class CCtrl_Key : public CKey_Base { typedef CKey_Base TBase;
	public:
		enum e_state : uint32_t {
		e_none     = 0x0,  // normal state, neither pressed nor released;
		e_pressed  = 0x1,  // the key is pressed and still be held;
		e_released = 0x2,  // the key is released;
		};
		
		 CCtrl_Key (void); CCtrl_Key (const CCtrl_Key&); CCtrl_Key (CCtrl_Key&&);
		~CCtrl_Key (void) = default;

		e_state  State (void) const;      // gets current key state;
		bool     State (const e_state);   // sets current key state' returns 'true' in case of state change;

		bool  Is_pressed (void) const;    // returns 'true' if the key is pressed;
		bool  Is_released (void) const;   // returns 'true' if the key is released;
	
		CCtrl_Key& operator = (const CCtrl_Key&);
		CCtrl_Key& operator = (CCtrl_Key&&);

		CCtrl_Key& operator <<(const e_state);
		const
		CKey_Base& operator ()(void) const;
		CKey_Base& operator ()(void) ;

	private:
		e_state  m_state;  // pressed/released;
	};

	class CLock_Key : public CKey_Base { typedef CKey_Base TBase;
	public:
		enum e_turn : uint32_t {
			e_off = 0x0,
			e_on
		};
		CLock_Key (void); CLock_Key (const CLock_Key&); CLock_Key (CLock_Key&&); ~CLock_Key (void) = default;

		bool  Is_turned (void) const;     // returns 'true' in case when the key state is turned on, e.g. caps loc is turned on;
		bool  Is_turned (const e_turn);   // turns 'on' or 'off' the key turn state;

		e_turn Turn (void) const;         // returns an element of turn state enumeration which is currently set;

		CLock_Key& operator = (const CLock_Key&);
		CLock_Key& operator = (CLock_Key&&);

		CLock_Key& operator <<(const e_turn);
		const
		CKey_Base& operator ()(void) const;
		CKey_Base& operator ()(void) ;

	private:
		e_turn m_turn; // turned on/off;
	};
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ;
	// these codes are for using in GetAsyncKeyState(), they have different codes in console type definition;
	static const uint16_t v_psd_codes[] = {VK_LCONTROL, VK_RCONTROL, VK_LSHIFT, VK_RSHIFT, VK_LMENU, VK_RMENU}; // 6 elements;
	static const uint32_t v_psd_count = _countof(v_psd_codes);
	static _pc_sz p_psd_names[] = {_T("L-Ctrl"), _T("R-Ctrl"), _T("L-Shift"), _T("R-Shift"), _T("L-Alt"), _T("R-Alt")}; // 6 elements;

	// these codes are from console type definition (wincontypes.h), otherwise it would be >> VK_CAPITAL, VK_NUMLOCK and VK_SCROLL;
	static const uint16_t v_lck_codes[] = /*{CAPSLOCK_ON, NUMLOCK_ON, SCROLLLOCK_ON}*/{VK_CAPITAL, VK_NUMLOCK, VK_SCROLL};
	static const uint32_t v_lck_count = _countof(v_lck_codes);
	static _pc_sz p_lck_names[] = {_T("Caps Lock"), _T("Num Lock"), _T("ScrLk")}; // https://en.wikipedia.org/wiki/Scroll_Lock ;

	// perhaps using std::map would be better;
	typedef ::std::vector<CCtrl_Key> ctrl_keys_t;
	typedef ::std::vector<CLock_Key> lock_keys_t;

	/* from https://learn.microsoft.com/en-us/windows/console/key-event-record-str#remarks ;
	ENHANCED_KEY could possibly be one of the keys from keypad:
	(Num Lock is off)
	VK_NUMPAD0 >> [Ins] ; VK_DECIMAL >> [Del] ;
	VK_NUMPAD1 >> [End] ; VK_NUMPAD2 >> [Down]; VK_NUMPAD3 >> [Pg Dn]; VK_NUMPAD4 >> [Left]; VK_NUMPAD6 >> [Right];
	VK_NUMPAD7 >> [Home]; VK_NUMPAD8 >> [Up]  ; VK_NUMPAD9 >> [Pg Up];
	(Num Lock does not affect)
	VK_RETURN  >> [Enter],VK_DIVIDE  >> [/];
	*/

	class CKey_enum {
	public:
		CKey_enum (void); CKey_enum (const CKey_enum&) = delete; CKey_enum (CKey_enum&&) = delete; ~CKey_enum (void) = default;

		const
		CCtrl_Key& Get_Ctrl (const dword _v_code) const; // gets the reference to key by virtual code (either generic or console code), if not found, fake reference is returned;
		CCtrl_Key& Get_Ctrl (const dword _v_code) ;
		const
		CLock_Key& Get_Lock (const dword _v_code) const;
		CLock_Key& Get_Lock (const dword _v_code) ;

		const ctrl_keys_t& Set_Ctrl (void); // it uses GetAsyncKeyState() for setting appropriate state of the control keys; 
		const lock_keys_t& Set_Lock (void); // it uses GetAsyncKeyState() for setting appropriate state of the lock keys;

		const ctrl_keys_t& Set_Ctrl (const dword _ctrl_state); // sets ctrl key state by using MOUSE_EVENT_RECORD.dwControlKeyState;
		const lock_keys_t& Set_Lock (const dword _lock_state); // sets lock key state by using MOUSE_EVENT_RECORD.dwControlKeyState;

	private:
		CKey_enum& operator = (const CKey_enum&) = delete; CKey_enum& operator = (CKey_enum&&) = delete;
		ctrl_keys_t m_ctrl;
		lock_keys_t m_lock;
	};

}}}}

#endif/*_CONSOLE_EVT_KEY_H_INCLUDED*/