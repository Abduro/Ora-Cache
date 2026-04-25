#ifndef _RUNNER_TPL_H_INCLUDED
#define _RUNNER_TPL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2026 at , UTC+4, Batumi, Thursday;
	This is Ebo Pack system thread pool wrapper interface declaration file;
*/
#include "runner.bas.h"

namespace shared { namespace runnable { namespace threads { namespace pool { using namespace shared::runnable;
	// https://learn.microsoft.com/en-us/windows/win32/procthread/process-and-thread-functions#thread-pool-functions ;
	using namespace shared::types;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerwaitforsingleobject ;
	class CThreadType {
	public:
		enum e_type : uint32_t {
		/* alias    | element value          | brief description ;
		------------+------------------------+-------------------*/
		  eDefault  = WT_EXECUTEDEFAULT      , // the callback function is queued to a non-I/O worker thread;
		  eIOThread = WT_EXECUTEINIOTHREAD   , // not used; I/O worker threads were removed starting from Vista and Server 2k8;
		  eUIThread = WT_EXECUTEINUITHREAD   , // for use calls to APC: https://learn.microsoft.com/en-us/windows/win32/sync/asynchronous-procedure-calls ;
		  eLongOper = WT_EXECUTELONGFUNCTION , // the callback function can perform a long wait;
		};
		/* the other flags that are available to set heap optimization structure through:
		   https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapsetinformation ;
		   https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-heap_optimize_resources_information ;
		   https://learn.microsoft.com/en-us/windows/win32/memory/memory-management-structures ;
		*/
	};
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/ ;
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-queueuserworkitem ;
	class CThreadPool {
	public:
		template <typename T>
		static int QueueUserWorkItem (void (T::*pfn)(void),  T* pObject, ULONG flags = CThreadType::eLongOper);

		template <typename T>
		static int QueueUserWorkItemEx (void (T::*pfn)(T*), T* pObject, ULONG flags = CThreadType::eLongOper);

	private:
		template <typename T>
		static dword __stdcall ThreadProc(void* _p_context);

		template <typename T>
		static dword __stdcall ThreadProcEx(void* _p_context);
	};
	/* https://learn.microsoft.com/en-us/windows/win32/procthread/thread-pooling ;
	   the excerpt from above article: ...There is no way to cancel a work item after it has been queued...;
	*/
	using CState = TThreadState;
	class CTplRunner : public TThreadBase { typedef TThreadBase TBase;
	public:
		 CTplRunner (void); const CTplRunner (const CTplRunner&) = delete; CTplRunner (CTplRunner&&) = delete;
		~CTplRunner (void);
		
		err_code  Start (void);
		err_code  Stop  (void); // in order to stop the work item thread procedure execution there is only way: to use event and interrupt flag;

	protected:
		virtual void Run_Func (void); // this is default implementation of the thread function;

	private:
		CTplRunner& operator = (const CTplRunner&) = delete; CTplRunner& operator = (CTplRunner&&) = delete;
		
	};
}}}}

#endif/*_RUNNER_TPL_H_INCLUDED*/