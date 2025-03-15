#ifndef _SHARED_RANDOM_H_INCLUDED
#define _SHARED_RANDOM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Feb-2011 at 3:09:34p, GMT+3, Rostov-on-Don, Friday;
	This is Multichart authorize server user impersonate helper class declaration file. [on-site work; https://www.multicharts.com/ ]
	----------------------------------------------------------------------------- [oDesk.com]
	Adopted to Pulsepay project on 3-Jun-2012 at 1:38:40pm, GMT+3, Rostov-on-Don, Sunday;
	----------------------------------------------------------------------------- [Upwork.com]
	Adopted to Maars TS1 server project on 31-Oct-2015 at 12:15:34p, GMT+7, Phuket, Rawai, Saturday;
	Adopted to Daya Dimensi Global Task project on 2-Apr-2017 at 02:46:52a, UTC+7, Phuket, Rawai, Sunday;
*/
#include <limits>
#include <guiddef.h>
namespace std {
#include <time.h>
}
#include "shared.types.h"
#include "shared.string.h"

namespace shared { namespace common {

	// https://en.wikipedia.org/wiki/Pseudorandom_number_generator ;

	using namespace shared::types;

	class CRndGen {
	public:
		 CRndGen (void);
		 CRndGen (const CRndGen&) = delete; CRndGen(CRndGen&&) = delete;
		~CRndGen (void);

	public:
		long     SignedLong  (const long  _min = (std::numeric_limits<long>::min)() , 
		                      const long  _max = (std::numeric_limits<long>::max)() ) const;

		CString  UniqueSeq   (const dword _length, const bool bCaseSensitive = false) const;
		CString  UniqueSeq_Ex(const dword _length, const bool bLowCase = true)const;

		_uint    Unsigned    (const _uint _min = (std::numeric_limits<_uint>::min)(), 
		                      const _uint _max = (std::numeric_limits<_uint>::max)()) const;

		// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cocreateguid ;
	public:
		static CString  GuidAsText(const bool _b_simple , const bool bCaseSensitive = false);
		static CString  GuidAsText(const GUID& _guid_ref, const bool _b_simple , const bool bCaseSensitive);

	private:
		CRndGen& operator = (const CRndGen&) = delete;
		CRndGen& operator = (CRndGen&&) = delete;
	};

	class CRndGen_Ex : public CRndGen { typedef CRndGen TBase;
	public:
		 CRndGen_Ex (void);
		 CRndGen_Ex (const CRndGen_Ex&) = delete; CRndGen_Ex (CRndGen_Ex&&) = delete;
		~CRndGen_Ex (void);

	public:
		double  Epsilone (void) const;

	public:
		double  operator ()(void) const;

	private:
		CRndGen_Ex& operator = (const CRndGen_Ex&) = delete;
		CRndGen_Ex& operator = (CRndGen_Ex&&) = delete;
	};
}}

typedef shared::common::CRndGen    TRandom;
typedef shared::common::CRndGen_Ex TRandom_Ex;

#endif/*__PULSEPAYSHAREDFIMPLERSONATE_H_7F403554_2B6C_4f5d_9005_BF4E218DB42A_INCLUDED*/