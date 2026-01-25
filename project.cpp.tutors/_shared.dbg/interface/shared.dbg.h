#ifndef _SHARED_DBG_H_INCLUDED
#define _SHARED_DBG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 00:09:05.317, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared project debug config declarations' file;
	-----------------------------------------------------------------------------
	Adopted to tutorials solution on 19-Aug-2025 at 11:33:11.427, UTC+4, Batumi, Tuesday;
*/
#include <atltrace.h>
#include <cstdarg>

#include "shared.types.h"
#include "shared.preproc.h"

	// https://en.cppreference.com/w/cpp/language/enum ;
	enum class e_print : uint32_t {
		e_all   = 0x0,  // prints out the class name and namespace path, class field value(s);
		e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
		e_req   = 0x2   // prints out the class object field value(s) only;
	};

	// https://learn.microsoft.com/en-us/cpp/atl/reference/debugging-and-error-reporting-macros ;
	// https://stackoverflow.com/questions/20508086/getting-rid-of-atltracegeneral-category-shown-in-atltrace-output ; << good example ;
#if defined(_DEBUG)
	/*
	*important*
		regarding a variadic argument list:
		::ATL::CString is capable to format variadic argument list by CString::FormatV() ::
		https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class?view=msvc-150#formatv ;

		alternatively, the following function can be used:
		StringCchVPrintfEx() :: https://learn.microsoft.com/en-us/windows/win32/api/strsafe/nf-strsafe-stringcchvprintfexw ;
	*/

namespace shared { namespace dbg {

	using namespace shared::defs;

	class CModule {
	public:
		static CString  Get_path (CError&); // gets full path to dyna-lib, it is especially intended for MSTest projects;
	private:
		CModule (void) = delete; CModule (const CModule&) = delete; CModule (CModule&&) = delete; ~CModule (void) = delete;
		CModule& operator = (const CModule&) = delete; CModule& operator = (CModule&&) = delete;
	};

	// debug messages cannot be sent to the test case console output window, but for running test cases it would be helpful to see all trace messages there;
	// the trace output and test console wrapper is not thead safe yet;
	interface ITestOutput {
		virtual void Write (_pc_sz _p_msg) { _p_msg; }
	};

	class CTrace {
	private:
		CTrace (void) = delete; CTrace (const CTrace&) = delete; CTrace (CTrace&&) = delete; ~CTrace (void) = delete;
		
	public:
		enum e_category : uint32_t {
		     e_err  = 0x2, // this is error category trace prefix: [error] ;
		     e_impt = 0x3, // this is positive message that requires a user attention: [important] ; light blue color; https://www.allacronyms.com/important/abbreviated ;
		     e_info = 0x0, // this is information category trace prefix: [info] ; light grey, perhaps as silver;
		     e_warn = 0x1, // this is warning category trace prefix: [warn] ; in yellow color;
		};

		static void Empty_ln (void);               // outputs an empty line;
		static void OnTime   (_pc_sz _p_text = 0); // outputs local time;
		static void Use_con  (const bool); // changes the output target: if it is set to 'true' outer console is used instead of VS 'debug output'; 
		static bool Use_con  (void);       // returns the current state of using outer console;

		// https://learn.microsoft.com/en-us/cpp/preprocessor/variadic-macros ;
		/*
			Initially it is supposed to have overloaded methods with one name 'Out',
			but unfortunately when using macros for calling those methods, the compliler generates the code that is not supposed to be:
			by unknown reason fixed parameters are recognized as a part of variadic arguments' list;
		*/
		static void Out_0(_pc_sz _p_sz_format, ...);
		static void Out_0(const e_category, _pc_sz _p_sz_format, ...);

		static void Out_2(const e_category, _pc_sz _p_cls, _pc_sz _p_method, _pc_sz _p_sz_format, ...); // this method for #define ;
		static void Out_3(const e_category, _pc_sz _p_nm_space, _pc_sz _p_cls, _pc_sz _p_method, _pc_sz _p_sz_format, ...); // this method for #define ;

		static void SetTestOut (ITestOutput*); // nullptr is also acceptable and it means to unsubscribe the test console from debug output;

	private:
		CTrace& operator = (const CTrace&) = delete; CTrace& operator = (CTrace&&) = delete;
	};
}}

typedef shared::dbg::CTrace __trace;

#define __empty_ln() __trace::Empty_ln();

#define __trace_err(_p_format, ...)  __trace::Out_0(__trace::e_err , _p_format, __VA_ARGS__);   // no namespace, class and method names are included;
#define __trace_impt(_p_format, ...) __trace::Out_0(__trace::e_impt, _p_format, __VA_ARGS__);   // no namespace, class and method names are included;
#define __trace_info(_p_format, ...) __trace::Out_0(__trace::e_info, _p_format, __VA_ARGS__);   // no namespace, class and method names are included;
#define __trace_warn(_p_format, ...) __trace::Out_0(__trace::e_warn, _p_format, __VA_ARGS__);   // no namespace, class and method names are included;

#define __trace_err_2(_p_format, ...)  __trace::Out_2(__trace::e_err , (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;
#define __trace_impt_2(_p_format, ...) __trace::Out_2(__trace::e_impt, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;
#define __trace_info_2(_p_format, ...) __trace::Out_2(__trace::e_info, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;
#define __trace_warn_2(_p_format, ...) __trace::Out_2(__trace::e_warn, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;

#define __trace_err_3(_p_format, ...)  __trace::Out_3(__trace::e_err , (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;
#define __trace_impt_3(_p_format, ...) __trace::Out_3(__trace::e_impt, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;
#define __trace_info_3(_p_format, ...) __trace::Out_3(__trace::e_info, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;
#define __trace_warn_3(_p_format, ...) __trace::Out_3(__trace::e_warn, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;

#else
#define __empty_ln() {}

#define __trace_err(_p_format, ...)    { _p_format; __VA_ARGS__; }
#define __trace_impt(_p_format, ...)   { _p_format; __VA_ARGS__; }
#define __trace_info(_p_format, ...)   { _p_format; __VA_ARGS__; }
#define __trace_warn(_p_format, ...)   { _p_format; __VA_ARGS__; }

#define __trace_err_2(_p_format, ...)  { _p_format; __VA_ARGS__; }
#define __trace_impt_2(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_info_2(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_warn_2(_p_format, ...) { _p_format; __VA_ARGS__; }

#define __trace_err_3(_p_format, ...)  { _p_format; __VA_ARGS__; }
#define __trace_impt_3(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_info_3(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_warn_3(_p_format, ...) { _p_format; __VA_ARGS__; }

#endif

#include <mutex>

namespace shared { namespace sys_core {

	typedef ::std::lock_guard<std::recursive_mutex> TGuard;
	static  ::std::recursive_mutex the_lock;
}}
#define TSafe_Lock() shared::sys_core::TGuard locker(shared::sys_core::the_lock);

#endif/*_SHARED_DBG_H_INCLUDED*/