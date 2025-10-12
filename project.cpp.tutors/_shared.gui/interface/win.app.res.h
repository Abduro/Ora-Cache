#ifndef _WIN_APP_RES_H_INCLUDED
#define _WIN_APP_RES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) in 12-Oct-2025 at 09:33:46.867, UTC+4, Batumi, Sunday;
	This is Ebo Pack windows executable genereic resource wrapper interface declaration file;
*/
#include "shared.defs.h"
namespace shared { namespace app { namespace res {

	using namespace shared::defs;
	// https://learn.microsoft.com/en-us/windows/win32/menurc/resource-types ;
	enum class e_res_types {
	e_data   = 10,  // RT_RCDATA ; raw app defined resource; for including shaper source file as a resource entry;
	e_string =  6,  // RT_STRING ; string-table entry; for creating string table entry of shader source text;
	};
	// https://learn.microsoft.com/en-us/windows/win32/menurc/using-resources ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-findresourcea ;
	class CLocator {
	public:
		CLocator (void); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete; ~CLocator (void);

		TError&  Error (void) const;
		bool     Has (const uint16_t _u_res_id, const e_res_types) const;

	private:
		CLocator& operator = (const CLocator&) = delete; CLocator& operator = (CLocator&&) = delete;
		mutable
		CError  m_error;
	};

}}}

#endif/*_WIN_APP_RES_H_INCLUDED*/