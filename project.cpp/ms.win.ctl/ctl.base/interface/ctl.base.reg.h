#ifndef _CTL_REG_BASE_H_INCLUDED
#define _CTL_REG_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 11:59:29.237, UTC+4, Batumi, Thursday;
	The is base control registry storage wrapper interface declaration file;
*/
#include "ctl.base.defs.h"
#include "sys.registry.h"

namespace ex_ui { namespace controls { namespace storage {

	using CRoot_base = ::shared::sys_core::storage::CRoot;

	class CRoot : public CRoot_base { typedef CRoot_base TBase;
	public:
		CRoot (void) = default; CRoot (const CRoot&) = delete; CRoot (CRoot&&) = delete; ~CRoot (void) = default;

		_pc_sz  Path (void) const;  // returns the registry path to controls' root node;
		const
		CRoot_base& operator ()(void) const;
		CRoot_base& operator ()(void) ;

	private:
		CRoot& operator = (const CRoot&) = delete; CRoot& operator = (CRoot&&) = delete;
	};

}}}

#endif/*_CTL_REG_BASE_H_INCLUDED*/