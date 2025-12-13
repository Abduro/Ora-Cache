#ifndef _SYS_SYNC_OBJ_H_INCLUDED
#define _SYS_SYNC_OBJ_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-May-2012 at 10:29:48pm, GMT+3, Rostov-on-Don, Tuesday;
	This is Shared Lite Library Generic Synchronize Object class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 27-May-2018 at 1:20:24p, UTC+7, Phuket, Rawai, Sunday;
	Adopted to FakeGPS driver project on 13-Dec-2019 at 9:22:22a, UTC+7, Novosibirsk, Friday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 06:32:33.6343384, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h>

namespace shared { namespace sys_core {
	// https://learn.microsoft.com/en-us/windows/win32/sync/critical-section-objects ;
	using crt_section = CRITICAL_SECTION;
	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initializecriticalsectionandspincount ;
	/*
		unfortunately, there is no way to check critical section initialization success:
		...starting with Windows Vista, the InitializeCriticalSectionAndSpinCount function always succeeds, even in low memory situations;
		the truth cannot be always the truth;
	*/
	class CSyncObject {
	public:
		 CSyncObject(void);
		~CSyncObject(void); // learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-deletecriticalsection ;

	public:
		void Lock   (void) const;
		bool TryLock(void) const;
		void Unlock (void) const;

	private:  // non-copyable;
		CSyncObject(const CSyncObject&) = delete;
		CSyncObject& operator= (const CSyncObject&) = delete;
	protected:
		mutable crt_section m_sec;
		volatile bool m_deleted;
	};

	template<typename TLocker>
	class CGenericAutoLocker {
	private:
		TLocker&    m_locker_ref;

	public:
		 CGenericAutoLocker(TLocker& locker_ref) : m_locker_ref(locker_ref) { m_locker_ref.Lock(); }
		~CGenericAutoLocker(void) { m_locker_ref.Unlock(); }

	private: // non-copyable;
		 CGenericAutoLocker(const CGenericAutoLocker&);
		 CGenericAutoLocker& operator= (const CGenericAutoLocker&);
	};

	template<typename TLocker>
	class CGenericAutoLockerEx
	{
	private:
		BOOL        m_locked;
		TLocker&    m_locker_ref;
	public:
		 CGenericAutoLockerEx(TLocker& locker_ref) : m_locker_ref(locker_ref), m_locked(FALSE) { m_locked = m_locker_ref.TryLock(); }
		~CGenericAutoLockerEx(void) {
			if (m_locked)
				m_locker_ref.Unlock();
		}
	public:
		BOOL   IsLocked(void)const { return m_locked; }
	private: // non-copyable;
		CGenericAutoLockerEx(const CGenericAutoLockerEx&);
		CGenericAutoLockerEx& operator= (const CGenericAutoLockerEx&);
	};
}}

typedef shared::sys_core::CSyncObject& TSyncRef;

typedef const shared::sys_core::CGenericAutoLocker<const shared::sys_core::CSyncObject> TAutoLocker;
#define Safe_Lock(cs)    TAutoLocker   tAutoLocker(cs);

typedef const shared::sys_core::CGenericAutoLockerEx<const shared::sys_core::CSyncObject> TAutoLockerEx;
#define Safe_Lock_Ex(cs) TAutoLockerEx tAutoLockerEx(cs); if (!tAutoLockerEx.IsLocked()) return S_OK;

#endif/*_SYS_SYNC_OBJ_H_INCLUDED*/