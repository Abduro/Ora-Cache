#ifndef _WEB_IE_LOCATOR_H_INCLUDED
#define _WEB_IE_LOCATOR_H_INCLUDED
/*
	Createed by Tech_dog (ebontrop@gmail.com) on 02-Oct-2026 at 09:45:24.611, UTC+4, Batumi, Friday;
	This is IE web url locator interface declaration file.
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { using namespace ::ex_ui::web::IE::defs;
namespace urls {

	class CExe_Url {
	public:
		// https://learn.microsoft.com/en-us/windows/win32/menurc/resource-types ;
		enum e_res_type : uint32_t {
		// resource types that may be possibly used in HTML's content;
		/* ----------+-------+------------+--------------------+
		 |  alias    | value | constant   | brief description; |
		 +-----------+-------+------------+-------------------*/
			e_binary = 10,  // RT_RCDATA  | App-defined resource (raw data);
			e_bitmap =  2,  // RT_BITMAP  | Bitmap resource;
			e_html   = 23,  // RT_HTML    | HTML resource;
			e_menu   =  4,  // RT_MENU    | Menu resource;
			e_string =  6,  // RT_STRING  | String-table entry;
			e__undef =  0,
		};
		CExe_Url (void); CExe_Url (const CExe_Url&) = delete; CExe_Url (CExe_Url&&) = delete; ~CExe_Url (void) = default;

		TError&  Error (void) const;

		_pc_sz   Get (void) const;
		err_code Set (_pc_sz _file_path, const e_res_type, const uint32_t _res_id);

	private:
		CExe_Url& operator = (const CExe_Url&) = delete; CExe_Url& operator = (CExe_Url&&) = delete;
		CError   m_error;
		CString  m_cache; // the format: res://<path_to_binary_file>/<resource_type>/<resource_id> ;
	};

	class CType {
	public:
		enum e_url_type : uint32_t {
			eHostExecutable  = 0,   // a link that points to resource of browser host (default);
			eExternalLink    = 1,   // a link that does not require a parse process;
			eOuterBrowser    = 2,   // a special link that contains a URL, which must be open by default browser separately;
			eInterCommand    = 3,   // a link that provides command identifier for web control host;
		};

		 CType (_pc_sz _lp_sz_pat = 0); CType (const CType&) = delete; CType (CType&&) = delete;
		 CType (const e_url_type = e_url_type::eHostExecutable);
		~CType (void);

		TError& Error (void) const;
		bool    IsCmd (void) const; // checks for internal command type;
		bool    IsExt (void) const; // checks for external URL type;
		bool    IsOut (void) const; // checks for outer browser URL type;

		e_url_type Get (void) const;
		void       Set (const e_url_type);
		err_code   Set (_pc_sz _lp_sz_pat);

		CType& operator << (_pc_sz _lp_sz_pat);
		CType& operator << (const e_url_type);

		operator TError& (void) const;     // returns encapsulated error object reference;
		operator e_url_type (void) const;  // returns encapsulated type;
		operator bool (void) const;        // checks for type availability, i.e. for no error;

		static int32_t MinLen (void);      // returns *pattern* length consistent with CStringW::GetLength();
		static CString Prefix (const e_url_type) ;    // evaluates a prefix if any;
		static e_url_type ToType (_pc_sz _lp_sz_pat); // converts string to type if possible;

	private:
		CType& operator = (const CType&) = delete; CType& operator = (CType&&) = delete;
		e_url_type m_type ;
		CError     m_error;
	};

	class CLocator {
	public:
		using e_url_type = CType::e_url_type;

		 CLocator (const e_url_type = e_url_type::eHostExecutable);
		 CLocator (_pc_sz _lp_sz_pat); CLocator (const CLocator&) = delete; CLocator (CLocator&&) = delete;
		~CLocator (void);

		bool          Accept(_pc_sz _pattern) const;
		const
		_variant_t&   Data  (void) const;
		dword_t       DataAsCommand (void) const;
		TErrorRef     Error (void) const;
		const
		CType& Type (void) const;
		CType& Type (void) ;

		_pc_sz    URL  (void) const;
		_pc_sz    URL  (_pc_sz lpszPattern);
		err_code  URL  (_pc_sz lpszPattern, CString& _result);

		CLocator& operator << (const CType&);
		CLocator& operator << (const e_url_type);
		CLocator& operator << (_pc_sz _pattern);

		operator dword_t (void)  const;  // gets URL data as internal command identifier;
		operator _pc_sz  (void)  const;  // gets a URL that is encapsulated in this object;
		operator TError& (void)  const;
		bool operator == (_pc_sz) const; // checks for URL similarity;

	private:
		mutable
		CError     m_error;
		CType      m_type ;
		CString    m_url  ;
		_variant_t m_data ;
	};
}

}}}
#endif/*_WEB_IE_LOCATOR_H_INCLUDED*/