#ifndef _UIXELEMENT_H_7F592FBD_AE95_40d1_B6B0_DFCE630991B4_INCLUDED
#define _UIXELEMENT_H_7F592FBD_AE95_40d1_B6B0_DFCE630991B4_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Nov-2014 at 5:47:22p, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library HTML element wrapper class declaration file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 30-Jul-2018 at 2:51:25p, UTC+7, Novosibirsk, Monday;
*/
#include "shared.web.defs.h"

namespace ex_ui { namespace web
{
	typedef ::ATL::CComPtr<IHTMLElement> TElementObject;
	class CHtmlElement
	{
	protected:
		TElementObject  m_el;
		CStringW        m_el_id;
		CAxWindow&      m_browser;
	public:
		 CHtmlElement(::ATL::CAxWindow& _browser, LPCWSTR lpszId);
		~CHtmlElement(void);
	public:
		CStringW        Content(void)             const;        // gets inner html of the element
		HRESULT         Content(LPCWSTR lpszInner)     ;        // sets inner html of the element
		bool            Disabled   (void)         const;
		HRESULT         Disabled   (const bool)        ;
		CStringW        Identifier (void)         const;
		bool            IsValid    (void)         const;
		RECT            Rectangle  (void)         const;
		CStringW        Style      (void)         const;
		HRESULT         Style      (LPCWSTR)           ;        // adds style to existing one; if already defined, it is replaced;
		bool            Visible    (void)         const;
		HRESULT         Visible    (const bool)        ;
	};

	class CHtmlOption
	{
	private:
		CStringW        m_value;
		CStringW        m_text;
		bool            m_bSelected;
	public:
		 CHtmlOption(void);
		~CHtmlOption(void);
	public:
		bool           HasValue(LPCWSTR)         const;
		bool           Selected(void)            const;
		VOID           Selected(const bool)           ;
		LPCWSTR        Text (void)               const;
		VOID           Text (LPCWSTR)                 ;
		LPCWSTR        Value(void)               const;
		VOID           Value(LPCWSTR)                 ;
		bool           ValueAsBool(void)         const;
		LONG           ValueAsLong(void)         const;
	};

	typedef ::std::vector<CHtmlOption> THtmlOptions;

	class CHtmlSelect :
		public  CHtmlElement
	{
		typedef CHtmlElement TBase;
	private:
		THtmlOptions      m_items;
	public:
		 CHtmlSelect(::ATL::CAxWindow&, LPCWSTR lpszId);
		~CHtmlSelect(void);
	public:
		const
		THtmlOptions&     Options (void)            const;
		LONG              Selected(void)            const;
		HRESULT           Selected(const LONG lIndex)    ;
		HRESULT           Selected(LPCWSTR lpszValue)    ;
		const CHtmlOption&SelectedOption(void)      const;
	};

	class CHtmlInput :
		public  CHtmlElement
	{
		typedef CHtmlElement TBase;
	public:
		 CHtmlInput(::ATL::CAxWindow&, LPCWSTR lpszId);
		~CHtmlInput(void);
	public:
		CStringW        Text(void)const;
		HRESULT         Text(LPCWSTR);
	};
}}

#endif/*_UIXELEMENT_H_7F592FBD_AE95_40d1_B6B0_DFCE630991B4_INCLUDED*/