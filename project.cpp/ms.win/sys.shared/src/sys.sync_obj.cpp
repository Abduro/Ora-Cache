/*
	Created by Tech_dog (ebontrop@gmail.com) 21-Mar-2014 at 12:20:42pm, GMT+4, Taganrog, Friday;
	This is Platinum project shared generic synchronize object class implementation file.
	-----------------------------------------------------------------------------
	Adopted to File Guardian (thefileguardian.com) on 27-May-2018 at 1:20:35p, UTC+7, Phuket, Rawai, Sunday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:13:54a, UTC+7, Novosibirsk, Friday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 06:39:57.4439814, UTC+7, Novosibirsk, Saturday;
*/
#include "sys.sync_obj.h"

using namespace shared::sys_core;

/////////////////////////////////////////////////////////////////////////////

CSyncObject::CSyncObject(void) // throw() // no XP support
{
#if (0)
	__try
	{
#endif
	// https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializecriticalsection
	//	::InitializeCriticalSection(&m_sec);
	// https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializecriticalsectionandspincount
	const BOOL b_result = ::InitializeCriticalSectionAndSpinCount(&m_sec, 0x400);
	if (b_result == FALSE) {}
#if (0)
	}
	__except(STATUS_NO_MEMORY == ::GetExceptionCode())
	{}
#endif
}

CSyncObject::~CSyncObject(void)
{
	::DeleteCriticalSection(&m_sec);
//	::memset((void*)&m_sec, 0, sizeof(CRITICAL_SECTION));
}

/////////////////////////////////////////////////////////////////////////////

void CSyncObject::Lock (void) const
{
	__try {
		::EnterCriticalSection(&m_sec);
	}
	__except(STATUS_NO_MEMORY == ::GetExceptionCode())
	{}
}

bool CSyncObject::TryLock (void) const {
	return !!::TryEnterCriticalSection(&m_sec);
}

void CSyncObject::Unlock (void) const {
	__try {
		::LeaveCriticalSection(&m_sec);
	}
	__except(STATUS_NO_MEMORY == ::GetExceptionCode())
	{}
}