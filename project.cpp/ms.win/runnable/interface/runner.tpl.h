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
 *                                                                             *
 *-----------------------------------------------------------------------------*
 *  This is Ebo Pack shared library system thread pool class declaration file. *
 *-----------------------------------------------------------------------------*
 *                                                                             *
 * Adopted and extended by Tech_dog (ebontrop@gmail.com)                       *
 * on 21-Sep-2015 at 12:48:06am, GMT+7, Phuket, Rawai, Monday;                 *
 *-----------------------------------------------------------------------------*
 *                                                                             *
 *******************************************************************************
*/
#define _HAS_AUTO_PTR_ETC 1
#pragma warning(push)
#pragma warning(disable:4995)
#include <memory>
#pragma warning(pop)

#include "sys.sync_obj.h"
#include "sys.error.h"

#include "shared.types.h"

namespace shared { namespace runnable {

	using namespace shared::types;

	class CThreadType {
	public:
		enum { // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerwaitforsingleobject ;
			eDefault  = WT_EXECUTEDEFAULT     ,
			eIOThread = WT_EXECUTEINIOTHREAD  ,
			eUIThread = WT_EXECUTEINUITHREAD  ,
			eLongOper = WT_EXECUTELONGFUNCTION,
		};
	};
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/ ;
	// https://docs.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-queueuserworkitem ;
	class CThreadPool {
	public:
		template <typename T>
		static BOOL QueueUserWorkItem(
					void (T::*pfn)(void), 
					T* pObject,
					ULONG flags = CThreadType::eLongOper
				)
		{
			typedef std::pair<void (T::*)(), T*> CallbackType;
			std::auto_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

			if (::QueueUserWorkItem(ThreadProc<T>, ptr_.get(), flags))
			{
				ptr_.release();
				return true;
			}
			else
				return false;
		}

		template <typename T>
		static BOOL QueueUserWorkItemEx(
					void (T::*pfn)(T*),
					T* pObject,
					ULONG flags = CThreadType::eLongOper
				)
		{
			typedef std::pair<void (T::*)(T*), T*> CallbackType;
			std::auto_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

			if (::QueueUserWorkItem(ThreadProcEx<T>, ptr_.get(), flags))
			{
				ptr_.release();
				return true;
			}
			else
				return false;
		}
	private:
		template <typename T>
		static DWORD __stdcall ThreadProc(PVOID context)
		{
			typedef std::pair<void (T::*)(), T*> CallbackType;

			std::auto_ptr<CallbackType> p(static_cast<CallbackType*>(context));

			(p->second->*p->first)();
			return 0;
		}

		template <typename T>
		static DWORD __stdcall ThreadProcEx(PVOID context)
		{
			typedef std::pair<void (T::*)(T*), T*> CallbackType;

			std::auto_ptr<CallbackType> ptr_(static_cast<CallbackType*>(context));

			(ptr_->second->*ptr_->first)(ptr_->second);
			return 0;
		}
	};

	class CThreadCrtDataBase {
	protected:
		volatile 
		bool           m_bStopped;
		HANDLE         m_hStopEvent;
	public:
		CThreadCrtDataBase(void);
		virtual ~CThreadCrtDataBase(void);
	public:
		const
		HANDLE&        EventObject(void) const;
		HANDLE&        EventObject(void);
		HRESULT        Initialize (void);
		bool           IsStopped  (void) const;
		void           IsStopped  (const bool);
		bool           IsValid    (void) const;  // checks stop event for valid value;
		HRESULT        Terminate  (void);
	private:
		CThreadCrtDataBase(const CThreadCrtDataBase&);
		CThreadCrtDataBase& operator= (const CThreadCrtDataBase&);
	};

	class CThreadCrtData : public CThreadCrtDataBase {
	                      typedef CThreadCrtDataBase TBase;
	public:
		 CThreadCrtData(void);
		~CThreadCrtData(void);
	};

	class CThreadState {
	public:
		enum {
			eStopped   =  0x0,
			eError     =  0x1,
			eWorking   =  0x2,
		};
	};

	using shared::sys_core::CError;
	using shared::sys_core::CSyncObject;

	class CThreadBase {
	protected:
		CThreadCrtData  m_crt ;
		CSyncObject     m_lock;

	protected:
		volatile
		DWORD           m_state;

	protected:
		 CThreadBase(void);
		~CThreadBase(void);
	public:
		virtual bool    IsComplete(void)const;
		virtual HRESULT MarkToStop(void);
		virtual HRESULT Start(void);
		virtual HRESULT Stop (void);

	private:
		virtual void    ThreadFunction(void) = 0 ; // derived class must provide thread function implementation;

	public:
		const bool      IsRunning(void) const;
		const bool      IsValid  (void) const;
		const DWORD     State    (void) const;
	};
}}

typedef shared::runnable::CThreadCrtData  TThreadCrtData;
typedef shared::runnable::CThreadBase     TThreadBase;

#endif/*_RUNNER_TPL_H_INCLUDED*/