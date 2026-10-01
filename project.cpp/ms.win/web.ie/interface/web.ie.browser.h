#ifndef _UIXFRAME_H_F5F0005B_EB0A_4905_BD5F_98AACA44E965_INCLUDED
#define _UIXFRAME_H_F5F0005B_EB0A_4905_BD5F_98AACA44E965_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2014 at 5:57:02pm, GMT+4, Saint-Petersburg, Thursday;
	This is Ebo Pack UIX library web browser control wrapper class(es) declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:01:28p, UTC+7, Phuket, Rawai, Monday;
	Adopted to v15a on 2-Oct-2018 at 10:06:09p, UTC+7, Novosibirsk, Tuesday;
*/
#include "shared.gen.sys.err.h"
#if (0)
#include "generic.stg.data.h"
#endif
#include "shared.web.defs.h"
#include "shared.web.html.el.h"

#define _use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_

namespace ex_ui { namespace web
{
	namespace core {
		class CWebBrowserWrap;
	}
	using ex_ui::web::core::CWebBrowserWrap;
	using shared::sys_core::CError;
#if(0)
	using shared::lite::data::CRawData;
#endif
	class CWebBrowser
	{
		typedef ::ATL::CComQIPtr<IWebBrowser2> TWebBrowser;
	private:
		mutable CError           m_error;
		mutable CWebBrowserWrap* m_browser;
		TWebBrowser              m_web_obj;
	public:
		 CWebBrowser(IWebBrowserEventHandler&);
		~CWebBrowser(void);
	public:
		CStringW                 Charset(void)const;
		HRESULT                  Charset(LPCWSTR, const bool bRefresh);
		HRESULT                  Content(CStringW&)const;    // returns HTML document content that is currently displayed in the control;
		HRESULT                  Create (const HWND hParent, const RECT& rcArea_ref, const bool bVisible = true);
		HRESULT                  Create (const HWND hParent, const RECT& rcArea_ref, ::ATL::CComPtr<IServiceProvider>&);
		HRESULT                  Destroy(void);
		TErrorRef                Error  (void)const;
		HRESULT                  ExecuteScript(LPCWSTR lpszScript);
		const
		::ATL::CAxWindow&        GetAxWindowRef(void) const;
		::ATL::CAxWindow&        GetAxWindowRef(void);
		HRESULT                  GetScriptObject(::ATL::CComPtr<IDispatch>&)const;
		bool                     IsBusy (void)const;
		bool                     IsValid(void)const;
#if defined(_use_IE6_compatible_CB5829FE_6DE5_4fe2_B8D8_32996330F16B_)
		HRESULT                  Open(::ATL::CComPtr<IStream>&);
#else
		HRESULT                  Open(::ATL::CComPtr<IMoniker>&);
		HRESULT                  Open(const CRawData&);
#endif
		HRESULT                  Open (LPCWSTR pURL);
		HRESULT                  Print(void);
		HRESULT                  PrintPreview(void);
		HRESULT                  Redirect(LPCWSTR pTarget,const bool bAsync = true);
		HRESULT                  Refresh (void);
		HRESULT                  SetBackColor  (const COLORREF);
		void                     SetInitialized(void);
		bool                     Silent(void) const;
		HRESULT                  Silent(const bool);      // if true, it suppresses ***all*** message boxes
		::ATL::CStringW          Title (void) const;
		HRESULT                  Title (LPCWSTR);
	public:
		operator CAxWindow&(void);
	private: // non-copyable;
		CWebBrowser (const CWebBrowser&);
		CWebBrowser& operator = (const CWebBrowser&);
	};
}}

#endif/*_UIXFRAME_H_F5F0005B_EB0A_4905_BD5F_98AACA44E965_INCLUDED*/