#ifndef _SHAREDDATETIME_H_INCLUDED
#define _SHAREDDATETIME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) at 01-Dec-2008 09:12:10pm, GMT+3, Rostov-on-Don, Monday;
	This is a date & time data wrapper interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to File Guardian project on 10-Jan-2016 at 2:41:14am, GMT+7, Phuket, Rawai, Sunday; (thefileguardian.com)
	Adopted to FakeGPS driver project on 18-Apr-2020 at 3:40:47a, UTC+7, Novosibirsk, Saturday;
	Adopted to Geometry Curve project on 18-Feb-2024 at 14:25:42.7173072, UTC+7, Novosibirsk, Sunday;
*/
#include <atlbase.h>
#include <atlstr.h>
namespace std {
	#include <time.h>
}
#include "shared.preproc.h"
#include "shared.str.ext.h"

namespace shared { namespace sys_core {

	using namespace shared::types;


	class CDateTimeStyle {
	public:
		enum _e{
			eUnspecified = 0,
			eUtcTimeZone = 1,
			eNoMillisecs = 2,
		};
	};

	class CDateBias {
	private:
		LONG  m_bias_hr; // hour(s)
		LONG  m_bias_mn; // minute(s)
		LONG  m_bias;    // standard type bias;
	public:
		CDateBias(void);
	public:
		HRESULT    Initialize(void);
	public:
		const LONG Bias   (void)const;
		const LONG Hours  (void)const;
		const bool IsBeforeUtc(void)const;
		const LONG Minutes(void)const;
	};

	class CTimeBase {

	protected:
		bool       m_b_is_tz;                      // if true, time/date is local, i.e. takes into account a time zone;
	protected:
		CTimeBase(const bool bTimezone);
	public:
		bool       IsLocal(void)const;
	};
	// https://techcommunity.microsoft.com/t5/azure-developer-community-blog/it-s-2020-is-your-code-ready-for-leap-day/ba-p/1157279
	class CSystemTime : public SYSTEMTIME, public CTimeBase {
	                   typedef SYSTEMTIME  TBase;
	public:
		CSystemTime(const bool bTimezone = false); // initializes to current UTC time
		CSystemTime(const FILETIME&);              // initializes from file time provided
		CSystemTime(const LARGE_INTEGER&);         // initializes from driver structure;
		CSystemTime(const SYSTEMTIME&);            // initializes to system time provided
		CSystemTime(const time_t&);                // initializes from unix-based time;
	public:
		void       Clear   (void);
		INT        Compare (const CSystemTime&, const WORD _msec_threshold = 0) const; // 0 - equal; -1 - this is later; 1 - this is prior;
		HRESULT    Current (void);
		CString    DefaultFormatValue(void)const;
		bool       IsValid (void)const;
		HRESULT    Random  (void);
		HRESULT    ToString(CString& _result, const DWORD _style = CDateTimeStyle::eUnspecified) const;
		HRESULT    ToValue (LPCTSTR _lp_sz_value); // expects a format like this: yyyy/MM/dd hh:mm:ss.mss;

	public:
		CSystemTime&    operator=(const DATE);
		CSystemTime&    operator=(const FILETIME&);
		CSystemTime&    operator=(const LARGE_INTEGER&);
		CSystemTime&    operator=(const LPCTSTR);
		CSystemTime&    operator=(const SYSTEMTIME&);
		CSystemTime&    operator=(const time_t&);
	public:
		operator const  DATE       (void)const;
		operator const  SYSTEMTIME&(void)const;
		operator        SYSTEMTIME&(void)     ;
		operator const LPSYSTEMTIME(void)     ;
		operator       LPSYSTEMTIME(void)     ;
	public:
		static LPCTSTR  GetDefaultFormat(const bool bScanPattern, const DWORD _style = CDateTimeStyle::eNoMillisecs);
	};

	/////////////////////////////////////////////////////////////////////////////
	// this is simplified wrapper of system time structure;
	class CDateTime
	{
	private:
		SYSTEMTIME    m_time;

	public:
		CDateTime(void);
		CDateTime(const CDateTime& );
		CDateTime(const time_t);                 // initializes from unix time
		CDateTime(const SYSTEMTIME&);
	public:
		SYSTEMTIME   GetCurrent   (void) const;
		CString      GetDate      (void) const;
		CString      GetTimeAsUnix(void) const; // YYYY-MM-DDThh:mm:ss.sTZD (eg 1997-07-16T19:20:30.45+01:00)
		CString      GetUnixEpoch (void) const; // YYYY-MM-DD hh:mm:ss.s    (eg 1997-07-16 19:20:30.45)
		CString      GetTime      (void) const;
		void         Refresh      (void);       // resets to current local time;
#if defined(_DEBUG)
		CString Print (void) const;
#endif
	public:
		CDateTime&   operator=    (const CDateTime&);

	public:
		static INT   Compare(
		                const FILETIME& _t0,
		                const FILETIME& _t1,
		                const WORD _msec_threshold = 0
		            ); // 0 - equal; -1 - _t0 later; 1 - _t1 later
		static INT   Compare(
		                const SYSTEMTIME& _t0,
		                const SYSTEMTIME& _t1,
		                const WORD _msec_threshold = 0
		            ); // 0 - equal; -1 - _t0 later; 1 - _t1 later
		static time_t FileTimeToUnix  (const FILETIME&  );
		static time_t SystemTimeToUnix(const SYSTEMTIME&);
	};

	/////////////////////////////////////////////////////////////////////////////
	
	bool operator == (const CDateTime&, const CDateTime&);
	bool operator != (const CDateTime&, const CDateTime&);

	/////////////////////////////////////////////////////////////////////////////

	class CFileTime : public CTimeBase
	{
		typedef CTimeBase TBase;
		// https://msdn.microsoft.com/en-us/library/221w8e43.aspx
	private:
		FILETIME       m_ftime;
	public:
		CFileTime(const bool bTimezone = false);
		CFileTime(const FILETIME&);
		CFileTime(const LARGE_INTEGER&);
		CFileTime(const SYSTEMTIME&);
		CFileTime(const time_t&);
	public:
		CFileTime& operator=(const FILETIME&);
		CFileTime& operator=(const LARGE_INTEGER&);
		CFileTime& operator=(const SYSTEMTIME&);
		CFileTime& operator=(const time_t&);
	public:
		bool operator== (const CFileTime&);
		bool operator!= (const CFileTime&);
		bool operator<  (const CFileTime&);
		bool operator>  (const CFileTime&);
	public:
		HRESULT   Clear(void);
		INT       Compare(
		                const FILETIME& _ft,
		                const WORD _msec_threshold = 0
		          ); // 0 - equal; -1 - _t0 later; 1 - _t1 later
		HRESULT   ToString(CString& _result) const; // formats file time as string;
	};

	class CUnixTime : public CTimeBase {
		typedef CTimeBase TBase;
		enum _e {
			eFormattedBufferSize = 30,
		};
	private:
		time_t       m_time;
	public:
		CUnixTime(const bool bTimezone = false);
		CUnixTime(const time_t&, const bool bTimezone = false);
	public:
		void         Clear   (void);
		time_t&      Current (void);
		INT          GapWith (const time_t&)const;
		INT          GapWithCurrent(void) const;
		bool         IsNull  (void)const;
		bool         IsValid (void)const;
		HRESULT      ToString(const bool bFormatted, CString& _result) const; // YYYY-MM-DDThh:mm:ss.sTZD (eg 1997-07-16T19:20:30.45+01:00)
	public:
		CUnixTime&   operator=(const DATE);
		CUnixTime&   operator=(const CSystemTime&);
		CUnixTime&   operator=(const FILETIME&);
		CUnixTime&   operator=(const LARGE_INTEGER&);
		CUnixTime&   operator=(const SYSTEMTIME&);
		CUnixTime&   operator=(const time_t&);
	public:
		bool operator== (const CUnixTime&) const;
		bool operator!= (const CUnixTime&) const;
		bool operator<  (const CUnixTime&) const;
		bool operator>  (const CUnixTime&) const;
	public:
		operator const  DATE   (void)const;
		operator const  time_t&(void)const;
		operator        time_t&(void)     ;
		operator const  time_t*(void)     ;
		operator        time_t*(void)     ;
	};
}}

#endif/*_SHAREDDATETIME_H_24C438F9_D1CA_4541_A02C_9D4C52874657_INCLUDED*/