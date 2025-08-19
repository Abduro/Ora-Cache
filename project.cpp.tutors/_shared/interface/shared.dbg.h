#ifndef _SHARED_DBG_H_INCLUDED
#define _SHARED_DBG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 00:09:05.317, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared project debug config declarations' file;
	-----------------------------------------------------------------------------
	Adopted to tutorials solution on 19-Aug-2025 at 11:33:11.427, UTC+4, Batumi, Tuesday;
*/
#include <cstdint>
#include <atltrace.h>

#include "shared.defs.h"
#include "shared.preproc.h"

#if defined(_DEBUG)
	// https://en.cppreference.com/w/cpp/language/enum ;
	enum class e_print : uint32_t {
		e_all   = 0x0,  // prints out the class name and namespace path, class field value(s);
		e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
		e_req   = 0x2   // prints out the class object field value(s) only;
	};

	// https://learn.microsoft.com/en-us/cpp/atl/reference/debugging-and-error-reporting-macros ;
	// https://stackoverflow.com/questions/20508086/getting-rid-of-atltracegeneral-category-shown-in-atltrace-output ; << good example ;

namespace shared { namespace dbg {

	using namespace shared::defs;

	class CTrace {
	private:
		CTrace (void) = delete; CTrace (const CTrace&) = delete; CTrace (CTrace&&) = delete; ~CTrace (void) = delete;
		
	public:
		enum e_category : uint32_t {
		     e_info = 0x0, // this is informative category trace prefix: [info] ;
		     e_warn = 0x1, // this is warning category trace prefix: [warn] ;
		     e_err  = 0x2, // this is error category trace prefix: [error] ;
		};
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

	private:
		CTrace& operator = (const CTrace&) = delete; CTrace& operator = (CTrace&&) = delete;
	};
}}

typedef shared::dbg::CTrace __trace;

#define __trace_err(_p_format, ...)  __trace::Out_0(__trace::e_err , _p_format, __VA_ARGS__);   // no namespace, class and method names are included;
#define __trace_info(_p_format, ...) __trace::Out_0(__trace::e_info, _p_format, __VA_ARGS__);   // no namespace, class and method names are included;
#define __trace_warn(_p_format, ...) __trace::Out_0(__trace::e_warn, _p_format, __VA_ARGS__);   // no namespace, class and method names are included;

#define __trace_err_2(_p_format, ...)  __trace::Out_2(__trace::e_err , (_pc_sz)__CLASS__, (_pc_sz)__METHOD__. _p_format, __VA_ARGS__); // class and metod names are included automatically;
#define __trace_info_2(_p_format, ...) __trace::Out_2(__trace::e_info, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;
#define __trace_warn_2(_p_format, ...) __trace::Out_2(__trace::e_warn, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // class and metod names are included automatically;

#define __trace_err_3(_p_format, ...)  __trace::Out_3(__trace::e_err , (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;
#define __trace_info_3(_p_format, ...) __trace::Out_3(__trace::e_info, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;
#define __trace_warn_3(_p_format, ...) __trace::Out_3(__trace::e_warn, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_format, __VA_ARGS__); // namespace, class and metod names are included automatically;

#else

#define __trace_err(_p_format, ...)    { _p_format; __VA_ARGS__; }
#define __trace_info(_p_format, ...)   { _p_format; __VA_ARGS__; }
#define __trace_warn(_p_format, ...)   { _p_format; __VA_ARGS__; }

#define __trace_err_2(_p_format, ...)  { _p_format; __VA_ARGS__; }
#define __trace_info_2(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_warn_2(_p_format, ...) { _p_format; __VA_ARGS__; }

#define __trace_err_3(_p_format, ...)  { _p_format; __VA_ARGS__; }
#define __trace_info_3(_p_format, ...) { _p_format; __VA_ARGS__; }
#define __trace_warn_3(_p_format, ...) { _p_format; __VA_ARGS__; }

#endif

#endif/*_SHARED_DBG_H_INCLUDED*/