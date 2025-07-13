#ifndef _EBO_TEST_$2$_MEM_H_INCLUDED
#define _EBO_TEST_$2$_MEM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Aug-2024 at 10:58:32.7913639, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared lib memory management base interface declaration file; 
*/
#include "_log.h"

#include "sys.mem.global.h"
#include "sys.mem.handle.h"
#include "sys.mem.heap.h"

namespace ebo { namespace boo { namespace test { namespace memory {

	using namespace ebo::boo::test;

	__class (CBuffer) {
	public:
		 CBuffer (const bool _b_verb = false);
		~CBuffer (void) = default;

	public:
		__ctor (_ctor);
		__method (Set);

	private:
		bool     m_b_verb;
		TRawData m_buffer;
	};

	__class (CHandle) {
	public:
		 CHandle (const bool _b_verb = false);
		~CHandle (void) = default;

	public:
		__ctor (_ctor);
		__method (Clone); // clones the input handle of temporary file that is created outside of this class;

	private:
		bool     m_b_verb;
		THandle  m_handle;
	};

	using THeap = shared::memory::CHeap; // the heap class has static methods only, thus no its object can be created;

	__class (CHeap) {
	public:
		 CHeap (const bool _b_verb = false);
		~CHeap (void) = default;

	public:
		__method (GetWhere);   // checks the input object pointer for allocation in the heap memory or on the stack;

	private:
		bool   m_b_verb;
	};

	__class (CMemAlloc) {
	public:
		 CMemAlloc (const bool _b_verb = false);
		~CMemAlloc (void) = default;

	public:
		__method (Life_Cycle);
		__method (Realloc);

	private:
		bool    m_b_verb;
		TPsuedo m_alloca;
	};
}}}}

#pragma comment(lib, "sys.shared_v15.lib")   // is already included in shared lib ebo_test_$$$ test project;
#pragma comment(lib, "sys.err.core_v15.lib") // system error handling wrapper lib;
#pragma comment(lib, "sys.mem.core_v15.lib") // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$2$_MEM_H_INCLUDED*/