#ifndef _OBJ_PARSER_LOAD_H_INCLUDED
#define _OBJ_PARSER_LOAD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 19:59:33.114, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface declaration file;
*/
#include "obj_parser.defs.h"

namespace shared { namespace parsers { namespace obj {

	class CLoader {
	public:
		CLoader (void); CLoader (const CLoader&) = delete; CLoader (CLoader&&) = delete; ~CLoader (void);

		TError&  Error (void) const;


	private:
		CLoader& operator = (const CLoader&) = delete; CLoader& operator = (CLoader&&) = delete;
		CError m_error;
	};

	class CLocator {
	public:
		CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete; ~CLocator (void);

		TError&  Error (void) const;


	private:
		CLocator& operator = (const CLocator&) = delete; CLocator& operator = (CLocator&&) = delete;
		CError m_error;
	};

}}}

#endif/*_OBJ_PARSER_LOAD_H_INCLUDED*/