#ifndef _OBJ_PARSER_LOAD_H_INCLUDED
#define _OBJ_PARSER_LOAD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Jul-2026 at 19:59:33.114, UTC+4, Batumi, Wednesday;
	This is 3D module object file loader interface declaration file;
*/
#include "obj_parser.defs.h"
#include "shared.cmd.ln.h"

namespace shared { namespace parsers { namespace obj {

	class CBase {
	protected:
		CBase (void); CBase (const CBase&) = delete; CBase (CBase&&) = delete; ~CBase (void) = default;
	public:
		TError&  Error (void) const;

	protected:
		CBase& operator = (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		mutable
		CError m_error;
	};

	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fsopen-wfsopen << file stream sharing;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s << security enhancements; it is used in the class below;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-wfopen << no security enhancements;
	class CLoader : public CBase { typedef CBase TBase;
	public:
		CLoader (void); CLoader (const CLoader&) = delete; CLoader (CLoader&&) = delete; ~CLoader (void);

		err_code Close (void);         // closes the file handle;
		bool Is_opened (void) const;   // returns true if the file handle/pointer is not nullptr/0, otherwise 'false' is returned;
		err_code Open  (_pc_sz _path); // opens the file by given file path;

	private:
		CLoader& operator = (const CLoader&) = delete; CLoader& operator = (CLoader&&) = delete;
		FILE*  m_p_file;
	};

	class CLocator : public CBase { typedef CBase TBase;
	public:
		CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete; ~CLocator (void) = default;

		bool  Is_found (void) const; // if the object file is not empty, checks the file existance, if it is then 'true', otherwise 'false';

		err_code Locate (void);      // checks command line first; if there is no path to object file, the system registry is checked then;
		_pc_sz   Path (void) const;  // gets the path of object source file;

		static _pc_sz Root (void);   // gets registry key path that is the root for object parser settings;

	private:
		CLocator& operator = (const CLocator&) = delete; CLocator& operator = (CLocator&&) = delete;
		CString m_obj_path;
	};

	class CReader : public CBase { typedef CBase TBase;
	public:
		CReader (void); CReader (const CReader&) = delete; CReader (CReader&&) = delete; ~CReader (void) = default;

		err_code Read (void);

	private:
		CReader& operator = (const CReader&) = delete; CReader& operator = (CReader&&) = delete;
	};

}}}

#endif/*_OBJ_PARSER_LOAD_H_INCLUDED*/