#ifndef _SYS_MEM_GLOBAL_H_INCLUDED
#define _SYS_MEM_GLOBAL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Apr-2024 at 22:40:30.1690346, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared global memory allocator interface declaration file;
*/
#include "sys.err.codes.h"
#include "sys.error.h"

#include "shared.string.h"
#include "shared.random.h"  // for guid generation; no reference to sys.com.core is required;
#include "shared.types.h"

#include "sys.mem.handle.h"

namespace shared { namespace memory {

	using namespace shared::types;

	// https://learn.microsoft.com/en-us/windows/win32/memory/comparing-memory-allocation-methods ;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx;

	using cbool   = const bool;
	
	struct shared_data { // this structure does not control the input data life cycle nether check its validity;
	public:
		shared_data (void);
		shared_data (dword _size, const void* p_data = NULL);
		shared_data (const shared_data&);

	public:
		const
		void* p_data; // this member may point to no data, i.e. equals to null or zero;
		dword n_size; // this member must have a value, otherwise a memory block being created is marked as discarded;

		shared_data& operator = (const shared_data&);
		shared_data& operator <<(const void* p_data);
		shared_data& operator <<(const dword n_size);

		bool operator != (const shared_data&) const;
		bool operator == (const shared_data&) const;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalflags ;
	struct shared_flags {
	public:
		enum e_flags : dword { // if take a look at documentation for GlobalAlloc() it very looks like e_movable flag discards e_fixed one;
			e_fixed   = GMEM_FIXED   ,  // allocates fixed memory;
			e_modify  = GMEM_MODIFY  ,  // modifies the attributes of an already-allocated block of memory; neither reallocation nor content change; 
			e_movable = GMEM_MOVEABLE,  // memory blocks are never moved in physical memory, but they can be moved within the default heap ;
			e_to_zero = GMEM_ZEROINIT,  // initializes memory contents to zero ;
		};
	public:
		shared_flags (dword = e_movable | e_to_zero);

	public:
		err_code Get (const handle ) const; // gets flags that are set for memory block (to m_is_set), or GMEM_INVALID_HANDLE if an error occurs;
		bool     Has (const e_flags) const; // checks input flag in the set of assigned flags (m_is_set);
#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all) const;
#endif
	public:
		mutable  dword m_is_set; // the flags that is set for creating a global memory block or those retrieved by calling Get() for handle provided;
	public:
		operator dword (void) const;

		shared_flags& operator = (const shared_flags&);
		shared_flags& operator +=(const e_flags);
		shared_flags& operator -=(const e_flags);
	};
#pragma region __refs_7
	// https://learn.microsoft.com/en-us/windows/win32/memory/global-and-local-functions  ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalalloc ; not recommended and for compatibility only ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalrealloc ;
#pragma endregion
	class CAllocator { // ToDo: Lock() and UnLock() operations are not implemented yet; (done)
	public:
		class CBuilder {
		public:
			 CBuilder (CAllocator&); CBuilder (void) = delete; CBuilder (const CBuilder&) = delete; CBuilder (CBuilder&&) = delete;
			~CBuilder (void);

		public:
			err_code  Create (void) ;          // creates global memory block by specified shared_flags and shared_data;
			err_code  Destroy(void) ;
			TError&   Error  (void) const;
#if defined(_DEBUG)
			CString   Print  (void) const;     // returns the last error of the object;
#endif
			err_code  Update (const shared_data&);  // new size of memory block may be specified with no data pointer; the flag 'modify' keeps data;
			err_code  Update (const shared_flags&); // does nothing, but assigns input flags to those that are currently set; looks like Update() must be called afterwards;

		public:
			CBuilder& operator = (const CBuilder&) = delete;
			CBuilder& operator = (CBuilder&&) = delete;

		private:
			CAllocator& m_alloc;
			CError  m_error;
		};

		class CContent {
		public:
			 CContent (CAllocator&); CContent (void) = delete; CContent (const CContent&) = delete; CContent (CContent&&) = delete;
			~CContent (void);

		public:
			TError&    Error (void) const;
			const bool Is (void) const;            // checks memory data for data pointer assignment, data size and memory buffer validity;
#if defined(_DEBUG)
			CString    Print (const e_print = e_print::e_all) const;
#endif
			CString    Read  (void) const;         // reads content data from memory block; treating bytes as character sequence is not checked;
			err_code   Write (const shared_data&);
			err_code   Write (_pc_sz _p_sz_str );  // writes the input string as byte array; if memory buffer size is not enough, the string is truncated;
			                                       // in case of truncation the string is terminated by zero at place of cutting off;

		public:
			CContent& operator = (const CContent&) = delete;
			CContent& operator = (CContent&&) = delete;

		private:
			CAllocator&    m_alloc;
			mutable CError m_error;

			friend class   CBuilder;
		};
		// lock method requires the memory must have the 'moveable' flag because CreateStreamOnHGlobal() requires moveable;
		/*
		*Important* : if access to data is not correct, i.e. when memory block is movable, but data of block is accessed directly, but not through
		              ::GlobalLock(), destroying this memory by GlobalFree() will throw system error 347 that means 'Invalid Handle';
		*/
		class CLocker {
		public:
			 CLocker (CAllocator&); CLocker (void) = delete; CLocker (const CLocker&) = delete; CLocker (CLocker&&) = delete;
			~CLocker (void) ;

		public:
			TError&  Error (void) const;
			err_code Lock  (void) ;      // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globallock ;
			err_code Unlock(void) ;      // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalunlock ;

			bool Is_locked (void) const; // actually, it is enough to check the pointer value to the memory block been locked;
#if defined(_DEBUG)
			CString  Print (const e_print = e_print::e_all) const;
#endif
			const
			void*    Ptr (void) const;   // gets the pointer to memory block that is retrieved by calling Lock() function;

		public: const void* operator () (void) const;
		        operator const bool (void) const;

		private: CLocker& operator = (const CLocker&) = delete; CLocker& operator = (CLocker&&) = delete;
		private:
			CError m_error;
			CAllocator& m_alloc;
			void*  m_memory;     // the pointer to global memory itself; this pointer can be obtained by calling Lock() function;
		};
	public:
		CAllocator (void); CAllocator (const CAllocator&) = delete; CAllocator (CAllocator&&) = delete;
	   ~CAllocator (void);

	public:
		const
		CBuilder&  Builder (void) const;
		CBuilder&  Builder (void) ;
		const
		CContent&  Content (void) const;
		CContent&  Content (void) ;

		const shared_data&  Data (void) const;
		const shared_flags& Flags(void) const;
		
		bool Data  (const shared_data&) ; // sets shared data before creating the memory block; in case of modifying existing block, Update() must be called; 
		bool Flags (const shared_flags&); // returns true in case flags are changed;
		const
		CLocker&  Locker (void) const;
		CLocker&  Locker (void) ;

		const handle Handle (void) const; // returns a handle to global memory block that is created by this class object;		
		const bool   Is (void) const;     // just checks global memory block handle and nothing more; checking as regular handle is not applicable;

		// https://english.stackexchange.com/questions/611086/refresh-vs-update ;
		TError&  Error (void) const;
		dword    Size  (void) const;      // returns the actual size of memory block in bytes;
		
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
	public:
		CAllocator& operator <<(const shared_data& );  // sets shared data values, Builder().Update() must be called afterwards;
		CAllocator& operator <<(const shared_flags&);  // looks useful before creating global memory block;
	private: CAllocator& operator = (const CAllocator&) = delete;
	private:
		mutable
		CError  m_error ;
		handle  m_handle;       // psuedo-global memory block handle;

		shared_data   m_data ;  // shared data for holding data content in the global memory block of particular size;
		shared_flags  m_flags;  // flags are taking into account by Update();

		CBuilder m_builder;
		CContent m_content;
		CLocker  m_locker ;

		friend class CAllocator::CBuilder;
	//	friend class CAllocator::CContent;
	};

	// https://learn.microsoft.com/en-us/windows/win32/memory/file-mapping ;
	// https://learn.microsoft.com/en-us/windows/win32/memory/using-file-mapping ;
	/*
		*important*: it is supposed the shared data type is assigned to shared named object before creating a memory block;
		             the shared data is used by page and view objects, if necessary to change the shared memory block:
		            (1) close the view;
		            (2) destroy the page;
		            (3) assign required values for shared data;
		            (4) re-create the page and open view again;
	*/
	class CSharedNamed {
	public:
		/*
			Shared memory is not mapped to any disk file, but it is backed by system paging file:
			https://learn.microsoft.com/en-us/windows/win32/memory/sharing-files-and-memory ;
		*/
		class CPage {
		public:
			 CPage (CSharedNamed&); CPage (void) = delete; CPage (const CPage&) = delete; CPage (CPage&&) = delete;
			~CPage (void);

		public:
			err_code Create (void) ;          // creates a system page in virtual address space of shared memory;
			err_code Destroy(void) ;          // destroys a handle of the system page;
			TError&  Error  (void) const;

			const handle Handle (void) const; // returns a handle to the created memory mapped page;
			const bool   Is (void) const;
#if defined(_DEBUG)
			CString   Print (const e_print = e_print::e_all) const;
#endif
		public:
			CPage& operator = (const CPage&) = delete;
			CPage& operator = (CPage&&) = delete;

			operator const handle (void) const;
			operator       handle (void)      ;

		private:
			CSharedNamed& m_named;
			CError m_error ;
			handle m_handle;
		};
		// https://learn.microsoft.com/en-us/windows/win32/memory/creating-a-file-mapping-using-large-pages ;
		class CSecurity {
		public:
			 CSecurity (void); CSecurity (const CSecurity&) = delete; CSecurity (CSecurity&&) = delete;
			~CSecurity (void);

		public:
			CSecurity& operator = (const CSecurity&) = delete;
			CSecurity& operator = (CSecurity&&) = delete;
		};
		// https://learn.microsoft.com/en-us/windows/win32/memory/reading-and-writing-from-a-file-view ;
		// https://learn.microsoft.com/en-us/windows/win32/debug/using-an-exception-handler ;
		class CView {
		public:
			 CView (CSharedNamed&); CView (void) = delete; CView (const CView&) = delete; CView (CView&&) = delete;
			~CView (void);

		public:
			err_code Close (void) ; // closes an access to the internal data memory buffer;
			err_code Open  (void) ; // opens an access to memory page as the byte buffer; the size of data is defined in parent class;
			TError&  Error (void) const;
			const bool Is  (void) const; // returns true in case when an access to data is open, otherwise false; no read/write is checked;

#if defined(_DEBUG)
			CString  Print (const e_print = e_print::e_all) const;
#endif
			CString  Read  (void) ; // treats data buffer as a sequence of the characters;
			err_code Write (void) ; // tries to write data that is stored in parent named object, but not written to view memory block;
			err_code Write (const shared_data& ); // writes input data to this view memory block, the data is not saved in named object;
			err_code Write (_pc_sz _p_sz_string); // writes input string, if its size is greater than view memory one, the string is truncated;

		public:
			CView& operator = (const CView&) = delete;
			CView& operator = (CView&&) = delete;

		private:
			CSharedNamed&  m_named ;
			mutable CError m_error ;
			const byte*    m_p_data;
		};

	public:
		 CSharedNamed (void); CSharedNamed (const CSharedNamed&) = delete; CSharedNamed (CSharedNamed&&) = delete;
		~CSharedNamed (void);

	public:
		const
		shared_data& Data (void) const;
		const bool   Data (const shared_data&); // setting shared data must lead to re-creating CPage and CView objects;

		TError&  Error(void) const;
		_pc_sz   Name (void) const;  // returns a name of this object;
		err_code Name (_pc_sz)    ;  // names this object, if null is provided, the name will be generated; moreover, page object will be destroyed;
		const
		CPage&   Page (void) const;
		CPage&   Page (void)      ;

#if defined (_DEBUG)
		CString Print (void) const;
#endif
		const
		CSecurity& Security (void) const;
		CSecurity& Security (void) ;
		const
		CView&  View (void) const;
		CView&  View (void) ;

		const bool   Is (void) const; // returns true in case if page object is created;

	public:
		CSharedNamed& operator = (const CSharedNamed&) = delete;
		CSharedNamed& operator = (CSharedNamed&&) = delete;
		CSharedNamed& operator <<(const shared_data&);

	public:
		static CString Name_Auto (void); // generates object name in format: Global\\{GUID} ;

	private:
		mutable
		CError   m_error;
		CPage    m_page ;
		CView    m_view ;
		CString  m_name ; // the name of the associating object, must start from prefix 'Global'... ;

		shared_data m_data;
		CSecurity   m_sec ;

		friend class CPage; // for setting error object on create and on destroy operations;
//		friend class CView;
	};
}}

typedef shared::memory::shared_flags          shared_flags;
typedef shared::memory::shared_flags::e_flags t_mem_flags ;

typedef shared::memory::CAllocator TPsuedo;  // uses the GlobalAlloc() and GlobalReAlloc() WinAPI functions;
typedef shared::memory::CAllocator::CBuilder TMemBuilder;
typedef shared::memory::CAllocator::CContent TMemContent;
/*
	the excerpt from https://learn.microsoft.com/en-us/windows/win32/memory/file-mapping :
	'The system creates a file mapping object (also known as a section object)...'
*/
typedef shared::memory::CSharedNamed  TSection;
typedef shared::memory::CSharedNamed::CPage TPage;          // ToDo: new name would be more applicable, such as TMemPage;
typedef shared::memory::CSharedNamed::CSecurity TSecurity;
typedef shared::memory::CSharedNamed::CView TView;          // ToDo: new name would be more applicable, such as TMemView;

#endif/*_SYS_MEM_GLOBAL_H_INCLUDED*/