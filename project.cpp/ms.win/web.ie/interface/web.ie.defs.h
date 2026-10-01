#ifndef _WEB_IE_DEFS_H_INCLUDED
#define _WEB_IE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2014 at 3:42:04a, GMT+3, Taganrog, Saturday;
	This is Ebo Pack shared UIX Web Browser library common interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 2:48:42p, UTC+7, Novosibirsk, Monday;
*/
#include <dispex.h>
#include <map>
#include <vector>
#include <Exdisp.h>
#include <Exdispid.h>

#include "shared.gen.sys.err.h"

namespace ex_ui { namespace web
{
	using shared::sys_core::CError;

	class CUrlLocateType {
	public:
		enum _e {
			eHostExecutable  = 0,   // a link that points to resource of browser host (default);
			eExternalLink    = 1,   // a link that does not require a parse process;
			eOuterBrowser    = 2,   // a special link that contains a URL, which must be open default browser separately;
			eInterCommand    = 3,   // a link that provides command identifier for web control host;
		};
	protected:
		_e          m_type ;
		CError      m_error;

	public:
		 CUrlLocateType (LPCWSTR _lp_sz_pat = NULL);
		 CUrlLocateType (const _e = CUrlLocateType::eHostExecutable);
		~CUrlLocateType (void);

	public:
		TErrorRef   Error(void) const;
		const bool  IsCmd(void) const; // checks for internal command type;
		const bool  IsExt(void) const; // checks for external URL type;
		const bool  IsOut(void) const; // checks for outer browser URL type;
		const _e    Type (void) const;
		VOID        Type (const _e)  ;
		HRESULT     Type (LPCWSTR _lp_sz_pat);

	public:
		CUrlLocateType& operator << (LPCWSTR _lp_sz_pat);
		CUrlLocateType& operator << (const _e);
	public:
		operator TErrorRef  (void)   const;  // returns encapsulated error object reference;
		operator const _e   (void)   const;  // returns encapsulated type;
		operator const bool (void)   const;  // checks for type availability, i.e. for no error;

	public:
		static const  INT MinLen(void)     ; // returns *pattern* length consistent with CStringW::GetLength();
		static CStringW   Prefix(const _e) ; // evaluates a prefix if any;
		static const _e   ToType(LPCWSTR _lp_sz_pat); // converts string to type if possible;
	};

	class CUrlLocator {
	private:
		mutable
		CError        m_error;
		CUrlLocateType
		              m_type ;
		CStringW      m_url  ;
		_variant_t    m_data ;

	public:
		 CUrlLocator(const CUrlLocateType::_e = CUrlLocateType::eHostExecutable);
		 CUrlLocator(LPCWSTR _lp_sz_pat);
		~CUrlLocator(void);

	public:
		bool          Accept(LPCWSTR _lp_sz_pat) const;
		const
		_variant_t&   Data  (void) const;
		DWORD         DataAsCommand(void) const;
		TErrorRef     Error (void) const;
		const
		CUrlLocateType& Type(void) const;
		CUrlLocateType& Type(void)      ;
		LPCWSTR       URL   (void) const;
		LPCWSTR       URL   (LPCWSTR lpszPattern);
		HRESULT       URL   (LPCWSTR lpszPattern, CStringW& _result);

	public:
		CUrlLocator& operator<<  (const CUrlLocateType&   );
		CUrlLocator& operator<<  (const CUrlLocateType::_e);
		CUrlLocator& operator<<  (LPCWSTR _lp_sz_pat);
	public:
		operator DWORD    (void)  const;                         // gets URL data as internal command identifier;
		operator LPCWSTR  (void)  const;                         // gets a URL that is encapsulated in this object;
		operator TErrorRef(void)  const;
		bool operator== (LPCWSTR) const;                         // checks for URL similarity;
	};

	class eBrowserEmulationVersion
	{
	public:
		enum _e {
			eDefault            =     0,
			eVersion7           =  7000,
			eVersion8           =  8000,
			eVersion8Standards  =  8888,
			eVersion9           =  9000,
			eVersion9Standards  =  9999,
			eVersion10          = 10000,
			eVersion10Standards = 10001,
			eVersion11          = 11000,
			eVersion11Edge      = 11001
		};
	};

	class CBrowserEmulateMan
	{
	private:
		mutable
		CError             m_error;
		CStringW         m_host_name;              // application executable name (without full path),
		                                             // which hosts the web browser control;
	public:
		CBrowserEmulateMan(LPCWSTR lpszHost = NULL); // if not provided, the current executable name is used;
	public:
		HRESULT            ApplyLatestVersion(void);
		TErrorRef          Error    (void)const;
		bool               IsEnabled(const eBrowserEmulationVersion::_e)const;
		eBrowserEmulationVersion::_e LatestAvailableVersion(void)const;
		eBrowserEmulationVersion::_e Mode(void)const;
		HRESULT            Mode (const eBrowserEmulationVersion::_e);
	};

	interface IWebBrowserEventHandler
	{
		virtual HRESULT    BrowserEvent_BeforeNavigate  (LPCWSTR lpszUrl)                           PURE;
		virtual HRESULT    BrowserEvent_DocumentComplete(LPCWSTR lpszUrl, const bool bStreamObject) PURE;
		virtual HRESULT    BrowserEvent_OnMouseMessage  (const MSG&) { return E_NOTIMPL; }
	};

	interface IHtmlElementEventCallback
	{
		virtual HRESULT    HtmlEvent_OnGeneric( LPCWSTR lpszElement, LPCWSTR lpszEvent ) { lpszElement; lpszEvent; return S_OK; }
	};
}}

#endif/*_WEB_IE_DEFS_H_INCLUDED*/