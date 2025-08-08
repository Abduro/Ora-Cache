#ifndef _LOG_H_INCLUDED
#define _LOG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-Apr-2024 at 08:16:58.2117972, UTC+7, Novosibirsk, Monday;
	This is Ebo Pak UIX libs unit test logger interface declaration file.
*/
#include "_defs.h"

namespace ebo { namespace boo { namespace test {

	static _pc_sz _p_pfx = _T("\t\t");         // the indentation at the start of the line;
	static _pc_sz _p_sfx = _T("\n");           // new line only;
	static _pc_sz _p_new_line = _T("\n\t\t");  // new line with indentation;

	static _pc_sz _p_new_ln = _T("\n\t\t");    // just playing with names;

	using TParts  = shared::common::TParts;    // text lines actually; 
	using TCached = shared::common::TParts;    // buffered text for cache output;

	class CCache {
	public:
		 CCache (void);
		 CCache (const CCache&) = delete;
		 CCache (CCache&&) = delete;
		~CCache (void);

	public:
		void  Clear(void);

		const TCached& Get (void) const; // gets a reference to a vector of buffered strings (ro); 
		      TCached& Get (void)      ; // gets a reference to a vector of buffered strings (rw);

		_pc_sz Prefix (void) const;      // gets a prefix string that is inserted before each element of the buffer;
		void   Prefix (_pc_sz)   ;       // sets a prefix string, it can be equal to null or be empty; '\t' (default);

		_pc_sz Suffix (void) const;      // gets a suffix string that is inserted after each element of the buffer;
		void   Suffix (_pc_sz)   ;       // sets a suffix string, it can be equal to null or be empty; '\n' (default);

		void   Output (void) const;

	public:
		CCache& operator = (const CCache&) = delete;
		CCache& operator = (CCache&&) = delete;

		CCache& operator <<(_pc_sz _prefix); // ToDo: it would be better to use pattern, not a prefix;
		CCache& operator >>(_pc_sz _suffix); // ToDo: it would be better to use pattern, not a suffix;

		CCache& operator +=(_pc_sz _p_out ); // appends a raw text to this cache;
		CCache& operator +=(const CString&); // appends a string object to this cache;
		CCache& operator +=(const TParts&);  // appends words i.e. parts of the sentence(s) that can be differ to multiple lines by a separator;
		const
		CCache& operator()(void) const;

	private:
		TCached  m_strings;
		CString  m_prefix ;
		CString  m_suffix ;
	};

	class CLog_Opts {
	public:
		enum _accepted : uint32_t {
			e_none = 0,
			e_new_line = 1, // if is turned on, i.e. is set to options, new line is applied before the next output to the log;
			e_emp_line = 2, // appens an empty line, no symbols;
		};
	public:
		 CLog_Opts (void) ;
		 CLog_Opts (const CLog_Opts&) = delete;
		 CLog_Opts (CLog_Opts&&) = delete;
		~CLog_Opts (void) ;

	public:
		bool Get (CLog_Opts::_accepted) const;        // gets the requested option set; returns either true or false;
		void Set (CLog_Opts::_accepted, bool _b_set); // sets the input option to on/off or true/false;

	public:
		CLog_Opts& operator +=(const CLog_Opts::_accepted _opt); // sets the input option;
		CLog_Opts& operator -=(const CLog_Opts::_accepted _opt); // remove the input option from the options' set;

	private:
		CLog_Opts& operator = (const CLog_Opts&) = delete;
		CLog_Opts& operator = (CLog_Opts&&) = delete;

	private:
		uint32_t m_accepted;  // this is the set of accepted options for applying to log output content format;
	};

	class CLogger {
	public:
		 CLogger (void) = default;
		 CLogger (const CLogger&) = delete;
		 CLogger (CLogger&&) = delete;
		~CLogger (void) = default;

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
		const
		CLog_Opts& Opts(void) const;
		CLog_Opts& Opts(void) ;

	public: // https://en.cppreference.com/w/cpp/language/operators ;
	        // https://en.cppreference.com/w/cpp/language/user_literal ;	
		CLogger& operator = (const CLogger&) = delete;
		CLogger& operator = (CLogger&&) = delete;

		const CLogger& operator <<(const CString&) const;
		const CLogger& operator <<(_pc_sz _lp_sz_text) const;
		/*
			the following two operators work for output by this class only, cached messages' object does not know anything of the output options; :(
		*/
		CLogger& operator +=(const CLog_Opts::_accepted _opt); // sets the input option; this is for direct call the CLog_Opts::Set(..., true );
		CLogger& operator -=(const CLog_Opts::_accepted _opt); // remove the input option from the options' set; the CLog_Opts::Set(..., false);

		CLogger& operator +=(const CString& cs_out) ;     // appends the input string object to the cache; [for simplicity of input];
		CLogger& operator +=(_pc_sz _p_sz_out) ;          // appends the raw text to the cache; [for simplicity of input];

	public:
		CLogger& operator >>(_pc_sz _lp_sz_pat); // sets the pattern string;

		operator CCache& (void);

		const
		CLogger& operator()(void) const; // it is the shortcut for cached strings class functor operator;

	private:
		CString   m_pattern; // not used yet;
		CCache    m_cache;
		CLog_Opts m_opts ;
	};

}}}

typedef ebo::boo::test::CLog_Opts            TLog_Opts;
typedef ebo::boo::test::CLog_Opts::_accepted TLog_Acc ;
typedef ebo::boo::test::CLogger TLogger;
// returns a reference to a singleton of the logger object; no const is required due to some settings of logger attributes is possible;
/*const*/TLogger& _out(void);

#endif/*_LOG_H_INCLUDED*/