#ifndef __OWNERDRAW_GDIPLUS_WRAP_H_
#define __OWNERDRAW_GDIPLUS_WRAP_H_
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2009 at 7:03:18p, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack GDI+ library owner draw wrapper class(es) declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 3-May-2020 at 0:33:05a, UTC+7, Novosibirsk, Sunday;
*/
#include "uix.gdi.defs.h"

namespace ex_ui { namespace draw {

	using shared::sys_core::CError;

	class CFontOptions {
	public:
		enum _opt : ULONG {
			eNone          = 0x0000, // creates font with default (i.e. system height/bold/italic)
			eExactSize     = 0x0001, // creates font with specified size (irrelative)
			eRelativeSize  = 0x0002, // creates font with relative size (reduction/increasing)
			eBold          = 0x0004,
			eItalic        = 0x0008,
			eUnderline     = 0x0010,
		};

	public:
		 CFontOptions (void);
		 explicit CFontOptions (const DWORD _opts);
		 explicit CFontOptions (const CFontOptions&);
		~CFontOptions (void);

	public:
		DWORD   Get (void) const;
		bool    Has (const DWORD _opts) const;
		DWORD&  Set (void)      ;
#if defined(_DEBUG)
		static
		CString Print (const uint32_t _u_flags) ;             // prints only flags provided for testing purpose;
		CString Print (const e_print = e_print::e_all) const; // the same as above, but value is currently set to field of this class;
#endif
	public:
		bool    IsBold (void) const;
		bool    IsItalic (void) const;
		bool    IsUnderline (void) const;

	public:
		CFontOptions&  operator = (const DWORD _opts);        // sets options value;
		CFontOptions&  operator = (const CFontOptions&);      // sets options value;
		CFontOptions&  operator+= (const DWORD _opts);        // adds options;
		CFontOptions&  operator-= (const DWORD _opts);        // excludes options;

	public:
		const bool     operator == (const CFontOptions&) const;
		const bool     operator != (const CFontOptions&) const;
		const bool     operator == (const DWORD _opts) const;          // returns true if options include value provided, otherwise, false;
		const bool     operator != (const DWORD _opts) const;          // returns true if options exclude value provided, otherwise, false;
		operator const DWORD (void) const;

	protected:
		DWORD m_opts;
	};
}}

typedef ex_ui::draw::CFontOptions  TFontOpts;

namespace ex_ui { namespace draw {
	// https://stackoverflow.com/questions/371018/create-modified-hfont-from-hfont ;
	class CFont_Base {
	protected:
		 CFont_Base (void);
		 CFont_Base (const CFont_Base&);
		 CFont_Base (const HFONT);
		 CFont_Base (CFont_Base&&);
		~CFont_Base (void);

	public:
		err_code  Destroy(void);
		HFONT     Detach (void);
		HFONT     Handle (void) const;
		bool      Is     (void) const;

		TErrorRef Error (void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		HFONT const Get (void) const ; // the same as Handle();
		err_code    Set (const HFONT); // duplicates an input font; 

	public:
		operator const HFONT (void) const;

	public:
		CFont_Base& operator = (const CFont_Base&);
		CFont_Base& operator <<(const HFONT);
		CFont_Base& operator = (CFont_Base&&); // TODO::requires a review;

	protected:
		HFONT  m_handle;
		CError m_error;

	public:
		static bool Is (const HFONT);
	};

#if defined(_DEBUG)
	class CFont_Dbg : public CFont_Base { typedef CFont_Base TBase;
	public:
		 CFont_Dbg (void); CFont_Dbg (const CFont_Dbg&) = delete; CFont_Dbg (CFont_Dbg&&) = delete;
		~CFont_Dbg (void);

	public:
		const
		CFont_Base&  Base (void) const;
		CFont_Base&  Base (void) ;

	private:
		CFont_Dbg&  operator = (const CFont_Dbg&) = delete;
		CFont_Dbg&  operator = (CFont_Dbg&&) = delete;
	};
#endif

	//  https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-logfontw
	class CFont : public CFont_Base { typedef CFont_Base TBase;
	public:
		 CFont (void); // no font is created on this constructor;
		 CFont (_pc_sz pszFamily, const dword dwOptions = TFontOpts::eNone, const LONG lParam = 0); // system font is created from the desktop;
		~CFont (void);
	public:
		int16_t   Angle (void) const;    // gets the current rotation angle in degrees; by default is set to zero;
		bool      Angle (const int16_t); // sets the rotation angle; returns true if the value is changed;
		/* inputs:
				pszFamily - font name; dwOptions - font attributes; lParam - an exact font size or size factor (+/-); */
		err_code  Create (_pc_sz pszFamily = nullptr, const dword dwOptions = CFontOptions::eNone, const _long lParam = 0);
		HFONT     Detach (void);
		_pc_sz    Family (void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	private:
		bool      m_bManaged; // flag that indicates font handle must be destroyed (if the font is not stock one)
		int16_t   m_angle   ; // the rotation angle, can be eiter positive (for counter-cw) in range [0:360];
		CString   m_family  ;
	};

	class CFontScalable : public CFont_Base {
	                     typedef CFont_Base TBase;
	public:
		 CFontScalable(const HDC, _pc_sz lpszFontFamily, const INT nSize, const DWORD dwOptions = CFontOptions::eNone);
		~CFontScalable(void);

	public:
		HRESULT   Create (const HDC, _pc_sz lpszFontFamily, const INT nSize, const DWORD dwOptions = CFontOptions::eNone);
	};
	// *important*: CLogFont is defined in WTL, but it has a lot of functionality that is not required,
	//              thus the following class is used for drawing functions;
	class CLogFont {
	public:
		 CLogFont (void);
		 CLogFont (const CLogFont&);
		 CLogFont (const HFONT);
		 CLogFont (const LOGFONT&);
		 CLogFont (CLogFont&&);
		~CLogFont (void);

	public:
		CLogFont& operator = (const CLogFont&);
		CLogFont& operator <<(const HFONT);
		CLogFont& operator <<(const LOGFONT&);
		CLogFont& operator = (CLogFont&&);

	public:
		TErrorRef   Error (void) const;

	public:
		const
		LOGFONT&    Get (void) const;
		LOGFONT&    Get (void)      ;
		err_code    Set (void)      ; // it would be better to call this method as 'Clear';
		err_code    Set (const LOGFONT&);
		err_code    Set (const HFONT, const DWORD _opts = CFontOptions::eNone);

	public:
		operator const  LOGFONT&(void)
		const; operator LOGFONT&(void);

	protected:
		LOGFONT   m_log  ;
		CError    m_error;
	};
}}

typedef ex_ui::draw::CFont TFont;
typedef ex_ui::draw::CLogFont TLogFont;

#endif/*__OWNERDRAW_GDIPLUS_WRAP_H_*/