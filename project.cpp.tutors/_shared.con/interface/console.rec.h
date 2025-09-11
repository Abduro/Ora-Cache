#ifndef _OUT_RECORD_H_INCLUDED
#define _OUT_RECORD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2022 at 08:00:21.7006502, UTC+7, Novosibirsk, Sunday;
	This is system console output record interface declaration file;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.defs.h"

namespace shared { namespace console {

	class CRecord
	{
	public:
		 CRecord (void);
		 CRecord (const CRecord&);
		 CRecord (TRecordType, _pc_sz _lp_sz_text);
		~CRecord (void);

	public:
		_pc_sz   Text (void) const;       // gets a text of the record;
		err_code Text (_pc_sz)   ;       // sets a text to the record; returns E_INVALIDARG in case when given text is nullptr or is empty;

		TRecType Type (void) const;
		err_code Type (TRecType)  ;       // returns S_OK if current type is not equal to given value, otherwise S_FALSE is returned;

		bool  IsValid (void) const;       // checks the record text for validity;

	public:
		err_code   Out(void) const;       // just outputs the text, timestamp and record header;

	public:
		CRecord&   operator = (const CRecord&);
		CRecord&   operator <<(_pc_sz _lp_sz_text);
		CRecord&   operator <<(TRecordType);

	public:
		operator _pc_sz  (void) const;
		operator TRecType(void) const; 

	protected:
		TRecordType m_rec_type;           // by default it is info record type;
		CString     m_rec_text;           // actually, caching the message text for output is not required and must be deprecated;
	};

	class CRec_Err : public CRecord {
	                typedef CRecord TBase;
	public:
		 CRec_Err (_pc_sz _lp_sz_text);  // calls base class error output function automatically;
		 CRec_Err (TErrorRef);            // applies an error output template;
		~CRec_Err (void);
	};

	class CRec_Info : public CRecord {
	                 typedef CRecord TBase;
	public:
		 CRec_Info (_pc_sz _lp_sz_text); // calls base class info output function automatically;
		~CRec_Info (void);
	};

	class CRec_Warn : public CRecord {
	                 typedef CRecord TBase;
	public:
		 CRec_Warn (_pc_sz _lp_sz_text); // calls base class warning output function automatically;
		~CRec_Warn (void);
	};
}}

typedef shared::console::CRecord TRecord;

#endif/*_OUT_RECORD_H_INCLUDED*/