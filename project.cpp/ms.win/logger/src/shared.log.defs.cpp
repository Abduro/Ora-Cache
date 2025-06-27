/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Jun-2025 at 11:46:24.043, UTC+4, Batumi, Friday;
	This is Shared Log Library Common Definition implementation file.
*/
#include "shared.log.defs.h"

using namespace shared::log;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace log { namespace _impl { void __warning_lnk_4221 (void) {}

	using shared::sys_core::CSyncObject;

	static CSyncObject& Indent_SafeGuardRef(void)
	{
		static CSyncObject crt_sect;
		return crt_sect;
	}
}}}

#define Evt_Log_Safe__Lock() Safe_Lock(_impl::Indent_SafeGuardRef());

/////////////////////////////////////////////////////////////////////////////

CIndentation:: CIndentation (void) : m_main_thread(::GetCurrentThreadId()) {}
CIndentation::~CIndentation (void) {
	m_indents.clear();
	
}

/////////////////////////////////////////////////////////////////////////////

err_code CIndentation::Current (const int nIndent) {
	nIndent;
	Evt_Log_Safe__Lock();

	TIndentMap::iterator it__ = m_indents.find(::GetCurrentThreadId());
	if (it__ != m_indents.end())
	{
		it__->second = nIndent;
		return __s_ok;
	}
	else if (!__create_indent_on_demand(nIndent))
		return __e_no_memory;
	else
		return __s_ok;
}

int CIndentation::Current (void) const {

	Evt_Log_Safe__Lock();

	if (this->Locker().IsLocked())
		return 0;

	TIndentMap::const_iterator it__ = m_indents.find(::GetCurrentThreadId());

	if (it__ != m_indents.end())
		return it__->second;
	else
		return 0;
}

int CIndentation::Decrease(void) {

	Evt_Log_Safe__Lock();

	TIndentMap::iterator it__ = m_indents.find(::GetCurrentThreadId());

	if (it__ != m_indents.end())
	{
		if (it__->second > 0) it__->second--;
		return it__->second;
	}
	else
		return 0;
}

bool CIndentation::Increase(void) {

	Evt_Log_Safe__Lock();

	TIndentMap::iterator it__ = m_indents.find(::GetCurrentThreadId());

	if (it__ != m_indents.end())
	{
		it__->second++;
		return true;
	}
	else
		return __create_indent_on_demand(1);
}

bool CIndentation::IsCtxAvailable (void) const {

	Evt_Log_Safe__Lock();

	TIndentMap::const_iterator it__ = m_indents.find(::GetCurrentThreadId());
	return (it__ != m_indents.end());
}

bool CIndentation::IsMainThreadCtx (void) const {
	return (::GetCurrentThreadId() == m_main_thread);
}

bool CIndentation::Remove (void) {

	Evt_Log_Safe__Lock();
	{
		TIndentMap::iterator it__ = m_indents.find (::GetCurrentThreadId());
		if (it__!=m_indents.end())
			m_indents.erase(it__);
	}
	{
		TLockMap::iterator it__ = m_locker.m_locks.find (::GetCurrentThreadId());
		if (it__!=m_locker.m_locks.end())
			m_locker.m_locks.erase(it__);
	}
	return true;
}

int  CIndentation::Replicate (void) const {

	Evt_Log_Safe__Lock();

	TIndentMap::const_iterator it__ = m_indents.find (m_main_thread);

	if (it__ != m_indents.end())
		return it__->second;
	else
		return 0;
}

_pc_sz CIndentation::ToString (void) const {

	Evt_Log_Safe__Lock();

	const int n_ident = this->Current();

	switch (n_ident)
	{
	case  0:  return _T("");
	case  1:  return _T("  ");
	case  2:  return _T("    ");
	case  3:  return _T("      ");
	case  4:  return _T("        ");
	case  5:  return _T("          ");
	case  6:  return _T("            ");
	case  7:  return _T("              ");
	case  8:  return _T("                ");
	case  9:  return _T("                  ");
	case 10:  return _T("                    ");
	case 11:  return _T("                      ");
	case 12:  return _T("                        ");
	case 13:  return _T("                          ");
	case 14:  return _T("                            ");
	case 15:  return _T("                              ");
	case 16:  return _T("                                ");
	case 17:  return _T("                                  ");
	case 18:  return _T("                                    ");
	}
	return _T("  ");
}

/////////////////////////////////////////////////////////////////////////////

bool CIndentation::__create_indent_on_demand (const int nValue) {
	try
	{
		m_indents.insert(::std::make_pair(::GetCurrentThreadId(), nValue));
	}
	catch (const ::std::bad_alloc&) { ATLASSERT(true == false); return false; }
	return true;
}

/////////////////////////////////////////////////////////////////////////////

CIndentation::CLocker:: CLocker (void) {}
CIndentation::CLocker::~CLocker (void) { m_locks.clear(); }

/////////////////////////////////////////////////////////////////////////////

bool  CIndentation::CLocker::IsLocked (void) const {

	Evt_Log_Safe__Lock();

	TLockMap::const_iterator it__ = this->m_locks.find(::GetCurrentThreadId());

	if (it__ != this->m_locks.end())
		return it__->second;
	else
		return false;
}

bool  CIndentation::CLocker::Lock (void) {

	Evt_Log_Safe__Lock();

	TLockMap::iterator it__ = m_locks.find(::GetCurrentThreadId());

	if (it__ != m_locks.end())
		return (it__->second = true);
	else
		return __create_lock_on_demand();
}

bool  CIndentation::CLocker::Unlock(void) {
	
	Evt_Log_Safe__Lock();

	TLockMap::iterator it__ = m_locks.find(::GetCurrentThreadId());
	if (it__ != m_locks.end())
	{
		it__->second = false;
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////

bool  CIndentation::CLocker::__create_lock_on_demand (void) {
	try {
		m_locks.insert(::std::make_pair(::GetCurrentThreadId(), true));
	}
	catch (::std::bad_alloc&){ ATLASSERT(true==false); return false; }
	return true;
}