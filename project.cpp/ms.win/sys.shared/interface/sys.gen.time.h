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

#include "sys.err.codes.h"

namespace shared { namespace sys_core {

	using namespace shared::types;

	class CDateTimeFmt {
	public:
		// https://en.wikipedia.org/wiki/ISO_8601 ; https://www.w3.org/TR/NOTE-datetime ;
		// https://help.sumologic.com/docs/send-data/reference-information/time-reference/ ;
		enum iso_8601 : uint32_t {
			e_date = 0x0, // date in UTC: yyyy-mm-dd ;
			e_time = 0x1, // time in UTC: hh:mm:ssZ ;
			e_time_n_offset = 0x2, // time and offset in UTC: hh:mm:ss+/-hh:mm ;
			e_time_complete = 0x3, // time and offset in UTC: hh:mm:ss.sss+/-hh:mm ;
			e_date_n_time   = 0x4, // date and time in UTC: yyyy-mm-ddThh:mm:ssZ ;
			e_date_n_time_offset = 0x5, // date and time with the offset in UTC: yyyy-mm-ddThh:mm:ss+/-hh:mm ;
			e_time_spl_n  = 0x6,   // hh:mm:ss.sss-hh:mm ; the problem with sign output option is there is no output of required number of digits;
			e_time_spl_p  = 0x7,   // hh:mm:ss.sss+hh:mm ; the problem is the same as above;
		};
		 CDateTimeFmt (void) = default; CDateTimeFmt (const CDateTimeFmt&) = delete; CDateTimeFmt (CDateTimeFmt&&) = delete;
		~CDateTimeFmt (void) = default;

	static CString GetPattern (const CDateTimeFmt::iso_8601);

	private:
		CDateTimeFmt& operator = (const CDateTimeFmt&) = delete; CDateTimeFmt& operator = (CDateTimeFmt&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-gettimezoneinformation ;
	class CTimeOffset {
	public:
		static const int16_t _hr_min = -12, _hr_max = +12, _mins_min = -0, _mins_max = +60; // '-0' looks good ;)  
	public:
		struct s_offset {    // this is called 'bias' in MS documentation;
			int16_t _hours;  // acceptable range is [-12...+12]; ToDo: max and min values need to be figured out;
			int16_t _mins ;  // acceptable range is [ 00...+50]; offset of India time zone for example;
		};
	public:
		 CTimeOffset (void); CTimeOffset (const CTimeOffset&) = delete; CTimeOffset (CTimeOffset&&) = delete;
		~CTimeOffset (void) = default;
		// the alias can be retrieved by querying time zone information, but it can be input directly if necessary;
		_pc_sz  Alias (void) const;       // gets alias, brief description of the bios, for example: 'EST';
		bool    Alias (_pc_sz) ;          // sets the alias, returns 'true' if alias value is changed;
		const
		s_offset& Get (void) const;       // perhaps it would be better to call it 'bias';
		s_offset& Get (void);             // returns reference to the offset for direct access to its structure;
		err_code  Set (const int16_t _hours, const int16_t _mins, _pc_sz _p_alias = nullptr); // no thorough check of input values is made;
		err_code  Set (void);             // sets offset data by querying information of time zone that is currently set on a user PC;

		CString   To_string (void) const; // the following pattern is applied by default: -/+hh:mm (%s); the alias is included if it is set;

	private:
		CTimeOffset& operator = (const CTimeOffset&) = delete; CTimeOffset& operator = (CTimeOffset&&) = delete; // not required yet;
		CString   m_alias;
		s_offset  m_bias ;  // just playing with names: 'offset' and 'bias';
	};

	class CTimeBase {
	protected:
		CTimeBase(const bool bTimezone);
	public:
		bool  IsLocal(void)const;
	protected:
		bool  m_b_is_tz; // if true, time/date is local, i.e. takes into account a time zone;
	};

	// https://techcommunity.microsoft.com/t5/azure-developer-community-blog/it-s-2020-is-your-code-ready-for-leap-day/ba-p/1157279
	class CSystemTime : public SYSTEMTIME, public CTimeBase { typedef SYSTEMTIME TBase;
	public:
		CSystemTime (const bool bTimezone = false); // initializes to current UTC time
		CSystemTime (const FILETIME&);              // initializes from file time provided
		CSystemTime (const LARGE_INTEGER&);         // initializes from driver structure;
		CSystemTime (const SYSTEMTIME&);            // initializes to system time provided
		CSystemTime (const time_t&);                // initializes from unix-based time;

		CSystemTime (const CSystemTime&) = delete; CSystemTime (CSystemTime&&) = delete; ~CSystemTime (void) = default;

	public:
		void     Clear   (void);
		int      Compare (const CSystemTime&, const uint16_t _msec_threshold = 0) const; // 0 - equal; -1 - this is later; 1 - this is prior;
		err_code Current (void);

		bool     IsValid (void) const;

		const
		CTimeOffset& Offset (void) const;
		CTimeOffset& Offset (void) ;

		err_code Random (void);
		CString  To_string (const CDateTimeFmt::iso_8601) const;
		err_code ToValue (_pc_sz _p_value); // expects a format like this: yyyy/MM/dd hh:mm:ss.mss;

	public:
		CSystemTime&  operator = (const DATE);
		CSystemTime&  operator = (const FILETIME&);
		CSystemTime&  operator = (const LARGE_INTEGER&);
		CSystemTime&  operator = (const _pc_sz);
		CSystemTime&  operator = (const SYSTEMTIME&);
		CSystemTime&  operator = (const time_t&);
								 
		CSystemTime&  operator = (const CSystemTime&) = delete; CSystemTime& operator = (CSystemTime&&) = delete; // not required yet;

	public:
		operator const  DATE        (void) const;
		operator const  SYSTEMTIME& (void) const;
		operator        SYSTEMTIME& (void) ;
		operator const LPSYSTEMTIME (void) ;
		operator       LPSYSTEMTIME (void) ;

	private:
		CTimeOffset   m_offset;
	};

	/////////////////////////////////////////////////////////////////////////////
	// this is simplified wrapper of system time structure;
	class CDateTime {
	public:
		CDateTime(void); CDateTime (const CDateTime&&) = delete; ~CDateTime (void) = default;
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
		CDateTime&   operator = (const CDateTime&); CDateTime& operator = (CDateTime&&) = delete;

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
	private:
		SYSTEMTIME    m_time;
	};

	/////////////////////////////////////////////////////////////////////////////
	
	bool operator == (const CDateTime&, const CDateTime&);
	bool operator != (const CDateTime&, const CDateTime&);

	/////////////////////////////////////////////////////////////////////////////

	class CFileTime : public CTimeBase { typedef CTimeBase TBase;
	public:
		CFileTime (const bool bTimezone = false);
		CFileTime (const FILETIME&);
		CFileTime (const LARGE_INTEGER&);
		CFileTime (const SYSTEMTIME&);
		CFileTime (const time_t&);
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
		CString   To_string(const CDateTimeFmt::iso_8601) const; // formats file time as string;

	private:
		FILETIME  m_ftime; // https://msdn.microsoft.com/en-us/library/221w8e43.aspx
	};

	class CUnixTime : public CTimeBase { typedef CTimeBase TBase;
		enum _e {
			eFormattedBufferSize = 30,
		};
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
	private:
		time_t   m_time;
	};
}}

#endif/*_SHAREDDATETIME_H_24C438F9_D1CA_4541_A02C_9D4C52874657_INCLUDED*/