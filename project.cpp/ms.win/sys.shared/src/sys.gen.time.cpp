/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jan-2016 at 2:49:52am, GMT+7, Phuket, Rawai, Sunday;
	This is (thefileguardian.com) shared lite library date & time interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to FakeGPS driver project on 18-Apr-2020 at 4:35:35a, UTC+7, Novosibirsk, Saturday;
	Adopted to Geometry Curve project on 18-Feb-2024 at 14:29:18.2169222, UTC+7, Novosibirsk, Sunday;
*/
#include "sys.gen.time.h"

using namespace shared::sys_core;
/////////////////////////////////////////////////////////////////////////////

CDateBias::CDateBias(void) : m_bias_hr(0), m_bias_mn(0), m_bias(0) {}

/////////////////////////////////////////////////////////////////////////////

HRESULT    CDateBias::Initialize(void)
{
	HRESULT hr_ = S_OK;
	TIME_ZONE_INFORMATION tzi = {0};
	const DWORD dwType = ::GetTimeZoneInformation(&tzi);

	switch (dwType)
	{
	case TIME_ZONE_ID_UNKNOWN : // no daylight;
	case TIME_ZONE_ID_STANDARD: // no daylight;
	case TIME_ZONE_ID_DAYLIGHT:
		break;
	default:
		hr_ = HRESULT_FROM_WIN32(::GetLastError());
		return hr_;
	}

	m_bias = tzi.Bias;

	m_bias_hr = abs(m_bias) / 60;
	m_bias_mn = abs(m_bias) % 60;
	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

const LONG CDateBias::Bias (void)const { return m_bias; }
const LONG CDateBias::Hours(void)const { return m_bias_hr; }
const bool CDateBias::IsBeforeUtc(void)const { return (0 < m_bias); }
const LONG CDateBias::Minutes(void)const     { return  m_bias_mn; }
/////////////////////////////////////////////////////////////////////////////

CTimeBase::CTimeBase(const bool bTimezone) : m_b_is_tz(bTimezone) {}

/////////////////////////////////////////////////////////////////////////////

bool     CTimeBase::IsLocal(void)const { return m_b_is_tz; }

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace _impl
{
	bool CSystemTime_IsEqual(const SYSTEMTIME& _left, const SYSTEMTIME& _right, const WORD _msec_threshold)
	{
		if (_left.wYear   != _right.wYear  ) return false;
		if (_left.wMonth  != _right.wMonth ) return false;
		if (_left.wDay    != _right.wDay   ) return false;
		if (_left.wHour   != _right.wHour  ) return false;
		if (_left.wMinute != _right.wMinute) return false;
		if (_left.wSecond != _right.wSecond) return false;
		if (_left.wMilliseconds > _right.wMilliseconds
		 && _left.wMilliseconds - _right.wMilliseconds > _msec_threshold)
				return false;
		if (_right.wMilliseconds > _left.wMilliseconds
		 && _right.wMilliseconds - _left.wMilliseconds > _msec_threshold)
				return false;

		return true;
	}

	bool CSystemTime_LeftAfterRight(const SYSTEMTIME& _left, const SYSTEMTIME& _right, const WORD _msec_threshold)
	{
		if (_left.wYear   >  _right.wYear) return true;
		if (_left.wYear   == _right.wYear   && _left.wMonth  > _right.wMonth ) return true;
		if (_left.wMonth  == _right.wMonth  && _left.wDay    > _right.wDay   ) return true;
		if (_left.wDay    == _right.wDay    && _left.wHour   > _right.wHour  ) return true;
		if (_left.wHour   == _right.wHour   && _left.wMinute > _right.wMinute) return true;
		if (_left.wMinute == _right.wMinute && _left.wSecond > _right.wSecond) return true;

		if (_left.wMilliseconds >= _right.wMilliseconds
		 && _left.wMilliseconds  - _right.wMilliseconds <= _msec_threshold)
			return true;

		if (_right.wMilliseconds  > _left.wMilliseconds
		 && _right.wMilliseconds  - _left.wMilliseconds <= _msec_threshold)
			return true;

		return false;
	}

	bool CSystemTime_LeftLaterRight(const SYSTEMTIME& _left, const SYSTEMTIME& _right, const WORD _msec_threshold) {
		return CSystemTime_LeftAfterRight(_left, _right, _msec_threshold);
	}

	WORD CSystemTime_RandomWord(const WORD _low, const WORD _high) {

		static bool bInited = false;
		if (bInited == false) {
			bInited  = true; ::srand((unsigned)::std::time(NULL));
		}

		WORD word_ = 0;
		do { word_ = (WORD)(::rand() % (_high)); } while (_low > word_ || word_ > _high);

		return word_;
	}
}}}
using namespace shared::sys_core::_impl;
/////////////////////////////////////////////////////////////////////////////

CSystemTime::CSystemTime(const bool bTimezone) : CTimeBase(bTimezone) {
	::memset((SYSTEMTIME*)this, 0, sizeof(SYSTEMTIME)); // TODO: it's obviously to use this->Clear();
}

CSystemTime::CSystemTime(const FILETIME& _ft)     : CTimeBase(true) { *this = _ft;  }
CSystemTime::CSystemTime(const LARGE_INTEGER& _li): CTimeBase(true) { *this = _li;  }
CSystemTime::CSystemTime(const SYSTEMTIME& _tm)   : CTimeBase(true) { *this = _tm;  }
CSystemTime::CSystemTime(const time_t& _tm)       : CTimeBase(true) { *this = _tm;  }

/////////////////////////////////////////////////////////////////////////////

void     CSystemTime::Clear  (void) { ::memset((SYSTEMTIME*)this, 0, sizeof(SYSTEMTIME)); m_b_is_tz = false; }

INT      CSystemTime::Compare(const CSystemTime& _sys, const WORD _msec_threshold) const
{
	return (CSystemTime_LeftAfterRight(*this, _sys, _msec_threshold));
}

HRESULT  CSystemTime::Current(void) {
	if (CTimeBase::IsLocal())
		::GetLocalTime(this);
	else
		::GetSystemTime(this);

	HRESULT hr_ = S_OK;
	return  hr_;
}

CString  CSystemTime::DefaultFormatValue(void)const {

	CString result_;
	result_.Format(
		CSystemTime::GetDefaultFormat(false, CDateTimeStyle::eUnspecified) ,
		(*this).wYear, (*this).wMonth, (*this).wDay, (*this).wHour, (*this).wMinute, (*this).wSecond, (*this).wMilliseconds
	);
	return result_;
}

bool     CSystemTime::IsValid(void)const {
	
	const bool isLeapYear  = (TBase::wYear % 4 == 0 && (TBase::wYear % 100 != 0 || TBase::wYear % 400 == 0));

	bool b_valid = true;
	if ( b_valid ) b_valid = (TBase::wYear != 0 && TBase::wYear != 1601 && TBase::wMonth != 0 && TBase::wDay != 0 && TBase::wMilliseconds != 0);
	if ( b_valid ) b_valid = (TBase::wYear % 400 == 0 && TBase::wYear % 4 == 0);
	if ( b_valid ) b_valid = (TBase::wYear % 100 != 0);
	if ( b_valid && TBase::wMonth == 2) b_valid = (isLeapYear ?  TBase::wDay < 30 : TBase::wDay < 29);
	return b_valid;
}

HRESULT  CSystemTime::Random (void) {
	::memset(this, 0, sizeof(SYSTEMTIME));
	this->wYear    = CSystemTime_RandomWord(1990, 2035);
	this->wMonth   = CSystemTime_RandomWord(   1,   12);
	this->wDay     = CSystemTime_RandomWord(   1,   31);  // TODO: this value must be in accordance with month and leap year;
	this->wHour    = CSystemTime_RandomWord(   0,   23);
	this->wMinute  = CSystemTime_RandomWord(   0,   59);
	this->wSecond  = CSystemTime_RandomWord(   0,   59);
	this->wMilliseconds
	               = CSystemTime_RandomWord(   0,  999);
	HRESULT hr_ = S_OK;
	return  hr_;
}

HRESULT  CSystemTime::ToString(CString& _result, const DWORD _style) const
{
	HRESULT hr_ = S_OK;
	// YYYY-MM-DDThh:mm:ss.sTZD (eg 1997-07-16T19:20:30.45+01:00)
	// http://www.w3.org/TR/NOTE-datetime
	static LPCTSTR p_date_0 = _T("%04d-%02d-%02dT%02d:%02d:%02d.%02d%s%02d:%02d");
	static LPCTSTR p_date_1 = _T("%04d-%02d-%02dT%02d:%02d:%02dZ");

	if (CDateTimeStyle::eNoMillisecs & _style)
	{
		_result.Format(
			p_date_1, (*this).wYear, (*this).wMonth, (*this).wDay, (*this).wHour, (*this).wMinute, (*this).wSecond
		);
		return hr_;
	}

	CDateBias bias_;
	hr_ = bias_.Initialize();
	if (FAILED(hr_))
		return hr_;

	_result.Format(
			p_date_0, (*this).wYear, (*this).wMonth, (*this).wDay, (*this).wHour, (*this).wMinute, (*this).wSecond,
			static_cast<WORD>((*this).wMilliseconds / 10) , // needs only two digits, not three ones
			bias_.IsBeforeUtc() ? _T("+") : _T("-"),        // UTC = local time + bias, i.e. for time zones after GMT the bias is negative; 
			bias_.Hours(),
			bias_.Minutes()
		);
	return hr_;
}

HRESULT  CSystemTime::ToValue(LPCTSTR _lp_sz_value) {

	HRESULT hr_ = S_OK;
	if (NULL == _lp_sz_value || 0==::lstrlenW(_lp_sz_value))
		return (hr_ = E_INVALIDARG);
	
	static LPCTSTR lp_sz_fmt = _T("%d/%d/%d %d:%d:%d.%d"); // yyyy/MM/dd hh:mm:ss.mss
#if(0)
	// Error: Stack around the variable 'string' was corrupted; this error is caused by overflowing WORD type members by INT type;
	::_stscanf_s(
		_lp_sz_value, lp_sz_fmt,
		&TBase::wYear, &TBase::wMonth, &TBase::wDay, &TBase::wHour, &TBase::wMinute, &TBase::wSecond, &TBase::wMilliseconds
	);
#endif
	enum _ndx {
		e_year    = 0x0,
		e_month   = 0x1,
		e_day     = 0x2,
		e_hour    = 0x3,
		e_min     = 0x4,
		e_sec     = 0x5,
		e_msec    = 0x6,
	};
	LONG val_[e_msec + 1] = {0};

	::_stscanf_s(
		_lp_sz_value, lp_sz_fmt,
		&val_[e_year], &val_[e_month], &val_[e_day], &val_[e_hour], &val_[e_min], &val_[e_sec], &val_[e_msec]
	);

	TBase::wDay          = static_cast<WORD>(val_[e_day]);
	TBase::wHour         = static_cast<WORD>(val_[e_hour]);
	TBase::wMilliseconds = static_cast<WORD>(val_[e_msec]);
	TBase::wMinute       = static_cast<WORD>(val_[e_min]);
	TBase::wMonth        = static_cast<WORD>(val_[e_month]);
	TBase::wSecond       = static_cast<WORD>(val_[e_sec]);
	TBase::wYear         = static_cast<WORD>(val_[e_year]);

	if (TBase::wHour > 12)
		this->m_b_is_tz = true;

	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

CSystemTime&  CSystemTime::operator=(const DATE _date) {
	::VariantTimeToSystemTime(_date, this);
	return *this;
}
			  
CSystemTime&  CSystemTime::operator=(const FILETIME& _ft)
{
	if (!_ft.dwHighDateTime || !_ft.dwLowDateTime)
		::memset((SYSTEMTIME*)this, 0, sizeof(SYSTEMTIME));
	else if (CTimeBase::IsLocal()){
		FILETIME ft_ = {0};
		FileTimeToLocalFileTime(&_ft, &ft_);
		FileTimeToSystemTime(&ft_, this);
	}
	else {
		::FileTimeToSystemTime(&_ft, (SYSTEMTIME*)this);
	}

	return *this;
}
			  
CSystemTime&  CSystemTime::operator=(const LARGE_INTEGER& _li)
{
	if (CTimeBase::IsLocal()) {
		*this = *((PFILETIME)&_li);
	}
	else {
		FILETIME ft_ = {0};
		ft_.dwHighDateTime = _li.HighPart;
		ft_.dwLowDateTime  = _li.LowPart;
		*this = ft_;
	}
	return *this;
}
			  
CSystemTime&  CSystemTime::operator=(const LPCTSTR lpszData) {
#if(0)
	if (NULL == lpszData || ::lstrlenW(lpszData) < 1)
		return *this;
#endif
	//
	// TODO: the function fails due to argument type overflow (INT to WORD);
	//
#if (0)
	::_stscanf_s(
		lpszData,
		CSystemTime::GetDefaultFormat(true), &TBase::wYear, &TBase::wMonth, &TBase::wDay, &TBase::wHour, &TBase::wMinute, &TBase::wSecond
		);
#else
	this->ToValue(lpszData);
#endif
	return *this;
}
			  
CSystemTime&  CSystemTime::operator=(const SYSTEMTIME& _time)
{
	const DWORD size_ = sizeof(SYSTEMTIME);
	::memcpy_s(
			this  ,
			size_ ,
			&_time,
			size_
		);
	return *this;
}
			  
CSystemTime&  CSystemTime::operator=(const time_t& _time)
{
	::memset(this, 0, sizeof(SYSTEMTIME));
	//
	// time_t does not contain milliseconds, in comparison with driver ability to save timestamp in nanoseconds :(;
	// https://support.microsoft.com/en-us/help/167296/how-to-convert-a-unix-time-t-to-a-win32-filetime-or-systemtime
	//
	LONGLONG ll_ = Int32x32To64(_time, 10000000) + 116444736000000000;
	FILETIME ft_ = {0};
	ft_.dwLowDateTime  = (DWORD)ll_;
	ft_.dwHighDateTime = ll_ >> 32;

	*this = ft_;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
CSystemTime::operator const  DATE       (void)const {
	DOUBLE dt_ = 0.0f;
	::SystemTimeToVariantTime((LPSYSTEMTIME)this, &dt_);
	return dt_;
}
CSystemTime::operator const  SYSTEMTIME&(void)const { return *this; }
CSystemTime::operator        SYSTEMTIME&(void)      { return *this; }
CSystemTime::operator const LPSYSTEMTIME(void)      { return  this; }
CSystemTime::operator       LPSYSTEMTIME(void)      { return  this; }

/////////////////////////////////////////////////////////////////////////////

LPCTSTR  CSystemTime::GetDefaultFormat(const bool bScanPattern, const DWORD _style) {
	if (bScanPattern) {
		static LPCTSTR lpsz_ = _T("%d-%d-%d %d:%d:%d"); return lpsz_;
	}
	else
	if (CDateTimeStyle::eNoMillisecs & _style) {
		static LPCTSTR lpsz_ = _T("%04d-%02d-%02d %02d:%02d:%02d"); return lpsz_;
	}
	else {
		static LPCTSTR lpsz_ = _T("%04d-%02d-%02d %02d:%02d:%02d.%03d"); return lpsz_;
	}
}

/////////////////////////////////////////////////////////////////////////////

CDateTime::CDateTime(void) { ::GetLocalTime(&m_time); }
CDateTime::CDateTime(const CDateTime& _ref) : CDateTime() { *this = _ref; }

CDateTime::CDateTime(const SYSTEMTIME& _st) {
	::memcpy_s(&m_time, sizeof(SYSTEMTIME), &_st, sizeof(SYSTEMTIME));
}

CDateTime::CDateTime(const time_t _time)
{
	::memset(&m_time, 0, sizeof(SYSTEMTIME));

	LONGLONG ll_ = Int32x32To64(_time, 10000000) + 116444736000000000;
	FILETIME ft_ = {0};
	ft_.dwLowDateTime  = (DWORD)ll_;
	ft_.dwHighDateTime = ll_ >> 32;

	::FileTimeToSystemTime(&ft_, &m_time);
}

/////////////////////////////////////////////////////////////////////////////

SYSTEMTIME CDateTime::GetCurrent   (void) const { return m_time; }

CString    CDateTime::GetDate      (void) const {
	static LPCTSTR lp_sz_pat = _T("%04d-%02d-%02d");
	CString cs_date;
	cs_date.Format(
		lp_sz_pat, m_time.wYear, m_time.wMonth, m_time.wDay
	);
	return cs_date;
}

CString    CDateTime::GetTimeAsUnix(void) const {
	// YYYY-MM-DDThh:mm:ss.sTZD (eg 1997-07-16T19:20:30.45+01:00)
	// http://www.w3.org/TR/NOTE-datetime
	static LPCTSTR p_date = _T("%04d-%02d-%02dT%02d:%02d:%02d.%02d%s%02d:%02d");

	TIME_ZONE_INFORMATION tzi = {0};
	::GetTimeZoneInformation(&tzi);

	LONG l_bias = tzi.Bias;

	const LONG l_bias_h = abs(l_bias) / 60;
	const LONG l_bias_m = abs(l_bias) % 60;

	::ATL::CString cs_timestamp;
	cs_timestamp.Format(
		p_date        ,
		m_time.wYear  ,
		m_time.wMonth ,
		m_time.wDay   ,
		m_time.wHour  ,
		m_time.wMinute,
		m_time.wSecond,
		(WORD)m_time.wMilliseconds/10 , // needs only two digits, not three ones
		l_bias < 0 ? _T("+") : _T("-"), // UTC = local time + bias, i.e. for time zones after GMT the bias is negative; 
		l_bias_h,
		l_bias_m
	);
	return cs_timestamp;
}

CString    CDateTime::GetUnixEpoch (void) const {
	static LPCTSTR p_date = _T("%04d-%02d-%02d %02d:%02d:%02d.%02d");

	::ATL::CString cs_timestamp;
	cs_timestamp.Format(
		p_date        ,
		m_time.wYear  ,
		m_time.wMonth ,
		m_time.wDay   ,
		m_time.wHour  ,
		m_time.wMinute,
		m_time.wSecond,
		(WORD)m_time.wMilliseconds/10  // needs only two digits, not three ones
	);
	return cs_timestamp;
}

CString    CDateTime::GetTime(void) const {
	static LPCTSTR lp_sz_pat = _T("%02d:%02d:%02d.%02d");
	CString cs_time;
	cs_time.Format(
			lp_sz_pat, m_time.wHour, m_time.wMinute, m_time.wSecond, m_time.wMilliseconds
		);
	return cs_time;
}

void       CDateTime::Refresh(void) { ::GetLocalTime(&m_time); }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
	CString CDateTime::Print (void) const {
	
		_pc_sz p_sz_pat = _T("cls::[%s]>>{%s %s}");

		CString cs_out; cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, this->GetDate().GetString(), this->GetTime().GetString());
		return  cs_out;
	}
#endif
/////////////////////////////////////////////////////////////////////////////

CDateTime& CDateTime::operator= (const CDateTime& _rh_ref) {

	const DWORD size_ = sizeof(SYSTEMTIME);
	::memcpy_s(
		&this->m_time, size_ , &_rh_ref.m_time, size_
	);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

INT    CDateTime::Compare(const FILETIME& _t0, const FILETIME& _t1, const WORD _msec_threshold)
{
	SYSTEMTIME t0_ = {0}; ::FileTimeToSystemTime(&_t0, &t0_);
	SYSTEMTIME t1_ = {0}; ::FileTimeToSystemTime(&_t1, &t1_);

	const INT result_ = CDateTime::Compare(t0_, t1_, _msec_threshold);
	return result_;
}

INT    CDateTime::Compare(const SYSTEMTIME& _t0, const SYSTEMTIME& _t1, const WORD _msec_threshold)
{
	if (CSystemTime_IsEqual(_t0, _t1, _msec_threshold))
		return  0;
	if (CSystemTime_LeftLaterRight(_t0, _t1, _msec_threshold))
		return -1;
	else
		return  1;
}

time_t CDateTime::FileTimeToUnix(const FILETIME& _ftime)
{
	SYSTEMTIME st_ = {0};
	::FileTimeToSystemTime(&_ftime, &st_);

	time_t result_ = CDateTime::SystemTimeToUnix(st_);
	return result_;
}

time_t CDateTime::SystemTimeToUnix(const SYSTEMTIME& _st)
{
	struct tm tmp_ = {0};
	tmp_.tm_mday   = _st.wDay;
	tmp_.tm_mon    = _st.wMonth - 1;
	tmp_.tm_year   = _st.wYear  - 1900;

	tmp_.tm_sec    = _st.wSecond;
	tmp_.tm_min    = _st.wMinute;
	tmp_.tm_hour   = _st.wHour;

	time_t result_ = std::mktime(&tmp_);
	return result_;
}

/////////////////////////////////////////////////////////////////////////////
namespace shared { namespace common {
	bool operator == (const CDateTime& _lh_ref, const CDateTime& _rh_ref) {
		return CSystemTime_IsEqual(_lh_ref.GetCurrent(), _rh_ref.GetCurrent(), 0);
	}
	bool operator != (const CDateTime& _lh_ref, const CDateTime& _rh_ref) {
		return !CSystemTime_IsEqual(_lh_ref.GetCurrent(), _rh_ref.GetCurrent(), 0);
	}
}}
/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core {
/////////////////////////////////////////////////////////////////////////////

CFileTime::CFileTime(const bool bTimezone) : TBase(bTimezone) { this->Clear(); }
CFileTime::CFileTime(const FILETIME& _ft) : TBase(false) { *this = _ft; }
CFileTime::CFileTime(const LARGE_INTEGER& _li) : TBase(false) { *this = _li; }
CFileTime::CFileTime(const SYSTEMTIME& _sys) : TBase(false) { *this = _sys; }
CFileTime::CFileTime(const time_t& _time) : TBase(false) { *this = _time; }

/////////////////////////////////////////////////////////////////////////////

CFileTime& CFileTime::operator=(const FILETIME& _ft) {

	if (!_ft.dwHighDateTime || !_ft.dwLowDateTime)
		this->Clear();
	else {
		this->m_ftime = _ft;
	}
	return *this;
}

CFileTime& CFileTime::operator=(const LARGE_INTEGER& _li) {

	m_ftime.dwHighDateTime   = _li.HighPart;
	m_ftime.dwLowDateTime    = _li.LowPart ;

	return *this;
}

CFileTime& CFileTime::operator=(const SYSTEMTIME& _sys) {

	if (::SystemTimeToFileTime(&_sys, &m_ftime)) {
		if (TBase::IsLocal()) {

			FILETIME local_ = {0};

			if (!::FileTimeToLocalFileTime(&m_ftime, &local_))
				this->Clear();
			else
				m_ftime = local_;
		}
	}
	else
		this->Clear();
	return *this;
}

CFileTime& CFileTime::operator=(const time_t& _time) {

	LONGLONG ll_ = Int32x32To64(_time, 10000000) + 116444736000000000;
    m_ftime.dwLowDateTime  = (DWORD) ll_;
    m_ftime.dwHighDateTime = ll_ >>32;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

bool CFileTime::operator== (const CFileTime& _ft) { return (this->m_ftime.dwHighDateTime == _ft.m_ftime.dwHighDateTime
                                                         && this->m_ftime.dwLowDateTime  == _ft.m_ftime.dwLowDateTime); }
bool CFileTime::operator!= (const CFileTime& _ft) { return (this->m_ftime.dwHighDateTime != _ft.m_ftime.dwHighDateTime
                                                         || this->m_ftime.dwLowDateTime  != _ft.m_ftime.dwLowDateTime); }
bool CFileTime::operator<  (const CFileTime& _ft) { return (this->m_ftime.dwHighDateTime << _ft.m_ftime.dwHighDateTime
                                                         || this->m_ftime.dwLowDateTime  << _ft.m_ftime.dwLowDateTime); }
bool CFileTime::operator>  (const CFileTime& _ft) { return (this->m_ftime.dwHighDateTime >> _ft.m_ftime.dwHighDateTime
                                                         || this->m_ftime.dwLowDateTime  >> _ft.m_ftime.dwLowDateTime); }

/////////////////////////////////////////////////////////////////////////////

HRESULT CFileTime::Clear(void) {
	HRESULT hr_ = S_OK;
	// ::std::fill_n(&m_ftime, sizeof(FILETIME), 0);
	//
	// https://stackoverflow.com/questions/1975916/should-c-programmer-avoid-memset
	::memset(&m_ftime, 0, sizeof(FILETIME));
	return  hr_;
}

INT     CFileTime::Compare(const FILETIME& _ft, const WORD _msec_threshold)
{
	CSystemTime this_ = m_ftime;
	const INT result_ = this_.Compare(CSystemTime(_ft), _msec_threshold);
	return result_;
}

HRESULT CFileTime::ToString(CString& _result) const
{
	CSystemTime sys_(TBase::IsLocal());
	sys_ = m_ftime;

	HRESULT hr_ = sys_.ToString(_result);
	return  hr_;
}

}}
/////////////////////////////////////////////////////////////////////////////

CUnixTime::CUnixTime(const bool bTimezone) : m_time(NULL), TBase(bTimezone) {
}
CUnixTime::CUnixTime(const time_t& _time, const bool bTimezone) : m_time(_time), TBase(bTimezone) {
}

/////////////////////////////////////////////////////////////////////////////

void    CUnixTime::Clear (void)      { m_time = 0; }

time_t& CUnixTime::Current(void){
	
	m_time = ::std::time(0);

	if (TBase::IsLocal()){
	     struct tm info_ = {0};
	     ::std::localtime_s(&info_, &m_time);
	}
	else ::std::time(&m_time);
	return *this;
}

INT     CUnixTime::GapWith(const time_t& _time)const {
	INT n_sec = static_cast<INT>(::std::difftime(_time, m_time));
	return n_sec;
}

INT     CUnixTime::GapWithCurrent(void) const {
	struct tm info_ = {0};
	time_t current_ = ::std::time(0);
	if (TBase::IsLocal()) ::std::localtime_s(&info_, &current_);
	else                  ::std::time(&current_);
	return this->GapWith(current_);
}

bool    CUnixTime::IsNull(void)const {
	return (0 == m_time);
}

bool    CUnixTime::IsValid(void)const {
	//
	//  TODO: checking addition operation result is probably a confirmation of the validity;
	//        something likes this:
	//  if((now = time(NULL)) == (time_t)-1) goto __error_handler;
	//  tp = localtime(&now);
	//  tp->tm_sec += 10; /* Add 10 sec */
	//  if((then = mktime(tp)) == (time_t)-1) goto __error_handler;
	//
	return (0 < m_time && m_time != (time_t)-1);
}

HRESULT CUnixTime::ToString(const bool bFormatted, CString& _result)const {

	HRESULT hr_ = S_OK;

	if (bFormatted) {

		WCHAR buff_[CUnixTime::eFormattedBufferSize]= {0};
		struct tm p_tm = {0};

		if (TBase::IsLocal())
			::std::localtime_s(&p_tm, &this->m_time);
		else
			::std::gmtime_s(&p_tm, &this->m_time);


			if (::wcsftime(
				buff_, _countof(buff_), _T("%Y-%m-%d %H:%M:%S"), &p_tm
			))
				_result = buff_;
			else
				hr_ = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
	}
	else {
		_result.Format(
					_T("%ld"), this->m_time
				);
	}
	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

CUnixTime&   CUnixTime::operator=(const DATE _date) {
	CSystemTime sys_tm; sys_tm = _date;
	return (*this = sys_tm);
}

CUnixTime&   CUnixTime::operator=(const CSystemTime& _sys) {

	return (*this = (SYSTEMTIME&)_sys);
}

CUnixTime&   CUnixTime::operator=(const FILETIME& _ft) {

	LARGE_INTEGER li_time = {0};
	li_time.LowPart  = _ft.dwLowDateTime;
	li_time.HighPart = _ft.dwHighDateTime;

	return (*this = li_time);
}

CUnixTime&   CUnixTime::operator=(const LARGE_INTEGER& _li) {

	this->m_time = _li.QuadPart / 10000000ULL - 11644473600ULL;

	return *this;
}

CUnixTime&   CUnixTime::operator=(const SYSTEMTIME& _sys) {

	struct tm time_ = {0};
	time_.tm_mday   = _sys.wDay;
	time_.tm_mon    = _sys.wMonth - 1;
	time_.tm_year   = _sys.wYear  - 1900;

	time_.tm_sec    = _sys.wSecond;
	time_.tm_min    = _sys.wMinute;
	time_.tm_hour   = _sys.wHour;

	LONG i_sec = 0;
	if (TBase::IsLocal()) {
		// does not	work as expected:	
		// https://stackoverflow.com/questions/28696211/conversion-from-systemtime-to-time-t-gives-out-time-in-utc-gmt

		CDateBias bias_;
		bias_.Initialize();

		i_sec = bias_.Hours() * 3600 + bias_.Minutes() * 60;
		if (bias_.IsBeforeUtc() == false)
			i_sec = -i_sec;

#define _n_sec_per_hour (3600)
#define _n_hrs_per_day  (24)
#define _n_sec_per_day  (_n_sec_per_hour * _n_hrs_per_day)
	//
	//  getting time zone shift in seconds also works;
	//	const errno_t err_ =  ::_get_timezone(&i_sec);
	//	if (err_ == 0) {
	//		i_sec = -i_sec;
			i_sec = (i_sec >  12 * _n_sec_per_hour) ? (i_sec - _n_sec_per_day) : i_sec;
			i_sec = (i_sec < -11 * _n_sec_per_hour) ? (i_sec + _n_sec_per_day) : i_sec;

	//	}
	//  this code is not provided via web site; but it still remains crucial;
	//  it calculates properly a base of time value for local zone;
	//
		time_.tm_hour = time_.tm_hour + (bias_.IsBeforeUtc() ? -bias_.Hours()   : +bias_.Hours());
		time_.tm_min  = time_.tm_min  + (bias_.IsBeforeUtc() ? -bias_.Minutes() : +bias_.Minutes());
	}
	m_time  = ::std::mktime(&time_);
	m_time += i_sec;

	return *this;
}

CUnixTime&   CUnixTime::operator=(const time_t& _time) {

	this->m_time = _time;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

bool CUnixTime::operator== (const CUnixTime& _time) const { return (this->m_time == _time.m_time); }
bool CUnixTime::operator!= (const CUnixTime& _time) const { return (this->m_time == _time.m_time); }
bool CUnixTime::operator<  (const CUnixTime& _time) const { return (this->m_time  < _time.m_time); }
bool CUnixTime::operator>  (const CUnixTime& _time) const { return (this->m_time  > _time.m_time); }

/////////////////////////////////////////////////////////////////////////////
CUnixTime::operator const  DATE   (void)const {
	CSystemTime sys_tm = this->m_time;
	return (DATE)sys_tm;
}
CUnixTime::operator const  time_t&(void)const { return  m_time; }
CUnixTime::operator        time_t&(void)      { return  m_time; }
CUnixTime::operator const  time_t*(void)      { return &m_time; }
CUnixTime::operator        time_t*(void)      { return &m_time; }