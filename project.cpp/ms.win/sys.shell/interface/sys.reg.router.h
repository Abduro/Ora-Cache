#ifndef _SYS_REG_ROUTER_H_INCLUDED
#define _SYS_REG_ROUTER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 10:28:49.086, UTC+4, Batumi, Thursday;
	This Ebo Pack commom registry paths' router class interface declaration file;
*/
#include "sys.shell.inc.h"

namespace shared { namespace sys_core { namespace storage {
	using namespace shared::sys_core::shell;
	class CRoot {
	public:
		CRoot (void); CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		const
		HKEY    Key  (void) const;  // returns the root key handle;
		_pc_sz  Path (void) const;  // returns the root path;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};
}}}
#endif/*_SYS_REG_ROUTER_H_INCLUDED*/