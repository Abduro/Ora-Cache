#ifndef _MSXML_HTTP_H_INCLUDED
#define _MSXML_HTTP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Apr-2024 at 00:23:50.9188115, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack MSXML http data provider interface declaration file;
*/
#include "msxml.base.h"

namespace shared { namespace xml { namespace ms { namespace http {

	using CError = shared::sys_core::CError;
	using TBase  = shared::xml::ms::CProv_Base;

	class CProvider : public TBase {
	public:
		 CProvider (void);
		 CProvider (const CProvider&);
		 CProvider (CProvider&&) = delete;
		~CProvider (void);

	public:
		CProvider& operator = (const CProvider&);
		CProvider& operator = (CProvider&&) = delete;
	};
}}}}

#endif/*_MSXML_HTTP_H_INCLUDED*/