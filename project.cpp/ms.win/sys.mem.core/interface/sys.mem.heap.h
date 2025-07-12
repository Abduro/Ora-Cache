#ifndef _GENERICSTGDATA_H_INCLUDED
#define _GENERICSTGDATA_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2010 at 1:56:43am, GMT+3, Rostov-on-Don, Thursday;
	This is SfxSOA package shared library generic raw data class declaration file. [voluntary project]
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 28-May-2018 at 11:58:22a, UTC+7, Phuket, Rawai, Monday; [Upwork.com]
	Adopted to Geometry Curve project on 17-Feb-2024 at 23:41:57.4957620, UTC+7, Novosibirsk, Saturday; [trying to find work in software ]
*/
#include <vector>
#include <atlfile.h>
#include <atlsafe.h>

#include <crtdbg.h>

#include "sys.error.h" // _CrtIsValidHeapPointer() looks like for checking a pointer *share*; it is dependable on input parameters' signature;
#if (0)
#include "sys.com.array.h" // moved to sys.com.core adapter class;
#endif
#include "shared.string.h"

namespace shared { namespace memory
{
	using shared::sys_core::CError;
	using TError  = const CError;

	using namespace shared::types;

	using byte    = BYTE ;        // perhaps this 'using' replaces the 'byte' data type, but who cares about mvc++ spec, winapi is important here;
	using p_byte  = byte*;        // such a kind of 'using' may not be always used due to compiler error(s) like this: C2440|C2446; (requires to check);
	using pc_byte = const p_byte;

	/*
		The class CHeap has to method of checking where object memory is : either in heap or on stack;
		Is_alloca() and Is_stack() give correct result, but are implemented in different ways;
		ToDo: Is_alloca needs more tests, because it throws an exception in case of applying new operator for allocating memory in heap;
	*/

	class CHeap {
	public:
		CHeap (void) = delete; CHeap(const CHeap&) = delete; CHeap(CHeap&&) = delete; ~CHeap(void) = delete; // looks like a namespace this time;
	public:
#pragma region __refs_6
		// https://learn.microsoft.com/en-us/previous-versions/ys6cfhhh(v=vs.140) >> one of the possible approaches; but it is not recommended to use this approach;
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapvalidate >> no way;
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapwalk >> maybe is this one;

		// https://stackoverflow.com/questions/1576300/checking-if-a-pointer-is-allocated-memory-or-not >> has no deal;
#pragma endregion
		static bool Is_alloca (const void* const);
		// https://www.codeproject.com/Messages/2467319/Re-Determine-Location-of-a-Variable >> this answer is right and works;
		// https://www.codeproject.com/Members/Jeffrey-Walton >> thanks for the answer;
		static bool Is_stack  (const void* const);

	private:
		CHeap& operator = (const CHeap&) = delete;
		CHeap& operator = (CHeap&&) = delete;
	};

	using CFile   = ::ATL::CAtlFile;

	// https://learn.microsoft.com/en-us/windows/win32/Memory/heap-functions ;
	/* *important*:
	    considering the following fact that the memory is allocated in the heap, HeapValidate() function must be used;
		but it is necessary to take into account some special circumstances regarding a performance of the validate process;
	*/
	// raw buffer is just for storing data and is not intended for heap management, its copy and move constructors and operators are disabled;
	class CRawBuffer {
	protected:
		 CRawBuffer (void); CRawBuffer (const CRawBuffer&) = delete; CRawBuffer (CRawBuffer&&) = delete;
		~CRawBuffer (void);

	public:
		err_code Clear  (void);         // removes the *data* from the heap; the ptr to heap memory block remains valid;
		TError&  Error  (void) const;   // returns the error object;
		bool    IsEmpty (void) const;   // checks memory block for containing a data, otherwize the block is filled by zeros; (may be very slow);
		bool    IsValid (bool _verify = false) const; // checks a pointer to the memory block in heap; no HeapValidate() is called by default;

	public:
		CRawBuffer& operator = (const CRawBuffer&) = delete;
		CRawBuffer& operator = (CRawBuffer&&) = delete;

	protected:
		byte*   m_pData ;
		dword   m_dwSize;

	protected:
		mutable CError m_error; // a mutability is required for methods or functions those do not change the state of this class object: IsValid()...;
	};
	class CRawData : public  CRawBuffer { typedef CRawBuffer TBase;
	public:
		 CRawData (void);
		 CRawData (const CRawData&);
		 CRawData (CRawData&&);
#if (0) // moved to sys.com.core adapter class;
		 CRawData (const _variant_t&);       // ia created from bstr data;
#endif
		 CRawData (const dword dwSize);
#if (0) // moved to sys.com.core adapter class;
		 CRawData (const LPSAFEARRAY, const VARTYPE _v_expected = VT_UI1);
#endif
		 CRawData (const byte* pData, const dword dwSize);
		~CRawData (void);

	public:
		err_code  Append (const CRawData&);
		err_code  Append (const byte* pData, const dword dwSize);
		// ToDo:  Attach cannot use const byte* input arg due to const_cast must be applied;
		err_code  Attach (const byte* pData, const dword dwSize , const bool _reset); // data must be created in current process memory heap;

#if (0) // moved to sys.com.core adapter class;
		err_code  CopyToVariantAsArray(_variant_t&)const;          // data is interpreted as binary and is copied to safe array as is;
		err_code  CopyToVariantAsUtf16(_variant_t&)const;          // data is interpreted as Utf8 text and is converted to Utf16 bstr;
		err_code  CopyToVariantAsUtf8 (_variant_t&)const;          // data is interpreted as Utf8 text and is copied to bstr as is;
#endif
		err_code  Create (const dword dwSize);                     // creates a memory block by specified size;
		err_code  Create (const byte* pData, const dword dwSize);  // creates a memory block by specified size and copies input data to the block;
#if (0) // moved to sys.com.core adapter class;
		err_code  Create (const LPSAFEARRAY, const VARTYPE _v_expected = VT_UI1);
#endif
		err_code  Create (_pc_sz _lp_sz_file);       // creates buffer from file;
		p_byte    Detach (void) ;                    // detaches from the memory block handle;
		err_code  Free   (void) ;                    // deallocates the memory block; destroys heap handle;
		
		err_code  Extend (const dword _sz_of_add);   // extends/increases the memory by reallocating it in accordance with given size;
		const
		byte*     GetData(void) const;               // returns const ptr to memory block data (ro);
		byte*     GetData(void)      ;               // returns pointer to memory block data (rw);
		dword     GetSize(void) const;               // gets the size of the memory block that is used in creating of it; no HeapSize() is used;
		                                             // https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapsize ;
		err_code  ToFile (_pc_sz _lp_sz_path) const; // saves data to file specified;
#if (0) // moved to sys.com.core adapter class;
		err_code  ToSafeArray  (LPSAFEARRAY& _out_array,  const VARTYPE _v_expected = VT_UI1) const; // other variant types are not expected;
#endif
		err_code  ToStringUtf16(CStringW& ) const;   // assumes the buffer contains unicode string;
		err_code  ToStringUtf8 (CStringA& ) const;   // assumes the buffer contains ansi string;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		operator const bool  (void) const;  // returns a validity state of the object;
		operator const dword (void) const;  // returns a buffer size;
		operator const p_byte(void) const;  // returns a buffer data pointer (ra);
		operator       p_byte(void)      ;  // returns a buffer data pointer (rw);

	public:
		CRawData& operator+= (const CRawData&);
		CRawData& operator = (const CRawData&);
#if (0) // moved to sys.com.core adapter class;
		CRawData& operator = (const _variant_t&);  // creates from bstr data; *important*: data buffer contains binary string that includes its length;
#endif
		CRawData& operator = (const ::std::vector<byte>&);
		CRawData& operator = (CRawData&&);
	};

	// https://learn.microsoft.com/en-us/windows/win32/memory/enumerating-a-heap >> just for getting to know (%#p);
}}

typedef shared::memory::CRawData  TRawData;

#endif/*_GENERICSTGDATA_H_INCLUDED*/