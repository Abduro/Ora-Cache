#ifndef _WEB_IE_REG_H_INCLUDED
#define _WEB_IE_REG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Oct-2026 at 22:53:22.140, (GMT+4), Batumi;
	This is MS Internet Explorer registry entries' wrapper interfsace declaration file;
*/
#include "web.ie.defs.h"
#include "sys.registry.h"

namespace ex_ui { namespace web { namespace IE { namespace storage {

	using namespace ::ex_ui::web::IE::defs;
	using CRoot_base = ::shared::sys_core::storage::CRoot; // actually, this class is created for specifying the entry point to registry for ebo pack;

namespace route {
	class CRoot : public CRoot_base { typedef CRoot_base TBase;
	public:
		CRoot (void) = default; CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		_pc_sz  Path (void) const;  // returns the registry path to Internet Explorer emulator root node;
		const
		CRoot_base& operator ()(void) const;
		CRoot_base& operator ()(void) ;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};

	class CEmulation : public CRoot { typedef CRoot TBase;
	public:
		CEmulation (void) = default; CEmulation (const CEmulation&) = delete; CEmulation (CEmulation&&) = delete; ~CEmulation (void) = default;

		_pc_sz Path (void) const;

	private:
		CEmulation& operator = (const CEmulation&) = delete; CEmulation& operator = (CEmulation&&) = delete;
	};
}
}}}}

#endif/*_WEB_IE_REG_H_INCLUDED*/