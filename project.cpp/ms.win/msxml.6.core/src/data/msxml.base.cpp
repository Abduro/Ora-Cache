/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2024 at 19:51:14.8089054, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack MSXML data base provider interface implementation file;
*/
#include "msxml.base.h"

using namespace shared::xml::ms;

/////////////////////////////////////////////////////////////////////////////

CProv_Base:: CProv_Base (void) { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CProv_Base:: CProv_Base (const CProv_Base& _ref) : CProv_Base() { *this = _ref; }
CProv_Base::~CProv_Base (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CXmlDoc&     CProv_Base::Doc (void) const { return this->m_x_doc; }
CXmlDoc&     CProv_Base::Doc (void)       { return this->m_x_doc; }
TErrorRef    CProv_Base::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

CProv_Base&  CProv_Base::operator = (const CProv_Base& _ref) { *this << _ref.Doc(); return *this; }
CProv_Base&  CProv_Base::operator <<(const CXmlDoc& _doc) { this->Doc() = _doc; return *this; }