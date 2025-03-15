#ifndef _MS_CON_OUT_H_INCLUDED
#define _MS_CON_OUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-May-2024 at 17:07:45.0519612, UTC+7, Novosibirsk, Wednesday;
	This Ebo Pack cppunit test console app output interface declaration file;
*/
#include <iostream>

#ifdef _UNICODE
#define _out_t ::std::wcout
#else
#define _out_t ::std::cout
#endif

#include "ms.con.app.h"

namespace ebo { namespace boo { namespace con {

	using namespace shared::types;

	using TParts  = shared::common::TParts; // text lines actually; 
	using TCached = shared::common::TParts; // buffered text for cache output;

	using TString = TStringEx;

	// ToDo: this is almost the same class as ebo::boo::test::CCache; it is obvious that CCache class implementation must be shared;
	class CCache {
		inline static _pc_sz default_pat = _T("\t%s\n");
	public:
		 CCache (void);
		 CCache (const CCache&) = delete;
		 CCache (CCache&&) = delete;
		~CCache (void);

	public:
		const TCached& Get (void) const; // gets a reference to a vector of buffered strings (ro); 
		      TCached& Get (void)      ; // gets a reference to a vector of buffered strings (rw);

		_pc_sz Pattern (void) const;
		bool   Pattern (_pc_sz = default_pat);

		bool   Append  (_pc_sz _p_sz_item); // appends a text piece to the cache; returns true if succeed; Get() may be used for direct access to data;
		void   Output  (void) const;

	public:
		CCache& operator +=(_pc_sz _p_sz_item); // appends a text line or item;
		CCache& operator +=(const CString&);    // appends a text line or item;
		CCache& operator >>(_pc_sz _p_sz_pat);  // sets the pattern text;
		CCache& operator >>(const CString&);    // sets the pattern text;

		const
		CCache& operator()(void) const;  // prints cached items to console output;

	private:
		mutable
		CString m_pattern;               // the pattern which is used for formatting one row or line of the buffered text item;
		TCached m_cached ;
	};

	class COut {
	public:
		 COut (void) = default;
		 COut (const COut&) = delete;
		 COut (COut&&) = delete;
		~COut (void) = default;

	public:
		const
		CCache&  Cache (void) const;   // gets a reference to cached strings (ro);
		CCache&  Cache (void)      ;   // gets a reference to cached strings (rw);

		void  Wait (_pc_sz _p_sz_title = NULL); // waits for input stream;
	
	public:
		COut& operator = (const COut&) = default;
		COut& operator = (COut&&) = delete;

		COut& operator <<(const CString&);    // appends a text line or item to cache;
		COut& operator <<(_pc_sz _p_sz_item); // appends a text line or item to cache;

		const
		COut& operator()(void) const;  // prints cached items to console output;

	private:
		CCache  m_cache;
	};

}}}

typedef ebo::boo::con::CCache TCache;
typedef ebo::boo::con::COut   TOut;

TOut&  _out (void);

#endif/*_MS_CON_OUT_H_INCLUDED*/