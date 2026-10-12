#ifndef _WEB_IE_AUX_H_INCLUDED
#define _WEB_IE_AUX_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 08-Oct-2026 at 00:38:26.455, UTC+4, Batumi, Friday;
	This is IE browser auxiliary properties' and state classes' interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	class CWebBrowser; // it looks like a pointer to this class should be provided as an input one;

	class CCommand {
	public:
		 CCommand (TBrwWndPtr&); CCommand (void) = delete; CCommand (const CCommand&) = delete; CCommand (CCommand&&) = delete;
		~CCommand (void) = default;

		TErrorRef Error (void) const;
		bool   Is_valid (void) const;

		err_code  Print (void);
		err_code  PrintPreview (void);

	private:
		CCommand& operator = (const CCommand&) = delete; CCommand& operator = (CCommand&&) = delete;
		mutable
		CError m_error;
		TBrwWndPtr m_control;
	};

	class CState {
	public:
		 CState (CWebBrowser*); CState (const CState&) = delete; CState (CState&&) = delete;
		~CState (void) = default;

		TErrorRef Error (void) const;
		bool   Is_busy  (void) const;
		bool   Is_valid (void) const;

		bool     Silent (void) const;
		err_code Silent (const bool); // if true, it suppresses ***all*** message boxes

		operator bool (void) const;   // indicates a validity status of the web browser control object;

	private:
		CState& operator = (const CState&) = delete; CState& operator = (CState&&) = delete;
		mutable
		CError m_error;
		CWebBrowser* m_browser;
	};

}}}

#endif/*_WEB_IE_AUX_H_INCLUDED*/
