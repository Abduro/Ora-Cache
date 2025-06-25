#ifndef _MSXML_ERROR_H_INCLUDED
#define _MSXML_ERROR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2024 at 22:37:20.5994402, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack MS XML error interface declaration file;
*/
#include "msxml.defs.h"

namespace shared { namespace xml { namespace ms {

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms767720(v=vs.85) ; error class members are here;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms757019(v=vs.85) ;

	typedef ::ATL::CComPtr<IXMLDOMParseError> TErrorPtr;

	class CParseError : public CError { typedef CError TBase;
	public:
		 CParseError (void);
		 CParseError (const CParseError&);
		 CParseError (CParseError&&) = delete;
		 CParseError (const TErrorPtr&);
		~CParseError (void);

	public:
		long    Code (void) const;      // returns the error code of the last parse;
		long    Line (void) const;      // returns the line number that contains the error;
		long    Position (void) const;  // returns the character position within the line where the error occurred;
		CString Reason (void) const;    // describes the reason for the error;
		long    Shift (void) const;     // returns the absolute XML source file position where the error occurred;
		CString Text (void) const;      // returns the full text of the line containing the error;
		CString Url (void) const;       // returns the URL of the XML document containing the last error;

	public:
		const
		TErrorPtr& Ptr (void) const;
		TErrorPtr& Ptr (void)      ;

		const bool Inited (void) const; // returns the status of raw parse error pointer initialization, checking the pointer for null is enough;
#ifdef _DEBUG
		CString  Print (void) const;    // outputs the error class attributes values to string for test purposes;
#endif

	public:
		CParseError&  operator = (const CParseError&);
		CParseError&  operator = (CParseError&&) = delete;
		CParseError&  operator <<(const TErrorPtr&);

		operator const TErrorPtr& (void) const;
		operator       TErrorPtr& (void)      ;

		operator const CError& (void) const;
		operator       CError& (void)      ;

		CError&  operator ()(void);

	private:
		TErrorPtr m_raw_ptr;
	};

}}}

#endif/*_MSXML_ERROR_H_INCLUDED*/