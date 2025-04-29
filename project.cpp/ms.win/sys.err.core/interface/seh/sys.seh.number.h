#ifndef _SYS_SEH_NUMBER_H_INCLUDED
#define _SYS_SEH_NUMBER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-May-2024 at 14:04:04.9384459, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack errno constant enumeration interface declaration file;
*/
#include "sys.seh.common.h"

#define TSafe_No() shared::safe::TGuard guard(shared::safe::TMutex);

namespace shared { namespace sys_core { namespace seh {

	using TString = TStringEx;

	/*
		https://learn.microsoft.com/en-us/cpp/c-runtime-library/errno-constants ;
		this class contains a description of system error numbers (not for all) ;
	*/
	class CNumber : public CNode { typedef CNode TBase;
	public:
		 CNumber (void);
		 CNumber (const CNumber&);
		 CNumber (const errno_l, _pc_sz _alias, _pc_sz _desc);
		 CNumber (CNumber&&) = delete;
		~CNumber (void);

	public:
		bool Is (void) const;  // returns true if number code is not zero and description is set;
#if defined (_DEBUG)
		CString  Print(const ::e_print = e_print::e_req) const;
#endif
	public:
		CNumber& operator = (const CNumber&);
		CNumber& operator = (CNumber&&) = delete;
	};

	typedef ::std::map<errno_l, CNumber> TNumbers;
	/*
		not all error numbers is enumerated by this class, fake number enumeration takes care about this;
		only the most common error numbers are included in the set, for example, errors that occur when copying data in memory:
		https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s ;
	*/
	
	class CNumber_Fake : public CZyme { typedef CZyme TBase;
	public:
		 CNumber_Fake (void);
		 CNumber_Fake (const CNumber_Fake&) = delete;
		 CNumber_Fake (CNumber_Fake&&) = delete;
		~CNumber_Fake (void);

	public:
		const
		TNumbers& Get (void) const;      // gets the reference to number collection ;
		err_code  Set (void) ;           // adds a predefined error numbers;

		bool Has (errno_l) const;        // returns true in case when predefined number collection has the object of such value;
		const
		CNumber& Find (errno_l) const;   // returns found number object, otherwise fake object is returned; *important*: partially thread-safe;
#if defined(_DEBUG)
		CString Print (_pc_sz _pfx = _T("\t"), _pc_sz _sfx = _T("\n")) const;
#endif
	public:
		CNumber_Fake&  operator = (const CNumber_Fake&) = delete;
		CNumber_Fake&  operator = (CNumber_Fake&&) = delete;

	public:
		static CNumber_Fake& Ref (void); // returns singleton object for avoiding a creation of predefined exception number set each time;

	private:
		TNumbers m_numbers;
	};
}}}

#endif/*_SYS_SEH_NUMBER_H_INCLUDED*/