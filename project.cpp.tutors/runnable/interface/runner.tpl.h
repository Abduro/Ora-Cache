#ifndef _RUNNER_TPL_H_INCLUDED
#define _RUNNER_TPL_H_INCLUDED
/*
 *******************************************************************************
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
 *  This is Ebo Pack shared library system thread pool class declaration file. *
 *-----------------------------------------------------------------------------*
 * Adopted and extended by Tech_dog (ebontrop@gmail.com)                       *
 * on 21-Sep-2015 at 12:48:06am, GMT+7, Phuket, Rawai, Monday;                 *
 *******************************************************************************
*/
#define _HAS_AUTO_PTR_ETC 1
#pragma warning(push)
#pragma warning(disable:4995)
#include <memory>
#pragma warning(pop)

#include "run.event.h"

namespace shared { namespace runnable { using namespace shared::defs;

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
		// the other flags that are available to set heap optimization structure through:
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapsetinformation ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-heap_optimize_resources_information ;
		// https://learn.microsoft.com/en-us/windows/win32/memory/memory-management-structures ;
	};
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/ ;
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-queueuserworkitem ;
	class CThreadPool {
	public:
		template <typename T>
		static int QueueUserWorkItem (void (T::*pfn)(void),  T* pObject, ULONG flags = CThreadType::eLongOper) {
			pObject; flags;
			typedef std::pair<void (T::*)(), T*> CallbackType;
			std::auto_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));
			// https://en.cppreference.com/w/cpp/memory/auto_ptr.html ;
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
			std::auto_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

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

			std::auto_ptr<CallbackType> p(static_cast<CallbackType*>(_p_context));

			(p->second->*p->first)();
			return 0;
		}

		template <typename T>
		static dword __stdcall ThreadProcEx(void* _p_context) {
			_p_context;
			typedef std::pair<void (T::*)(T*), T*> CallbackType;

			std::auto_ptr<CallbackType> ptr_(static_cast<CallbackType*>(_p_context));

			(ptr_->second->*ptr_->first)(ptr_->second);
			return 0;
		}
	};

	class CThreadCrtData {
	public:
		 CThreadCrtData (void); CThreadCrtData (const CThreadCrtData&) = delete; CThreadCrtData (CThreadCrtData&&) = delete;
		~CThreadCrtData (void); // no virtuality of the destructor due to it is assumed no base class will be created through heap memory allocation;

	public:
		TError&   Error (void) const;
		const
		CEvent&   Event (void) const;
		CEvent&   Event (void);

		bool      IsStopped (void) const;
		void      IsStopped (const bool);

	protected:
		volatile 
		bool    m_bStopped;
		CEvent  m_event;
		CError  m_error;

	private:
		CThreadCrtData& operator = (const CThreadCrtData&) = delete; CThreadCrtData& operator = (CThreadCrtData&&) = delete;
	};

	class CThreadState {
	public:
		enum e_state : uint32_t {
			eStopped   =  0x0,
			eError     =  0x1,
			eWorking   =  0x2,
		};
	};

	using shared::sys_core::CError;
	using shared::sys_core::CSyncObject;

	class CThreadBase {
	private:
		virtual void ThreadFunction(void) = 0 ; // derived class must provide thread function implementation;

	protected:
		 CThreadBase (void);
		~CThreadBase (void);

	public:
		TError&  Error (void) const;
		bool     IsComplete (void) const;
		err_code MarkToStop (void);
		err_code Start (void);
		err_code Stop  (void);

	public:
		const bool   IsRunning (void) const;
		const bool   IsValid   (void) const;
		const dword  State     (void) const;

	protected:
		volatile dword  m_state;
		CThreadCrtData  m_crt ;
		CSyncObject     m_lock;
		mutable CError  m_error;
	};
}}

typedef shared::runnable::CThreadCrtData  TThreadCrtData;
typedef shared::runnable::CThreadBase     TThreadBase;

#endif/*_RUNNER_TPL_H_INCLUDED*/