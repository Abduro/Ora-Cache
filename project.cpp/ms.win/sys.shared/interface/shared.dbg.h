#ifndef _SHARED_DBG_H_INCLUDED
#define _SHARED_DBG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 00:09:05.317, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared project debug config declarations' file;
*/
#include <cstdint>
#include <atltrace.h>
#if defined(_DEBUG)
	// https://en.cppreference.com/w/cpp/language/enum ;
	enum class e_print : uint32_t {
		e_all   = 0x0,  // prints out the class name and namespace path, class field value(s);
		e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
		e_req   = 0x2   // prints out the class object field value(s) only;
	};

	// https://learn.microsoft.com/en-us/cpp/atl/reference/debugging-and-error-reporting-macros ;
	// https://stackoverflow.com/questions/20508086/getting-rid-of-atltracegeneral-category-shown-in-atltrace-output ; << good example ;
#if (0) // it is not required;
#ifdef ATLTRACE
#undef ATLTRACE
#endif
#ifdef ATLTRACE2
#undef ATLTRACE2
#endif
#endif
namespace shared { namespace dbg {

	class CTrace {
	private:
		CTrace (void) = delete; CTrace (const CTrace&) = delete; CTrace (CTrace&&) = delete; ~CTrace (void) = delete;
		
	public:
		enum e_category : uint32_t {
		     e_info = 0x0, // this is informative category trace prefix: [inf] ;
		     e_warn = 0x1, // this is warning category trace prefix: [wrn] ;
		     e_err  = 0x2, // this is error category trace prefix: [err] ;
		};
		// https://learn.microsoft.com/en-us/cpp/preprocessor/variadic-macros ;
		static void Out (const TCHAR* format, ...);
		static void Out (const e_category, const TCHAR* format, ...);

	private:
		CTrace& operator = (const CTrace&) = delete; CTrace& operator = (CTrace&&) = delete;
	};
}}

typedef shared::dbg::CTrace __trace;

#define __trace_err(_p_format, ...)  __trace::Out(__trace::e_err , _p_format, __VA_ARGS__);
#define __trace_info(_p_format, ...) __trace::Out(__trace::e_info, _p_format, __VA_ARGS__);
#define __trace_warn(_p_format, ...) __trace::Out(__trace::e_warn, _p_format, __VA_ARGS__);

#endif

#endif/*_SHARED_DBG_H_INCLUDED*/