#ifndef _WEB_IE_BROWSER_H_INCLUDED
#define _WEB_IE_BROWSER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2014 at 5:57:02pm, GMT+4, Saint-Petersburg, Thursday;
	This is Ebo Pack UIX library web browser control wrapper class(es) declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:01:28p, UTC+7, Phuket, Rawai, Monday;
	Adopted to v15a on 2-Oct-2018 at 10:06:09p, UTC+7, Novosibirsk, Tuesday;
*/
#include "web.ie.aux.h"
#include "web.ie.html.h"
#include "web.ie.content.h"
#include "web.ie.script.h"

#define _use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;

	class CWebBrowser {
	public:
		 CWebBrowser (IWbEvtHandler&); CWebBrowser (void) = delete; CWebBrowser (const CWebBrowser&) = delete; CWebBrowser (CWebBrowser&&) = delete;
		~CWebBrowser (void);
		const
		CCommand&  Command (void) const;
		CCommand&  Command (void) ;
		const
		CContent&  Content (void) const;
		CContent&  Content (void) ;

		err_code   Create (const HWND hParent, const RECT& rcArea_ref, const bool bVisible = true);
		err_code   Create (const HWND hParent, const RECT& rcArea_ref, CComPtr<IServiceProvider>&);
		err_code   Destroy(void);
		const
		TWebBrwPtr& Ctrl (void) const; // gets the reference to IE WebBrowser2 activeX control; (ro)
		TWebBrwPtr& Ctrl (void) ;      // gets the reference to IE WebBrowser2 activeX control; (rw)

		TErrorRef  Error  (void) const;
		const
		TBrwWndPtr& Host (void) const; // returns the reference to the activeX control (IWbBrowser2) host, i.e. CAxWindow, which holds its instance; (ro)
		TBrwWndPtr& Host (void) ;      // returns the reference to the activeX control (IWbBrowser2) host, i.e. CAxWindow, which holds its instance; (rw)
//#if defined(_use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_)
		err_code   Open (CComPtr<IStream>&);
//#else
		err_code   Open (CComPtr<IMoniker>&);
		err_code   Open (const TRawData&);
//#endif
		err_code   Open (_pc_sz pURL);
		
		err_code   Redirect (_pc_sz pTarget, const bool bAsync = true);
		err_code   Refresh (void);
		const
		CScript&   Script (void) const;
		CScript&   Script (void) ;
		const
		CState&    State (void) const;
		CState&    State (void) ;
		const
		CAxWindow& Window (void) const;
		CAxWindow& Window (void);

	private:
		CWebBrowser& operator = (const CWebBrowser&) = delete; CWebBrowser& operator = (CWebBrowser&&) = delete;
		mutable CError m_error;
		mutable TBrwWndPtr m_host; // this is the window ptr that helds IWebBrowser2 ActiveX control instance;
		TWebBrwPtr m_browser;
		CCommand   m_command;
		CContent   m_content;
		CScript    m_script;
		CState     m_state;
	};
}}}

typedef ex_ui::web::IE::CWebBrowser TIEBrowser;
TIEBrowser* Get_IE_ptr (void); // of course there nay be multiple instances of web browser object, but for test cases the singleton is enough;

#endif/*_WEB_IE_BROWSER_H_INCLUDED*/