#ifndef _SHARED_DBG_H_INCLUDED
#define _SHARED_DBG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 00:09:05.317, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared project debug config declarations' file;
*/
#include <cstdint>
#if defined(_DEBUG)
	// https://en.cppreference.com/w/cpp/language/enum ;
	enum class e_print : uint32_t {
		e_all   = 0x0,  // prints out the class name and namespace path, class field value(s);
		e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
		e_req   = 0x2   // prints out the class object field value(s) only;
	};
#endif

#endif/*_SHARED_DBG_H_INCLUDED*/