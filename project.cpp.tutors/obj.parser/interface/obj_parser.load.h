#ifndef _OBJ_PARSER_LOAD_H_INCLUDED
#define _OBJ_PARSER_LOAD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 19:59:33.114, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface declaration file;
*/
#include "obj_parser.defs.h"
#include "shared.cmd.ln.h"

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
		CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete; ~CLocator (void) = default;

		TError&  Error (void) const;
		err_code Locate (void);      // checks command line first; if there is no path to object file, the system registry is checked then;
		_pc_sz   Path (void) const;  // gets the path of object source file;

		static _pc_sz Root (void);   // gets registry key path that is the root for object parser settings;

	private:
		CLocator& operator = (const CLocator&) = delete; CLocator& operator = (CLocator&&) = delete;
		CError  m_error;
		CString m_obj_path;
	};

}}}

#endif/*_OBJ_PARSER_LOAD_H_INCLUDED*/