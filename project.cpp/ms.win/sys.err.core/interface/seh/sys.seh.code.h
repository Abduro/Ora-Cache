#ifndef _SYS_SEH_CODE_H_INCLUDED
#define _SYS_SEH_CODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-May-2024 at 22:59:47.5446193, UTC+7, Novosibirsk, Monday;
	This is Ebo Pack system SEH EXCEPTION_RECORD code enumeration interface declaration file;
*/
#include "sys.seh.common.h"

#define TSafe_Code() shared::safe::TGuard guard(shared::safe::TMutex);
// the predefined codes are here: https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record ;
// some of the codes are listed below:
#pragma region __sys_ex_code
#define __ex_acc_violate EXCEPTION_ACCESS_VIOLATION      // The thread tried to read from or write to a virtual address ... have the appropriate access.
#define __ex_out_bounds  EXCEPTION_ARRAY_BOUNDS_EXCEEDED // The thread tried to access an array element that is out of bounds ...
#define __ex_dbg_break   EXCEPTION_BREAKPOINT            // A breakpoint was encountered.
#define __ex_bad_align   EXCEPTION_DATATYPE_MISALIGNMENT // The thread tried to read or write data that is misaligned on hardware ...
#define __ex_not_operand EXCEPTION_FLT_DENORMAL_OPERAND  // One of the operands in a floating-point operation is denormal.
#define __ex_div_flt_0   EXCEPTION_FLT_DIVIDE_BY_ZERO    // The thread tried to divide a floating-point value by a floating-point divisor of zero.
#define __ex_div_int_0   EXCEPTION_INT_DIVIDE_BY_ZERO    // The thread tried to divide an integer value by an integer divisor of zero.
#define __ex_ovr_stack   EXCEPTION_STACK_OVERFLOW        // The thread used up its stack.
#define __ex_err_page    EXCEPTION_IN_PAGE_ERROR         // The thread tried to access a page that was not present.
#pragma endregion

namespace shared { namespace sys_core { namespace seh {

	// system exception codes is defined in format 0xc007xxxx; so this must be transformed to long value of the two first bytes;
	__inline errno_l ex_sys_const_to_code (uint32_t _sys_const_def) { return (uint32_t)(_sys_const_def & 0xff); }
#define __sys_ex_code_2_errno(val) (val & 0xff)
	
	class CCode : public CNode { typedef CNode TBase;
	public:
		// if do not declare such enumeration, c/c++ compiler does not recognize double '#define' preprocessor declaration;
		// this is mostly (possibly) expected codes that can be thrown;
		enum _values : errno_l {
			e_acc_violate = __sys_ex_code_2_errno(__ex_acc_violate) ,
			e_out_bounds  = __sys_ex_code_2_errno(__ex_out_bounds ) ,
			e_dbg_break   = __sys_ex_code_2_errno(__ex_dbg_break  ) ,
			e_bad_align   = __sys_ex_code_2_errno(__ex_bad_align  ) ,
			e_not_operand = __sys_ex_code_2_errno(__ex_not_operand) ,
			e_div_flt_0   = __sys_ex_code_2_errno(__ex_div_flt_0  ) ,
			e_div_int_0   = __sys_ex_code_2_errno(__ex_div_int_0  ) ,
			e_ovr_stack   = __sys_ex_code_2_errno(__ex_ovr_stack  ) ,
			e_err_page    = __sys_ex_code_2_errno(__ex_err_page   ) ,
		};
	public:
		 CCode (void);
		 CCode (const CCode&);
		 CCode (const errno_l _code, _pc_sz _alias, _pc_sz _desc, uint32_t _origin);
		 CCode (CCode&&) = delete;
		~CCode (void);
	public:
		bool Is (void) const;  // returns true if number code is not zero and description is set;
#if defined (_DEBUG)
		CString  Print(const e_print = e_print::e_req) const;
#endif
		uint32_t Origin (void) const; // returns original code value, as it is set in system API; issue: the parent code value will be not coincident;
		bool     Origin (uint32_t)  ; // sets new origin code, the parent code value is updated appropriately; returns true if changed;

	public:
		CCode& operator = (const CCode&);
		CCode& operator = (CCode&&) = delete;

		CCode& operator <<(const uint32_t _origin);

	private:
		uint32_t m_origin;
	};

	typedef ::std::map<errno_l, CCode> TCodes;  // a key is exception code, a value - code object;
	/*
		this class object can be created and called on the stack, but Find() method returns a reference to the code object being found, 
		and it may lead to the error that is thrown by using this reference later, i.e. after destoying this collection object on the stack changing;
		it is safer to use singleton Ref();
	*/
	class CCode_Fake : public CZyme { typedef CZyme TBase;
	public:
		 CCode_Fake (void); // sets predefined codes on creation of this class object;
		 CCode_Fake (const CCode_Fake&) = delete;
		 CCode_Fake (CCode_Fake&&) = delete;
		~CCode_Fake (void);

	public:
		const CCode& Get (const TPointers* const) const; // extracts the information of code from exception record;
		const CCode& Get (const TRecord* const) const;   // extracts the information of code from exception record;
		const
		TCodes&  Get (void) const;     // gets the reference to exception code collection ;
		err_code Set (void);           // adds a predefined exception codes;

		bool Has (errno_l) const;      // returns true in case when such a code is predefined in CCode::_values{} enum;
		const
		CCode& Find (errno_l) const;   // if the code is not added to CCode::_values{} enum, a reference to fake code is returned;
		const
		CCode& Find (uint32_t) const;  // using original code value for finding the code object; map hash is not used, just a loop through all objects;

#if defined(_DEBUG)
		CString Print (_pc_sz _pfx = _T("\t"), _pc_sz _sfx = _T("\n")) const;
#endif
	public:
		CCode_Fake& operator = (const CCode_Fake&) = delete;
		CCode_Fake& operator = (CCode_Fake&&) = delete;

		const CCode& operator <<(const TPointers* const); // tries to extract information of exception codes from the record;
		const CCode& operator <<(const TRecord* const);   // tries to extract information of exception codes from the record;

	public:
		static CCode_Fake& Ref (void); // returns singleton object for avoiding a creation of predefined exception code set each time;

	private:
		TCodes m_codes;
	};

}}}

typedef shared::sys_core::seh::CCode::_values  TCodeValues;

#endif/*_SYS_SEH_CODE_H_INCLUDED*/