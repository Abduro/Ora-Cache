#ifndef _HANDLER_BASE_H_INCLUDED
#define _HANDLER_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2021 at 3:00:59.3369990 pm, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack UIX window message handler base interface declaration file.
	// https://www.ibm.com/docs/en/xl-c-and-cpp-aix/16.1?topic=functions-function-declarations-definitions ; >> just for better understanding 'declare|define';
*/
#include <atlbase.h>
#include <atlwin.h>
#include <set>
#include <iterator>

#include "sys.error.h"
#include "sys.sync_obj.h"

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"

//#pragma comment(lib, "geometry.2D_v15.lib")

namespace ex_ui { namespace message { namespace handlers {// regarding namespace naming: 'window_message' or 'wm' shortcut look like more informative, but not for this case;

	// https://www.abbreviations.com/abbreviation/handler >> 'hdl' shortcut is okay, but 'hand' looks like to be much better; :D
	// https://en.wikipedia.org/wiki/Message_passing      >> the base definition of what message passing is and what is a purpose for;

	using namespace shared::types;

	using shared::sys_core::CError;
	using shared::sys_core::CSyncObject;

	using TError = const CError;

	class CBase { // non-copyable;
	protected:
		mutable
		CError      m_error;
		CSyncObject m_guard; // this class object will be created on each new instance of this class;

	protected:
		 CBase (void);
		 CBase (const CBase&) = delete;
		 CBase (CBase&&) = delete;
		~CBase (void);

	public:
		TErrorRef Error(void) const;
		err_code  Lock (void) ;
		err_code  Unlock (void) ;

	private:
		CBase& operator = (const CBase&) = delete;
		CBase& operator = (CBase&&) = delete;
	};

}}}

#endif/*_HANDLER_BASE_H_INCLUDED*/