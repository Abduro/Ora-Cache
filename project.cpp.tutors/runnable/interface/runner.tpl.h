#ifndef _RUNNER_TPL_H_INCLUDED
#define _RUNNER_TPL_H_INCLUDED

/******************************************************************************\
 * Copyright (c) Microsoft Corporation.                                        *
 *                                                                             *
 * The class was designed by Kenny Kerr. It provides the ability to queue      *
 * simple member functions of a class to the Windows thread pool.              *
 *                                                                             *
 * Kenny Kerr spends most of his time designing and building distributed       *
 * applications for the Microsoft Windows platform. He also has a particular   *
 * passion for C++ and security programming. Reach Kenny at                    *
 * http://weblogs.asp.net/kennykerr/ or visit his Web site:                    *
 * http://www.kennyandkarin.com/Kenny/.                                        *
 *                                                                             *
 * This source is subject to the Microsoft Public License.                     *
 * See http://www.microsoft.com/en-us/openness/resources/licenses.aspx#MPL.    *
 * All other rights reserved.                                                  *
 *                                                                             *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, *
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED       *
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.      *
 *-----------------------------------------------------------------------------*
 * This is Ebo Pack shared library system thread pool class declaration file.  *
 *-----------------------------------------------------------------------------*
 * Adopted and extended by Tech_dog (ebontrop@gmail.com)                       *
 * on 21-Sep-2015 at 12:48:06am, GMT+7, Phuket, Rawai, Monday;                 *
\******************************************************************************/

#include "run.event.h"
#if (0)
// https://stackoverflow.com/questions/48882439/how-to-restore-auto-ptr-in-visual-studio-c17 ;
// https://stackoverflow.com/questions/3451099/stdauto-ptr-to-stdunique-ptr ;
#endif
namespace shared { namespace runnable { namespace threads { using namespace shared::defs; using namespace shared::runnable;

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
		static int QueueUserWorkItem (void (T::*pfn)(void),  T* pObject, ULONG flags = CThreadType::eLongOper) {
			pObject; flags;
			typedef std::pair<void (T::*)(), T*> CallbackType;
			::std::unique_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

			if (::QueueUserWorkItem(ThreadProc<T>, ptr_.get(), flags)) {
				ptr_.release(); // the ownership of the encapsulated pointer is given to system procedure;
				return true;
			} else
				return false;
		}

		template <typename T>
		static int QueueUserWorkItemEx (void (T::*pfn)(T*), T* pObject, ULONG flags = CThreadType::eLongOper) {
			pObject; flags;
			typedef std::pair<void (T::*)(T*), T*> CallbackType;
			::std::unique_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

			if (::QueueUserWorkItem(ThreadProcEx<T>, ptr_.get(), flags)) {
				ptr_.release(); // the ownership of the encapsulated pointer is given to system procedure;
				return true;
			}
			else
				return false;
		}
	private:
		template <typename T>
		static dword __stdcall ThreadProc(void* _p_context) {
			_p_context;
			typedef std::pair<void (T::*)(), T*> CallbackType;

			::std::unique_ptr<CallbackType> ptr_(static_cast<CallbackType*>(_p_context));

			(ptr_->second->*ptr_->first)();
			return 0;
		}

		template <typename T>
		static dword __stdcall ThreadProcEx(void* _p_context) {
			_p_context;
			typedef std::pair<void (T::*)(T*), T*> CallbackType;

			::std::unique_ptr<CallbackType> ptr_(static_cast<CallbackType*>(_p_context));

			(ptr_->second->*ptr_->first)(ptr_->second);
			return 0;
		}
	};

	using CError  = shared::sys_core::CError;
	using CLocker = shared::sys_core::CSyncObject;

	class CState {
	public:
		 enum e_state : uint32_t { eStopped = 0x0, eCompleted, eError, eWorking };
		 CState (void); CState (const CState&) = delete; CState (CState&&) = delete;
		~CState (void) = default;

		TError&  Error (void) const;
		const
		CEvent&  Event (void) const;
		CEvent&  Event (void);

		e_state  Get (void) const;      // returns currently set state value;
		bool     Set (const e_state);   // returns 'true' in case of state value change; this is direct set of the value;

		bool Is_completed (void) const; // calls the event object and changing the current state value appropriately;
		bool Is_error     (void) const; // returns result in accordance with current state of the error object;
		bool Is_running   (void) const;
		bool Is_stopped   (void) const;

		bool Is_valid (void) const;     // checks internal event object and own error state;

		CLocker& Locker (void);

		operator uint32_t (void) const;
		const
		CEvent&  operator ()(void) const;
		CEvent&  operator ()(void) ;

		CEvent&  operator <<(const e_state);
		CEvent&  operator <<(const TError&); // sets current state value to e_state::eError, the error object is updated too;
		CEvent&  operator >>(e_state& _out); // assigns current state value to input variable reference;

	private:
		CState& operator = (const CState&) = delete; CState& operator = (CState&&) = delete;
		// https://stackoverflow.com/questions/2484980/why-is-volatile-not-considered-useful-in-multithreaded-c-or-c-programming ;
		mutable CEvent  m_event;
		mutable CError  m_error;
		mutable e_state m_state;
		mutable CLocker m_lock ;
	};

	class CBase {
	public:
		 CBase (void); const CBase (const CBase&) = delete; CBase (CBase&&) = delete;
		~CBase (void);

		TError&   Error (void) const;

		bool   Is_valid (void) const; // checks error objects: its own and state object;
		
		err_code  Start (void);
		err_code  Stop  (void);
		const
		CState&   State (void) const;
		CState&   State (void);

		const
		CState& operator ()(void) const;
		CState& operator ()(void) ;

	protected:
		mutable
		CError  m_error;
		CState  m_state;
		
	private:
		CBase& operator =  (const CBase&) = delete; CBase& operator = (CBase&&) = delete;
		virtual void ThreadFunction (void) = 0 ; // derived class must provide thread function implementation;
	};
}}}

typedef shared::runnable::threads::CBase   TThreadBase;
typedef shared::runnable::threads::CState  TThreadState;

#endif/*_RUNNER_TPL_H_INCLUDED*/