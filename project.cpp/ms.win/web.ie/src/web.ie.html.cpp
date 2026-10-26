/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Nov-2014 at 6:00:00p, GMT+3, Taganrog, Saturday;
	This is Ebo Pack UIX library HTML element accessor class implementation file.
	-----------------------------------------------------------------------------
	Adopted to v15 on 28-May-2018 at 9:37:51p, UTC+7, Phuket, Rawai, Monday;
*/
#include "web.ie.html.h"
#include "web.ie.accessor.h"

using namespace ::ex_ui::web::IE::core;
using namespace ::ex_ui::web::IE::html;
using CValue = COption::CValue;

#pragma region cls::CElement{}

CElement::CElement(CAxWindow& _ctrl_wnd, _pc_sz _p_el_id) : m_ctrl_wnd(_ctrl_wnd), m_el_id(_p_el_id) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (m_ctrl_wnd) {
		CAccessor accessor(this->m_ctrl_wnd);
		accessor.Element(this->m_el_ptr, _p_el_id);
	}
}

CString  CElement::Content (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) {
		this->m_error <<__e_not_inited;
		return CString();
	}

	CString cs_content;

	_bstr_t val_;
	this->m_error << m_el_ptr->get_innerHTML(val_.GetAddress());
	if (this->Error() == false)
		cs_content = (_pc_sz) val_;

	return cs_content;
}

err_code CElement::Content (_pc_sz _p_html) {
	_p_html;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->m_error <<__e_not_inited;

	_bstr_t val_(_p_html);

	this->m_error << this->m_el_ptr->put_innerHTML(val_);
	return  this->Error();
}

TError&  CElement::Error (void) const { return this->m_error; }

bool     CElement::Disabled (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	bool bDisabled = false;

	if (this->Is_valid())
	{
		CComQIPtr<IHTMLElement3> ext_;
		this->m_error << this->m_el_ptr.QueryInterface(&ext_);
		if (this->Error())
			return bDisabled;

		if (!ext_)
			return bDisabled;

		VARIANT_BOOL vDisabled = VARIANT_FALSE;
		this->m_error << ext_->get_isDisabled(&vDisabled);

		if (this->Error() == false)
			 bDisabled = (vDisabled == VARIANT_TRUE);
	}
	return bDisabled;
}

err_code CElement::Disabled (const bool bDisabled) {
	bDisabled;
	this->m_error <<__METHOD__<<__s_ok;

	if (!this->Is_valid())
		return this->m_error <<__e_not_inited;

	CComQIPtr<IHTMLElement3> ext_;
	this->m_error << this->m_el_ptr.QueryInterface(&ext_);
	if (this->Error())
		return this->Error();
	if (!ext_)
		return this->m_error <<__e_not_impl;

	this->m_error << ext_->put_disabled(bDisabled ? VARIANT_TRUE : VARIANT_FALSE);
	return this->Error();
}

CString  CElement::Identifier (void) const { return this->m_el_id; }
bool     CElement::Is_valid (void) const { return (m_el_ptr != false); }

rect_t   CElement::Rectangle (void) const {
	rect_t rc_ = {0};
	if (this->Is_valid() == false)
		return rc_;
	else
	{
		m_el_ptr->get_offsetLeft  (&rc_.left  );
		m_el_ptr->get_offsetTop   (&rc_.top   );
		m_el_ptr->get_offsetWidth (&rc_.right ); rc_.right  += rc_.left;
		m_el_ptr->get_offsetHeight(&rc_.bottom); rc_.bottom += rc_.top;
	}
	return rc_;
}

CString  CElement::Style (void) const {
	this->m_error <<__METHOD__<<__s_ok;
	
	if (false == this->Is_valid()) {
		this->m_error <<__e_not_inited;
		return CString();
	}

	CString cs_style;

	CComPtr<IHTMLStyle> pStyle;
	this->m_error << m_el_ptr->get_style(&pStyle);
	if (this->Error() || !pStyle)
		return cs_style;

	_bstr_t bs_style;
	this->m_error << pStyle->toString(bs_style.GetAddress());
	if (this->Error() == false)
		cs_style = static_cast<_pc_sz>(bs_style);

	return cs_style;
}

err_code CElement::Style (_pc_sz _p_style) {
	_p_style;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->m_error <<__e_not_inited;

	this->m_error << this->m_el_ptr->setAttribute(_bstr_t(_T("style")), _variant_t(_p_style), 0);
	return  this->Error();
}

bool CElement::Visible (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	bool b_result = false; // this is the default value for error cases: if this class is not initialized or COM-object method fails; 

	if (false == this->Is_valid()) {
		this->m_error <<__e_not_inited;
		return b_result;
	}

	CComPtr<IHTMLStyle> pStyle;
	this->m_error << this->m_el_ptr->get_style(&pStyle);
	if (this->Error() || !pStyle)
		return b_result;

	_variant_t val_;
	this->m_error << pStyle->getAttribute(_bstr_t(_T("display")), 0, &val_);
	if (this->Error())
		return b_result;

	switch (val_.vt) {
	case VT_BSTR: { CString cs_value(val_.bstrVal); cs_value.Trim(); b_result = (0 == cs_value.CompareNoCase(_T("block"))); } break;
	case VT_BOOL: { b_result = (VARIANT_TRUE == val_.boolVal); } break;
	}
	return b_result;
}

err_code CElement::Visible (const bool b_value) {
	b_value;
	this->m_error <<__METHOD__<<__s_ok;
	if (false == this->Is_valid())
		return this->m_error <<__e_not_inited;

	CComPtr<IHTMLStyle> pStyle;
	this->m_error << this->m_el_ptr->get_style(&pStyle);

	if (false){}
	else if (this->Error()){}
	else if (!pStyle) this->m_error <<__e_not_impl;
	else {
		_variant_t val_ = (b_value ? _T("block") : _T("none"));
		this->m_error << pStyle->setAttribute(_bstr_t(_T("display")), val_,  0);
	}
	return this->Error();
}

#pragma endregion
#pragma region cls::CInput{}

CInput::CInput(CAxWindow& _browser, _pc_sz _p_el_id) : TBase(_browser, _p_el_id) { TBase::m_error >>__CLASS__; }

CString CInput::Text (void) const {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == TBase::Is_valid()) {
		TBase::m_error <<__e_not_inited; return CString();
	}
	
	CComQIPtr<IHTMLInputTextElement> pInput;
	TBase::m_error << TBase::m_el_ptr.QueryInterface(&pInput);
	if (TBase::Error() || !pInput)
		return CString();

	_bstr_t bs_val;
	TBase::m_error << pInput->get_value(bs_val.GetAddress());
	if (TBase::Error())
		return CString();

	CString cs_text;
	cs_text = static_cast<_pc_sz>(bs_val);
	return cs_text;
}

err_code CInput::Text (_pc_sz _p_text) {
	_p_text;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == TBase::Is_valid()) {
		return TBase::m_error <<__e_not_inited;
	}

	CComQIPtr<IHTMLInputTextElement> pInput;
	TBase::m_error << TBase::m_el_ptr.QueryInterface(&pInput);
	if (TBase::Error())
		return TBase::Error();
	if (!pInput)
		return TBase::m_error <<__e_not_impl;

	_bstr_t bs_text(_p_text);
	TBase::m_error <<  pInput->put_value(bs_text);

	return TBase::Error();
}

#pragma endregion
#pragma region cls::COption{}

COption::COption (void) : m_selected(false){}
COption::COption (COption&& _victim) : COption() { *this = _victim; }
COption::COption (const COption& _src) : COption() { *this = _src; }

bool     COption::Selected (void) const { return this->m_selected; }
void     COption::Selected (const bool _yes_or_no) {  m_selected = _yes_or_no; }

_pc_sz   COption::Text (void) const { return (_pc_sz) this->m_text; }
void     COption::Text (_pc_sz _p_txt) { this->m_text = _p_txt; }
const
CValue&  COption::Value (void) const { return this->m_value; }
CValue&  COption::Value (void)       { return this->m_value; }

COption& COption::operator = (const COption& _src) { *this << _src.Text() << _src.Value(); return *this; }
COption& COption::operator <<(_pc_sz _p_text) { this->Text(_p_text); return *this; }
COption& COption::operator <<(const CValue& _value) { this->Value() = _value; return *this; }

COption& COption::operator = (COption&& _victim) {
	*this = (const COption&)_victim; return *this;
}

#pragma endregion
#pragma region cls::CSelect{}

CSelect::CSelect(CAxWindow& _browser, _pc_sz _p_el_id) : TBase(_browser, _p_el_id) { TBase::m_error >>__CLASS__; }

long_t CSelect::Index (void) const {

	for (size_t j_ = 0; j_ < m_items.size(); j_++){
		if (m_items[j_].Selected())
			return static_cast<long_t>(j_);
	}
	return -1;
}

err_code CSelect::Index (const long_t  _n_index) {
	_n_index;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_n_index < 0 || this->Is_empty() || _n_index > static_cast<long_t>(this->m_items.size()) - 1)
		return TBase::m_error <<__e_index;

	const long_t curr_ndx = this->Index();
	if (curr_ndx == _n_index )
		return TBase::m_error <<__s_false;

	CComQIPtr<IHTMLSelectElement> pSelect;
	TBase::m_error << TBase::m_el_ptr.QueryInterface(&pSelect);

	if (TBase::Error()) return TBase::Error();
	if (!pSelect) return TBase::m_error <<__e_not_inited;

	TBase::m_error << pSelect->put_selectedIndex(_n_index);
	if (TBase::Error())
		return TBase::Error();

	try {
		if (-1 != curr_ndx)
			this->m_items.at(curr_ndx).Selected(false); // unselects the previously selected option;

		m_items.at(_n_index).Selected(true); // selects new option;

	} catch (const ::std::out_of_range&) { TBase::m_error <<__e_index; }

	return TBase::Error();
}

bool   CSelect::Is_empty (void) const { return this->m_items.empty(); }
bool   CSelect::Is_valid (void) const { return this->Is_empty() == false;}

const
TOptions& CSelect::Items (void) const { return m_items; }
err_code  CSelect::Items (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	CComQIPtr<IHTMLSelectElement> pSelect;
	TBase::m_el_ptr.QueryInterface(&pSelect);
	if (!pSelect)
		return TBase::Error();

	long_t lCount = 0;
	TBase::m_error << pSelect->get_length(&lCount);
	if (TBase::Error())
		return TBase::Error();

	for (long_t i_ = 0; i_ < lCount; i_++) {

		CComPtr<IDispatch> pdispOption;
		TBase::m_error << pSelect->item(_variant_t(i_), _variant_t(i_), &pdispOption);
		if (TBase::Error())
			break;

		::ATL::CComQIPtr<IHTMLOptionElement> pSelectOption;
		TBase::m_error <<  pdispOption.QueryInterface(&pSelectOption);
		if (TBase::Error() || !pSelectOption)
			break;
		try
		{
			COption item_;
			bstr_t bs_txt;

			TBase::m_error << pSelectOption->get_text(bs_txt.GetAddress());
			if (TBase::Error())
				break;
			item_.Text((_pc_sz)bs_txt);

			bstr_t bs_val;
			TBase::m_error << pSelectOption->get_value(bs_val.GetAddress());
			if (TBase::Error())
				break;
			item_.Value().Set((_pc_sz)bs_val);

			VARIANT_BOOL bSelected = VARIANT_FALSE;
			TBase::m_error <<  pSelectOption->get_selected(&bSelected);
			if (TBase::Error())
				break;
			item_.Selected(VARIANT_TRUE == bSelected);

			m_items.push_back(item_);
		}
		catch(::std::bad_alloc&) { TBase::m_error << __e_no_memory; break; }
		catch(_com_error& err_obj) { TBase::m_error = err_obj; break; }
	}
	return TBase::Error();
}

const
COption&  CSelect::Selected (void) const
{
	const long_t l_ndx = this->Index();

	if (0 > l_ndx || this->Is_empty() || l_ndx > this->Items().size() - 1) {
		static COption invalid_;
		return invalid_;
	}

	return m_items[l_ndx];
}

err_code  CSelect::Selected (_pc_sz _p_value) {
	_p_value;
	TBase::m_error <<__METHOD__<<__s_ok;
	for (size_t i_ = 0; i_ < this->m_items.size(); i_++)
	{
		const COption& item_ = m_items[i_];
		if (item_.Value().Has(_p_value)) {
			return this->Index( static_cast<long_t>(i_));
		}
	}
	return TBase::m_error <<__e_not_found;
}

#pragma endregion
#pragma region cls::CValue{}

CValue::CValue (void) {}
CValue::CValue (const CValue& _src) : CValue() { *this = _src; }

bool   CValue::AsBool (void) const {

	if (this->m_value.IsEmpty()) return false;
	if (this->m_value.CompareNoCase(_T("yes")) == 0) return true;
	if (this->m_value.CompareNoCase(_T("true")) == 0) return true;

	return !!this->AsLong();
}
long_t CValue::AsLong (void) const { return ::_tstol(this->m_value); }

bool   CValue::Has (_pc_sz _p_value) const { return (0 == this->m_value.CompareNoCase(_p_value)); }

_pc_sz CValue::Get (void) const { return (_pc_sz) this->m_value; }
void   CValue::Set (_pc_sz _p_value) { this->m_value = _p_value; this->m_value.Trim(); }

CValue& CValue::operator = (const CValue& _src) { *this << _src.Get(); return *this; }
CValue& CValue::operator <<(_pc_sz _p_value) { this->Set(_p_value); return *this; }

#pragma endregion