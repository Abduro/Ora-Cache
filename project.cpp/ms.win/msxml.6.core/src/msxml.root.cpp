/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Jun-2025 at 12:55:18.420,UTC+4, Batumi;
	This is Ebo Pack MSXML document root node wrapper interface implementation file;
*/
#include "msxml.root.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

CRoot:: CRoot(void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CRoot:: CRoot(const TXmlElementPtr _ptr) : CRoot() { *this << _ptr; }
CRoot::~CRoot(void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CRoot::Atts (CNode_Atts& _atts) {
	_atts;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false)
		return (this->m_error << (err_code) TErrCodes::eExecute::eState);

	::ATL::CComPtr<IXMLDOMNamedNodeMap> root_atts;

	err_code n_result = m_ptr->get_attributes(&root_atts);
	if (__failed(n_result))
		return (this->m_error << n_result);

	LONG lCount = 0;
	n_result = root_atts->get_length(&lCount);
	if (__failed(n_result))
		return (this->m_error << n_result);

	for (LONG i_ = 0; i_ < lCount; i_++) {
		::ATL::CComPtr<IXMLDOMNode> node_;
		n_result = root_atts->get_item(i_, &node_);

		if (__failed(n_result))
			return (this->m_error << n_result);

		_bstr_t b_name;
		n_result = node_->get_nodeName(b_name.GetAddress());
		if (__failed(n_result))
			return (this->m_error << n_result);

		CAttribute att_;
		att_.Name((_pc_sz) b_name);

		n_result = node_->get_nodeValue(&att_.Value());
		if (__failed(n_result))
			return (this->m_error << n_result);

		n_result = _atts.Add(att_);
		if (__failed(n_result))
			return (this->m_error << n_result);
	}
	return m_error;
}

TError& CRoot::Error (void) const { return m_error; }

bool    CRoot::Is_valid (void) const { return nullptr != this->Ptr(); }

const
TNodePtr& CRoot::Ptr (void) const { return this->m_ptr; }
TNodePtr& CRoot::Ptr (void)       { return this->m_ptr; }

err_code CRoot::Kids (CNode_Enum& _kids) {
	_kids;
	this->m_error << __METHOD__ << __s_ok;
	if (this->Is_valid() == false)
		return (this->m_error << (err_code) TErrCodes::eExecute::eState);

	::ATL::CComPtr<IXMLDOMNodeList> kids_;

	err_code n_result = m_ptr->get_childNodes(&kids_);
	if (__failed(n_result))
		return (this->m_error << n_result);

	LONG lCount = 0;
	n_result = kids_->get_length(&lCount);
	if (__failed(n_result))
		return (this->m_error << n_result);

	for (LONG i_ = 0; i_ < lCount; i_++) {

		::ATL::CComPtr<IXMLDOMNode> node_ ;
		n_result = kids_->get_item(i_,  &node_);

		if (__failed(n_result))
			return (this->m_error << n_result);

		DOMNodeType eType = NODE_INVALID ;
		n_result = node_->get_nodeType(&eType);
		if (__failed(n_result))
			return (this->m_error << n_result);

		if (NODE_ELEMENT != eType)
			continue;

		::ATL::CComQIPtr<IXMLDOMElement> el_;
		n_result = node_.QueryInterface(&el_);
		if (__failed(n_result))
			return (this->m_error << n_result);

		if (nullptr == el_)
			return (this->m_error << E_NOINTERFACE);

		CRoot ptr_; ptr_ = el_;
		CNode kid_;
		n_result = ptr_.Name  (kid_.Name_Ref());   if (__failed(n_result)) return (this->m_error << n_result);
		n_result = ptr_.Text  (kid_.Text_Ref());   if (__failed(n_result)) return (this->m_error << n_result);
		n_result = ptr_.Atts  (kid_.Attributes()); if (__failed(n_result)) return (this->m_error << n_result);

		CNode_Enum* p_kids  = const_cast<CNode_Enum*>(kid_.Children());
		if (nullptr != p_kids){
			n_result = ptr_.Kids(*p_kids);
			if (__failed(n_result))
				return (this->m_error << n_result);
		}
		n_result = _kids.Add(kid_);
		if (__failed(n_result))
			return (this->m_error << n_result);
	}
	return this->Error();
}

err_code CRoot::Name  (CAtlString& _name) {
	_name;
	this->m_error << __METHOD__ << __s_ok;
	if (this->Is_valid() == false)
		return (this->m_error << (err_code) TErrCodes::eExecute::eState);

	_bstr_t bs_name;
	err_code n_result = m_ptr->get_nodeName(bs_name.GetAddress());
	if (__s_ok == n_result)
		_name = (_pc_sz)bs_name;
	else
		this->m_error << n_result;

	return this->Error();
}

err_code CRoot::Text  (CAtlString& _text) {
	_text;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false)
		return (this->m_error << (err_code) TErrCodes::eExecute::eState);

	::ATL::CComPtr<IXMLDOMNode> kid_;

	err_code n_result = m_ptr->get_firstChild(&kid_);
	if (__failed(n_result))
		return this->m_error << n_result; // an error;

	if (nullptr == kid_)
		return this->m_error; // no text ;

	DOMNodeType eType = NODE_INVALID;

	n_result = kid_->get_nodeType(&eType);
	if (__failed(n_result))
		return  (this->m_error << n_result);

	if (NODE_TEXT != eType)
		return this->m_error; // no text node;

	variant_t val_;
	n_result = kid_->get_nodeValue(&val_);
	if (__failed(n_result))
		return  (this->m_error << n_result);

	if (VT_BSTR == val_.vt)
		_text = val_.bstrVal;

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CRoot& CRoot::operator << (const TXmlElementPtr _p) { m_ptr = _p; return *this; }
CRoot& CRoot::operator <<(const CNode_Atts& _atts) {
	_atts;
	this->m_error << __METHOD__ << __s_ok;

	for (TAttributes::const_iterator it_ = _atts.Ref().begin(); it_ != _atts.Ref().end(); ++it_) {
		err_code n_result = m_ptr->setAttribute(_bstr_t(it_->first), _variant_t(it_->second.ToText().GetString()));
		if (__failed(n_result)) {
			this->m_error << n_result; break;
		}
	}

	return *this;
}

const
TNodePtr& CRoot::operator ()(void) const { return this->Ptr(); }
TNodePtr& CRoot::operator ()(void)       { return this->Ptr(); }