/*
	Createed by Tech_dog (ebontrop@gmail.com) on 08-Oct-2026 at 17:26:19.386, UTC+4, Batumi, Thursday;
	This is IE HTML document content wrapper interface implementation file.
*/
#include "web.ie.content.h"
#include "web.ie.accessor.h"
#include "web.ie.host.wnd.h"

using namespace ::ex_ui::web::IE;
using namespace ::ex_ui::web::IE::core;

#pragma region cls::CCharset{}

CCharset::CCharset (TBrwWndPtr& _p_wrapper) : m_control(_p_wrapper) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CCharset::Error (void) const { return this->m_error; }
const
CString& CCharset::Get (void) {
	this->m_error << __METHOD__ << __s_ok;
	
	if (false == this->m_control) {
		this->m_error <<__e_not_inited; return this->m_charset;
	}
	CComPtr<IHTMLDocument2> p_document;

	CAccessor acc(*this->m_control);
	this->m_error << acc.Document2(p_document);

	if (this->m_error) // checking p_document for 'null' value is not required because the accessor function returns an error in such case;
		return this->m_charset;	

	_bstr_t bstrCharset;
	this->m_error << p_document->get_charset(bstrCharset.GetAddress());

	if (!this->m_error)
		this->m_charset = (_pc_sz) bstrCharset;

	return this->m_charset;
}

err_code CCharset::Set (_pc_sz pszCharset/*, const bool bRefresh*/) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->m_control)
		return this->m_error <<__e_not_inited;

	CComPtr<IHTMLDocument2> p_document;

	CAccessor acc(*this->m_control);
	this->m_error << acc.Document2(p_document);

	if (this->m_error) // checking p_document for 'null' value is not required because the accessor function returns an error in such case;
		return this->Error();

	this->m_error << p_document->put_charset(_bstr_t(pszCharset));
	return this->Error();
}

#pragma endregion
#pragma region cls::CContent{}

CContent:: CContent (TBrwWndPtr& _p_wrapper) : m_control(_p_wrapper), m_charset(_p_wrapper) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CContent::~CContent (void) {}

const
CCharset&  CContent::Charset (void) const { return this->m_charset; }
CCharset&  CContent::Charset (void)       { return this->m_charset; }

TError&    CContent::Error (void) const { return this->m_error; }
const
 CString&  CContent::Get (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->m_control) {
		this->m_error  <<__e_not_inited; return this->m_content;
	}
	TDocument3Ptr p_document;

	CAccessor acc(*this->m_control);
	this->m_error << acc.Document3(p_document);
	if (this->m_error)
		return this->m_content;

	TElementPtr root_;

	this->m_error << p_document->get_documentElement(&root_);
	if (this->Error())
		return this->m_content;

	_bstr_t content_;

	this->m_error << root_->get_outerHTML(content_.GetAddress());
	if (this->Error() == false)
		this->m_content = (_pc_sz) content_;

	return this->m_content;
}

bool CContent::Is_valid (void) const {
	return (this->m_error << (nullptr != this->m_control ? __s_ok : __e_not_inited)).Is() == false;
}

CString  CContent::Title (void) const {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false) { return CString(); }

	TDocument2Ptr p_document;

	CAccessor acc(*this->m_control);
	this->m_error << acc.Document2(p_document);
	if (this->m_error)
		return CString();

	CString cs_title;
	_bstr_t bs_title;

	this->m_error << p_document->get_title(bs_title.GetAddress());
	if (m_error)
		return cs_title;
	cs_title = bs_title.GetBSTR();
	return cs_title;
}

err_code CContent::Title (_pc_sz pTitle) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false) return this->Error();

	TDocument2Ptr p_document;

	CAccessor acc(*this->m_control);
	this->m_error << acc.Document2(p_document);
	if (this->Error())
		return this->Error();

	_bstr_t bs_title(pTitle);
	this->m_error << p_document->put_title(bs_title);

	return this->Error();
}

#pragma endregion