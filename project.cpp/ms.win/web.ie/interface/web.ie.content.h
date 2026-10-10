#ifndef _WEB_IE_CONTENT_H_INCLUDED
#define _WEB_IE_CONTENT_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 08-Oct-2026 at 17:10:01.310, UTC+4, Batumi, Thursday;
	This is IE HTML document content wrapper interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	class CCharset {
	public:
		 CCharset (void) = delete;
		 CCharset (TBrwWndPtr&); CCharset (const CCharset&) = delete; CCharset (CCharset&&) = delete;
		~CCharset (void);

		TError&  Error (void) const;
		const
		CString& Get (void);
		err_code Set (_pc_sz _p_value/*, const bool bRefresh*/);

	private:
		CCharset& operator = (const CCharset&) = delete; CCharset& operator = (CCharset&&) = delete;
		CError       m_error;
		CString      m_charset;
		TBrwWndPtr& m_control;
	};

	class CContent {
	public:
		 CContent (void) = delete;
		 CContent (TBrwWndPtr&); CContent (const CContent&) = delete; CContent (CContent&&) = delete;
		~CContent (void);

		const
		CCharset& Charset (void) const;
		CCharset& Charset (void) ;
		TError&   Error (void) const;
		const
		CString&  Get (void); // returns HTML document content that is currently displayed in the web control; if the result is empty, an error occurred;

		bool   Is_valid (void) const;

		CString   Title (void) const;
		err_code  Title (_pc_sz);

	private:
		CContent& operator = (const CContent&) = delete; CContent& operator = (CContent&&) = delete;
		mutable
		CError       m_error;
		CCharset     m_charset;
		CString      m_content;
		TBrwWndPtr& m_control;
	};

}}}

#endif/*_WEB_IE_CONTENT_H_INCLUDED*/