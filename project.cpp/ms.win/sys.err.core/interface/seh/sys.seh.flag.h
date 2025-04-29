#ifndef _SYS_SEH_FLAG_H_INCLUDED
#define _SYS_SEH_FLAG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-May-2024 at 15:30:20.9979909, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack system SEH EXCEPTION_RECORD flag enumeration interface declaration file;
*/
#include "sys.seh.common.h"

#define TSafe_Flag() shared::safe::TGuard guard(shared::safe::TMutex);

namespace shared { namespace sys_core { namespace seh {

	/*
		system usage flag is set by default to true, that means it is reserved for internal use by the OS system services;
		https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record
		...
		the excerpt from [ExceptionFlags] description:
		exception flags not present in the following table should be treated as reserved for system use ;
	*/
#define __ex_no_way   EXCEPTION_NONCONTINUABLE  // Noncontinuable exception;
#define __ex_unwind   EXCEPTION_UNWINDING       // Unwind is in progress;
#define __ex_to_exit  EXCEPTION_EXIT_UNWIND     // Exit unwind is in progress;
#define __ex_no_stack EXCEPTION_STACK_INVALID   // Stack out of limits or unaligned;
#define __ex_nested   EXCEPTION_NESTED_CALL     // Nested exception handler call;
#define __ex_target   EXCEPTION_TARGET_UNWIND   // Target unwind in progress;
#define __ex_collide  EXCEPTION_COLLIDED_UNWIND // Collided exception handler call;

	class CFlag : public CNode { typedef CNode TBase;
	public:
		enum _values   : uint8_t { // https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-dtyp/a88ed362-a905-4ed2-85f5-cfc8692c9842 ;
			e_none     = 0x0,
			e_no_way   = __ex_no_way  ,
			e_unwind   = __ex_unwind  ,
			e_go_exit  = __ex_to_exit ,
			e_no_stack = __ex_no_stack,
			e_nested   = __ex_nested  ,
			e_target   = __ex_target  ,
			e_collide  = __ex_collide ,
		};
	public:
		 CFlag (void);
		 CFlag (const CFlag&);
		 CFlag (const errno_l _code, _pc_sz _p_alias, _pc_sz _p_desc, bool _is_sys = true);
		 CFlag (CFlag&&) = default;
		~CFlag (void);
	public:
		bool Is (void) const;     // returns true if number code is not zero and description is set;
		bool Is_sys (void) const; // returns true if this flag is reserved for system use; returns false if the flag code is not assigned;
		bool Is_sys (bool) ;      // returns true if value of system use flag is changed;
#if defined (_DEBUG)
		CString  Print(const e_print = e_print::e_req) const;
#endif
	public:
		CFlag& operator = (const CFlag&);
		CFlag& operator = (CFlag&&) = default;
		CFlag& operator <<(const bool _is_sys);

	public:
		static const bool Has (const uint32_t _raw, const CFlag::_values); // returns true if raw input data contains the flag value specified;

	protected:
		bool m_is_sys;
	};

	typedef ::std::map<errno_l, CFlag> TFlags;

	class CFlag_Fake : public CZyme { typedef CZyme TBase;
	public:
		 CFlag_Fake (void); // sets predefined codes on creation of this class object;
		 CFlag_Fake (const CFlag_Fake&) = delete;
		 CFlag_Fake (CFlag_Fake&&) = delete;
		~CFlag_Fake (void);

	public:
		const
		TFlags&  Get (void) const;     // gets the reference to exception code collection ;
		err_code Set (void);           // adds a predefined exception codes;

		bool Has (errno_l) const;      // returns true in case when such a code is predefined in CCode::_values{} enum;
		const
		CFlag& Find (errno_l) const;   // if the code is not added to CCode::_values{} enum, a reference to fake code is returned;

#if defined(_DEBUG)
		CString Print (_pc_sz _pfx = _T("\t"), _pc_sz _sfx = _T("\n")) const;
#endif
	public:
		CFlag_Fake& operator = (const CFlag_Fake&) = delete;
		CFlag_Fake& operator = (CFlag_Fake&&) = delete;

	public:
		static CFlag_Fake& Ref (void); // returns singleton object for avoiding a creation of predefined exception code set each time;

	private:
		TFlags m_flags;
	};
	// this class is for specializing on unwinding stack, especially at exception handling moment ;
	// good explanation is here : https://stackoverflow.com/questions/2331316/what-is-stack-unwinding ;
	class CFlag_Unw : public CFlag { typedef CFlag TBase;
	public:
		 CFlag_Unw (void);
		 CFlag_Unw (const CFlag_Unw&);
		 CFlag_Unw (const errno_l _code, _pc_sz _p_alias, _pc_sz _p_desc); // the flag that relays to unwinding process is for system use usually;
		 CFlag_Unw (CFlag_Unw&&) = delete; // not required yet;
		~CFlag_Unw (void);

	public:
//		bool Is_unwind (void) const;
#if defined (_DEBUG)
//		CString  Print(const TBase::e_print = TBase::e_req) const;
#endif
	public:
		CFlag_Unw& operator = (const CFlag_Unw&);
		CFlag_Unw& operator = (CFlag_Unw&&) = delete; // not required yet;

	public:
		static const bool Is_unwind (const uint32_t); // just checks the input value for containing one of the unwinding flag values;
	};

	typedef ::std::vector<CFlag> TRawFlags;

	class CFlag_Unw_Collection : public CZyme { typedef CZyme TBase;
	public:
		 CFlag_Unw_Collection (void);
		 CFlag_Unw_Collection (const CFlag_Unw_Collection&);
		 CFlag_Unw_Collection (CFlag_Unw_Collection&&) = delete;
		~CFlag_Unw_Collection (void);

	public:
		const
		TRawFlags& Get (void) const;
		err_code   Set (const TPointers* const);    // extracts the information of flags from exception record of the pointers;
		err_code   Set (const TRecord* const);      // extracts the information of flags from exception record;
		err_code   Set (const uint32_t _raw_flags); // extracts flags from raw value;

	protected:
		void Set (const TRawFlags&);                // just for use by assignment operator;

	public:
		CFlag_Unw_Collection& operator = (const CFlag_Unw_Collection&);
		CFlag_Unw_Collection& operator = (CFlag_Unw_Collection&&) = delete;

		CFlag_Unw_Collection& operator <<(const TPointers* const);
		CFlag_Unw_Collection& operator <<(const TRecord* const);
		CFlag_Unw_Collection& operator <<(const uint32_t _raw_value);

		const TRawFlags& operator >> (const TRecord* const); // just for suitable return of extracted flags from input record pointer;

#if defined (_DEBUG)
		static CString  Print (const TRawFlags&, _pc_sz _sep = _T("\n\t")); // prints out the input flags; input separator is used for multiline output;
#endif

	protected:
		CFlag_Unw_Collection& operator <<(const TRawFlags&);

	private:
		TRawFlags m_flags;
	};
}}}

typedef shared::sys_core::seh::CFlag::_values TExcValues;

#endif/*_SYS_SEH_FLAG_H_INCLUDED*/