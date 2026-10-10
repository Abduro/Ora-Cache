#ifndef _WEB_IE_EMULATE_H_INCLUDED
#define _WEB_IE_EMULATE_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 02-Oct-2026 at 09:53:32.196, UTC+4, Batumi, Friday;
	This is installed IE emulate wrapper interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	class CEmulate
	{
	public:
		enum e_version : uint32_t {
			e__undef = 0, e_11 = 11000, e_edge = 11001
		};

		 CEmulate (_pc_sz _p_host = nullptr); // if not provided, the current executable name is used;
		 CEmulate (const CEmulate&) = delete; CEmulate (CEmulate&&) = delete;
		~CEmulate (void) = default;

		err_code  ApplyLatest (void);
		TError&   Error (void) const;
		bool      Is_enabled (const e_version) const;

		e_version LatestAvailableVersion (void) const;
		e_version Mode (void) const;
		err_code  Mode (const e_version);

	private:
		CEmulate& operator = (const CEmulate&) = delete; CEmulate& operator = (CEmulate&&) = delete;
		mutable
		CError  m_error;
		CString m_host_name; // application executable name (without full path), which hosts the web browser control;
	};

}}}
#endif/*_WEB_IE_EMULATE_H_INCLUDED*/