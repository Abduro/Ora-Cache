#ifndef _WEB_IE_HTML_H_INCLUDED
#define _WEB_IE_HTML_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Nov-2014 at 5:47:22p, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library HTML element wrapper class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 2:51:25p, UTC+7, Novosibirsk, Monday;
*/
#include "web.ie.defs.h"

namespace ex_ui { namespace web { namespace IE { namespace html { using namespace ::ex_ui::web::IE::defs;

	class CElement {
	public:
		 CElement (CAxWindow& _ctrl_wnd, _pc_sz _p_el_id);
		 CElement (void) = delete; CElement (const CElement&) = delete; CElement (CElement&&) = delete;
		~CElement (void) = default;

		CString   Content (void) const;      // gets inner html of the element;
		err_code  Content (_pc_sz _p_html);  // sets inner html of the element;

		bool      Disabled (void) const;
		err_code  Disabled (const bool);

		TError&   Error (void) const;

		CString   Identifier (void) const;
		bool      Is_valid   (void) const;
		rect_t    Rectangle  (void) const;

		CString   Style (void) const;
		err_code  Style (_pc_sz);            // adds style to existing one; if already defined, it is replaced;

		bool      Visible (void) const;
		err_code  Visible (const bool);

	protected:
		CElement&  operator = (const CElement&) = delete; CElement& operator = (CElement&&) = delete;
		mutable
		CError      m_error;
		CAxWindow&  m_ctrl_wnd;
		TElementPtr m_el_ptr;
		CString     m_el_id;
	};

	class COption {
	public:
		 COption (void); COption (const COption&); COption (COption&&);
		~COption (void) = default;

		bool   Selected (void) const;
		void   Selected (const bool);

		_pc_sz Text (void) const;
		void   Text (_pc_sz _p_txt);
		
		COption& operator = (const COption&); COption& operator = (COption&&);
		COption& operator <<(_pc_sz _p_text);

		class CValue {
		public:
			CValue (void); CValue (const CValue&); CValue (CValue&&) = delete; ~CValue (void) = default;

			bool   AsBool (void) const;
			long_t AsLong (void) const;

			bool   Has (_pc_sz _p_text) const;

			_pc_sz Get (void) const;
			void   Set (_pc_sz _p_value);

			CValue& operator = (const CValue&); CValue& operator = (CValue&&) = delete;
			CValue& operator <<(_pc_sz _p_value);
		private:
			CString m_value;
		};

		const
		CValue& Value (void) const;
		CValue& Value (void) ;
		COption& operator <<(const CValue&);

	private:
		CString m_text;
		bool    m_selected;
		CValue  m_value;
	};

	typedef ::std::vector<COption> TOptions;

	class CSelect : public CElement { typedef CElement TBase;
	public:
		 CSelect (CAxWindow& _browser, _pc_sz _p_el_id); CSelect (const CSelect&) = delete; CSelect (CSelect&&) = delete;
		~CSelect (void);

		long_t    Index (void) const;
		err_code  Index (const long_t);

		bool   Is_empty (void) const;
		bool   Is_valid (void) const;

		const
		TOptions& Items (void) const;   // gets a reference to the vector of the available options;
		err_code  Items (void) ;        // fills the vector by available options;

		const
		COption&  Selected (void) const;
		err_code  Selected (_pc_sz _p_value);
		
	private:
		CSelect& operator = (const CSelect&) = delete; CSelect& operator = (CSelect&&) = delete;
		TOptions m_items;
	};

	class CInput : public CElement { typedef CElement TBase;
	public:
		 CInput (CAxWindow& _browser, _pc_sz _p_el_id);
		 CInput (void) = delete; CInput (const CInput&) = delete; CInput (CInput&&) = delete;
		~CInput (void) = default;

		CString  Text (void) const;
		err_code Text(_pc_sz _p_txt);

	private:
		CInput& operator = (const CInput&) = delete; CInput& operator = (CInput&&) = delete;
	};
}}}}

#endif/*_WEB_IE_HTML_H_INCLUDED*/