#ifndef _WEB_IE_VERSION_H_INCLUDED
#define _WEB_IE_VERSION_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 02-Oct-2026 at 09:53:32.196, UTC+4, Batumi, Friday;
	This is installed IE version wrapper interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	class CVersion
	{
	public:
		enum e_version : uint32_t {
			e__undef = 0, e_7 = 7000, e_8 = 8000, e_8_std = 8888, e_9 = 9000, e_9_std = 9999, e_10 = 10000, e_10_std = 10001, e_11 = 11000,
			e_edge = 11001,
		};

		 CVersion (_pc_sz _p_host = nullptr); // if not provided, the current executable name is used;
		 CVersion (const CVersion&) = delete; CVersion (CVersion&&) = delete;
		~CVersion (void) = default;

		err_code  ApplyLatest (void);
		TError&   Error (void) const;
		bool      Is_enabled (const e_version) const;

		e_version LatestAvailableVersion (void) const;
		e_version Mode (void) const;
		err_code  Mode (const e_version);

	private:
		CVersion& operator = (const CVersion&) = delete; CVersion& operator = (CVersion&&) = delete;
		mutable
		CError  m_error;
		CString m_host_name; // application executable name (without full path), which hosts the web browser control;
	};

}}}
#endif/*_WEB_IE_VERSION_H_INCLUDED*/