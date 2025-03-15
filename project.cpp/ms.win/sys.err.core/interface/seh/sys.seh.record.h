#ifndef _SYS_STD_RECORD_H_INCLUDED
#define _SYS_STD_RECORD_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-May-2024 at 10:27:27.4096435, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack EXCEPTION_RECORD structure wrapper interface declaration file;
*/
#include "sys.seh.common.h"
#include "sys.seh.code.h"
#include "sys.seh.flag.h"

namespace shared { namespace sys_core { namespace seh {

	class CRecord {
	public:
		 CRecord (void) ;
		 CRecord (const CRecord&);
		 CRecord (const TPointers* const);
		 CRecord (const TRecord* const);
		 CRecord (CRecord&&) = delete;
		~CRecord (void);

	public:
#if (0) // there is no reason to save input pointer to record memory that is being thrown;
		const
		TRecord& Get (void) const;
		TRecord& Get (void) ;
		err_code Set (const TRecord&);
#else
		const CCode&     Code (void) const;
		const TRawFlags& Flags(void) const;

		err_code Set (const TPointers* const); // gets a record pointer from exception ones and sets this record object's attributes;
		err_code Set (const TRecord* const);   // sets record object property from the exception record pointer that is being thrown by the system;

	protected:
		CCode&     Code  (void) ;
		TRawFlags& Flags (void) ;
#endif
	public:
#if defined (_DEBUG)
		CString    Print (_pc_sz _sep = _T("\n\t")) const; // prints out content of this object attributes; input separator is used for multiline output;

		CString  operator >>(const TPointers* const);
		CString  operator >>(const TRecord* const);
#endif
	public:
		CRecord& operator = (const CRecord&);
		CRecord& operator = (CRecord&&) = delete;

		CRecord& operator <<(const TPointers* const);
		CRecord& operator <<(const TRecord* const);

	protected:
		CRecord& operator <<(const CCode&);
		CRecord& operator <<(const TRawFlags&);

	private:
#if (0)
		TRecord   m_raw;
#else
		CCode     m_code;    // exception record has only one exception code;
		TRawFlags m_flags;   // a set of flags that may be contained;
#endif
	};

}}}

#endif/*_SYS_STD_RECORD_H_INCLUDED*/