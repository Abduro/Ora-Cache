#ifndef _SHARED_WND_RES_H_INCLUDED
#define _SHARED_WND_RES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Jul-2012 at 8:19:45pm, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Shared Application Icon Holder class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 28-May-2018 at 5:24:53p, UTC+7, Phuket, Rawai, Monday;
*/
#include "shared.defs.h"

namespace ex_ui { namespace resource {

	using namespace shared::defs;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagea ;
	// when an icon is loaded, it must be assigned to a window, no icon life-cycle control is provided by this class yet;
	class CIcon {
	public:
		 CIcon (void);
		 CIcon (const CIcon&) = delete; CIcon (CIcon&&) = delete;
		~CIcon (void);

	public:
		TError& Error (void) const;
		HICON   Load  (const uint16_t nIconResId, const bool bTreatAsLargeIcon) const; // returns icon descriptor; caller must take care of icon destroying;

	private:
		CIcon& operator = (const CIcon&) = delete; // looks like useless;
		CIcon& operator = (CIcon&&) = delete;

	protected:
		mutable
		CError m_error;
	};

}}

#endif/*_SHARED_WND_RES_H_INCLUDED*/