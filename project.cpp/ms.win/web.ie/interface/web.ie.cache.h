#ifndef _WEB_IE_CACHE_H_INCLUDED
#define _WEB_IE_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Oct-2026 at 09:54:28.477, UTC+4, Batumi, Sunday;
	This is Ebo Pack IE 11 IWebBrowser2 control data cache wrapper interface declaration file;
*/
#include "web.ie.defs.h"
#include <shellapi.h>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "shell32.lib")

namespace ex_ui { namespace web { namespace IE { using namespace ex_ui::web::IE::defs;

	class CCache {
	public:
		enum e_clear_flags : dword_t {
		     e_history  = 0x1, // Browsing History;
		     e_cookies  = 0x2, // Cookies;
		     e_files    = 0x8, // Temporary Internet Files (Web Cache files);
		     e_all_data = 0xff // Clear All items altogether (Cache, Cookies, History, Form data, Passwords);
		};
		enum e_nav_flags : dword_t {
		     e_no_history = 0x1, // prevents the page from being added to the historical log;
		     e_no_read    = 0x2, // forces the browser to ignore any existing cached copies on the local disk and request a fresh copy from the server;
		     e_no_write   = 0x4, // prevents the downloaded page and its immediate resources from being saved to the local disk cache;
		     e_no_all = e_no_history | e_no_read | e_no_write // all navigate options are turned off;
		};

		CCache (void); CCache (const CCache&) = delete; CCache (CCache&&) = delete; ~CCache (void) = default;

		err_code Clear (void);
		err_code Clear_ex (const dword_t = e_clear_flags::e_all_data); // calls control panel component through shell execute in order to clear all cache of IE;
		TError&  Error (void) const;

	private:
		CCache& operator = (const CCache&) = delete; CCache& operator = (CCache&&) = delete;
		CError m_error;
	};

}}}

#endif/*_WEB_IE_CACHE_H_INCLUDED*/