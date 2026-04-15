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

	class CPosition : public CBase { typedef CBase TBase;
	public:
		 CPosition (void);
		~CPosition (void);

		const
		t_rect&  Get (void) const;
		err_code Set (const t_rect&); // for direct set the window position and to save it to the registry;

		err_code Load (void); // loads console window position;
		err_code Save (void); // saves console window position; gets the actual window position before saving;

		CString To_str (const e_print = e_print::e_all);

	private:
		t_rect m_rc_pos;  // the console window rectangle in screen coordinates;
	};

	class CShow : public CBase { typedef CBase TBase;
	public:
		 CShow (void);
		~CShow (void) = default;

		err_code Load (void);
		err_code Save (void);

		bool Is_visible (void) const;

	private:
		bool m_visible; // by default is 'true';
	};
}

	class CPersistent : public persistent::CBase { typedef persistent::CBase TBase;
	public:
		using CPin = persistent::CPin;
		using CPos = persistent::CPosition;

		 CPersistent (void); CPersistent (const CPersistent&) = delete; CPersistent (CPersistent&&) = delete;
		~CPersistent (void);

		err_code Load (void); // loads all persistent components; if one of them is failed, just traces of the error;
		err_code Save (void); // saves all persistent components; if one of them is failed, just traces of the error;

		const
		CPin& Pin (void) const;
		CPin& Pin (void) ;
		const
		CPos& Pos (void) const;
		CPos& Pos (void) ;

	protected:
		CPersistent& operator = (const CPersistent&) = delete; CPersistent& operator = (CPersistent&&) = delete;
		CPin  m_pin;
		CPos  m_pos;
	};

}}

// taking into account the fact the only one console can be associated with one process, using a singleton is acceptable approach;
typedef shared::console::CPersistent TConPers; TConPers&  Get_ConPers (void);

#endif/*_CONSOLE_PERS_H_INCLUDED*/