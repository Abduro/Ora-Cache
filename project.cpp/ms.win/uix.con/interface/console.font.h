#ifndef _CON_FONT_H_INCLUDED
#define _CON_FONT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Oct-2022 at 00:09:08.7039551, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack Windows system console font wrapper interface declaration file;
*/
#include <tchar.h>
#include "sys.error.h"
#include "shared.string.h"
#include "shared.types.h"
namespace shared { namespace console {

	using namespace shared::types;

	using shared::sys_core::CError;
	using shared::sys_core::CErr_Format;

	// https://learn.microsoft.com/en-us/windows/console/coord-str ;
	// https://learn.microsoft.com/en-us/windows/console/console-font-infoex ;
	typedef CONSOLE_FONT_INFO   ConFntInfo;
	typedef CONSOLE_FONT_INFOEX ConFntInfoEx;

	class CFont {
	public:
		 CFont (void);
		 CFont (const CFont&);            // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-textmetrica ;
		 CFont (_pc_sz _lp_sz_face_name); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-textmetricw ;
		~CFont (void);

	public:
		const
		ConFntInfoEx& Get (void) const;   // re-call the system function to retrieve the font info in case when font structure is unset;
		HRESULT       Set (_pc_sz _lp_sz_face_name); // TODO: it is assumed that font family is TMPF_TRUETYPE, when new font is set;

	public:
		TErrorRef Error (void) const;
		bool      Is    (void) const;   // checks the condole font structure for validity of data; 
		UINT      Size  (void) const;   // gets font size that is set in console output; (deprecated);

	public:
		const
		ConFntInfoEx& Raw (void) const;
		ConFntInfoEx& Raw (void)      ;

	public:
		CFont&  operator = (const CFont&);
		CFont&  operator <<(_pc_sz _lp_sz_face_name);

	public:
		operator bool (void) const;     // calls CFont::Is();
		operator const ConFntInfoEx& (void) const;
		operator       ConFntInfoEx& (void)      ;

	private:
		mutable CError m_error;
		mutable ConFntInfoEx m_info;
	};

}}
#endif/*_CON_FONT_H_INCLUDED*/