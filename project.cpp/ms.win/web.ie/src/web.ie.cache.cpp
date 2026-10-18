/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Oct-2026 at 09:55:34.192, UTC+4, Batumi, Sunday;
	This is Ebo Pack IE 11 IWebBrowser2 control data cache wrapper interface implementation file;
*/
#include "web.ie.cache.h"
#include <wininet.h>

using namespace ::ex_ui::web::IE;

namespace ex_ui { namespace web { namespace IE { namespace _impl {

	class CSession {
	public:
		CSession (void) = default; CSession (const CSession&) = delete; CSession (CSession&&) = delete; ~CSession (void) = default;

		err_code End (void) { // clears out the current session and cookie states;
			// https://learn.microsoft.com/en-us/windows/win32/wininet/option-flags ;
			// https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetsetoptionw ;
			// tells the WinINet engine to finalize current cookie transactions and drop memory cache ;
			return (!::InternetSetOption(NULL, INTERNET_OPTION_END_BROWSER_SESSION, NULL, 0) ? __LastErrToHresult() : __s_ok);
		}

	private:
		CSession& operator = (const CSession&) = delete; CSession& operator = (CSession&&) = delete;
	};

}}}} using namespace _impl;

#pragma region cls::CCache{}

CCache::CCache (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CCache::Clear (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CSession().End();

	dword_t dwEntrySize = 0;

	// https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-findfirsturlcacheentryW ;
	::FindFirstUrlCacheEntry(0, 0, &dwEntrySize);
	if (this->m_error.Last() != (err_code) TErrCodes::eData::eBuffer)
		return this->Error();

	CHeapPtr<INTERNET_CACHE_ENTRY_INFO> spCacheEntry;
	if (!spCacheEntry.AllocateBytes(dwEntrySize))
		return this->m_error <<__e_no_memory;

	spCacheEntry->dwStructSize = dwEntrySize;

	handle_t hCacheDir = ::FindFirstUrlCacheEntry(NULL, spCacheEntry, &dwEntrySize); // the size of the cache entry is already retrieved;
	if (nullptr == hCacheDir)
		return this->m_error.Last();

	bool bMoreItems = true;
	while (bMoreItems) {
		if (spCacheEntry->lpszSourceUrlName) {
			// https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-deleteurlcacheentry ;
			if (false == !!::DeleteUrlCacheEntry(spCacheEntry->lpszSourceUrlName)) {
				this->m_error.Last(); break;
			}
		}
		dword_t dwNextEntrySize = 0;
		// https://learn.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-findnexturlcacheentryW ;
		if (false == !!::FindNextUrlCacheEntry(hCacheDir, 0, &dwNextEntrySize)) {
			this->m_error.Last();
			if (this->Error() != (err_code) TErrCodes::eData::eBuffer) {
				break;
			}
			if (!spCacheEntry.ReallocateBytes(dwNextEntrySize)) {
				this->m_error <<__e_no_memory; break;
			}
		}
		bMoreItems = ::FindNextUrlCacheEntry(hCacheDir, spCacheEntry, &dwNextEntrySize);
	}
	if (false == !!::FindCloseUrlCache(hCacheDir)) this->m_error.Last(); else hCacheDir = nullptr;

	return this->Error();
}

err_code CCache::Clear_ex (const dword_t _flags) {
	_flags;
	this->m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecuteW ;

	static _pc_sz p_cmd_pat = _T("inetcpl.cpl,ClearMyTracksByProcess %u");

	int32_t n_result = static_cast<int32_t>(reinterpret_cast<uintptr_t>(
			::ShellExecute(0, _T("open"), _T("rundll32.exe"), TString().Format(p_cmd_pat, _flags), 0, SW_HIDE)
		)); // int32_t << uintptr << void* (HINSTANCE);
	if (33 > n_result)
		this->m_error.Last();

	return this->Error();
}

TError& CCache::Error (void) const { return this->m_error; }


#pragma endregion