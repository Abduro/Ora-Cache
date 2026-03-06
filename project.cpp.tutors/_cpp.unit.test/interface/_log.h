#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-Apr-2024 at 08:16:58.2117972, UTC+7, Novosibirsk, Monday;
	This is Ebo Pak UIX libs unit test logger interface declaration file.
*/
#include "_defs.h"
#include "shared.dbg.h"
#include "shared.timer.h" // for using shared::common::CChrono and CChrono_auto classes;

namespace ebo { namespace boo { namespace test {

	namespace predefs {
	static _pc_sz _p_pfx = _T("\t\t");         // the indentation at the start of the line;
	static _pc_sz _p_sfx = _T("\n");           // new line only;
	static _pc_sz _p_new_ln = _T("\n\t");      // new line with indentation;
	}
	using TParts  = shared::defs::TParts;      // text lines actually; 
	using TCached = shared::defs::TParts;      // buffered text for cache output;

	using CChrono = shared::common::CChrono;
	using CChrono_auto = shared::common::CChrono_auto;

	class CIndent_auto {
	public:
		CIndent_auto (void); CIndent_auto (const CIndent_auto&) = delete; CIndent_auto (CIndent_auto&&) = delete; ~CIndent_auto (void);
		operator _pc_sz (void) const;
	};

	class CCache {
	public:
		CCache (void); CCache (const CCache&) = delete; CCache (CCache&&) = delete; ~CCache (void);

		void  Clear(void);

		const TCached& Get (void) const; // gets a reference to a vector of buffered strings (ro); 
		      TCached& Get (void)      ; // gets a reference to a vector of buffered strings (rw);
		const
		bool&  Locked (void) const;      // gets a reference to the lock flag of this cache (ro); 'true' means: add message - 'no', otherwise 'yes';
		bool&  Locked (void) ;           // gets a reference to the lock flag of this cache (rw); 'true' means: add message - 'no', otherwise 'yes';

		_pc_sz Prefix (void) const;      // gets a prefix string that is inserted before each element of the buffer;
		void   Prefix (_pc_sz)   ;       // sets a prefix string, it can be equal to null or be empty; '\t' (default);

		_pc_sz Suffix (void) const;      // gets a suffix string that is inserted after each element of the buffer;
		void   Suffix (_pc_sz)   ;       // sets a suffix string, it can be equal to null or be empty; '\n' (default);

		void   Output (void) const;

	public:
#pragma region opers
		CCache& operator = (const CCache&) = delete;
		CCache& operator = (CCache&&) = delete;

		CCache& operator <<(_pc_sz _prefix); // ToDo: it would be better to use pattern, not a prefix;
		CCache& operator >>(_pc_sz _suffix); // ToDo: it would be better to use pattern, not a suffix;

		CCache& operator +=(_pc_sz _p_out ); // appends a raw text to this cache;
		CCache& operator +=(const CString&); // appends a string object to this cache;
		CCache& operator +=(const TParts&);  // appends words i.e. parts of the sentence(s) that can be differ to multiple lines by a separator;
		CCache& operator +=(TError&);        // appends error object content; *important*: verbose mode does *not* affect the error output;
		const
		CCache& operator ()(void) const;     // ouputs this cache content to 'Test' ouput panel;
		CCache& operator ()(const bool _b_verb); // if '_b_verb' is 'true' there's no lock for adding a message, otherwise the lock is turned on;
		operator bool (void) const;          // returns current lock status of this cache;
#pragma endregion
	private:
		bool m_locked; // the flag for indicating the block of adding new messages to this cache; is set to 'false' by default;
		TCached  m_strings;
		CString  m_prefix ;
		CString  m_suffix ;
	};

	class CLogger : public shared::dbg::ITestOutput {
	public:
		 CLogger (void); CLogger (const CLogger&) = delete; CLogger (CLogger&&) = delete; ~CLogger (void) = default;

	public:
		// https://en.cppreference.com/w/cpp/utility/format/spec ;
		// https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions ;
		_pc_sz   Pattern (void) const;
		bool     Pattern (_pc_sz _pat); // returns true in case when input arg not empty; no check of format specifications yet;

		const
		CCache&  Cached (void) const;   // gets a reference to cached strings (ro);
		CCache&  Cached (void)      ;   // gets a reference to cached strings (rw);

	public:
		void Out (const CString&) const;
		void Out (_pc_sz _lp_sz_text) const;
		
	public: // https://en.cppreference.com/w/cpp/language/operators ;
	        // https://en.cppreference.com/w/cpp/language/user_literal ;	
		CLogger& operator = (const CLogger&) = delete;
		CLogger& operator = (CLogger&&) = delete;

		const CLogger& operator <<(const CString&) const;
		const CLogger& operator <<(_pc_sz _lp_sz_text) const;

		CLogger& operator +=(const CString& cs_out);     // appends the input string object to the cache; [for simplicity of input];
		CLogger& operator +=(_pc_sz _p_sz_out);          // appends the raw text to the cache; [for simplicity of input];
		CLogger& operator +=(TError&);             // appends the error object content;

		CLogger& operator >>(_pc_sz _lp_sz_pat);   // sets the pattern string;

		operator CCache& (void);

		const
		CLogger& operator()(void) const;           // it is the shortcut for cached strings class functor operator;
		CLogger& operator()(const bool _b_verb);   // allows/disallows adding messages to the cache;

		void Write (_pc_sz _p_msg) override final; // ITestOutput interface method;

		CLogger& operator()(TError&);              // adds error message regardless the verbose option, because any error is always important;

	private:
		mutable
		CCache    m_cache;
		CString   m_pattern; // not used yet;
	};

	class CTime : public shared::common::ISpent {
	public:
		CTime (void); CTime (const CTime&) = delete; CTime (CTime&&) = delete; ~CTime (void) = default;
		_pc_sz Spent (void) const;
		_pc_sz operator ()(void) const;
	private:
		CTime& operator = (const CTime&) = delete; CTime& operator = (CTime&&) = delete;
		void Put (_pc_sz) override final;

		CString m_spent;
	};
}}}

typedef ebo::boo::test::CLogger TLogger;
// returns a reference to a singleton of the logger object; no const is required due to some settings of logger attributes is possible;
/*const*/TLogger& _out(void);

#endif/*_LOG_H_INCLUDED*/