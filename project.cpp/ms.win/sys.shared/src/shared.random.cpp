/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Jun-2012 at 1:48:04pm, GMT+3, Rostov-on-Don, Sunday;
	This is Shared Lite library pseudo-random number/sequence generator class implementation file. [a voluntary project]
	-----------------------------------------------------------------------------
	Adopted to Daya Dimensi Global Task project on 2-Apr-2017 at 02:52:40a, UTC+7, Phuket, Rawai, Sunday; [Upwork.com]
	Adopted to Ebo Pack on 23-Oct-2018 at 11:26:25a, UTC+7, Novosibirsk, Tuesday; [a voluntary project]
*/
#include "shared.random.h"

using namespace shared::common;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace common { namespace _impl {

	void RandomValue_Initialize(void) {

		static bool bInitialized = false;

		if (bInitialized == false) {
			bInitialized  = true;
			::std::srand((unsigned)::std::time(0));
		}
	}

	const char RandomValue_Hash[] = {
				0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
				0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 
				0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54,
				0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x61, 0x62, 0x63, 0x64,
				0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
				0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
				0x79, 0x7a
			}; // [Aa-Zz | 0-9]
	static
	int  RandomValue_Hash_Size = sizeof(RandomValue_Hash)/sizeof(char);

	void RandomValue_Norm(CString& _cs_guid ) {
		if (_cs_guid.IsEmpty() == false)
		{
			_cs_guid.Replace(_T("{"), _T(""));
			_cs_guid.Replace(_T("}"), _T(""));
			_cs_guid.Replace(_T("-"), _T(""));
		}
	}

	CString RandomValue_GUID(const bool bNormalize)
	{
		CString _cs_guid;
		{
			GUID  guid_ = {0};
			HRESULT hr_ = ::CoCreateGuid(&guid_);
			if (SUCCEEDED(hr_))
			{
				TCHAR buffer_[_MAX_PATH] = {0};
				::StringFromGUID2(guid_, buffer_, _countof(buffer_));
				_cs_guid = buffer_;
			}
		}
		if (bNormalize)
			RandomValue_Norm(_cs_guid);

		return _cs_guid;
	}

	static
	const int RandomValue_GUID_Normalized_Len = 32;
}}}
using namespace shared::common::_impl;
/////////////////////////////////////////////////////////////////////////////

CRndGen:: CRndGen (void) { RandomValue_Initialize(); }
CRndGen::~CRndGen (void) {}

/////////////////////////////////////////////////////////////////////////////

long    CRndGen::SignedLong (const long _min, const long _max) const {
	_min; _max;
	if (_max < _min || _max == _min)
		return 0;
	::srand((unsigned)::std::time(0));
	return static_cast<long> ((double)::rand() / (RAND_MAX + 1) * (_max - _min) + _min);
}

CString CRndGen::UniqueSeq (const dword _length, const bool bCaseSensitive) const {
	_length; bCaseSensitive;
	CString cs_seq;
	for ( dword i_ = 0; i_ < _length; i_++)
	{
		const WORD wIndex = (_word) (::rand() % (RandomValue_Hash_Size - 1));
		cs_seq += RandomValue_Hash[wIndex];
	}

	if (!bCaseSensitive)
		cs_seq.MakeLower();
	return cs_seq;
}

CString CRndGen::UniqueSeq_Ex (const dword _length, const bool bLowCase) const {
	_length; bLowCase;

	if (!_length)
		return CString();

	CString seq_;

	const bool bNormalize = true;
	const INT count_ = _length / RandomValue_GUID_Normalized_Len + 1;
	for (INT j_ = 0; j_ < count_; j_++)
	{
		CString cs_part = RandomValue_GUID(bNormalize);
		if (cs_part.IsEmpty()) // indicates an error ;
			break;
		seq_ += cs_part;
	}
	if (bLowCase && !seq_.IsEmpty())
		seq_.MakeLower();

	return seq_.Left(_length);
}

_uint   CRndGen::Unsigned (const _uint _min, const _uint _max) const
{
	if (_max < _min || _max == _min)
		return 0;
	::srand((unsigned)::std::time(0));
	return static_cast<_uint> ((double)::rand() / (RAND_MAX + 1) * (_max - _min) + _min);
}

/////////////////////////////////////////////////////////////////////////////

CString CRndGen::GuidAsText(const bool _b_simple , const bool bCaseSensitive) {
	_b_simple; bCaseSensitive;

	CString cs_guid = RandomValue_GUID(_b_simple);

	if (bCaseSensitive == false)
		cs_guid.MakeLower();

	return cs_guid;
}

CString CRndGen::GuidAsText(const GUID& _guid_ref, const bool _b_simple , const bool bCaseSensitive) {
	_guid_ref; _b_simple; bCaseSensitive;

	CString cs_guid;
	{
		t_char buffer_[_MAX_PATH] = {0};
		::StringFromGUID2(_guid_ref, buffer_, _countof(buffer_));
		cs_guid = buffer_;
	}

	if (_b_simple == true)
		RandomValue_Norm(cs_guid);

	if (bCaseSensitive == false)
		cs_guid.MakeLower();

	return cs_guid;
}

/////////////////////////////////////////////////////////////////////////////

CRndGen_Ex:: CRndGen_Ex(void) : TBase() {}
CRndGen_Ex::~CRndGen_Ex(void) {}

/////////////////////////////////////////////////////////////////////////////

double CRndGen_Ex::Epsilone (void) const {

	LARGE_INTEGER n_marker = {0};
	// https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter ;
	if (::QueryPerformanceCounter(&n_marker)) {
		const DWORD dw_random = n_marker.LowPart ^ ((DWORD) n_marker.HighPart);
		return ((n_marker.LowPart & 0xFF) / 1000000.0);
	}
	else
		return 0.0f;
}

/////////////////////////////////////////////////////////////////////////////

double CRndGen_Ex::operator ()(void) const { return this->Epsilone(); }