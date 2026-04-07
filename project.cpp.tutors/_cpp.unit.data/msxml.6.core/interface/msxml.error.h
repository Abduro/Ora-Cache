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

	class CErr_Desc {
	public:
		 CErr_Desc (void); CErr_Desc (const CErr_Desc&); CErr_Desc (CErr_Desc&&);
		~CErr_Desc (void) ;

	public:
		long   Code  (void) const;    // returns the error code of the last parse;
		bool   Code  (const long);    // sets the error code, returns 'true' if code is changed;
		_pc_sz Reason(void) const;    // describes the reason for the error;
		bool   Reason(_pc_sz) ;       // sets the reason by which the error is thrown; returns'true' in case of reason's change;
		_pc_sz Text  (void) const;    // returns the full text of the line containing the error;
		bool   Text  (_pc_sz) ;       // set a snippet of XML data that leads to parse error; returns 'true' in case of text's change;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		err_code  Set (const TErrorPtr _p_from);    // sets/updates values of all data fields from input parse error pointer;

	public:
		CErr_Desc& operator = (const CErr_Desc&);
		CErr_Desc& operator = (CErr_Desc&&);        // doesn't care about move or swap operation, just calls the above assignment operation;

		CErr_Desc& operator <<(const long _n_code);
		CErr_Desc& operator <<(_pc_sz _p_reason);
		CErr_Desc& operator >>(_pc_sz _for_fixing); // receives the snippet of the XML data text that leads to the error and requires to be fixed;

	private:
		long     m_code;
		CString  m_reason;
		CString  m_text;
	};

	class CErr_Pos {
	public:
		static const long not_set = -1;
	public:
		 CErr_Pos (void); CErr_Pos (const CErr_Pos&); CErr_Pos (CErr_Pos&&);
		~CErr_Pos (void) ;

	public:
		long  Col (void) const;      // returns the character position within the line where the error occurred;
		bool  Col (const long);

		long  Offset (void) const;   // returns the absolute XML source file position where the error occurred;
		bool  Offset (const long);
#if defined(_DEBUG)
		CString   Print  (const e_print = e_print::e_all) const;
#endif
		long  Row (void) const;      // returns the line/row number that contains the error;
		bool  Row (const long);

		err_code  Set (const TErrorPtr _p_from); // sets/updates values of all data fields from input parse error pointer;
		bool  Set (const long _n_col, const long _n_row, const long _n_offset);

	public:
		CErr_Pos& operator = (const CErr_Pos&);
		CErr_Pos& operator = (CErr_Pos&&);       // no swap operation is cared about, it is replaced by above copy assignment;

		CErr_Pos& operator <<(const long _n_col);
		CErr_Pos& operator ^ (const long _n_row);
		CErr_Pos& operator >>(const long _n_offset);

	private:
		long  m_col;
		long  m_row;     // it is called as a line, not the row, but nevertheless, a row much better suited to column;
		long  m_offset;  // the number of the characters from starting point of the XML data file;
	};

	class CParseError : public CError { typedef CError TBase;
	public:
		 CParseError (void);
		 CParseError (const CParseError&);
		 CParseError (CParseError&&) = delete;
		 CParseError (const TErrorPtr&);
		~CParseError (void);

	public:
		const
		CErr_Desc&  Desc (void) const;
		CErr_Desc&  Desc (void) ;
		// overrides the base error object error property due to if this parse error pointer is assigned, its code value must be checked too:
		// this->IXMLDOMParseError->get_errorCode() != 0;
		bool   Is (void) const;
		const
		CErr_Pos&   Pos (void) const;
		CErr_Pos&   Pos (void) ;

#ifdef _DEBUG
		// outputs the error class attributes' values to string for test purposes;
		// the enumerations' declaration collision: global e_print with error object its own e_print;
		CString   Print (const ::e_print = ::e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TErrorPtr&  Ptr (void) const;
		TErrorPtr&  Ptr (void)      ;

		err_code Refresh(void);        // updates all internal fields and components; this is useful case when raw parse pointer is assgned;
		
		_pc_sz   Source (void) const;  // returns the URL of the XML document containing the last error;

	public:
		CParseError&  operator = (const CParseError&);      // makes a copy of the input source object reference;
		CParseError&  operator = (CParseError&&) = delete;  // the move or swap operation is not necessary yet;

		CParseError&  operator <<(const TErrorPtr&);        // assignes the parse error interface pointer;
		CParseError&  operator <<(const CErr_Desc&);        // sets the parse error description object;
		CParseError&  operator <<(const CErr_Pos &);        // sets the object that describes at what position of XML data the error was thrown;

		operator const TErrorPtr& (void) const;             // allows to set this error object as input argument for getting raw pointer;
		operator       TErrorPtr& (void)      ;             // the same as above;

		operator const CError& (void) const;                // allows to set this error object as base one as an input argument;
		operator       CError& (void)      ;                // the same as above;

		const
		TErrorPtr& operator [](const long _not_used) const; // provides direct access to to the raw pointer for calling its properties;
		TErrorPtr& operator [](const long _not_used) ;      // the same as above;
		const
		CError&  operator ()(void) const;                   // provides direct access to base error object for using its functionality;
		CError&  operator ()(void);                         // the same as above;

	private:
		TErrorPtr m_raw_ptr ; // this pointer instance can be retrieved only from XML DOM document object;
		CErr_Pos  m_position; // the exact character position where the parser lost recognizing the XML data format;
		CErr_Desc m_desc;
		CString   m_src_url ; // this is the error source file URL;
	};

}}}

#endif/*_MSXML_ERROR_H_INCLUDED*/