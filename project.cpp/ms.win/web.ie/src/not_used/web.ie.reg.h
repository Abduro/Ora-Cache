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

	// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-gppref/fa847fc5-a7a0-4b26-8bc5-58ebdff28957 ;

namespace route {
	class CRoot : public CRoot_base { typedef CRoot_base TBase;
	public:
		class CVersion {
		public:
			CVersion (void) = default; CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete; ~CVersion (void) = default;

			_pc_sz Value (void) const; // returns value name that contains the latest version of IE currently installed on this computer;

		private:
			CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;
		};

		CRoot (void) = default; CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		_pc_sz  Path (void) const;  // returns the registry path to Internet Explorer emulator root node;

		const
		CVersion&   Version (void) const;
		const
		CRoot_base& operator ()(void) const;
		CRoot_base& operator ()(void) ;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
		CVersion m_version;
	};

	// The Internet Explorer 11 is deprecated, but particular settiings are still be in registry under HKEY_LOCAL_MACHINE;
	class CEmulation : public CRoot { typedef CRoot TBase;
	public:
		CEmulation (void) = default; CEmulation (const CEmulation&) = delete; CEmulation (CEmulation&&) = delete; ~CEmulation (void) = default;

		_pc_sz Path (void) const;

	private:
		CEmulation& operator = (const CEmulation&) = delete; CEmulation& operator = (CEmulation&&) = delete;
	};
} 
	class CWeb_router {
	public:
		using CRoot = route::CRoot;
		CWeb_router (void) = default; CWeb_router (const CWeb_router&) = delete; CWeb_router (CWeb_router&&) = delete; ~CWeb_router (void) = default;

		const
		CRoot& Root (void) const;
		CRoot& Root (void) ;

	private:
		CWeb_router& operator = (const CWeb_router&) = delete; CWeb_router& operator = (CWeb_router&&) = delete;
		CRoot m_root;
	};
}}}}

typedef ::ex_ui::web::IE::storage::CWeb_router TWebRouter; TWebRouter& Get_web_router (void);

#endif/*_WEB_IE_REG_H_INCLUDED*/