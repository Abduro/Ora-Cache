#ifndef _SHAREDLOGCOMMONDEFS_H_INCLUDED
#define _SHAREDLOGCOMMONDEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com)) on 21-Aug-2013 at 2:26:14am, GMT+3, Taganrog, Wednesday;
	This is PulsePay Shared Common Event Logger class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Platinum Payroll project on 19-Mar-2014 at 7:36:14am, GMT+3, Taganrog, Wednesday;
	Extended by Tech_dog (ebontrop@gmail.com) on 11-Jul-2015 at 12:32:18pm, GMT+7, Phuket, Rawai, Saturday;
	Adopted to Ebo Pack renderer project on 27-Jun-2025 at 09:45:32.705, UTC+4, Batumi, Friday;
*/
#include <atlbase.h>
#include <map>

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"
#include "sys.error.h"
#include "sys.sync_obj.h"

#include "sys.mem.heap.h"
#include "com.def.base.h"

namespace shared { namespace log {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	typedef dword thread_id;

	class eMsgType {
	public:
		enum _e : uint32_t {
			eInfo    = 0,
			eWarning = 1,
			eError   = 2,
			eWaiting = 3,
		};
	};

	class eLogOption {
	public:
		enum _e : uint32_t {
			eNone       = 0x0,
			eUseJournal = 0x1, // system event journal;
			eUseFile    = 0x2  // file logger;
		};
	};

	interface ILogGenericCallback
	{
		virtual VOID ILog_OnGenericEvent(const eMsgType::_e, CAtlString _evt_details) PURE;
	};

	// it is assumed that the first call to the logger is done from the main thread, for example, from the main function ;
	// this class is thread safe;
	class CIndentation {

		typedef ::std::map<thread_id, int > TIndentMap;
		typedef ::std::map<thread_id, bool> TLockMap  ; // the key is the thread identifier, the value indicates the thread is locked or not;

	public:
		// the locker operates by using ::GetCurrentThreadId();
		class CLocker { friend class CIndentation;
		private:
			 CLocker (void); CLocker (const CLocker&) = delete; CLocker (CLocker&&) = delete;
			~CLocker (void);

		public:
			bool  IsLocked (void) const; // gets current thread Id and checks the lock map for getting the lock status;
			bool  Lock     (void) ;      // disallows to use indentation;
			bool  Unlock   (void) ;      // allows to use indentation; 

		private:
			CLocker& operator = (const CLocker&) = delete;
			CLocker& operator = (CLocker&&) = delete;

			bool __create_lock_on_demand (void);

		private:
			TLockMap  m_locks;
		};
	public:
		 CIndentation (void); CIndentation (const CIndentation&) = delete; CIndentation (CIndentation&&) = delete;
		~CIndentation (void);

	public:
		err_code Current (const int nIndent);
		int      Current (void) const;

		int   Decrease(void) ;
		bool  Increase(void) ;

		bool  IsCtxAvailable  (void) const;
		bool  IsMainThreadCtx (void) const;

		const
		CLocker& Locker (void) const;
		CLocker& Locker (void) ;

		bool  Remove (void) ;
		int   Replicate(void) const; // gets the current indent from main thread ;

		_pc_sz ToString (void) const;

	private:
		bool __create_indent_on_demand (const int nValue = 0);

	private:
		CIndentation& operator = (const CIndentation&) = delete;
		CIndentation& operator = (CIndentation&&) = delete;

	private:
		TIndentMap   m_indents;
		thread_id    m_main_thread;
		CLocker      m_locker;
	};
}}

#endif/*_SHAREDLOGCOMMONDEFS_H_INCLUDED*/