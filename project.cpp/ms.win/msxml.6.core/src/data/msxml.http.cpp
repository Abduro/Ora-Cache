/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2024 at 00:25:26.4982011, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack MSXML http data provider interface implementation file;
*/
#include "msxml.http.h"

using namespace shared::xml::ms::http;

/////////////////////////////////////////////////////////////////////////////

CProvider:: CProvider (void) : TBase() { TBase::m_error >> __CLASS__; }
CProvider:: CProvider (const CProvider& _ref) : CProvider() { *this = _ref; }
CProvider::~CProvider (void) {}

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

CProvider&  CProvider::operator = (const CProvider& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }