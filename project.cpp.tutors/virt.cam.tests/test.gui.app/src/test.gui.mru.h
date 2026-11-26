#ifndef _TEST_GUI_MRU_H_INCLUDED
#define _TEST_GUI_MRU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Nov-2026 at 10:37:27.155, UTC+4, Batumi, Tuesday;
	This is virtual camera test application MRU class interface declaration file;
*/
#include "test.gui.reg.h"

namespace test { namespace app { namespace storage {

	using qword_t = ::shared::sys_core::storage::qword_t;

	class CTimestamp {
	public:
		CTimestamp (const qword_t = 0ULL); CTimestamp (const CTimestamp&); CTimestamp (CTimestamp&&); ~CTimestamp (void) = default;
		CTimestamp (_pc_sz _p_value);

		qword_t Current (void);         // sets this timestamp to current system time;
		qword_t Get (void) const;
		bool    Set (const qword_t);    // returns 'true' in case of value change;
		static
		bool    To_qword (_pc_sz _in_value, qword_t& _out_value); // converts string value to qword_t, returns 'true' on success; hexadecimal format of input value is auto-recognized;
		bool    To_qword (_pc_sz _in_value);
		static
		bool    Is_hex (_pc_sz _p_value);   // checks a hex-prefix '0x';
		static
		bool    Is_valid (_pc_sz _p_value); // required length of a string (eaquals to 16 symbols' count), hexidecimal format is taken into account;
		static
		bool    Is_valid (const qword_t);
		bool    Is_valid (void) const;
		static
		CString To_str (const qword_t, const bool _b_hex = true);
		CString To_str (const bool _b_hex = true) const;

		CTimestamp& operator = (const CTimestamp&);
		CTimestamp& operator = (CTimestamp&&);
		CTimestamp& operator <<(const qword_t _value);
		CTimestamp& operator <<(_pc_sz _p_value);

		operator const qword_t (void) const;

	private:
		qword_t  m_value;
	};

	/* this class works with URLs in the following format: file:///{the path to an HTML file, expected using slashes instead of back ones}.html;*/
	class CMruItem {
	public:
		CMruItem (void); CMruItem (const CMruItem&); CMruItem (CMruItem&&); ~CMruItem (void) = default;

		TError&   Error (void) const;
		bool   Is_valid (void) const;      // checks the timestamp and existace of HTML file path specified;

		_pc_sz    Path (void) const;       // returns the currently set a path to HTML file; the path spec is in 'file:///...' because it is web browser requirement;
		err_code  Path (_pc_sz _file_url); // checks input path for existance; the input argument value is expected to be in the following format: 'file:///...';

		bool Is_path_equal (_pc_sz _file_url) const;

		const
		CTimestamp& Timestamp (void) const;
		CTimestamp& Timestamp (void) ;

		CMruItem& operator = (const CMruItem&); CMruItem& operator = (CMruItem&&);
		CMruItem& operator <<(_pc_sz _file_url);
		CMruItem& operator <<(const CTimestamp&);

		bool operator == (_pc_sz _p_path) const; // case-insensitive comparison of the input path with the path of this object; doesn't be called :(

	private:
		mutable
		CError     m_error;
		CString    m_path;
		CTimestamp m_stamp;
	};

	typedef ::std::map<qword_t, CMruItem> TMruItems;

	class CMruList {
	public:
		 CMruList (void); CMruList (const CMruList&) = delete; CMruList (CMruList&&) = delete;
		~CMruList (void);

		err_code AddUrl (_pc_sz _p_html_path); // adds new recent item by input html file path;

		TError&  Error (void) const;
		const
		TMruItems& Items (void) const;
		TMruItems& Items (void) ;

		err_code Load (void);
		err_code Save (void);

		err_code Remove (_pc_sz _p_html_path);

	private:
		CMruList& operator = (const CMruList&) = delete; CMruList& operator = (CMruList&&) = delete;
		CError    m_error;
		TMruItems m_items;
	};

}}}
#endif/*_TEST_GUI_MRU_H_INCLUDED*/