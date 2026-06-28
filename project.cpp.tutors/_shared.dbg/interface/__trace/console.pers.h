#ifndef _CONSOLE_PERS_H_INCLUDED
#define _CONSOLE_PERS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 09:26:16.579, UTC+4, Batumi, Wednesday;
	This is system console registry persistency interface declaration file;
*/
#include "console.defs.h"
#include "shared.dbg.h"

namespace shared { namespace console { using namespace shared::defs;
namespace persistent {
	class CBase {
	protected:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void) = default;
	public:
		TError& Error (void) const;

	protected:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError m_error;
	};
	// actually, it is not a number of lines that is acceptable for trace console output,
	// it is a count of trace messages being visible in the console;
	class CLines : public CBase { typedef CBase TBase;
	public:
		 static const uint32_t accepted = 666u; // in fact it is maximum value that is reasonable for trace output monitoring; can be changed of course;
		 static const uint32_t no_limit = static_cast<uint32_t>(-1);
		 CLines (void);
		~CLines (void) = default;

		bool     Clear (void);                 // removes the lines' limit and clear the registry; returns 'true' in case of change the limit value;
		uint32_t Get (void) const;             // gets number of acceptable lines in trace console output;
		err_code Set (const uint32_t _lines);  // sets number of acceptable lines in trace console output;

		bool  Is_set (void) const;  // returns 'false' in case if lines number is not saved in registry or has the default value 'no_limit';

		err_code Load (void);
		err_code Save (void);

		CLines&  operator <<(const uint32_t _lines);

	private:
		uint32_t m_lines;
	};

	class CPin : public CBase { typedef CBase TBase;
	public:
		 CPin (void);
		~CPin (void) = default;

		err_code Load (void);
		err_code Save (void);

		bool Is_pinned (void) const;
		void Is_pinned (const bool _on_or_off);

		CString To_str (const e_print = e_print::e_all);

		CPin& operator <<(const bool _b_on_or_off);

	private:
		bool m_pinned; // the flag of pinned/unpinned state of the console window; used by gui app;
	};
	/*to-do: all classes including CPosition is intended for using by debug trace console;
	  but for the new version, other project requires console too, obj_parser for example;
	*/
	class CPosition : public CBase { typedef CBase TBase;
	public:
		 CPosition (void);
		~CPosition (void);

		const
		t_rect&  Get (void) const;
		err_code Set (const t_rect&); // for direct set the window position and to save it to the registry;

		_pc_sz   Key (void) const; // gets the registry path of the key that is the root for console settings; for position only this time;
		err_code Key (_pc_sz);     // sets the registry path of the key that is the root for console settings;

		err_code Load (void); // loads console window position;
		err_code Save (void); // saves console window position; gets the actual window position before saving;

		CString To_str (const e_print = e_print::e_all);

		CPosition& operator <<(_pc_sz _p_root_path); // sets the root key path to read/write position data;

	private:
		t_rect  m_rc_pos;     // the console window rectangle in screen coordinates;
		CString m_key_path;   // this is the path that is set for console settings that is not 'debug trace';
	};

	class CShow : public CBase { typedef CBase TBase;
	public:
		 CShow (void);
		~CShow (void) = default;

		bool Is_visible (void) const;            // gets the current state of the console window;
		void Is_visible (const bool _yes_or_no); // sets the current state of the console window;

		err_code Load (void);   // loads console window visibility state;
		err_code Save (void);   // saves console window visibility state;

	private:
		bool m_visible; // by default is 'true';
	};
}
	class CPersistent : public persistent::CBase { typedef persistent::CBase TBase;
	public:
		using CLines = persistent::CLines;
		using CPin   = persistent::CPin;
		using CPos   = persistent::CPosition;
		using CShow  = persistent::CShow;

		 CPersistent (void); CPersistent (const CPersistent&) = delete; CPersistent (CPersistent&&) = delete;
		~CPersistent (void);

		err_code Load (void); // loads all persistent components; if one of them is failed, just traces of the error;
		err_code Save (void); // saves all persistent components; if one of them is failed, just traces of the error;

		const
		CLines& Lines (void) const;
		CLines& Lines (void) ;
		const
		CPin& Pin (void) const;
		CPin& Pin (void) ;
		const
		CPos& Pos (void) const;
		CPos& Pos (void) ;
		const
		CShow& Show (void) const;
		CShow& Show (void) ;

	protected:
		CPersistent& operator = (const CPersistent&) = delete; CPersistent& operator = (CPersistent&&) = delete;
		CLines m_lines;
		CPin   m_pin;
		CPos   m_pos;
		CShow  m_show;
	};

	bool operator != (const t_rect& _left, const t_rect& _right);
	bool operator == (const t_rect& _left, const t_rect& _right);
}}

// taking into account the fact the only one console can be associated with one process, using a singleton is acceptable approach;
typedef shared::console::CPersistent TConPers; TConPers&  Get_ConPers (void);

#endif/*_CONSOLE_PERS_H_INCLUDED*/