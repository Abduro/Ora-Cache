#ifndef _COMMON_VIEW_H_INCLUDED
#define _COMMON_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Oct-2026 at 12:31:35.913, UTC+4, Batumi, Monday;
	This is virtual camera common GUI base view interface declaration file;
*/
#include <common.defs.h>

namespace test { namespace gui { namespace views { using namespace ::test::draw::defs;

	class CBase {
	public:
		 CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);
	};

}}}

#endif/*_COMMON_VIEW_H_INCLUDED*/