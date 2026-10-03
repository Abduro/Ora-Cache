/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Nov-2014 at 6:00:00p, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library HTML element accessor class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:37:51p, UTC+7, Phuket, Rawai, Monday;
*/
#if (0)
#include "shared.web.html.el.h"
#include "shared.web.obj.access.h"

using namespace ex_ui::web;
using namespace ex_ui::web::core;

/////////////////////////////////////////////////////////////////////////////

CHtmlElement::CHtmlElement(::ATL::CAxWindow& _browser, LPCWSTR lpszId):m_browser(_browser), m_el_id(lpszId)
{
	if (m_browser)
	{
		CWebBrowserObjectAccessor acc(m_browser);
		acc.ElementObject(m_el, lpszId);
	}
}

CHtmlElement::~CHtmlElement(void)
{
}

/////////////////////////////////////////////////////////////////////////////

CStringW    CHtmlElement::Content(void)const
{
	CStringW cs_content;
	if (!m_el)
		return cs_content;
	_bstr_t val_;
	HRESULT hr_ = m_el->get_innerHTML(val_.GetAddress());
	if (!FAILED(hr_))
		cs_content = (LPCWSTR)val_;
	return cs_content;
}

HRESULT     CHtmlElement::Content(LPCWSTR lpszInner)
{
	if (!m_el)
		return OLE_E_BLANK;
	_bstr_t val_(lpszInner);
	HRESULT hr_ = m_el->put_innerHTML(val_);
	return  hr_;
}

bool        CHtmlElement::Disabled(void)const
{
	bool bDisabled = false;
	if (this->IsValid())
	{
		CComQIPtr<IHTMLElement3> ext_;
		HRESULT hr_ = m_el.QueryInterface(&ext_);
		if (FAILED(hr_))
			return bDisabled;
		if (!ext_)
			return bDisabled;
		VARIANT_BOOL vDisabled = VARIANT_FALSE;
		hr_ = ext_->get_isDisabled(&vDisabled);
		if (FAILED(hr_))
			return bDisabled;
		bDisabled = (vDisabled == VARIANT_TRUE);
	}
	return bDisabled;
}

HRESULT     CHtmlElement::Disabled(const bool bDisabled)
{
	if (!this->IsValid())
		return OLE_E_BLANK;
	CComQIPtr<IHTMLElement3> ext_;
	HRESULT hr_ = m_el.QueryInterface(&ext_);
	if (FAILED(hr_))
		return hr_;
	if (!ext_)
		return (hr_ = E_NOINTERFACE);

	hr_ = ext_->put_disabled(bDisabled ? VARIANT_TRUE : VARIANT_FALSE);
	return hr_;
}

CStringW    CHtmlElement::Identifier (void)const
{
	return m_el_id;
}

bool        CHtmlElement::IsValid(void)const
{
	return (m_el != false);
}

RECT        CHtmlElement::Rectangle(void) const
{
	RECT rc_ = {0};
	if (!m_el)
		return rc_;
	else
	{
		m_el->get_offsetLeft  (&rc_.left  );
		m_el->get_offsetTop   (&rc_.top   );
		m_el->get_offsetWidth (&rc_.right ); rc_.right  += rc_.left;
		m_el->get_offsetHeight(&rc_.bottom); rc_.bottom += rc_.top;
	}
	return rc_;
}

CStringW    CHtmlElement::Style(void)const
{
	CStringW cs_style;

	if (!this->IsValid())
		return cs_style;

	::ATL::CComPtr<IHTMLStyle> pStyle;
	HRESULT hr_ = m_el->get_style(&pStyle);
	if (FAILED(hr_) || !pStyle)
		return cs_style;

	_bstr_t bs_style;
	hr_ = pStyle->toString(bs_style.GetAddress());
	if (SUCCEEDED(hr_))
		cs_style = static_cast<LPCWSTR>(bs_style);

	return cs_style;
}

HRESULT     CHtmlElement::Style(LPCWSTR lpszStyle)
{
	if (!this->IsValid())
		return OLE_E_BLANK;
	HRESULT hr_ = m_el->setAttribute(_bstr_t(_T("style")), _variant_t(lpszStyle), NULL);
	return  hr_;
}

bool        CHtmlElement::Visible(void) const
{
	bool b_result = true;

	if (!this->IsValid())
		return b_result;

	::ATL::CComPtr<IHTMLStyle> pStyle;
	HRESULT hr_ = m_el->get_style(&pStyle);
	if (FAILED(hr_) || !pStyle)
		return b_result;

	_variant_t val_;
	hr_ = pStyle->getAttribute(_bstr_t(_T("display")), 0, &val_);
	if (FAILED(hr_))
		return b_result;

	switch (val_.vt)
	{
	case VT_BSTR:
		{
			::ATL::CStringW cs_value(val_.bstrVal);
			cs_value.Trim();
			b_result = (0 == cs_value.CompareNoCase(_T("block")));
		} break;
	case VT_BOOL:
		{
			b_result = (VARIANT_TRUE == val_.boolVal);
		} break;
	}

	return b_result;
}

HRESULT     CHtmlElement::Visible(const bool b_value)
{
	if (!this->IsValid())
		return OLE_E_BLANK;
	::ATL::CComPtr<IHTMLStyle> pStyle;
	HRESULT hr_ = m_el->get_style(&pStyle);
	if (FAILED(hr_))
		return hr_;
	else if (!pStyle)
		return(hr_ = E_NOINTERFACE);
	else
	{
		_variant_t val_ = (b_value ? _T("block") : _T("none"));
		hr_ = pStyle->setAttribute(_bstr_t(_T("display")), val_,  0);
	}

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

CHtmlOption:: CHtmlOption(void) : m_bSelected(false)
{
}

CHtmlOption::~CHtmlOption(void)
{
}

/////////////////////////////////////////////////////////////////////////////

bool        CHtmlOption::HasValue(LPCWSTR pszValue)const
{
	return (0 == m_value.CompareNoCase(pszValue));
}

bool        CHtmlOption::Selected(void)const
{
	return m_bSelected;
}

VOID        CHtmlOption::Selected(const bool bSelected)
{
	m_bSelected = bSelected;
}

LPCWSTR     CHtmlOption::Text (void)const
{
	return m_text;
}

VOID        CHtmlOption::Text (LPCWSTR pszText)
{
	m_text = pszText;
}

LPCWSTR     CHtmlOption::Value(void)const
{
	return m_value;
}

VOID        CHtmlOption::Value(LPCWSTR pszValue)
{
	m_value = pszValue;
	m_value.Trim();
}

bool        CHtmlOption::ValueAsBool(void)const
{
	if (m_value.IsEmpty()) return false;
	if (m_value.CompareNoCase(_T("yes")) == 0)return true;
	if (m_value.CompareNoCase(_T("true")) == 0) return true;
	const LONG lValue = ::_tstol(m_value);
	return !!lValue;
}

LONG        CHtmlOption::ValueAsLong(void)const
{
	return ::_tstol(m_value);
}

/////////////////////////////////////////////////////////////////////////////

CHtmlSelect::CHtmlSelect(::ATL::CAxWindow& _wnd, LPCWSTR lpszId) : TBase(_wnd, lpszId)
{
	::ATL::CComQIPtr<IHTMLSelectElement> pSelect;
	TBase::m_el.QueryInterface(&pSelect);
	if (!pSelect)
		return;

	LONG lCount = 0;
	HRESULT hr_ = pSelect->get_length(&lCount);
	if (FAILED(hr_))
		return;
	for (LONG i_ = 0; i_ < lCount; i_++) {
		::ATL::CComPtr<IDispatch> pdispOption;
		hr_ = pSelect->item(_variant_t(i_), _variant_t(i_), &pdispOption);
		if (FAILED(hr_))
			return;
		::ATL::CComQIPtr<IHTMLOptionElement> pSelectOption;
		hr_ = pdispOption.QueryInterface(&pSelectOption);
		if (FAILED(hr_))
			return;
		if (!pSelectOption)
			return;
		try
		{
			CHtmlOption item_;
			bstr_t bs_txt;

			hr_ = pSelectOption->get_text(bs_txt.GetAddress());
			if (FAILED(hr_))
				break;
			item_.Text((LPCWSTR)bs_txt);

			bstr_t bs_val;
			hr_ = pSelectOption->get_value(bs_val.GetAddress());
			if (FAILED(hr_))
				break;
			item_.Value((LPCWSTR)bs_val);

			VARIANT_BOOL bSelected = VARIANT_FALSE;
			hr_ = pSelectOption->get_selected(&bSelected);
			if (FAILED(hr_))
				break;
			item_.Selected(VARIANT_TRUE == bSelected);

			m_items.push_back(item_);
		}
		catch(::std::bad_alloc&)
		{
			hr_ = E_OUTOFMEMORY; break;
		}
		catch(_com_error& err_obj)
		{
			hr_ = err_obj.Error(); break;
		}
	}
}

CHtmlSelect::~CHtmlSelect(void)
{
}

/////////////////////////////////////////////////////////////////////////////

const
THtmlOptions& CHtmlSelect::Options(void) const
{
	return m_items;
}

LONG        CHtmlSelect::Selected(void) const
{
	for (size_t j_ = 0; j_ < m_items.size(); j_++){
		if (m_items[j_].Selected())
			return static_cast<LONG>(j_);
	}
	return -1;
}

HRESULT     CHtmlSelect::Selected(const LONG lIndex)
{
	::ATL::CComQIPtr<IHTMLSelectElement> pSelect;
	HRESULT hr_ = TBase::m_el.QueryInterface(&pSelect);
	if (FAILED(hr_))
		return hr_;
	if (!pSelect)
		return (hr_ = E_NOINTERFACE);

	hr_ = pSelect->put_selectedIndex(lIndex);
	if (FAILED(hr_))
		return hr_;

	const LONG selected_ = this->Selected();
	if (-1 != selected_)
		m_items[selected_].Selected(false);

	m_items[lIndex].Selected(true);

	return hr_;
}

HRESULT     CHtmlSelect::Selected(LPCWSTR lpszValue)
{
	for (size_t i_ = 0; i_ < m_items.size(); i_++)
	{
		const CHtmlOption& item_ = m_items[i_];
		if (item_.HasValue(lpszValue))
		{
			return this->Selected(
							static_cast<LONG>(i_)
						);
		}
	}
	return TYPE_E_ELEMENTNOTFOUND;
}
const
CHtmlOption&CHtmlSelect::SelectedOption(void) const
{
	static CHtmlOption invalid_;
	const LONG selected_ = this->Selected();
	if (-1 == selected_)
		return invalid_;

	return m_items[selected_];
}

/////////////////////////////////////////////////////////////////////////////

CHtmlInput::CHtmlInput(::ATL::CAxWindow& _wnd, LPCWSTR lpszId) : TBase(_wnd, lpszId)
{
}

CHtmlInput::~CHtmlInput(void)
{
}

/////////////////////////////////////////////////////////////////////////////

CStringW  CHtmlInput::Text(void)const
{
	CStringW cs_text;
	if (!TBase::m_el)
		return cs_text;

	::ATL::CComQIPtr<IHTMLInputTextElement> pInput;
	HRESULT hr_ = TBase::m_el.QueryInterface(&pInput);
	if (FAILED(hr_))
		return cs_text;
	if (!pInput)
		return cs_text;

	_bstr_t bs_val;
	hr_ = pInput->get_value(bs_val.GetAddress());
	if (FAILED(hr_))
		return cs_text;

	cs_text = static_cast<LPCWSTR>(bs_val);
	return cs_text;
}

HRESULT     CHtmlInput::Text(LPCWSTR lpszText)
{
	if (!TBase::m_el)
		return OLE_E_BLANK;

	::ATL::CComQIPtr<IHTMLInputTextElement> pInput;
	HRESULT hr_ = TBase::m_el.QueryInterface(&pInput);
	if (FAILED(hr_))
		return hr_;
	if (!pInput)
		return (hr_ = E_NOINTERFACE);

	_bstr_t bs_text(lpszText);
	hr_ = pInput->put_value(bs_text);
	return  hr_;
}

#endif